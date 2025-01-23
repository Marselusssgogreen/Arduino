// Pastikan aplikasi arduino mempunyai pustaka servo kalau tidak error terus seperti tadi
#include <Servo.h>

// Ini untuk mendefinisikan pin nya sensor ultrasonik ya
const int trigPin = 5;
const int echoPin = 7;

// Ini untuk mendefinisikan pin motor servo 
const int servoPin = 9;

// Ini untuk mendefinisikan pin lampu LED ini idenya Wilson 
const int ledPin = 13;

// Membuat Objek Servo
Servo servo;

// Mendefinisikan variabel durasi dan jarak
long duration;
int distance;

void setup() {
  // Menginisialisasi pin servo
  servo.attach(servoPin);

  // Mengatur pin sensor ultrasonik
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Untuk mengatur lampu LED
  pinMode(ledPin, OUTPUT);

  // Buat mindahin posisi servo ke posisi tutup 0 derajat jangan diganggu gugat
  servo.write(0);

  // Ini untuk memulai komunikasi di debugging atau serial monitor
  Serial.begin(9600);
}

void loop() {
  // Untuk menghasilkan gelombang ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Untuk mengukur pantulan gelombang ultrasonik
  duration = pulseIn(echoPin, HIGH);

  // Untuk menghitung jarak dalam satuan cm bukan km ya
  distance = duration * 0.034 / 2;

  // Ini untuk serial monitor ya, jika tidak paham tanya Wilson
  Serial.print("Jarak Objek bukan Jarak Cinta: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Membuka tempat sampah dengan jarak yang ditentukan, Wilson rekomendasikan 20 cm
  if (distance <= 20) {
    digitalWrite(ledPin, HIGH); // Ini untuk menghidupin lampu led nya ya
    servo.write(90);           // Posisi membuka dari motor servo nya, jangan diubah dan pastikan 90 derajat, jika ketahuan Wilson bisa ditindak itu
    delay(3000);               // Membuka tempat sampah selama 3 detik, yang ini Wilson izinkan untuk dikustomisasi
    servo.write(0);            // Posisi menutup dari motor servo, 0 derajat dan jangan diganggu atau rusak
    digitalWrite(ledPin, LOW); // Mematikan lampu LED
  }

  // Ini untuk kecepatan refresh sensornya
  delay(10);
}
