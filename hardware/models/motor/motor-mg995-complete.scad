use <motor-mg995-body.scad>
use <motor-mg995-horn.scad>
use <motor-mg995-body-mount.scad>
use <motor-mg995-horn-mount.scad>

module motor_mg995_complete(){
  union(){
    offset_motor_mg995_body();
    offset_motor_mg995_horn();
    offset_motor_mg995_body_mount();
    offset_motor_mg995_horn_mount();
  }
}

module motor_mg995_rotate(){
  rotate([0, 0, $t * 360]){
    motor_mg995_complete();
  }
}

motor_mg995_rotate();
