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
int V1 = 0, V2= 0, Vt= 0;
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
  lcd.clear();
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
  delay(500);
  // int rpm = getRPM();
  // if (rpm > rpmMaximum) rpmMaximum = rpm;
  // if (rpm > 100) {
  //   digitalWrite(backLight, HIGH);
  // }
  // else 
  // {
  //   digitalWrite(backLight, LOW);
  // }
  //lcd.clear();
  
  //displayBar(rpm);
 // lcd.setCursor(0, 0); 
  //displayRPM(rpm);
  displayWind();
  displayLight();
  lcd.setCursor(12, 0); 
  Vt= V1+V2;
  if (Vt < 1)
  {
    digitalWrite(backLight, LOW);
    Serial.println(Vt);
    lcd.print("P:");
    lcd.print(Vt);
  }
  else
  {
    digitalWrite(backLight, HIGH);
    Serial.println(Vt);
    lcd.print("P:");
    lcd.print(Vt);
  }
  
    
}

void displayLight()
{
  // lightcode.c
   // reads the input on analog pin A0 (value between 0 and 1023)
    int analogValue = analogRead(A0);

    Serial.print("Analog reading = ");
    Serial.print(analogValue);   // the raw analog reading

    
    lcd.setCursor(0, 0); 
    // We'll have a few threshholds, qualitatively determined
    if (analogValue < 50) {
        Serial.println(" Dark");
        lcd.print("Dark");
        V2=0;
    }
    else if (analogValue < 150) {

        Serial.println(" Room light");
        lcd.print("Room light");
        V2=1;
    }
    else if (analogValue < 250) {

        Serial.println(" Light");
        lcd.print("Light");
        V2=1;
    }
    else if (analogValue < 450) {

        Serial.println(" Bright");
        lcd.print("Bright");
        V2=2;
    }
    else {
        Serial.println(" Very Bright");
        lcd.print("Very Bright");
        V2=3;
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
 // lcd.clear();
  lcd.setCursor(0, 1); 
  lcd.print(rpm,DEC);
  lcd.setCursor(7,1);
  lcd.print(rpmMaximum, DEC);
  lcd.setCursor(13,1);
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

void displayWind()
{
  
  int rpm = getRPM();
  lcd.setCursor(0, 1);
  if (rpm > rpmMaximum) rpmMaximum = rpm;
  if (rpm < 100) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("No Wind");
    // lcd.setCursor(13,1);
    // lcd.print(rpm,DEC);
    V1=0;
  }
else if (rpm < 200) {
    lcd.clear();
    lcd.setCursor(0, 1);
    digitalWrite(backLight, HIGH);
    lcd.print("Light Wind");
    // lcd.setCursor(13,1);
    // lcd.print(rpm,DEC);
    V1=1;
  }
else if (rpm < 300) {
    lcd.clear();
    lcd.setCursor(0, 1);
    digitalWrite(backLight, HIGH);
    lcd.print("Medium Wind");
    // lcd.setCursor(13,1);
    // lcd.print(rpm,DEC);
    V1=2;
  }
else if (rpm < 400) {
    lcd.clear();
    lcd.setCursor(0, 1);
    digitalWrite(backLight, HIGH);
    lcd.print("Strong Wind");
    // lcd.setCursor(13,1);
    // lcd.print(rpm,DEC);
    V1=2;
  }
else {
    lcd.clear();
    lcd.setCursor(0, 1);
    digitalWrite(backLight, HIGH);
    lcd.print("V.Strong Wind");
    // lcd.setCursor(13,1);
    // lcd.print(rpm,DEC);
    V1=3;
  }
}

