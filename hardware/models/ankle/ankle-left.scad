include <ankle-config.scad>;
include <../motor/motor-sm30-config.scad>;
include <../foot/foot-config.scad>;
use <../motor/motor-sm30-body-mount.scad>;

module ankle_left(){
  /* Apply global properties */
  color(PRINT_COLOR){
    rotate([90, 180, 90]){
      offset_motor_sm30_body_mount();
    }
    translate([0, 0, HORN_DIAM * 2.35]){
      rotate([90, 0, 0]){
        offset_motor_sm30_body_mount();
      }
    }
  }
}

module offset_ankle_left(){
  translate([FOOT_SPACE, 0, 0]){
    ankle_left();
  }
}

offset_ankle_left();