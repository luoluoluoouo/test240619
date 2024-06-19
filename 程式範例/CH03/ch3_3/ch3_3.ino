// ===== ch3_3.ino =====
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
  //由中間而兩旁
  for(int i=0;i<4;i++) {
    digitalWrite(LED[3-i], On); //驅動左邊LED
    digitalWrite(LED[i+4], On); //驅動右邊LED
    delay(100);       //暫停0.1秒
  }
  //關閉
  for(int i=0;i<8;i++) {
    digitalWrite(LED[i], Off);  //驅動LED
  }
  delay(500);       //暫停0.5秒
}

