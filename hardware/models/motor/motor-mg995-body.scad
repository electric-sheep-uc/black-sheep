include <motor-mg995-config.scad>

module body(body_width, body_height, body_depth){
  cube([body_width, body_depth, body_height], true);
}

module body_mounts(mount_width, mount_height, mount_depth, mount_offset, mount_hole_offset_y){
  /* North mount */
  translate([0, mount_hole_offset_y, mount_offset]){
    cube([mount_width, mount_depth, mount_height], true);
  }
  /* South mount */
  translate([0, -mount_hole_offset_y, mount_offset]){
    cube([mount_width, mount_depth, mount_height], true);
  }
}

module body_mount_holes(screw_height, screw_radius, screw_offset_x, screw_offset_y, mount_offset){
  /* North mount left */
  translate([-screw_offset_x, screw_offset_y, mount_offset]){
    cylinder(screw_height * 1.01, screw_radius, screw_radius, true);
  }
  /* North mount right */
  translate([screw_offset_x, screw_offset_y, mount_offset]){
    cylinder(screw_height * 1.01, screw_radius, screw_radius, true);
  }
  /* South mount left */
  translate([-screw_offset_x, -screw_offset_y, mount_offset]){
    cylinder(screw_height * 1.01, screw_radius, screw_radius, true);
  }
  /* South mount right */
  translate([screw_offset_x, -screw_offset_y, mount_offset]){
    cylinder(screw_height * 1.01, screw_radius, screw_radius, true);
  }
}

module motor_mg995_body(){
  /* Apply global properties */
  color(PRINT_COLOR){
    translate([0, 0, BODY_DEPTH / 2]){
      union(){
        body(BODY_WIDTH, BODY_HEIGHT, BODY_DEPTH);
        difference(){
          body_mounts(BODY_WIDTH, MOUNT_HEIGHT, MOUNT_DEPTH, (MOUNT_OFFSET_BOTTOM - MOUNT_HEIGHT) / 2, (MOUNT_DEPTH + BODY_DEPTH) / 2);
          body_mount_holes(MOUNT_HEIGHT, MOUNT_HOLE_DIAM / 2, MOUNT_HOLE_DIFF_X / 2, ((BODY_DEPTH + MOUNT_DEPTH + MOUNT_HOLE_OFFSET_Y) / 2), (MOUNT_OFFSET_BOTTOM - MOUNT_HEIGHT) / 2);
        }
      }
    }
  }
}

module offset_motor_mg995_body(){
  translate([0, 0, BODY_DEPTH / -2]){
    motor_mg995_body();
  }
}

offset_motor_mg995_body();