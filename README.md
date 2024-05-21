# auto-awning-close

The auto-awning-close project utilizes an Arduino Nano to automate the closing of an awning by interfacing with the original remote controller through relays. This setup allows the Arduino to send commands to the awning's existing control system, ensuring seamless integration with the original mechanism. A separate remote controller is used to communicate with the Arduino board, which then activates the appropriate relays to operate the awning.

This project includes detailed breadboard and PCB layouts to guide assembly, making it a reliable and efficient solution for automating awning control based on programmable conditions or user input. [See schematics](schematics/)

## Features

- __Weather-Based Automation:__ The system detects environmental conditions such as rain and wind, automatically closing the awning to prevent damage or water ingress.
- __Time-Based Automation:__ Define specific time intervals during which the awning should be open or closed, adapting to your schedule or daylight hours.
- __Remote Control Integration:__ The project includes support for a separate remote controller, allowing manual operation alongside automated functionality.

## Dependencies
- [RCSwitch lib](https://github.com/sui77/rc-switch/releases/tag/2.6.4)
- [Rtc_Pcf8563 lib](https://github.com/elpaso/Rtc_Pcf8563)
- [Wire lib](https://www.arduino.cc/reference/en/language/functions/communication/wire/)

# License

This project is licensed under the GPLv3 License - see the [LICENSE](LICENSE) file for details.

# Contributing

If you have suggestions or improvements, feel free to create a pull request or open an issue.
