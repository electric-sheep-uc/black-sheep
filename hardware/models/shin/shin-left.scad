include <shin-config.scad>;
include <../motor/motor-sm30-config.scad>;
use <../motor/motor-sm30-horn-mount.scad>;

module shin_mounts(shin_length, body_depth){
  translate([0, 0, 0]){
    rotate([90, 0, 0]){
      offset_motor_sm30_horn_mount();
    }
  }
  translate([0, 0, 86.75]){
    rotate([90, 180, 90]){
      offset_motor_sm30_horn_mount();
    }
  }
}

module shin_left(){
  /* Apply global properties */
  color(PRINT_COLOR){
    union(){
      shin_mounts(SHIN_LENGTH, BODY_DEPTH);
    }
  }
}

module offset_shin_left(){
  translate([SHIN_SPACE, 0, 0]){
    shin_left();
  }
}

offset_shin_left();