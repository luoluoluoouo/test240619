// ===== ch12_2.ino =====
#include <DHT.h>
const int dhtPin=A0;      //宣告A0腳連接dhtPin信號
DHT myDHT(dhtPin,DHT11);
float temp=0.0;       //宣告溫度變數
int x=0;          //宣告變數
//七段顯示器===================
const int scan[4]={ 5,6,7,8};   //宣告5腳~8腳為scan[0]~scan[3](掃描接腳)
const int dataPin=10,latchPin=11,clockPin=12;   
//宣告10腳連接串列資料，11腳連接栓鎖信號，12接腳移位脈波信號
const int segCode[10]={0xC0,0xF9,0xA4,0xB0,0x99, 0x92,0x82,0xF8,0x80,0x90};
//宣告0~9編碼
int dispData[4]={0,0,0,0};
//指撥開關===================
const int DIP=A5;       //宣告A5腳連接DIP信號
void scan7seg(int cnts);    //宣告顯示函數
void convertBCD(void);    //宣告轉換函數

//初始設定
void setup() {
  myDHT.begin();    //啟用DHT11
  Serial.begin(9600);   //啟用序列埠監控視窗
  //七段顯示器===================
  for(int i=0;i<4;i++) {
    pinMode(scan[i], OUTPUT); //將scan[0]~scan[3]腳規畫為輸出埠
    digitalWrite(scan[i], 1);   //關閉scan[0]~scan[3]
  }
  pinMode(dataPin, OUTPUT);   //將dataPin腳規畫為輸出埠
  pinMode(clockPin, OUTPUT);    //將clockPin腳規畫為輸出埠
  pinMode(latchPin, OUTPUT);    //將latchPin腳規畫為輸出埠
  digitalWrite(latchPin, 0);      //latchPin初值設定為0
}
//主程式
void loop() {
  int dip = digitalRead(DIP);     //讀取指撥開關
  temp = myDHT.readTemperature(dip);  //讀取溫度
  x=(int(temp));          //取整數
  convertBCD();         //轉換BCD
  scan7seg(500);          //顯示4秒
}
//自建函數
//顯示函數
void scan7seg(int cnts){
  for(int j=0;j<cnts;j++) {
    for(int i=0;i<4;i++) {
      digitalWrite(latchPin, 0);    //解除資料栓鎖
      shiftOut(dataPin, clockPin, MSBFIRST, segCode[dispData[i]]);
    //輸出顯示資料
      digitalWrite(latchPin, 1);    //栓鎖資料
      digitalWrite(scan[i], 0); //輸出掃描信號
      delay(2);       //暫停2毫秒
      digitalWrite(scan[i], 1);   //關閉掃描信號
    }
  }
}
//轉換函數
void convertBCD(void){
  dispData[0] = x%10;     //解析個位數
  dispData[1] = x/10%10;  //解析十位數
  dispData[2] = x/100%10; //解析百位數
  dispData[3] = x/1000;   //解析千位數
}

