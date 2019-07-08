include <foot-config.scad>;
include <../motor/motor-sm30-config.scad>;
use <../motor/motor-sm30-body.scad>;
use <../motor/motor-sm30-horn-top.scad>;
use <../motor/motor-sm30-horn-bottom.scad>;
use <../motor/motor-sm30-horn-mount.scad>;

module foot_base(foot_width, foot_depth, foot_base){
  translate([0, 0, 0]){
    cube([foot_width, foot_depth, foot_base], true);
  }
}

module foot_motor_mount(foot_depth, foot_base, horn_diam, body_depth, horn_diam){
  outer_mount_scale = (1 / 2) * 1.5;
  clear_scale = 1.75;
  translate([0, -10, (body_depth / 2) + (horn_diam * outer_mount_scale * clear_scale / 2) + (foot_base / 2)]){
    rotate([-90, 0, 90]){
      offset_motor_sm30_horn_mount();
    }
  }
}

module foot_studs(foot_width, foot_depth, foot_base, stud_height, stud_radius){
  /* Front left */
  translate([-foot_width / 3, -foot_depth / 2.5, -stud_height / 2]){
    cylinder(stud_height, stud_radius / 1.5, stud_radius, true);
  }
  /* Front right */
  translate([foot_width / 3, -foot_depth / 2.5, -stud_height / 2]){
    cylinder(stud_height, stud_radius / 1.5, stud_radius, true);
  }
  /* Rear left */
  translate([-foot_width / 3, foot_depth / 2.5, -stud_height / 2]){
    cylinder(stud_height, stud_radius / 1.5, stud_radius, true);
  }
  /* Rear right */
  translate([foot_width / 3, foot_depth / 2.5, -stud_height / 2]){
    cylinder(stud_height, stud_radius / 1.5, stud_radius, true);
  }
}


module foot_left(){
  /* Apply global properties */
  color(PRINT_COLOR){
    translate([FOOT_SPACE, 0, 0]){
      foot_base(FOOT_WIDTH, FOOT_DEPTH, FOOT_BASE);
      foot_motor_mount(FOOT_DEPTH, FOOT_BASE, HORN_DIAM, BODY_DEPTH, HORN_DIAM);
      foot_studs(FOOT_WIDTH, FOOT_DEPTH, FOOT_BASE, FOOT_STUD_HEIGHT, FOOT_STUD_RADIUS);
    }
  }
}

module offset_foot_left(){
  foot_left();
}

offset_foot_left();