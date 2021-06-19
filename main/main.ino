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
const int recRelay4 = 3696136;
const int recRelay3 = 16736114;
const int recRelay2 = 16736120;
const int recRelay1 = 16736113;

int delayTime = 500;
// status of roleta
bool isOpen = false;


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
  ///rtc.initClock();
  //set a time to start with.
  //day, weekday, month, century(1=1900, 0=2000), year(0-99)
  ///rtc.setDate(18, 6, 6, 0, 21);
  //hr, min, sec
  ///rtc.setTime(18, 44, 0);
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

void relayOn(int pin, bool controller = false)
{
  Serial.print("realy ");
  Serial.print(pin);
  Serial.print("\n");

  if(controller == false)
  {
    Serial.println("jsemtu");
    if(pin == relay4)
    {
      isOpen = true;
    }
    if(pin == relay1)
    {
      isOpen = false;
    } 
  }

  digitalWrite(pin, HIGH);
  delay(delayTime);
  if(pin == relay3) {
  //  delay(1500);
  }
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

  // assign day and month into variable
  char h1 = rtc.formatTime(RTCC_TIME_HM)[0];
  char h2 = rtc.formatTime(RTCC_TIME_HM)[1];
  int onlyHour = ( 10 * (h1 - '0') ) + h2 - '0';

  char m1 = rtc.formatTime(RTCC_TIME_HM)[3];
  char m2 = rtc.formatTime(RTCC_TIME_HM)[4];
  int onlyMinutes = ( 10 * (m1 - '0') ) + m2 - '0';

  char M1 = rtc.formatDate()[0];
  char M2 = rtc.formatDate()[1];
  int onlyMonth = ( 10 * (M1 - '0') ) + M2 - '0';
  
  Serial.println(onlyHour);
  Serial.println(onlyMinutes);
  Serial.println(onlyMonth);
  Serial.println(isOpen);

  // setting up date and time from serial monitor
  if (Serial.available())
  {
    char input = Serial.read();
    if (input == 'u') updateRTC();  // update RTC time
  }

  // time actions
  if(onlyMonth >= 5 && onlyMonth <= 9)
  {
     if(onlyHour >= 7 && onlyHour <= 14)
     {
        if(isOpen == false)
        {
          relayOn(relay4);
        }
     }
     else
     {
        if(isOpen == true)
        {
          relayOn(relay1);
        }
     }
  }
  
  // rain actions
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
    //digitalWrite(relay1, LOW); -> probably useless
  }

  // remote controller actions
  if (mySwitch.available())
  {
    int received = mySwitch.getReceivedValue();
    Serial.println("Received " + received);

    if (received == recRelay1)
    {
      relayOn(relay1, true);
    }
    if (received == recRelay2)
    {
      relayOn(relay2, true);
    }
    if (received == recRelay3)
    {
      relayOn(relay3, true);
    }
    if (received == recRelay4)
    {
      relayOn(relay4, true);
    }

    mySwitch.resetAvailable();
  }
}
