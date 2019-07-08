include <head-config.scad>

module ears(head_radius, ear_size, ear_radius, ear_angle, thickness){
  d = head_radius - (head_radius / ear_radius);
  /* Right ear */
  translate([d * sin(ear_angle), 0, d * cos(ear_angle)]){
    rotate([0, ear_angle, 0]){
      difference(){
        cylinder(ear_size, ear_radius, 2, false);
        cylinder(ear_size - thickness, ear_radius - thickness, 2, false);
      }
    }
  }
  /* Left ear */
  translate([d * sin(-ear_angle), 0, d * cos(-ear_angle)]){
    rotate([0, -ear_angle, 0]){
      difference(){
        cylinder(ear_size, ear_radius, 2, false);
        cylinder(ear_size - thickness, ear_radius - thickness,2, false);
      }
    }
  }
}

module head_to_head_holes(head_radius, mount_size, screw_size, pilot_size){
  /* Right side screw hole */
  translate([head_radius - (mount_size * 0.25), 0, mount_size * 0.5]){
    cylinder(head_radius, screw_size, screw_size, true);
  }
  /* Right side pilot hole */
  translate([head_radius - (mount_size * 0.25), 0, (head_radius * 0.5) - mount_size * 0.75]){
    cylinder(head_radius * 0.5, pilot_size, pilot_size, true);
  }
  /* Left side screw hole */
  translate([-head_radius + (mount_size * 0.25), 0, mount_size * 0.5]){
    cylinder(head_radius, screw_size, screw_size, true);
  }
  /* Left side pilot hole */
  translate([-head_radius + (mount_size * 0.25), 0, (head_radius * 0.5) - mount_size * 0.75]){
    cylinder(head_radius * 0.5, pilot_size, pilot_size, true);
  }
}

module head_top(){
  /* Apply global properties */
  color(PRINT_COLOR){
    difference(){
      union(){
        difference(){
          head_base(HEAD_SIZE, 0.5, THICKNESS);
          eye_socket(HEAD_SIZE, EYE_SIZE);
        }
        ears(HEAD_SIZE, EAR_SIZE, EAR_RADIUS, EAR_ANGLE, THICKNESS);
        head_to_head_mounts(HEAD_SIZE, MOUNT_SIZE);
      }
      head_to_head_holes(HEAD_SIZE, MOUNT_SIZE, SCREW_SIZE, PILOT_SIZE);
    }
  }
}

module offset_head_top(){
  head_top();
}

offset_head_top();
