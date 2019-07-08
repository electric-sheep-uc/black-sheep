include <torso-config.scad>
use <torso-upper.scad>

module torso_panel_left_upper(width, height, depth, thickness, hole_radius, backoff){
  difference(){
    translate([width / 2, 0, 0]){
      cube([thickness / 4, (depth - backoff) - (thickness * 1.5), ((height - backoff) / 2) - (thickness * 1.5)], true);
    }
    torso_holes(width, height, depth, thickness, hole_radius);
  }
}

module torso_panel_left_upper_fit(width, height, depth, thickness, hole_radius, edge_round, backoff){
  difference(){
    torso_panel_left_upper(width, height, depth, thickness, hole_radius, backoff);
    translate([0, 0, 30]){
      cube([160, 120, 60], true);
    }
  }
}

module offset_torso_panel_left_upper(){
  translate([0, 0, TORSO_WIDTH / 3]){
    torso_panel_left_upper_fit(TORSO_WIDTH, TORSO_HEIGHT, TORSO_DEPTH, THICKNESS, TORSO_HOLE_RADIUS, TORSO_ROUND, PANEL_BACKOFF);
  }
}

offset_torso_panel_left_upper();