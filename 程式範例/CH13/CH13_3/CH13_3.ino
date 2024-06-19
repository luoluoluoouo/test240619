// ===== ch13_3.ino =====
// ===== 遙控器控制馬達 =====
#include <IRremote.h>  //掛載IRremote函數庫
const int M1=2, M2=3;   //宣告2腳連接M1信號、3腳連接M2信號
const int Lled=5;     //宣告5腳連接Lled信號
const int Rled=6;     //宣告6腳連接Rled信號
const int ON=0,OFF=1;   //宣告ON、OFF信號，低態動作
const int IRR=A1;     //宣告A1腳連接IRR信號
IRrecv irrecv(IRR);     //建構接收物件
decode_results results;   //建構解碼結果物件
#define keyL 0xFF22DD   //定義keyL(向左鍵)編碼
#define keyR 0xFFC23D   //定義keyR(向右鍵)編碼
#define keyOff 0xFF02FD   //定義keyOff(OK鍵)編碼
/*
向左鍵的編碼：0xFF22DD
向右鍵的編碼：0xFFC23D
向OK鍵的編碼：0xFF02FD
*/
//初始設定
void setup() {
  pinMode(M1, OUTPUT);  //將M1腳規畫為輸出埠
  digitalWrite(M1, 0);    //M1初值設定為0
  pinMode(M2, OUTPUT);  //將M2腳規畫為輸出埠
  digitalWrite(M2, 0);    //M2初值設定為0
  pinMode(Lled, OUTPUT);  //將Lled腳規畫為輸出埠
  digitalWrite(Lled, OFF);    //Lled初值設定為OFF
  pinMode(Rled, OUTPUT);  //將Rled腳規畫為輸出埠
  digitalWrite(Rled, OFF);    //Rled初值設定為OFF
  irrecv.enableIRIn();    //啟用接收功能
}
//主程式
void loop() {
  if (irrecv.decode(&results)) {    //若接收到資料，則解碼
    switch (results.value) {    //根據讀入之信號來判斷
      case keyL:        //若遙控器按向左鍵
        digitalWrite(M1,0);     //驅動馬達正轉
        digitalWrite(M2,1);     //驅動馬達正轉
        digitalWrite(Lled,ON);  //Lled亮
        digitalWrite(Rled,OFF); //Rled不亮
        break;
      case keyR:        //若遙控器按向右鍵
        digitalWrite(M1,1);     //驅動馬達反轉
        digitalWrite(M2,0);     //驅動馬達反轉
        digitalWrite(Lled,OFF); //Lled不亮
        digitalWrite(Rled,ON);  //Rled亮
        break;
      case keyOff:        //若遙控器按OK鍵
        digitalWrite(M1,0);     //馬達停止
        digitalWrite(M2,0);     //馬達停止
        digitalWrite(Lled,OFF); //Lled亮
        digitalWrite(Rled,OFF); //Rled不亮
        break;
    }
    irrecv.resume();    //進入待命狀態
  }
}

