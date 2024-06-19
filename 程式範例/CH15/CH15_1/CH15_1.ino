// ===== ch15_1.ino =====
// ===== 藍牙控制LED =====
#include <SoftwareSerial.h >      //掛載SoftwareSerial函數庫
const int RXD=5, TXD=6;     //宣告5腳連接RXD信號、6腳連接TXD信號
SoftwareSerial myBT(RXD, TXD);  //建構軟體串列埠
const int LED[]={12,11,10,9, 8,7,4,3};  //宣告LED接腳
const int ON=0,OFF=1;     //宣告低態動作信號
int inst=0;   //宣告變數
void eyebrow(void);         //宣告眉開眼笑函數
void pili(void);          //宣告霹靂燈函數
void wipers(void);        //宣告雨刷函數
//初始設定
void setup() {
  for(int i=0;i<8;i++){     
    pinMode(LED[i], OUTPUT);  //將LED腳規畫為輸出埠
    digitalWrite(LED[i], OFF);    //LED初值設定為OFF
    }
    myBT.begin(9600);         //啟用藍牙模組，鮑率為9600
}
//主程式
void loop() {
  if(myBT.available()>0) inst=myBT.read();  //讀取藍牙信號
  switch (inst) {         //根據藍牙信號
    case '0':           //若藍牙信號=0
      for(int i=0;i<8;i++)        //關閉全部LED
       digitalWrite(LED[i],OFF);
      break;
    case '1':           //若藍牙信號=1
      eyebrow();          //眉開眼笑
      break;
    case '2':           //若藍牙信號=2
      pili();           //霹靂燈
      break;
    case '3':           //若藍牙信號=3
      wipers ();          //雨刷
      break;
  }
}
//自建函數
void eyebrow(void){           //眉開眼笑
  for(int i=0;i<4;i++){
    digitalWrite(LED[3-i], ON);     //點亮LED[3-i]
    digitalWrite(LED[4+i], ON);     //點亮LED[4+i]
    delay(100);           //持續0.1秒
    digitalWrite(LED[3-i], OFF);    //關閉LED[3-i]
    digitalWrite(LED[4+i], OFF);    //關閉LED[4+i]
  }
}
void pili(void){          //霹靂燈
  //單燈右移
  for(int i=0;i<8;i++){
    digitalWrite(LED[i], ON);       //點亮LED[i]
    delay(100);           //持續0.1秒
    digitalWrite(LED[i], OFF);    //關閉LED[i]
  }
  //單燈左移
  for(int i=0;i<8;i++){
    digitalWrite(LED[7-i], ON);     //點亮LED[7-i]
    delay(100);           //持續0.1秒
    digitalWrite(LED[7-i], OFF);    //關閉LED[7-i]
  }
}
void wipers(void){          //雨刷
  for(int i=0;i<4;i++){
    digitalWrite(LED[i], ON);       //點亮LED[i]
    digitalWrite(LED[4+i], ON);     //點亮LED[4+i]
    delay(100);           //持續0.1秒
  }
  for(int i=3;i>=0;i--){
    digitalWrite(LED[i], OFF);       //關閉LED[i]
    digitalWrite(LED[4+i], OFF);     //關閉LED[4+i]
    delay(100);           //暫停0.1秒
   }
}

