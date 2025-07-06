#include "../include/countdown.h"
#include <thread>
#include <chrono>
#include <atomic>

// Variabel-variabel ini hanya akan terlihat di dalam file ini
namespace {
    std::atomic<bool> countdown_active(false);
    std::atomic<int> time_left_seconds(0);
    std::thread countdown_thread;
}

// Fungsi yang dijalankan oleh thread untuk menghitung mundur
void countdownWorker(int duration) {
    auto start_time = std::chrono::steady_clock::now();
    time_left_seconds = duration;

    while (countdown_active && time_left_seconds > 0) {
        // Cek setiap 100 milidetik agar lebih responsif saat dihentikan
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        auto now = std::chrono::steady_clock::now();
        int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();
        time_left_seconds = duration - elapsed;
    }
    
    if (countdown_active && time_left_seconds <= 0) {
        // Waktu benar-benar habis, biarkan countdown_active tetap true untuk menandakan kekalahan
    }
}

void startCountdown(int duration_seconds) {
    if (countdown_thread.joinable()) {
        countdown_active = false;
        countdown_thread.join();
    }
    countdown_active = true;
    countdown_thread = std::thread(countdownWorker, duration_seconds);
}

void stopCountdown() {
    countdown_active = false;
    if (countdown_thread.joinable()) {
        countdown_thread.join();
    }
}

bool isCountdownTimeUp() {
    // Waktu habis jika sudah tidak aktif DAN sisa waktunya 0 atau kurang
    return !countdown_active.load() && time_left_seconds.load() <= 0;
}

int getCountdownTimeLeft() {
    int time = time_left_seconds.load();
    return (time > 0) ? time : 0;
}