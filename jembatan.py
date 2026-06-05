import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import serial  # Library untuk komunikasi ke Arduino
import time

# =========================================================================
# 1. KONFIGURASI ARDUINO (GANTI 'COM5' SUEUAI DENGAN PORT DI ARDUINO IDE KAMU!)
# =========================================================================
PORT_ARDUINO = 'COM5' 

try:
    arduino = serial.Serial(PORT_ARDUINO, 9600, timeout=1)
    time.sleep(2)  # Beri waktu 2 detik agar koneksi serial stabil
    print(f"[INFO] Berhasil terhubung ke Arduino di {PORT_ARDUINO}!")
except Exception as e:
    print(f"[ERROR] Gagal terhubung ke Arduino di {PORT_ARDUINO}. Periksa kabel USB! \nDetail: {e}")
    arduino = None

# 2. Hubungkan ke Firebase
cred = credentials.Certificate("kunci-firebase.json")
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://project-akhir-inotek-default-rtdb.asia-southeast1.firebasedatabase.app'
})

print("\n=== JEMBATAN PYTHON KONEKSI PENUH AKTIF ===")
print("Mencoba mendengarkan perubahan data dari Website...\n")

# 3. Fungsi pemicu saat tombol di website diklik
def pemicu_perubahan(event):
    status = event.data
    if status is not None:
        if status == 1:
            print(f"[INFO] Website mengubah data menjadi: {status}")
            if arduino:
                arduino.write(b'1')  # Kirim karakter '1' lewat kabel USB ke Arduino
                print("       -> Perintah '1' (NYALA) terkirim ke Arduino.")
        elif status == 0:
            print(f"[INFO] Website mengubah data menjadi: {status}")
            if arduino:
                arduino.write(b'0')  # Kirim karakter '0' lewat kabel USB ke Arduino
                print("       -> Perintah '0' (MATI) terkirim ke Arduino.")

# Jalankan pemantauan Firebase
db.reference('status_lampu').listen(pemicu_perubahan)

while True:
    time.sleep(1)