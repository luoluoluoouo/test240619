// ===== ch9_Ex.ino =====
const int relayPin=4;       //宣告4腳連接繼電器
const int ON=0, OFF=1;    //宣告ON為低態、OFF為高態(低態動作)
const int dipSw1=A0;      //宣告A0腳連接模式切換指撥開關
const int dipSw2=A1;      
//宣告A1腳連接調整時間(ON)/設定繼電器開關時間(OFF)
const int hoursPb=A4;     //宣告A4腳連接時調整按鈕開關
const int minutesPb=A5;     //宣告A5腳連接分調整按鈕開關
const int buzzerPin=13;     //宣告13腳連接蜂鳴器
const int scan[4]={5,6,7,8};    //宣告5腳~8腳為scan[0]~scan[3](掃描接腳)
const int PP=9,dataPin=10,latchPin=11,clockPin=12;    
//宣告9腳連接閃秒點
//宣告10腳連接串列資料，11腳連接栓鎖信號，12接腳移位脈波信號
const int segCode[]={ 0xC0,0xF9,0xA4,0xB0,0x99, 0x92,0x82,0xF8,0x80,0x90};
//宣告0~9編碼
int dispData[4]={0,0,1,0};  //宣告顯示暫存區，初值為01:00
//dispData[3]:時之十位數、dispData[2]:時之個位數
//dispData[1]:分之十位數、dispData[0]:分之個位數
int relayData[4]={0,0,1,0}; //宣告顯示暫存區，初值為01:00
//relayData[3]:時之十位數、relayData[2]:時之個位數
//relayData[1]:分之十位數、relayData[0]:分之個位數
unsigned long CK=0;   //宣告系統時間變數
byte scanP=0;     //宣告掃描指標變數
byte milliSec=0;      //宣告毫秒變數
byte pp=0;        //宣告半秒變數
byte seconds=0;     //宣告秒變數
byte minutes=0;     //宣告分變數
byte hours=1;     //宣告時變數
byte minutesSet=0;    //宣告開啟時間之分變數
byte hoursSet=1;    //宣告開啟時間之時變數
void tBeep(void);   //宣告正點報時函數
//Switch=0(ON)顯示時鐘、Switch=1(OFF)顯示繼電器動作時間
void scan7seg(int x, bool Switch);//宣告顯示函數
//初始設定
void setup() {
  for(int i=0;i<4;i++) {
    pinMode(scan[i], OUTPUT);     //將scan[0]~scan[3]腳規畫為輸出埠
    digitalWrite(scan[i], 1);         //關閉scan[0]~scan[3]
  }
  pinMode(dataPin, OUTPUT);     //將dataPin腳規畫為輸出埠
  pinMode(clockPin, OUTPUT);      //將clockPin腳規畫為輸出埠
  pinMode(latchPin, OUTPUT);      //將latchPin腳規畫為輸出埠
  digitalWrite(latchPin, 0);        //latchPin初值設定為0
  pinMode(buzzerPin, OUTPUT);   //將buzzerPin腳規畫為輸出埠
  digitalWrite(buzzerPin, 0);     //buzzerPin初值設定為0
  pinMode(relayPin, OUTPUT);      //將relayPin腳規畫為輸出埠
  digitalWrite(relayPin, OFF);      //relayPin初值設定為OFF
  CK = millis();          //取得系統時間
  pinMode(PP, OUTPUT);        //將PP腳規畫為輸出埠
}
//主程式
void loop() {
  //讀取模式指撥開關(ON=0計時, OFF=1調整)
  bool modeSw= digitalRead(dipSw1);
  //讀取typeSw指撥開關(ON=調整時間, OFF=1設定繼電器動作時間)
  bool typeSw= digitalRead(dipSw2);
//調整模式========================================
  while(modeSw && typeSw){//OFF,OFF設定繼電器動作時間
    modeSw= digitalRead(dipSw1);
    typeSw= digitalRead(dipSw2);
    scan7seg(5,1);            //顯示繼電器動作時間
    //調整分
    bool mTune= digitalRead(minutesPb);   //讀取minutesPb
    while(!mTune){
      if(++minutesSet==60) minutesSet=0;  //調整分
      relayData[1]=minutesSet/10;     //擷取分之十位數
      relayData[0]=minutesSet%10;     //擷取分之個位數
      scan7seg(12,1);         //顯示顯示繼電器動作時間
      mTune= digitalRead(minutesPb);    //讀取minutesPb
    }
    //調整時
    bool hTune= digitalRead(hoursPb);     //讀取hoursPb
    while(!hTune){
      if(++hoursSet==13) hoursSet=1;    //調整時
      relayData[3]=hoursSet/10;     //擷取時之十位數
      relayData[2]=hoursSet%10;     //擷取時之個位數
      scan7seg(12,1);         //顯示顯示繼電器動作時間
      hTune= digitalRead(hoursPb);    //讀取hoursPb
    }
  }  
//====================================
  while(modeSw && !typeSw){//OFF,ON調整時間
    modeSw= digitalRead(dipSw1);
    typeSw= digitalRead(dipSw2);
    scan7seg(5,0);            //顯示時鐘時間
    //調整分
    bool mTune= digitalRead(minutesPb);   //讀取minutesPb
    while(!mTune){
      if(++minutes==60) minutes=0;      //調整分
      dispData[1]=minutes/10;       //擷取分之十位數
      dispData[0]=minutes%10;     //擷取分之個位數
      scan7seg(12,0);         //顯示時鐘時間
      mTune= digitalRead(minutesPb);    //讀取minutesPb
    }
    //調整時
    bool hTune= digitalRead(hoursPb);     //讀取hoursPb
    while(!hTune){
      if(++hours==13) hours=1;      //調整時
      dispData[3]=hours/10;       //擷取時之十位數
      dispData[2]=hours%10;       //擷取時之個位數
      scan7seg(12,0);         //顯示時鐘時間
      hTune= digitalRead(hoursPb);    //讀取hoursPb
    }
  }  
//====================================
//計時模式========================================
  while(!modeSw){
    //讀取指撥開關(ON=0計時, OFF=1調整)
    modeSw= digitalRead(dipSw1);
    if((millis()-CK)>=2) {        //每2ms執行一次
      CK = millis();          //儲存目前時間
      //掃描七段顯示器
      if((++scanP)==4) scanP=0;   //下一個位數
      for(int dig=0;dig<4;dig++)
        digitalWrite(scan[dig], 1);       //清除掃描信號
      digitalWrite(latchPin, 0);      //解除資料栓鎖
      shiftOut(dataPin, clockPin, MSBFIRST, segCode[dispData[scanP]]);
    //輸出顯示資料
      digitalWrite(latchPin, 1);      //栓鎖資料
      digitalWrite(scan[scanP], 0);   //輸出掃描信號
      //時間處理
      if((++milliSec)==250) {     //半秒(500ms)
        milliSec=0;         //milliSec歸零
        pp=!pp;         //切換閃秒指標
        digitalWrite(PP, pp);     //輸出閃秒信號
        if(pp) {          //1秒
          if(++seconds==60) {   //59秒
            seconds=0;      //秒歸零
            if(++minutes==60) {   //59分
              minutes=0;      //分歸零
              tBeep();      //正點報時
              if(++hours==13){    //12時
                hours=1;      //時歸零(1)
              }  //12時迴圈
              dispData[3]=hours/10; //擷取時之十位數
              dispData[2]=hours%10; //擷取時之個位數
            }  //59分迴圈
            dispData[1]=minutes/10; //擷取分之十位數
            dispData[0]=minutes%10; //擷取分之個位數
            //檢查是否到達設定時間
            if(minutes==minutesSet && hours==hoursSet)
              digitalWrite(relayPin, 0); //繼電器激磁
            //10分鐘後關閉繼電器
            if(minutes==(minutesSet+10) && hours==hoursSet)
              digitalWrite(relayPin, 1); //繼電器斷磁
          }  //59秒迴圈
        }  //1秒迴圈
      }  //半秒迴圈
    }  //毫秒迴圈
  }
}
//自建函數
//宣告正點報時函數
void tBeep(void){
  for(int cnts=0;cnts<2;cnts++){  //248ms*2約0.5秒
    tone(buzzerPin,1000); //產生1KHz嗶聲
    scan7seg(16,0);       //顯示(8m*16=128ms)
    noTone(buzzerPin);  //靜音
    scan7seg(15,0);       //顯示(8ms*15=120ms)
  }
  pp=!pp;       //切換閃秒指標
  CK = millis();      //儲存目前時間
}
//宣告顯示函數(8ms)
//Switch=0(ON)顯示時鐘、Switch=1(OFF)顯示繼電器動作時間
void scan7seg(int x, bool Switch){ 
  if(Switch) {    //DIP2 OFF：顯示繼電器動作時間
    for(int j=0;j<x;j++) {
      for(int i=0;i<4;i++) {
        digitalWrite(latchPin, 0);      //解除資料栓鎖
        shiftOut(dataPin, clockPin, MSBFIRST, segCode[relayData[i]]);
        //輸出顯示資料
        digitalWrite(latchPin, 1);      //栓鎖資料
        digitalWrite(scan[i], 0);     //輸出掃描信號
        delay(2);             //暫停2毫秒
        digitalWrite(scan[i], 1);   //關閉掃描信號
      }
    }
  }
  else  {     //DIP2 ON：顯示時鐘時間
    for(int j=0;j<x;j++) {
      for(int i=0;i<4;i++) {
        digitalWrite(latchPin, 0);      //解除資料栓鎖
        shiftOut(dataPin, clockPin, MSBFIRST, segCode[dispData[i]]);
        //輸出顯示資料
        digitalWrite(latchPin, 1);      //栓鎖資料
        digitalWrite(scan[i], 0);     //輸出掃描信號
        delay(2);             //暫停2毫秒
        digitalWrite(scan[i], 1);   //關閉掃描信號
      }
    }
  }
}

