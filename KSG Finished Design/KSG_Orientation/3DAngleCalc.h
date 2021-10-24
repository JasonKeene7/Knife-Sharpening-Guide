#ifndef DANGLECALC_H
#define DANGLECALC_H

//Needed to save class in header file
#include <Adafruit_ST7735.h>
#include <Adafruit_BNO055.h>

class angle3D
{
  Adafruit_ST7735 tft;    //LCD class
  Adafruit_BNO055 bno;    //BNO055 class

  const int CLASS_DELAY0 = 300;     //Button depress delay
  const int CLASS_DELAY1 = 150;     //Screen refresh delay
  const int CLASS_DELAY2 = 1500;    //Text delay
  
  const float DtR = PI/180.0;   //Degrees to radians
  const float RtD = 180.0/PI;   //Radians to degrees
  const char options[3][10] =   //Menu options 
    {"New Angle","Re-Level","Return"};

  bool dis_data = false;  //Debug mode
  int SELECT;             //Pushbutton pin
  int SWEEP;              //Potentiometer pin

  //All angle values are stored in radians
  float desired_angle = 0.0;                  //Target angle
  float Radx = 0.0, Rady = 0.0, Radz = 0.0;   //Stores BNO orientation data
  /* If variable name above doesn't make sense, they were already there in a previous verion 
   * of the program, so I yoinked those and am too lazy to change the names right now.
   */
  float Cxyzi = 1.0, Cxyzj = 0.0, Cxyzk = 0.0;   //Calibration for a non-level grindstone
  float Rxyzi = 1.0, Rxyzj = 0.0, Rxyzk = 0.0;   //Rotation vectors read by BNO055
  float calc_angle3D = 0.0;                   //Saved angle calculation
  
  void set_angle();             //Set desired sharpaning angle
  void angle3D_calc(bool);      //Calculate rotation vectors
  void calibration();           //Calibrate grindstone level
  void LCD_text(uint8_t);       //Display text on LCD
  void angle_2planes();         //Calculate angle between knife and grindstone
  void display_menu(uint8_t);   //Display moptions menu
  
public:
  angle3D();                      //Class constructor
  void initialize(int, int);      //Initialize LCD and some other functions
  void read_BNO(bool);            //Read BNO055 sensor
  float get_angle();              //Return calculated angle
  float get_desAngle();           //Return target angle
  void LCD_angle(float, bool);    //Display current angle
  void LCD_menu();                //Display options menu
}; 
#endif
