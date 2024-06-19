// ===== ch10_2.ino =====
// ===== 直流馬達轉向控制 =====
const int pbF=A4, pbR=A5;    //宣告A4腳連接pbF信號、A5腳連接pbR信號
const int M1=2, M2=3;     //宣告2腳連接M1信號、3腳連接M2信號
//初始設定
void setup() {
  pinMode(M1, OUTPUT);      //將M1腳規畫為輸出埠
  digitalWrite(M1, 0);        //M1初值設定為0
  pinMode(M2, OUTPUT);      //將M2腳規畫為輸出埠
  digitalWrite(M2, 0);        //M2初值設定為0
}
//主程式
void loop() {
  int F = digitalRead (pbF);    //讀取正轉按鈕
  int R = digitalRead (pbR);    //讀取反轉按鈕
  if(!F&&R) {                   //若只按下正轉按鈕
    digitalWrite(M1, 1);        //驅動直流馬達正轉
    digitalWrite(M2, 0); 
  } 
  else if(F&&!R)  {             //若只按下反轉按鈕
    digitalWrite(M1, 0);        //驅動直流馬達反轉
    digitalWrite(M2, 1); 
  } 
  else{
      digitalWrite(M1, 0);      //直流馬達停止
      digitalWrite(M2, 0); 
  }
  delay(100);           //暫停0.1秒
}

