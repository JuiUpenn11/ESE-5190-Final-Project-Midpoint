#include <Arduino.h>
#ifdef USE_TINYUSB
#include <Adafruit_TinyUSB.h>
#endif

#ifndef PIN_BUZZER
#define PIN_BUZZER    A0
#endif

uint8_t const pin_buzzer = PIN_BUZZER;

#define NOTE_G4  392
#define NOTE_C5  523
#define NOTE_E5  659
#define NOTE_G5  784
#define WHOLE         2200       // Length of time in milliseconds of a whole note (i.e. a full bar).
#define HALF          WHOLE/2
#define QUARTER       HALF/2
#define EIGHTH        QUARTER/2
#define EIGHTH_TRIPLE QUARTER/3
#define SIXTEENTH     EIGHTH/2

#include "Adafruit_seesaw.h"
#include <seesaw_neopixel.h>

#define  DEFAULT_I2C_ADDR1 0x3A
#define  DEFAULT_I2C_ADDR2 0x3B

#define  SWITCH1  18  // PA01
#define  SWITCH2  19 // PA02
#define  SWITCH3 20 // PA03
#define  SWITCH4  2 // PA06
#define  PWM1  12  // PC00            //LEDS
#define  PWM2  13 // PC01
#define  PWM3  0 // PA04
#define  PWM4  1 // PA05

#define  SWITCH5  18  // PA01
#define  SWITCH6  19 // PA02
#define  SWITCH7  20 // PA03
#define  SWITCH8  2 // PA06
#define  PWM5  12  // PC00
#define  PWM6  13 // PC01
#define  PWM7  0 // PA04
#define  PWM8  1 // PA05

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#define TFT_CS         20
#define TFT_RST        19 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         2
#define TFT_MOSI 7  // Data out
#define TFT_SCLK 6  // Clock out
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

Adafruit_seesaw ss1;
Adafruit_seesaw ss2;
int waitTime =2000;
int currentScore1 = 0; 
int currentScore2 = 0; 

void setup() {
  Serial.begin(115200);      // open the serial port at 9600 bps: 
  
  while (!Serial) 
  delay(10);   // wait until serial port is opened

  Serial.println(F("Testing!"));
  
  if (!ss1.begin(DEFAULT_I2C_ADDR1)) {
    Serial.println(F("seesaw1 not found!"));
    while(1) 
    delay(10);
  }
  if (!ss2.begin(DEFAULT_I2C_ADDR2)) {
    Serial.println(F("seesaw2 not found!"));
    while(1) 
    delay(10);
  }  

   pinMode(pin_buzzer, OUTPUT);            //buzzer set as output
   digitalWrite(pin_buzzer, LOW);
  
  ss1.pinMode(SWITCH1, INPUT_PULLUP);     // buttons are set to high when not pressed and  change to LOW when closed (pressed)
  ss1.pinMode(SWITCH2, INPUT_PULLUP);
  ss1.pinMode(SWITCH3, INPUT_PULLUP);
  ss1.pinMode(SWITCH4, INPUT_PULLUP);
  ss1.pinMode(PWM1, OUTPUT);             //Leds set as output
  ss1.pinMode(PWM2, OUTPUT);
  ss1.pinMode(PWM3, OUTPUT);
  ss1.pinMode(PWM4, OUTPUT);

  ss2.pinMode(SWITCH5, INPUT_PULLUP);
  ss2.pinMode(SWITCH6, INPUT_PULLUP);
  ss2.pinMode(SWITCH7, INPUT_PULLUP);
  ss2.pinMode(SWITCH8, INPUT_PULLUP);
  ss2.analogWrite(PWM5, 127);
  ss2.analogWrite(PWM6, 127);
  ss2.analogWrite(PWM7, 127);
  ss2.analogWrite(PWM8, 127);

  randomSeed(analogRead(0));
}

void playNote(int frequency, int duration, bool hold = false, bool measure = true) {
  (void) measure;

  if (hold) {
    
    tone(pin_buzzer, frequency, duration + duration / 32);
  } 
  else {
    
    tone(pin_buzzer, frequency, duration);
  }

  delay(duration + duration / 16);
}

void loop() {
 
  if(currentScore1 == 0 && currentScore2 == 0){
  playNote(NOTE_G5, HALF, false);                    //start sound
  playNote(NOTE_E5, SIXTEENTH, false);
  playNote(NOTE_G5, EIGHTH, true, false);
  playNote(NOTE_E5, EIGHTH_TRIPLE, false, false);
  playNote(NOTE_C5, EIGHTH_TRIPLE, true, false);
  playNote(NOTE_G4, EIGHTH_TRIPLE, true, false);  

  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  testdrawtext1("Welcome to Whack-It-First!", ST77XX_RED);
  delay(2000);
  tft.fillScreen(ST77XX_BLACK);
  delay(2000);
  testdrawtext1("Press the pink button to  begin the game!", ST77XX_RED);
  delay(2000);
  }
  
  int newColor1 = pickNewColor1();
  int newColor2 = pickNewColor2();
 
  ss1.digitalWrite(newColor1, HIGH);
  ss2.digitalWrite(newColor2, HIGH);        
                                                
  //check to see if whacked or not
  if (isWhacked1(newColor1) ) {
    Serial.println("You whacked the mole!");
    //ledOff(newColor);
    ss1.digitalWrite(newColor1, LOW);
    currentScore1++;
    delay(200); //pause briefly before showing a new mole
    waitTime = 0.9*waitTime;
    if(currentScore1 >= 50){
      currentScore1++;
      delay(200);
      waitTime = 0.5*waitTime;
      if(currentScore1 >= 100){
      currentScore1++;
      delay(100);
      waitTime = 0.3*waitTime;
      }            
    }
  } else {
    Serial.println("You failed to whack the mole! Game over.");
    gameover();
    waitTime = 2000;
  } 

  if (isWhacked2(newColor2) ) {
    Serial.println("You whacked the mole!");
    //ledOff(newColor);
    ss2.digitalWrite(newColor2, LOW);
    currentScore2++;
    tft.fillScreen(ST77XX_BLACK);
    testdrawtext2("Score of player1:",currentScore1, "Score of player2:", currentScore2, ST77XX_RED);
    delay(200); //pause briefly before showing a new mole
    waitTime = 0.9*waitTime;
    if(currentScore2 >= 50){
      currentScore2++;
      testdrawtext2("Score of player1:",currentScore1, "Score of player2:", currentScore2, ST77XX_RED);
      delay(200);
      waitTime = 0.5*waitTime;
      if(currentScore2 >= 100){
      currentScore2++;
      testdrawtext2("Score of player1:",currentScore1, "Score of player2:", currentScore2, ST77XX_RED);
      delay(100);
      waitTime = 0.3*waitTime;
      }            
    }
  } else {
    Serial.println("You failed to whack the mole! Game over.");
    gameover();
    waitTime = 2000;
  } 
  // challenge - how to speed up the game at next mole? (and reset after game over?)
}

boolean isWhacked1(int newColor1) {
  int i = 0;
  int chkButton;
  boolean whacked = false;
  boolean buttonPressed = false;

  //start the counter and wait for botton to be pressed..or timeout
  Serial.print("Wait Time: ");
  Serial.print(waitTime);
  while ((i < waitTime) and (!buttonPressed)) {
    
    chkButton = isButtonPressedcheck1(); //0 if nothing is pressed
    if (newColor1 == chkButton) { //correct button is pressed
      whacked = true;
      buttonPressed = true;
    } else if (chkButton >= 0) { //incorrect button is pressed
      whacked = false;
      buttonPressed = true;
    } 
    i++;
    //Serial.println("."); //Comment out later. This slows down the loop
    delay(1); //make each loop about 1ms
  }
  if (buttonPressed) {
    Serial.println("..button detected.");
  } else {
    Serial.println("..time out");
  }
  return whacked;
}

boolean isWhacked2(int newColor2) {
  int i = 0;
  int chkButton;
  boolean whacked = false;
  boolean buttonPressed = false;

  //start the counter and wait for botton to be pressed..or timeout
  Serial.print("Wait Time: ");
  Serial.print(waitTime);
  while ((i < waitTime) and (!buttonPressed)) {
    
    chkButton = isButtonPressedcheck2(); //0 if nothing is pressed
    if (newColor2 == chkButton) { //correct button is pressed
      whacked = true;
      buttonPressed = true;
    } else if (chkButton >= 0) { //incorrect button is pressed
      whacked = false;
      buttonPressed = true;
    } 
    i++;
    //Serial.println("."); //Comment out later. This slows down the loop
    delay(1); //make each loop about 1ms
  }
  if (buttonPressed) {
    Serial.println("..button detected.");
  } else {
    Serial.println("..time out");
  }
  return whacked;
}

//function that monitor all buttons and returns a integer
// 0 = nothing pressed
// 2-5 = button prssed
// variation #2 - 
// do not turn off led if button is NOT pressed
int isButtonPressedcheck1() {
  
    unsigned int buttonPressed = -1;
  
    //2 = red, 3 = blue, 4 = yellow, 5=green
    //Set to LOW when a button is pressed

    if (! ss1.digitalRead(SWITCH1)) {
      //ledOn(PWM1);
      ss1.digitalWrite(PWM1, HIGH);
      buttonPressed = PWM1;
    } /*else {
      ledOff(PWM1);;
    }*/
  
    if (! ss1.digitalRead(SWITCH2)) {
      //ledOn(PWM2);
      ss1.digitalWrite(PWM2, HIGH);
      buttonPressed = PWM2;
    } /*else {
      ledOff(PWM2);
    } */
  
    if (! ss1.digitalRead(SWITCH3)) {
      //ledOn(PWM4);
      ss1.digitalWrite(PWM3, HIGH);
      buttonPressed = PWM3;
    } /* else {
      ledOff(PWM4);
    } */
  
    if (! ss1.digitalRead(SWITCH4)) {
      //ledOn(PWM3);
      ss1.digitalWrite(PWM4, HIGH);
      buttonPressed = PWM4;
    } /*else {
      ledOff(PWM3);
    } */

    return buttonPressed;
}

int isButtonPressedcheck2() {
  
    unsigned int buttonPressed = -1;
  
    //2 = red, 3 = blue, 4 = yellow, 5=green
    //Set to LOW when a button is pressed

    if (! ss2.digitalRead(SWITCH5)) {
      //ledOn(PWM1);
      ss2.digitalWrite(PWM5, HIGH);
      buttonPressed = PWM5;
    } /*else {
      ledOff(PWM1);;
    }*/
  
    if (! ss2.digitalRead(SWITCH6)) {
      //ledOn(PWM2);
      ss2.digitalWrite(PWM6, HIGH);
      buttonPressed = PWM6;
    } /*else {
      ledOff(PWM2);
    } */
  
    if (! ss2.digitalRead(SWITCH7)) {
      //ledOn(PWM4);
      ss2.digitalWrite(PWM7, HIGH);
      buttonPressed = PWM7;
    } /* else {
      ledOff(PWM4);
    } */
  
    if (! ss2.digitalRead(SWITCH8)) {
      //ledOn(PWM3);
      ss2.digitalWrite(PWM8, HIGH);
      buttonPressed = PWM8;
    } /*else {
      ledOff(PWM3);
    } */

    return buttonPressed;
}


void gameover() {
  
   for (int i=0; i <= 2; i++){
    ss1.digitalWrite(PWM1, HIGH);
    ss1.digitalWrite(PWM2, HIGH);
    ss1.digitalWrite(PWM3, HIGH);
    ss1.digitalWrite(PWM4, HIGH);

    ss2.digitalWrite(PWM5, HIGH);
    ss2.digitalWrite(PWM6, HIGH);
    ss2.digitalWrite(PWM7, HIGH);
    ss2.digitalWrite(PWM8, HIGH);
     
    playNote(NOTE_G4, EIGHTH_TRIPLE, true, false);      // end sound
    playNote(NOTE_C5, EIGHTH_TRIPLE, true, false);
    playNote(NOTE_E5, EIGHTH_TRIPLE, false, false);
    playNote(NOTE_G5, EIGHTH, true, false);
    playNote(NOTE_E5, SIXTEENTH, false);
    playNote(NOTE_G5, HALF, false);   

    delay(200);

    ss1.digitalWrite(PWM1, LOW);
    ss1.digitalWrite(PWM2, LOW);
    ss1.digitalWrite(PWM3, LOW);
    ss1.digitalWrite(PWM4, LOW);

    ss2.digitalWrite(PWM5, LOW);
    ss2.digitalWrite(PWM6, LOW);
    ss2.digitalWrite(PWM7, LOW);
    ss2.digitalWrite(PWM8, LOW);
    
   }
    Serial.println(currentScore1);
    Serial.println(currentScore2);
    tft.fillScreen(ST77XX_BLACK);
    testdrawtext2("Final Score of player1 is:",currentScore1, "Final Score of player2 is:",currentScore2, ST77XX_RED);
    delay(3000);
    tft.fillScreen(ST77XX_BLACK);
    testdrawtext1("The Game Ends !",ST77XX_RED);                              
    delay(5000);

    currentScore1 = 0;
    currentScore2 = 0;
}  

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//function that monitor all buttons and returns a integer
// 0 = nothing pressed
// 2-5 = button prssed
/*
int isButtonPressed() {
  
    int buttonPressed = 0;
  
    //2 = red, 3 = blue, 4 = yellow, 5=green
    //Set to LOW when a button is pressed

    if (ss.digitalRead(SWITCH1) == LOW) {
      ss.digitalWrite(PWM1, HIGH);
      buttonPressed = PWM1;
    } else {
      ss.digitalWrite(PWM1, LOW);
    }
  
    if (ss.digitalRead(SWITCH2) == LOW) {
      ss.digitalWrite(PWM2, HIGH);
      buttonPressed = PWM2;
    } else {
      ss.digitalWrite(PWM2, LOW);
    }
  
    if (ss.digitalRead(SWITCH3) == LOW) {
      ss.digitalWrite(PWM3, HIGH);
      buttonPressed = PWM3;
    } else {
      ss.digitalWrite(PWM3, LOW);
    }
  
    if (ss.digitalRead(SWITCH4) == LOW) {
      ss.digitalWrite(PWM4, HIGH);
      buttonPressed = PWM4;
    } else {
      ss.digitalWrite(PWM4, LOW);
    }

    return buttonPressed;
}
*/
int pickNewColor1 () {
  
  int randomColor;
  int randomArray[4] = {PWM1, PWM2, PWM3, PWM4};
  int randIndex = (int)random(0, 4);
  randomColor = randomArray[randIndex];
  return randomColor;

}

int pickNewColor2 () {
  
  int randomColor;
  int randomArray[4] = {PWM5, PWM6, PWM7, PWM8};
  int randIndex = (int)random(0, 4);
  randomColor = randomArray[randIndex];
  return randomColor;

}

void testdrawtext1(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testdrawtext2(char *text1, int value1, char *text2, int value2, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text1);
  tft.print(value1);
  tft.print(text2);
  tft.print(value2);
}