$fn = 64;
CAMERA_WIDTH = 30.2;
CAMERA_DEPTH = 25.2;
CAMERA_PCB = 1;
CAMERA_HEIGHT = 6.9;
CAMERA_HOLE_DIAM = 2.8;
CAMERA_HOLE_X_DIST = 23.8;
CAMERA_MOUNT_HEIGHT = 4;
CAMERA_SCREW_DIAM = 1.8;

module camera_pcb(){
  translate([0, 0, (CAMERA_PCB + CAMERA_HEIGHT) / 2]){
    difference(){
      /* PCB + lens */
      union(){
        cube([CAMERA_WIDTH, CAMERA_DEPTH, CAMERA_PCB], true);
        translate([0, 0, CAMERA_HEIGHT / 2]){
          cube([CAMERA_WIDTH / 2, CAMERA_DEPTH / 2, CAMERA_HEIGHT], true);
        }
      }
      /* Top left screw hole */
      translate([-CAMERA_HOLE_X_DIST / 2, CAMERA_DEPTH / 2, 0]){
        cylinder(CAMERA_HEIGHT * 2, CAMERA_HOLE_DIAM / 2, CAMERA_HOLE_DIAM / 2, true);
      }
      /* Top right screw hole */
      translate([CAMERA_HOLE_X_DIST / 2, CAMERA_DEPTH / 2, 0]){
      cylinder(CAMERA_HEIGHT * 2, CAMERA_HOLE_DIAM / 2, CAMERA_HOLE_DIAM / 2, true);
      }
      /* Bottom left screw hole */
      translate([-CAMERA_HOLE_X_DIST / 2, -CAMERA_DEPTH / 2, 0]){
        cylinder(CAMERA_HEIGHT * 2, CAMERA_HOLE_DIAM / 2, CAMERA_HOLE_DIAM / 2, true);
      }
      /* Bottom right screw hole */
      translate([CAMERA_HOLE_X_DIST / 2, -CAMERA_DEPTH / 2, 0]){
        cylinder(CAMERA_HEIGHT * 2, CAMERA_HOLE_DIAM / 2, CAMERA_HOLE_DIAM / 2, true);
      }
    }
  }
}

camera_pcb();