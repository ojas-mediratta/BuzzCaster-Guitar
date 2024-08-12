#include <LiquidCrystal.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

const int rs = 5, en = 4, d4 = 3, d5 = 2, d6 = 1, d7 = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

AudioInputI2S            i2s1;
AudioEffectFreeverb      freeverb1;
AudioMixer4              mixer1;
AudioOutputI2S           i2s2;
AudioControlSGTL5000     sgtl5000_1;
AudioConnection          patchCord1(i2s1, 0, freeverb1, 0);
AudioConnection          patchCord2(i2s1, 0, mixer1, 2);
AudioConnection          patchCord3(freeverb1, 0, mixer1, 1);
AudioConnection          patchCord4(mixer1, 0, i2s2, 0);

// Rotary Encoder Inputs
#define inputCLK 16
#define inputDT 17
#define encoderButton 22

// Potentiometer Inputs
#define pot1            A12  
#define pot2            A11  
#define pot3            A10 

int counter = 0;
int currentStateCLK;
int previousStateCLK;

String encdir = "";

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Set encoder pins as inputs
  pinMode(inputCLK, INPUT);
  pinMode(inputDT, INPUT);
  pinMode(encoderButton, INPUT_PULLUP);
  // Setup Serial Monitor
  Serial.begin(9600);
  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previousStateCLK = digitalRead(inputCLK);

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(10);

  // I2S audio init
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.9);

  AudioInterrupts();
}

void loop() {
  // read pot levels
  float knob1 = (float)analogRead(pot1) / 1023.0;  // room size
  float knob2 = (float)analogRead(pot2) / 1023.0;  // damping
  float knob3 = (float)analogRead(pot3) / 1023.0;  // dry level

  mixer1.gain(0, 0);            // unused, gain 0
  mixer1.gain(1, 0.5);          // freeverb (wet) gain 
  mixer1.gain(2, knob3);        // dry gain 
  mixer1.gain(3, 0);            // unused, gain 0

  freeverb1.roomsize(knob1);
  freeverb1.damping(knob2);

  // Read the current state of inputCLK
  currentStateCLK = digitalRead(inputCLK);

  // Pushbutton functionality
  if (!digitalRead(encoderButton)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cleared");
    delay(1000);
    counter = 0;
    lcd.clear();
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
    } else {
      // Encoder is rotating clockwise
      lcd.clear();
      counter++;
      encdir = "CW";
      Serial.print("Direction: ");
      Serial.print(encdir);
      Serial.print(" -- Value: ");
      Serial.println(counter);
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("Room:");
  lcd.print((int)(knob1 * 100));
  lcd.print(" Damp:");
  lcd.print((int)(knob2 * 100));
  lcd.setCursor(0, 1);
  lcd.print("Dry:");
  lcd.print((int)(knob3 * 100));
 
  // determine how much actual memory is needed for the audio processes
  // Serial.print("Max audio blocks used: ");
  // Serial.println(AudioMemoryUsageMax());
  // Serial.println();

  // Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK;
}