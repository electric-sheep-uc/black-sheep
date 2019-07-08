use <shin-left.scad>;
use <shin-right.scad>;

module shin_complete(){
  union(){
    offset_shin_left();
    offset_shin_right();
  }
}

module shin_rotate(){
  rotate([0, 0, $t * 360]){
    shin_complete();
  }
}

shin_rotate();