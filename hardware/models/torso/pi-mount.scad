include <pi.scad>;

module pi_mount(){
  difference(){
    union(){
      /* Top left screw hole */
      translate([(-PI_WIDTH / 2) + PI_HOLE_X_OFFSET, PI_HOLE_Y_DIST / 2, -(PI_HEIGHT / 2)]){
        cylinder(PI_MOUNT_HEIGHT, PI_HOLE_DIAM, PI_HOLE_DIAM, true);
      }
      /* Top right screw hole */
      translate([(-PI_WIDTH / 2) + PI_HOLE_X_OFFSET + PI_HOLE_X_DIST, PI_HOLE_Y_DIST / 2, -(PI_HEIGHT / 2)]){
        cylinder(PI_MOUNT_HEIGHT, PI_HOLE_DIAM, PI_HOLE_DIAM, true);
      }
      /* Bottom left screw hole */
      translate([(-PI_WIDTH / 2) + PI_HOLE_X_OFFSET, -PI_HOLE_Y_DIST / 2, -(PI_HEIGHT / 2)]){
        cylinder(PI_MOUNT_HEIGHT, PI_HOLE_DIAM, PI_HOLE_DIAM, true);
      }
      /* Bottom right screw hole */
      translate([(-PI_WIDTH / 2) + PI_HOLE_X_OFFSET + PI_HOLE_X_DIST, -PI_HOLE_Y_DIST / 2, -(PI_HEIGHT / 2)]){
        cylinder(PI_MOUNT_HEIGHT, PI_HOLE_DIAM, PI_HOLE_DIAM, true);
      }
    }
    /* Top left screw hole */
    translate([(-PI_WIDTH / 2) + PI_HOLE_X_OFFSET, PI_HOLE_Y_DIST / 2, 0]){
      cylinder(PI_DEPTH * 2, PI_SCREW_DIAM / 2, PI_SCREW_DIAM / 2, true);
    }
    /* Top right screw hole */
    translate([(-PI_WIDTH / 2) + PI_HOLE_X_OFFSET + PI_HOLE_X_DIST, PI_HOLE_Y_DIST / 2, 0]){
      cylinder(PI_DEPTH * 2, PI_SCREW_DIAM / 2, PI_SCREW_DIAM / 2, true);
    }
    /* Bottom left screw hole */
    translate([(-PI_WIDTH / 2) + PI_HOLE_X_OFFSET, -PI_HOLE_Y_DIST / 2, 0]){
      cylinder(PI_DEPTH * 2, PI_SCREW_DIAM / 2, PI_SCREW_DIAM / 2, true);
    }
    /* Bottom right screw hole */
    translate([(-PI_WIDTH / 2) + PI_HOLE_X_OFFSET + PI_HOLE_X_DIST, -PI_HOLE_Y_DIST / 2, 0]){
      cylinder(PI_DEPTH * 2, PI_SCREW_DIAM / 2, PI_SCREW_DIAM / 2, true);
    }
  }
}

pi_mount();