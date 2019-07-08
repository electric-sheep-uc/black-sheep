use <../shoulder/shoulder-left.scad>
use <../shoulder/shoulder-right.scad>
use <../arm-parts/armParts-right.scad>
use <../hand/hand_right.scad>

module complete_arm_right()
{   shoulder_right();
        rotate([0,180,90]) translate ([-200,-20,-30]) {
            arm_right(true, true);
             translate ([-120,-5,0]) {
               rotate([180,180,0])  right_hand();
                ///// arm(false, true);
                ///// translate ([-120,-5,0]) hand();// arm(false, true);
                 //rotate([0,180,0]) 
                 //translate ([-120,-5,0]) hand();
             }
            }
         
    //arm(false, true);
   // hand();
    
    }
    
    complete_arm_right();