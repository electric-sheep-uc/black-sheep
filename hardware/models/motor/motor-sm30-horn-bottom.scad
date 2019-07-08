include <motor-sm30-config.scad>;
use <motor-sm30-horn-top.scad>;

module offset_motor_sm30_horn_bottom(){
  mirror([0, 0, 180]){
    offset_motor_sm30_horn_top();
  }
}

offset_motor_sm30_horn_bottom();