//include <upper-arm-config.scad>
include <../Motor-FS6535/motor-fs6535-horn-config.scad>
include <../Motor-FS6535/motor-fs6535-config.scad>
use <../arm-parts/cageSide.scad>
use <../Motor-FS6535/motor-fs6535.scad>
use <../Motor-FS6535/motor-fs6535-horn.scad>
use <../arm-parts/armParts-right.scad>

module rounded_edged_cube(cubeDims, cornerRoundedness, height)
{
if(str($qual) != "undef"){
  $fn = $qual;
}else{
  $fn = 64;
}
minkowski()
{
  cube(cubeDims, center=true);
  cylinder(r=cornerRoundedness,h=height);
}
}
module hand_parts(){
// hand shapes 
     //       rotate([0,90,0]) cube([30,6, 30], center=true);
    //        translate([25,0,0]) rotate([90,0,0]) cylinder(6,20,20, center=true);
    HEIGHT=20;
    WIDTH=20;
        difference(){
        rounded_edged_cube(cubeDims=[30,20,1], cornerRoundedness=15, height=20);
        rounded_edged_cube(cubeDims=[26,16,1], cornerRoundedness=11, height=20);   
        }
    
    }
    
module right_hand(){
    mirror(){
    translate([175,-10.5,5]) difference() {
       rotate([0,0,180]) translate([70, -43,14])	cageSide(false, true);
		//translate([0,0,-13]) cube([40,40,10], center=true);
	}
   translate([40.2,20,16]) rotate([90, 0, 0]) hand_parts();
}
	/*
   translate([32,20,15.5]) rotate([90, 0, 0]) scale ([0.6,0.6,0.6]){
    union(){
        translate([-5,0,0]) motor_fs6535_horn_mount(false);
        translate([37.5,0,0])  mirror() motor_fs6535_horn_mount(false);
    }
    
}*/
    //special hand parts
    /*union(){
        motor_fs6535_horn_mount();
        //
        translate([75,30,20]) hand_parts();
        translate([75,-28,20]) hand_parts();
   }
   */
   }
  
    right_hand();