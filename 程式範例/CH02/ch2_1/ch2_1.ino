// ===== ch2_1.ino =====
const int LED[4]={7,6,5,4};     //7~4腳分別為LED[0]~LED[3]
const int DIP[4]={A0,A1,A2,A3}; //A0~A3腳分別為DIP[0]~DIP[3]

void setup() {
  for(int i=0;i<4;i++) {
    pinMode(LED[i], OUTPUT);  //將LED[0]~LED[3]腳規畫為輸出埠
    digitalWrite(LED[i], 1);  //關閉LED[0]~LED[3]
  }
}

void loop() {
  for(int i=0;i<4;i++) {
    int sw=digitalRead(DIP[i]); //讀取DIP[i]
    digitalWrite(LED[i],sw);    //反應到LED[i]
  }
  delay(100);           //暫停0.1秒
}

