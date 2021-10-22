#include "3DAngleCalc.h"

//Librearies for BNO gyroscope
#include <Wire.h>
#include <Adafruit_Sensor.h>    //Core sensor library
#include <Adafruit_BNO055.h>    //Spcific library for BNO055

//Libraries for LCD screen
#include <SPI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Specific library for ST7735
#define TFT_RST   8
#define TFT_CS    9
#define TFT_DC    10

//General library
#include <math.h>

using namespace std;

//Initialize main, LCD, and BNO objects
angle3D::angle3D():tft(TFT_CS, TFT_DC, TFT_RST), bno(55, 0x28){}

//Initialize the LCD, BNO and other settings in another method cause program would explode if it was done during setup
void angle3D::initialize(int button, int analog)
{
  SELECT = button; SWEEP = analog;  //Save input pins
  
  tft.initR(INITR_BLACKTAB);        //Init ST7735S chip, black tab
  tft.fillScreen(ST77XX_BLACK);     //Clear screen to Black
  tft.setRotation(1); LCD_text(0);  //Orient screen

  if(!bno.begin()) { LCD_text(6); while(1); }   //Check BNO connection
  
  set_angle(); calibration(); LCD_text(5);    //Initial calibrations
}

//Read the BNO055 sensor
void angle3D::read_BNO(bool flag_0)
{
  sensors_event_t level;
  bno.getEvent(&level);         //Get and save sensor values
  Radx = level.orientation.x * DtR;
  Rady = level.orientation.y * DtR;
  Radz = level.orientation.z * DtR;
  angle3D_calc(flag_0);         //Using the method parameter as both flags will always be the same
}

//Set desired angle
void angle3D::set_angle()
{
  //Convert the potentiometer input into degrees and send to another method to be displayed
  LCD_text(1);
  while(digitalRead(SELECT)) 
  {
    LCD_angle(analogRead(SWEEP)/1028.0 * 90, false);
  }
  desired_angle = analogRead(SWEEP)/1028.0 * PI/2.0;    //Convert analog to radians
  delay(CLASS_DELAY0); while(!digitalRead(SELECT));     //Make sure the button is unpressed before continuing
}

//Calibrate sensor for an unlevel grindstone
void angle3D::calibration()
{
  bool choice = false;   //Start calibration flag

  //Calibrate grindstone level if beleived not to be flat
  LCD_text(2);
  while(digitalRead(SELECT))
  {
    if(analogRead(SWEEP) < 512) { digitalWrite(5, LOW); choice = false; }
    else { digitalWrite(5, HIGH); choice = true; }
    delay(CLASS_DELAY1);
  }
  digitalWrite(5, LOW);                               //Reset LED
  delay(CLASS_DELAY1); while(!digitalRead(SELECT));   //Make sure the button is unpressed before continuing

  if(choice)
  {
    //Add wait code so BNO has time to be set
    LCD_text(3);
    while(digitalRead(SELECT));
    delay(CLASS_DELAY0); while(!digitalRead(SELECT));   //Make sure the button is unpressed before continuing

    read_BNO(true);
    LCD_text(4);

    if(dis_data)
    {
      //Display grindstone calibration
      Serial.print("\nX: ");  Serial.print(Cxyzi*RtD, 4);
      Serial.print("\tY: ");  Serial.print(Cxyzj*RtD, 4);
      Serial.print("\tZ: ");  Serial.println(Cxyzk*RtD, 4);
    }
  }
  delay(CLASS_DELAY0); while(!digitalRead(SELECT));    //Make sure the button is unpressed before continuing
}

/* Formula used to find the angle of the knife in 3D space:
 * Got the rotation vectors for the Y and Z axis and added the matrecies together:
 * the result seen in the first row of float variables, then using the angle of two 
 * planes formula to find the angle of the rotation vector and the plane of the grindstone.
 */
void angle3D::angle_2planes()
{  
  calc_angle3D =  acos((Rxyzi*Cxyzi + Rxyzj*Cxyzj + Rxyzk*Cxyzk)/
                  (pow(pow(Rxyzi,2)+pow(Rxyzj,2)+pow(Rxyzk,2),1/2)*pow(pow(Cxyzi,2)+pow(Cxyzj,2)+pow(Cxyzk,2),1/2)));
  
  if(isnan(calc_angle3D)) calc_angle3D = PI/2;    //Sets anlge to 90deg if vertical
  else if(calc_angle3D > PI/2) calc_angle3D -= 2 * (calc_angle3D - PI/2);
}

float angle3D::get_angle() { return calc_angle3D * RtD; }       //Return current angle
float angle3D::get_desAngle() { return desired_angle * RtD; }   //Return desired angle

//Calculate vector rotation
void angle3D::angle3D_calc(bool flag_cal)
{
  if(flag_cal)
  {
    //Calculate calibration vectors
    Cxyzi = cos(Radz) * cos(Rady);
    Cxyzj = sin(Radz) * cos(Radx) + cos(Radz) * sin(Rady) * sin(Radx);
    Cxyzk = sin(Radz) * sin(Radx) - cos(Radz) * sin(Rady) * cos(Radx);
  }
  else
  {
    //Calibrate knife vectors
    Rxyzi = cos(Radz) * cos(Rady);
    Rxyzj = sin(Radz) * cos(Radx) + cos(Radz) * sin(Rady) * sin(Radx);
    Rxyzk = sin(Radz) * sin(Radx) - cos(Radz) * sin(Rady) * cos(Radx);
    
    //Display the input angles
   if(dis_data)
   {
     Serial.print("\nX: ");   Serial.print(Rxyzi, 4);
     Serial.print("\tY: ");   Serial.print(Rxyzj, 4);
     Serial.print("\tZ: ");   Serial.print(Rxyzk, 4);

      uint8_t system, gyro, accel, mag;
      system = gyro = accel = mag = 0;
      bno.getCalibration(&system, &gyro, &accel, &mag);

      /* The data should be ignored until the system calibration is > 0 */
      Serial.print("\t");
      if (!system)
      {
        Serial.print("! ");
      }

      /* Display the individual values */
      Serial.print("\tSys:");   Serial.print(system, DEC);
      Serial.print(" G:");    Serial.print(gyro, DEC);
      Serial.print(" A:");    Serial.print(accel, DEC);
      Serial.print(" M:");    Serial.print(mag, DEC);
   }

    angle_2planes();
  }
}

void angle3D::LCD_angle(float dis_angle, bool flag_0)
{
  delay(CLASS_DELAY1);
  tft.fillScreen(ST77XX_BLACK);   //Clear screen to Black
  tft.setCursor(0,0);
  //Display the target angle above if set true
  if(flag_0) { tft.setTextColor(0xFFFF); tft.print("Target: "); tft.print(desired_angle * RtD); tft.println(); }
  tft.setTextColor(0xFFFF); tft.print("Angle: "); tft.print(dis_angle);   //Display current angle
}

void angle3D::LCD_text(uint8_t flag_text)
{
  delay(CLASS_DELAY1);
  tft.fillScreen(ST77XX_BLACK);   //Clear screen to Black
  tft.setCursor(0,0); tft.setTextColor(0xFFFF);
  
  switch(flag_text)
  {
    case 0: tft.println("PROGRAM START"); break;
    case 1: tft.println("Set desired angle"); break;
    case 2: tft.println("Calibrate grindstone?"); break;
    case 3: tft.println("Please set BNO on grindstone, then press button to continue."); break;
    case 4: tft.print("X: "); tft.print(Cxyzi*RtD); tft.println(" deg");
            tft.print("Y: "); tft.print(Cxyzj*RtD); tft.println(" deg");
            tft.print("Z: "); tft.print(Cxyzk*RtD); tft.println(" deg");
            break;
    case 5: tft.println("Knife calculation START"); break;
    case 6: tft.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!"); break;
    
    default: tft.println("Unkown flag!!!"); break;
  }
  delay(CLASS_DELAY2);
}

//Option menu control and method caller
void angle3D::LCD_menu()
{
  uint8_t line = 0;
  while(!digitalRead(SELECT));
  delay(CLASS_DELAY1);
  
  while(digitalRead(SELECT))
  {
    delay(CLASS_DELAY1);
    tft.fillScreen(ST77XX_BLACK);   //Clear screen to Black
    line = analogRead(SWEEP)/1028.0 * sizeof(options)/(sizeof(char)*10);
    display_menu(line);
  }
  delay(CLASS_DELAY0); while(!digitalRead(SELECT));   //Make sure the button is unpressed before continuing
  
  switch(line)
  {
    case 0: set_angle(); break;
    case 1: calibration(); break;
    case 2: break;
    default: Serial.println("No such option exists"); break;
  }
}

//Display options menu
void angle3D::display_menu(uint8_t highlight)
{
  tft.setCursor(0,0);
  for(uint8_t lister = 0; lister < sizeof(options)/(sizeof(char)*10); lister++)
  {
    tft.setTextColor(0xFFFF);
    
    //If the potentiometer position and for loop matches, highlight option
    if(highlight == lister) { tft.setTextColor(0xF800); tft.print(">"); }

    //Load then list menu option names
    char option_name[10];
    for(uint8_t load = 0; load < 10; load++)
    {
      option_name[load] = options[lister][load];
    }
    tft.print(lister); tft.print(": "); tft.print(option_name); tft.println();
  }
}
