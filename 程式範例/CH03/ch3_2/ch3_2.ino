// ===== ch3_2.ino =====
const int LED[8]={9,8,7,6, 5,4,3,2};    //宣告9腳~2腳為LED[0]~LED[7]
//宣告Off變數，初值為1；On變數，初值為0；
int Off=1, On=0;          

void setup() {
  for(int i=0;i<8;i++) {
    pinMode(LED[i], OUTPUT);  //將LED[0]~LED[7]腳規畫為輸出埠
    digitalWrite(LED[i], Off);    //關閉LED[0]~LED[7]
  }
}

void loop() {
  //由左而右
  for(int i=0;i<8;i++) {
    digitalWrite(LED[i], On); //驅動LED
    delay(10);     //暫停0.1秒
    digitalWrite(LED[i], Off);  //驅動LED
  }
  //由右而左
  for(int i=7;i>0;i--) {
    digitalWrite(LED[i], On); //驅動LED
    delay(100);     //暫停0.1秒
    digitalWrite(LED[i], Off);  //驅動LED
  }
}

