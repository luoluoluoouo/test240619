// ===== ch16_3.ino =====
// ===== 藍牙控制雙軸機械臂 =====
#include <SoftwareSerial.h >      //掛載SoftwareSerial函數庫
const int RXD=5, TXD=6;     //宣告5腳連接RXD信號、6腳連接TXD信號
SoftwareSerial myBT(RXD, TXD);  //建構軟體串列埠
const int servoPin1=3,servoPin2=9;
//宣告3腳連接servoPin1信號、9腳連接servoPin2信號
#include <Servo.h>      //掛載Servo.h函數庫
Servo servoA;       //建構servoA伺服器物件(旋轉)
Servo servoB;       //建構servoB伺服器物件(上下)
int RL=90, UD=90;     //宣告RL(旋轉變數)、UD(上下變數)
int inst=0;
//初始設定
void setup() {
  servoA.attach(servoPin1); // servoA連線
  servoB.attach(servoPin2); // servoB連線
  myBT.begin(9600);     //啟用藍牙模組，鮑率為9600
  servoA.write(RL);     //驅動servoA伺服機置中
  servoB.write(UD);     //驅動servoB伺服機置中
}
//主程式
void loop() {
  if(myBT.available()>0) {
    inst=myBT.read();  //讀取藍牙信號
    switch (inst) {         //根據藍牙信號
      //servoA伺服器(旋轉)
      case 'L':         //若手機按向左鈕
        RL-=10;         //調整角度
        if(RL <=10) RL=10;    //檢查邊界
        servoA.write(RL);     //驅動servoA伺服機置中
        break;
      case 'R':         //若手機按向右鈕
        RL+=10;         //調整角度
        if(RL >=170) RL=170;  //檢查邊界
        servoA.write(RL);     //驅動servoA伺服機置中
        break;
      //servoB伺服器(上下)
      case 'D':         //若若手機按向下鈕
        UD+=10;         //調整角度
        if(UD >=170) UD=170;    //檢查邊界
        servoB.write(UD);     //驅動servoB伺服機置中
        break;
      case 'U':         //若手機按向上鈕
        UD-=10;         //調整角度
        if(UD <=10) UD=10;  //檢查邊界
        servoB.write(UD);     //驅動servoB伺服機置中
        break;
      case 'A':         //若手機按A鈕
        for(RL=10;RL<=170;RL+=10){
          servoA.write(RL);     //驅動servoA伺服機
          delay(50);      //暫停0.05秒
        }
        RL=90;
        servoA.write(RL);     //驅動servoA伺服機置中
        break;
      case 'B':         //若手機按B鈕
        for(UD=10;UD<=170;UD+=10){
          servoB.write(UD);   //驅動servoB伺服機
          delay(50);      //暫停0.05秒
        }
        UD=90;
        servoB.write(UD);   //驅動servoB伺服機置中
        break;
    }
  }
  delay(100);           //延遲0.1秒
}

