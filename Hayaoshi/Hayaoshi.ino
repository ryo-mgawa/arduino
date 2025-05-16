#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x)[0]))

// 型定義
typedef unsigned char u1;

// Pin番号
const u1 button[3] = {2, 3, 4};
const u1 led[3] = {10, 11, 12};
const u1 outputPin = 9;
const u1 maruButton = 13;
const u1 batsuButton = 14;

const u1 buttonCount = ARRAY_LENGTH(button);
const u1 ledCount = ARRAY_LENGTH(led);

// ボタン押下時に電圧が下がるため、BUTTON_ONが0でBUTTON_OFFが1とする
const u1 BUTTON_ON = 0;
const u1 BUTTON_OFF = 1;

u1 buttonFlag = BUTTON_OFF;

void setup() {
  // 回答者のボタン初期化
  for (u1 b = 0; b < buttonCount; b++) {
    pinMode(button[b], INPUT);
    pinMode(led[b], OUTPUT);
  }
  
  // 出題者のボタン初期化
  pinMode(maruButton, INPUT);
  pinMode(batsuButton, INPUT);

  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, HIGH);

  LedInit();

  // outputPinのHIGHが安定するまでdelayする
  delay(100);
}

void loop() {
  if (buttonFlag == BUTTON_OFF){
    for (u1 buttonNum = 0; buttonNum < buttonCount; buttonNum++) {
      u1 buttonState = digitalRead(button[buttonNum]);

      if (buttonState == BUTTON_ON) {
        LedOn(buttonNum);
      }
    }
  }
  else {
    if (digitalRead(maruButton) == BUTTON_ON ||
        digitalRead(batsuButton) == BUTTON_ON){
      ButtonInit();
      LedInit();
    }
  }

  delay(1);
}

void LedOn(u1 ledNum){
  digitalWrite(led[ledNum], HIGH);
  buttonFlag = BUTTON_ON;
}

void ButtonInit(){
  buttonFlag == BUTTON_OFF;
}

void LedInit(){
  for (u1 ledNum = 0; ledNum < ledCount; ledNum++){
    digitalWrite(led[ledNum], LOW);
  }
}