include <thigh-config.scad>;
use <thigh-left.scad>;

module thigh_right(){
  /* Apply global properties */
  color(PRINT_COLOR){
    mirror([90, 0, 0]){
      offset_thigh_left();
    }
  }
}

module offset_thigh_right(){
  thigh_right();
}

offset_thigh_right();