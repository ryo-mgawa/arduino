// 型定義
typedef unsigned char u1;

// Pin番号
u1 button1 = 2;
u1 button2 = 4;
u1 outputPin = 9;
u1 led1 = 10;
u1 led2 = 11;

// ボタン押下時に電圧が下がるため、BUTTON_ONが0でBUTTON_OFFが1とする
const u1 BUTTON_ON = 0;
const u1 BUTTON_OFF = 1;

int buttonFlag;

void setup() {
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(outputPin, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  buttonFlag = BUTTON_OFF;

  digitalWrite(outputPin, HIGH);

  // outputPinのHIGHが安定するまでdelayする
  delay(100);
}

void loop() {
  int button1State = digitalRead(button1);
  int button2State = digitalRead(button2);

  if (buttonFlag == BUTTON_ON) return;
  
  if (button1State == BUTTON_ON && button2State == BUTTON_ON){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    buttonFlag = BUTTON_ON;
  }
  else if (button1State == BUTTON_ON){
    digitalWrite(led1, HIGH);
    buttonFlag = BUTTON_ON;
  }
  else if (button2State == BUTTON_ON){
    digitalWrite(led2, HIGH);
    buttonFlag = BUTTON_ON;
  }
  
  delay(1);
}