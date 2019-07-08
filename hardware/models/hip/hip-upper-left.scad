include <hip-config.scad>;
include <../motor/motor-sm30-config.scad>;
include <../foot/foot-config.scad>;
use <../motor/motor-sm30-horn-mount.scad>;

module hip_upper_left(){
  /* Apply global properties */
  color(PRINT_COLOR){
    translate([0, 0, 0]){
      rotate([90, 0, 0]){
        offset_motor_sm30_horn_mount();
      }
    }
    translate([0, 0, HORN_DIAM * 3.63]){
      rotate([90, 180, 90]){
        offset_motor_sm30_horn_mount();
      }
    }
  }
}

module offset_hip_upper_left(){
  translate([FOOT_SPACE, 0, BODY_DEPTH * 2]){
    hip_upper_left();
  }
}

offset_hip_upper_left();