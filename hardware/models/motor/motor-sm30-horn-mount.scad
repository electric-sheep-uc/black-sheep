include <motor-sm30-config.scad>;
use <motor-sm30-horn-top.scad>;
use <motor-sm30-horn-mount-half.scad>;

module horn_bracket(horn_diam, horn_height, ring_diam, ring_height, screw_diam, inner_screw_diam, inner_screw_dist, outer_screw_diam, outer_screw_dist, body_height){
  outer_mount_scale = (1 / 2) * 1.5;
  inner_mount_scale = (1 / 2) * 1.05;
  inner_ring_scale = (1 / 2) * 1.2;
  bracket_width_scale = 1.4;
  /* NOTE: Magic multiplier for motor clearence. */
  clear_scale = 1.75;
  difference(){
    union(){
      offset_motor_sm30_horn_mount_half();
      translate([0, 0, horn_height]){
        translate([0, horn_diam * outer_mount_scale * clear_scale, -((body_height - (horn_height * 2)) / 2)]){
          cube([horn_diam * outer_mount_scale * bracket_width_scale, horn_height * 2, body_height + (horn_height * 4)], true);
        }
      }
    }
    translate([0, 0, horn_height * 3.25]){
      horn_holes(inner_screw_diam * 2, inner_screw_dist, outer_screw_diam * 2, outer_screw_dist, horn_height * 2);
      horn_holes(inner_screw_diam * 2.5, inner_screw_dist, outer_screw_diam * 2.5, outer_screw_dist, horn_height * 1.5);
    }
  }
}

module motor_sm30_horn_mount(){
  wire_hole = 15;
  /* Apply global properties */
  color(PRINT_COLOR){
    difference(){
      union(){
        translate([0, HORN_DEPTH_OFFSET_FAR_SIDE - (BODY_DEPTH / 2), (BODY_HEIGHT / 2) + ((HORN_HEIGHT_RING_HEIGHT) / 2) + (HORN_DIST_TO_BODY / 2)]){
          horn_bracket(HORN_DIAM, HORN_HEIGHT, HORN_HEIGHT_RING_DIAM, HORN_HEIGHT_RING_HEIGHT, HORN_SCREW_DIAM, HORN_MOUNT_INNER_DIAM, HORN_MOUNT_INNER_DIST, HORN_MOUNT_OUTER_DIAM, HORN_MOUNT_OUTER_DIST, BODY_HEIGHT);
        }
        mirror([0, 0, 180]){
          translate([0, HORN_DEPTH_OFFSET_FAR_SIDE - (BODY_DEPTH / 2), (BODY_HEIGHT / 2) + ((HORN_HEIGHT_RING_HEIGHT) / 2) + (HORN_DIST_TO_BODY / 2)]){
            horn_bracket(HORN_DIAM, HORN_HEIGHT, HORN_HEIGHT_RING_DIAM, HORN_HEIGHT_RING_HEIGHT, HORN_SCREW_DIAM, HORN_MOUNT_INNER_DIAM, HORN_MOUNT_INNER_DIST, HORN_MOUNT_OUTER_DIAM, HORN_MOUNT_OUTER_DIST, BODY_HEIGHT);
          }
        }
      }
      translate([0, BODY_DEPTH / 1.25, 0]){
        rotate([90, 0, 0]){
          cylinder(BODY_DEPTH / 2, wire_hole / 2, wire_hole / 2, true);
        }
      }
    }
  }
}

module offset_motor_sm30_horn_mount(){
  motor_sm30_horn_mount();
}

offset_motor_sm30_horn_mount();