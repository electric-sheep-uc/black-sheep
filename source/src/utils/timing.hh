#pragma once

/**
 * timing.hh
 *
 * Allow threads to be timing and for performance data to be analysed.
 **/
class Timing{
  private:
    Config* timing;
    int window;

  public:
    /**
     * Timing()
     *
     * Initialize the timing object and associated variables.
     **/
    Timing();

   /**
    * ~Timing()
    *
    * Deconstruct the timing object and memory used.
    **/
   ~Timing();

   /**
    * eventStart()
    *
    * Record the timing of some event as it begins. If the event has not yet
    * been recorded, it will be added.
    *
    * @param loop The loop to be updated.
    * @param event The name of the event to be recorded.
    **/
   void eventStart(std::string loop, std::string event);

   /**
    * eventEnd()
    *
    * Record the timing of some event as it ends.
    *
    * @param loop The loop to be updated.
    * @param event The name of the event to be recorded.
    **/
   void eventEnd(std::string loop, std::string event);

   /**
    * loopTick()
    *
    * Record the tick of a given loop, i.e. the fact it has successfully
    * completed a single loop since the last tick.
    *
    * @param loop The loop to be updated.
    **/
   void loopTick(std::string loop);

   /**
    * getData()
    *
    * Convert the timing data to a JSON formatted string.
    *
    * @return The timing data JSON formatted string.
    **/
   std::string getData();
};
