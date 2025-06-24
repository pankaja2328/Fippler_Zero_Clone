#pragma once
#include <Arduino.h>
#include <U8g2lib.h>

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

void menuSetup();
void menuLoop();
void drawMenu();
bool readButton(int pin);
void handleSelect(size_t idx);

// Expose menu indices if you want
extern const char* menuItems[];
extern size_t selectedIdx;
constexpr size_t menuLength = 11;
extern size_t topIdx;