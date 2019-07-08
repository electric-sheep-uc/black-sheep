include <neck-config.scad>

include <../motor/motor-mg995-config.scad>
use <../motor/motor-mg995-horn-mount.scad>

module neck_rafts(){
  raft_height = 16;
  raft_width = 1;
  raft_depth = raft_height;
  raft_spacing = 7;
  translate([-raft_depth / 2, 0, (-(HORN_DIAM / 4) * 2.25) +(raft_height / 2)]){
    rotate([0, 0, -90]){
      for(i = [-1.5 : 1 : 1.5]){
        translate([i * raft_spacing, 0, 0]){
          difference(){
            cube([raft_width, raft_depth, raft_height], true);
            translate([0, -sqrt(raft_depth), sqrt(raft_height)]){
              rotate([-45, 0, 0]){
                cube([raft_width * 2, raft_depth, raft_height * 2], true);
              }
            }
          }
        }
      }
    }
  }
}

module neck(){
  /* Apply global properties */
  color(PRINT_COLOR){
    union(){
      translate([(-(HORN_DIAM / 4) * 5) + (HORN_HEIGHT / 1.3), 0, -(HORN_DIAM / 4) * 2.5]){
        motor_mg995_horn_mount();
      }
      translate([-HORN_HEIGHT * 2.5, 0, -(HORN_DIAM / 4) * 2.5]){
          cube([(HORN_DIAM / 1.8) + HORN_HEIGHT, HORN_DIAM * 1.25, HORN_HEIGHT * 1.5], true);
      }
      translate([0, 0, HORN_DIAM * 1.4]){
        rotate([0, 90, 0]){
          motor_mg995_horn_mount();
        }
      }
      translate([0, 0, HORN_HEIGHT * 0.5]){
        rotate([0, 90, 180]){
          cube([HORN_DIAM * 1.5, HORN_DIAM * 1.25, HORN_HEIGHT * 1.5], true);
        }
      }
      neck_rafts();
    }
  }
}

module offset_neck(){
  neck();
}

offset_neck();