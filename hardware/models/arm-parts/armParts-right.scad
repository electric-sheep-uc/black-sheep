include <upper-arm-config.scad>
include <../Motor-FS6535/motor-fs6535-horn-config.scad>
include <../Motor-FS6535/motor-fs6535-config.scad>
use <cageSide.scad>
use <../Motor-FS6535/motor-fs6535.scad>
use <../Motor-FS6535/motor-fs6535-horn.scad>
use <armParts-left.scad>

module arm_right()
{
    mirror( [0,1,0]) arm(false, true);

}
arm_right();