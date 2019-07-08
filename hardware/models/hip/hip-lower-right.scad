include <hip-config.scad>;
use <hip-lower-left.scad>;

module hip_lower_right(){
  /* Apply global properties */
  color(PRINT_COLOR){
    mirror([90, 0, 0]){
      offset_hip_lower_left();
    }
  }
}

module offset_hip_lower_right(){
  hip_lower_right();
}

offset_hip_lower_right();