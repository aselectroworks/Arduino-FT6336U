#include "FT6336U.h"

#define I2C_SDA 22
#define I2C_SCL 23
#define RST_N_PIN 21
#define INT_N_PIN 34
#define DISPLAY_WIDTH 135
#define DISPLAY_HEIGHT 240

Touch ctp = Touch(DISPLAY_HEIGHT, DISPLAY_WIDTH, I2C_SDA, I2C_SCL, RST_N_PIN, INT_N_PIN);

void setup() {
    Serial.begin(115200);

    ctp.begin();
}

void loop() {
    if(ctp.touched()){
        TS_Point p = ctp.getPoint();
        Serial.print("Touch sensing: ");
        Serial.print(p.x);
        Serial.print(", ");
        Serial.print(p.y);
        Serial.println(".");
    }
}
