$fn = 64;
SMART_WIDTH = 56.0;
SMART_DEPTH = 38.8;
SMART_HEIGHT = 12.4;
SMART_HOLE_DIAM = 3.3;
SMART_HOLE_X_DIST = 48.8;
SMART_HOLE_Y_DIST = 28.4;
SMART_MOUNT_HEIGHT = 4;
SMART_SCREW_DIAM = SMART_HOLE_DIAM * 0.9;

module smart(){
  difference(){
    /* Body */
    union(){
      cube([SMART_WIDTH, SMART_DEPTH, SMART_HEIGHT], true);
    }
    /* Top left screw hole */
    translate([-SMART_HOLE_X_DIST / 2, SMART_HOLE_Y_DIST / 2, 0]){
      cylinder(SMART_DEPTH * 2, SMART_HOLE_DIAM / 2, SMART_HOLE_DIAM / 2, true);
    }
    /* Top right screw hole */
    translate([SMART_HOLE_X_DIST / 2, SMART_HOLE_Y_DIST / 2, 0]){
      cylinder(SMART_DEPTH * 2, SMART_HOLE_DIAM / 2, SMART_HOLE_DIAM / 2, true);
    }
    /* Bottom left screw hole */
    translate([-SMART_HOLE_X_DIST / 2, -SMART_HOLE_Y_DIST / 2, 0]){
      cylinder(SMART_DEPTH * 2, SMART_HOLE_DIAM / 2, SMART_HOLE_DIAM / 2, true);
    }
    /* Bottom right screw hole */
    translate([SMART_HOLE_X_DIST / 2, -SMART_HOLE_Y_DIST / 2, 0]){
      cylinder(SMART_DEPTH * 2, SMART_HOLE_DIAM / 2, SMART_HOLE_DIAM / 2, true);
    }
  }
}

smart();