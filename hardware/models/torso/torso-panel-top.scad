include <torso-config.scad>
use <torso-upper.scad>

module torso_panel_top(width, height, depth, thickness, hole_radius, backoff){
  difference(){
    translate([0, 0, height / 4]){
      cube([(width - backoff) - (thickness * 1.5), (depth - backoff) - (thickness * 1.5), thickness / 4], true);
    }
    torso_holes(width, height, depth, thickness, hole_radius);
  }
}

module torso_panel_top_fit(width, height, depth, thickness, hole_radius, edge_round, backoff){
  switch_width = 21.3;
  switch_depth = 27.0;
  power_width = 8.9;
  power_height = 10.7;
  power_depth = 13.7;
  button_hole_diam = 3.2;
  button_hole_width = 10.8;
  button_hole_depth = 32.9;
  button_space_width = 6.3;
  button_space_depth = 28.6;
  cable_diam = 15;
  difference(){
    union(){
      torso_panel_top(width, height, depth, thickness, hole_radius, backoff);
      translate([0, -depth / 12, (height / 4) + (thickness / 4.1)]){
        cube([(width - backoff) - (thickness * 1.5), ((depth / 6) - backoff) - (thickness * 1.5), thickness / 4], true);
      }
      /* Power hole support */
      translate([width / 3, depth / 3.25, (height / 4) + (thickness / 4)]){
        cube([power_height + thickness, power_width + thickness, thickness / 3], true);
      }
    }
    translate([0, 0, height / 4]){
      cube([30, 100, thickness * 2], true);
      cube([10, 120, thickness * 2], true);
    }
    translate([0, -35, height / 4]){
      cube([160, 45, thickness / 3], true);
    }
    translate([-backoff, 0, 0]){
      torso_handle(width, height, depth, thickness, edge_round);
    }
    translate([backoff, 0, 0]){
      torso_handle(width, height, depth, thickness, edge_round);
    }
    /* Switch hole */
    translate([width / 3, depth / 10, height / 4]){
      cube([switch_width + backoff, switch_depth + (backoff * 2), thickness * 2], true);
    }
    /* Power hole */
    translate([width / 3, depth / 3.25, height / 4]){
      cube([power_height + backoff, power_width + backoff, power_depth + backoff], true);
    }
    /* Button hole */
    translate([-width / 2.75, depth / 5, height / 4]){
      cube([button_space_width + backoff, button_space_depth + backoff, thickness * 2], true);
      translate([-button_hole_width / 2, -button_hole_depth / 2, 0]){
        cylinder(thickness * 2, button_hole_diam / 2, button_hole_diam / 2, true);
      }
      translate([button_hole_width / 2, -button_hole_depth / 2, 0]){
        cylinder(thickness * 2, button_hole_diam / 2, button_hole_diam / 2, true);
      }
      translate([-button_hole_width / 2, button_hole_depth / 2, 0]){
        cylinder(thickness * 2, button_hole_diam / 2, button_hole_diam / 2, true);
      }
      translate([button_hole_width / 2, button_hole_depth / 2, 0]){
        cylinder(thickness * 2, button_hole_diam / 2, button_hole_diam / 2, true);
      }
    }
    /* Cable size */
    translate([-width / 5, depth / 3, height / 4]){
      cylinder(thickness * 2, cable_diam / 2, cable_diam / 2, true);
    }
  }
}

module offset_torso_panel_top(){
  translate([0, 0, TORSO_WIDTH / 3]){
    torso_panel_top_fit(TORSO_WIDTH, TORSO_HEIGHT, TORSO_DEPTH, THICKNESS, TORSO_HOLE_RADIUS, TORSO_ROUND, PANEL_BACKOFF);
  }
}

offset_torso_panel_top();