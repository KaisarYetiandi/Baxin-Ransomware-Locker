# BAXIN Ransomware 

Sebuah project ransomware berbasis terminal Linux — dirancang untuk keperluan testing

---

## Fitur utama  
• Mengunci terminal Linux dan menonaktifkan seluruh input keyboard  
• Tetap aktif meskipun korban melakukan restart atau logout  
• Komunikasi dua arah antara attacker dan korban lewat bot Telegram  
• Menggunakan ID korban unik untuk setiap komunikasi  
• Fitur self-destruct setelah berhasil di-unlock (menghapus jejak)  
• Persistence otomatis melalui .bashrc, .zshrc, .profile, dan crontab  
• Tampilan banner + animasi teks menyerupai ransomware asli

> Semua proses berjalan langsung dari terminal CLI, tanpa GUI

---

## Kelemahan  
• Tidak mengenkripsi file (fokus hanya pada lockscreen terminal)  
• Unlock code masih bersifat statis (belum dinamis)  
• Belum menggunakan teknik injection atau bypass advanced  
• Masih dalam tahap uji coba (early-stage development)

---

## Cara Build & Eksekusi

> Saatnya compile dan jalankan 💻

### 1. Install semua dependency:
```bash
sudo apt update && sudo apt install build-essential libcurl4-openssl-dev libjson-c-dev libx11-dev
```
Setelah itu compile menjadi file exe
```
gcc baxin.c -o baxin -lX11 -lcurl -ljson-c -lpthread
```
Jalankan
```
./baxin
```

## Disclaimer  
Tool ini dibuat hanya untuk edukasi, analisis, dan simulasi.
Dilarang digunakan untuk aktivitas ilegal

---

## Catatan tambahan  
• Tujuan utama adalah memahami konsep dasar ransomware interaktif  
• Support Telegram API secara penuh (custom bot/token)  
• Direkomendasikan untuk distro Linux berbasis Ubuntu/Debian/Arch dan Kali Linux

---

## Kontak  
Email: DarknesEmperor@proton.me
GitHub: github.com/EmperorYetiandi
