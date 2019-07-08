include <thigh-config.scad>;
include <../motor/motor-sm30-config.scad>;
use <../motor/motor-sm30-body-mount.scad>;
use <../motor/motor-sm30-horn-mount.scad>;

module thigh_mounts(thigh_length, body_depth){
  translate([0, 0, -body_depth / 1.9]){
    rotate([90, 180, 90]){
      offset_motor_sm30_body_mount();
    }
  }
  translate([0, 31, thigh_length - (body_depth / 2.1)]){
    rotate([0, 0, 180]){
     offset_motor_sm30_horn_mount();
    }
  }
}

module thigh_left(){
  /* Apply global properties */
  color(PRINT_COLOR){
    union(){
      thigh_mounts(THIGH_LENGTH, BODY_DEPTH);
    }
  }
}

module offset_thigh_left(){
  translate([THIGH_SPACE, 0, 0]){
    thigh_left();
  }
}

offset_thigh_left();