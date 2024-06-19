// ===== ch11_1.ino =====
// ===== 搖桿控制LED =====
const int LED[]={12,11,10,9, 8,7,6,5};  //宣告12~5腳連接LED[0]~LED[7]
const int jV=A3,jH=A4,jPB=A5;   //宣告A3~A5腳連接jV,jH與jPB信號
//jV不使用
const int ON=0,OFF=1;       //宣告低態動作信號
//初始設定
void setup() {
  for(int i=0;i<8;i++){     
    pinMode(LED[i], OUTPUT);  //將LED[0]~LED[7]規畫為輸出埠
    digitalWrite(LED[i], OFF);    //將LED[0]~LED[7]初值設定為OFF
  } 
}
//主程式
void loop() {
  int PB = digitalRead (jPB);       //讀取搖桿之按鈕
  if(!PB){            //若按下搖桿之按鈕
    while (!PB){           //搖桿之按鈕被按下
      for(int i=0;i<8;i++){     
        digitalWrite(LED[i], ON); //將LED[0]~LED[7]設定為ON
      }
      PB = digitalRead (jPB);       //讀取搖桿之按鈕
    } 
  } 
  else {
    for(int i=0;i<8;i++){     
      digitalWrite(LED[i], OFF); //將LED[0]~LED[7]設定為OFF
    }
  }
  int H = analogRead (jH);      //讀取搖桿之水平電位計
  H=map(H, 0,1023,0,7);         //轉換範圍
    digitalWrite(LED[H], ON);   //將LED[H]設定為ON
  delay(100);                   //暫停0.1秒
}

