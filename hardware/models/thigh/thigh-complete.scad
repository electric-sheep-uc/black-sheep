use <thigh-left.scad>;
use <thigh-right.scad>;

module thigh_complete(){
  union(){
    offset_thigh_left();
    offset_thigh_right();
  }
}

module thigh_rotate(){
  rotate([0, 0, $t * 360]){
    thigh_complete();
  }
}

thigh_rotate();