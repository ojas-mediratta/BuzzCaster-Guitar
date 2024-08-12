#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Rotary Encoder Inputs
#define inputCLK 16
#define inputDT 17
#define encoderButton 22

// Potentiometer Inputs
#define pot1 A12
#define pot2 A11
#define pot3 A10

int counter = 0;
int currentStateCLK;
int previousStateCLK;

String encdir = "";
enum FXModeType { TUNER,
                  OVERDRIVE,
                  DISTORTION,
                  CHORUS,
                  DELAY,
                  REVERB,
                  FLANGER
};
FXModeType FXMode;
bool lockEffect;

void setup() {
  lcd.init();
  lcd.backlight();
  // Set encoder pins as inputs
  pinMode(inputCLK, INPUT);
  pinMode(inputDT, INPUT);
  pinMode(encoderButton, INPUT_PULLUP);
  // Setup Serial Monitor
  Serial.begin(9600);
  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previousStateCLK = digitalRead(inputCLK);
}

void loop() {
  // read pot levels
  // float knob1 = (float)analogRead(pot1) / 1023.0;
  // float knob2 = (float)analogRead(pot2) / 1023.0;
  // float knob3 = (float)analogRead(pot3) / 1023.0;

  // Read the current state of inputCLK
  currentStateCLK = digitalRead(inputCLK);

  // Pushbutton functionality
  if (!digitalRead(encoderButton)) {
    lcd.setCursor(15, 0);
    lcd.print("<");
    lockEffect = 1;
  }

  // If the previous and the current state of the inputCLK are different then a pulse has occured
  if (currentStateCLK != previousStateCLK) {
    // If the inputDT state is different than the inputCLK state then
    // the encoder is rotating counterclockwise
    if (digitalRead(inputDT) != currentStateCLK) {
      lcd.clear();
      counter--;
      encdir = "CCW";
      Serial.print("Direction: ");
      Serial.print(encdir);
      Serial.print(" -- Value: ");
      Serial.println(counter);

      lcd.setCursor(0, 0);

      switch (counter % 14) {
        case 0:
        case 1:
          FXMode = TUNER;
          lcd.print("TUNER");
          break;
        case 2:
        case 3:
          FXMode = OVERDRIVE;
          lcd.print("OVERDRIVE");
          break;
        case 4:
        case 5:
          FXMode = DISTORTION;
          lcd.print("DISTORTION");
          break;
        case 6:
        case 7:
          FXMode = CHORUS;
          lcd.print("CHORUS");
          break;
        case 8:
        case 9:
          FXMode = DELAY;
          lcd.print("DELAY");
          break;
        case 10:
        case 11:
          FXMode = REVERB;
          lcd.print("REVERB");
          break;
        case 12:
        case 13:
          FXMode = FLANGER;
          lcd.print("FLANGER");
          break;
      }
    } else {
      // Encoder is rotating clockwise
      lcd.clear();
      counter++;
      encdir = "CW";
      Serial.print("Direction: ");
      Serial.print(encdir);
      Serial.print(" -- Value: ");
      Serial.println(counter);

      switch (counter % 14) {
        case 1:
        case 2:
          FXMode = TUNER;
          lcd.print("TUNER");
          break;
        case 3:
        case 4:
          FXMode = OVERDRIVE;
          lcd.print("OVERDRIVE");
          break;
        case 5:
        case 6:
          FXMode = DISTORTION;
          lcd.print("DISTORTION");
          break;
        case 7:
        case 8:
          FXMode = CHORUS;
          lcd.print("CHORUS");
          break;
        case 9:
        case 10:
          FXMode = DELAY;
          lcd.print("DELAY");
          break;
        case 11:
        case 12:
          FXMode = REVERB;
          lcd.print("REVERB");
          break;
        case 13:
        case 0:
          FXMode = FLANGER;
          lcd.print("FLANGER");
          break;
      }
    }
  }



  // lcd.setCursor(0, 0);
  // lcd.print("Room:");
  // lcd.print((int)(knob1 * 100));
  // lcd.print(" Damp:");
  // lcd.print((int)(knob2 * 100));
  // lcd.setCursor(0, 1);
  // lcd.print("Dry:");
  // lcd.print((int)(knob3 * 100));

  // Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK;
}