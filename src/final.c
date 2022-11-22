

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int backLight=13, rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 const int hallPin = A1 ;     // initializing a pin for the sensor output

const int ledPin =  13 ;     // initializing a pin for the led. Arduino has built in led attached to pin 13

// variables will change :

int hallState = 0 ;          // initializing a variable for storing the status of the hall sensor.

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  

  // Print a message to the LCD.
  //lcd.print("hello, world!");

  Serial.begin(9600);
  pinMode(backLight, OUTPUT);
  ///MAGNET
 /* pinMode ( ledPin , OUTPUT ) ;      // This will initialize the LED pin as an output pin :

  pinMode ( hallPin , INPUT ) ;      // This will initialize the hall effect sensor pin as an input pin to the Arduino :

 Serial.begin( 9600 ) ; */

}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);

  // lightcode.c
   // reads the input on analog pin A0 (value between 0 and 1023)
    int analogValue = analogRead(A0);

    Serial.print("Analog reading = ");
    Serial.print(analogValue);   // the raw analog reading

    // We'll have a few threshholds, qualitatively determined
    if (analogValue < 30) {
        lcd.clear();
        digitalWrite(backLight, LOW);
        Serial.println(" - Dark");
        lcd.print(" - Dark");
    }
    else if (analogValue < 150) {
        lcd.clear();
        digitalWrite(backLight, HIGH);
        Serial.println(" - Room light");
        lcd.print(" -  Room light");
        
    }
    else if (analogValue < 250) {
        lcd.clear();
        digitalWrite(backLight, HIGH);
        Serial.println(" - Light");
        lcd.print(" - Light");
    }
    else if (analogValue < 450) {
        lcd.clear();
        digitalWrite(backLight, HIGH);
        Serial.println(" - Bright");
        lcd.print(" - Bright");
    }
    else {
        lcd.clear();
        digitalWrite(backLight, HIGH);
        Serial.println(" - Very Bright");
        lcd.print(" -  Very Bright");
    }
    

    delay(500);

   /* hallState = digitalRead ( hallPin ) ;                           // reading from the sensor and storing the state of the hall effect sensor :

  if ( hallState == LOW ) {                                                // Checking whether the state of the module is high or low



    digitalWrite ( ledPin , HIGH ) ;                                 // turn on the LED if he state of the module is high

  } 

  else {

    digitalWrite ( ledPin , LOW ) ;                                      // otherwise turn off the LED :



  }

} */

}





