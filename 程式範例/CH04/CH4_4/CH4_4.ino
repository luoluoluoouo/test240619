// ===== ch4_4.ino =====
const int scan[4]={ 5,6,7,8};    //宣告5腳~8腳為scan[0]~scan[3](掃描接腳)
const int dataPin=10,latchPin=11,clockPin=12;   
//宣告10腳連接串列資料，11腳連接栓鎖信號，12接腳移位脈波信號
const int segCode[11]=
{0xC0,0xF9,0xA4,0xB0,0x99,  0x92,0x82,0xF8,0x80,0x90,  0x7F};
//宣告0~9, .編碼
const int dispData[13]={10,10,10, 0,1,2,3,4,5,6,7,8,9};//宣告所要顯示的資料
int sh=0;

void setup() {
  for(int i=0;i<4;i++) {
    pinMode(scan[i], OUTPUT); //將scan[0]~scan[3]腳規畫為輸出埠
    digitalWrite(scan[i], 1);   //關閉scan[0]~scan[3]
  }
  pinMode(dataPin, OUTPUT);   //將dataPin腳規畫為輸出埠
  pinMode(clockPin, OUTPUT);    //將clockPin腳規畫為輸出埠
  pinMode(latchPin, OUTPUT);    //將latchPin腳規畫為輸出埠
  digitalWrite(latchPin, 0);      //latchPin初值設定為0
}

void loop() {
  for(int j=0;j<50;j++) {     //步進間距0.2秒
    for(int i=0;i<4;i++) {
      digitalWrite(latchPin, 0);    //解除資料栓鎖
      shiftOut(dataPin, clockPin, MSBFIRST, segCode[dispData[(i+sh)%13]]);
    //輸出顯示資料
      digitalWrite(latchPin, 1);    //栓鎖資料
      digitalWrite(scan[3-i], 0); //輸出掃描信號
      delay(1);       //暫停1毫秒
      digitalWrite(scan[3-i], 1); //關閉掃描信號
    }
  }
  if(++sh>=13) sh=0;      //移位
}

