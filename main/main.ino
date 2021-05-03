// připojení knihovny
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
int delayTime = 2000;

int led1 = 4;
int led2 = 5;
int led3 = 6;
int led4 = 7;

int wind = 8;
int receiver = 9;

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  pinMode(wind, INPUT);


  // inicializace komunikace po sériové lince
  Serial.begin(9600);

  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
}

void ledTest()
{
  for(int i = 4; i < 8; i++)
  {
    digitalWrite(i, HIGH);
    delay(1000);
    digitalWrite(i, LOW);
  }
}

void ledLight(int pin)
{
  digitalWrite(pin, HIGH);
  delay(delayTime);
  digitalWrite(pin, LOW);
}

void loop()
{
  if(digitalRead(wind) == HIGH)
  {
    digitalWrite(led1, HIGH);
  }
  else
  {
    digitalWrite(led1, LOW);
  }

  if (mySwitch.available())
  {
    Serial.print("Received ");
    Serial.print( mySwitch.getReceivedValue() );

    switch(mySwitch.getReceivedValue())
    {
      case 16736113:
        Serial.println("aaaaaaaaaa");
        ledLight(led1);
        delay(delayTime);
      break;
      case 3696136:
        Serial.println("bbbbbbbbbb");
        ledLight(led2);
        delay(delayTime);
      break;
      case 16736120:
        Serial.println("cccccccccc");
        ledLight(led3);
        delay(delayTime);
      break;
      case 16736114:
        Serial.println("dddddddddd");
        ledLight(led4);
        delay(delayTime);
      break;
    }

    mySwitch.resetAvailable();
  }
}