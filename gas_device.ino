#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h> // For SIM800L communication

// Define pins
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 8;
const int led1Pin = 7; // For red LED 
const int led2Pin = 6; // For yellow LED 
 
// Define SIM800L pins
const int rxPin = 12;
const int txPin = 13;

// Create LCD and SIM800L objects
LiquidCrystal_I2C lcd(0x3F, 16, 2);  // Adjust I2C address if needed
SoftwareSerial sim800l(rxPin, txPin);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
lcd.init();
lcd.backlight();
  lcd.begin(16,2);
  sim800l.begin(9600);  // Start SIM800L communication
}

void loop() {
  long duration, distanceCm;

  // Measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;

  // Display distance on LCD
  lcd.clear();
  lcd.print("Distance: ");
  lcd.print(distanceCm);
  lcd.print(" cm");

  // Check distance and take actions
  if (distanceCm < 10) { //for red led 
    // Beep buzzer once
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);

    // Blink LED for 1 second
    digitalWrite(led1Pin, HIGH);
    delay(1000);
    digitalWrite(led1Pin, LOW);

    // Send "high alert" SMS
    makeCall();
    sendSMS("+919149374020", " Jabtagunj ward-01-1S is now going to over flow.");
    sendSMS("+918077940900", "Jabtagunj ward-01-1S is now going to over flow.");
    
  } else if (distanceCm < 40) { //for yellow led
   // Beep buzzer once
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);

    // Blink LED for 1 second
    digitalWrite(led2Pin, HIGH);
    delay(1000);
    digitalWrite(led2Pin, LOW);
   
    // Send "alert" SMS
    sendSMS("+919149374020", "Jabtagunj ward-01-1S is need to clean.");
  }

  delay(500);  // Delay between readings
}

void sendSMS(String phoneNumber, String message) {
  sim800l.print("AT+CMGF=1\r");  // Set SMS mode to text
  delay(1000);
  sim800l.print("AT+CMGS=\"");
  sim800l.print(phoneNumber);
  sim800l.println("\"");
  delay(1000);
  sim800l.println(message);
  delay(1000);
  sim800l.println((char)26);  // Send SMS command
  delay(1000);
}
void makeCall() {
  sim800l.println("ATD+918077940900;"); // Replace with your number
  delay(100); // Adjust the delay based on your needs
}  give me name for this project
