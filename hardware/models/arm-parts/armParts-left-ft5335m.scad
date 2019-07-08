include <upper-arm-ft5335m-config.scad>
include <../Motor-FT5335M/motor-ft5335m-horn-config.scad>
include <../Motor-FT5335M/motor-ft5335m-config.scad>
use <cageSide-ft5335m.scad>
use <../Motor-FT5335M/motor-ft5335m.scad>
use <../Motor-FT5335M/motor-ft5335m-horn.scad>

//armPart(4);
module armPart(ri) {
   //#  
    //translate([0, HORN_HEIGHT, HORN_RADIUS]) 
	difference() {
		union() {
			//rotate([90, 0, 0]) 
           //# cube([MOTOR_FT5335M_BODY_LENGTH/2, HORN_HEIGHT, HORN_RADIUS*2]);
           //#cube([MOTOR_FT5335M_BODY_LENGTH, 8, MOTOR_FT5335M_BODY_WIDTH]); MOTOR_FT5335M_LOWERBODY_HEIGHT
            cube([MOTOR_FT5335M_BODY_LENGTH, 8, MOTOR_FT5335M_LOWERBODY_HEIGHT]); 
			//translate([0,0,8]) rotate([-90,0,0]) cylinder(r=8, h=2, $fn=45);
            
            /*translate([MOTOR_FT5335M_BODY_LENGTH/2, 8, MOTOR_FT5335M_BODY_WIDTH/2]) 
            rotate([90, 0, 0])  motor_ft5335m_horn();*/
		}
       //#translate([MOTOR_FT5335M_BODY_LENGTH/2, HORN_HEIGHT/2, HORN_RADIUS]) 
        
        //horns vertical 
        translate([MOTOR_FT5335M_BODY_LENGTH/2-5, 8, MOTOR_FT5335M_LOWERBODY_HEIGHT/2]) 
        rotate([90, 0, 0])  scale([1,1,2.5]) horn_holes(HORN_SCREW_HOLE_DIAMETER / 2, HORN_SCREW_RADIUS, HORN_HEIGHT * 2);// horn_holes();
        //horns orizental 
        translate([MOTOR_FT5335M_BODY_LENGTH/2-5, 8, MOTOR_FT5335M_LOWERBODY_HEIGHT/2]) 
        rotate([90, 90, 0])  scale([1,1,2.5])    horn_holes(HORN_SCREW_HOLE_DIAMETER / 2, HORN_SCREW_RADIUS, HORN_HEIGHT * 2);// horn_holes();

	}
}

module arm(withMotor, spring) {
    //withMotor=true;
	   translate([175,-10.5,5]) difference() {
       rotate([0,0,180]) translate([74, -43,18])	cageSide(withMotor, true);
		//translate([0,0,-13]) cube([40,40,10], center=true);
	}
	
    translate([-5,0,0]) motor_ft5335m_horn_mount(true);
	if (spring) {
	}
}
module motor_ft5335m_horn_mount(withExtraSpace){
    union(){
    translate([-8,24.8,0])  armPart();
    translate([-8,-42.5,0])  armPart();
    // back part of the mount container
	scale(2.5,2.5,2.5){
        difference(){
            union() {
                translate([21.5, -17, 0]) rotate([0, 0, 45]) cube([6.35, 3, 16]);
                translate([21.5, 10, 0]) rotate([0, 0, 0])  cube([6.35, 3, 16]);
                translate([23, -12.5, 0]) cube([3, 25.5, 16]);
                //space for a wire might need to cut down
                if(withExtraSpace)
                {
                translate([24, 0, 0]) cube([5, 2, 16]);
                translate([25, 8, 0]) cube([4, 5, 16]);
                }
            }
        }
    }
    }
}

//mirror( [0,1,0]) 
arm(false, true);