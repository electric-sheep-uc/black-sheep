include <torso-config.scad>
use <torso-panel-front-upper.scad>

module torso_panel_back_upper_fit(width, height, depth, thickness, hole_radius, edge_round, backoff){
  difference(){
    rotate([0, 0, 180]){
      torso_panel_front_upper(width, height, depth, thickness, hole_radius, backoff);
    }
  }
}

module offset_torso_panel_back_upper(){
  translate([0, 0, TORSO_WIDTH / 3]){
    torso_panel_back_upper_fit(TORSO_WIDTH, TORSO_HEIGHT, TORSO_DEPTH, THICKNESS, TORSO_HOLE_RADIUS, TORSO_ROUND, PANEL_BACKOFF);
  }
}

offset_torso_panel_back_upper();