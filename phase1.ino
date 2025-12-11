void setup() {
  pinMode(9, OUTPUT);  // PWM-Pin
}
int eins = 51;
int zwei = 102;
int drei = 153;
int vier = 204;
int funf = 255;

void loop() {
  analogWrite(9, eins); // ca. 2,5 V "Analogeffekt"
  delay (5000);
    analogWrite(9, zwei); // ca. 2,5 V "Analogeffekt"
  delay (5000);
    analogWrite(9, drei); // ca. 2,5 V "Analogeffekt"
  delay (5000);
    analogWrite(9, vier); // ca. 2,5 V "Analogeffekt"
  delay (5000);
    analogWrite(9, funf); // ca. 2,5 V "Analogeffekt"
  delay (5000);
}

