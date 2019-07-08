include <smart.scad>;

module smart_mount(){
  difference(){
    union(){
      /* Top left screw hole */
      translate([-SMART_HOLE_X_DIST / 2, SMART_HOLE_Y_DIST / 2, -(SMART_HEIGHT + SMART_MOUNT_HEIGHT) / 2]){
        cylinder(SMART_MOUNT_HEIGHT, SMART_HOLE_DIAM, SMART_HOLE_DIAM, true);
      }
      /* Top right screw hole */
      translate([SMART_HOLE_X_DIST / 2, SMART_HOLE_Y_DIST / 2, -(SMART_HEIGHT + SMART_MOUNT_HEIGHT) / 2]){
        cylinder(SMART_MOUNT_HEIGHT, SMART_HOLE_DIAM, SMART_HOLE_DIAM, true);
      }
      /* Bottom left screw hole */
      translate([-SMART_HOLE_X_DIST / 2, -SMART_HOLE_Y_DIST / 2, -(SMART_HEIGHT + SMART_MOUNT_HEIGHT) / 2]){
        cylinder(SMART_MOUNT_HEIGHT, SMART_HOLE_DIAM, SMART_HOLE_DIAM, true);
      }
      /* Bottom right screw hole */
      translate([SMART_HOLE_X_DIST / 2, -SMART_HOLE_Y_DIST / 2, -(SMART_HEIGHT + SMART_MOUNT_HEIGHT) / 2]){
        cylinder(SMART_MOUNT_HEIGHT, SMART_HOLE_DIAM, SMART_HOLE_DIAM, true);
      }
    }
    /* Top left screw hole */
    translate([-SMART_HOLE_X_DIST / 2, SMART_HOLE_Y_DIST / 2, 0]){
      cylinder(SMART_DEPTH * 2, SMART_SCREW_DIAM / 2, SMART_SCREW_DIAM / 2, true);
    }
    /* Top right screw hole */
    translate([SMART_HOLE_X_DIST / 2, SMART_HOLE_Y_DIST / 2, 0]){
      cylinder(SMART_DEPTH * 2, SMART_SCREW_DIAM / 2, SMART_SCREW_DIAM / 2, true);
    }
    /* Bottom left screw hole */
    translate([-SMART_HOLE_X_DIST / 2, -SMART_HOLE_Y_DIST / 2, 0]){
      cylinder(SMART_DEPTH * 2, SMART_SCREW_DIAM / 2, SMART_SCREW_DIAM / 2, true);
    }
    /* Bottom right screw hole */
    translate([SMART_HOLE_X_DIST / 2, -SMART_HOLE_Y_DIST / 2, 0]){
      cylinder(SMART_DEPTH * 2, SMART_SCREW_DIAM / 2, SMART_SCREW_DIAM / 2, true);
    }
  }
}

smart_mount();