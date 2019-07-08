#pragma once

#include <sys/time.h>

#define PI 3.14159265358979323846
#define RAW_MAX 4096

#define CLAMP(x, l, h) (((x) > h) ? h : (((x) < l) ? l : (x)))
#ifndef MIN
  #define MIN(x, y) ((x < y) ? (x) : (y))
#endif
#ifndef MAX
  #define MAX(x, y) ((x > y) ? (x) : (y))
#endif

#define RAW2RAD(x) ((x * 2 * PI) / RAW_MAX)
#define RAD2RAW(x) ((x * RAW_MAX) / (2 * PI))
