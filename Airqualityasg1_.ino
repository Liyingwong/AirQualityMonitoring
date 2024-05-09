#include <Wire.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h> 
#include "MQ135.h"

String apiKey = "ZH0MFBJAVY9SIRYL"; //Enter your Write API Key from ThingSpeak

const char* ssid = "UUMWiFi_Guest";
const char* password = NULL;
const char* server = "api.thingspeak.com";
const int sensorPin = 0;
int air_quality;

WiFiClient client;

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

  lcd.print("Hello World :)");
  delay(2000);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  lcd.setCursor(0,0);
  lcd.print("Connecting to: ");
  Serial.println(ssid);
  lcd.setCursor(0,1);
  lcd.println(ssid);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  lcd.clear();
  lcd.print("WiFi Connected");
  delay(1000);

}

void loop() {
  lcd.clear(); // Clear LCD screen at the beginning of each loop

  // Read humidity and temperature from DHT sensor
  float h = dht.readHumidity(); // Read humidity from DHT sensor
  float t = dht.readTemperature (); // Read temperature from DHT sensor
  // Read analog value from MQ135 sensor and convert to CO2 level
  int analogValue = analogRead(A0); // Read analog value from MQ135 sensor
  co2lvl = analogValue - 400; // Adjust for sensor offset
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
  if ((co2lvl >= 300) && (co2lvl <= 1400))
  {
    lcd.setCursor(0,1);
    lcd.print("Condition: Good ");
    Serial.println("Condition: Good");
  }
  else if ((co2lvl >= 1400) && (co2lvl <= 2000))
  {
    lcd.setCursor(0,1);
    lcd.print("Condition: Bad "); // Display custom character for bad air quality
    Serial.println("Condition: Bad");
  }
  else
  {
    lcd.setCursor(0,1);
    lcd.print("   Danger!");
    Serial.println("Condition: Danger");
  }

   if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(t);
    postStr += "&field2=";
    postStr += String(h);
    postStr += "&field3=";
    postStr += String(co2lvl);
    postStr += "\r\n\r\n";
    
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    
    Serial.println("Data sent to ThingSpeak");
   }
    client.stop();
  delay(2000); // Delay before next loop iteration
}

