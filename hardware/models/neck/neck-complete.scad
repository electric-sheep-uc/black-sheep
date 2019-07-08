use <neck.scad>

module neck_complete(){
  offset_neck();
}

module neck_rotate(){
  rotate([0, 0, $t * 360]){
    neck_complete();
  }
}

neck_rotate();
