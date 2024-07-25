#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>
#include <TimerFreeTone.h>

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 200 // Maximum distance to measure (in cm)
#define BUZZER_PIN 7
#define LED_PIN 6

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialize with the I2C address of the display
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  delay(50);
  unsigned int distance = sonar.ping_cm();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Water Level: ");
  display.print(distance);
  display.print(" cm");

  if (distance <= 10) {  // Low water level
    display.setCursor(0, 10);
    display.print("Water level LOW!");
    TimerFreeTone(BUZZER_PIN, 1000, 200); // Buzzer ON
    digitalWrite(LED_PIN, HIGH); // LED ON
  } else {
    TimerFreeTone(BUZZER_PIN, 0, 0);  // Buzzer OFF
    digitalWrite(LED_PIN, LOW); // LED OFF
  }

  display.display();
}
