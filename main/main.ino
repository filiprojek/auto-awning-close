#include <RCSwitch.h>
#include <Wire.h>
#include <Rtc_Pcf8563.h>

RCSwitch mySwitch = RCSwitch();
Rtc_Pcf8563 rtc;

// defining used pins
int wind = 8;
int rain = 12;
int receiver = 9;

int relay1 = 7;
int relay2 = 6;
int relay3 = 5;
int relay4 = 4;

// codes from remote controller
const int recRelay4 = 16736114;
const int recRelay3 = 16736120;
const int recRelay2 = 3696136;
const int recRelay1 = 16736113;

int delayTime = 2000;

void setup()
{
  Serial.begin(9600);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(wind, INPUT);
  pinMode(rain, INPUT);

  mySwitch.enableReceive(0); // Receiver on interrupt 0 => that is pin #2

  //clear out the registers
  rtc.initClock();
  //set a time to start with.
  //day, weekday, month, century(1=1900, 0=2000), year(0-99)
  rtc.setDate(14, 6, 3, 1, 10);
  //hr, min, sec
  rtc.setTime(1, 15, 0);
}

void updateRTC()
{
  /*
     function to update RTC time using user input
  */

  // ask user to enter new date and time
  const char txt[6][15] = { "year [4-digit]", "month [1~12]", "day [1~31]",
                            "hours [0~23]", "minutes [0~59]", "seconds [0~59]"};
  String str = "";
  long newDate[6];

  while (Serial.available()) {
    Serial.read();  // clear serial buffer
  }

  for (int i = 0; i < 6; i++) {

    Serial.print("Enter ");
    Serial.print(txt[i]);
    Serial.print(": ");

    while (!Serial.available()) {
      ; // wait for user input
    }

    str = Serial.readString();  // read user input
    newDate[i] = str.toInt();   // convert user input to number and save to array

    Serial.println(newDate[i]); // show user input
  }

  // update RTC
  //rtc.adjust(DateTime(2021, newDate[1], newDate[2], newDate[3], newDate[4], newDate[5]));
  rtc.setDate(newDate[2], 6, newDate[1], 0, 2020);
  Serial.println("RTC Updated!");
}

void relayOn(int pin)
{
  Serial.println("realy " + pin);

  digitalWrite(pin, HIGH);
  delay(delayTime);
  digitalWrite(pin, LOW);
  
  delay(delayTime);
}



void loop()
{
    //formatted strings are at the current time/date.
  Serial.print(rtc.formatTime());
  Serial.print("\r\n");
  Serial.print(rtc.formatDate());
  Serial.print("\r\n");
  delay(1000);
  
  if (Serial.available())
  {
    char input = Serial.read();
    if (input == 'u') updateRTC();  // update RTC time
  }

  if(digitalRead(rain) != HIGH)
  {
    Serial.println("cegoslav");
  }
  
  // wind actions
  if (digitalRead(wind) == HIGH)
  {
    digitalWrite(relay1, HIGH);
  }
  else
  {
    digitalWrite(relay1, LOW);
  }

  // remote controller actions
  if (mySwitch.available())
  {
    int received = mySwitch.getReceivedValue();
    Serial.println("Received " + received);

    if (received == recRelay1)
    {
      relayOn(relay1);
    }
    if (received == recRelay2)
    {
      relayOn(relay2);
    }
    if (received == recRelay3)
    {
      relayOn(relay3);
    }
    if (received == recRelay4)
    {
      relayOn(relay4);
    }

    mySwitch.resetAvailable();
  }
}
