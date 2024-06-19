// ===== ch16_1.ino =====
// ===== 搖桿控制雙軸機械臂 =====
const int servoPin1=3,servoPin2=9;
//宣告2腳連接servoPin1信號、3腳連接servoPin2信號
const int jV=A3, jH=A4, jPB=A5;//宣告搖桿之接腳
#include <Servo.h>      //掛載Servo.h函數庫
Servo servoA;       //建構servoA伺服器物件
Servo servoB;       //建構servoB伺服器物件
//初始設定
void setup() {
  servoA.attach(servoPin1); // servoA連線
  servoB.attach(servoPin2); // servoB連線
}
//主程式
void loop() {
  int V = analogRead(jV);     //讀取垂直電位計並存入jV變數
  V = map(V,0,1023, 10,170);    //轉換範圍
  servoA.write(V);        //驅動servoA伺服機
  int H = analogRead(jH);     //讀取水平電位計並存入jH變數
  H = map(H,0,1023, 10,170);    //轉換範圍
  servoB.write(H);        //驅動servoB伺服機
  delay(100);           //延遲0.1秒
}

