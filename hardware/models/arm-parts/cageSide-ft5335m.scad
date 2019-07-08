include <upper-arm-config.scad>
include <cage-side-ft5335m-config.scad>
include <../Motor-FT5335M/motor-ft5335m-config.scad>
use <../Motor-FT5335M/motor-ft5335m.scad>

module cageSide(withMotor, mount) {
	difference() {
		rotate([-90,0,0]) union() {
            //cage body 
           translate([-MOTOR_FT5335M_BODY_LENGTH/2-CAGE_SIDE_WALL_WIDTH+CAGE_SIDE_BACKOFF/2,-MOTOR_FT5335M_BODY_WIDTH/2,0]) 
            
            cube([MOTOR_FT5335M_BODY_LENGTH+2*CAGE_SIDE_WALL_WIDTH,
                  MOTOR_FT5335M_BODY_WIDTH +CAGE_SIDE_WALL_WIDTH+CAGE_SIDE_BACKOFF,
                  CAGE_SIDE_HEIGHT+CAGE_SIDE_WALL_WIDTH+CAGE_SIDE_BACKOFF]
            );
            
            //mount plate 
		/*	translate([CAGE_SIDE_BACKOFF/2,
                       CAGE_SIDE_WALL_WIDTH,
                       (MOTOR_FT5335M_BODY_HEIGHT-MOTOR_FT5335M_CENTER_PLATE_HEIGHT)+CAGE_SIDE_BACKOFF]) 
            */
           translate([CAGE_SIDE_BACKOFF/2,
                       CAGE_SIDE_WALL_WIDTH, 
                       (MOTOR_FT5335M_LOWERBODY_HEIGHT+CAGE_SIDE_WALL_WIDTH-0.5)])
            ft5335m_motor_body_mount();
           // translate([CAGE_SIDE_BACKOFF/2,CAGE_SIDE_WALL_WIDTH,CAGE_SIDE_HEIGHT+CAGE_SIDE_BACKOFF+0.49]) ft5335m_motor_body_mount();
            //cube([MOTOR_FT5335M_CENTER_PLATE_LENGTH,MOTOR_FT5335M_CENTER_PLATE_WIDTH+4,5]); MOTOR_FT5335M_BODY_HEIGHT
		}
		
        // open front part of the box
    rotate([-90,0,0]) 
        translate(
        [-(MOTOR_FT5335M_BODY_LENGTH/2),
        -(MOTOR_FT5335M_BODY_WIDTH/2 -CAGE_SIDE_WALL_WIDTH),
        CAGE_SIDE_WALL_WIDTH]) 
        
       cube([MOTOR_FT5335M_BODY_LENGTH+CAGE_SIDE_BACKOFF,
        MOTOR_FT5335M_CENTER_PLATE_WIDTH+CAGE_SIDE_WALL_WIDTH,
        MOTOR_FT5335M_BODY_HEIGHT]);
	   
        // open the side for cabels
        rotate([-90,0,0]) translate([
        -(MOTOR_FT5335M_BODY_LENGTH/2+CAGE_SIDE_WALL_WIDTH+1),
        -(MOTOR_FT5335M_BODY_WIDTH/2-CAGE_SIDE_WALL_WIDTH),
        MOTOR_FT5335M_BODY_HEIGHT/2-22]) 
        cube([CAGE_SIDE_WALL_WIDTH+4,MOTOR_FT5335M_BODY_WIDTH+CAGE_SIDE_WALL_WIDTH,16]);
	}
	if (mount) {
		translate([-(MOTOR_FT5335M_BODY_LENGTH/2)+ MOTOR_FT5335M_SCREWS_DISTANCE_SIDE + 8, 0, -CAGE_SIDE_WALL_WIDTH])
        
        rotate([90, 0, 0]) union() {
			//cylinder(r=7.2, h=0.5, $fn=45);
			difference() {
			//	cylinder(r=6, h=5, $fn=45);
             //   cylinder(r=MOTOR_FT5335M_SHAFT_RADIUS*0.4, h=5, $fn=45);
			//	translate([0,0,-0.05]) cylinder(r=1.1, h=4, $fn=45);
			} 
        
		}
	}
	if (withMotor) {
        color("LightBlue", 0.5)  rotate([90,0,180])  
        translate([-CAGE_SIDE_BACKOFF,
        (CAGE_SIDE_WALL_WIDTH-6),
        (MOTOR_FT5335M_BODY_HEIGHT/2+CAGE_SIDE_WALL_WIDTH+CAGE_SIDE_BACKOFF)]) 
      //  rotate([90,0,180]) 
        ft5335m_motor(); 
	}
}
cageSide(false, true);