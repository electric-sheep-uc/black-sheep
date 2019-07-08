include <torso-config.scad>
use <battery.scad>;
use <power.scad>;
use <power-mount.scad>;
use <torso-tray.scad>;

module power_tray(){
  translate([0, 0, TRAY_THICKNESS * 8]){
    #battery();
  }
  scaler = 1.015;
  difference(){
    torso_tray();
    /* Make room for DC power over hang */
    translate([TRAY_THICKNESS * 4, 0, TRAY_THICKNESS * 8]){
      rotate([0, 0, 90]){
        scale([scaler, scaler, scaler]){
          power();
        }
      }
    }
  }
}

power_tray();