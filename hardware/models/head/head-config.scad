/* "Resolution" of arcs */
if(str($qual) != "undef"){
  $fn = $qual;
}else{
  $fn = 64;
}
/* Constants in mm */
HEAD_SIZE = 100 /  2;
EYE_SIZE = HEAD_SIZE / 2.5;
CABLE_SIZE = 12;
EAR_SIZE = EYE_SIZE;
EAR_RADIUS = EYE_SIZE / 2;
EAR_ANGLE = 45;
MOUNT_SIZE = HEAD_SIZE / 5;
SCREW_SIZE = 1;
PILOT_SIZE = SCREW_SIZE * 3;
THICKNESS = 2;
/* Plastic colour */
PRINT_COLOR = [0.2, 0.2, 0.2];

module head_base(head_radius, keep_ratio, thickness){
  /* Create the top half of the head */
  intersection(){
    /* Create hollow sphere */
    difference(){
      sphere(head_radius);
      sphere(head_radius - thickness);
    }
    /* Offset the intersection sube */
    translate([0, 0, head_radius * 0.5]){
      cube([head_radius * 2, head_radius * 2, head_radius * 2 * keep_ratio], true);
    }
  };
}

module eye_socket(head_radius, eye_size){
  /* Position the eyes at the edge of the head */
  translate([0, -head_radius, 0]){
    /* Center */
    sphere(eye_size);
  }
}

module cable_socket(head_radius, cable_size){
  /* Position the cable at the bottom of the head */
  rotate([30, 0, 0]){
    translate([0, head_radius, 0]){
      /* Center */
      sphere(cable_size);
    }
  }
}

module head_to_head_mounts(head_radius, mount_size){
  /* Right side */
  translate([head_radius - (mount_size * 0.25), 0, mount_size * 0.5]){
    cube([mount_size * 0.5, mount_size, mount_size], true);
  }
  /* Left side */
  translate([-head_radius + (mount_size * 0.25), 0, mount_size * 0.5]){
    cube([mount_size * 0.5, mount_size, mount_size], true);
  }
}