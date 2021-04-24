#include <VirtualWire.h>

int led = 2;
int btnA = 4;
int btnB = 5;
int btnC = 6;
int btnD = 7;

int transmitter = 8;



void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(led, OUTPUT);
  pinMode(btnA, INPUT);
  pinMode(btnB, INPUT);
  pinMode(btnC, INPUT);
  pinMode(btnD, INPUT);

  // vysilac
  // nastavení typu bezdrátové komunikace
  vw_set_ptt_inverted(true);
  // nastavení čísla datového pinu pro vysílač
  vw_set_tx_pin(transmitter);
  // nastavení rychlosti přenosu v bitech za sekundu
  vw_setup(1000);
}

const char whichButtonWasPressed()
{


  Serial.write("\n\nreturn false\n\n");
  return "";
}

void sendMsg(const char inputMsg = "")
{
   const char input = inputMsg;

  Serial.write("\n odesilani...");
  // proměnná zprava pro poslání textu
  const char *zprava = input;
  // rozsvícení LED diody při odesílání (nepovinné)
  digitalWrite(led, true);
  // odeslání textu v proměnné zprava
  vw_send((uint8_t *)zprava, strlen(zprava));
  // vyčkání na odeslání celé zprávy
  vw_wait_tx();
  // zhasnutí LED diody při odeslání (nepovinné)
  digitalWrite(led, false);
  // pauza mezi posláním zpráv
  delay(100);
}

void loop()
{
  // put your main code here, to run repeatedly:
  /*
  const char pressedBtn = whichButtonWasPressed();
  if(pressedBtn != "")
  {
    Serial.write("\n \n ifstatement \n \n");
    sendMsg(pressedBtn);
  }
  */

  if(digitalRead(btnA) == HIGH)
  {
    Serial.write("btna");
    const char pressedBtn = "btnA";
    sendMsg(pressedBtn);
  }
  if(digitalRead(btnB) == HIGH)
  {
    Serial.write("btnb");
    const char pressedBtn =  "btnB";
    sendMsg(pressedBtn);
  }
  if(digitalRead(btnC) == HIGH)
  {
    Serial.write("btnc");
    const char pressedBtn =  "btnC";
    sendMsg(pressedBtn);
  }
  if(digitalRead(btnD) == HIGH)
  {
    Serial.write("btnd");
    const char pressedBtn =  "btnD";
    sendMsg(pressedBtn);
  }

  
/*
  if(pressedBtn != "false")
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }
*/
}