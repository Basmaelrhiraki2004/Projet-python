#include "DHT.h"
#include <ESP32Servo.h>
#define DHTPIN 4      // Pin connecté au DHT22
#define DHTTYPE DHT22 // Type de capteur
#define LEDPIN 2      // Pin connecté à la LED
#define SERVOPIN 16   // Pin connecté au servo

DHT dht(DHTPIN, DHTTYPE);
Servo myServo;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(LEDPIN, OUTPUT);
  myServo.attach(SERVOPIN);
  myServo.write(0); // Initialiser le servo à 0°
}

void loop() {
  // Lecture des données du capteur DHT22
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Erreur de lecture du DHT22");
    return;
  }

  // Affichage des données
  Serial.print("Température: ");
  Serial.print(temperature);
  Serial.print("°C  |  Humidité: ");
  Serial.print(humidity);
  Serial.println("%");

  // Contrôle de la LED
  if (temperature > 30.0) {
    digitalWrite(LEDPIN, HIGH); // Allume la LED si la température dépasse 30°C
  } else {
    digitalWrite(LEDPIN, LOW);
  }

  // Contrôle du servo en fonction de l'humidité
  int servoAngle = map(humidity, 0, 100, 0, 180); // Convertit l'humidité en angle (0° à 180°)
  myServo.write(servoAngle);

  delay(2000); // Attente de 2 secondes avant la prochaine lecture
}
