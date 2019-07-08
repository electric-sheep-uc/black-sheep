include <upper-arm-config.scad>
include <../Motor-FT5335M/motor-ft5335m-horn-config.scad>
include <../Motor-FT5335M/motor-ft5335m-config.scad>
use <cageSide-ft5335m.scad>
use <../Motor-FT5335M/motor-ft5335m.scad>
use <../Motor-FT5335M/motor-ft5335m-horn.scad>
use <armParts-left-ft5335m.scad>

module arm_right()
{
    mirror( [0,1,0]) arm(false, true);

}
arm_right();