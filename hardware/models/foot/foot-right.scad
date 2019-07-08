include <foot-config.scad>;
use <foot-left.scad>;

module foot_right(){
  /* Apply global properties */
  color(PRINT_COLOR){
    mirror([90, 0, 0]){
      offset_foot_left();
    }
  }
}

module offset_foot_right(){
  foot_right();
}

offset_foot_right();