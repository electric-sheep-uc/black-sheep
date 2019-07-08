include <pwm.scad>;

module pwm_mount(){
  difference(){
    union(){
      /* Top left screw hole */
      translate([-PWM_HOLE_X_DIST / 2, PWM_HOLE_Y_DIST / 2, -(PWM_HEIGHT + PWM_MOUNT_HEIGHT) / 2]){
        cylinder(PWM_MOUNT_HEIGHT, PWM_HOLE_DIAM, PWM_HOLE_DIAM, true);
      }
      /* Top right screw hole */
      translate([PWM_HOLE_X_DIST / 2, PWM_HOLE_Y_DIST / 2, -(PWM_HEIGHT + PWM_MOUNT_HEIGHT) / 2]){
        cylinder(PWM_MOUNT_HEIGHT, PWM_HOLE_DIAM, PWM_HOLE_DIAM, true);
      }
      /* Bottom left screw hole */
      translate([-PWM_HOLE_X_DIST / 2, -PWM_HOLE_Y_DIST / 2, -(PWM_HEIGHT + PWM_MOUNT_HEIGHT) / 2]){
        cylinder(PWM_MOUNT_HEIGHT, PWM_HOLE_DIAM, PWM_HOLE_DIAM, true);
      }
      /* Bottom right screw hole */
      translate([PWM_HOLE_X_DIST / 2, -PWM_HOLE_Y_DIST / 2, -(PWM_HEIGHT + PWM_MOUNT_HEIGHT) / 2]){
        cylinder(PWM_MOUNT_HEIGHT, PWM_HOLE_DIAM, PWM_HOLE_DIAM, true);
      }
    }
    /* Top left screw hole */
    translate([-PWM_HOLE_X_DIST / 2, PWM_HOLE_Y_DIST / 2, 0]){
      cylinder(PWM_DEPTH * 2, PWM_SCREW_DIAM / 2, PWM_SCREW_DIAM / 2, true);
    }
    /* Top right screw hole */
    translate([PWM_HOLE_X_DIST / 2, PWM_HOLE_Y_DIST / 2, 0]){
      cylinder(PWM_DEPTH * 2, PWM_SCREW_DIAM / 2, PWM_SCREW_DIAM / 2, true);
    }
    /* Bottom left screw hole */
    translate([-PWM_HOLE_X_DIST / 2, -PWM_HOLE_Y_DIST / 2, 0]){
      cylinder(PWM_DEPTH * 2, PWM_SCREW_DIAM / 2, PWM_SCREW_DIAM / 2, true);
    }
    /* Bottom right screw hole */
    translate([PWM_HOLE_X_DIST / 2, -PWM_HOLE_Y_DIST / 2, 0]){
      cylinder(PWM_DEPTH * 2, PWM_SCREW_DIAM / 2, PWM_SCREW_DIAM / 2, true);
    }
  }
}

pwm_mount();