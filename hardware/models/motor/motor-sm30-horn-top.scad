include <motor-sm30-config.scad>;

module horn(horn_diam, horn_height, ring_diam, ring_height){
  cylinder(horn_height, horn_diam / 2, horn_diam / 2, true);
  translate([0, 0, horn_height]){
    cylinder(ring_height, ring_diam / 2, ring_diam / 2, true);
  }
}

module horn_center_hole(screw_diam, horn_height, ring_height){
  cylinder((horn_height + ring_height) * 2, screw_diam / 2, screw_diam / 2, true);
}

module horn_holes(inner_screw_diam, inner_screw_dist, outer_screw_diam, outer_screw_dist, horn_height){
  /* Inner holes */
  rotate([0, 0, 0]){
    /* North screw hole */
    translate([0, inner_screw_dist, 0]){
      cylinder(horn_height * 2, inner_screw_diam / 2, inner_screw_diam / 2, true);
    }
    /* East screw hole */
    translate([inner_screw_dist, 0, 0]){
      cylinder(horn_height * 2, inner_screw_diam / 2, inner_screw_diam / 2, true);
    }
    /* South screw hole */
    translate([0, -inner_screw_dist, 0]){
      cylinder(horn_height * 2, inner_screw_diam / 2, inner_screw_diam / 2, true);
    }
    /* West screw hole */
    translate([-inner_screw_dist, 0, 0]){
      cylinder(horn_height * 2, inner_screw_diam / 2, inner_screw_diam / 2, true);
    }
  }
  /* Outer holes */
  rotate([0, 0, 45]){
    /* North screw hole */
    translate([0, outer_screw_dist, 0]){
      cylinder(horn_height * 2, outer_screw_diam / 2, outer_screw_diam / 2, true);
    }
    /* East screw hole */
    translate([outer_screw_dist, 0, 0]){
      cylinder(horn_height * 2, outer_screw_diam / 2, outer_screw_diam / 2, true);
    }
    /* South screw hole */
    translate([0, -outer_screw_dist, 0]){
      cylinder(horn_height * 2, outer_screw_diam / 2, outer_screw_diam / 2, true);
    }
    /* West screw hole */
    translate([-outer_screw_dist, 0, 0]){
      cylinder(horn_height * 2, outer_screw_diam / 2, outer_screw_diam / 2, true);
    }
  }
}

module motor_sm30_horn_top(){
  /* Apply global properties */
  color(PRINT_COLOR){
    translate([0, 0, HORN_HEIGHT / 2]){
      difference(){
        horn(HORN_DIAM, HORN_HEIGHT, HORN_HEIGHT_RING_DIAM, HORN_HEIGHT_RING_HEIGHT);
        horn_center_hole(HORN_SCREW_DIAM, HORN_HEIGHT, HORN_HEIGHT_RING_HEIGHT);
        horn_holes(HORN_MOUNT_INNER_DIAM, HORN_MOUNT_INNER_DIST, HORN_MOUNT_OUTER_DIAM, HORN_MOUNT_OUTER_DIST, HORN_HEIGHT);
      }
    }
  }
}

module offset_motor_sm30_horn_top(){
  translate([0, HORN_DEPTH_OFFSET_FAR_SIDE - (BODY_DEPTH / 2), (BODY_HEIGHT / 2) + HORN_DIST_TO_BODY]){
    motor_sm30_horn_top();
  }
}

offset_motor_sm30_horn_top();