include <motor-ft5335M-horn-config.scad>

module horn(horn_radius, horn_height){
  //cylinder(horn_height, horn_radius, horn_radius, true);
  cube([HORN_LENGTH,HORN_WIDTH,HORN_HEIGHT], center=true);  
}

module horn_holes(screw_radius, screw_radius_horn, horn_height){
   
	translate([HORN_SCREW_RADIUS_1,0,0]) cylinder(horn_height+2, screw_radius, screw_radius, true);
    translate([-HORN_SCREW_RADIUS_1,0,0]) cylinder(horn_height+2, screw_radius, screw_radius, true);
    
    translate([HORN_SCREW_RADIUS_2,0,0]) cylinder(horn_height+2, screw_radius, screw_radius, true);
    translate([-HORN_SCREW_RADIUS_2,0,0]) cylinder(horn_height+2, screw_radius, screw_radius, true);
    
    translate([HORN_SCREW_RADIUS_3,0,0]) cylinder(horn_height+2, screw_radius, screw_radius, true);
    translate([-HORN_SCREW_RADIUS_3,0,0]) cylinder(horn_height+2, screw_radius, screw_radius, true);

//HORN_CENTER_HOLE_RADIES;
   translate([0, 0, 0]) cylinder(h=horn_height, r=HORN_CENTER_HOLE_RADIES, center=true);
  //  translate([0, 0, 0]) cylinder(h=horn_height, r=horn_height/2, center=true);
}
//motor_ft5335m_horn
module motor_ft5335m_horn(){
  /* Apply global properties */
  color(PRINT_COLOR){
    translate([0, 0, HORN_HEIGHT / 2]){
      difference(){
        horn(HORN_RADIUS, HORN_HEIGHT);
        horn_holes(HORN_SCREW_HOLE_DIAMETER / 2, HORN_SCREW_RADIUS, HORN_HEIGHT * 2);
      }
    }
  }
}

module offset_motor_ft5335m_horn(){
  //translate([0, HORN_DEPTH_OFFSET, ((BODY_HEIGHT) / 2) + (HORN_HEIGHT * 0.5)])
    {
    motor_ft5335m_horn();
  }
}

offset_motor_ft5335m_horn();

