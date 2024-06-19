#include <DHT.h>

float humidity = 0.0, temperature_c = 0.0;
const byte DHT_PIN = D1;
const byte DHT_TYPE = 22;
DHT dht(DHT_PIN, DHT_TYPE);

#define MQ_PIN A0
#define BUZZER_PIN D8
#define RELAY_TEMP_PIN D2
#define RELAY_HUMIDITY_PIN D7
#define FLAME_SENSOR_PIN D6
#define RELAY_FLAME_PIN D0

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_TEMP_PIN, OUTPUT);
  pinMode(RELAY_HUMIDITY_PIN, OUTPUT);
  pinMode(FLAME_SENSOR_PIN, INPUT);
  pinMode(RELAY_FLAME_PIN, OUTPUT);
}

void loop() {
  // Gas sensor
  int gasValue = analogRead(MQ_PIN);
  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  if (gasValue > 650) {
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("Gas detected! Buzzer activated.");
    delay(1000); // Buzzer on for 1 second
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Temperature and Humidity sensor
  humidity = dht.readHumidity();
  temperature_c = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature_c)) {
    Serial.println("Failed to read from DHT sensor");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(temperature_c);
  Serial.print("°C\t");
  Serial.println();

  // Relay for temperature
  if (temperature_c > 30) {
    digitalWrite(RELAY_TEMP_PIN, HIGH);
    Serial.println("Temperature above 30°C. Relay for temperature activated.");
  } else {
    digitalWrite(RELAY_TEMP_PIN, LOW);
  }

  // Relay for humidity
  if (humidity > 85) {
    digitalWrite(RELAY_HUMIDITY_PIN, HIGH);
    Serial.println("Humidity above 85%. Relay for humidity activated.");
  } else {
    digitalWrite(RELAY_HUMIDITY_PIN, LOW);
  }

  // Flame sensor
  int flameValue = digitalRead(FLAME_SENSOR_PIN);
  Serial.print("Flame Sensor Value: ");
  Serial.println(flameValue);

  // Relay for flame detection
  if (flameValue == HIGH) {
    digitalWrite(RELAY_FLAME_PIN, HIGH);
    Serial.println("Flame detected! Relay for flame activated.");
  } else {
    digitalWrite(RELAY_FLAME_PIN, LOW);
  }

  delay(2000); // Adjust the delay according to your needs
}
