#include <RCSwitch.h>
#include <Rtc_Pcf8563.h>
#include <Wire.h>

RCSwitch remote = RCSwitch();
Rtc_Pcf8563 rtc;

// defining used pins
const int wind = 8;
const int rain = 12;

const int r_close = 4; // close
const int r_stop = 5;  // stop
const int r_open = 6;  // open
const int r_led = 7;   // led

// codes from remote controller
const unsigned long rec_r_close = 16736113;
const unsigned long rec_r_stop = 16736114;
const unsigned long rec_r_open = 3696136;
const unsigned long rec_r_led = 16736120;

int delayTime = 500; // default delay time used everywhere
bool isOpen = false; // current status
bool t_open = false; // open by time

void setup()
{
    Serial.begin(9600);
    Wire.begin(); // Initialize I2C communication

    Serial.println("press 'u' to set the new date");
    Serial.print("\n\n\n\n\n");

    pinMode(r_close, OUTPUT);
    pinMode(r_led, OUTPUT);
    pinMode(r_stop, OUTPUT);
    pinMode(r_open, OUTPUT);
    pinMode(wind, INPUT);
    pinMode(rain, INPUT);

    remote.enableReceive(0); // Receiver on interrupt 0 => that is pin #2

    relayOn(r_close, true); // close the awning to return it to its base state
    printStatus();
}

void loop()
{
    // if serial is available, check user's input for char 'u' for date update
    if (Serial.available() > 0)
    {
        char userInput = Serial.read();
        if (userInput == 'u')
        {
            setNewDateTimeFromSerial();
        }
    }

    // Extract hour and month
    int hour = (rtc.formatTime()[0] - '0') * 10 + (rtc.formatTime()[1] - '0');
    int month = (rtc.formatDate()[0] - '0') * 10 + (rtc.formatDate()[1] - '0');

    // handle actions
    handleTimeBasedActinos(hour, month);
    handleWeatherBasedActions();
    handleRemoteControlActions();

    // printStatus();
    delay(250);
}

void relayOn(int pin, bool controller = false)
{
    Serial.println("Turning on relay pin ");
    Serial.print(pin);
    Serial.print("\n");

    Serial.println("isOpen: ");
    Serial.print(isOpen);
    Serial.print("\r\n");

    if (pin == r_open)
    {
        isOpen = true;
    }

    if (pin == r_close)
    {
        isOpen = false;
    }

    if (pin == r_close && isOpen == false && controller == false)
    {
        Serial.println("Not closing - already closed");
        return;
    }

    digitalWrite(pin, HIGH);
    delay(delayTime);
    digitalWrite(pin, LOW);
    delay(delayTime);
}

void handleTimeBasedActions(int hour, int month)
{
    if (month >= 5 && month <= 8)
    {
        if (hour >= 7 && hour <= 14 && !t_open)
        {
            Serial.println("Time to open");
            relayOn(r_open);
            t_open = !t_open;
        }
        else if (t_open)
        {
            Serial.println("Time to close");
            relayOn(r_close);
            t_open = !t_open;
        }
    }
}

void handleWeatherBasedActions()
{
    // rain actions
    if (digitalRead(rain) != HIGH)
    {
        Serial.println("Rain detected, closing");
        relayOn(r_close);
    }

    // wind actions
    if (digitalRead(wind) == HIGH)
    {
        Serial.println("Wind detected, closing");
        relayOn(r_close);
    }
}

void handleRemoteControlActions()
{
    if (remote.available())
    {
        int received = remote.getReceivedValue();
        Serial.println("Received " + received);

        switch (received)
        {
        case rec_r_close:
            relayOn(r_close, true);
            break;
        case rec_r_led:
            relayOn(r_led, true);
            break;
        case rec_r_stop:
            relayOn(r_stop, true);
            break;
        case rec_r_open:
            relayOn(r_open, true);
            break;
        }

        remote.resetAvailable();
    }
}

void setNewDateTimeFromSerial()
{
    Serial.println("Enter new date and time in format: YYYY MM DD HH MM SS");
    while (Serial.available() > 0)
    {
        String input = Serial.readStringUntil('\n');
        int year, month, day, hour, minute, second;

        if (sscanf(input.c_str(), "%d %d %d %d %d %d", &year, &month, &day, &hour, &minute, &second) == 6)
        {
            rtc.setDate(day, rtc.getWeekday(), month, false, year - 2000);
            rtc.setTime(hour, minute, second);
            Serial.println("Time set successfully!");
        }
        else
        {
            Serial.println("Invalid input. Please enter the date and time in the format: YYYY MM DD HH MM SS");
        }
    }
}

void printStatus()
{
    // print current status
    Serial.println("Time:");
    Serial.print(rtc.formatTime());
    Serial.print(" | ");
    Serial.print(rtc.formatDate());
    Serial.print("\r\n");

    Serial.println("isOpen: ");
    Serial.print(isOpen);
    Serial.print("\r\n");
}
