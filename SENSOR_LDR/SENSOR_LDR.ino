int ldr = A0;

int led_merah = 8;
int led_kuning = 9;
int led_hijau = 10;

// Variabel baru untuk menyimpan perintah dari Website (lewat Python)
char perintahWeb = '0'; 

void setup() {
  pinMode(led_merah, OUTPUT);
  pinMode(led_kuning, OUTPUT);
  pinMode(led_hijau, OUTPUT);

  Serial.begin(9600); // Membuka jalur komunikasi serial
}

void loop() {
  // 1. Sensor LDR tetap membaca dan menampilkan nilai di Serial Monitor
  int nilaiLDR = analogRead(ldr);
  Serial.print("Nilai LDR = ");
  Serial.println(nilaiLDR);

  // 2. CEK APAKAH ADA PERINTAH MASUK DARI PYTHON/WEBSITE
  if (Serial.available() > 0) {
    perintahWeb = Serial.read(); // Membaca karakter '1' atau '0' dari Python
  }

  // 3. LOGIKA KENDALI LAMPU (Sekaruh mengikuti tombol di Website)
  if (perintahWeb == '1') {   // Jika di website di-klik ON
    digitalWrite(led_merah, HIGH);
    digitalWrite(led_kuning, HIGH);
    digitalWrite(led_hijau, HIGH);
  } 
  else if (perintahWeb == '0') { // Jika di website di-klik OFF
    digitalWrite(led_merah, LOW);
    digitalWrite(led_kuning, LOW);
    digitalWrite(led_hijau, LOW);
  }

  delay(100);
}
