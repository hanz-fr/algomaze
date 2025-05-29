
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>  // For _kbhit() and _getch()

// ANSI color codes for bright colors
const std::string colors[] = {
    "\033[31m", // Red
    "\033[33m", // Yellow
    "\033[32m", // Green
    "\033[36m", // Cyan
    "\033[34m", // Blue
    "\033[35m", // Magenta
};

const int colorsCount = sizeof(colors) / sizeof(colors[0]);

const std::string resetColor = "\033[0m";

// Function to print text with a typewriter-like animation effect with cycling colors
void animateText(const std::string& text, unsigned int millis_per_char = 50) {
    int colorIndex = 0;
    for (char c : text) {
        std::cout << colors[colorIndex] << c << resetColor << std::flush;
        colorIndex = (colorIndex + 1) % colorsCount;
        std::this_thread::sleep_for(std::chrono::milliseconds(millis_per_char));
    }
    std::cout << std::endl;
}

// Function to print text with a specific color
void printColoredText(const std::string& text, const std::string& color) {
    std::cout << color << text << resetColor << std::flush;
}

// Function to blink the entire text continuously in cycling colors until any key is pressed
void blinkTextUntilKeyPress(const std::string& text, unsigned int blink_delay_ms = 500) {
    std::cout << " " << std::endl;
    int colorIndex = 0;
    while (true) {
        if (_kbhit()) {
            // Clear the key pressed so it doesn't remain in buffer
            _getch();
            break;
        }

        // Print text in current color
        std::cout << "\r";
        printColoredText(text, colors[colorIndex]);
        colorIndex = (colorIndex + 1) % colorsCount;
        std::this_thread::sleep_for(std::chrono::milliseconds(blink_delay_ms));

        // Erase text by printing carriage return and spaces
        std::cout << "\r" << std::string(text.size(), ' ') << "\r" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(blink_delay_ms));
    }
    // Show text with last color before exit
    std::cout << "\r";
    printColoredText(text, colors[colorIndex]);
    std::cout << std::endl;
}