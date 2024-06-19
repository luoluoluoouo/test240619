// ===== ch2_3.ino =====
const int LED=7;      //7腳為LED
const int PB=A0;      //A0腳為PB
int onOff=1;        //宣告onOff變數，初值為1

void setup() {
  pinMode(LED, OUTPUT); //將LED腳規畫為輸出埠
  digitalWrite(LED, 1);   //關閉LED
}

void loop() {
  int pb=digitalRead(PB); //讀取PB鈕
  if (!pb)  {         //若按下PB鈕
    while(!pb)  pb=digitalRead(PB);   //等待PB鈕放開
    onOff=!onOff;       //切換onOff狀態
    digitalWrite(LED,onOff);  //onOff狀態輸出到LED
  }

  delay(100); //暫停0.1秒
}

