int ldr = A0;

int led_merah = 8;
int led_kuning = 9;
int led_hijau = 10;

void setup() {
  pinMode(led_merah, OUTPUT);
  pinMode(led_kuning, OUTPUT);
  pinMode(led_hijau, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  int nilaiLDR = analogRead(ldr);

  Serial.print("Nilai LDR = ");
  Serial.println(nilaiLDR);

  // Karena nilai LDR kamu hanya sekitar 0-5
  if (nilaiLDR > 4) {   // GELAP

    digitalWrite(led_merah, HIGH);
    digitalWrite(led_kuning, HIGH);
    digitalWrite(led_hijau, HIGH);

  } else {              // TERANG

    digitalWrite(led_merah, LOW);
    digitalWrite(led_kuning, LOW);
    digitalWrite(led_hijau, LOW);

  }

  delay(100);
}
