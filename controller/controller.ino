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

/* const char whichButtonWasPressed()
{

  Serial.write("\n\nreturn false\n\n");
  return "";
} */

/* void sendMsg(inputMsg)
{
  Serial.write("input");
  // Serial.write(input)
  Serial.write("\n odesilani...\n");

  switch (inputMsg)
  {
    case 'A':
      vw_send((uint8_t *)"1", strlen("1"));
    break;
    case 'B':
      vw_send((uint8_t *)"2", strlen("2"));
    break;
    case 'C':
      vw_send((uint8_t *)"3", strlen("3"));
    break;
    case 'D':
      vw_send((uint8_t *)"4", strlen("4"));
    break;
    default:
      vw_send((uint8_t *)"0", strlen("0"));
  }

  vw_wait_tx();
  digitalWrite(13, false);
  delay(900);
} */

void loop()
{
  String pressedBtn = "N";
  if (digitalRead(btnA) == HIGH)
  {
    Serial.write("btna");
    pressedBtn = "A";

    Serial.write("\n odesilani...\n");
    vw_send((uint8_t *)"1", strlen("1"));
    vw_wait_tx();
    digitalWrite(13, false);
    delay(900);
  }

  if (digitalRead(btnB) == HIGH)
  {
    Serial.write("btnb");
    pressedBtn = "B";

    Serial.write("\n odesilani...\n");
    vw_send((uint8_t *)"2", strlen("2"));
    vw_wait_tx();
    digitalWrite(13, false);
    delay(900);
  }

  if (digitalRead(btnC) == HIGH)
  {
    Serial.write("btnc");
    pressedBtn = "C";

    Serial.write("\n odesilani...\n");
    vw_send((uint8_t *)"3", strlen("3"));
    vw_wait_tx();
    digitalWrite(13, false);
    delay(900);
  }
  
  if (digitalRead(btnD) == HIGH)
  {
    Serial.write("btnd");
    pressedBtn = "D";

    Serial.write("\n odesilani...\n");
    vw_send((uint8_t *)"4", strlen("4"));
    vw_wait_tx();
    digitalWrite(13, false);
    delay(900);
  }
}


/*     vw_send((uint8_t *)"1", strlen("1"));
    vw_wait_tx();
    digitalWrite(13, false);
    delay(900); */