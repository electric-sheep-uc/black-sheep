/* "Resolution" of arcs */
if(str($qual) != "undef"){
  $fn = $qual;
}else{
  $fn = 64;
}
/* Constants in mm */
BODY_ROUNDED = true;
BODY_WIDTH = 28.5;
BODY_HEIGHT = 34.0;
BODY_DEPTH = 46.5;
BODY_HEIGHT_WITH_HORNS = 45.4;
HORN_DIAM = 23.9;
HORN_HEIGHT = 2.5;
HORN_HEIGHT_RING_HEIGHT = 2.4;
HORN_HEIGHT_RING_DIAM = 8.9;
HORN_DEPTH_OFFSET_FAR_SIDE = 35.25;
HORN_SCREW_DIAM = 3.0;
HORN_MOUNT_DIAM = 1.8;
HORN_MOUNT_DIST = 8.0;
HORN_DIST_TO_BODY = 0.7;
MOUNT_HOLE_DIST_TO_EDGE = 11;
MOUNT_FAR_DIST_TO_EDGE = 16;
MOUNT_NEAR_DIST_TO_EDGE = 8;
MOUNT_HOLE_DIAM = 2.4;
MOUNT_HOLE_HEIGHT = 10;
/* Plastic colour */
PRINT_COLOR = [0.2, 0.2, 0.2];

module body_mount_holes(screw_height, screw_diam, screw_off, screw_off_far, screw_off_near, body_width, body_depth, body_height){
  /* Top face translation */
  translate([(body_width / 2) + (screw_height / 2), 0, 0]){
    rotate([0, 90, 0]){
      /* Far side */
      translate([screw_off - (body_height / 2), -screw_off_far, 0]){
        cylinder(screw_height * 2, screw_diam / 2, screw_diam / 2, true);
      }
      translate([(body_height / 2) - screw_off, -screw_off_far, 0]){
        cylinder(screw_height * 2, screw_diam / 2, screw_diam / 2, true);
      }
      /* Near side */
      translate([screw_off - (body_height / 2), screw_off_near, 0]){
        cylinder(screw_height * 2, screw_diam / 2, screw_diam / 2, true);
      }
    }
  }
  /* Bottom face translation */
  translate([(-body_width / 2) + (-screw_height / 2), 0, 0]){
    rotate([0, 90, 0]){
      /* Far side */
      translate([screw_off - (body_height / 2), -screw_off_far, 0]){
        cylinder(screw_height * 2, screw_diam / 2, screw_diam / 2, true);
      }
      translate([(body_height / 2) - screw_off, -screw_off_far, 0]){
        cylinder(screw_height * 2, screw_diam / 2, screw_diam / 2, true);
      }
      /* Near side */
      translate([screw_off - (body_height / 2), screw_off_near, 0]){
        cylinder(screw_height * 2, screw_diam / 2, screw_diam / 2, true);
      }
    }
  }
 }