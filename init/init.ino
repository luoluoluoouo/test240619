//init
  //按鈕
    const int PB[4] = { A0, A1, A2, 4 };  //宣告A0腳~A4腳為PB[0]~PB[3]
    int pp = 0;  //按鈕指標
    #define Off 1
    #define On 0

  //按鈕鍵盤
    //const int col[4] = { A0, A1, A2, A3 };  //宣告A0腳~A3腳為col[0]~col[3](按鈕狀態)

  //可變電阻
    // const int VR=A2;      //宣告A2腳連接VR信號

  //搖桿
    const int jV=A3,jH=A4,jPB=A5;   //宣告A3~A5腳連接jV,jH與jPB信號

  //LED
    //const int LED[8]={9,8,7,6,5,4,3,2}; //宣告9腳~2腳為LED[0]~LED[7] 

  //七段顯示器
    const int scan[4] = { 5, 6, 7, 8 };     //宣告5腳~8腳為scan[0]~scan[3](掃描接腳)
    const int dataPin = 10, latchPin = 11, clockPin = 12;
    //宣告10腳連接串列資料，11腳連接栓鎖信號，12接腳移位脈波信號
    // const int PP=9; //閃秒
    // const int segCode[] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90}; //0~9
    const int barCode[] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F,0xFF}; //A~G + .
    int dispData[4] = { 0, 0, 0, 0 };  //宣告顯示暫存區

  //繼電器
    // const int relayPin = 4;

  //蜂鳴器
    const int buzzerPin = 13;  //宣告buzzerPin信號連接13腳

  //馬達
    const int M1=2, M2=3;    //宣告2腳連接M1、3腳連接M2信號

  //S1
    int num = 0;
  //S2
    int leval = 0;
  //S3
    int wsad = 0;
    int S3Code[] = {0xFF,0xFE,0xF7,0xF9,0xCF}; //無,A,D,EF,BC
  //S4

  void setup() {
    //按鈕
      for (int i = 0; i < 4; i++) {
        pinMode(PB[i], INPUT);  //將scan[0]~scan[3]腳規畫為輸出埠
      }
    //LED
      // for(int i=0;i<8;i++) {
      //   pinMode(LED[i], OUTPUT);  //將LED[0]~LED[7]腳規畫為輸出埠
      //   digitalWrite(LED[i], Off);    //關閉LED[0]~LED[7]
      // }
    //七段顯示器
      for (int i = 0; i < 4; i++) {
        pinMode(scan[i], OUTPUT);  //將scan[0]~scan[3]腳規畫為輸出埠
        digitalWrite(scan[i], 1);  //關閉scan[0]~scan[3]
      }
      pinMode(dataPin, OUTPUT);     //將dataPin腳規畫為輸出埠
      pinMode(clockPin, OUTPUT);    //將clockPin腳規畫為輸出埠
      pinMode(latchPin, OUTPUT);    //將latchPin腳規畫為輸出埠
      digitalWrite(latchPin, 0);    //latchPin初值設定為0
      // pinMode(PP, OUTPUT);        //將PP腳規畫為輸出埠
      // digitalWrite(PP, Off);
    //繼電器
      // pinMode(relayPin, OUTPUT);    //將relayPin腳規畫為輸出埠
      // digitalWrite(relayPin, Off);  //relayPin初值設定為off
    //蜂鳴器
      pinMode(buzzerPin, OUTPUT);   //將buzzerPin腳規畫為輸出埠
      digitalWrite(buzzerPin, 0);   //buzzerPin初值設定為0
    //馬達
      pinMode(M1, OUTPUT);      //將M1腳規畫為輸出埠
      digitalWrite(M1, 0);        //M1初值設定為0
      pinMode(M2, OUTPUT);      //將M2腳規畫為輸出埠
      digitalWrite(M2, 0);        //M2初值設定為0

    //Serial
      Serial.begin(9600);
  }

//main
  void loop() {
    readPb();  //讀取按鈕
    switch(pp) {
      case 1:
        S1();
        break;
      case 2:
        S2(); 
        break;
      case 3:
        S3();
        break;
      case 4:
        S4(); 
        break;
      default:
        break;
      }
  }

void readPb(void){
  //若按鈕PB[0]被按下，則將按鈕指標pp=1
  if(!digitalRead(PB[0])) pp = 1; 
  //若按鈕PB[1]被按下，則將按鈕指標pp=2
  else if(!digitalRead(PB[1])) pp = 2;
  //若按鈕PB[2]被按下，則將按鈕指標pp=3 
  else if(!digitalRead(PB[2])) pp = 3; 
  //若按鈕PB[3]被按下，則將按鈕指標pp=4
  else if(!digitalRead(PB[3])) pp = 4; 
}

void S1() { //按鈕一程式

}

void S2() { //按鈕二程式
    
}

void S3() { //按鈕三程式

}

void S4() { //按鈕四程式

}
