$fn = 64;
PWM_WIDTH = 62.3;
PWM_DEPTH = 25.4;
PWM_HEIGHT = 14.6;
PWM_HOLE_DIAM = 2.9;
PWM_HOLE_X_DIST = 55.5;
PWM_HOLE_Y_DIST = 19.0;
PWM_MOUNT_HEIGHT = 4;
PWM_SCREW_DIAM = PWM_HOLE_DIAM * 0.9;

module pwm(){
  difference(){
    /* Body */
    union(){
      cube([PWM_WIDTH, PWM_DEPTH, PWM_HEIGHT], true);
    }
    /* Top left screw hole */
    translate([-PWM_HOLE_X_DIST / 2, PWM_HOLE_Y_DIST / 2, 0]){
      cylinder(PWM_DEPTH * 2, PWM_HOLE_DIAM / 2, PWM_HOLE_DIAM / 2, true);
    }
    /* Top right screw hole */
    translate([PWM_HOLE_X_DIST / 2, PWM_HOLE_Y_DIST / 2, 0]){
      cylinder(PWM_DEPTH * 2, PWM_HOLE_DIAM / 2, PWM_HOLE_DIAM / 2, true);
    }
    /* Bottom left screw hole */
    translate([-PWM_HOLE_X_DIST / 2, -PWM_HOLE_Y_DIST / 2, 0]){
      cylinder(PWM_DEPTH * 2, PWM_HOLE_DIAM / 2, PWM_HOLE_DIAM / 2, true);
    }
    /* Bottom right screw hole */
    translate([PWM_HOLE_X_DIST / 2, -PWM_HOLE_Y_DIST / 2, 0]){
      cylinder(PWM_DEPTH * 2, PWM_HOLE_DIAM / 2, PWM_HOLE_DIAM / 2, true);
    }
  }
}

pwm();