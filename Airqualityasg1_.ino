#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h> 
#include "MQ135.h"

// Define pin constants
#define DHTPIN D5     // Pin for DHT22 sensor
#define DHTTYPE DHT22 // DHT sensor type (DHT22)

// Initialize DHT and LCD objects
DHT dht (DHTPIN, DHTTYPE); // Create a DHT object for temperature and humidity sensor (DHT22)
LiquidCrystal_I2C lcd(0x27, 16, 2); // Create an LCD object for the I2C interface

int co2lvl;          // Variable to store CO2 level

void setup () {
  // Initialize LCD, DHT sensor, and serial communication
  lcd.init();  
  dht.begin ();
  Serial.begin (9600);
  // Turn on LCD backlight and clear the screen
  lcd.backlight();
  lcd.clear();
  delay(1000);
  lcd.clear(); // Clear again after a delay
}

void loop() {
  lcd.clear(); // Clear LCD screen at the beginning of each loop

  // Read humidity and temperature from DHT sensor
  float h = dht.readHumidity(); // Read humidity from DHT sensor
  float t = dht.readTemperature (); // Read temperature from DHT sensor
  // Read analog value from MQ135 sensor and convert to CO2 level
  int analogValue = analogRead(A0); // Read analog value from MQ135 sensor
  co2lvl = analogValue - 600; // Adjust for sensor offset
  co2lvl = map(co2lvl, 0, 1024, 400, 5000); // Map analog reading to CO2 range

  // Check for NaN (not a number) readings
  if (isnan(h) || isnan (t) || isnan (co2lvl)) {
    Serial.println("Failed to read fron DHT sensor!"); 
    return;
  }
  // Print readings to serial monitor
  Serial.print ("Humidity: ");
  Serial.print (h);
  Serial.print (" %\t");
  Serial.print ("Temperature: ");
  Serial.print (t);
  Serial.print (" *C ");
  Serial.println("");
  Serial.print("CO2: ");
  Serial.print(co2lvl);
  Serial.println(" PPM");

  // Display readings on LCD
  lcd.setCursor(0,0);
  lcd.print("Humi :");
  lcd.print(h);
  lcd.print(" %");

  lcd.setCursor(0,1);
  lcd.print("Temp :");
  lcd.print(t);
  lcd.print(" C");

  delay(2000); // Delay to read before updating LCD

  lcd.clear(); // Clear screen before displaying CO2 reading

  lcd.setCursor(0,0);
  lcd.print("CO2 :");
  lcd.print(co2lvl);
  lcd.print(" PPM");

  // Display air quality status based on CO2 level
  if ((co2lvl >= 350) && (co2lvl <= 1400))
  {
    lcd.setCursor(0,1);
    lcd.print("  Good ");
    lcd.write(byte(0)); // Display custom character for good air quality
  }
  else if ((co2lvl >= 1400) && (co2lvl <= 2000))
  {
    lcd.setCursor(0,1);
    lcd.print("  Bad "); // Display custom character for bad air quality
    lcd.write(byte(1));
  }
  else
  {
    lcd.setCursor(0,1);
    lcd.print(" Danger!");
  }
  delay(2000); // Delay before next loop iteration
}
