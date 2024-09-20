#include <LiquidCrystal.h>

// LCD display variables
const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// SR04 Ultrasonic Sensor variables
const int trigPin = 7;
const int echoPin = 8;
float duration, distance;

// LED variables
unsigned long previousLedTime = 0;
bool ledState = LOW;
const int ledPin = 2;

// Passive buzzer variables
const int buzzerPin = 9;

// Function to get distance from the ultrasonic sensor
double getDistance() {
    // Trigger the ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure the time for the echo to return
    duration = pulseIn(echoPin, HIGH);

    // Calculate the distance based on the time
    distance = (duration * 0.0343) / 2;
    return distance;
}

// Function to handle inactive alarm state
void alarmInactive() {
    lcd.setCursor(0, 0);
    lcd.print("DISTANCE IS SAFE ");
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
}

// Function to blink the LED at a defined speed
void ledBlink(int periodMs) {
    if (millis() - previousLedTime >= periodMs) {
        previousLedTime = millis();
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
    }
}

// Function to handle triggered alarm state
void alarmTriggered() {
    lcd.setCursor(0, 0);
    lcd.print("ALARM TRIGGERED!");

    if (distance <= 15.0) {
        digitalWrite(ledPin, HIGH);
        tone(buzzerPin, 400);
    }
    
    if (distance <= 10.0 && distance > 5.0) {
        ledBlink(600);
        tone(buzzerPin, 300);
    } 
    else if (distance <= 5.0) {
        ledBlink(200);
        tone(buzzerPin, 200);
    }
}

// Function to display distance on the LCD
void displayLCD(double distance) {
    lcd.setCursor(0, 1);
    lcd.print("Distance:");
    lcd.print(distance);
    lcd.print("cm");
}
