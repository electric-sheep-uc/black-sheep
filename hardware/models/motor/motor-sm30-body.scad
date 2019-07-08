include <motor-sm30-config.scad>;

module body(body_width, body_depth, body_height, screw_diam, rounded){
  if(rounded){
    rnd_factor = 1.5;
    minkowski(){
      cube([body_width - (screw_diam * rnd_factor), body_depth - (screw_diam * rnd_factor), body_height], true);
      cylinder(0.0000001, (screw_diam / 2) * rnd_factor, (screw_diam / 2) * rnd_factor, true);
    }
  }else{
     cube([body_width, body_depth, body_height], true);
  }
}

module motor_sm30_body(){
  /* Apply global properties */
  color(PRINT_COLOR){
    translate([0, 0, BODY_DEPTH / 2]){
      difference(){
        body(BODY_WIDTH, BODY_DEPTH, BODY_HEIGHT, MOUNT_HOLE_DIAM, BODY_ROUNDED);
        body_mount_holes(MOUNT_HOLE_HEIGHT, MOUNT_HOLE_DIAM, MOUNT_HOLE_DIST_TO_EDGE, BODY_WIDTH, BODY_DEPTH, BODY_HEIGHT);
      }
    }
  }
}

module offset_motor_sm30_body(){
  translate([0, 0, BODY_DEPTH / -2]){
    motor_sm30_body();
  }
}

offset_motor_sm30_body();