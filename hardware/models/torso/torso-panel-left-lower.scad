include <torso-config.scad>
use <torso-panel-left-upper.scad>

module torso_panel_left_lower_fit(width, height, depth, thickness, hole_radius, edge_round, backoff){
  difference(){
    translate([0, 0, -height / 2]){
      torso_panel_left_upper(width, height, depth, thickness, hole_radius, backoff);
    }
    translate([0, 0, 30]){
      cube([160, 120, 60], true);
    }
  }
}

module offset_torso_panel_left_lower(){
  translate([0, 0, TORSO_WIDTH / 3]){
    torso_panel_left_lower_fit(TORSO_WIDTH, TORSO_HEIGHT, TORSO_DEPTH, THICKNESS, TORSO_HOLE_RADIUS, TORSO_ROUND, PANEL_BACKOFF);
  }
}

offset_torso_panel_left_lower();