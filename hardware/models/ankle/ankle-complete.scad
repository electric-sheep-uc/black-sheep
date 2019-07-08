use <ankle-left.scad>;
use <ankle-right.scad>;

module ankle_complete(){
  union(){
    offset_ankle_left();
    offset_ankle_right();
  }
}

module ankle_rotate(){
  rotate([0, 0, $t * 360]){
    ankle_complete();
  }
}

ankle_rotate();