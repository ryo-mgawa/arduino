int button1 = 2;
int button2 = 4;
int outputPin = 9;
int led1 = 10;
int led2 = 11;

int buttonFlag;

void setup() {
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(outputPin, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  buttonFlag = 0;

  digitalWrite(outputPin, HIGH);

  // outputPinのHIGHが安定するまでdelayする
  delay(100);
}

void loop() {
  int button1State = digitalRead(button1);
  int button2State = digitalRead(button2);

  if (buttonFlag == 1) return;
  
  if (button1State == 0 && button2State ==0){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    buttonFlag = 1;
  }
  else if (button1State == 0){
    digitalWrite(led1, HIGH);
    buttonFlag = 1;
  }
  else if (button2State == 0){
    digitalWrite(led2, HIGH);
    buttonFlag = 1;
  }
  
  delay(1);
}