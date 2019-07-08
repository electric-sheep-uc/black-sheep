include <ankle-config.scad>;
use <ankle-left.scad>;

module ankle_right(){
  /* Apply global properties */
  color(PRINT_COLOR){
    mirror([90, 0, 0]){
      offset_ankle_left();
    }
  }
}

module offset_ankle_right(){
  ankle_right();
}

offset_ankle_right();