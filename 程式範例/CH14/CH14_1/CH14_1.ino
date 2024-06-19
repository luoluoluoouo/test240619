// ===== ch14_1.ino =====
// ===== LCD顯示溫濕度 =====
#include  <Wire.h>    //掛載Wire.h標頭檔
#include  <LiquidCrystal_I2C.h> //掛載LiquiaCrystal_I2C.h標頭檔
const int Address=0x27;   //宣告I2C位址
LiquidCrystal_I2C  I2C_LCD(Address,16,2); //建構LiquiaCrystal_I2C.h物件
byte degree[]={ 0b00110,
        0b01001,
        0b01001,
        0b00110,
        0b00000,
        0b00000,
        0b00000,
        0b00000 }; 
#include <DHT.h>
const int dhtPin=A0;    //宣告A0腳連接dhtPin信號
DHT myDHT(dhtPin,DHT11);
float tempC=0.0,tempF=0.0,RH=0.0;
//宣告攝氏溫度(tempC)、華氏溫度(tempF)與濕度(RH)之變數
const int dipPin=A3;    //宣告A3腳連接dipPin信號
//初始設定
void setup() {
  I2C_LCD.begin();      //啟用LCD
  I2C_LCD.backlight();      //開啟LCD背光
  I2C_LCD.createChar(0,degree); //載入自建字元
  myDHT.begin();        //啟用DHT11
}
//主程式
void loop() {
  int dip = digitalRead (dipPin);       //讀取指撥開關
  I2C_LCD.home();         //啟用LCD歸位
  I2C_LCD.print("Temp. : ");      //顯示Temp. :
  if (dip) {              //指撥開關切到OFF位置(攝氏溫度)
    tempC = myDHT.readTemperature(0); //讀取攝氏溫度
    I2C_LCD.setCursor(8,0);       //游標移至(8,0)位置
    I2C_LCD.print(tempC);       //顯示攝氏溫度
    I2C_LCD.setCursor(14,0);    //游標移至(14,0)位置
    I2C_LCD.write(0);         //顯示度
    I2C_LCD.print("C");       //顯示C
  }
  else  {                 //指撥開關切到ON位置(華氏溫度)
    tempF = myDHT.readTemperature(1); //讀取華氏溫度
    I2C_LCD.setCursor(8,0);       //游標移至(8,0)位置
    I2C_LCD.print(tempF);       //顯示華氏溫度
    I2C_LCD.setCursor(14,0);    //游標移至(14,0)位置
    I2C_LCD.write(0);         //顯示度
    I2C_LCD.print("F");       //顯示F
  }
  RH = myDHT.readHumidity();      //讀取濕度
  I2C_LCD.setCursor(0,1);       //游標移至(0,1)位置
  I2C_LCD.print("Humi. : ");      //顯示Humi. :
  I2C_LCD.print(RH);        //顯示度
  I2C_LCD.print("%RH");       //顯示%RH
  delay(500);           //暫停0.5秒
}

