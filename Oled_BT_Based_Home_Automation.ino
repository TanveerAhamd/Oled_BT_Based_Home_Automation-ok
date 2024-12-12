#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_I2C_ADDR 0x3C
#define OLED_RST_PIN -1

String inputString = "";
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RST_PIN);

// Track the state of each load
bool load1 = false;
bool load2 = false;
bool load3 = false;
bool load4 = false;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDR);
  Serial.begin(9600);

  // Initialize the OLED display
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
    display.setCursor(0, 0);
  display.println("SMART");
  display.setCursor(0, 25);
  display.println("HOME");
  display.setCursor(0, 45);
  display.println("Automation");
  display.display();
  delay(3000);
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("@TICER");
  display.setCursor(0, 20);
  display.println("ROBOTICS");
  display.setCursor(0, 40);
  display.println("CLUB LDN");
  display.display();
  delay(3000);


  // Initialize pins for loads
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);

  // Display initial load statuses
  updateDisplay();
}

void loop() {
  if (Serial.available()) {
    inputString = Serial.readStringUntil('\n'); // Read input until newline character
    inputString.trim();                        // Remove whitespace and newline

    Serial.println("Received: " + inputString);

    // Update load states based on commands
    if (inputString == "a") {
      load1 = true;
      digitalWrite(10, LOW);
    } else if (inputString == "A") {
      load1 = false;
      digitalWrite(10, HIGH);
    } else if (inputString == "b") {
      load2 = true;
      digitalWrite(11, LOW);
    } else if (inputString == "B") {
      load2 = false;
      digitalWrite(11, HIGH);
    } else if (inputString == "c") {
      load3 = true;
      digitalWrite(12, LOW);
    } else if (inputString == "C") {
      load3 = false;
      digitalWrite(12, HIGH);
    } else if (inputString == "d") {
      load4 = true;
      digitalWrite(13, LOW);
    } else if (inputString == "D") {
      load4 = false;
      digitalWrite(13, HIGH);
    }

    // Update the OLED display with the new statuses
    updateDisplay();
    inputString = "";
  }
}

void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(32, 5);
  display.println("LOAD STATUS:");

  // Display the status of each load
  display.setCursor(0, 20);
  display.print("Load 1:");
  display.println(load1 ? "ON" : "OFF");

  display.setCursor(0, 35);
  display.print("Load 2:");
  display.println(load2 ? "ON" : "OFF");

  display.setCursor(65, 20);
  display.print("Load 3:");
  display.println(load3 ? "ON" : "OFF");

  display.setCursor(65, 35);
  display.print("Load 4:");
  display.println(load4 ? "ON" : "OFF");

  display.setCursor(0, 52);
  display.println("TICER Robotic-Club LD");
  display.display();
}
