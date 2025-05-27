#ifndef WELCOME_PRESS_ANY_KEY_H
#define WELCOME_PRESS_ANY_KEY_H

#include <string>

void animateText(const std::string& text, unsigned int millis_per_char = 50);
void printColoredText(const std::string& text, const std::string& color);
void blinkTextUntilKeyPress(const std::string& text, unsigned int blink_delay_ms = 500);

#endif