void setup() {
    Serial.begin(9600);
}

void loop() {
    // reads the input on analog pin A0 (value between 0 and 1023)
    int analogValue = analogRead(A0);

    Serial.print("Analog reading = ");
    Serial.print(analogValue);   // the raw analog reading

    // We'll have a few threshholds, qualitatively determined
    if (analogValue < 10) {
        Serial.println(" - Dark");
    }
    else if (analogValue < 40) {
        Serial.println(" - Dim");
    }
    else if (analogValue < 150) {
        Serial.println(" - Light");
    }
    else if (analogValue < 450) {
        Serial.println(" - Bright");
    }
    else {
        Serial.println(" - Very Bright");
    }

    delay(500);
}
