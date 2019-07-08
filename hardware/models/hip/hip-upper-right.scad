include <hip-config.scad>;
use <hip-upper-left.scad>;

module hip_upper_right(){
  /* Apply global properties */
  color(PRINT_COLOR){
    mirror([90, 0, 0]){
      offset_hip_upper_left();
    }
  }
}

module offset_hip_upper_right(){
  hip_upper_right();
}

offset_hip_upper_right();