include <torso-config.scad>
use <pwm.scad>;
use <pwm-mount.scad>;
use <smart.scad>;
use <smart-mount.scad>;
use <torso-tray.scad>;

module pwm_smart_tray(){
  translate([0, TORSO_DEPTH / 4, TRAY_THICKNESS * 4]){
    //#pwm();
    pwm_mount();
  }
  translate([0, -TORSO_DEPTH / 4, TRAY_THICKNESS * 4]){
    //#smart();
    smart_mount();
  }
  torso_tray();
}

pwm_smart_tray();