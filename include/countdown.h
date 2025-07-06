#ifndef COUNTDOWN_H
#define COUNTDOWN_H

// Memulai timer hitung mundur dengan durasi tertentu
void startCountdown(int duration_seconds);

// Menghentikan timer secara paksa (misal saat pemain menang atau keluar)
void stopCountdown();

// Mengecek apakah waktu sudah habis
bool isCountdownTimeUp();

// Mendapatkan sisa waktu dalam detik
int getCountdownTimeLeft();

#endif