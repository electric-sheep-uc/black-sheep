$fn = 64;
PI_WIDTH = 85.0;
PI_DEPTH = 56.2;
PI_HEIGHT = 15.4;
PI_HOLE_DIAM = 2.7;
PI_HOLE_X_OFFSET = 3.3;
PI_HOLE_X_DIST = 57.9;
PI_HOLE_Y_DIST = 48.6;
PI_MOUNT_HEIGHT = 4;
PI_SCREW_DIAM = PI_HOLE_DIAM * 0.9;

module pi(){
  difference(){
    /* Body */
    union(){
      cube([PI_WIDTH, PI_DEPTH, PI_HEIGHT], true);
    }
    /* Top left screw hole */
    translate([(-PI_WIDTH / 2) + PI_HOLE_X_OFFSET, PI_HOLE_Y_DIST / 2, 0]){
      cylinder(PI_DEPTH * 2, PI_HOLE_DIAM / 2, PI_HOLE_DIAM / 2, true);
    }
    /* Top right screw hole */
    translate([(-PI_WIDTH / 2) + PI_HOLE_X_OFFSET + PI_HOLE_X_DIST, PI_HOLE_Y_DIST / 2, 0]){
      cylinder(PI_DEPTH * 2, PI_HOLE_DIAM / 2, PI_HOLE_DIAM / 2, true);
    }
    /* Bottom left screw hole */
    translate([(-PI_WIDTH / 2) + PI_HOLE_X_OFFSET, -PI_HOLE_Y_DIST / 2, 0]){
      cylinder(PI_DEPTH * 2, PI_HOLE_DIAM / 2, PI_HOLE_DIAM / 2, true);
    }
    /* Bottom right screw hole */
    translate([(-PI_WIDTH / 2) + PI_HOLE_X_OFFSET + PI_HOLE_X_DIST, -PI_HOLE_Y_DIST / 2, 0]){
      cylinder(PI_DEPTH * 2, PI_HOLE_DIAM / 2, PI_HOLE_DIAM / 2, true);
    }
  }
}

pi();