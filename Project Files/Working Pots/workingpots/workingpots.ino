// Potentiometer Inputs
#define pot1 A17
#define pot2 A16
#define pot3 A15

void setup() {
  // put your setup code here, to run once:
  // Setup Serial Monitor
  Serial.begin(9600);
}

void loop() {
  float knob1 = analogRead(pot1) / 1023.0;
  float knob2 = analogRead(pot2) / 1023.0;
  float knob3 = analogRead(pot3) / 1023.0;

  Serial.print("Pot1: ");
  Serial.print(knob1);
  Serial.print(", Pot2: ");
  Serial.print(knob2);
  Serial.print(", Pot3: ");
  Serial.println(knob3);
}
