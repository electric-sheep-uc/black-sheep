include <torso-config.scad>
use <torso-panel-left-upper.scad>

module torso_panel_right_upper_fit(width, height, depth, thickness, hole_radius, edge_round, backoff){
  mirror([1, 0, 0]){
    torso_panel_left_upper_fit(width, height, depth, thickness, hole_radius, edge_round, backoff);
  }
}

module offset_torso_panel_right_upper(){
  translate([0, 0, TORSO_WIDTH / 3]){
    torso_panel_right_upper_fit(TORSO_WIDTH, TORSO_HEIGHT, TORSO_DEPTH, THICKNESS, TORSO_HOLE_RADIUS, TORSO_ROUND, PANEL_BACKOFF);
  }
}

offset_torso_panel_right_upper();