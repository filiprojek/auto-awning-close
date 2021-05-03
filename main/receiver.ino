// 433 MHz vysílač

// připojení knihovny
#include <VirtualWire.h>

void setup()
{
  // nastavení typu bezdrátové komunikace
  vw_set_ptt_inverted(true);
  // nastavení čísla datového pinu pro vysílač
  vw_set_tx_pin(8);
  // nastavení rychlosti přenosu v bitech za sekundu
  vw_setup(1000);
  pinMode(13, OUTPUT);
}

void loop()
{
  // vytvoření proměnných pro různé
  // druhy zpráv
  // proměnná zprava pro poslání textu
  const char *zprava = "Cas od zapnuti: ";
  // proměnná s načtením počtu sekund od
  // připojení napájení
  long cas = millis()/1000;
  // pracovní proměnná pro konverzi
  // čísla na text
  char znaky [128];
  // příkazy pro konverzi čísla na text,
  // čas převedený na text je uložen do
  // proměnné casZnaky
  snprintf(znaky, sizeof(znaky), "%ld", cas);
  char *casZnaky = znaky;
  // rozsvícení LED diody při odesílání (nepovinné)
  digitalWrite(13, true);
  // odeslání textu v proměnné zprava
  vw_send((uint8_t *)zprava, strlen(zprava));
  // vyčkání na odeslání celé zprávy
  vw_wait_tx();
  // zhasnutí LED diody při odeslání (nepovinné)
  digitalWrite(13, false);
  // pauza mezi posláním zpráv
  delay(100);
  // obdobný kus kódu, který opět rozsvítí LED
  // diodu, zašle obsah proměnné casZnaky
  // a po odeslání LED diodu zhasne
  digitalWrite(13, true);
  vw_send((uint8_t *)"1", strlen("1"));
  vw_wait_tx();
  digitalWrite(13, false);
  delay(900);
}