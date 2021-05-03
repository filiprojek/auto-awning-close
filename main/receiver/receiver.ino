#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

int delayTime = 2000;


void setup()
{
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
}

void loop()
{
  if (mySwitch.available())
  {
    
/*     Serial.print("Received ");
    Serial.print( mySwitch.getReceivedValue() );
    Serial.print(" / ");
    Serial.print( mySwitch.getReceivedBitlength() );
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println( mySwitch.getReceivedProtocol() ); */

    switch(mySwitch.getReceivedValue())
    {
      case 16736113:
        Serial.println("aaaaaaaaaa");
        delay(delayTime);
      break;
      case 3696136:
        Serial.println("bbbbbbbbbb");
        delay(delayTime);
      break;
      case 16736120:
        Serial.println("cccccccccc");
        delay(delayTime);
      break;
      case 16736114:
        Serial.println("dddddddddd");
        delay(delayTime);
      break;
    }


    mySwitch.resetAvailable();
  }
}