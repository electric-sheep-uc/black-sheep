use <hip-lower-left.scad>;
use <hip-lower-right.scad>;
use <hip-upper-left.scad>;
use <hip-upper-right.scad>;

module hip_complete(){
  union(){
    offset_hip_lower_left();
    offset_hip_lower_right();
    offset_hip_upper_left();
    offset_hip_upper_right();
  }
}

module hip_rotate(){
  rotate([0, 0, $t * 360]){
    hip_complete();
  }
}

hip_rotate();