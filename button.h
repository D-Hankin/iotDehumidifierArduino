#include <Arduino_LED_Matrix.h>
#include "numbers.h"

int buttonPin = 7;
int buttonState = 0;
ArduinoLEDMatrix matrix;

void buttonSetup() {
  pinMode(buttonPin, INPUT);
  matrix.begin();
}

void buttonAction(byte dat[5]) {
  buttonState = digitalRead(buttonPin);

    // Check for button press
    if (buttonState == LOW) {
        
        static long lastPress = 0;
        long currentMillis = millis();
        if (currentMillis - lastPress > 200) {
            lastPress = currentMillis;

            int firstDigit = dat[0] / 10;
            int secondDigit = dat[0] % 10; 

             if (firstDigit >= 0 && firstDigit < 10) {
                switch (firstDigit) {
                    case 0:
                        matrix.renderBitmap(frame_0, 8, 12);
                        break;
                    case 1:
                        matrix.renderBitmap(frame_1, 8, 12);
                        break;
                    case 2:
                        matrix.renderBitmap(frame_2, 8, 12);
                        break;
                    case 3:
                        matrix.renderBitmap(frame_3, 8, 12);
                        break;
                    case 4:
                        matrix.renderBitmap(frame_4, 8, 12);
                        break;
                    case 5:
                        matrix.renderBitmap(frame_5, 8, 12);
                        break;
                    case 6:
                        matrix.renderBitmap(frame_6, 8, 12);
                        break;
                    case 7:
                        matrix.renderBitmap(frame_7, 8, 12);
                        break;
                    case 8:
                        matrix.renderBitmap(frame_8, 8, 12);
                        break;
                    case 9:
                        matrix.renderBitmap(frame_9, 8, 12);
                        break;
                }
                delay(1000);
            }

            if (secondDigit >= 0 && secondDigit < 10) {
                switch (secondDigit) {
                    case 0:
                        matrix.renderBitmap(frame_0, 8, 12);
                        break;
                    case 1:
                        matrix.renderBitmap(frame_1, 8, 12);
                        break;
                    case 2:
                        matrix.renderBitmap(frame_2, 8, 12);
                        break;
                    case 3:
                        matrix.renderBitmap(frame_3, 8, 12);
                        break;
                    case 4:
                        matrix.renderBitmap(frame_4, 8, 12);
                        break;
                    case 5:
                        matrix.renderBitmap(frame_5, 8, 12);
                        break;
                    case 6:
                        matrix.renderBitmap(frame_6, 8, 12);
                        break;
                    case 7:
                        matrix.renderBitmap(frame_7, 8, 12);
                        break;
                    case 8:
                        matrix.renderBitmap(frame_8, 8, 12);
                        break;
                    case 9:
                        matrix.renderBitmap(frame_9, 8, 12);
                        break;
                }
                delay(1000);
            }
            matrix.renderBitmap(percent, 8, 12);
            delay(1000);
            matrix.clear();
        }
    } else {
        matrix.clear();
    }
}