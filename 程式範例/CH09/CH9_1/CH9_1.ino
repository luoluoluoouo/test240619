// ===== ch9_1.ino =====
const int scan[4]={5,6,7,8};    //宣告5腳~8腳為scan[0]~scan[3](掃描接腳)
const int PP=9,dataPin=10,latchPin=11,clockPin=12;    
//宣告9腳連接閃秒點
//宣告10腳連接串列資料，11腳連接栓鎖信號，12接腳移位脈波信號
const int segCode[]={ 0xC0,0xF9,0xA4,0xB0,0x99, 0x92,0x82,0xF8,0x80,0x90};
//宣告0~9編碼
int dispData[4]={0,0,1,0};  //宣告顯示暫存區，初值為01:00
//dispData[3]:時之十位數、dispData[2]:時之個位數
//dispData[1]:分之十位數、dispData[0]:分之個位數
unsigned long CK=0; //宣告系統時間變數
byte scanP=0;     //宣告掃描指標變數
byte milliSec=0;      //宣告毫秒變數
byte pp=0;        //宣告半秒變數
byte seconds=0;     //宣告秒變數
byte minutes=0;     //宣告分變數
byte hours=1;     //宣告時變數
//初始設定
void setup() {
  for(int i=0;i<4;i++) {
    pinMode(scan[i], OUTPUT);     //將scan[0]~scan[3]腳規畫為輸出埠
    digitalWrite(scan[i], 1);     //關閉scan[0]~scan[3]
  }
  pinMode(dataPin, OUTPUT);       //將dataPin腳規畫為輸出埠
  pinMode(clockPin, OUTPUT);      //將clockPin腳規畫為輸出埠
  pinMode(latchPin, OUTPUT);      //將latchPin腳規畫為輸出埠
  digitalWrite(latchPin, 0);      //latchPin初值設定為0
  CK = millis();          //取得系統時間
  pinMode(PP, OUTPUT);      //將PP腳規畫為輸出埠
}
//主程式
void loop() {
  if((millis()-CK)>=2) {        //每2ms執行一次
    CK = millis();              //儲存目前時間
    //掃描七段顯示器
    if((++scanP)==4) scanP=0;       //下一個位數
    for(int dig=0;dig<4;dig++)
      digitalWrite(scan[dig], 1);     //清除掃描信號
    digitalWrite(latchPin, 0);      //解除資料栓鎖
    shiftOut(dataPin, clockPin, MSBFIRST, segCode[dispData[scanP]]);
    //輸出顯示資料
    digitalWrite(latchPin, 1);      //栓鎖資料
    digitalWrite(scan[scanP], 0);   //輸出掃描信號
    //時間處理
    if((++milliSec)==250) {     //半秒(500ms)
      milliSec=0;               //milliSec歸零
      pp=!pp;                   //切換閃秒指標
      digitalWrite(PP, pp);     //輸出閃秒信號
      if(pp) {                  //1秒
        if(++seconds==60) {     //59秒
          seconds=0;            //秒歸零
          if(++minutes==60) {   //59分
            minutes=0;          //分歸零
            if(++hours==13){    //12時
              hours=1;          //時歸零(1)
            }  //12時迴圈
            dispData[3]=hours/10; //擷取時之十位數
            dispData[2]=hours%10; //擷取時之個位數
          }  //59分迴圈
          dispData[1]=minutes/10;   //擷取分之十位數
          dispData[0]=minutes%10; //擷取分之個位數
        }  //59秒迴圈
      } //1秒迴圈
    }  //半秒迴圈
  }  //毫秒迴圈
}

