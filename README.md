# 🚪 Door Monitoring System Overview

This setup involves two main components:
1. **Arduino script** for monitoring the door's state.
2. **ESP32 script** that handles WiFi connectivity to send notifications via a web service (IFTTT) when the door state changes.

The Arduino script utilizes sensors to detect and indicate the door's status, while the ESP32 handles WiFi connectivity and HTTP requests.

## 🛠 Arduino Code Explanation

### Hardware Components & Pins

- **I2C LCD Display**: Connected via I2C with an address of `0x27`, configured with 16 columns and 2 rows.
- **Door Sensor**: Attached to pin `2` for detecting door open/close states.
- **Buzzer**: Attached to pin `3` to sound an alert when the door opens.
- **RGB LED**: Connected to pins `9` (red), `10` (green), and `11` (blue) for visual status indication.

### Modules & Header Files

- `Wire.h`: Manages I2C communication for the LCD display.
- `LiquidCrystal_I2C.h`: Controls the LCD.

### Main Functions

- **Setup**: Initializes serial communication, sets up pin modes, initializes the LCD, and sets the RGB LED to blue (indicative of system ready).
- **doorControl**: Checks the door's state, updates the LCD and RGB LED colors accordingly, and controls the buzzer. It also sends the door state ("OPEN" or "CLOSED") via serial.
- **setColor**: Adjusts the RGB LED color by controlling the PWM outputs to each pin.

## 🌐 ESP32 Code Explanation

### Modules & Header Files

- `WiFi.h`: Manages all WiFi-related functionalities.

### Configuration Details

- **SSID and Password**: Credentials for connecting to the WiFi network.
- **Host**: URL of the IFTTT service for sending notifications.

### Main Functions

- **Setup**: Establishes serial communication, connects to the WiFi network, and initiates a connection to the IFTTT host.
- **Logic Flow**: Waits for serial input from the Arduino which indicates the door state. If "OPEN", it sends a request to IFTTT.

### Serial Communication Between Arduino and ESP32

- **Arduino**: Sends a string "OPEN" or "CLOSED" based on the door state.
- **ESP32**: Reads the incoming serial data, processes it, and triggers actions based on the content.

## 📋 Summary

This system is designed for integrated IoT applications where local monitoring (via Arduino) and remote notifications (via ESP32 and WiFi) are required. The setup is ideal for home security systems where immediate alerts and remote notifications are crucial.
