
include <motor-ft5335M-config.scad>
ft5335m_motor();
//FT5335M_motor_body_mount();

module ft5335m_motor_body_mount(){
    			//center plate (body mount plate)

difference(){
     cube([MOTOR_FT5335M_CENTER_PLATE_LENGTH,MOTOR_FT5335M_CENTER_PLATE_WIDTH,MOTOR_FT5335M_CENTER_PLATE_HEIGHT], center=true);
    
    // four holes two on each side for screws 
		translate([MOTOR_FT5335M_CENTER_PLATE_LENGTH/2-MOTOR_FT5335M_SCREWS_RADIUS-1.5,
        -(MOTOR_FT5335M_CENTER_PLATE_WIDTH/2 - MOTOR_FT5335M_SCREWS_DISTANCE_SIDE ),
        0])
   cylinder(r=MOTOR_FT5335M_SCREWS_RADIUS, h=MOTOR_FT5335M_CENTER_PLATE_HEIGHT, $fn=20, center=true);
        
        translate([ -(MOTOR_FT5335M_CENTER_PLATE_LENGTH/2-MOTOR_FT5335M_SCREWS_RADIUS-1.5),
        -(MOTOR_FT5335M_CENTER_PLATE_WIDTH/2 - MOTOR_FT5335M_SCREWS_DISTANCE_SIDE ),
        0])  
        cylinder(r=MOTOR_FT5335M_SCREWS_RADIUS, h=MOTOR_FT5335M_CENTER_PLATE_HEIGHT, $fn=20, center=true);
        
        translate([-(MOTOR_FT5335M_CENTER_PLATE_LENGTH/2-MOTOR_FT5335M_SCREWS_RADIUS-1.5),
        (MOTOR_FT5335M_CENTER_PLATE_WIDTH/2 - MOTOR_FT5335M_SCREWS_DISTANCE_SIDE ),
        0])  
        cylinder(r=MOTOR_FT5335M_SCREWS_RADIUS, h=MOTOR_FT5335M_CENTER_PLATE_HEIGHT, $fn=20, center=true);
        
        translate([MOTOR_FT5335M_CENTER_PLATE_LENGTH/2-MOTOR_FT5335M_SCREWS_RADIUS-1.5,
        (MOTOR_FT5335M_CENTER_PLATE_WIDTH/2 - MOTOR_FT5335M_SCREWS_DISTANCE_SIDE ),
        0])  
        cylinder(r=MOTOR_FT5335M_SCREWS_RADIUS, h=MOTOR_FT5335M_CENTER_PLATE_HEIGHT, $fn=20, center=true);
        
        // hole breaks 
        /*
        translate([MOTOR_FT5335M_CENTER_PLATE_LENGTH/2-0.8,
        -(MOTOR_FT5335M_CENTER_PLATE_WIDTH/2 - MOTOR_FT5335M_SCREWS_DISTANCE_SIDE ),
        (MOTOR_FT5335M_BODY_HEIGHT/2-4-MOTOR_FT5335M_CENTER_PLATE_HEIGHT/2)])  
        cylinder(r=1.7, h=MOTOR_FT5335M_CENTER_PLATE_HEIGHT, $fn=20, center=true);
        
        translate([ -(MOTOR_FT5335M_CENTER_PLATE_LENGTH/2-0.8),
        -(MOTOR_FT5335M_CENTER_PLATE_WIDTH/2 - MOTOR_FT5335M_SCREWS_DISTANCE_SIDE ),
        (MOTOR_FT5335M_BODY_HEIGHT/2-4-MOTOR_FT5335M_CENTER_PLATE_HEIGHT/2)])  
        cylinder(r=1.7, h=MOTOR_FT5335M_CENTER_PLATE_HEIGHT, $fn=20, center=true);
        
        translate([-(MOTOR_FT5335M_CENTER_PLATE_LENGTH/2-0.8),
        (MOTOR_FT5335M_CENTER_PLATE_WIDTH/2 - MOTOR_FT5335M_SCREWS_DISTANCE_SIDE ),
        (MOTOR_FT5335M_BODY_HEIGHT/2-4-MOTOR_FT5335M_CENTER_PLATE_HEIGHT/2)])  
        cylinder(r=1.7, h=MOTOR_FT5335M_CENTER_PLATE_HEIGHT, $fn=20, center=true);
        
        translate([MOTOR_FT5335M_CENTER_PLATE_LENGTH/2-0.8,
        (MOTOR_FT5335M_CENTER_PLATE_WIDTH/2 - MOTOR_FT5335M_SCREWS_DISTANCE_SIDE ),
        (MOTOR_FT5335M_BODY_HEIGHT/2-4-MOTOR_FT5335M_CENTER_PLATE_HEIGHT/2)])  
        cylinder(r=1.7, h=MOTOR_FT5335M_CENTER_PLATE_HEIGHT, $fn=20, center=true);*/
    }
    }

module ft5335m_motor_body()
    {
                    //body block
			 cube([MOTOR_FT5335M_BODY_LENGTH,MOTOR_FT5335M_BODY_WIDTH,MOTOR_FT5335M_BODY_HEIGHT], center=true);
        }

module ft5335m_motor_top_plate()
        {
            //cube([MOTOR_FT5335M_TOP_PLATE_LENGTH,MOTOR_FT5335M_TOP_PLATE_WIDTH,MOTOR_FT5335M_TOP_PLATE_HEIGHT], center=true);
            }
module ft5335m_motor_shaft()
            {
               // cylinder(r=MOTOR_FT5335M_SHAFT_RADIUS, h=MOTOR_FT5335M_SHAFT_HEIGHT, $fn=20, center=true);
                }
module ft5335m_motor_shaft_support()
                {
                    cylinder(r=MOTOR_FT5335M_TOP_CYLINDER_RADIUS, h=MOTOR_FT5335M_TOP_CYLINDER_HEIGHT, $fn=100, center=true);		}
                    
module ft5335m_motor(){	
             ft5335m_motor_body();
            
            //CENTER_LINE 
            /*
             translate([0,0,MOTOR_FT5335M_BODY_HEIGHT/2-4]) 
            cube([MOTOR_FT5335M_CENTER_LINE_LENGTH,MOTOR_FT5335M_CENTER_LINE_WIDTH,MOTOR_FT5335M_CENTER_LINE_HEIGHT], center=true);*/
            //body mount 
            //translate([0,0,MOTOR_FT5335M_BODY_HEIGHT/2-4-MOTOR_FT5335M_CENTER_PLATE_HEIGHT/2])   FT5335M_motor_body_mount();
            translate([0,0, MOTOR_FT5335M_CENTER_PLATE_OFFSET-MOTOR_FT5335M_BODY_HEIGHT/2]) ft5335m_motor_body_mount();
            
    //top plate 
             //translate([(MOTOR_FT5335M_BODY_LENGTH-MOTOR_FT5335M_TOP_PLATE_LENGTH)/2,0,MOTOR_FT5335M_BODY_HEIGHT/2]) FT5335M_motor_top_plate();
            // shaft cylinder 
			//translate([MOTOR_FT5335M_BODY_LENGTH/2-12.5,0,MOTOR_FT5335M_BODY_HEIGHT/2 + MOTOR_FT5335M_SHAFT_HEIGHT/2]) FT5335M_motor_shaft();

            //cylinder around shaft 
            translate([MOTOR_FT5335M_BODY_LENGTH/2-12.5,0,MOTOR_FT5335M_BODY_HEIGHT/2]) 
            ft5335m_motor_shaft_support();		
}