// Konfigurasi pin
const int voltagePin = A0;        // Input pembagi tegangan
const int relayPin = 8;           // Kontrol relay
const int ledPin = 13;            // Indikator LED

// Parameter tegangan
const float vMax = 14.4;          // Batas atas (full)
const float vMin = 12.0;          // Batas bawah (mulai isi)

// Kalibrasi pembagi tegangan
const float voltageDividerRatio = 5.0 / (5.0 * (10.0 + 2.0) / 2.0); // ganti sesuai resistor

float readBatteryVoltage() {
  int analogValue = analogRead(voltagePin);
  float voltage = analogValue * (5.0 / 1023.0);
  float batteryVoltage = voltage * ((10.0 + 2.0) / 2.0); // Ubah sesuai resistor divider
  return batteryVoltage;
}

void setup() {
  pinMode(voltagePin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float batteryVoltage = readBatteryVoltage();
  Serial.print("Tegangan Aki: ");
  Serial.println(batteryVoltage);

  if (batteryVoltage >= vMax) {
    digitalWrite(relayPin, LOW);  // Matikan charger
    digitalWrite(ledPin, LOW);    // Indikator OFF
  } else if (batteryVoltage <= vMin) {
    digitalWrite(relayPin, HIGH); // Aktifkan charger
    digitalWrite(ledPin, HIGH);   // Indikator ON
  }

  delay(1000); // Cek setiap 1 detik
}