#define TEST
#pragma once

#include "log.hh"

/**
 * test.hh
 *
 * A separate class for performing basic tests with zero dependencies.
 **/
class Test{
  public:
    static int total;
    static int pass;

  private:
    /**
     * assurt()
     *
     * Check that something is equal to another thing.
     *
     * @param name The short name for the test.
     * @param result The result of the test, true or false.
     **/
    static void assurt(const char* name, bool result){
      ++Test::total;
      LOGM("  ", name);
      if(result){
        ++Test::pass;
        LOG("        [ OK ]");
      }else{
        WARN("              [FAIL]");
      }
    }

  public:
    /**
     * smartcontroller_cc()
     *
     * Run basic tests against the smart controller.
     **/
    void smartcontroller_cc();

    /**
     * integral_cc()
     *
     * Run basic tests against the integral image generator.
     **/
    void integral_cc();
};
