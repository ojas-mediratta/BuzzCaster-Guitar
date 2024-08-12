#include <LiquidCrystal.h>

// const int rs = 5, en = 4, d4 = 3, d5 = 2, d6 = 1, d7 = 0;
// LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Rotary Encoder Inputs
#define inputCLK 16
#define inputDT 17
#define encoderButton 22

int counter = 0;
int currentStateCLK;
int previousStateCLK;

String encdir = "";

void setup() {
  // // set up the LCD's number of columns and rows:
  // lcd.begin(16, 2);
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
  // Read the current state of inputCLK
  currentStateCLK = digitalRead(inputCLK);

  // If the previous and the current state of the inputCLK are different then a pulse has occured
  if (currentStateCLK != previousStateCLK) {

    // If the inputDT state is different than the inputCLK state then
    // the encoder is rotating counterclockwise
    if (digitalRead(inputDT) != currentStateCLK) {
      counter--;
      encdir = "CCW";
    } else {
      // Encoder is rotating clockwise
      counter++;
      encdir = "CW";
    }
    Serial.print("Direction: ");
    Serial.print(encdir);
    Serial.print(" -- Value: ");
    Serial.println(counter);
  }
  // Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK;
}