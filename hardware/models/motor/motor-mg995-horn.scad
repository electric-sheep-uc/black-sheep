include <motor-mg995-config.scad>

module horn(horn_radius, horn_height, horn_height_whole, horn_screw_mount_radius){
  cylinder(horn_height, horn_radius, horn_radius, true);
  translate([0, 0, -(horn_height_whole) / 2]){
    cylinder(horn_height_whole - horn_height, horn_screw_mount_radius, horn_screw_mount_radius, true);
  }
}

module horn_holes(screw_radius, screw_offset, horn_height){
  /* North screw hole */
  translate([0, screw_offset, 0]){
    cylinder(horn_height * 1.01, screw_radius, screw_radius, true);
  }
  /* East screw hole */
  translate([screw_offset, 0, 0]){
    cylinder(horn_height * 1.01, screw_radius, screw_radius, true);
  }
  /* South screw hole */
  translate([0, -screw_offset, 0]){
    cylinder(horn_height * 1.01, screw_radius, screw_radius, true);
  }
  /* West screw hole */
  translate([-screw_offset, 0, 0]){
    cylinder(horn_height * 1.01, screw_radius, screw_radius, true);
  }
  /* Center screw hole */
  translate([0, 0, 0]){
    cylinder(horn_height * 8, screw_radius, screw_radius, true);
  }
}

module motor_mg995_horn(){
  /* Apply global properties */
  color(PRINT_COLOR){
    translate([0, 0, HORN_HEIGHT / 2]){
      difference(){
        horn(HORN_DIAM / 2, HORN_HEIGHT, HORN_HEIGHT_WHOLE, HORN_SCREW_MOUNT_DIAM / 2);
        horn_holes(HORN_SCREW_HOLE_DIAM / 2, HORN_SCREW_OFFSET, HORN_HEIGHT);
      }
    }
  }
}

module offset_motor_mg995_horn(){
  translate([0, HORN_DEPTH_OFFSET, (BODY_HEIGHT + HORN_HEIGHT + HORN_HEIGHT_OFFSET) / 2]){
    motor_mg995_horn();
  }
}

offset_motor_mg995_horn();
