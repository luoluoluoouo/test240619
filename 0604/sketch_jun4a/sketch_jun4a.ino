//init
  //按鈕
    const int PB[4] = { 12, 11, 10, 9 };  //宣告A0腳~A4腳為PB[0]~PB[3]
    int pp = 0;  //按鈕指標
    #define Off 1
    #define On 0

  //按鈕鍵盤
    const int col[4] = { A0, A1, A3, A4 };  //宣告A0腳~A3腳為col[0]~col[3](按鈕狀態)

  //可變電阻
    const int VR=A2;      //宣告A2腳連接VR信號

  //搖桿
    // const int jV=A3,jH=A4,jPB=A5;   //宣告A3~A5腳連接jV,jH與jPB信號

  //LED
    //const int LED[8]={9,8,7,6,5,4,3,2}; //宣告9腳~2腳為LED[0]~LED[7] 

  //七段顯示器
    const int scan[4] = { 5, 6, 7, 8 };     //宣告5腳~8腳為scan[0]~scan[3](掃描接腳)
    // const int dataPin = 10, latchPin = 11, clockPin = 12;
    // //宣告10腳連接串列資料，11腳連接栓鎖信號，12接腳移位脈波信號
    // // const int PP=9; //閃秒
    // // const int segCode[] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90}; //0~9
    // const int barCode[] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F,0xFF}; //A~G + .
    // int dispData[4] = { 0, 0, 0, 0 };  //宣告顯示暫存區

  //繼電器
    // const int relayPin = 4;

  //蜂鳴器
    const int buzzerPin = 13;  //宣告buzzerPin信號連接13腳

  //馬達
    const int M1=2, M2=3;    //宣告2腳連接M1、3腳連接M2信號

  //I2C LCD
    #include  <Wire.h>          //掛載Wire.h標頭檔
    #include  <LiquidCrystal_I2C.h>   //掛載LiquiaCrystal_I2C.h標頭檔
    const int Address=0x27;       //宣告I2C位址
    LiquidCrystal_I2C  I2C_LCD(Address,16,2); //建構LiquiaCrystal_I2C.h物件

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
      // pinMode(dataPin, OUTPUT);     //將dataPin腳規畫為輸出埠
      // pinMode(clockPin, OUTPUT);    //將clockPin腳規畫為輸出埠
      // pinMode(latchPin, OUTPUT);    //將latchPin腳規畫為輸出埠
      // digitalWrite(latchPin, 0);    //latchPin初值設定為0
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
    //LCD
      I2C_LCD.begin();        //啟用LCD
      I2C_LCD.backlight();    //開啟LCD背光
      I2C_LCD.home();       //游標歸位

    //Serial
      Serial.begin(9600);
  }

//main
  void loop() {
    //根據題目要求呼叫函式
    // Q1(); // 題目一函式
    // Q2(); // 題目二函式
    // Q3(); // 題目三函式
  }

int vrValue = 0; // 宣告一個變數用來存儲可變電阻的值
void Q1() { // 題目一函式
  int vrValue = analogRead(VR); // 讀取可變電阻的值

  // 將可變電阻的值映射到馬達的速度
  int motorSpeed = map(vrValue, 0, 1023, 0, 255); 
  analogWrite(M1, motorSpeed); // 設定 M1 馬達的轉速
  analogWrite(M2, 0); // 設定 M2 馬達的轉速歸零

  // 將可變電阻的值映射到蜂鳴器的頻率
  int freq = map(vrValue, 0, 1023, 200, 2000); 
  tone(buzzerPin, freq); // 設定蜂鳴器的頻率

  // 在LCD上顯示馬達轉速
  I2C_LCD.home();        // 將 LCD 的游標設定到起始位置
  I2C_LCD.print("Motor Speed: "); // 在 LCD 上顯示文字
  if(motorSpeed<100) I2C_LCD.print(" ");
  if(motorSpeed<10) I2C_LCD.print(" ");
  I2C_LCD.print(motorSpeed); // 在 LCD 上顯示馬達的轉速
  // 在LCD上顯示蜂鳴器頻率
  I2C_LCD.setCursor(0, 1);
  I2C_LCD.print("Frequency: "); // 在 LCD 上顯示文字
  I2C_LCD.print(" ");
  if(freq<1000) I2C_LCD.print(" ");
  if(freq<100) I2C_LCD.print(" ");
  if(freq<10) I2C_LCD.print(" ");
  I2C_LCD.print(freq);
}

int get = 0; // 宣告一個變數用來存儲鍵值
void Q2() { // 題目二函式
  for(int i=0;i<4;i++) { // 迴圈4次，每次處理一個掃描信號
    digitalWrite(scan[i], 0);   //輸出掃描信號(從R0開始)
    //讀取按鈕部分
    for(int j=0;j<4;j++) { // 迴圈4次，每次讀取一個按鈕
      int pb=digitalRead(col[j]); //讀取行信號(按鈕)
      if(!pb) {         //若按鈕被按下
        while(!pb) {      //等待按鈕放開
          digitalWrite(scan[i], 0); //重新輸出掃描信號
          pb=digitalRead(col[j]); //讀取行信號(按鈕)
        }
        get = 4*i+j;    //計算鍵值，並放入個位數暫存區
      }
    }
    digitalWrite(scan[i], 1);   //關閉掃描信號
  } 
  I2C_LCD.print(decToBin(get)); // 在LCD上顯示鍵值的二進制表示
  delay(10); // 延遲10毫秒
  I2C_LCD.home();       //游標歸位
  I2C_LCD.clear(); // 清除LCD顯示以便下一次顯示
}

// 將十進制數字轉換為二進制字串
String decToBin(int dec) {
  if (dec == 0) return "0";
  else if (dec == 1) return "1";
  else return decToBin(dec / 2) + String(dec % 2);
}


int Num[] = {0,0,0,0}; //建立一個數字陣列用ㄧ來存儲鍵盤輸入的數字
float Num12[] = {0,0}; // 建立一個陣列來存儲兩個數字
float result = 0; // 宣告一個變數用來存儲計算結果
//將數字陣列轉換為數字
int Numlist2num() {
  return Num[3] + Num[2]*10 + Num[1]*100 + Num[0]*1000;
}
void Q3() { // 題目三函式
  for(int k=0;k<2;k++) { // 迴圈兩次，每次獲取一個數字
    int times = 0; // 設定一個計數器
    for(int i=0;i<4;i++) Num[i] = 0; // 初始化數字陣列
    while(times < 4) { // 當計數器小於4時，繼續執行
      for(int i=0;i<4;i++) { // 迴圈4次，每次讀取一個按鈕
        digitalWrite(scan[i], 0);   //輸出掃描信號(從R0開始)
        //讀取按鈕部分
        for(int j=0;j<4;j++) {
          int pb=digitalRead(col[j]); //讀取行信號(按鈕)
          if(!pb) {         //若按鈕被按下
            while(!pb) {      //等待按鈕放開
              digitalWrite(scan[i], 0); //重新輸出掃描信號
              pb=digitalRead(col[j]); //讀取行信號(按鈕)
            }
            Num[times] = (4*i+j); // 將按鈕的值存入數字陣列
            Num12[k] = Numlist2num(); // 將數字陣列轉換為數字並存入Num12陣列
            times += 1; // 計數器加1
          }
        }
        digitalWrite(scan[i], 1);   //關閉掃描信號
      } 

      // 將Num1與Num2的值顯示在LCD上
      for(int N=0;N<4;N++) {
        I2C_LCD.setCursor(0,N);  //設定游標位置
        I2C_LCD.print("Num");I2C_LCD.print(N);I2C_LCD.print(":");
        if(Num12[N]<1000) I2C_LCD.print("0");
        if(Num12[N]<100) I2C_LCD.print("0");
        if(Num12[N]<10) I2C_LCD.print("0");
        // 將Num1與Num2的值轉換為整數後顯示在LCD上
        I2C_LCD.print(int(Num12[N])); 
      } 
    }
  }

  // 顯示計算結果
  I2C_LCD.setCursor(10, 0);
  I2C_LCD.print("Ans:");
  while(1) { // 重複執行
    readPb();  //讀取按鈕
    switch(pp) { // 根據按鈕的值進行運算
      case 1: result = Num12[0] + Num12[1]; break; // 加法
      case 2: result = Num12[0] - Num12[1]; break; // 減法
      case 3: result = Num12[0] * Num12[1]; break; // 乘法
      case 4: result = Num12[0] / Num12[1]; break; // 除法
      default: break;
      }
      // 將結果顯示在LCD上
      I2C_LCD.setCursor(9, 1);
      if(result<1000000) I2C_LCD.print(" ");
      if(result<100000) I2C_LCD.print(" ");
      if(result<10000) I2C_LCD.print(" ");
      I2C_LCD.print(result);
      delay(100); // 延遲100ms
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
