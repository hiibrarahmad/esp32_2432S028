#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <HardwareSerial.h>
#include "image_Data.h"  // Include the image data header

HardwareSerial SerialPort(2);

char receivedData[100];
int forceValues[10] = {0};  // Store force values in mN
int currentIndex = 0;
int timeStep = 1;
int currentTime = 0;
int latestForce = 0;
bool graphPage = true;  // Track the current page: graph or table
bool buttonState = false;  // Track ON/OFF state

TFT_eSPI tft = TFT_eSPI();
#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

const int rgbRedPin = 5;
const int rgbGreenPin = 18;
const int rgbBluePin = 19;

// Function Prototypes
void drawArrow(bool right);
void drawAxes();
void plotGraph();
void displayHeader();
void blinkLED();
void updateValues(int newForce);
void displayTable();
void toggleButton();

// Draw Header with Latest Value, REVIVE Label, Button, and Arrow
void displayHeader() {
    tft.fillRect(0, 0, 320, 40, TFT_WHITE);  // Clear header area

    // Display Latest Value
    tft.setCursor(10, 10);  // Positioned on the left side
    tft.setTextColor(TFT_BLACK);
    tft.print("Latest: ");
    tft.print(latestForce);
    tft.print(" mN");

    // Display REVIVE Label
    tft.setCursor(140, 10);  // Positioned next to the latest value
    tft.setTextColor(TFT_BLACK);
    tft.print("REVIVE");

    // Draw Button
    uint16_t buttonColor = buttonState ? TFT_GREEN : TFT_RED;
    tft.fillCircle(220, 20, 15, buttonColor);  // Button positioned after REVIVE label

    // Draw Arrow (page-specific)
    if (graphPage) {
        drawArrow(true);  // Right arrow for graph page
    } else {
        drawArrow(false);  // Left arrow for table page
    }
}

// Toggle Button State and Send ON/OFF Message
void toggleButton() {
    buttonState = !buttonState;  // Toggle state

    // Update Button Color
    uint16_t buttonColor = buttonState ? TFT_GREEN : TFT_RED;
    tft.fillCircle(220, 20, 15, buttonColor);

    // Send ON/OFF message via serial
    SerialPort.println(buttonState ? "ON" : "OFF");
}

// Draw Axes for Graph
void drawAxes() {
    tft.fillRect(40, 40, 260, 180, TFT_WHITE);
    tft.drawLine(40, 220, 300, 220, TFT_BLACK);  // X-axis
    tft.setCursor(310, 210);
    tft.print("Time");

    tft.drawLine(40, 220, 40, 40, TFT_BLACK);  // Y-axis
    tft.setCursor(5, 30);
    tft.print("Force (mN)");

    for (int i = 0; i <= 6; i++) {
        int yValue = i * 250;
        tft.drawLine(38, 220 - i * 30, 42, 220 - i * 30, TFT_BLACK);
        tft.setCursor(5, 215 - i * 30);
        tft.print(yValue);
    }
}

// Plot Graph with Color-Coded Points
void plotGraph() {
    int prevX = 40;
    int prevY = 220 - (forceValues[0] * 180 / 1500);

    for (int i = 1; i < 10; i++) {
        int x = 40 + i * 26;
        int y = 220 - (forceValues[i] * 180 / 1500);

        tft.drawLine(prevX, prevY, x, y, TFT_RED);  // Line connecting points

        // Determine point color based on value change
        uint16_t pointColor = (forceValues[i] > forceValues[i - 1]) ? TFT_GREEN
                                : (forceValues[i] < forceValues[i - 1]) ? TFT_RED
                                : TFT_WHITE;

        // Draw the point with the appropriate color
        tft.fillCircle(x, y, 3, pointColor);

        prevX = x;
        prevY = y;
    }
}

// Update Values and Graph/Table
void updateValues(int newForce) {
    for (int i = 1; i < 10; i++) {
        forceValues[i - 1] = forceValues[i];
    }
    forceValues[9] = newForce;
    latestForce = newForce;

    displayHeader();  // Update header

    if (graphPage) {
        tft.fillRect(41, 41, 259, 179, TFT_WHITE);
        drawAxes();
        plotGraph();
    } else {
        displayTable();  // Update the table view
    }

    blinkLED();
}

// Blink LED
void blinkLED() {
    digitalWrite(rgbRedPin, HIGH);
    delay(100);
    digitalWrite(rgbRedPin, LOW);
}

// Draw Arrow for Page Navigation
void drawArrow(bool right) {
    int x = right ? 290 : 10;  // Adjusted arrow position
    int y = 15;  // Align arrow vertically with other elements

    if (right) {
        tft.fillTriangle(x, y, x - 20, y - 10, x - 20, y + 10, TFT_BLACK);  // Right arrow
    } else {
        tft.fillTriangle(x, y, x + 20, y - 10, x + 20, y + 10, TFT_BLACK);  // Left arrow
    }
}

// Display Table View
void displayTable() {
    tft.fillScreen(TFT_WHITE);
    displayHeader();  // Ensure header is shown on the table page

    tft.setTextColor(TFT_BLACK);
    tft.setCursor(80, 50);
    tft.print("Force Values (mN)");

    for (int i = 0; i < 10; i++) {
        tft.setCursor(80, 80 + i * 20);
        tft.print("Time ");
        tft.print(currentTime - (10 - i - 1) * timeStep);
        tft.print(": ");
        tft.print(forceValues[i]);
        tft.print(" mN");
    }
}

// Setup Function
void setup() {
    pinMode(rgbRedPin, OUTPUT);
    pinMode(rgbGreenPin, OUTPUT);
    pinMode(rgbBluePin, OUTPUT);

    tft.init();
    tft.setRotation(1);
    touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    touchscreen.begin(touchscreenSPI);

    SerialPort.begin(115200, SERIAL_8N1, 16, 17);

    tft.fillScreen(TFT_WHITE);
    displayHeader();
    drawAxes();
}

// Loop Function
void loop() {
    while (SerialPort.available()) {
        char c = SerialPort.read();
        if (c == '/') {
            receivedData[currentIndex] = '\0';
            int forceValue = atoi(receivedData);
            updateValues(forceValue);
            currentIndex = 0;
            currentTime += timeStep;
        } else if (c != 't') {
            receivedData[currentIndex++] = c;
            if (currentIndex >= sizeof(receivedData) - 1) {
                currentIndex = sizeof(receivedData) - 1;
            }
        }
    }

    if (touchscreen.tirqTouched() && touchscreen.touched()) {
        TS_Point p = touchscreen.getPoint();
        p.x = map(p.x, 200, 3700, 1, 320);
        p.y = map(p.y, 240, 3800, 1, 240);

        if (p.x > 205 && p.x < 235 && p.y < 40) {
            toggleButton();  // Toggle button state
        }

        if (graphPage && p.x > 260 && p.x < 320 && p.y < 40) {
            graphPage = false;
            displayTable();
        } else if (!graphPage && p.x < 60 && p.y < 40) {
            graphPage = true;
            tft.fillScreen(TFT_WHITE);
            displayHeader();
            drawAxes();
            plotGraph();
        }
    }
}
