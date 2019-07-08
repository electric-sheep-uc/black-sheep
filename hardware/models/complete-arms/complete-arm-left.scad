use <../shoulder/shoulder-left.scad>
use <../arm-parts/armParts-left.scad>
use <../hand/hand_left.scad>

module complete_arm()
{   shoulder();
        rotate([0,180,90]) translate ([-200,-20,-30]) {
            arm(true, true);
             translate ([-120,-5,0]) {
                 hand();
                ///// arm(false, true);
                ///// translate ([-120,-5,0]) hand();// arm(false, true);
                 //rotate([0,180,0]) 
                 //translate ([-120,-5,0]) hand();
             }
            }
         
    //arm(false, true);
   // hand();
    
    }
    
    complete_arm();