// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
float count = 0;

const int 
backLight = 13,
rs = 12,
en = 11, 
d4 = 5, 
d5 = 4, 
d6 = 3, 
d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int hallPin = A1 ;     // initializing a pin for the sensor output


// variables will change :

int hallState = 0 ;          // initializing a variable for storing the status of the hall sensor.

void setup() {
  

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // For Wind / Magnet

  // This will initialize the hall effect sensor pin as an input pin to the Arduino :
  pinMode ( hallPin , INPUT ) ;                        

  //Economy mode
  pinMode(backLight, OUTPUT);

  //Serial
  Serial.begin(9600);
  
  

  ///MAGNET
  // pinMode ( hallPin , INPUT ) ; 


  
}

void loop() {
  // set the cursor to column 0, line 0
  // (note: line 0 is the first row, since counting begins with 0):
  

   // lightcode.c
   // reads the input on analog pin A0 (value between 0 and 1023)
    int analogValue = analogRead(A0);

    Serial.print("Analog reading = ");
    Serial.print(analogValue);   // the raw analog reading

    
    // We'll have a few threshholds, qualitatively determined
    if (analogValue < 30) {
        lcd.clear();                  // without this you can have error prints
        digitalWrite(backLight, LOW); // if is dark we will stop the backlight 
        Serial.println(" Dark");
        lcd.print("Dark");
    }
    else if (analogValue < 150) {
        lcd.clear();
        digitalWrite(backLight, HIGH);
        Serial.println(" Room light");
        lcd.print("Room light");
    }
    else if (analogValue < 250) {
        lcd.clear();
        digitalWrite(backLight, HIGH);
        Serial.println(" Light");
        lcd.print("Light");
    }
    else if (analogValue < 450) {
        lcd.clear();
        digitalWrite(backLight, HIGH);
        Serial.println(" Bright");
        lcd.print("Bright");
    }
    else {
        lcd.clear();
        digitalWrite(backLight, HIGH);
        Serial.println(" Very Bright");
        lcd.print("Very Bright");
    }
    delay(700);

}
