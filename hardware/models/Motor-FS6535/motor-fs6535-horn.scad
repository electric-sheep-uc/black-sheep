include <motor-fs6535-horn-config.scad>

module horn(horn_radius, horn_height){
  cylinder(horn_height, horn_radius, horn_radius, true);
}

module horn_holes(screw_radius, screw_radius_horn, horn_height){
   for (i=[1:NUMBER_OF_HOLES])  {
	translate([HORN_HOLES_INNER_RADIUS*cos(i*(360/NUMBER_OF_HOLES)),HORN_HOLES_INNER_RADIUS*sin(i*(360/NUMBER_OF_HOLES)),0]) 
       cylinder(horn_height+2, screw_radius, screw_radius, true);
}  
   for (i=[1:NUMBER_OF_HOLES])  {
	translate([HORN_HOLES_OUTER_RADIUS*cos(i*(360/NUMBER_OF_HOLES)),HORN_HOLES_OUTER_RADIUS*sin(i*(360/NUMBER_OF_HOLES)),0]) 
       cylinder(horn_height+2, screw_radius, screw_radius, true);
}
//HORN_CENTER_HOLE_RADIES;
   translate([0,0, 0]) cylinder(h=horn_height+6, r=HORN_CENTER_HOLE_RADIES+2, center=true);
}

module motor_fs6535_horn(){
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

module offset_motor_fs6535_horn(){
  //translate([0, HORN_DEPTH_OFFSET, ((BODY_HEIGHT) / 2) + (HORN_HEIGHT * 0.5)])
    {
    motor_fs6535_horn();
  }
}

offset_motor_fs6535_horn();

