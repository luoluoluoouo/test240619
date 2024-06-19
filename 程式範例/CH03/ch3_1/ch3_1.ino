// ===== ch3_1.ino =====
const int LED[8]={9,8,7,6, 5,4,3,2};    //宣告9腳~2腳為LED[0]~LED[7]
int onOff=1;            //宣告onOff變數，初值為1

void setup() {
  for(int i=0;i<8;i++) {
    pinMode(LED[i], OUTPUT);  //將LED[0]~LED[7]腳規畫為輸出埠
    digitalWrite(LED[i], 1);    //關閉LED[0]~LED[7]
  }
}

void loop() {
  for(int i=0;i<8;i++) {
    digitalWrite(LED[i], onOff);  //驅動LED
    onOff=!onOff;       //切換狀態
  }
  delay(250); //暫停0.25秒
  onOff=!onOff;       //切換狀態
}

