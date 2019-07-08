include <motor-mg995-config.scad>
use <motor-mg995-body.scad>

module external_body_mounts(mount_width, mount_height, mount_depth, mount_offset, mount_hole_offset_y){
  /* North mount */
  translate([mount_height / 2, mount_hole_offset_y + (mount_height / 1.8), mount_offset]){
    difference(){
      cube([mount_width + mount_height, mount_depth + mount_height, mount_height * 3], true);
      translate([0, -mount_height / 2, 0]){
        cube([mount_width * 2, mount_depth * 1.2, mount_height * 1.2], true);
      }
    }
  }
  /* South mount */
  translate([mount_height / 2, -mount_hole_offset_y + (-mount_height / 1.8), mount_offset]){
    difference(){
      cube([mount_width + mount_height, mount_depth + mount_height, mount_height * 3], true);
      translate([0, mount_height / 2, 0]){
        cube([mount_width * 2, mount_depth * 1.2, mount_height * 1.2], true);
      }
    }
  }
  translate([(mount_width + (mount_height * 1.2)) / 2, 0, mount_offset]){
    cube([mount_height, BODY_DEPTH + (mount_depth * 3), mount_height * 3], true);
  }
}

module external_body_mount_holes(screw_height, screw_radius, screw_offset_x, screw_offset_y, mount_offset){
  /* North mount left */
  translate([-screw_offset_x, screw_offset_y, mount_offset]){
    cylinder(screw_height * 8, screw_radius, screw_radius, true);
  }
  /* North mount right */
  translate([screw_offset_x, screw_offset_y, mount_offset]){
    cylinder(screw_height * 8, screw_radius, screw_radius, true);
  }
  /* South mount left */
  translate([-screw_offset_x, -screw_offset_y, mount_offset]){
    cylinder(screw_height * 8, screw_radius, screw_radius, true);
  }
  /* South mount right */
  translate([screw_offset_x, -screw_offset_y, mount_offset]){
    cylinder(screw_height * 8, screw_radius, screw_radius, true);
  }
}

module motor_mg995_body_mount(){
  /* Apply global properties */
  color(PRINT_COLOR){
    translate([0, 0, BODY_DEPTH / 2]){
      union(){
        difference(){
          external_body_mounts(BODY_WIDTH, MOUNT_HEIGHT, MOUNT_DEPTH, (MOUNT_OFFSET_BOTTOM - MOUNT_HEIGHT) / 2, (MOUNT_DEPTH + BODY_DEPTH) / 2);
          external_body_mount_holes(MOUNT_HEIGHT, MOUNT_SCREW_DIAM / 2, MOUNT_HOLE_DIFF_X / 2, ((BODY_DEPTH + MOUNT_DEPTH + MOUNT_HOLE_OFFSET_Y) / 2), (MOUNT_OFFSET_BOTTOM - MOUNT_HEIGHT) / 2);
        }
      }
    }
  }
}

module offset_motor_mg995_body_mount(){
  translate([0, 0, BODY_DEPTH / -2]){
    motor_mg995_body_mount();
  }
}

#offset_motor_mg995_body();
offset_motor_mg995_body_mount();