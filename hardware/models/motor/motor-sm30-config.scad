/* "Resolution" of arcs */
if(str($qual) != "undef"){
  $fn = $qual;
}else{
  $fn = 64;
}
/* Constants in mm */
BODY_ROUNDED = true;
BODY_WIDTH = 28.0;
BODY_HEIGHT = 34.4;
BODY_DEPTH = 52.0;
BODY_HEIGHT_WITH_HORNS = 45.4;
HORN_DIAM = 23.9;
HORN_HEIGHT = 2.5;
HORN_HEIGHT_RING_HEIGHT = 2.4;
HORN_HEIGHT_RING_DIAM = 8.9;
HORN_DEPTH_OFFSET_FAR_SIDE = 38.0;
HORN_SCREW_DIAM = 3.0;
HORN_MOUNT_INNER_DIAM = 1.8;
HORN_MOUNT_INNER_DIST = 8.0;
HORN_MOUNT_OUTER_DIAM = 1.8;
HORN_MOUNT_OUTER_DIST = 9.5;
HORN_DIST_TO_BODY = 0.7;
MOUNT_HOLE_DIST_TO_EDGE = 1.8;
MOUNT_HOLE_DIAM = 2.4;
MOUNT_HOLE_HEIGHT = 10;
/* Plastic colour */
PRINT_COLOR = [0.2, 0.2, 0.2];

module body_mount_holes(screw_height, screw_diam, screw_offset, body_width, body_depth, body_height){
  /* Top face translation */
  translate([0, 0, (body_height / 2) + (screw_height / 2)]){
    /* Left upper mount */
    translate([screw_offset - (body_width / 2), (body_depth / 2) - screw_offset, 0]){
      cylinder(screw_height * 2, screw_diam / 2, screw_diam / 2, true);
    }
    /* Left middle mount */
    translate([screw_offset - (body_width / 2), 0, 0]){
      cylinder(screw_height * 2, screw_diam / 2, screw_diam / 2, true);
    }
    /* Left lower mount */
    translate([screw_offset - (body_width / 2), screw_offset - (body_depth / 2), 0]){
      cylinder(screw_height * 2, screw_diam / 2, screw_diam / 2, true);
    }
    /* Right upper mount */
    translate([(body_width / 2) - screw_offset, (body_depth / 2) - screw_offset, 0]){
      cylinder(screw_height * 2, screw_diam / 2, screw_diam / 2, true);
    }
    /* Right middle mount */
    translate([(body_width / 2) - screw_offset, 0, 0]){
      cylinder(screw_height * 2, screw_diam / 2, screw_diam / 2, true);
    }
    /* Right lower mount */
    translate([(body_width / 2) - screw_offset, screw_offset - (body_depth / 2), 0]){
      cylinder(screw_height * 2, screw_diam / 2, screw_diam / 2, true);
    }
  }
  /* Bottom face translation */
  translate([0, 0, - (body_height / 2) - (screw_height / 2)]){
    /* Left upper mount */
    translate([screw_offset - (body_width / 2), (body_depth / 2) - screw_offset, 0]){
      cylinder(screw_height * 2, screw_diam / 2, screw_diam / 2, true);
    }
    /* Left middle mount */
    translate([screw_offset - (body_width / 2), 0, 0]){
      cylinder(screw_height * 2, screw_diam / 2, screw_diam / 2, true);
    }
    /* Left lower mount */
    translate([screw_offset - (body_width / 2), screw_offset - (body_depth / 2), 0]){
      cylinder(screw_height * 2, screw_diam / 2, screw_diam / 2, true);
    }
    /* Right upper mount */
    translate([(body_width / 2) - screw_offset, (body_depth / 2) - screw_offset, 0]){
      cylinder(screw_height * 2, screw_diam / 2, screw_diam / 2, true);
    }
    /* Right middle mount */
    translate([(body_width / 2) - screw_offset, 0, 0]){
      cylinder(screw_height * 2, screw_diam / 2, screw_diam / 2, true);
    }
    /* Right lower mount */
    translate([(body_width / 2) - screw_offset, screw_offset - (body_depth / 2), 0]){
      cylinder(screw_height * 2, screw_diam / 2, screw_diam / 2, true);
    }
  }
}