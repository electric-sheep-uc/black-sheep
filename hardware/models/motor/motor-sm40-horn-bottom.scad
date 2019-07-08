include <motor-sm40-config.scad>;
use <motor-sm40-horn-top.scad>;

module offset_motor_sm40_horn_bottom(){
  mirror([0, 0, 180]){
    offset_motor_sm40_horn_top();
  }
}

offset_motor_sm40_horn_bottom();