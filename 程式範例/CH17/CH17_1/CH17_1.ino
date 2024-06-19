// ===== ch17_1.ino =====
// ===== 紅外線控制串列式RGB LED =====
#include <IRremote.h>    //掛載IRremote函數庫
const int IRR=A1;       //宣告A1腳連接IRR信號
IRrecv irrecv(IRR);       //建構接收物件
decode_results results;     //建構解碼結果物件
#define key0 0xFF4AB5     //定義key0編碼
#define key1 0xFF6897     //定義key1編碼
#define key2 0xFF9867     //定義key2編碼
#define key3 0xFFB04F     //定義key3編碼
#define key4 0xFF30CF     //定義key4編碼
const int cnts=17;       //宣告LED的數量為17
const int pin=2;        //宣告LED的信號連接到2腳
const int pot=A0;        //宣告可變電阻器連接到A0腳
#include  <Adafruit_NeoPixel.h>
Adafruit_NeoPixel LEDs=Adafruit_NeoPixel(cnts, pin, NEO_RGB+NEO_KHZ800);
void eyebrow (uint32_t c24, uint8_t waiting); //宣告眉開眼笑函數
void theaterChase(uint32_t color, uint8_t waiting); //宣告群蛙亂跳函數
void rainbow(uint8_t waiting);  //宣告彩虹漸變函數
void rainbowCycle(uint8_t counts, uint8_t waiting); //宣告彩虹輪動函數
void brightness();      //宣告亮度調整函數
uint32_t Wheel(byte WheelPos);//宣告彩虹色階產生函數
//初始設定
void setup() {
  irrecv.enableIRIn();    //啟用接收功能
  LEDs.begin();     //啟用NeoPixel
  brightness();       //設定亮度
}
//主程式
void loop() {
  if (irrecv.decode(&results)) {    //若接收到資料，則解碼
    switch (results.value) {    //根據讀入之信號來判斷
      case key0:        //若遙控器按0鍵，則關閉LED
        for (int i=0;i< LEDs.numPixels(); i++) LEDs.setPixelColor(i, 0);
        LEDs.show();      //顯示LED
        break;
      case key1:        //若遙控器按1鍵，眉開眼笑
        eyebrow(LEDs.Color(255,0,0),100); //紅眉毛
        eyebrow(LEDs.Color(0,255,0),100); //綠眉毛
        eyebrow(LEDs.Color(0,0,255),100); //藍眉毛
        eyebrow(LEDs.Color(255,255,255),100); //白眉毛
        break;
      case key2:        //若遙控器按2鍵，群蛙亂跳
        theaterChase(LEDs.Color(255,0,0), 60);  //紅蛙亂跳
        theaterChase(LEDs.Color(0,255,0), 60);  //綠蛙亂跳
        theaterChase(LEDs.Color(0,0,255), 60);  //藍蛙亂跳
        theaterChase(LEDs.Color(255,255,255), 60);  //白蛙亂跳
        break;
      case key3:        //若遙控器按3鍵，彩虹漸變
        rainbow(100);     //慢動
        rainbow(50);      //快動
        break;
      case key4:        //若遙控器按4鍵，彩虹輪動
        rainbowCycle(5, 10);    //連續五圈
        break;
    }
    irrecv.resume();      //進入待命狀態
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

