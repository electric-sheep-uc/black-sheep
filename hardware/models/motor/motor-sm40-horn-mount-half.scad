include <motor-sm40-config.scad>;
use <motor-sm40-horn-top.scad>;

module half_horn_bracket(horn_diam, horn_height, ring_diam, ring_height, hm_diam, screw_diam, screw_dist, body_height){
  outer_mount_scale = (1 / 2) * 1.5;
  inner_mount_scale = (1 / 2) * 1.05;
  inner_ring_scale = (1 / 2) * 1.2;
  bracket_width_scale = 1.4;
  /* NOTE: Magic multiplier for motor clearence. */
  clear_scale = 1.75;
  difference(){
    translate([0, 0, horn_height]){
      difference(){
        union(){
          translate([0, 0, horn_height / 0.75]){
            cylinder(horn_height * 3.25, horn_diam * inner_mount_scale, horn_diam * inner_mount_scale, true);
          }
          translate([0, horn_diam * outer_mount_scale * clear_scale * 0.5, horn_height * 2]){
            cube([horn_diam * outer_mount_scale * bracket_width_scale, horn_diam * outer_mount_scale * clear_scale, horn_height * 2], true);
          }
        }
        cylinder(ring_height * 8, ring_diam * inner_ring_scale, ring_diam * inner_ring_scale, true);
        translate([0, -ring_diam * inner_ring_scale * 2, 0]){
          cube([ring_diam * inner_ring_scale * 2, ring_diam * inner_ring_scale * 4, ring_height * 8], true);
        }
      }
    }
    scale([1, 1, 8]){
      horn_center_hole(hm_diam, horn_height, ring_height);
      /* NOTE: Widen holes, allow easier fit of screw. */
      horn_holes(screw_diam * 1.1, screw_dist, horn_height);
    }
    translate([0, 0, horn_height * 3.25]){
      horn_holes(screw_diam * 2, screw_dist, horn_height * 2);
      horn_holes(screw_diam * 2.5, screw_dist, horn_height * 1.5);
    }
  }
}

module motor_sm40_horn_mount_half(){
  wire_hole = 15;
  /* Apply global properties */
  color(PRINT_COLOR){
    half_horn_bracket(HORN_DIAM, HORN_HEIGHT, HORN_HEIGHT_RING_DIAM, HORN_HEIGHT_RING_HEIGHT, HORN_SCREW_DIAM, HORN_MOUNT_DIAM, HORN_MOUNT_DIST, BODY_HEIGHT);
  }
}

module offset_motor_sm40_horn_mount_half(){
  motor_sm40_horn_mount_half();
}

offset_motor_sm40_horn_mount_half();