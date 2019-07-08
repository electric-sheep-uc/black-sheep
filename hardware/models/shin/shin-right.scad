include <shin-config.scad>;
use <shin-left.scad>;

module shin_right(){
  /* Apply global properties */
  color(PRINT_COLOR){
    mirror([90, 0, 0]){
      offset_shin_left();
    }
  }
}

module offset_shin_right(){
  shin_right();
}

offset_shin_right();