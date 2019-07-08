use <motor-sm30-body.scad>;
use <motor-sm30-horn-top.scad>;
use <motor-sm30-horn-bottom.scad>;
use <motor-sm30-body-mount.scad>;
use <motor-sm30-horn-mount.scad>;

module motor_sm30_complete(){
  union(){
    offset_motor_sm30_body();
    offset_motor_sm30_horn_top();
    offset_motor_sm30_horn_bottom();
    offset_motor_sm30_body_mount();
    offset_motor_sm30_horn_mount();
  }
}

module motor_sm30_rotate(){
  rotate([0, 0, $t * 360]){
    motor_sm30_complete();
  }
}

motor_sm30_rotate();