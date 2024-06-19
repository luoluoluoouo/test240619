// ===== ch16_2.ino =====
// ===== 紅外線控制雙軸機械臂 =====
#include <IRremote.h>  //掛載IRremote函數庫
const int IRR=A1;     //宣告A1腳連接IRR信號
IRrecv irrecv(IRR);     //建構接收物件
decode_results results;   //建構解碼結果物件
#define keyL 0xFF22DD   //定義keyL(向左鍵)編碼
#define keyR 0xFFC23D   //定義keyR(向右鍵)編碼
#define keyU 0xFF629D   //定義keyU(向上鍵)編碼
#define keyD 0xFFA857   //定義keyD(向下鍵)編碼
#define keyOK 0xFF02FD  //定義keyOK(OK鍵)編碼
const int servoPin1=3,servoPin2=9;
//宣告3腳連接servoPin1信號、9腳連接servoPin2信號
#include <Servo.h>      //掛載Servo.h函數庫
Servo servoA;       //建構servoA伺服器物件(旋轉)
Servo servoB;       //建構servoB伺服器物件(上下)
int RL=90, UD=90;     //宣告RL(旋轉變數)、UD(上下變數)
//初始設定
void setup() {
  irrecv.enableIRIn();    //啟用接收功能
  servoA.attach(servoPin1); // servoA連線
  servoB.attach(servoPin2); // servoB連線
}
//主程式
void loop() {
  if (irrecv.decode(&results)) {    //若接收到資料，則解碼
    switch (results.value) {    //根據讀入之信號來判斷
      //servoA伺服器(旋轉)
      case keyL:        //若遙控器按向左鍵
        RL-=5;        //調整角度
        if(RL <=10) RL=10;    //檢查邊界
        servoA.write(RL);     //驅動servoA伺服機置中
        break;
      case keyR:        //若遙控器按向右鍵
        RL+=5;        //調整角度
        if(RL >=170) RL=170;  //檢查邊界
        servoA.write(RL);     //驅動servoA伺服機置中
        break;
      //servoB伺服器(上下)
      case keyD:        //若遙控器按向左鍵
        UD+=5;        //調整角度
        if(UD >=170) UD=170;    //檢查邊界
        servoB.write(UD);     //驅動servoB伺服機置中
        break;
      case keyU:        //若遙控器按向右鍵
        UD-=5;        //調整角度
        if(UD <=10) UD=10;  //檢查邊界
        servoB.write(UD);     //驅動servoB伺服機置中
        break;
      case keyOK:         //若遙控器按OK鍵
        RL=90;UD=90;
        servoA.write(RL);     //驅動servoA伺服機置中
        servoB.write(UD);     //驅動servoB伺服機置中
        break;
    }
    irrecv.resume();    //進入待命狀態
  }
  delay(100);           //延遲0.1秒
}

