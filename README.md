# esp32-rgb-web-controller-project
A simple ESP32 project that lets you control an RGB LED through a responsive web interface over Wi-Fi. Supports color presets like red, green, blue, yellow, purple, cyan, white, and off — all with just a tap in your browser.

# ESP32 RGB Web Controller

A responsive and Wi-Fi-enabled RGB LED controller built using an ESP32. This project allows you to control the color of an RGB LED directly from a custom-designed webpage hosted on the ESP32 itself.

## Features

- Control RGB LED from any device connected to the same Wi-Fi network.
- Web interface with preset color buttons: Red, Green, Blue, Yellow, Purple, Cyan, White, and Off.
- Responsive design for phones, tablets, and desktops.
- Uses native ESP32 PWM channels for smooth color control.

## Hardware Requirements

- ESP32 development board
- Common anode/cathode RGB LED (with appropriate resistors)
- Breadboard & jumper wires
- Wi-Fi connection

## Software & Libraries

- [ESP32 core for Arduino](https://github.com/espressif/arduino-esp32)
- Arduino IDE
- Libraries:
  - `WiFi.h`
  - `WebServer.h`
  - `driver/ledc.h` (for PWM control)

## Pin Configuration

| LED Color | ESP32 Pin |
|-----------|-----------|
| Red       | 23        |
| Green     | 22        |
| Blue      | 21        |

