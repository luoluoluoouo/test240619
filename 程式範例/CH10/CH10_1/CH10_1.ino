// ===== ch10_1.ino =====
// ===== 直流馬達速度控制 =====
const int M1=2, M2=3;    //宣告2腳連接M1、3腳連接M2信號
const int VR=A2;      //宣告A2腳連接VR信號
//初始設定
void setup() {
  pinMode(M1, OUTPUT);      //將M1腳規畫為輸出埠
  digitalWrite(M1, 0);        //M1初值設定為0
  pinMode(M2, OUTPUT);      //將M2腳規畫為輸出埠
  digitalWrite(M2, 0);        //M2初值設定為0
}
//主程式
void loop() {
  int vr = analogRead (VR);         //讀取可變電阻器
  analogWrite(M2, vr/4);        //驅動直流馬達
  delay(100);           //暫停0.1秒
}

