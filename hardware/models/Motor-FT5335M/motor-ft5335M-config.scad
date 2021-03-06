MOTOR_FT5335M_CENTER_PLATE_LENGTH=76;
MOTOR_FT5335M_CENTER_PLATE_WIDTH=32.5;
MOTOR_FT5335M_CENTER_PLATE_HEIGHT=5.0;
MOTOR_FT5335M_CENTER_PLATE_OFFSET=42.2;

MOTOR_FT5335M_CENTER_LINE_WIDTH=3.0;
MOTOR_FT5335M_CENTER_LINE_LENGTH=MOTOR_FT5335M_CENTER_PLATE_LENGTH-4.8;
MOTOR_FT5335M_CENTER_LINE_HEIGHT=1.6;


MOTOR_FT5335M_BODY_LENGTH=62.9;
MOTOR_FT5335M_BODY_WIDTH=32.5;
MOTOR_FT5335M_BODY_HEIGHT=55.9;
MOTOR_FT5335M_LOWERBODY_HEIGHT=41.3;

MOTOR_FT5335M_SHAFT_HEIGHT=.5;
MOTOR_FT5335M_SHAFT_RADIUS=9.25;

MOTOR_FT5335M_TOP_PLATE_HEIGHT=6.2;
MOTOR_FT5335M_TOP_PLATE_LENGTH=59; //cercile radius is 3. 
MOTOR_FT5335M_TOP_PLATE_WIDTH=32.5;

//MOTOR_FT5335M_SCREWS_RADIUS=2.8;
MOTOR_FT5335M_SCREWS_RADIUS=2.5;
MOTOR_FT5335M_SCREWS_DISTANCE_SIDE=4;

MOTOR_FT5335M_TOP_CYLINDER_HEIGHT=5.2;
MOTOR_FT5335M_TOP_CYLINDER_RADIUS=4.5;

/* "Resolution" of arcs */
if(str($qual) != "undef"){
  $fn = $qual;
}else{
  $fn = 64;
}
/* Constants in mm */
/*BODY_WIDTH = 29.10;
BODY_HEIGHT = 49.50;
BODY_DEPTH = 68;
HORN_WIDTH = 19.5;
HORN_HEIGHT = 06.0;
HORN_DEPTH = 19.5;
HORN_SCREW_RADIUS = 06.0;
HORN_SCREW_HOLE_DIAMETER = 02.5;
HORN_DEPTH_OFFSET = (BODY_DEPTH / 2) - 09.5;
HOLE_OFFSET_WIDTH = 10.0 / 2;
HOLE_OFFSET_HEIGHT = 28.5 - (BODY_HEIGHT / 2);
HOLE_OFFSET_DEPTH = 46.5 / 2;
HOLE_RADIUS = 03.5 / 2;
SCREW_RADIUS = HOLE_RADIUS * 0.75;
MOUNT_HEIGHT = 05.0;
MOUNT_DEPTH = 07.0;
MODEL_ACCURACY_BACKOFF = 1.0;*/
/* Plastic colour */
PRINT_COLOR = [0.2, 0.2, 0.2];