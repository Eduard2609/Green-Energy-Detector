// includerea librariei:
#include <LiquidCrystal.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////
// initializare biblioteca asociind orice pin de interfata lcd necesar cu numarul de pin arduino la care este conectat
const int 
backLight = 13,
rs = 12,
en = 11, 
d4 = 5, 
d5 = 4, 
d6 = 3, 
d7 = 2,
hallPin = A1 ;                              // initializarea unui pin pentru iesirea senzorului
/////////////////////////////////////////////////////////////////////////////////////////////////////
int V1 = 0, V2= 0, Vt= 0;
/////////////////////////////////////////////////////////////////////////////////////////////////////
// const pentru RPM si magent
const int hallSensorPin = 8;                // conectati senzorul cu efect hall la pinul 2
const unsigned long sampleTime = 1000;
const int maxRPM = 1260;                    // rpm maxim pentru bara lcd
int rpmMaximum = 0;
volatile int value;
/////////////////////////////////////////////////////////////////////////////////////////////////////
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
/////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  // acest lucru va initializa pinul senzorului cu efect hall ca pin de intrare la arduino
  pinMode(hallSensorPin,INPUT);
  // serial
  // apelam timer
  // configurati numarul de coloane si randuri al ecranului lcd:
  lcd.begin(16, 2);
  lcd.clear();
  // mod economie energie
  pinMode(backLight, OUTPUT);
  // start
  digitalWrite(backLight, HIGH);
  lcd.print("Initializing");
  full_timer();
  delay(1000);
  lcd.clear(); 
}

void full_timer(){
  // pune codul de configurare aici:
  ADMUX = 0x44;   // 0b01000100
  ADCSRA = 0xAF; 
  ADCSRB = 0x05;  // citirea semnalului analogic sa se realizeze cand numaratorul 1 trece prin valoarea comparatorului B
  Serial.begin(9600);
  setup_timer1();
}

void setup_timer1(){
  TCCR1A = 0x00;
  TCCR1B = 0x03;  // prescaler de 256; numaratorul functioneaza in modul normal
  OCR1B = 33000;  // valoare aleatorie
  TIMSK1 = 0x04;  // s-a activat intreruperea comparatorului B al timerului 1
  }

ISR(TIMER1_COMPB_vect){
}

//////////////////////////////////////////////////////////////////////////
// Setup value
ISR(ADC_vect){  // la fiecare 1048ms trebuie sa se initieze o citire a semnalului analogic
  value = ADC;
}
//////////////////////////////////////////////////////////////////////////

void loop() {
  delay(250);
  displayWind();
  displayLightReg();
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

void displayLightReg(){
  Serial.println(value);
      lcd.setCursor(0, 0); 
    // vom avea cateva praguri, determinate calitativ
    if (value < 50) {
        Serial.println(" Dark");
        lcd.print("Dark");
        V2=0;
    }
    else if (value < 150) {
        Serial.println(" Room light");
        lcd.print("Room light");
        V2=1;
    }
    else if (value < 250) {
        Serial.println(" Light");
        lcd.print("Light");
        V2=1;
    }
    else if (value < 450) {
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
    V1=0;
  }
else if (rpm < 200) {
    lcd.clear();
    lcd.setCursor(0, 1);
    digitalWrite(backLight, HIGH);
    lcd.print("Light Wind");
    V1=1;
  }
else if (rpm < 300) {
    lcd.clear();
    lcd.setCursor(0, 1);
    digitalWrite(backLight, HIGH);
    lcd.print("Medium Wind");
    V1=2;
  }
else if (rpm < 400) {
    lcd.clear();
    lcd.setCursor(0, 1);
    digitalWrite(backLight, HIGH);
    lcd.print("Strong Wind");
    V1=2;
  }
else {
    lcd.clear();
    lcd.setCursor(0, 1);
    digitalWrite(backLight, HIGH);
    lcd.print("V.Strong Wind");
    V1=3;
  }
}
