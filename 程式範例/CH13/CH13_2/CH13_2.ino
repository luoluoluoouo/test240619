// ===== ch13_2.ino =====
// ===== 遙控器控制繼電器 =====
#include <IRremote.h>  //掛載IRremote函數庫
const int IRR=A1;     //宣告A1腳連接IRR信號
IRrecv irrecv(IRR);     //建構接收物件
decode_results results;   //建構解碼結果物件
const int LED=13;      //宣告5腳連接LED信號
const int relayPin=4;   //宣告4腳連接relayPin信號
const int ON=0, OFF=1;    //宣告ON/OFF信號(低態動作)
int SW=OFF;       //宣告SW變數
#define keyOn 0xFF42BD  //定義keyOn(*)編碼
#define keyOff 0xFF52AD //定義keyOff(#)編碼
/*
向*鍵的編碼：0xFF42BD
向#鍵的編碼：0xFF52AD
*/

//初始設定
void setup() {
  pinMode(relayPin, OUTPUT);    //將relayPin規劃為輸出接腳
  digitalWrite(relayPin, OFF);    //將relayPin的初值設定為OFF 
  pinMode(LED, OUTPUT);   //將LED規劃為輸出接腳
  digitalWrite(LED, OFF);     //將LED的初值設定為OFF 
  pinMode(relayPin, OUTPUT);    //將relayPin規劃為輸出接腳
  irrecv.enableIRIn();      //啟用接收功能
}
//主程式
void loop() {
  if (irrecv.decode(&results)) {  //若接收到資料，則解碼
    if (results.value==keyOff) {    //若遙控器按#鍵
      SW=OFF;     
    }
    else if (results.value==keyOn) {  //若遙控器按*鍵
      SW=ON;    
    }
    irrecv.resume();    //進入待命狀態
  }
  digitalWrite(relayPin,SW);  //驅動繼電器
  digitalWrite(LED,SW); //驅動LED
}

