#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <LiquidCrystal_I2C.h>

// GUItool: begin automatically generated code
AudioInputI2S i2s1;                   //xy=157,289
AudioAnalyzeNoteFrequency notefreq1;  //xy=460.2857208251953,368.85712814331055
AudioEffectWaveshaper waveshape1;     //xy=474,426
AudioEffectFlange flange1;            //xy=650,408
AudioEffectChorus chorus1;            //xy=650,452
AudioMixer4 mixer2;                   //xy=810,442
AudioEffectDelay delay1;              //xy=964.571418762207,438.5714416503906
AudioMixer4 mixer3;                   //xy=1128,414
AudioEffectFreeverb freeverb1;        //xy=1316,400
AudioMixer4 mixer1;                   //xy=1502.8571548461914,307.92857933044434
AudioOutputI2S i2s2;                  //xy=1652.0000228881836,311.0000047683716
AudioConnection patchCord1(i2s1, 0, mixer1, 1);
AudioConnection patchCord2(i2s1, 0, waveshape1, 0);
AudioConnection patchCord3(i2s1, 0, notefreq1, 0);
AudioConnection patchCord4(waveshape1, chorus1);
AudioConnection patchCord5(waveshape1, flange1);
AudioConnection patchCord6(flange1, 0, mixer2, 0);
AudioConnection patchCord7(chorus1, 0, mixer2, 1);
AudioConnection patchCord8(mixer2, delay1);
AudioConnection patchCord9(delay1, 0, mixer3, 0);
AudioConnection patchCord10(delay1, 1, mixer3, 1);
AudioConnection patchCord11(delay1, 2, mixer3, 2);
AudioConnection patchCord12(delay1, 3, mixer3, 3);
AudioConnection patchCord13(mixer3, freeverb1);
AudioConnection patchCord14(freeverb1, 0, mixer1, 0);
AudioConnection patchCord15(mixer1, 0, i2s2, 0);
AudioConnection patchCord16(mixer1, 0, i2s2, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=1041.4285714285713,125.71428571428571
// GUItool: end automatically generated code

// Init LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Rotary Encoder Inputs
#define inputCLK 16
#define inputDT 17
#define encoderButton 22

// Potentiometer Inputs
#define pot1 A17
#define pot2 A16
#define pot3 A15

// Push-Button Input
#define button1 5

// Effect state
bool tunerOn = false;
bool driveOn = false;
bool chorusOn = false;
bool flangeOn = false;
bool delayOn = false;
bool reverbOn = false;

int counter = 0;
int currentStateCLK;
int previousStateCLK;

//Encoder Direction for Debugging
String encdir = "";

//Drive Arrays
// float overdrive[5] =
  void setup() {
  // Init LCD
  lcd.init();
  lcd.backlight();

  // Set encoder pins as inputs
  pinMode(inputCLK, INPUT);
  pinMode(inputDT, INPUT);
  pinMode(encoderButton, INPUT_PULLUP);

  // Set button as pullup input
  pinMode(button1, INPUT_PULLUP);

  // Setup Serial Monitor
  Serial.begin(9600);

  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previousStateCLK = digitalRead(inputCLK);

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(40);

  // I2S audio init
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.6);
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.lineInLevel(15);
  // sgtl5000_1.lineOutLevel(15);

  // Master Mixer Settings
  mixer1.gain(0, 0);    // wet gain
  mixer1.gain(1, 0.8);  // dry gain
  mixer1.gain(2, 0);    // unused, gain 0
  mixer1.gain(3, 0);    // unused, gain 0

  mixer2.gain(0, 1);  // flange gain
  mixer2.gain(1, 1);  // chorus gain
  mixer2.gain(2, 0);  // unused, gain 0
  mixer2.gain(3, 0);  // unused, gain 0

  mixer3.gain(0, 1);  // delay1
  mixer3.gain(1, 1);  // delay2
  mixer3.gain(2, 1);  // delay3
  mixer3.gain(3, 1);  // delay4

  // Initialize note frequency threshold
  notefreq1.begin(.15);

  AudioInterrupts();
}

void loop() {

  //Read the current state of inputCLK
  currentStateCLK = digitalRead(inputCLK);

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

  switch ((12 + (counter % 12)) % 12) {
    case 0:
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("TUNER");
      break;
    case 2:
    case 3:
      lcd.setCursor(0, 0);
      lcd.print("DRIVE");
      break;
    case 4:
    case 5:
      lcd.setCursor(0, 0);
      lcd.print("CHORUS");
      break;
    case 6:
    case 7:
      lcd.setCursor(0, 0);
      lcd.print("FLANGE");
      break;
    case 8:
    case 9:
      lcd.setCursor(0, 0);
      lcd.print("DELAY");
      if (delayOn) {
        lcd.setCursor(15, 0);
        lcd.print("<");
        // Read pot level
        int knob1 = map((((int)analogRead(pot1) / 1023.0) * 100), 1, 99, 100, 500);
        mixer1.gain(0, 1);  // wet gain
        mixer1.gain(1, 1);  // dry gain
        mixer1.gain(2, 0);  // unused, gain 0
        mixer1.gain(3, 0);  // unused, gain 0
        delay1.delay(0, knob1);
        delay1.delay(1, (knob1 * 2));
        delay1.delay(2, (knob1 * 3));
        delay1.delay(3, (knob1 * 4));
        lcd.setCursor(0, 1);
        lcd.print("T:");
        lcd.print(knob1);
        lcd.print("ms    ");
        delay(30);

        if (!digitalRead(encoderButton)) {
          delayOn = false;
          lcd.clear();
          delay(50);  //debouncing
        }
      } else {
        lcd.setCursor(15, 0);
        lcd.print(" ");
        mixer1.gain(0, 1);  // wet gain
        mixer1.gain(1, 1);  // dry gain
        mixer1.gain(2, 0);  // unused, gain 0
        mixer1.gain(3, 0);  // unused, gain 0
        delay1.delay(0, 0);
        delay1.delay(1, 0);
        delay1.delay(2, 0);
        delay1.delay(3, 0);
        if (!digitalRead(encoderButton)) {
          delayOn = true;
          lcd.clear();
          delay(50);  //debouncing
        }
      }
      break;
    case 10:
    case 11:
      lcd.setCursor(0, 0);
      lcd.print("REVERB");
      if (reverbOn) {
        lcd.setCursor(15, 0);
        lcd.print("<");
        // Read pot levels
        int knob1 = ((int)analogRead(pot1) / 1023.0) * 100;
        int knob2 = ((int)analogRead(pot2) / 1023.0) * 100;
        int knob3 = ((int)analogRead(pot3) / 1023.0) * 100;
        mixer1.gain(0, ((float)analogRead(pot2) / 1023.0));  // wet gain
        mixer1.gain(1, ((float)analogRead(pot1) / 1023.0));  // dry gain
        mixer1.gain(2, 0);                                   // unused, gain 0
        mixer1.gain(3, 0);                                   // unused, gain 0
        freeverb1.roomsize((float)analogRead(pot3) / 1023.0);
        lcd.setCursor(0, 1);
        lcd.print("D:");
        lcd.print(knob1);
        lcd.print("W:");
        lcd.print(knob2);
        lcd.print("R:");
        lcd.print(knob3);
        lcd.print("      ");
        delay(30);

        if (!digitalRead(encoderButton)) {
          reverbOn = false;
          lcd.clear();
          delay(50);  //debouncing
        }
      } else {
        lcd.setCursor(15, 0);
        lcd.print(" ");
        mixer1.gain(0, 1);  // wet gain
        mixer1.gain(1, 1);  // dry gain
        mixer1.gain(2, 0);  // unused, gain 0
        mixer1.gain(3, 0);  // unused, gain 0
        freeverb1.roomsize(0);
        freeverb1.damping(0);
        if (!digitalRead(encoderButton)) {
          reverbOn = true;
          lcd.clear();
          delay(50);  //debouncing
        }
      }
      break;
  }


  //Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK;
}
