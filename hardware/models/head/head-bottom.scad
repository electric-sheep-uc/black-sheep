include <head-config.scad>

include <../motor/motor-mg995-config.scad>
use <../motor/motor-mg995-body.scad>
use <../motor/motor-mg995-body-mount.scad>
use <camera-mount.scad>

module head_camera_mount(head_size, thickness, eye_size){
  union(){
    translate([0, -head_size * 0.75, 0]){
      rotate([90, 0, 0]){
        translate([0, 0, -thickness / 2]){
          difference(){
            union(){
              cylinder(thickness, eye_size * 1.75, eye_size * 1.75, true);
            }
            translate([0, eye_size, 0]){
              cube([eye_size * 4, eye_size * 2, thickness * 4], true);
            }
          }
          cube([eye_size * 1.8, eye_size * 1.8, thickness], true);
        }
        camera_mount();
      }
    }
  }
}

module head_to_head_holes(head_radius, mount_size, screw_size){
  /* Right side screw hole */
  translate([head_radius - (mount_size * 0.25), 0, -(head_radius * 0.5) + (mount_size * 0.5)]){
    cylinder(head_radius, screw_size, screw_size, true);
  }
  /* Left side screw hole */
  translate([-head_radius + (mount_size * 0.25), 0, -(head_radius * 0.5) + (mount_size * 0.5)]){
    cylinder(head_radius, screw_size, screw_size, true);
  }
}

module head_bottom(){
  /* Apply global properties */
  color(PRINT_COLOR){
    rotate([0, 180, 0]){
      /* Make space for motor */
      difference(){
        /* Add the horn mount */
        union(){
          /* Make other half of head face other way */
          rotate([0, 180, 0]){
            difference(){
              union(){
                difference(){
                  head_base(HEAD_SIZE, 0.50, THICKNESS);
                  eye_socket(HEAD_SIZE, EYE_SIZE);
                  cable_socket(HEAD_SIZE, CABLE_SIZE);
                }
                head_to_head_mounts(HEAD_SIZE, MOUNT_SIZE);
              }
              head_to_head_holes(HEAD_SIZE, MOUNT_SIZE, SCREW_SIZE);
            }
          }
        }
        /* Cut out hole for motor to slide into */
        union(){
          scale([1.5, 1.5, 1.2]){
            translate([BODY_WIDTH / 1.5, 0, -HEAD_SIZE * 0.5]){
              rotate([0, 180, 0]){
                offset_motor_mg995_body();
                translate([-10, 0, 0]){
                  cube([35, 39.5, 15], true);
                }
              }
            }
          }
        }
      }
      translate([0, 0, -HEAD_SIZE * 0.5]){
        rotate([0, 90, 0]){
          offset_motor_mg995_body_mount();
          translate([-2.5, -BODY_DEPTH / 1.25, BODY_HEIGHT / 3]){
            cube([15, 10, 10], true);
          }
          translate([2.5, BODY_DEPTH / 1.25, BODY_HEIGHT / 3]){
            cube([10, 10, 10], true);
          }
        }
      }
      head_camera_mount(HEAD_SIZE, THICKNESS, EYE_SIZE);
    }
  }
}

module offset_head_bottom(){
  rotate([0, 180, 0]){
    head_bottom();
  }
}

offset_head_bottom();
