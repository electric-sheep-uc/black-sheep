#include "config.hh"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <sys/stat.h>

#include "../log.hh"

Config::Config(){
  temp = NULL;
}

Config::Config(const char* filename, bool isTemplate){
  temp = filename;
  std::ifstream fs(temp, std::fstream::in);
  /* Only template if template given */
  if(isTemplate){
    fs >> jTemp;
    fs.seekg(0);
    fs >> jData;
  }else{
    fs >> jData;
  }
  fs.close();
  /* If we are template, recursively load data */
  if(isTemplate){
    /* Load template defaults into data */
    jData = loadTemplate(jData);
    /* Make sure values are sane */
    if(!checkValues(jData, jTemp)){
      WARN("Configuration issue detected in template.");
    }
    /* Watch configuration file if it exists */
    std::string config = getObject("configuration", jData).get<std::string>();
    if(config.length() > 0){
      watchFile(config.c_str());
    }
  }
}

Config::~Config(){
  /* Do nothing */
}

nlohmann::json Config::loadTemplate(nlohmann::json j){
  if(j.is_object()){
    nlohmann::json t = j;
    if(!t["default"].is_null()){
      j = j["default"].get<std::string>();
    }else{
      for(nlohmann::json::iterator i = j.begin(); i != j.end(); i++){
        *i = loadTemplate(*i);
      }
    }
  }else if(j.is_array()){
    WARN("Unimplemented JSON template parsing.");
  }else{
    /* Do nothing */
  }
  return j;
}

bool Config::watchFile(const char* filename){
  try{
    struct stat result;
    if(stat(filename, &result) == 0){
      lastMods.push_back(result.st_mtime);
      lastMods.push_back(result.st_mtime);
    }else{
      WARN("Unable to retrieve modification time.");
      /* As we can't read it, pull out early */
      return false;
    }
    files.push_back(filename);
    /* As we have a new file to watch, re-read all */
    service();
    /* Check for a new configuration file to be added */
    std::string config = getObject("configuration", jData).get<std::string>();
    if(config.length() > 0 && config != std::string(filename)){
      return watchFile(config.c_str());
    }
    return true;
  }catch(...){
    return false;
  }
}

void Config::update(){
  try{
    bool serviced = false;
    struct stat result;
    for(unsigned int x = 0; x < files.size(); x++){
      stat(files[x].c_str(), &result);
      if(result.st_mtime != lastMods[x]){
        lastMods[x] = result.st_mtime;
        if(!serviced){
          /* Perform service */
          if(!service()){
            /* If bad load, invalidate this time stamp and try next time */
            lastMods[x] = -1;
            /* No point continuing as it all needs to be reloaded */
            return;
          }
          /* All files after need to be serviced encase they override */
          serviced = true;
        }
      }
    }
  }catch(...){
    /* Do nothing */
  }
}

bool Config::service(){
  try{
    LOG("Servicing configuration files...");
    nlohmann::json jDataNew;
    nlohmann::json j;
    for(unsigned int x = 0; x < files.size(); x++){
      std::ifstream fs(files[x], std::fstream::in);
      if(!fs.fail()){
        fs >> j;
        fs.close();
      }else{
        fs.close();
        return false;
      }
      jDataNew.merge_patch(j);
      /* Check values after merging */
      if(!checkValues(jDataNew, jTemp)){
        WARNM("Configuration issue detected in: ", files[x].c_str());
      }
    }
    jData = jDataNew;
    /* Pre-load the thread shared values */
    for(std::pair<std::string, std::shared_ptr<int>> p : iVals){
      int i = std::stoi(getString(p.first), NULL, 10);
      iVals[p.first] = std::make_shared<int>(i);
    }
    for(std::pair<std::string, std::shared_ptr<long long>> p : lVals){
      long long l = std::stoll(getString(p.first), NULL, 10);
      lVals[p.first] = std::make_shared<long long>(l);
    }
    for(std::pair<std::string, std::shared_ptr<double>> p : dVals){
      double d = std::stod(getString(p.first), NULL);
      dVals[p.first] = std::make_shared<double>(d);
    }
    return true;
  }catch(...){
    return false;
  }
}

bool Config::checkValues(nlohmann::json jD, nlohmann::json jT){
  try{
    bool success = true;
    if(jD.is_object()){
      for(nlohmann::json::iterator i = jD.begin(); i != jD.end(); i++){
        success &= checkValues(*i, jT[i.key()]);
      }
    }else if(jD.is_array()){
      WARN("Unimplemented JSON template parsing.");
    }else{
      /* Check values within range */
      if(jT["type"] == "string"){
        /* Do nothing */
      }else if(jT["type"] == "int"){
        int iVal = std::stoi(jD.get<std::string>(), NULL, 10);
        int iMin = std::stoi(jT["min"].get<std::string>(), NULL, 10);
        int iMax = std::stoi(jT["max"].get<std::string>(), NULL, 10);
        if(iVal < iMin || iVal > iMax){
          WARNI("Integer out of range.", iVal);
          success = false;
        }
      }else if(jT["type"] == "long"){
        long long lVal = std::stoll(jD.get<std::string>(), NULL, 10);
        long long lMin = std::stoll(jT["min"].get<std::string>(), NULL, 10);
        long long lMax = std::stoll(jT["max"].get<std::string>(), NULL, 10);
        if(lVal < lMin || lVal > lMax){
          WARNL("Long out of range.", lVal);
          success = false;
        }
      }else if(jT["type"] == "double"){
        double dVal = std::stod(jD.get<std::string>(), NULL);
        double dMin = std::stod(jT["min"].get<std::string>(), NULL);
        double dMax = std::stod(jT["max"].get<std::string>(), NULL);
        if(dVal < dMin || dVal > dMax){
          WARNF("Double out of range.", dVal);
          success = false;
        }
      }else{
        WARN("Unknown value type.");
        success = false;
      }
    }
    return success;
  }catch(...){
    return false;
  }
}

nlohmann::json Config::getObject(std::string name, nlohmann::json j){
  try{
    std::stringstream path(name);
    std::string part;
    nlohmann::json obj = j;
    while(std::getline(path, part, '.')){
      if(obj.is_object()){
        obj = obj[part];
      }else if(obj.is_array()){
        obj = obj[std::strtol(part.c_str(), NULL, 10)];
      }else{
        WARNM("Configuration can't get ", name.c_str());
      }
    }
    return obj;
  }catch(...){
    nlohmann::json z;
    return z;
  }
}

nlohmann::json Config::mergeObject(std::string name, std::string value){
  try{
    nlohmann::json obj;
    int beg = name.length() + 1;
    int end;
    std::string key;
    while(beg > 0){
      end = beg - 1;
      beg = name.find_last_of('.', end - 1) + 1;
      key = name.substr(beg, end - beg);
      nlohmann::json o;
      if((unsigned int)end < name.length() - 1){
        o[key] = obj;
      }else{
        o[key] = value;
      }
      obj = o;
    }
    return obj;
  }catch(...){
    nlohmann::json z;
    return z;
  }
}

void Config::setObject(std::string name, std::string value){
  try{
    nlohmann::json m = mergeObject(name, value);
    jData.merge_patch(m);
    jDelta.merge_patch(m);
    /* Invalidate the caches for these values */
    iVals[name] = NULL;
    lVals[name] = NULL;
    dVals[name] = NULL;
  }catch(...){
    /* Do nothing */
  }
}

std::string Config::getString(std::string name){
  try{
    /* TODO: Would be awesome to cache this thread safe. */
    return getObject(name, jData).get<std::string>();
  }catch(...){
    return "";
  }
}

std::shared_ptr<int> Config::getInt(std::string name){
  try{
    if(iVals.find(name) == iVals.end() || iVals[name] == NULL){
      int i = std::stoi(getString(name), NULL, 10);
      iVals[name] = std::make_shared<int>(i);
      return iVals[name];
    }else{
      return iVals[name];
    }
  }catch(...){
    return std::make_shared<int>(0);
  }
}

std::shared_ptr<long long> Config::getLong(std::string name){
  try{
    if(lVals.find(name) == lVals.end() || lVals[name] == NULL){
      long long l = std::stoll(getString(name), NULL, 10);
      lVals[name] = std::make_shared<long long>(l);
      return lVals[name];
    }else{
      return lVals[name];
    }
  }catch(...){
    return std::make_shared<long long>(0);
  }
}

std::shared_ptr<double> Config::getDouble(std::string name){
  try{
    if(dVals.find(name) == dVals.end() || dVals[name] == NULL){
      double d = std::stod(getString(name), NULL);
      dVals[name] = std::make_shared<double>(d);
      return dVals[name];
    }else{
      return dVals[name];
    }
  }catch(...){
    return std::make_shared<double>(0.0);
  }
}

int Config::getLength(std::string name){
  try{
    return getObject(name, jData).size();
  }catch(...){
    return 0;
  }
}

std::string Config::getDump(){
  try{
    return jData.dump();
  }catch(...){
    /* Return a blank dump on failure */
    return "{}";
  }
}

std::string Config::getTempDump(){
  try{
    return jTemp.dump();
  }catch(...){
    /* Return a blank dump on failure */
    return "{}";
  }
}

void Config::write(){
  try{
    /* Read the current delta file */
    nlohmann::json j;
    std::ifstream is(getString("app.config-delta"), std::fstream::in);
    is >> j;
    is.close();
    /* Merge the previous delta file with the new one */
    j.merge_patch(jDelta);
    /* Save the merged data */
    std::ofstream os(getString("app.config-delta"));
    os << std::setw(4) << j << std::endl;
    os.close();
  }catch(...){
    WARN("Exception thrown trying to save config");
  }
}
