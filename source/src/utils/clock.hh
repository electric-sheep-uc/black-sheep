#pragma once

#include <sys/time.h>

class CLOCK{
  public:
    /**
     * CURRENT_TIME_MILLIS()
     *
     * Get the current wall clock time in milliseconds since epoch.
     *
     * @return Number of milliseconds at the time of the request.
     **/
    static long long CURRENT_TIME_MILLIS(){
      struct timeval time;
      gettimeofday(&time, NULL);
      return ((long long)time.tv_sec * 1000) + ((long long)time.tv_usec / 1000);
    }
};
