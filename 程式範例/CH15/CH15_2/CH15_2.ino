// ===== ch15_2.ino =====
// ===== 藍牙控制繼電器 =====
#include <SoftwareSerial.h >      //掛載SoftwareSerial函數庫
const int RXD=5, TXD=6;     //宣告5腳連接RXD信號、6腳連接TXD信號
SoftwareSerial myBT(RXD, TXD);  //建構軟體串列埠
const int relayPin=4;       //宣告relayPin信號連接到4接腳
const int ON=0,OFF=1;     //宣告低態動作信號
int inst=0;             //宣告變數
//初始設定
void setup() {
  pinMode(relayPin, OUTPUT);    //將relayPin腳規畫為輸出埠
  digitalWrite(relayPin, OFF);    //relayPin初值設定為OFF
  myBT.begin(9600);       //啟用藍牙模組，鮑率為9600
}
//主程式
void loop() {
  if(myBT.available()>0) inst=myBT.read();  //讀取藍牙信號
  if(inst=='0')  digitalWrite(relayPin, OFF);    //關閉繼電器
  if(inst=='1') digitalWrite(relayPin, ON);  //開啟繼電器
} 

