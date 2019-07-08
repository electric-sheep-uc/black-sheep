include <motor-sm40-config.scad>;

module horn(horn_diam, horn_height, ring_diam, ring_height){
  cylinder(horn_height, horn_diam / 2, horn_diam / 2, true);
  translate([0, 0, horn_height]){
    cylinder(ring_height, ring_diam / 2, ring_diam / 2, true);
  }
}

module horn_center_hole(screw_diam, horn_height, ring_height){
  cylinder((horn_height + ring_height) * 2, screw_diam / 2, screw_diam / 2, true);
}

module horn_holes(screw_diam, screw_dist, horn_height){
  rotate([0, 0, 0]){
    /* North screw hole */
    translate([0, screw_dist, 0]){
      cylinder(horn_height * 2, screw_diam / 2, screw_diam / 2, true);
    }
    /* East screw hole */
    translate([screw_dist, 0, 0]){
      cylinder(horn_height * 2, screw_diam / 2, screw_diam / 2, true);
    }
    /* South screw hole */
    translate([0, -screw_dist, 0]){
      cylinder(horn_height * 2, screw_diam / 2, screw_diam / 2, true);
    }
    /* West screw hole */
    translate([-screw_dist, 0, 0]){
      cylinder(horn_height * 2, screw_diam / 2, screw_diam / 2, true);
    }
  }
}

module motor_sm40_horn_top(){
  /* Apply global properties */
  color(PRINT_COLOR){
    translate([0, 0, HORN_HEIGHT / 2]){
      difference(){
        horn(HORN_DIAM, HORN_HEIGHT, HORN_HEIGHT_RING_DIAM, HORN_HEIGHT_RING_HEIGHT);
        horn_center_hole(HORN_SCREW_DIAM, HORN_HEIGHT, HORN_HEIGHT_RING_HEIGHT);
        horn_holes(HORN_MOUNT_DIAM, HORN_MOUNT_DIST, HORN_HEIGHT);
      }
    }
  }
}

module offset_motor_sm40_horn_top(){
  translate([0, HORN_DEPTH_OFFSET_FAR_SIDE - (BODY_DEPTH / 2), (BODY_HEIGHT / 2) + HORN_DIST_TO_BODY]){
    motor_sm40_horn_top();
  }
}

offset_motor_sm40_horn_top();