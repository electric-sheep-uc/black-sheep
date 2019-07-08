include <upper-arm-config.scad>
include <../Motor-FS6535/motor-fs6535-config.scad>
include <cage-side-config.scad>
include <../Motor-FS6535/motor-fs6535-config.scad>
use <../Motor-FS6535/motor-fs6535.scad>

module cageSide(withMotor, mount) {
	difference() {
		rotate([-90,0,0]) union() {
            //cage body 
           translate([-MOTOR_FS6535_BODY_LENGTH/2-CAGE_SIDE_WALL_WIDTH,-MOTOR_FS6535_BODY_WIDTH/2,0]) 
            cube([MOTOR_FS6535_BODY_LENGTH+2*CAGE_SIDE_WALL_WIDTH+2*CAGE_SIDE_BACKOFF,
                  MOTOR_FS6535_BODY_WIDTH +CAGE_SIDE_WALL_WIDTH+CAGE_SIDE_BACKOFF,
                  CAGE_SIDE_HEIGHT+CAGE_SIDE_WALL_WIDTH+CAGE_SIDE_BACKOFF]
            );
            
            //mount plate 
			translate([1,CAGE_SIDE_WALL_WIDTH,CAGE_SIDE_HEIGHT+CAGE_SIDE_WALL_WIDTH]) fs6535_motor_body_mount();
            //cube([MOTOR_FS6535_CENTER_PLATE_LENGTH,MOTOR_FS6535_CENTER_PLATE_WIDTH+4,5]);
		}
		
        // open front part of the box
    rotate([-90,0,0]) 
        translate(
        [-(MOTOR_FS6535_BODY_LENGTH/2),
        -(MOTOR_FS6535_BODY_WIDTH/2 -CAGE_SIDE_WALL_WIDTH),
        CAGE_SIDE_WALL_WIDTH]) 
        
        cube([MOTOR_FS6535_BODY_LENGTH+2*CAGE_SIDE_BACKOFF,
        MOTOR_FS6535_CENTER_PLATE_WIDTH+2*CAGE_SIDE_WALL_WIDTH+2*CAGE_SIDE_BACKOFF,
        MOTOR_FS6535_BODY_HEIGHT+MOTOR_FS6535_CENTER_PLATE_HEIGHT]);
	   
        // open the side for cabels
        rotate([-90,0,0]) translate([
        -(MOTOR_FS6535_BODY_LENGTH/2+CAGE_SIDE_WALL_WIDTH),
        -(MOTOR_FS6535_BODY_WIDTH/2-CAGE_SIDE_WALL_WIDTH),
        MOTOR_FS6535_BODY_HEIGHT/2-22]) 
        cube([CAGE_SIDE_WALL_WIDTH+3,MOTOR_FS6535_BODY_WIDTH+CAGE_SIDE_WALL_WIDTH,16]);
        
        // remove (open) the top side 
		/*rotate([-90,0,0]) 
        translate([-(MOTOR_FS6535_BODY_LENGTH/2),
        -(MOTOR_FS6535_BODY_WIDTH/2-CAGE_SIDE_WALL_WIDTH),
        CAGE_SIDE_WALL_WIDTH]) 
        cube([MOTOR_FS6535_BODY_LENGTH,MOTOR_FS6535_BODY_WIDTH+CAGE_SIDE_WALL_WIDTH,
        MOTOR_FS6535_BODY_HEIGHT+CAGE_SIDE_WALL_WIDTH]);*/
	}
	if (mount) {
		translate([-(MOTOR_FS6535_BODY_LENGTH/2)+ MOTOR_FS6535_SCREWS_DISTANCE_SIDE + 8, 0, -CAGE_SIDE_WALL_WIDTH])
        
        #rotate([90, 0, 0]) union() {
                //originaly r=6.2 
			cylinder(r=7.2, h=0.5, $fn=45);
			difference() {
                //originaly r=5 
				cylinder(r=6, h=5, $fn=45);
               # cylinder(r=MOTOR_FS6535_SHAFT_RADIUS*0.4, h=5, $fn=45);
				translate([0,0,-0.05]) cylinder(r=1.1, h=4, $fn=45);
			}
		}
		/*color("Green") rotate([-90,0,0]) translate([5.3, 4.95, -3.5]) 
        cube([0.4, 5, 2.5]);*/
	}
	if (withMotor) {
        color("LightBlue", 0.5)  rotate([90,0,180])  
        translate([0,
        (CAGE_SIDE_WALL_WIDTH-6),
        (MOTOR_FS6535_BODY_HEIGHT/2+CAGE_SIDE_WALL_WIDTH+CAGE_SIDE_BACKOFF)]) 
      //  rotate([90,0,180]) 
        fs6535_motor(); 
	}
}
cageSide(false, true);