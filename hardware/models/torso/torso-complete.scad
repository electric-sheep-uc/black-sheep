use <torso-upper.scad>
use <torso-lower.scad>
use <torso-panel-top.scad>
use <torso-panel-bottom.scad>
use <torso-panel-front-upper.scad>
use <torso-panel-front-lower.scad>
use <torso-panel-back-upper.scad>
use <torso-panel-back-lower.scad>
use <torso-panel-left-upper.scad>
use <torso-panel-left-lower.scad>
use <torso-panel-right-upper.scad>
use <torso-panel-right-lower.scad>

module torso_complete(){
  union(){
    offset_torso_upper();
    offset_torso_lower();
    offset_torso_panel_top();
    offset_torso_panel_bottom();
    offset_torso_panel_front_upper();
    offset_torso_panel_front_lower();
    offset_torso_panel_back_upper();
    offset_torso_panel_back_lower();
    offset_torso_panel_left_upper();
    offset_torso_panel_left_lower();
    offset_torso_panel_right_upper();
    offset_torso_panel_right_lower();
  }
}

module torso_rotate(){
  rotate([0, 0, $t * 360]){
    torso_complete();
  }
}

torso_rotate();