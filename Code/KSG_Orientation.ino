/* 2 August, 2021
 * Thought of a better way to to find the knife angle.
 * Just use the Gyroscope:
 * With the gyroscope parallel to the knife's face and
 * assuming the person is always sharpening the edge
 * using perpendicular strokes, all that is needed would
 * be the gyroscope angle
 * 
 * TO DO: add a setup class that includes the desired knife
 * angle and calibration for the true angle of the grindstone
 */

#include "3DAngleCalc.h"

#define REFRESH_DELAY_MS    100   //Loop delay
#define SELECT              2     //Pushbutton
#define POT                 A0    //Potentiometer

angle3D calculator;

void setup() {
  delay(300);
  Serial.begin(115200);
  //while(!Serial);   //Uncomment if debuging code

  DDRD = B11111000; pinMode(POT, INPUT);
  calculator.initialize(SELECT, POT);
  delay(250);
}

void loop() {

  if(!digitalRead(SELECT)) calculator.LCD_menu();       //Pull up menu when pushbutton is pressed
  //Read BNO orientation then calculate the angle to the grindstone
  calculator.read_BNO(false); calculator.LCD_angle(calculator.get_angle(), true);
  correction(calculator.get_angle());
  delay(REFRESH_DELAY_MS);
}

//Calculate the difference between the desired and current angle
void correction(float sharpenAngle)
{
  float offBy = calculator.get_desAngle() - sharpenAngle;
  
  if(offBy < -9.0)                      PORTD = B00001000;
  else if(-9.0 < offBy && offBy < -6.0) PORTD = B00011000;
  else if(-5.0 < offBy && offBy < -3.0) PORTD = B00010000;
  else if(-3.0 < offBy && offBy < -1.0) PORTD = B00110000;
  else if(-1.0 < offBy && offBy < 1.0)  PORTD = B00100000;
  else if(1.0 < offBy && offBy < 3.0)   PORTD = B01100000;
  else if(3.0 < offBy && offBy < 6.0)   PORTD = B01000000;
  else if(6.0 < offBy && offBy < 9.0)   PORTD = B11000000;
  else if(9.0 < offBy)                  PORTD = B10000000;
}
