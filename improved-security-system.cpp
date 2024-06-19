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

// Gas Sensor Configuration
const int gasSensorPin = A0;
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
  int flameValue = analogRead(flameSensorPin);
  Serial.print("Flame Sensor Value: ");
  Serial.println(flameValue);

  // Gas Detection
  int gasValue = analogRead(gasSensorPin);
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  if (flameValue > thresholdValue || gasValue > 950) {
    Serial.println("Flame or Gas detected!");
    digitalWrite(relayPin, HIGH); // Activate the relay
    digitalWrite(buzzerPin, HIGH); // Activate the buzzer
  } else {
    Serial.println("No flame or gas detected");
    digitalWrite(relayPin, LOW);  // Deactivate the relay
    digitalWrite(buzzerPin, LOW);  // Deactivate the buzzer
  }

  Serial.println(); // Print a new line for clarity
  delay(1000);
}
