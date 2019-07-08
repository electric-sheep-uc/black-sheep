$fn = 64;
POWER_WIDTH = 74.2;
POWER_DEPTH = 77.8;
POWER_HEIGHT = 31.0;
POWER_HOLE_DIAM = 5.3;
POWER_HOLE_X_DIST = 64.5;
POWER_MOUNT_HEIGHT = 4;
POWER_SCREW_DIAM = POWER_HOLE_DIAM * 0.9;

module power(){
  difference(){
    /* Body */
    union(){
      cube([POWER_WIDTH, POWER_DEPTH, POWER_HEIGHT], true);
    }
    /* Left screw hole */
    translate([-POWER_HOLE_X_DIST / 2, 0, 0]){
      cylinder(POWER_DEPTH * 2, POWER_HOLE_DIAM / 2, POWER_HOLE_DIAM / 2, true);
    }
    /* Right screw hole */
    translate([POWER_HOLE_X_DIST / 2, 0, 0]){
      cylinder(POWER_DEPTH * 2, POWER_HOLE_DIAM / 2, POWER_HOLE_DIAM / 2, true);
    }
  }
}

power();