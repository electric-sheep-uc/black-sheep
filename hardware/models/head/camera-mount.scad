include <camera-pcb.scad>;

module camera_mount(){
  translate([0, 0, CAMERA_MOUNT_HEIGHT]){
    difference(){
      union(){
       /* Top left screw mount */
        translate([-CAMERA_HOLE_X_DIST / 2, CAMERA_DEPTH / 2, -(CAMERA_MOUNT_HEIGHT + CAMERA_PCB) / 2]){
          cylinder(CAMERA_MOUNT_HEIGHT, CAMERA_HOLE_DIAM, CAMERA_HOLE_DIAM, true);
        }
        /* Top right screw mount */
        translate([CAMERA_HOLE_X_DIST / 2, CAMERA_DEPTH / 2, -(CAMERA_MOUNT_HEIGHT + CAMERA_PCB) / 2]){
          cylinder(CAMERA_MOUNT_HEIGHT, CAMERA_HOLE_DIAM, CAMERA_HOLE_DIAM, true);
        }
        /* Bottom left screw mount */
        translate([-CAMERA_HOLE_X_DIST / 2, -CAMERA_DEPTH / 2, -(CAMERA_MOUNT_HEIGHT + CAMERA_PCB) / 2]){
          cylinder(CAMERA_MOUNT_HEIGHT, CAMERA_HOLE_DIAM, CAMERA_HOLE_DIAM, true);
        }
        /* Bottom right screw mount */
        translate([CAMERA_HOLE_X_DIST / 2, -CAMERA_DEPTH / 2, -(CAMERA_MOUNT_HEIGHT + CAMERA_PCB) / 2]){
          cylinder(CAMERA_MOUNT_HEIGHT, CAMERA_HOLE_DIAM, CAMERA_HOLE_DIAM, true);
        }
      }
      /* Top left screw hole */
      translate([-CAMERA_HOLE_X_DIST / 2, CAMERA_DEPTH / 2, 0]){
        cylinder(CAMERA_HEIGHT * 2, CAMERA_SCREW_DIAM / 2, CAMERA_SCREW_DIAM / 2, true);
      }
      /* Top right screw hole */
      translate([CAMERA_HOLE_X_DIST / 2, CAMERA_DEPTH / 2, 0]){
      cylinder(CAMERA_HEIGHT * 2, CAMERA_SCREW_DIAM / 2, CAMERA_SCREW_DIAM / 2, true);
      }
      /* Bottom left screw hole */
      translate([-CAMERA_HOLE_X_DIST / 2, -CAMERA_DEPTH / 2, 0]){
        cylinder(CAMERA_HEIGHT * 2, CAMERA_SCREW_DIAM / 2, CAMERA_SCREW_DIAM / 2, true);
      }
      /* Bottom right screw hole */
      translate([CAMERA_HOLE_X_DIST / 2, -CAMERA_DEPTH / 2, 0]){
        cylinder(CAMERA_HEIGHT * 2, CAMERA_SCREW_DIAM / 2, CAMERA_SCREW_DIAM / 2, true);
      }
    }
  }
}

camera_mount();