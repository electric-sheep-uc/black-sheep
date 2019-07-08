use <head-top.scad>
use <head-bottom.scad>

module head_complete(){
  union(){
    offset_head_top();
    offset_head_bottom();
  }
}

module head_rotate(){
  rotate([0, 0, $t * 360]){
    head_complete();
  }
}

head_rotate();
