#include <Wire.h>
#include "RTClib.h"

int OneMinuteBtn = 9;
int TenMinuteBtn = 10;
int OneHourBtn = 11;
int TenHourBtn = 12;

int TenHourCtrl = 13;
int OneHourCtrl = 14;
int TenMinuteCtrl = 15;
int OneMinuteCtrl = 16;



int oneMinuteCurPos = 0;
int tenMinuteCurPos = 0;
int oneHourCurPos = 0;
int tenHourCurPos = 1;

void birdUp()
{
  for(int i = 0; i<25; i++)
  {
    digitalWrite(TenHourCtrl, HIGH);
    digitalWrite(OneHourCtrl, HIGH);

    delay(50);
    
    digitalWrite(TenHourCtrl, LOW);
    digitalWrite(OneHourCtrl, LOW);
    
    digitalWrite(TenMinuteCtrl, HIGH);
    digitalWrite(OneMinuteCtrl, HIGH);

    delay(50);
  
    digitalWrite(TenMinuteCtrl, LOW);
    digitalWrite(OneMinuteCtrl, LOW);
  }

}

void clickOneNumber(int pin)
{
  digitalWrite(pin, HIGH);
  delay(50);
  digitalWrite(pin, LOW);
  delay(50);
}

void OneMinuteGoToNum(int num, bool doInitialize)
{
  while(oneMinuteCurPos != num || doInitialize)
  {
    clickOneNumber(OneMinuteCtrl);
    oneMinuteCurPos++;
    oneMinuteCurPos = oneMinuteCurPos%10;

    if(digitalRead(OneMinuteBtn) == 0)
    {
      oneMinuteCurPos = 9;
      doInitialize = false;
    }
  }
}

void TenMinuteGoToNum(int num, bool doInitialize)
{
  while(tenMinuteCurPos != num || doInitialize)
  {
    clickOneNumber(TenMinuteCtrl);
    tenMinuteCurPos++;
    tenMinuteCurPos = tenMinuteCurPos%10;

    if(digitalRead(TenMinuteBtn) == 0)
    {
      tenMinuteCurPos = 9;
      doInitialize = false;
    }
  }
}

void OneHourGoToNum(int num, bool doInitialize)
{
  while(oneHourCurPos != num || doInitialize)
  {
    clickOneNumber(OneHourCtrl);
    oneHourCurPos++;
    oneHourCurPos = oneHourCurPos%10;

    if(digitalRead(OneHourBtn) == 0)
    {
      oneHourCurPos = 9;
      doInitialize = false;
    }
  }
}


void TenHourGoToNum(int num, bool doInitialize)
{
  while(tenHourCurPos != num || doInitialize)
  {
    clickOneNumber(TenHourCtrl);
    tenHourCurPos++;
    tenHourCurPos = tenHourCurPos%10;

    if(digitalRead(TenHourBtn))
    {
      tenHourCurPos = 0;
      doInitialize = false;
    }
  }
}

void initializeShit()
{
  TenHourGoToNum(0, true);
  OneHourGoToNum(9, true);
  TenMinuteGoToNum(9, true);
  OneMinuteGoToNum(9, true);
}

RTC_DS1307 rtc;


void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  pinMode(OneMinuteBtn, INPUT);
  pinMode(TenMinuteBtn, INPUT);
  pinMode(OneHourBtn, INPUT);
  pinMode(TenHourBtn, INPUT);
  digitalWrite(OneMinuteBtn, HIGH);
  digitalWrite(TenMinuteBtn, HIGH);
  digitalWrite(OneHourBtn, HIGH);
  digitalWrite(TenHourBtn, HIGH);

  pinMode(TenHourCtrl, OUTPUT);
  pinMode(OneHourCtrl, OUTPUT);
  pinMode(TenMinuteCtrl, OUTPUT);
  pinMode(OneMinuteCtrl, OUTPUT);

  birdUp();
  
  initializeShit();

// Startup RTC
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

#ifdef SETTIME
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
#endif

// Set Time on Pinball
  DateTime now = rtc.now();
  /*
  TenHourGoToNum(now.hour()/10, false);
  OneHourGoToNum(now.hour()%10, false);
  TenMinuteGoToNum(now.minute()/10, false);
  OneMinuteGoToNum(now.minute()%10, false);
  */
  TenHourGoToNum(now.minute()/10, false);
  OneHourGoToNum(now.minute()%10, false);
  TenMinuteGoToNum(now.second()/10, false);
  OneMinuteGoToNum(now.second()%10, false);
  
}

int lastMinute = 0;
int lastHour = 0;

void loop() {
#ifdef DEBUG
  // put your main code here, to run repeatedly:
  Serial.print("OneMinute: ");
  Serial.print(digitalRead(OneMinuteBtn));
  Serial.print(" TenMinute: ");
  Serial.print(digitalRead(TenMinuteBtn));  
  Serial.print(" OneHour: ");
  Serial.print(digitalRead(OneHourBtn));
  Serial.print(" TenHour: ");
  Serial.println(digitalRead(TenHourBtn));
#endif
  
  // Set Time Pinball
  DateTime now = rtc.now();
  TenHourGoToNum(now.minute()/10, false);
  OneHourGoToNum(now.minute()%10, false);
  TenMinuteGoToNum(now.second()/10, false);
  OneMinuteGoToNum(now.second()%10, false);
  
  /*
  // Count up
  long curTime = millis();
  TenHourGoToNum((curTime/100000)%10, false);
  OneHourGoToNum((curTime/10000)%10, false);
  TenMinuteGoToNum((curTime/1000)%10, false);
  OneMinuteGoToNum((curTime/100)%10,false);
  */
}
