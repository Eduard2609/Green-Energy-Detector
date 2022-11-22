// include the library code:
#include <LiquidCrystal.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int 
backLight = 13,
rs = 12,
en = 11, 
d4 = 5, 
d5 = 4, 
d6 = 3, 
d7 = 2,
hallPin = A1 ;  // initializing a pin for the sensor output
/////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////
// const for RPM and magent
const int hallSensorPin = 8;               // connect the hall effect sensor on pin 2
const unsigned long sampleTime = 1000;
const int maxRPM = 1260;                  // maximum RPM for LCD Bar
int rpmMaximum = 0;
/////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
/////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {

   // This will initialize the hall effect sensor pin as an input pin to the Arduino 
  pinMode(hallSensorPin,INPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  //Economy mode
  pinMode(backLight, OUTPUT);

  //Start
  digitalWrite(backLight, HIGH);
  lcd.print("Initializing");
  delay(1000);
  lcd.clear();

  //Serial
  Serial.begin(9600);
}

void loop() {
  delay(100);
  int rpm = getRPM();
  if (rpm > rpmMaximum) rpmMaximum = rpm;
  if (rpm > 100) {
    digitalWrite(backLight, HIGH);
  }
  else 
  {
    digitalWrite(backLight, LOW);
  }
  lcd.clear();
  displayRPM(rpm);
  //displayBar(rpm);
  displayLight();
    
}

void displayLight()
{
  // lightcode.c
   // reads the input on analog pin A0 (value between 0 and 1023)
    int analogValue = analogRead(A0);

    Serial.print("Analog reading = ");
    Serial.print(analogValue);   // the raw analog reading

    lcd.clear();
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
}


int getRPM()
{
  int count = 0;
  boolean countFlag = LOW;
  unsigned long currentTime = 0;
  unsigned long startTime = millis();
  while (currentTime <= sampleTime)
  {
    if (digitalRead(hallSensorPin) == HIGH)
    {
      countFlag = HIGH;
    }
    if (digitalRead(hallSensorPin) == LOW && countFlag == HIGH)
    {
      count++;
      countFlag=LOW;
    }
    currentTime = millis() - startTime;
  }
  int countRpm = int(60000/float(sampleTime))*count;
  return countRpm;
}

void displayRPM(int rpm) 
{
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print(rpm,DEC);
  lcd.setCursor(7,0);
  lcd.print(rpmMaximum, DEC);
  lcd.setCursor(13,0);
  lcd.print("MAX");
  Serial.print("RPM = ");
  Serial.print(rpm);
  Serial.print("  MAX RPM = ");
  Serial.println(rpmMaximum);
}

void displayBar(int rpm)
{
  int numOfBars=map(rpm,0,maxRPM,0,15);
  lcd.setCursor(0,1);
  if (rpm!=0)
  {
  for (int i=0; i<=numOfBars; i++)
   {
        lcd.setCursor(i,1);
        lcd.write(1023);
      }
  }
} 
