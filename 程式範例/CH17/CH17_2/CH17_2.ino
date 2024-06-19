// ===== ch17_2.ino =====
// ===== 藍牙控制RGB LED =====
#include <SoftwareSerial.h >      //掛載SoftwareSerial函數庫
const int RXD=5, TXD=6;     //宣告5腳連接RXD信號、6腳連接TXD信號
SoftwareSerial myBT(RXD, TXD);  //建構軟體串列埠
const int cnts=17;        //宣告LED的數量為17
const int pin=2;          //宣告LED的信號連接到2腳
const int pot=A2;       //宣告可變電阻器連接到A0腳
#include  <Adafruit_NeoPixel.h>
Adafruit_NeoPixel LEDs=Adafruit_NeoPixel(cnts, pin, NEO_RGB+NEO_KHZ800);
void eyebrow (uint32_t c24, uint8_t waiting); //宣告眉開眼笑函數
void theaterChase(uint32_t color, uint8_t waiting); //宣告群蛙亂跳函數
void rainbow(uint8_t waiting);    //宣告彩虹漸變函數
void rainbowCycle(uint8_t counts, uint8_t waiting); //宣告彩虹輪動函數
void brightness();        //宣告亮度調整函數
uint32_t Wheel(byte WheelPos);  //宣告彩虹色階產生函數
int inst;
//初始設定
void setup() {
  myBT.begin(9600);       //啟用藍牙模組，鮑率為9600
  LEDs.begin();           //啟用串列式RGB LED
}
//主程式
void loop() {
  if(myBT.available()>0) {
    inst=myBT.read();     //讀取藍牙信號
    switch (inst) {       //根據藍牙信號
      case '0':        //若手機按清除鈕，則關閉LED
        for (int i=0;i< LEDs.numPixels(); i++) LEDs.setPixelColor(i, 0);
        LEDs.show();      //顯示LED
        break;
      case '1':        //若手機按眉開眼笑鈕
        eyebrow(LEDs.Color(255,0,0),100); //紅眉毛
        eyebrow(LEDs.Color(0,255,0),100); //綠眉毛
        eyebrow(LEDs.Color(0,0,255),100); //藍眉毛
        eyebrow(LEDs.Color(255,255,255),100); //白眉毛
        break;
      case '2':        //若手機按群蛙亂跳鈕
        theaterChase(LEDs.Color(255,0,0), 60);  //紅蛙亂跳
        theaterChase(LEDs.Color(0,255,0), 60);  //綠蛙亂跳
        theaterChase(LEDs.Color(0,0,255), 60);  //藍蛙亂跳
        theaterChase(LEDs.Color(255,255,255), 60);  //白蛙亂跳
        break;
      case '3':        //若手機按彩虹漸變鈕
        rainbow(100);     //慢動
        rainbow(50);      //快動
        break;
      case '4':        //若手機按彩虹輪動鈕
        rainbowCycle(5, 10);    //連續五圈
        break;
    }
  }
  delay(100);           //延遲0.1秒
}
// 眉開眼笑函數
// 由中間往兩邊點亮LED，再由右而左關閉
// 改變waiting值，可調整顏色塗佈速度
void eyebrow (uint32_t c24, uint8_t waiting) {
  for(int i=0; i<LEDs.numPixels()/2; i++){
    brightness();         //調整亮度
  LEDs.setPixelColor(LEDs.numPixels()/2-i-1, c24);  //點亮左邊眉毛
  LEDs.setPixelColor(LEDs.numPixels()/2+i, c24);  //點亮右邊眉毛
  LEDs.show();        //顯示LED
  delay(waiting);       //持續點亮waiting時間
  }
  for(int i=0; i< LEDs.numPixels()/2; i++){
    LEDs.setPixelColor(i, 0);     //關閉左邊眉毛
  LEDs.setPixelColor(LEDs.numPixels()-i-1, 0);//關閉右邊眉毛
  LEDs.show();        //顯示LED
  delay(waiting);       //持續點亮waiting時間
  }
}
//群蛙亂跳函數
//改變waiting值，可調整躍動速度
void theaterChase(uint32_t color, uint8_t waiting) {
  for (int i=0; i<10; i++){       //重複10次
    brightness();         //調整亮度
    for (int cShift=0; cShift < 3; cShift ++) {
      for (int j=0; j < LEDs.numPixels(); j+=3) //設定每隔3個LED，顏色為color
        LEDs.setPixelColor(j+cShift, color); 
      LEDs.show();        //顯示LED
      delay(waiting);       //持續點亮waiting時間
      for (int j=0; j < LEDs.numPixels(); j+=3) //設定每隔3個LED，顏色為0
        LEDs.setPixelColor(j+cShift, 0);
    }
  }
}
//彩虹漸變函數
//改變waiting值，可調整顯示的時間長度
void rainbow(uint8_t waiting) {
  for(int i=0; i<256; i++) {  //每圈256個顏色變化
    brightness();       //調整亮度
    for(int j=0; j< LEDs.numPixels(); j++) //設定每個LED的顏色
      LEDs.setPixelColor(j, Wheel((i+j) & 255));
    LEDs.show();      //顯示LED
    delay(waiting);       //持續點亮waiting時間
  }
}
//彩虹輪動函數
//counts值為輪動圈數
//改變waiting值，可調整顯示的時間長度
void rainbowCycle(uint8_t counts, uint8_t waiting){
  for(int i=0; i<counts; i++)     //彩虹輪動counts圈
    for(int j=0; j<256; j++){     //每圈256個顏色變化
      brightness();       //調整亮度
      for(int k=0; k< LEDs.numPixels(); k++) //設定每個LED的顏色 
          LEDs.setPixelColor(k, Wheel(((k*256/LEDs.numPixels())+j) & 255));
    LEDs.show();      //顯示LED
    delay(waiting);     //持續點亮waiting時間
    }
}
//========== 亮度調整函數 ============
// pot為連接電位計的類比輸入接腳，LEDs為物件名稱
void brightness(){
  int x=analogRead(pot);
  LEDs.setBrightness(x/4);
} 
//========== 彩虹色階產生函數 ============ 
uint32_t  Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85)    //若輪位小於85
    return LEDs.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  else if (WheelPos < 170) {  //若輪位在85~170之間
    WheelPos -= 85;     //輪位減去85，往前移動
    return LEDs.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } 
  else {          //若輪位大於於170
    WheelPos -= 170;    //輪位減去170，往前移動
    return LEDs.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

