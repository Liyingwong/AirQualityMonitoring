# Indoor Air Quality Monitoring System

This project is an indoor air quality monitoring system designed to measure and display key environmental parameters, including temperature, humidity, and CO2 levels. It utilizes an ESP8266 microcontroller, various sensors, and an LCD display for real-time data visualization. Additionally, the system sends the collected data to ThingSpeak for storage and further analysis.

## Features

- **Temperature Monitoring**: Utilizes a DHT22 sensor to measure ambient temperature.
- **Humidity Monitoring**: Utilizes a DHT22 sensor to measure relative humidity.
- **CO2 Level Monitoring**: Utilizes an MQ135 sensor to measure carbon dioxide (CO2) levels.
- **LCD Display**: Displays real-time environmental data on a 16x2 LCD screen.
- **Wi-Fi Connectivity**: Connects to a Wi-Fi network for data transmission to ThingSpeak.
- **ThingSpeak Integration**: Sends temperature, humidity, and CO2 level data to ThingSpeak for storage and visualization.

## Hardware Requirements

- ESP8266 microcontroller (e.g., NodeMCU)
- DHT22 temperature and humidity sensor
- MQ135 CO2 sensor
- 16x2 LCD display with I2C interface
- Jumper wires
- Breadboard

## Software Requirements

- Arduino IDE
- Required Libraries:
  - Wire.h
  - ESP8266WiFi.h
  - DHT.h
  - LiquidCrystal_I2C.h
  - MQ135.h

## Setup Instructions

1. **Hardware Setup**:
   - Connect the sensors and LCD display to the ESP8266 microcontroller as per the provided wiring diagram.
  
2. **Software Configuration**:
   - Install the required libraries in the Arduino IDE.
   - Open the Arduino sketch provided in this repository.
   - Replace placeholders in the sketch (e.g., Wi-Fi credentials, ThingSpeak API key) with your own information.

3. **Power On**:
   - Power on the system and monitor the readings displayed on the LCD screen.

4. **ThingSpeak Integration**:
   - Optionally, check the ThingSpeak channel associated with your API key for real-time and historical data visualization.

## Wiring Diagram

You may create schematic diagram or Fritzing diagram showing the wiring connections between the ESP8266, sensors, and LCD display.

## Contributing

Contributions to this project are welcomed! If you have any ideas for improvements or new features, feel free to open an issue or submit a pull request.

