include <torso-config.scad>
include <../foot/foot-config.scad>;
include <../motor/motor-sm30-config.scad>;
use <../motor/motor-sm30-body-mount.scad>

module torso_tray_body(width, height, depth, thickness, body_thickness, hole_radius){
  difference(){
    cube([(width / 2) - (body_thickness * 2), depth - (body_thickness * 3), hole_radius * 5], true);
    translate([0, 0, thickness]){
      cube([(width / 2) - (body_thickness * 2) - (thickness * 2), depth * 2, (hole_radius * 5) - thickness], true);
    }
    /* Reduce print volume */
    for(y = [-3:1:3]){
      for(x = [-3:1:3]){
        translate([(x * width) / 16, (y * depth) / 8, 0]){
          cube([(width / 32), depth / 16, depth], true);
        }
      }
    }
    /* Insert wire holes */
    for(y = [-1:1:1]){
      for(x = [-1:1:1]){
        translate([(x * width) / 8, (y * depth) / 4, 0]){
          cube([(width / 16), depth / 8, depth], true);
        }
      }
    }
  }
}

module torso_holes(width, height, depth, hole_radius){
  translate([0, -depth / 3, 0]){
    rotate([0, 90, 0]){
      cylinder(width * 2, hole_radius, hole_radius, true);
    }
  }
  translate([0, depth / 3, 0]){
    rotate([0, 90, 0]){
      cylinder(width * 2, hole_radius, hole_radius, true);
    }
  }
}

module torso_tray(){
  /* Apply global properties */
  color(PRINT_COLOR){
    union(){
      difference(){
        torso_tray_body(TORSO_WIDTH, TORSO_HEIGHT, TORSO_DEPTH, TRAY_THICKNESS, THICKNESS, TORSO_HOLE_RADIUS);
        torso_holes(TORSO_WIDTH, TORSO_HEIGHT, TORSO_DEPTH, TORSO_HOLE_RADIUS);
      }
    }
  }
}

module offset_torso_tray(){
  translate([0, 0, 0]){
    torso_tray();
  }
}

offset_torso_tray();