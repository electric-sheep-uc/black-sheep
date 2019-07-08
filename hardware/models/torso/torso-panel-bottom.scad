include <torso-config.scad>
use <torso-panel-top.scad>


module torso_panel_bottom_fit(width, height, depth, thickness, hole_radius, edge_round, backoff){
  difference(){
    torso_panel_top(width, height, depth, thickness, hole_radius, backoff);
    translate([-45, 0, height / 4]){
      cube([55, 120, 10], true);
    }
    translate([45, 0, height / 4]){
      cube([55, 120, 10], true);
    }
  }
}

module offset_torso_panel_bottom(){
  translate([0, 0, -TORSO_WIDTH / 3]){
    rotate([0, 180, 0]){
      torso_panel_bottom_fit(TORSO_WIDTH, TORSO_HEIGHT, TORSO_DEPTH, THICKNESS, TORSO_HOLE_RADIUS, TORSO_ROUND, PANEL_BACKOFF);
    }
  }
}

offset_torso_panel_bottom();