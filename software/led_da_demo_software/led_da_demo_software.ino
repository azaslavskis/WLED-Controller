#include <ESP32_WS2812_Lib.h>
#include <INA219.h>
#include <DS18B20.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Pin Definitions
#define SDA_PIN 4      // I2C SDA Pin
#define SCL_PIN 5      // I2C SCL Pin
#define ONE_WIRE_PIN 10 // OneWire data pin for DS18B20 sensors
#define LEDS_COUNT 8    // Number of LEDs in the WS2812 strip
#define LEDS_PIN 2      // Pin for WS2812 LED strip
#define CHANNEL 0       // LED channel for ESP32
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D  // Address for 128x64 OLED

// Global Objects
DS18B20 ds(ONE_WIRE_PIN);                        // Initialize DS18B20 sensor on the defined pin
ESP32_WS2812 strip = ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB); // WS2812 LED strip object
INA219 INA(0x40);                               // INA219 power sensor object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // OLED display object

void setup() {
  // Initialize Serial Communication
  Serial.begin(115200);
  Serial.println("[DEBUG] Serial initialized");

  // Initialize I2C
  Wire.setPins(SDA_PIN, SCL_PIN);
  Wire.begin();
  Serial.println("[DEBUG] I2C initialized");

  // Initialize INA219 Sensor
  if (!INA.begin()) {
    Serial.println("[ERROR] INA219 initialization failed");
  } else {
    INA.setMaxCurrentShunt(5, 0.002); // Configure shunt resistor
    Serial.println("[DEBUG] INA219 configured");
  }

  // Initialize OneWire DS18B20 Sensor
  Serial.println("[DEBUG] Scanning OneWire sensors...");
  int numDevices = ds.getNumberOfDevices(); // Scan for DS18B20 devices
  Serial.print("Devices found: ");
  Serial.println(numDevices);

  // Initialize OLED Display
  if (!display.begin(SSD1306_I2C_ADDRESS, SCREEN_ADDRESS)) {
    Serial.println("[ERROR] SSD1306 initialization failed");
    for (;;); // Halt execution if OLED initialization fails
  }
  display.display();  // Show splash screen
  delay(2000);        // Pause for 2 seconds
  display.clearDisplay();
  Serial.println("[DEBUG] OLED initialized");

  // Draw initial pixel on the display
  display.drawPixel(10, 10, SSD1306_WHITE);
  display.display();
}

void loop() {
  // Log INA219 Voltage and Current Readings
  Serial.println("[INFO] INA219 Readings:");
  Serial.print("Voltage: ");
  Serial.print(INA.getBusVoltage());
  Serial.print(" V, Current: ");
  Serial.print(INA.getCurrent());
  Serial.println(" mA");

  // Log Number of OneWire Sensors
  Serial.print("[INFO] DS18B20 Sensors Found: ");
  Serial.println(ds.getNumberOfDevices());

  // Blink an LED on pin 3
  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(3, LOW);
  delay(1000);

  // Update WS2812 LED Strip
  strip.setBrightness(0);          // Set brightness to minimum
  strip.setAllLedsColor(0, 0, 255); // Set all LEDs to blue
  strip.show();
  delay(1000);                     // Wait for 1 second

  strip.setBrightness(255);        // Set brightness to maximum
  strip.setAllLedsColor(0, 0, 255); // Keep LEDs blue
  strip.show();
  delay(1000);

  // Display Temperature Reading on OLED
  if (ds.getNumberOfDevices() > 0) {
    float temperature = ds.getTempC();
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Temperature: ");
    display.print(temperature);
    display.print(" C");
    display.display();
  } else {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.print("No DS18B20 sensors found");
    display.display();
  }

  delay(1000);  // Wait 1 second before next loop iteration
}
