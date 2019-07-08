include <upper-arm-config.scad>
use <cageSide.scad>
use <../motor_fs6535/motor_fs6535.scad>
use <../motor_fs6535/motor-fs6535-horn.scad>

module swing_parts(withMotor) {
    difference() {
		union() {
			//cylinder(r=20,h=5,$fn=45);
            motor_fs6535_horn();
            
            translate([-45, 17.5, 2.5]) rotate([0, 90, 0]) cylinder(r=2.5, h=45, $fn=45);
			translate([-27, 17.4, 2.5]) rotate([60, 90, 0]) cylinder(r=2.5, h=20, $fn=45);
		}
		translate([0,0,-0.05]) cylinder(r=3,h=5.1,$fn=45);
		translate([0, -18, 5.1]) cube([30, 10, 2], center=true);
		translate([0, 18, 5.1]) cube([30, 10, 2], center=true);
	}
}
module swing(withMotor){
    //translate([-5.5,-12.5,12.9]) 
     cageSide(withMotor, true);
     rotate ([180, 0, 180]) translate([-18,30,-21])  swing_parts(withMotor);
    }
swing(false);