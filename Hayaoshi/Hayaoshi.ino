// 型定義
typedef unsigned char u1;

// Pin番号
const u1 button[3] = {2, 3, 4};
const u1 led[3] = {10, 11, 12};
const u1 outputPin = 9;

// ボタン押下時に電圧が下がるため、BUTTON_ONが0でBUTTON_OFFが1とする
const u1 BUTTON_ON = 0;
const u1 BUTTON_OFF = 1;

u1 buttonFlag = BUTTON_OFF;

void setup() {
  for (u1 b = 0; b < 3; b++) {
    pinMode(button[b], INPUT);
    pinMode(led[b], OUTPUT);
  }
  pinMode(outputPin, OUTPUT);

  digitalWrite(outputPin, HIGH);

  // outputPinのHIGHが安定するまでdelayする
  delay(100);
}

void loop() {
  if (buttonFlag == BUTTON_ON) return;

  for (u1 buttonNum = 0; buttonNum < 3; buttonNum++) {
    u1 buttonState = digitalRead(button[buttonNum]);

    if (buttonState == BUTTON_ON) {
      digitalWrite(led[buttonNum], HIGH);
      buttonFlag = BUTTON_ON;
    }
  }

  delay(1);
}