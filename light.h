int redPin = 11;
int greenPin = 10;

void lightSetup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void setLight(byte dat[5], boolean dehumidifierStatus) {
  if (dat[0] >= 60) {  
    analogWrite(greenPin, 0);
    analogWrite(redPin, 255);
  } else if (dat[0] >= 53 && dehumidifierStatus == true) {  
    analogWrite(greenPin, 0);
    analogWrite(redPin, 255);
  } else if (dat[0] < 53 || (dat[0] < 60 && dehumidifierStatus == false)) {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
  } else {
    analogWrite(redPin, 120);
    analogWrite(greenPin, 120);
  }
}