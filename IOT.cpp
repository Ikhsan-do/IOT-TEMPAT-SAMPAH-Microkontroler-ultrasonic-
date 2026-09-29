#include <Servo.h>

const int trigPin = 10;
const int echoPin = 9;
const int servoPin = 8;

Servo servoMotor;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servoMotor.attach(servoPin);
  servoMotor.write(0); // Posisi awal servo tertutup
  Serial.begin(9600);
  Serial.println("Sistem dimulai");
}

void loop() {
  long duration;
  int distance;

  // Kirim pulsa ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Hitung durasi pantulan dengan timeout 30ms
  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    distance = -1; // Tidak ada pantulan terdeteksi
  } else {
    distance = duration * 0.034 / 2; // Konversi ke cm
  }

  Serial.print("Durasi: ");
  Serial.print(duration);
  Serial.print(" | Jarak: ");
  if (distance == -1) {
    Serial.println("Tidak terdeteksi");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }

  // Jika jarak valid dan kurang dari 10 cm, buka servo
  if (distance > 0 && distance < 10) {
    Serial.println("Objek terdeteksi! Membuka servo...");
    servoMotor.write(90);  // Buka servo
    delay(3000);           // Tunggu 3 detik
    Serial.println("Menutup servo...");
    servoMotor.write(0);   // Tutup servo
    delay(500);            // Delay singkat sebelum membaca ulang
  }

  delay(200);
}