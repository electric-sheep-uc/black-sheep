include <motor-sm30-config.scad>;

module body_shell(body_width, body_depth, body_height, horn_height, horn_diam, screw_height, screw_diam, screw_offset){
  thickness = horn_height * 2;
  shell_gap = 1.025;
  horn_gap = 1.75;
  difference(){
    translate([0, -thickness / 2, 0]){
      difference(){
        cube([body_width + thickness, body_depth, thickness + body_height], true);
        /* Remove spaces to keep cool and light */
        union(){
          /* Also allow for wire connector */
          translate([0, body_depth / 3.5, -body_height / 4]){
            cube([body_width * 2, body_depth / 4, body_height / 3], true);
          }
          translate([0, body_depth / 3.5, body_height / 4]){
            cube([body_width * 2, body_depth / 4, body_height / 3], true);
          }
        }
      }
    }
    cube([body_width * shell_gap, body_depth * shell_gap, body_height * shell_gap], true);
    /* Remove the screws */
    body_mount_holes(screw_height, screw_diam * 1.1, screw_offset, body_width, body_depth, body_height);
    /* NOTE: Indentation holes are a massive hack. */
    scale([1, 1, 1.55]){
      body_mount_holes(screw_height, screw_diam * 1.8, screw_offset, body_width, body_depth, body_height);
    }
    /* Remove horn footprint */
    translate([0, HORN_DEPTH_OFFSET_FAR_SIDE - (BODY_DEPTH / 2), 0]){
      cylinder(horn_height * 16, horn_diam / 1.8, horn_diam / 1.8, true);
      translate([0, horn_diam / 1.8, 0]){
        cube([2 * horn_diam / 1.8, 2 * horn_diam / 1.8, horn_height * 16], true);
      }
    }
  }
}

module motor_sm30_body_mount(){
  /* Apply global properties */
  color(PRINT_COLOR){
    union(){
      body_shell(BODY_WIDTH, BODY_DEPTH, BODY_HEIGHT, HORN_HEIGHT, HORN_DIAM, MOUNT_HOLE_HEIGHT, MOUNT_HOLE_DIAM, MOUNT_HOLE_DIST_TO_EDGE);
    }
  }
}

module offset_motor_sm30_body_mount(){
  motor_sm30_body_mount();
}

offset_motor_sm30_body_mount();
