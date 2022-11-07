void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  // reads the input on analog pin A0 (value between 0 and 1023)
  int analogValue = analogRead(A0);

  Serial.print("Analog reading: ");
  Serial.print(analogValue);   // the raw analog reading

  // We'll have a few threshholds, qualitatively determined
  if (analogValue < 200) {
    Serial.println(" - Darkest");
  } else if (analogValue < 400) {
    Serial.println(" - Dark");
  } else if (analogValue < 500) {
    Serial.println(" - Light");
  } else if (analogValue < 980) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }

  delay(500);
}