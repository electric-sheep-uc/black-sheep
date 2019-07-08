include <fan-config.scad>;
use <fan.scad>;

module fan_mount(){
  difference(){
    union(){
      /* Top left screw hole */
      translate([-FAN_HOLE_X_DIST / 2, -(FAN_DEPTH + FAN_MOUNT_HEIGHT) / 2, FAN_HOLE_Z_DIST / 2]){
        rotate([90, 0, 0]){
          cylinder(FAN_MOUNT_HEIGHT, FAN_HOLE_REAR_DIAM * 0.75, FAN_HOLE_REAR_DIAM * 0.75, true);
        }
      }
      /* Top right screw hole */
      translate([FAN_HOLE_X_DIST / 2, -(FAN_DEPTH + FAN_MOUNT_HEIGHT) / 2, FAN_HOLE_Z_DIST / 2]){
        rotate([90, 0, 0]){
          cylinder(FAN_MOUNT_HEIGHT, FAN_HOLE_REAR_DIAM * 0.75, FAN_HOLE_REAR_DIAM * 0.75, true);
        }
      }
      /* Bottom left screw hole */
      translate([-FAN_HOLE_X_DIST / 2, -(FAN_DEPTH + FAN_MOUNT_HEIGHT) / 2, -FAN_HOLE_Z_DIST / 2]){
        rotate([90, 0, 0]){
          cylinder(FAN_MOUNT_HEIGHT, FAN_HOLE_REAR_DIAM * 0.75, FAN_HOLE_REAR_DIAM * 0.75, true);
        }
      }
      /* Bottom right screw hole */
      translate([FAN_HOLE_X_DIST / 2, -(FAN_DEPTH + FAN_MOUNT_HEIGHT) / 2, -FAN_HOLE_Z_DIST / 2]){
        rotate([90, 0, 0]){
          cylinder(FAN_MOUNT_HEIGHT, FAN_HOLE_REAR_DIAM * 0.75, FAN_HOLE_REAR_DIAM * 0.75, true);
        }
      }
    }
    /* Top left screw hole */
    translate([-FAN_HOLE_X_DIST / 2, FAN_DEPTH / 2, FAN_HOLE_Z_DIST / 2]){
      rotate([90, 0, 0]){
        cylinder(FAN_DEPTH * 4, FAN_SCREW_DIAM / 2, FAN_SCREW_DIAM / 2, true);
      }
    }
    /* Top right screw hole */
    translate([FAN_HOLE_X_DIST / 2, FAN_DEPTH / 2, FAN_HOLE_Z_DIST / 2]){
      rotate([90, 0, 0]){
        cylinder(FAN_DEPTH * 4, FAN_SCREW_DIAM / 2, FAN_SCREW_DIAM / 2, true);
      }
    }
    /* Bottom left screw hole */
    translate([-FAN_HOLE_X_DIST / 2, FAN_DEPTH / 2, -FAN_HOLE_Z_DIST / 2]){
      rotate([90, 0, 0]){
        cylinder(FAN_DEPTH * 4, FAN_SCREW_DIAM / 2, FAN_SCREW_DIAM / 2, true);
      }
    }
    /* Bottom right screw hole */
    translate([FAN_HOLE_X_DIST / 2, FAN_DEPTH / 2, -FAN_HOLE_Z_DIST / 2]){
      rotate([90, 0, 0]){
        cylinder(FAN_DEPTH * 4, FAN_SCREW_DIAM / 2, FAN_SCREW_DIAM / 2, true);
      }
    }
  }
}

fan_mount();
#fan();