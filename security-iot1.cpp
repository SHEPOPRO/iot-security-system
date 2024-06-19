#include <DHT.h>

// DHT Sensor Configuration
float hum = 0.0, temp_c = 0.0, temp_f = 0.0;
const byte DHT_PIN = D1;
const byte DHT_TYPE = 22;
DHT dht(DHT_PIN, DHT_TYPE);

// Flame Sensor Configuration
const int flameSensorPin = D6;
const int relayPin = D7;
int thresholdValue = 500;

// Buzzer Configuration
int digital = 0;
const int buzzerPin = D0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Read DHT Sensor Data
  hum = dht.readHumidity();
  temp_c = dht.readTemperature();

  if (isnan(hum) || isnan(temp_c)) {
    Serial.println("Failed To Read From DHT Sensor");
  } else {
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print("%\t");
    Serial.print("Temperature: ");
    Serial.print(temp_c);
    Serial.print("°C\t");
  }

  // Flame Detection
  int sensorValue = analogRead(flameSensorPin);
  Serial.print("Flame Sensor Value: ");
  Serial.println(sensorValue);

  if (sensorValue > thresholdValue) {
    Serial.println("Flame detected!");
    digitalWrite(relayPin, HIGH); // Activate the relay
  } else {
    Serial.println("No flame detected");
    digitalWrite(relayPin, LOW);  // Deactivate the relay
  }

  // Buzzer Control
  digital = analogRead(A0);
  Serial.print("GAS Value: ");
  Serial.println(digital);

  if (digital > 950) {
    digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer
  } else {
    digitalWrite(buzzerPin, LOW);  // Turn off the buzzer
  }

  Serial.println(); // Print a new line for clarity
  delay(1000);
}
