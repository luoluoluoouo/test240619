// ===== ch8_1.ino =====
const int buzzerPin=13;//宣告13腳連接buzzerPin信號
const int col[4]={A0,A1,A2,A3};//宣告A0腳~A3腳為col[0]~col[3](按鈕狀態)
const int scan[4]={5,6,7,8};    //宣告5腳~8腳為scan[0]~scan[3](掃描接腳)
const int dataPin=10,latchPin=11,clockPin=12;   
//宣告10腳連接串列資料，11腳連接栓鎖信號，12接腳移位脈波信號
const int segCode[]={ 
  0xC0,0xF9,0xA4,0xB0,0x99, 0x92,0x82,0xF8,0x80,0x90,
  0x88, 0x83, 0xC6, 0xA1, 0x86,  0x8E, 0xFF};
//宣告0~9,A~F,空白編碼
int dispData[4]={16,16,16,16};  //宣告顯示暫存區
void shiftLeft(void);     //宣告左移函數
void disp7seg(void);     //宣告顯示函數
void beep(void);     //宣告嗶聲函數

void setup() {
  for(int i=0;i<4;i++) {
    pinMode(scan[i], OUTPUT); //將scan[0]~scan[3]腳規畫為輸出埠
    digitalWrite(scan[i], 1);   //關閉scan[0]~scan[3]
  }
  pinMode(dataPin, OUTPUT);   //將dataPin腳規畫為輸出埠
  pinMode(clockPin, OUTPUT);    //將clockPin腳規畫為輸出埠
  pinMode(latchPin, OUTPUT);    //將latchPin腳規畫為輸出埠
  digitalWrite(latchPin, 0);      //latchPin初值設定為0
  pinMode(buzzerPin, OUTPUT);    //將buzzerPin腳規畫為輸出埠
  digitalWrite(buzzerPin, 0);      //buzzerPin初值設定為0
}

void loop() {
  for(int i=0;i<4;i++) {
    disp7seg();          //掃描七段顯示器
    digitalWrite(scan[i], 0);   //輸出掃描信號(從R0開始)
    //讀取按鈕部分
    for(int j=0;j<4;j++) {
      int pb=digitalRead(col[j]); //讀取行信號(按鈕)
      if(!pb) {         //若按鈕被按下
        beep();         //嗶一聲
        while(!pb) {      //等待按鈕放開
          digitalWrite(scan[i], 0); //重新輸出掃描信號
          pb=digitalRead(col[j]); //讀取行信號(按鈕)
          disp7seg();      //掃描七段顯示器
        }
        shiftLeft();        //數字左移
        dispData[0]=4*i+j;    //計算鍵值，並放入個位數暫存區
      }
    }
    digitalWrite(scan[i], 1);   //關閉掃描信號
  } 
}
//自建函數
//左移函數
void shiftLeft(void){     
  dispData[3]= dispData[2];     //百位數移至千位數
  dispData[2]= dispData[1];     //十位數移至百位數
  dispData[1]= dispData[0];     //個位數移至十位數
}
//顯示函數
void disp7seg(void){     
  //for(int x=0;x<4;x++) digitalWrite(scan[x], 1);//清除掃描信號
  for(int dig=0;dig<4;dig++) {
    digitalWrite(latchPin, 0);    //解除資料栓鎖
    shiftOut(dataPin, clockPin, MSBFIRST, segCode[dispData[dig]]);
    //輸出顯示資料
    digitalWrite(latchPin, 1);    //栓鎖資料
    digitalWrite(scan[dig], 0);   //輸出掃描信號
    delay(1);         //暫停1毫秒
    digitalWrite(scan[dig], 1);   //關閉掃描信號
  }
}
//嗶聲函數
void beep(void) {   
    tone(buzzerPin, 1000);       //產生1KHz聲音
    for(int i=0;i<25;i++)  disp7seg();//顯示
    noTone(buzzerPin);
}

