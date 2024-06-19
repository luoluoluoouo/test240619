// ===== ch7_1.ino =====
const int VR=A2, LED=3;  //宣告A2腳連接VR信號、3腳連接LED信號
//==================================
void setup() {
  pinMode(LED, OUTPUT);   //將LED腳規畫為輸出埠
  digitalWrite(LED, 0);   //LED初值設定為0
}
//==================================
void loop() {
  int i=analogRead(VR);     //讀取VR2上的電壓
  i=map(i, 0, 1023, 0, 255);//轉換範圍
  analogWrite(LED,i);       //輸出到LED
  delay(100);               //暫停0.1秒
}

