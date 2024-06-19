// ===== ch12_1.ino =====
// ===== 基本溫濕度量測 =====
#include <DHT.h>
const int dhtPin=A0;      //宣告A0腳連接dhtPin信號
DHT myDHT(dhtPin,DHT11);
float tempC=0.0,tempF=0.0,RH=0.0,HI=0.0;
//宣告攝氏溫度(tempC)、華氏溫度(tempF)、濕度(RH)與酷熱指數(HI)之變數
//初始設定
void setup() {
  myDHT.begin();            //啟用DHT11
  Serial.begin(9600);        //啟用序列埠監控視窗
}
//主程式
void loop() {
  tempC = myDHT.readTemperature(0);   //讀取攝氏溫度
  Serial.print("Celsius temperature : ");//顯示攝氏溫度
  Serial.println(tempC);               
  tempF = myDHT.readTemperature(1);   //讀取華氏溫度
  Serial.print("Fahrenheit temperature : ");//顯示華氏溫度
  Serial.println(tempF);               
  RH = myDHT.readHumidity();          //讀取濕度
  Serial.print("Relative humidity : "); //顯示濕度
  Serial.println(RH);        
  HI = myDHT.computeHeatIndex(tempF, RH);//計算酷熱指數
  Serial.print("Heat Index : ");      //顯示酷熱指數
  Serial.println(HI);
  Serial.println();                 //空一行
  delay(1000);           //暫停1秒
}

