// ===== ch14_2.ino =====
// ===== LCD數位時鐘 =====
// ===== I2C LCD =====
#include  <Wire.h>          //掛載Wire.h標頭檔
#include  <LiquidCrystal_I2C.h>   //掛載LiquiaCrystal_I2C.h標頭檔
const int Address=0x27;       //宣告I2C位址
LiquidCrystal_I2C  I2C_LCD(Address,16,2); //建構LiquiaCrystal_I2C.h物件
// ===== 開關與蜂鳴器 =====
const int dip1Sw=A0;      //宣告A0腳連接顯示/調整模式切換指撥開關
const int dip2Sw=A1;      //宣告A1腳連接12/24模式切換指撥開關
const int hoursPb=A2;     //宣告A2腳連接時調整按鈕開關
const int minutesPb=A3;     //宣告A3腳連接分調整按鈕開關
const int buzzerPin=13;     //宣告13腳連接蜂鳴器
// ===== 時間 =====
unsigned long CK=0;   //宣告系統時間變數
byte seconds=0;     //宣告秒變數
byte minutes=0;     //宣告分變數
byte hours=1;     //宣告時變數
bool switchMode, timeMode;//宣告模式指標
void tBeep(void);   //宣告正點報時函數
void displayLCD(void); //宣告顯示函數
//初始設定
void setup() {
  I2C_LCD.begin();        //啟用LCD
  I2C_LCD.backlight();    //開啟LCD背光
  I2C_LCD.home();       //游標歸位
  pinMode(buzzerPin, OUTPUT);//將buzzerPin腳規畫為輸出埠
  digitalWrite(buzzerPin, 0); //buzzerPin初值設定為0
  CK = millis();      //取得系統時間
}
//主程式
void loop() {
  //讀取指撥開關(ON=0計時, OFF=1調整)
  switchMode= digitalRead(dip1Sw);  //讀取DIP1指撥開關
  //調整模式========================================
  while(switchMode){    //調整模式(DIP1指撥開關OFF)
    seconds=0;        //秒數歸零
    //顯示
    I2C_LCD.setCursor(0,1);     //cursor:0,1
    I2C_LCD.print("Tuning... "); //調整
    displayLCD();
    //讀取指撥開關(ON=0計時, OFF=1調整)
    switchMode = digitalRead(dip1Sw);
    //調整分
    bool mTune= digitalRead(minutesPb); //讀取minutesPb
    while(!mTune){
      if(++minutes==60) minutes=0;    //調整分
      I2C_LCD.setCursor(3,0);     //cursor:3,0
      I2C_LCD.print(minutes);     //分
      delay(200);           //每隔0.2秒加1
      mTune= digitalRead(minutesPb);  //讀取minutesPb
    }
    //調整時
    bool hTune= digitalRead(hoursPb);   //讀取hoursPb
    while(!hTune){ 
      timeMode= digitalRead(dip2Sw);  //讀取DIP2指撥開關
      //timeMode=true：12小時制(DIP2 OFF)
      //timeMode=false：24小時制(DIP2 ON)
    byte tt=timeMode? 12:24;    //設定時間顯示方式
      if(++hours==(tt+1)) hours=1;      //調整時
      I2C_LCD.setCursor(0,0);     //cursor:0,0
      I2C_LCD.print(hours);     //時
      delay(200);           //每隔0.2秒加1
      hTune= digitalRead(hoursPb); //讀取hoursPb
    }
  }
//計時模式========================================
  while(!switchMode){     //顯示時間模式(DIP1指撥開關ON)
    //顯示
    I2C_LCD.setCursor(0,1);     //cursor:0,1
    I2C_LCD.print("O'clock..."); //調整
    displayLCD();
    //讀取指撥開關(ON=0計時, OFF=1調整)
    switchMode= digitalRead(dip1Sw);
    if((millis()-CK)>=1000) {     //每1s執行一次
      CK = millis();          //儲存目前時間
      //時間處理
      timeMode= digitalRead(dip2Sw);  //讀取DIP2指撥開關
      //timeMode=true：12小時制(DIP2 OFF)
      //timeMode=false：24小時制(DIP2 ON)
    byte tt=timeMode? 12:24;    //設定時間顯示方式
      if(++seconds==60) {     //59秒
        seconds=0;      //秒歸零
        if(++minutes==60) {   //59分
          minutes=0;      //分歸零
          tBeep();      //正點報時
          if(++hours==(tt+1)){  //12/24時
            hours=1;      //時歸零(1)
          }  //12/24時迴圈
        }  //59分迴圈
      }  //59秒迴圈
    }  //1秒迴圈
  }
}
//自建函數
//宣告正點報時函數(嗶兩聲)
void tBeep(void){
  for(int cnts=0;cnts<2;cnts++){  
    tone(buzzerPin,1000);   //產生1KHz嗶聲
    delay(100);         //持續0.1秒
    noTone(buzzerPin);    //靜音
    delay(100);         //持續0.1秒
  }
}
//顯示函數
void displayLCD(void){
    I2C_LCD.home();       //游標歸位
    I2C_LCD.print("  ");     //清空
    I2C_LCD.home();       //游標歸位
    I2C_LCD.print(hours);     //時(cursor:0)
    I2C_LCD.setCursor(2,0);     //cursor:2,0
    I2C_LCD.print(":");       //冒號(cursor:2)
    I2C_LCD.print("  ");     //清空
    I2C_LCD.setCursor(3,0);     //cursor:3,0
    I2C_LCD.print(minutes);     //分(cursor:3)
    I2C_LCD.setCursor(5,0);     //cursor:5,0
    I2C_LCD.print(":");       //冒號(cursor:5)
    I2C_LCD.print("  ");     //清空
    I2C_LCD.setCursor(6,0);     //cursor:6,0
    I2C_LCD.print(seconds);     //秒(cursor:6)
}

