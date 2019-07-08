include <../arm-parts/upper-arm-config.scad>
include <../Motor-FS6535/motor-fs6535-horn-config.scad>
include <../Motor-FS6535/motor-fs6535-config.scad>

use <../arm-parts/cageSide.scad>
use <../Motor-FS6535/motor-fs6535.scad>
use <../Motor-FS6535/motor-fs6535-horn.scad>
use <../arm-parts/armParts-left.scad>

module shoulder(){
  difference(){
    union(){
      rotate([0, 0, 270]){
        translate([-117.5, 20, 0]){
          motor_fs6535_horn_mount();
        }
      }
      rotate([90, 0, 90]){
        translate([-32.5, 20, 0]){
          motor_fs6535_horn_mount();
        }
      }
      /* Joining struts */
      translate([0, 21.5, 53.5]){
        cube([40, 38.5, 10], false);
      }
      translate([0, 50, 37.5]){
        cube([40, 10, 20], false);
      }
    }
    translate([-5, -35, -25]){
      cube([50, 87.5, 78.5], false);
    }
  }
}
    
shoulder();