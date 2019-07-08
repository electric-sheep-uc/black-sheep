use <motor-sm40-body.scad>;
use <motor-sm40-horn-top.scad>;
use <motor-sm40-horn-bottom.scad>;
use <motor-sm40-body-mount.scad>;
use <motor-sm40-horn-mount.scad>;

module motor_sm40_complete(){
  union(){
    offset_motor_sm40_body();
    offset_motor_sm40_horn_top();
    offset_motor_sm40_horn_bottom();
    offset_motor_sm40_body_mount();
    offset_motor_sm40_horn_mount();
  }
}

module motor_sm40_rotate(){
  rotate([0, 0, $t * 360]){
    motor_sm40_complete();
  }
}

motor_sm40_rotate();