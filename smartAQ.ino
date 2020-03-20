// ------------- buzzer music notes -----------------------------------------------
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


//------import libraries-----------------------------
#include <Servo.h>
#include <Wire.h>
#include <BH1750.h>
#include <LiquidCrystal_I2C.h>

/////////// define pins ///////////////////
#define IR 2
#define buzzer 8
#define waterPump 12
#define led 13


//*********** LCD DISPLAY *****************
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//*********** SERVO *****************
Servo servo1;

//*********** LIGHT INTENSITY SENSOR *****************
BH1750 lightMeter(0x23);


// defining varibles for ultrasonic sensor
const unsigned int TRIG_PIN=9;
const unsigned int ECHO_PIN=10;
int distance;

// defining varibles for timer
unsigned long previousMillis = 0;
const long interval = 5000; // change the time intervel


void setup() {
  Serial.begin(9600);
  
  Wire.begin();
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
  //---IR sensor ---------
  pinMode(IR,INPUT); //Pin 5 as signal input
  
  //-water pump -------------
  pinMode(waterPump,OUTPUT);
  digitalWrite(waterPump,HIGH);

  //----LED--------------
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);

  //--------servo---------
  servo1.attach(52);
  servo1.write(60);

  //------ultrasonic--------
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);




  //---DISPLAY-------------
  lcd.begin(20,4);
  lcd.home ();      
  lcd.setCursor ( 3, 1 ); 
  lcd.print("SMART AQUARIUM"); 

}

int n=0;
bool state = HIGH;
void loop() {
  lcd.clear();
  while(1)  {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    servo1.write(55);
    delay(500);
    servo1.write(85);
    delay(500);
  }
  
   if(digitalRead(IR)==LOW)  { 
      lcd.setCursor ( 0, 0 ); 
      lcd.print("                   "); 
      lcd.setCursor ( 0, 1 ); 
      lcd.print("                  ");
   }
   else  {
      lcd.setCursor ( 0, 0 ); 
      lcd.print("Food container is"); 
      lcd.setCursor ( 0, 1 ); 
      lcd.print("empty"); 
      Play_Pirates();
    }
    
  ultrasonic_read();
  if (distance > 8 && state == HIGH ){
      state = LOW;
     digitalWrite(waterPump,state);
      lcd.setCursor ( 0, 2 ); 
      lcd.print("Water level is low"); 
     Serial.println("pump on");
  }
  else if( distance < 4 && state == LOW){
     state = HIGH;
     digitalWrite(waterPump,state);
      lcd.setCursor ( 0, 2 ); 
      lcd.print("                   ");
     Serial.println("pump off");
  }
    lightsensor();    
   
  }
}
