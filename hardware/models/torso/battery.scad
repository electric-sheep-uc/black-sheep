$fn = 64;
BATTERY_WIDTH = 35.4;
BATTERY_DEPTH = 115.3;
BATTERY_HEIGHT = 34.4;

module battery(){
  /* Body */
  union(){
    cube([BATTERY_WIDTH, BATTERY_DEPTH, BATTERY_HEIGHT], true);
  }
}

battery();