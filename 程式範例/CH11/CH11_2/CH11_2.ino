// ===== ch11_2.ino =====
// ===== 搖桿控制直流馬達速度與轉向 =====
const int M1=2, M2=3;      //告2腳連接M1信號、3腳連接M2信號
const int jV=A3,jH=A4,jPB=A5; //宣告A3~A5腳連接jV,jH與jPB信號
// jH不使用, jPB不使用
//初始設定
void setup() {
  pinMode(M1, OUTPUT);      //將M1腳規畫為輸出埠
  digitalWrite(M1, 0);        //M1初值設定為0
  pinMode(M2, OUTPUT);      //將M2腳規畫為輸出埠
  digitalWrite(M2, 0);        //M2初值設定為0
  Serial.begin(9600);
}
//主程式
void loop() {
  
  int V = analogRead (jH);        //讀取垂直電位計
  Serial.println(V);
}

