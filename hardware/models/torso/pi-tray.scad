include <torso-config.scad>
use <pi.scad>;
use <pi-mount.scad>;
use <torso-tray.scad>;

module pi_tray(){
  translate([0, 0, TRAY_THICKNESS * 4]){
    rotate([0, 0, 90]){
      //#pi();
      pi_mount();
    }
  }
  torso_tray();
}

pi_tray();