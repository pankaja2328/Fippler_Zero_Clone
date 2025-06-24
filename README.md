# Fippler Zero Clone

A WiFi and Bluetooth attack/utility toolkit for ESP32 with OLED display and button navigation.

## Features

- **Menu-driven UI** on OLED (SSD1306 128x64)
- **WiFi Scanning:** Scan and display nearby WiFi networks
- **Deauthentication**
- **Fake Access Points**
- **WiFi Beacon Flooding**
- **Probe Request Attacks**
- **Packet Sniffing**
- **Bluetooth Device Scanning & Tracking**
- **Bluetooth Jamming**
- **Mouse Jack Attacks**
- **Man-in-the-Middle**
- **BadUSB Attacks**

## Hardware Requirements

- ESP32 development board
- SSD1306 128x64 OLED display (I2C)
- 3 push buttons (UP, DOWN, SELECT) connected to GPIO 12, 14, 27 (default)

## Getting Started

1. **Clone this repository**  
   ```sh
   git clone https://github.com/yourusername/FipplerC.git
   ```

2. **Open with [PlatformIO](https://platformio.org/) in VS Code**

3. **Wiring**
   - Connect OLED to ESP32 I2C pins (usually SDA=21, SCL=22)
   - Connect buttons to GPIO 12 (UP), 14 (DOWN), 27 (SELECT) with pull-up resistors

4. **Build and Upload**
   - Click the PlatformIO "Upload" button or run:
     ```sh
     pio run --target upload
     ```

5. **Usage**
   - Use the buttons to navigate the menu.
   - Select "Scan for WiFi Networks" to scan and display nearby networks on the OLED.

## License

MIT License

---

**Disclaimer:**  
This project is for educational and research purposes only. Use responsibly and only on networks/devices you own or have permission to
