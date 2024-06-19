// ===== ch13_1.ino =====
// ===== 遙控器編碼測試=====
#include <IRremote.h>  //掛載IRremote函數庫
const int IRR=A1;     //宣告A1腳連接IRR信號
IRrecv irrecv(IRR);     //建構接收物件
decode_results results;   //建構解碼結果物件

//初始設定
void setup() {
  Serial.begin(9600);   //啟用序列埠監控視窗
  irrecv.enableIRIn();  //啟用接收功能
}
//主程式
void loop() {
  if (irrecv.decode(&results)) {  //若接收到資料，則解碼
    Serial.println(results.value, HEX); //在序列埠監控視窗裡以16進位碼顯示
    irrecv.resume();    //進入待命狀態
  }
}

