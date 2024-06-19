// ===== ch7_2.ino =====
const int VR=A2, LED=3; //宣告A2腳連接VR信號、3腳連接LED信號
int tmp=0;              //宣告暫存變數
//==================================
void setup() {
  pinMode(LED, OUTPUT);   //將LED腳規畫為輸出埠
  digitalWrite(LED, 0);   //LED初值設定為0
  Serial.begin(9600);      //啟用串列埠，而其傳輸率設定為9600bps
}
//==================================
void loop() {
  int i=analogRead(VR);       //讀取VR2上的電壓
  int j=map(i, 0, 1023, 0, 255);    //轉換範圍
  if (j!=tmp){                //若有變動
    tmp=j;                    //儲存
    analogWrite(LED,j);       //輸出到LED
    Serial.print("VR2: ");     //在序列埠監控視窗裡展示VR2:
    Serial.println(i);         //展示輸入電壓，並換行
    Serial.print("LED: ");     //在序列埠監控視窗裡展示LED:
    Serial.println(j);         //展示輸出電壓，並換行
    Serial.println();          //空行，並換行
    } 
  delay(100);                 //暫停0.1秒
}

