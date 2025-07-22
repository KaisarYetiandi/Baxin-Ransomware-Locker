# BAXIN Ransomware (Linux Terminal Locker)

Sebuah project ransomware berbasis terminal Linux — dirancang untuk keperluan testing, simulasi, dan riset keamanan siber.

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

## Disclaimer  
Tool ini dibuat hanya untuk edukasi, analisis, dan simulasi insiden keamanan.  
Dilarang digunakan untuk aktivitas ilegal atau tanpa izin pemilik sistem.  
Jalankan hanya di environment yang aman seperti Virtual Machine atau sandbox.

---

## Catatan tambahan  
• Tujuan utama adalah memahami konsep dasar ransomware interaktif  
• Support Telegram API secara penuh (custom bot/token)  
• Direkomendasikan untuk distro Linux berbasis Ubuntu/Debian/Arch

---

## Kontak  
Email: DarknessEmperor@proton.me
GitHub: github.com/EmperorYetiandi
