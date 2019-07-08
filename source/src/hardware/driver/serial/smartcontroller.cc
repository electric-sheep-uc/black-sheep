#include "smartcontroller.hh"

#include "../../../main.hh"

void SmartController::startComms(){
  /* Make sure this is worth it */
  if(!isActive()){
    WARN("1");
    return;
  }
  struct termios attribs;
  /* Set the attributes of communication */
  if(tcgetattr(fd, &attribs) < 0){
    WARN("2");
    closePort();
    return;
  }
  attribs.c_iflag &= ~(
    IGNBRK |
    BRKINT |
    ICRNL  |
    INLCR  |
    PARMRK |
    INPCK  |
    ISTRIP |
    IXON
  );
  attribs.c_oflag = 0;
  attribs.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
  attribs.c_cflag &= ~(CSIZE | PARENB);
  attribs.c_cflag |= CS8;
  attribs.c_cc[VMIN] = 1;
  attribs.c_cc[VTIME] = 0;
  /* Set baud rate */
  switch(*Main::config->getInt("motor.smart.baud").get()){
    case 115200 :
      if(cfsetispeed(&attribs, B115200) < 0){
        closePort();
        WARN("3");
        return;
      }
      if(cfsetispeed(&attribs, B115200) < 0){
        closePort();
        WARN("4");
        return;
      }
      break;
    case 1000000 :
      if(cfsetispeed(&attribs, B1000000) < 0){
        closePort();
        WARN("5");
        return;
      }
      if(cfsetispeed(&attribs, B1000000) < 0){
        closePort();
        WARN("6");
        return;
      }
      break;
    default:
      WARNM("Baud rate not supported", Main::config->getString("motor.smart.baud").c_str());
      WARN("7");
      return;
  }
  if(tcsetattr(fd, TCSANOW, &attribs) < 0){
    closePort();
    WARN("8");
    return;
  }
}

unsigned char SmartController::checkSum(SmartController::Packet pkt){
  /* Calculate the checksum */
  int sumParam = 0;
  for(int i = 0; i < pkt.numParam; i++){
    sumParam += pkt.param[i];
  }
  return ~(((int)pkt.id + (int)pkt.numParam + 2 + (int)pkt.cmd + (int)sumParam) % 256);
}

void SmartController::writePacket(SmartController::Packet pkt, bool dummy){
  /* Check the input data */
  if(pkt.id >= 255){
    WARN("Invalid packet ID!");
  }
  /* Write the packet */
  writeByte(0xFF); /* Header */
  writeByte(0xFF); /* Header */
  writeByte(pkt.id); /* ID */
  writeByte(pkt.numParam + 2); /* Data length */
  writeByte((unsigned char)pkt.cmd); /* Instruction */
  for(int x = 0; x < pkt.numParam; x++){
    writeByte(pkt.param[x]);
  }
  writeByte(checkSum(pkt)); /* Check sum */
}

SmartController::Packet SmartController::writePacket(SmartController::Packet pkt){
  writePacket(pkt, true);
  /* Only listen for response if we're told there will be one */
  if(pkt.response || pkt.cmd == CMD::PING || pkt.cmd == CMD::READ_DATA){
    return readPacket(pkt);
  }else{
    WARN("Undefined behaviour - asked to not to wait for packet that could respond");
    return pkt;
  }
}

SmartController::Packet SmartController::readPacket(SmartController::Packet pkt){
  int pos = 0;
  int c = 0;
  /* Loop until the packet is complete or we have read 16 bytes */
  while(pos < 16){
    c = readByte();
    /* Make sure we have a valid byte */
    if(c < 0){
      continue;
    }
    /* Check for header part 1 */
    if(pos == 0 && (unsigned char)c == 0xFF){
      ++pos;
      continue;
    }
    /* Check for header part 2 */
    if(pos == 1){
      if((unsigned char)c == 0xFF){
        ++pos;
        continue;
      }else{
        pos = 0;
        WARNB("Corrupted header ", c);
        continue;
      }
    }
    /* Store the motor ID */
    if(pos == 2){
      ++pos;
      pkt.id = (unsigned char)c;
      continue;
    }
    /* Store the data length */
    if(pos == 3){
      ++pos;
      pkt.numParam = (unsigned char)(c - 2);
      if(pkt.numParam < 0){
        pkt.numParam = 0;
        WARNI("Invalid effective length ", c)
      }
      continue;
    }
    /* Read instruction */
    if(pos == 4){
      /* TODO: This is actually the working status! */
      ++pos;
      pkt.cmd = (CMD)c;
      continue;
    }
    /* Read in payload until we hit the checksum */
    if(pos >= 5){
      ++pos;
      /* Read in the parameters */
      if(pos - 6 < pkt.numParam){
        pkt.param[pos - 6] = c;
        continue;
      }else{
        /* TODO: A 1/256 chance that a random packet still gets through. */
        /* Make sure check sum is valid */
        if(checkSum(pkt) != (unsigned)c){
          WARNB("Invalid packet check sum ", (unsigned)c);
          WARNB("Expected ", checkSum(pkt));
          break;
        }
        /* Break out of the loop regardless */
        break;
      }
    }
  }
  return pkt;
}
