#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char secretCode[7] = "123456";
char inputCode[7];
byte currentLength = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    Serial.print(key);
    
    if (key == '#') {
      inputCode[currentLength] = '\0';
      if (strcmp(inputCode, secretCode) == 0) {
        Serial.println(" Access Granted");
      } else {
        Serial.println(" Access Denied");
      }
      currentLength = 0;
    } else if (key == '*') {
      currentLength = 0;
      Serial.println(" Reset");
    } else if (currentLength < 6) {
      inputCode[currentLength] = key;
      currentLength++;
    }
  }
}
