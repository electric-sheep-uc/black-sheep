include <../arm-parts/upper-arm-config.scad>
include <../Motor-FS6535/motor-fs6535-horn-config.scad>
include <../Motor-FS6535/motor-fs6535-config.scad>

use <../arm-parts/cageSide.scad>
use <../Motor-FS6535/motor-fs6535.scad>
use <../Motor-FS6535/motor-fs6535-horn.scad>
use <../arm-parts/armParts-left.scad>

use <shoulder-left.scad>

module shoulder_right(){
  mirror([0, 0, 1]){
    shoulder();
  }
}

shoulder_right();