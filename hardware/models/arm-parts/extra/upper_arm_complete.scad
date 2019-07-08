include <upper-arm-config.scad>
use <cageSide.scad>
use <swing.scad>
use <motor_fs6535.scad>
use <armParts.scad>

module combine_parts() {
	translate([0,0,38]) 
    translate([0,0,43]) swing(true);
	//translate([0,0,43]) arm(true, true);
    
   /* swing( false);
	translate([0,0,43]) arm(false, true );*/
}
// shows the complete thing
combine_parts();
