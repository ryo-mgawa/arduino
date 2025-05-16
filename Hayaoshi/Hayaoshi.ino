// 型定義
typedef unsigned char u1;

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x)[0]))

// ボタンとLEDのピン
const u1 button[3] = {2, 3, 4}; //D2~D4
const u1 led[3] = {10, 11, 12};
const u1 maruButton = 6;
const u1 batsuButton = 7;
const u1 outputPin = 9;

const u1 buttonCount = ARRAY_LENGTH(button);
const u1 ledCount = ARRAY_LENGTH(led);

const u1 BUTTON_ON = 0;
const u1 BUTTON_OFF = 1;

volatile u1 buttonFlag = BUTTON_OFF;
volatile u1 pressedButtonIndex = 255;

// 現在のピン状態を保存
volatile u1 prevButtonState = 0xFF;

void setup() {
  // 各ピンのモード設定
  for (u1 i = 0; i < buttonCount; i++) {
    pinMode(button[i], INPUT);
    pinMode(led[i], OUTPUT);
  }
  pinMode(maruButton, INPUT);
  pinMode(batsuButton, INPUT);
  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, HIGH);

  LedInit();

  // ピンチェンジ割り込み有効化
  PCICR |= (1 << PCIE2);         // PCINT16-23 (D0～D7) グループを有効に
  PCMSK2 |= (1 << PCINT18);      // D2
  PCMSK2 |= (1 << PCINT19);      // D3
  PCMSK2 |= (1 << PCINT20);      // D4

  // 安定待ち
  delay(100);
}

void loop() {
  if (buttonFlag == BUTTON_OFF && pressedButtonIndex < buttonCount) {
    LedOn(pressedButtonIndex);
  }

  /*
  if (buttonFlag == BUTTON_ON) {
    if (digitalRead(maruButton) == BUTTON_ON || digitalRead(batsuButton) == BUTTON_ON) {
      ButtonInit();
      LedInit();
    }
  }
  */

  delay(1);
}

void LedOn(u1 ledNum){
  digitalWrite(led[ledNum], HIGH);
  buttonFlag = BUTTON_ON;
}

void ButtonInit(){
  buttonFlag = BUTTON_OFF;
  pressedButtonIndex = 255;
}

void LedInit(){
  for (u1 i = 0; i < ledCount; i++) {
    digitalWrite(led[i], HIGH);
  }

  delay(1500);

  for (u1 i = 0; i < ledCount; i++) {
    digitalWrite(led[i], LOW);
  }
}

// ピンチェンジ割り込みハンドラ（D0～D7）
ISR(PCINT2_vect) {
  // 各ボタンの状態を調べる
  for (u1 i = 0; i < buttonCount; i++) {
    u1 pin = button[i];
    u1 currentState = digitalRead(pin);

    // 変化があって、押された瞬間（LOW）なら
    if (((prevButtonState >> i) & 0x01) != currentState && currentState == BUTTON_ON) {
      if (buttonFlag == BUTTON_OFF) {
        pressedButtonIndex = i;
      }
    }

    // 状態を更新
    if (currentState == HIGH) {
      prevButtonState |= (1 << i);
    } else {
      prevButtonState &= ~(1 << i);
    }
  }
}