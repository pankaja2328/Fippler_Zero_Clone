#include "MenuUI.h"
#include "ApScan.h" // Add this include
#include <WiFi.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Buttons
constexpr int BTN_UP     = 12;
constexpr int BTN_DOWN   = 14;
constexpr int BTN_SELECT = 27;

// Menu data
const char* menuItems[] = { 
    "Scan for WiFi Networks",
    "Deauthentication", 
    "Fake Access Points", 
    "WiFi Beacon Flooding", 
    "Probe Request Attacks", 
    "Packet Sniffing", 
    "Bluetooth Device Scanning & Tracking", 
    "Bluetooth Jamming", 
    "Mouse Jack Attacks", 
    "Man-in-the-Middle", 
    "BadUSB Attacks" 
};
constexpr size_t menuLength = sizeof(menuItems) / sizeof(menuItems[0]);
size_t selectedIdx = 0;
size_t topIdx = 0;

// Interrupt flags (volatile for ISR use)
volatile bool upFlag = false;
volatile bool downFlag = false;
volatile bool selectFlag = false;

// Interrupt Service Routines
void IRAM_ATTR onUp()     { upFlag = true; }
void IRAM_ATTR onDown()   { downFlag = true; }
void IRAM_ATTR onSelect() { selectFlag = true; }

void drawMenu() {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x13_mf);

    const size_t maxVisible = 4;
    if (selectedIdx < topIdx)      topIdx = selectedIdx;
    else if (selectedIdx >= topIdx + maxVisible) topIdx = selectedIdx - maxVisible + 1;

    for (size_t i = 0; i < maxVisible; ++i) {
        size_t itemIdx = topIdx + i;
        if (itemIdx >= menuLength) break;
        int y = 16 + i * 16;
        if (itemIdx == selectedIdx) {
            u8g2.setDrawColor(1);
            u8g2.drawBox(0, y - 12, 128, 14);
            u8g2.setDrawColor(0);
            u8g2.setCursor(4, y);
            u8g2.print(menuItems[itemIdx]);
            u8g2.setDrawColor(1);
        } else {
            u8g2.setCursor(4, y);
            u8g2.print(menuItems[itemIdx]);
        }
    }
    u8g2.sendBuffer();
}

void displayWiFiScanResults() {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x13_mf);

    int n = WiFi.scanNetworks();
    if (n == 0) {
        u8g2.setCursor(0, 16);
        u8g2.print("No networks found.");
    } else {
        for (int i = 0; i < n && i < 4; ++i) { // Show up to 4 networks
            String ssid = WiFi.SSID(i);
            int rssi = WiFi.RSSI(i);
            u8g2.setCursor(0, 16 + i * 12);
            u8g2.print(ssid);
            u8g2.print(" (");
            u8g2.print(rssi);
            u8g2.print(")");
        }
    }
    u8g2.sendBuffer();
    delay(3000); // Show results for 3 seconds
    drawMenu();  // Return to menu
}

void handleSelect(size_t idx) {
    Serial.print("Selected: ");
    Serial.println(menuItems[idx]);
    if (idx == 0) { // "Scan for WiFi Networks"
        displayWiFiScanResults();
    }
    // Add more actions for other menu items if needed
}

void menuSetup() {
    u8g2.begin();
    u8g2.clearDisplay();

    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_DOWN, INPUT_PULLUP);
    pinMode(BTN_SELECT, INPUT_PULLUP);

    // Attach interrupts (FALLING edge = button press)
    attachInterrupt(digitalPinToInterrupt(BTN_UP),     onUp,     FALLING);
    attachInterrupt(digitalPinToInterrupt(BTN_DOWN),   onDown,   FALLING);
    attachInterrupt(digitalPinToInterrupt(BTN_SELECT), onSelect, FALLING);

    drawMenu();
}

void menuLoop() {
    static uint32_t lastNav = 0;
    const uint32_t debounceDelay = 150; // ms

    // Handle UP button
    if (upFlag && (millis() - lastNav > debounceDelay)) {
        upFlag = false;
        if (selectedIdx > 0) {
            --selectedIdx;
            drawMenu();
        }
        lastNav = millis();
    }
    // Handle DOWN button
    if (downFlag && (millis() - lastNav > debounceDelay)) {
        downFlag = false;
        if (selectedIdx < menuLength - 1) {
            ++selectedIdx;
            drawMenu();
        }
        lastNav = millis();
    }
    // Handle SELECT button
    if (selectFlag && (millis() - lastNav > debounceDelay)) {
        selectFlag = false;
        handleSelect(selectedIdx);
        drawMenu();
        lastNav = millis();
    }

    delay(10);
}
