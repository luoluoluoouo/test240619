// ===== ch15_3.ino =====
#include <DHT.h >          //掛載SoftwareSerial函數庫
#include <SoftwareSerial.h >      //掛載SoftwareSerial函數庫
const int dhtPin=A0;          //宣告A0腳連接dhtPin信號
DHT myDHT(dhtPin,DHT11);
// ===== 藍牙感測溫濕度 =====
const int RXD=5, TXD=6;     //宣告5腳連接RXD信號、6腳連接TXD信號
SoftwareSerial myBT(RXD, TXD);  //建構軟體串列埠
float temp=0.0,RH=0.0;      //宣告溫度與濕度變數
//初始設定
void setup() {
  myDHT.begin();            //啟用DHT11
  myBT.begin(9600);       //啟用藍牙模組，鮑率為9600
  Serial.begin(9600);
}
//主程式
void loop() {
  temp = myDHT.readTemperature(0); //讀取攝氏溫度
  byte T = int(temp);        //轉換為整數(0~50)
  RH = myDHT.readHumidity();    //讀取濕度
  byte H = int(RH)+50;        //轉換為整數+50(50~150)
  myBT.write(T);        //傳回溫度
  myBT.write(H);        //傳回濕度
  delay (3000);         //暫停3秒
} 

