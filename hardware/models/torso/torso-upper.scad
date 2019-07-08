include <torso-config.scad>
use <fan-mount.scad>
use <../motor/motor-mg995-body-mount.scad>
use <../arm-parts/cageSide.scad>

module torso_upper_cage(width, height, depth, thickness, hole_radius, edge_round){
  difference(){
    union(){
      difference(){
        union(){
          minkowski(){
            cube([width - edge_round * 2, depth - edge_round * 2, height / 2], true);
            cylinder(1, center=true);
          }
        }
        /* Remove all but support beams */
        cube([width + (thickness * 4), depth - (thickness * 4), (height / 2) - (thickness * 4)], true);
        cube([width - (thickness * 4), depth + (thickness * 4), (height / 2) - (thickness * 4)], true);
        cube([width - (thickness * 4), depth - (thickness * 4), (height / 2) + (thickness * 4)], true);
      }
      /* Add straight supports */
      translate([0, (depth / 2) - (thickness + (edge_round / 2)), 0]){
        cube([thickness * 2, (thickness * 2) - edge_round, height / 2], true);
      }
      translate([0, -(depth / 2) + (thickness + (edge_round / 2)), 0]){
        cube([thickness * 2, (thickness * 2) - edge_round, height / 2], true);
      }
      /* Add diagonal supports front/back */
      translate([(width / 4) - (thickness / 2), (depth / 2) - thickness, 0]){
        rotate([0, -35, 0]){
          cube([thickness, thickness * 2, sqrt((pow(width / 2, 2) + pow(height, 2))) / 2], true);
        }
      }
      translate([-(width / 4) + (thickness / 2), (depth / 2) - thickness, 0]){
        rotate([0, 35, 0]){
          cube([thickness, thickness * 2, sqrt((pow(width / 2, 2) + pow(height, 2))) / 2], true);
        }
      }
      translate([(width / 4) - (thickness / 2), -(depth / 2) + thickness, 0]){
        rotate([0, -35, 0]){
          cube([thickness, thickness * 2, sqrt((pow(width / 2, 2) + pow(height, 2))) / 2], true);
        }
      }
      translate([-(width / 4) + (thickness / 2), -(depth / 2) + thickness, 0]){
        rotate([0, 35, 0]){
          cube([thickness, thickness * 2, sqrt((pow(width / 2, 2) + pow(height, 2))) / 2], true);
        }
      }
    }
    /* Remove inserts for panels */
    translate([width / 2, 0, 0]){
      cube([thickness, depth - (thickness * 1.5), (height / 2) - (thickness * 1.5)], true);
    }
    translate([-width / 2, 0, 0]){
      cube([thickness, depth - (thickness * 1.5), (height / 2) - (thickness * 1.5)], true);
    }
    translate([0, depth / 2, 0]){
      cube([width - (thickness * 1.5), thickness, (height / 2) - (thickness * 1.5)], true);
    }
    translate([0, -depth / 2, 0]){
      cube([width - (thickness * 1.5), thickness, (height / 2) - (thickness * 1.5)], true);
    }
    translate([0, 0, height / 4]){
      cube([width - (thickness * 1.5), depth - (thickness * 1.5), thickness], true);
    }
    /* Remove holes  */
    torso_holes(width, height, depth, thickness, hole_radius);
  }
}

module torso_holes(width, height, depth, thickness, hole_radius){
  /* Remove panel holes */
  num_holes = 3;
  for(i = [-num_holes / 2 : 1 : num_holes / 2]){
    /* x axis holes */
    translate([0, i * ((depth - thickness * 6) / num_holes), (height / 4) - (thickness * 1.25)]){
      rotate([0, 90, 0]){
        cylinder(width + thickness, hole_radius, hole_radius, true);
      }
    }
    translate([0, i * ((depth - thickness * 6) / num_holes), -(height / 4) + (thickness * 1.25)]){
      rotate([0, 90, 0]){
        cylinder(width + thickness, hole_radius, hole_radius, true);
      }
    }
    translate([0, (depth / 2) - (thickness * 1.25), i * (((height / 2) - thickness * 6) / num_holes)]){
      rotate([0, 90, 0]){
        cylinder(width + thickness, hole_radius, hole_radius, true);
      }
    }
    translate([0, -(depth / 2) + (thickness * 1.25), i * (((height / 2) - thickness * 6) / num_holes)]){
      rotate([0, 90, 0]){
        cylinder(width + thickness, hole_radius, hole_radius, true);
      }
    }
    /* y axis holes */
    translate([0, 0, i * ((height / 8) - thickness * 1.5)]){
      rotate([90, 0, 0]){
        cylinder(depth + thickness, hole_radius, hole_radius, true);
      }
      translate([(-width / 2) + (thickness * 1.25), 0, 0]){
        rotate([90, 0, 0]){
          cylinder(depth + thickness, hole_radius, hole_radius, true);
        }
      }
      translate([(width / 2) - (thickness * 1.25), 0, 0]){
        rotate([90, 0, 0]){
          cylinder(depth + thickness, hole_radius, hole_radius, true);
        }
      }
    }
    translate([i * ((width / 4) - thickness * 1.5), 0, (height / 4) - (thickness * 1.25)]){
      rotate([90, 0, 0]){
        cylinder(depth + thickness, hole_radius, hole_radius, true);
      }
    }
    translate([i * ((width / 4) - thickness * 1.5), 0, -(height / 4) + (thickness * 1.25)]){
      rotate([90, 0, 0]){
        cylinder(depth + thickness, hole_radius, hole_radius, true);
      }
    }
    /* z axis mount holes */
    translate([-(width / 2) + (thickness * 1.25), i * ((depth / 4) - thickness * 1.5), height / 4]){
      cylinder(thickness * 8, hole_radius, hole_radius, true);
    }
    translate([(width / 2) - (thickness * 1.25), i * ((depth / 4) - thickness * 1.5), height / 4]){
      cylinder(thickness * 8, hole_radius, hole_radius, true);
    }
    translate([i * ((width / 4) - thickness * 1.5), -(depth / 2) + (thickness * 1.25), height / 4]){
      cylinder(thickness * 8, hole_radius, hole_radius, true);
    }
    translate([i * ((width / 4) - thickness * 1.5), (depth / 2) - (thickness * 1.25), height / 4]){
      cylinder(thickness * 8, hole_radius, hole_radius, true);
    }
    /* inter-body connecting holes */
    translate([-(width / 2) + (thickness * 1.25), i * ((depth / 4) - thickness * 1.5), -height / 4]){
      cylinder(thickness * 8, hole_radius, hole_radius, true);
    }
    translate([(width / 2) - (thickness * 1.25), i * ((depth / 4) - thickness * 1.5), -height / 4]){
      cylinder(thickness * 8, hole_radius, hole_radius, true);
    }
  }
}

module torso_handle(width, height, depth, thickness, edge_round){
  translate([0, depth / 2 - (thickness + (edge_round / 4)), (height / 4) + (thickness / 2)]){
    difference(){
      cube([thickness * 2, (thickness * 2) - (edge_round / 2), thickness * 2], true);
      cube([thickness, (thickness * 3) - (edge_round / 2), thickness], true);
    }
  }
  translate([(-width / 3), depth / 2 - (thickness + (edge_round / 4)), (height / 4) + (thickness / 2)]){
    difference(){
      cube([thickness * 2, (thickness * 2) - (edge_round / 2), thickness * 2], true);
      cube([thickness, (thickness * 3) - (edge_round / 2), thickness], true);
    }
  }
  translate([(width / 3), depth / 2 - (thickness + (edge_round / 4)), (height / 4) + (thickness / 2)]){
    difference(){
      cube([thickness * 2, (thickness * 2) - (edge_round / 2), thickness * 2], true);
      cube([thickness, (thickness * 3) - (edge_round / 2), thickness], true);
    }
  }
}

module torso_upper(){
  /* Apply global properties */
  color(PRINT_COLOR){
    union(){
      difference(){
        torso_upper_cage(TORSO_WIDTH, TORSO_HEIGHT, TORSO_DEPTH, THICKNESS, TORSO_HOLE_RADIUS, TORSO_ROUND);
        translate([0, -TORSO_DEPTH / 2, TORSO_HEIGHT / 4]){
          rotate([15, 0, 0]){
            cube([TORSO_WIDTH * 2, TORSO_DEPTH, TORSO_HEIGHT / 8], true);
          }
        }
      }
      translate([0, -TORSO_DEPTH / 3.5, TORSO_HEIGHT / 4.7]){
        rotate([15, 0, 0]){
          difference(){
            cube([TORSO_WIDTH - THICKNESS, TORSO_DEPTH / 2.75, THICKNESS / 2], true);
            num_holes = 6;
            for(i = [-num_holes / 2 : 1 : num_holes / 2]){
              translate([THICKNESS * 3 * i, 0, 0]){
                cube([THICKNESS, TORSO_DEPTH / 4, THICKNESS], true);
              }
            }
          }
        }
      }
      torso_handle(TORSO_WIDTH, TORSO_HEIGHT, TORSO_DEPTH, THICKNESS, TORSO_ROUND);
      /* Arms */
      translate([-TORSO_WIDTH / 2.38, TORSO_DEPTH / 9, TORSO_HEIGHT / 8]){
        rotate([0, 0, 90]){
          cageSide(false, false);
        }
      }
      translate([TORSO_WIDTH / 2.38, TORSO_DEPTH / 9, TORSO_HEIGHT / 8]){
        rotate([0, 0, -90]){
          mirror([1, 0, 0]){
            cageSide(false, false);
          }
        }
      }
      /* Neck */
      translate([0, THICKNESS * 2.9, TORSO_HEIGHT / 6.2]){
        offset_motor_mg995_body_mount();
      }
    }
  }
}

module offset_torso_upper(){
  translate([0, 0, TORSO_WIDTH / 3]){
    torso_upper();
  }
}

offset_torso_upper();