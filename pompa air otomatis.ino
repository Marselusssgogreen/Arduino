// Pin definisi
const int soilSensorPin = A0;  // Pin sensor kelembaban tanah
const int pumpPin = 8;         // Pin untuk relay pompa air (jangan dipakai takut error)
const int greenLedPin = 2;     // Pin LED hijau (tanah basah)
const int redLedPin = 4;       // Pin LED merah (tanah kering)
const int extraRedLedPin = 5;  // Ini sebenarnya bukan Pin LED melainkan untuk pompa airnya. Ini idenya Wilson kalau ada apa-apa tanya dia
// Ketika LED hijau dan merah terbalik, cukup kalian tukar posisi pin nya

const int wetThreshold = 300;    // Ambang batas untuk tanah basah
const int dryThreshold = 700;    // Ambang batas untuk tanah kering
unsigned long lastWateringTime = 0;
unsigned long wateringInterval = 10000;

void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(9600);

  // Konfigurasi pin
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, HIGH);

  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(extraRedLedPin, OUTPUT); // Konfigurasi untuk Pompa Airnya nanti

  Serial.println("Sistem monitoring kelembaban tanah dimulai...");
}

void loop() {
  int soilMoisture = analogRead(soilSensorPin);  // Membaca nilai kelembaban tanah

  // Tampilkan nilai kelembaban tanah di Serial Monitor
  Serial.print("Nilai kelembaban tanah: ");
  Serial.println(soilMoisture);

  // Logika untuk mengontrol LED dan pompa berdasarkan kelembaban tanah
  if (soilMoisture < wetThreshold) {
    // Tanah basah (LED hijau menyala)
    Serial.println("Status: Tanah basah (LED hijau menyala)");
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    digitalWrite(extraRedLedPin, LOW); // Matikan LED merah tambahan
    digitalWrite(pumpPin, HIGH); // Pastikan pompa mati
  } else if (soilMoisture >= wetThreshold && soilMoisture <= dryThreshold) {
    // Tanah sedang (tidak ada LED yang menyala), tetapi hasil praktik dua-duanya bakal nyala
    Serial.println("Status: Tanah sedang (tidak ada LED yang menyala)");
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(extraRedLedPin, LOW); // Matikan LED merah tambahan
    digitalWrite(pumpPin, HIGH); // Pastikan pompa mati
  } else {
    // Tanah kering (LED merah menyala dan pompa aktif)
    Serial.println("Status: Tanah kering (LED merah menyala dan pompa aktif)");
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    digitalWrite(extraRedLedPin, HIGH); // Pompa Air Hidup

    
    if (millis() - lastWateringTime > wateringInterval) {
      Serial.println("Pompa aktif: Menyiram tanaman...");
      digitalWrite(pumpPin, LOW);  
      delay(5000);                 
      digitalWrite(pumpPin, HIGH); 
      lastWateringTime = millis(); 
      Serial.println("Pompa mati: Penyiraman selesai.");
    }
  }

  // Debugging LED dan pompa
  Serial.print("LED hijau: ");
  Serial.println(digitalRead(greenLedPin) ? "ON" : "OFF");
  Serial.print("LED merah: ");
  Serial.println(digitalRead(redLedPin) ? "ON" : "OFF");
  Serial.print("LED merah tambahan: ");
  Serial.println(digitalRead(extraRedLedPin) ? "ON" : "OFF");
  Serial.print("Pompa: ");
  Serial.println(digitalRead(pumpPin) ? "OFF" : "ON");

  delay(1000); // Tunggu 1 detik sebelum membaca ulang
}
