// ===== ch6_2.ino =====
const int ON=A0, OFF=A1;
//宣告A0腳為ON信號輸入； A1腳為OFF信號輸入
const int relayPin=4;      //宣告relayPin信號連接4腳
const int buzzerPin=13;   //宣告buzzerPin信號連接13腳
const int on=0, off=1;      //宣告低態動作信號
const int onDelay=1000;   //宣告開啟延遲時間
const int offDelay=3000;    //宣告關閉延遲時間
void beep(void);      //宣告嗶聲函數
//==================================
void setup() {
  pinMode(relayPin, OUTPUT);    //將relayPin腳規畫為輸出埠
  digitalWrite(relayPin, off);    //relayPin初值設定為off
  pinMode(buzzerPin, OUTPUT); //將buzzerPin腳規畫為輸出埠
  digitalWrite(buzzerPin, 0);   //buzzerPin初值設定為0
}
//==================================
void loop() {
  int i=digitalRead(OFF);       //讀取OFF鈕
  if(!i) {            //若按下OFF鈕
    beep();         //嗶一聲
    delay(offDelay);      //延遲offDelay時間
    digitalWrite(relayPin, off);  //關閉繼電器
  }
  else{
    int i=digitalRead(ON);    //讀取ON鈕
    if(!i) {          //若按ON鈕
      beep();       //嗶一聲
      delay(onDelay);     //延遲onDelay時間
      digitalWrite(relayPin, on); //開啟繼電器
    }
  }
}
//beep()函數
void beep(void) {
  tone(buzzerPin, 1000);      //輸出1KH聲音
  delay(100);         //持續0.1秒
  noTone(buzzerPin);      //停止輸出聲音
  delay(100);         //持續0.1秒
} 

