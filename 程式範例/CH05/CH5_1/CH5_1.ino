// ===== ch5_1.ino =====
const int upCount=A0, downCount=A1;
//宣告A0腳~A1腳為upCount與downCount接腳
const int scan[4]={5,6,7,8};    //宣告5腳~8腳為scan[0]~scan[3](掃描接腳)
const int dataPin=10,latchPin=11,clockPin=12;   
//宣告10腳連接串列資料，11腳連接栓鎖信號，12接腳移位脈波信號
const int segCode[10]={0xC0,0xF9,0xA4,0xB0,0x99, 0x92,0x82,0xF8,0x80,0x90};
//宣告0~9編碼
int dispData[4]={0,0,0,0};//宣告顯示暫存器
const int buzzerPin=13;   //宣告buzzerPin信號連接13腳
int counter=0;            //宣告counter計數器變數
void Transfer(void);      //宣告Transfer()函數
void doDownCount(void);   //宣告doDownCount()函數
void doUpCount(void);     //宣告doUpCount()函數
void scan7seg(void);      //宣告scan7seg()函數
//==================================
void setup() {
  for(int i=0;i<4;i++) {
    pinMode(scan[i], OUTPUT); //將scan[0]~scan[3]腳規畫為輸出埠
    digitalWrite(scan[i], 1);   //關閉scan[0]~scan[3]
  }
  pinMode(dataPin, OUTPUT);   //將dataPin腳規畫為輸出埠
  pinMode(clockPin, OUTPUT);    //將clockPin腳規畫為輸出埠
  pinMode(latchPin, OUTPUT);    //將latchPin腳規畫為輸出埠
  digitalWrite(latchPin, 0);      //latchPin初值設定為0
  pinMode(buzzerPin, OUTPUT); //將buzzerPin腳規畫為輸出埠
  digitalWrite(buzzerPin, 0);   //buzzerPin初值設定為0
}
//==================================
void loop() {
  scan7seg();         //顯示
  int i=digitalRead(upCount);    //讀取S1鈕(上數鈕)
  if(!i) {            //若按上數鈕
    doUpCount();        //上數
    beep();         //嗶一聲
    while(!i) {         //等待放開上數鈕
      i=digitalRead(upCount);  //讀取上數鈕
      scan7seg();     //顯示
    }
  }
  else{
    int i=digitalRead(downCount);  //讀取S2鈕(下數鈕)
    if(!i) {          //若按下數鈕
      doDownCount();    //下數
      beep();       //嗶一聲
      while(!i) {       //等待放開下數鈕
        i=digitalRead(downCount);  //讀取下數鈕
        scan7seg();       //顯示
      }
    }
  }
}
//自建函數
//嗶聲函數
void beep(void) {
  tone(buzzerPin, 1000);//產生1KHz聲音
  delay(100);           //持續0.1秒
  noTone(buzzerPin);    //停止產生聲音
}
//顯示函數
void scan7seg() {
  for(int i=0;i<4;i++) {
    digitalWrite(latchPin, 0);    //解除資料栓鎖
    shiftOut(dataPin, clockPin, MSBFIRST, segCode[dispData[i]]);
    //輸出顯示資料
    digitalWrite(latchPin, 1);    //栓鎖資料
    digitalWrite(scan[3-i], 0);   //輸出掃描信號
    delay(1);         //暫停1毫秒
    digitalWrite(scan[3-i], 1);   //關閉掃描信號
  }
}
//上數函數
void doUpCount() {
  if(++counter>=10000) counter=0; //若超過9999則歸零
  Transfer();         //將計數器值轉換為顯示四位數顯示值
}
//下數函數
void doDownCount() {
  if(--counter<0) counter=9999; //若低於0，則回9999
  Transfer();                   //將計數器值轉換為顯示四位數顯示值
}
//下數函數
void Transfer() {
  dispData[3]=counter%10;     //擷取個位數
  dispData[2]=counter/10%10;  //擷取十位數
  dispData[1]=counter/100%10; //擷取百位數
  dispData[0]=counter/1000;   //擷取千位數
  scan7seg();                 //將計數器值轉換為顯示四位數顯示值
}

