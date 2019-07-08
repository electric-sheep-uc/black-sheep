include <fan-config.scad>

module fan(){
  difference(){
    /* Body */
    cube([FAN_WIDTH, FAN_DEPTH, FAN_HEIGHT], true);
    /* Top left screw hole */
    translate([-FAN_HOLE_X_DIST / 2, FAN_DEPTH / 2, FAN_HOLE_Z_DIST / 2]){
      rotate([90, 0, 0]){
        cylinder(FAN_DEPTH * 4, FAN_HOLE_FRONT_DIAM / 2, FAN_HOLE_FRONT_DIAM / 2, true);
        cylinder(FAN_DEPTH, FAN_HOLE_REAR_DIAM / 2, FAN_HOLE_REAR_DIAM / 2, true);
      }
    }
    /* Top right screw hole */
    translate([FAN_HOLE_X_DIST / 2, FAN_DEPTH / 2, FAN_HOLE_Z_DIST / 2]){
      rotate([90, 0, 0]){
        cylinder(FAN_DEPTH * 4, FAN_HOLE_FRONT_DIAM / 2, FAN_HOLE_FRONT_DIAM / 2, true);
        cylinder(FAN_DEPTH, FAN_HOLE_REAR_DIAM / 2, FAN_HOLE_REAR_DIAM / 2, true);
      }
    }
    /* Bottom left screw hole */
    translate([-FAN_HOLE_X_DIST / 2, FAN_DEPTH / 2, -FAN_HOLE_Z_DIST / 2]){
      rotate([90, 0, 0]){
        cylinder(FAN_DEPTH * 4, FAN_HOLE_FRONT_DIAM / 2, FAN_HOLE_FRONT_DIAM / 2, true);
        cylinder(FAN_DEPTH, FAN_HOLE_REAR_DIAM / 2, FAN_HOLE_REAR_DIAM / 2, true);
      }
    }
    /* Bottom right screw hole */
    translate([FAN_HOLE_X_DIST / 2, FAN_DEPTH / 2, -FAN_HOLE_Z_DIST / 2]){
      rotate([90, 0, 0]){
        cylinder(FAN_DEPTH * 4, FAN_HOLE_FRONT_DIAM / 2, FAN_HOLE_FRONT_DIAM / 2, true);
        cylinder(FAN_DEPTH, FAN_HOLE_REAR_DIAM / 2, FAN_HOLE_REAR_DIAM / 2, true);
      }
    }
  }
}

fan();