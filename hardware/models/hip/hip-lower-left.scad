include <hip-config.scad>;
include <../motor/motor-sm30-config.scad>;
include <../foot/foot-config.scad>;
use <../motor/motor-sm30-body-mount.scad>;

module hip_lower_left(){
  /* Apply global properties */
  color(PRINT_COLOR){
    translate([0, 0, 0]){
      rotate([0, 0, 180]){
        offset_motor_sm30_body_mount();
      }
    }
    translate([0, 22.5, HORN_DIAM * 2]){
      rotate([90, 0, 0]){
        offset_motor_sm30_body_mount();
      }
    }
  }
}

module offset_hip_lower_left(){
  translate([FOOT_SPACE, 0, 0]){
    hip_lower_left();
  }
}

offset_hip_lower_left();