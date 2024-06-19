// ===== ch5_2.ino =====
const int buzzerPin=13;    //宣告buzzerPin信號連接13腳
const int Note[7]={523,587,659,698,784,880,988};  //宣告音符
//==================================
void setup() {
  pinMode(buzzerPin, OUTPUT); //將buzzerPin腳規畫為輸出埠
  digitalWrite(buzzerPin, 0);   //buzzerPin初值設定為0
}
//==================================
void loop() {
  for(int i=0;i<7;i++) {      //依序播放
    tone(buzzerPin, Note[i]);   //產生音符聲音
    delay(100);       //持續0.1秒
    noTone(buzzerPin);      //停止產生聲音
  }
  delay(250);         //持續0.25秒
  for(int i=7;i>0;i--) {      //依序播放
    tone(buzzerPin, Note[i]);   //產生音符聲音
    delay(100);       //持續0.1秒
    noTone(buzzerPin);      //停止產生聲音
  }
  delay(500);         //持續0.5秒
}

