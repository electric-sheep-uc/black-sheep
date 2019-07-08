include <torso-config.scad>
include <../foot/foot-config.scad>;
include <../motor/motor-sm30-config.scad>;
use <battery.scad>
use <torso-upper.scad>
use <../motor/motor-sm30-body-mount.scad>

module torso_lower_cage(width, height, depth, thickness, hole_radius, edge_round){
  rotate([0, 180, 0]){
    torso_upper_cage(width, height, depth, thickness, hole_radius, edge_round);
  }
}

module torso_lower(){
  /* Apply global properties */
  color(PRINT_COLOR){
    union(){
      difference(){
        union(){
          torso_lower_cage(TORSO_WIDTH, TORSO_HEIGHT, TORSO_DEPTH, THICKNESS, TORSO_HOLE_RADIUS, TORSO_ROUND);
          /* Battery enclosure */
          rotate([0, 0, 90]){
            scale([1.25, 1, 1.25]){
              battery();
            }
          }
          translate([0, TORSO_DEPTH / 8, 0]){
            cube([THICKNESS, THICKNESS * 12, THICKNESS * 10], true);
          }
        }
        /* Create void for battery insertion */
        translate([0, 0, 0]){
          rotate([0, 0, 90]){
            scale([1.15, 1.5, 1.15]){
              battery();
            }
          }
          /* Make way for battery terminals */
          translate([-TORSO_WIDTH / 4, 0, -THICKNESS * 2]){
            cube([THICKNESS * 5, TORSO_DEPTH / 2, THICKNESS * 4], true);
          }
          translate([TORSO_WIDTH / 4, 0, -THICKNESS * 2]){
            cube([THICKNESS * 5, TORSO_DEPTH / 2, THICKNESS * 4], true);
          }
        }
      }
      translate([-TORSO_WIDTH / 3.3, TORSO_DEPTH / 3.75, -TORSO_HEIGHT / 3.75]){
        rotate([90, 180, 90]){
          offset_motor_sm30_body_mount();
        }
      }
      translate([TORSO_WIDTH / 3.3, TORSO_DEPTH / 3.75, -TORSO_HEIGHT / 3.75]){
        rotate([90, 180, 90]){
          offset_motor_sm30_body_mount();
        }
      }
    }
  }
}

module offset_torso_lower(){
  translate([0, 0, -TORSO_WIDTH / 3]){
    torso_lower();
  }
}

offset_torso_lower();