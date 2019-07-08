#include <iostream>

inline const char* GitHash(){
  #ifndef GIT_HASH
    #define GIT_HASH "UNKNOWN"
  #endif
  return GIT_HASH;
}
