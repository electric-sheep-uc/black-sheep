
include <motor-fs6535-config.scad>
fs6535_motor();
//fs6535_motor_body_mount();

module fs6535_motor_body_mount(){
    			//center plate (body mount plate)
difference(){
     cube([MOTOR_FS6535_CENTER_PLATE_LENGTH,MOTOR_FS6535_CENTER_PLATE_WIDTH,MOTOR_FS6535_CENTER_PLATE_HEIGHT], center=true);
    
    // four holes two on each side for screws 
		translate([MOTOR_FS6535_CENTER_PLATE_LENGTH/2-MOTOR_FS6535_SCREWS_RADIUS-1.5,
        -(MOTOR_FS6535_CENTER_PLATE_WIDTH/2 - MOTOR_FS6535_SCREWS_DISTANCE_SIDE ),
        0])
   cylinder(r=MOTOR_FS6535_SCREWS_RADIUS, h=MOTOR_FS6535_CENTER_PLATE_HEIGHT, $fn=20, center=true);
        
        translate([ -(MOTOR_FS6535_CENTER_PLATE_LENGTH/2-MOTOR_FS6535_SCREWS_RADIUS-1.5),
        -(MOTOR_FS6535_CENTER_PLATE_WIDTH/2 - MOTOR_FS6535_SCREWS_DISTANCE_SIDE ),
        0])  
        cylinder(r=MOTOR_FS6535_SCREWS_RADIUS, h=MOTOR_FS6535_CENTER_PLATE_HEIGHT, $fn=20, center=true);
        
        translate([-(MOTOR_FS6535_CENTER_PLATE_LENGTH/2-MOTOR_FS6535_SCREWS_RADIUS-1.5),
        (MOTOR_FS6535_CENTER_PLATE_WIDTH/2 - MOTOR_FS6535_SCREWS_DISTANCE_SIDE ),
        0])  
        cylinder(r=MOTOR_FS6535_SCREWS_RADIUS, h=MOTOR_FS6535_CENTER_PLATE_HEIGHT, $fn=20, center=true);
        
        translate([MOTOR_FS6535_CENTER_PLATE_LENGTH/2-MOTOR_FS6535_SCREWS_RADIUS-1.5,
        (MOTOR_FS6535_CENTER_PLATE_WIDTH/2 - MOTOR_FS6535_SCREWS_DISTANCE_SIDE ),
        0])  
        cylinder(r=MOTOR_FS6535_SCREWS_RADIUS, h=MOTOR_FS6535_CENTER_PLATE_HEIGHT, $fn=20, center=true);
        
        // hole breaks 
        /*
        translate([MOTOR_FS6535_CENTER_PLATE_LENGTH/2-0.8,
        -(MOTOR_FS6535_CENTER_PLATE_WIDTH/2 - MOTOR_FS6535_SCREWS_DISTANCE_SIDE ),
        (MOTOR_FS6535_BODY_HEIGHT/2-4-MOTOR_FS6535_CENTER_PLATE_HEIGHT/2)])  
        cylinder(r=1.7, h=MOTOR_FS6535_CENTER_PLATE_HEIGHT, $fn=20, center=true);
        
        translate([ -(MOTOR_FS6535_CENTER_PLATE_LENGTH/2-0.8),
        -(MOTOR_FS6535_CENTER_PLATE_WIDTH/2 - MOTOR_FS6535_SCREWS_DISTANCE_SIDE ),
        (MOTOR_FS6535_BODY_HEIGHT/2-4-MOTOR_FS6535_CENTER_PLATE_HEIGHT/2)])  
        cylinder(r=1.7, h=MOTOR_FS6535_CENTER_PLATE_HEIGHT, $fn=20, center=true);
        
        translate([-(MOTOR_FS6535_CENTER_PLATE_LENGTH/2-0.8),
        (MOTOR_FS6535_CENTER_PLATE_WIDTH/2 - MOTOR_FS6535_SCREWS_DISTANCE_SIDE ),
        (MOTOR_FS6535_BODY_HEIGHT/2-4-MOTOR_FS6535_CENTER_PLATE_HEIGHT/2)])  
        cylinder(r=1.7, h=MOTOR_FS6535_CENTER_PLATE_HEIGHT, $fn=20, center=true);
        
        translate([MOTOR_FS6535_CENTER_PLATE_LENGTH/2-0.8,
        (MOTOR_FS6535_CENTER_PLATE_WIDTH/2 - MOTOR_FS6535_SCREWS_DISTANCE_SIDE ),
        (MOTOR_FS6535_BODY_HEIGHT/2-4-MOTOR_FS6535_CENTER_PLATE_HEIGHT/2)])  
        cylinder(r=1.7, h=MOTOR_FS6535_CENTER_PLATE_HEIGHT, $fn=20, center=true);*/
    }
    }

module fs6535_motor_body()
    {
                    //body block
			 cube([MOTOR_FS6535_BODY_LENGTH,MOTOR_FS6535_BODY_WIDTH,MOTOR_FS6535_BODY_HEIGHT], center=true);
        }

module fs6535_motor_top_plate()
        {
            cube([MOTOR_FS6535_TOP_PLATE_LENGTH,MOTOR_FS6535_TOP_PLATE_WIDTH,MOTOR_FS6535_TOP_PLATE_HEIGHT], center=true);}
module fs6535_motor_shaft()
            {
                cylinder(r=MOTOR_FS6535_SHAFT_RADIUS, h=MOTOR_FS6535_SHAFT_HEIGHT, $fn=20, center=true);}
module fs6535_motor_shaft_support()
                {
                    cylinder(r=MOTOR_FS6535_TOP_CYLINDER_RADIUS, h=MOTOR_FS6535_TOP_CYLINDER_HEIGHT, $fn=100, center=true);		}
                    
module fs6535_motor(){	
             fs6535_motor_body();
            
            //CENTER_LINE 
            /*
             translate([0,0,MOTOR_FS6535_BODY_HEIGHT/2-4]) 
            cube([MOTOR_FS6535_CENTER_LINE_LENGTH,MOTOR_FS6535_CENTER_LINE_WIDTH,MOTOR_FS6535_CENTER_LINE_HEIGHT], center=true);*/
            //body mount 
            translate([0,0,MOTOR_FS6535_BODY_HEIGHT/2-4-MOTOR_FS6535_CENTER_PLATE_HEIGHT/2])   fs6535_motor_body_mount();
            
            //top plate 
             translate([(MOTOR_FS6535_BODY_LENGTH-MOTOR_FS6535_TOP_PLATE_LENGTH)/2,0,MOTOR_FS6535_BODY_HEIGHT/2]) fs6535_motor_top_plate();
            
            
            // shaft cylinder 
			translate([MOTOR_FS6535_BODY_LENGTH/2-12.5,0,MOTOR_FS6535_BODY_HEIGHT/2 + MOTOR_FS6535_SHAFT_HEIGHT/2]) fs6535_motor_shaft();
            
			
            //cylinder around shaft 
            translate([MOTOR_FS6535_BODY_LENGTH/2-12.5,0,MOTOR_FS6535_BODY_HEIGHT/2 + MOTOR_FS6535_SHAFT_HEIGHT/2 - MOTOR_FS6535_TOP_CYLINDER_HEIGHT/2]) 
            fs6535_motor_shaft_support();		
}