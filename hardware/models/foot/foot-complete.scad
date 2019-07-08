use <foot-left.scad>;
use <foot-right.scad>;

module foot_complete(){
  union(){
    offset_foot_left();
    offset_foot_right();
  }
}

module foot_rotate(){
  rotate([0, 0, $t * 360]){
    foot_complete();
  }
}

foot_rotate();