#include "AlarmFunctions.h"

unsigned long previousMillis = 0; // Store the last time the loop was updated
const long interval = 500;        //Time interval to update loop

void setup() {
    // Initialize LCD display
    lcd.begin(16, 2);

    // Configure LED
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    // Configure SR04 Ultrasonic Sensor
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(9600);

    // Configure passive buzzer
    pinMode(buzzerPin, OUTPUT);
}

void loop() {
    unsigned long currentMillis = millis();

    // Check if the interval has passed
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis; // Save the last time the loop was updated

        // Clear LCD screen for new readings
        lcd.clear();

        // Get the distance measurement
        double distance = getDistance();

        // Check distance and trigger appropriate alarm
        if (distance <= 15.0) {
            alarmTriggered();
        } else {
            alarmInactive();
        }

        // Display the distance on the LCD
        displayLCD(distance);
    }
}
