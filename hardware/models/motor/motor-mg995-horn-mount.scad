include <motor-mg995-config.scad>

module external_horn(horn_radius, horn_height, horn_height_whole, horn_screw_mount_radius){
  difference(){
    cube([horn_radius * 2.5, horn_radius * 2.5, horn_height * 2], true);
    translate([0, 0, -horn_height / 1.99]){
      cylinder(horn_height, horn_radius * 1.05, horn_radius * 1.05, true);
    }
  }
}

module external_horn_holes(screw_radius, screw_offset, horn_height){
    /* North screw hole */
  translate([0, screw_offset, 0]){
    cylinder(horn_height * 4, screw_radius, screw_radius, true);
  }
  /* East screw hole */
  translate([screw_offset, 0, 0]){
    cylinder(horn_height * 4, screw_radius, screw_radius, true);
  }
  /* South screw hole */
  translate([0, -screw_offset, 0]){
    cylinder(horn_height * 4, screw_radius, screw_radius, true);
  }
  /* West screw hole */
  translate([-screw_offset, 0, 0]){
    cylinder(horn_height * 4, screw_radius, screw_radius, true);
  }
  /* Center screw hole */
  translate([0, 0, 0]){
    cylinder(horn_height * 8, screw_radius * 1.2, screw_radius * 1.2, true);
  }
}

module motor_mg995_horn_mount(){
  /* Apply global properties */
  color(PRINT_COLOR){
    translate([0, 0, HORN_HEIGHT / 4]){
      difference(){
        external_horn(HORN_DIAM / 2, HORN_HEIGHT, HORN_HEIGHT_WHOLE, HORN_SCREW_MOUNT_DIAM / 2);
        external_horn_holes(HORN_SCREW_HOLE_DIAM / 2, HORN_SCREW_OFFSET, HORN_HEIGHT);
      }
    }
  }
}

module offset_motor_mg995_horn_mount(){
  translate([0, HORN_DEPTH_OFFSET, (BODY_HEIGHT + HORN_HEIGHT + HORN_HEIGHT_OFFSET) / 2]){
    motor_mg995_horn_mount();
  }
}

offset_motor_mg995_horn_mount();
