include <torso-config.scad>
use <torso-upper.scad>

module torso_panel_front_upper(width, height, depth, thickness, hole_radius, backoff){
  difference(){
    translate([0, -depth / 2, 0]){
      cube([(width - backoff) - (thickness * 1.5), thickness / 4, ((height - backoff) / 2) - (thickness * 1.5)], true);
    }
    torso_holes(width, height, depth, thickness, hole_radius);
    num_ver = 3;
    num_hor = 5;
    translate([0, -depth / 2, 0]){
      for(y = [-num_ver/ 2 : 1 : num_ver / 2]){
        for(x = [-num_hor / 2 : 1 : num_hor / 2]){
          if(x != 0){
            translate([x * (width / (num_hor + 2)), 0, y * (height / (2 * (num_ver + 2)))]){
              rotate([90, 0, 0]){
                cylinder(10, hole_radius, hole_radius, true);
              }
            }
          }
        }
      }
    }
  }
}

module torso_panel_front_upper_fit(width, height, depth, thickness, hole_radius, edge_round, backoff){
  difference(){
    torso_panel_front_upper(width, height, depth, thickness, hole_radius, backoff);
    translate([0, -depth / 2, 45]){
      cube([160, 10, 15], true);
    }
  }
}

module offset_torso_panel_front_upper(){
  translate([0, 0, TORSO_WIDTH / 3]){
    torso_panel_front_upper_fit(TORSO_WIDTH, TORSO_HEIGHT, TORSO_DEPTH, THICKNESS, TORSO_HOLE_RADIUS, TORSO_ROUND, PANEL_BACKOFF);
  }
}

offset_torso_panel_front_upper();