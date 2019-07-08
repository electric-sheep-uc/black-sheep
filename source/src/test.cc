#include "test.hh"

#include "main.cc"

int Test::total;
int Test::pass;

/**
 * main()
 *
 * Entry point into testing.
 *
 * @param argc Number of arguments.
 * @param argv An array of arguments.
 * @return The exit status of the program.
 **/
int main(int argc, char** argv){
  Test* test = new Test();
  test->smartcontroller_cc();
  test->integral_cc();
  if(Test::pass >= Test::total){
    LOG("\n\nSuccess!");
  }else{
    WARNI("\n\nFailed: ", Test::total - Test::pass);
  }
}

void Test::smartcontroller_cc(){
  SmartController* sc = new SmartController("/dev/null");
  unsigned char params[2];
  SmartController::Packet p;
  p.id = 0x01;
  p.cmd = SmartController::CMD::PING;
  p.param = params;
  p.numParam = 0;
  Test::assurt("checksum_ping_send", sc->checkSum(p) == 0xFB);
  p.id = 0x01;
  p.cmd = (SmartController::CMD)0x00; /* Working status */
  p.param = params;
  p.numParam = 0;
  Test::assurt("checksum_ping_return", sc->checkSum(p) == 0xFC);
}

void Test::integral_cc(){
  /* Create test data */
  int width = 640;
  int height = 480;
  LUT::Mask mask = LUT::Mask::BALL;
  unsigned char test[width * height];
  for(int y = 0; y < height; y++){
    for(int x = 0; x < width; x++){
      test[x + (width * y)] = x % 2 == 0 && y % 2 == 0 ? mask : 0;
    }
  }
  /* Run integral */
  Integral* i = new Integral(width, height);
  for(int y = 0; y < height; y++){
    for(int x = 0; x < width; x++){
      i->process(x, y, {0, 0, 0}, test[x + (width * y)]);
    }
  }
  /* Run tests */
  Test::assurt("single_area_case", i->getCount(mask, 0, 0, 0, 0) == 1);
  Test::assurt("four_area_case", i->getCount(mask, 0, 0, 1, 1) == 1);
  Test::assurt("nine_area_case", i->getCount(mask, 0, 0, 2, 2) == 4);
  Test::assurt("rectangle_case", i->getCount(mask, 1, 1, 2, 2) == 1);
}
