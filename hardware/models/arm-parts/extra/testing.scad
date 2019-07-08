
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

difference(){
rounded_edged_cube(cubeDims=[20,10,1], cornerRoundedness=10, height=20);
rounded_edged_cube(cubeDims=[17,7,1], cornerRoundedness=7, height=20);   
}