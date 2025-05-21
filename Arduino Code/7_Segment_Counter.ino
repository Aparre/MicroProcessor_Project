#include <BluetoothSerial.h>
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please check your ESP32 configuration.
#endif
BluetoothSerial ESP_BT; //Object for Bluetooth


//Output Pins for ones digit
const int a2_Pin = 15;
const int b2_Pin = 2;
const int c2_Pin = 4;
const int d2_Pin = 16;
const int e2_Pin = 17;
const int f2_Pin = 5;
const int g2_Pin = 18;
// output pins for tens digit
const int a1_Pin = 13;
const int b1_Pin = 12;
const int c1_Pin = 14;
const int d1_Pin = 27;
const int e1_Pin = 26;
const int f1_Pin = 25;
const int g1_Pin = 33;

int receivedValue;
int rValue;

void setup() {
  Serial.begin(9600);
  Serial.println("ESP32 Bluetooth LED Control");
  ESP_BT.begin("ESP32-Counter"); // Name of your Bluetooth device
  Serial.println("Bluetooth device is ready to pair!");

  //initializing pins
  pinMode(a1_Pin, OUTPUT);
  pinMode(b1_Pin, OUTPUT);
  pinMode(c1_Pin, OUTPUT);
  pinMode(d1_Pin, OUTPUT);
  pinMode(e1_Pin, OUTPUT);
  pinMode(f1_Pin, OUTPUT);
  pinMode(g1_Pin, OUTPUT);
  pinMode(a2_Pin, OUTPUT);
  pinMode(b2_Pin, OUTPUT);
  pinMode(c2_Pin, OUTPUT);
  pinMode(d2_Pin, OUTPUT);
  pinMode(e2_Pin, OUTPUT);
  pinMode(f2_Pin, OUTPUT);
  pinMode(g2_Pin, OUTPUT);

  //initaialize rValue for default
  rValue = 0;
}

void loop() {
  if (ESP_BT.available()) {
    receivedValue = ESP_BT.read();
  }
  rValue = receivedValue;
 
  int firstDigit = rValue % 10;
  int secondDigit = (rValue / 10) % 10;

  //first digit
  bcdTo7seg(firstDigit, true);
  delay(5);
  setOutput(true, 0, 0, 0, 0, 0, 0, 0);
  setOutput(false, 0, 0, 0, 0, 0, 0, 0);

  //second digit
  bcdTo7seg(secondDigit, false);
  delay(5);
  setOutput(true, 0, 0, 0, 0, 0, 0, 0);
  setOutput(false, 0, 0, 0, 0, 0, 0, 0);
}

void bcdTo7seg(int num, bool place) {
  switch (num)
  {
    case 0: setOutput(place, 1, 1, 1, 1, 1, 1, 0); break;  // 0
    case 1: setOutput(place, 0, 1, 1, 0, 0, 0, 0); break;  // 1
    case 2: setOutput(place, 1, 1, 0, 1, 1, 0, 1); break;  // 2
    case 3: setOutput(place, 1, 1, 1, 1, 0, 0, 1); break;  // 3
    case 4: setOutput(place, 0, 1, 1, 0, 0, 1, 1); break;  // 4
    case 5: setOutput(place, 1, 0, 1, 1, 0, 1, 1); break;  // 5
    case 6: setOutput(place, 1, 0, 1, 1, 1, 1, 1); break;  // 6
    case 7: setOutput(place, 1, 1, 1, 0, 0, 0, 0); break;  // 7
    case 8: setOutput(place, 1, 1, 1, 1, 1, 1, 1); break;  // 8
    case 9: setOutput(place, 1, 1, 1, 1, 0, 1, 1); break;  // 9
    case 10: setOutput(place, 0, 0, 0, 0, 1, 0, 1); break; // A
    case 11: setOutput(place, 0, 1, 0, 1, 1, 1, 1); break; // B
    case 12: setOutput(place, 0, 0, 1, 1, 1, 1, 0); break; // C
    case 13: setOutput(place, 1, 0, 0, 1, 1, 0, 1); break; // D
    case 14: setOutput(place, 1, 0, 0, 1, 1, 1, 1); break; // E
    case 15: setOutput(place, 0, 0, 0, 0, 1, 1, 1); break;
  }
}

void setOutput(bool ones,int a, int b, int c, int d, int e, int f, int g) {
  if (ones) {
    digitalWrite(a1_Pin, a);
    digitalWrite(b1_Pin, b);
    digitalWrite(c1_Pin, c);
    digitalWrite(d1_Pin, d);
    digitalWrite(e1_Pin, e);
    digitalWrite(f1_Pin, f);
    digitalWrite(g1_Pin, g);
  }
  else {
    digitalWrite(a2_Pin, a);
    digitalWrite(b2_Pin, b);
    digitalWrite(c2_Pin, c);
    digitalWrite(d2_Pin, d);
    digitalWrite(e2_Pin, e);
    digitalWrite(f2_Pin, f);
    digitalWrite(g2_Pin, g);
  }
}
