include <upper-arm-config.scad>
include <../Motor-FS6535/motor-fs6535-horn-config.scad>
include <../Motor-FS6535/motor-fs6535-config.scad>
use <cageSide.scad>
use <../Motor-FS6535/motor-fs6535.scad>
use <../Motor-FS6535/motor-fs6535-horn.scad>

//armPart(4);
module armPart(ri) {
   //#  
    //translate([0, HORN_HEIGHT, HORN_RADIUS]) 
	difference() {
		union() {
			//rotate([90, 0, 0]) 
            cube([MOTOR_FS6535_BODY_LENGTH/2, HORN_HEIGHT, HORN_RADIUS*2]);
			//translate([0,0,8]) rotate([-90,0,0]) cylinder(r=8, h=2, $fn=45);
            translate([0, HORN_HEIGHT, HORN_RADIUS]) rotate([90, 0, 0])  motor_fs6535_horn();
		}
       translate([0, HORN_HEIGHT/2, HORN_RADIUS]) rotate([90, 0, 0])  scale([1,1,16]) horn_holes();

	}
}

module arm(withMotor, spring) {
	   translate([175,35,5]) difference() {
       rotate([-90,0,180]) translate([70, -43,14])	cageSide(withMotor, true);
		//translate([0,0,-13]) cube([40,40,10], center=true);
	}
	
    translate([-5,0,0]) motor_fs6535_horn_mount(true);
	if (spring) {
	//#	translate([0,12.5,15.9]) springHolder();
	}
}


/*module rampPart(length) {
	difference() {
		cube([length, 8, 8]);
		translate([0,3,0]) rotate([30, 0, 0]) translate([-0.1, -8, 0]) cube([length+0.2,8,8]);
		translate([-0.1,5,0]) rotate([-30, 0, 0]) cube([length+0.2,8,8]);
		translate([-0.1,4,10]) rotate([0,90,0]) cylinder(r=5, h=length+0.2, $fn=45);
	}
}
*/

/*module springHolder() {
	rampPart(20);
	translate([1.7,0,0.1]) rotate([0,-15,0]) translate([-5,0,0]) rampPart(5);
	translate([-1.5,0,-0.7]) rotate([0,-30,0]) translate([-5,0,0]) rampPart(5);
	translate([18,4,0]) cylinder(r=1, h=8, $fn=45);
	translate([18,4,4.5]) rotate([0,30,0]) cylinder(r=1, h=4, $fn=45);
	translate([18.5,4,7.5]) cylinder(r=1.5, h=1, $fn=45);
	translate([19.5,4,7.5]) cylinder(r=1.5, h=1, $fn=45);
	translate([18.5,2.5,7.5]) cube([1,3,1]);
}*/


module motor_fs6535_horn_mount(withExtraSpace){
    union(){
    translate([21,37.5,0])  armPart();
    translate([21.5,-42.5,0])  armPart();
    
	scale(2.5,2.5,2.5){
        difference(){
            union() {
                translate([21.5, -17, 0]) rotate([0, 0, 45]) cube([6.35, 3, 16]);
                translate([19.5, 15.5, 0]) rotate([0, 0, -45])  cube([6.35, 3, 16]);
                translate([23, -12.5, 0]) cube([3, 25.5, 16]);
                //space for a wire might need to cut down
                if(withExtraSpace)
                {
                translate([22, 14.5, 0.75]) cube([8, 2, 15]);
                translate([25,7, 0.75]) cube([4, 5, 15]);
                }
            }
        }
    }
    }
}

//mirror( [0,1,0]) 
arm(false, true);