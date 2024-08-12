#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S i2s1;             //xy=148,264
AudioEffectFreeverb freeverb1;  //xy=1136,274
AudioMixer4 mixer1;             //xy=1288,352
AudioOutputI2S i2s2;            //xy=1643,286
AudioConnection patchCord1(i2s1, 0, freeverb1, 0);
AudioConnection patchCord2(i2s1, 0, mixer1, 1);
AudioConnection patchCord3(freeverb1, 0, mixer1, 0);
AudioConnection patchCord4(mixer1, 0, i2s2, 0);
AudioConnection patchCord5(mixer1, 0, i2s2, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=1032,100
// GUItool: end automatically generated code


// Potentiometer Inputs
#define pot1 A17
#define pot2 A16
#define pot3 A15


void setup() {

  Serial.begin(9600);
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(20);

  mixer1.gain(0, 0);    // wet gain
  mixer1.gain(1, 0.8);  // dry gain
  mixer1.gain(2, 0);    // unused, gain 0
  mixer1.gain(3, 0);    // unused, gain 0
  // I2S audio init
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.lineInLevel(0);
  // sgtl5000_1.lineOutLevel(15);
}

void loop() {
  freeverb1.roomsize((float)analogRead(pot1) / 1023.0);
  freeverb1.damping((float)analogRead(pot2) / 1023.0);
  mixer1.gain(0, (float)analogRead(pot3) / 1023.0);
}
