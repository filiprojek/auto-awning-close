#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

// defining used pins

int wind = 8;
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

  mySwitch.enableReceive(0); // Receiver on interrupt 0 => that is pin #2
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
