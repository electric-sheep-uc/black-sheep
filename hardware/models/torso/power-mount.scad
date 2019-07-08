include <power.scad>;

module power_mount(){
  difference(){
    union(){
      /* Left screw hole */
      translate([-POWER_HOLE_X_DIST / 2, 0, -(POWER_HEIGHT + POWER_MOUNT_HEIGHT) / 2]){
        cylinder(POWER_MOUNT_HEIGHT, POWER_HOLE_DIAM, POWER_HOLE_DIAM, true);
      }
      /* Right screw hole */
      translate([POWER_HOLE_X_DIST / 2, 0, -(POWER_HEIGHT + POWER_MOUNT_HEIGHT) / 2]){
        cylinder(POWER_MOUNT_HEIGHT, POWER_HOLE_DIAM, POWER_HOLE_DIAM, true);
      }
    }
    /* Left screw hole */
    translate([-POWER_HOLE_X_DIST / 2, 0, 0]){
      cylinder(POWER_DEPTH * 2, POWER_SCREW_DIAM / 2, POWER_SCREW_DIAM / 2, true);
    }
    /* Right screw hole */
    translate([POWER_HOLE_X_DIST / 2, 0, 0]){
      cylinder(POWER_DEPTH * 2, POWER_SCREW_DIAM / 2, POWER_SCREW_DIAM / 2, true);
    }
  }
}

power_mount();