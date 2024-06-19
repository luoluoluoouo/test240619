// ===== ch7_3.ino =====
const int LED=3;    //宣告3腳連接LED信號
int tmp0=0,tmp1=0;    //宣告變數
//==================================
void setup() {
  pinMode(LED, OUTPUT); //將LED腳規畫為輸出埠
  digitalWrite(LED, 0);   //LED初值設定為0
  Serial.begin(9600);     //啟用串列埠，而其傳輸率設定為9600bps
}
//==================================
void loop() {
  bool num=true,enter=false;      //設定指標
  if (Serial.available()>0){  //若序列埠接收到資料
    char x= Serial.read();   //讀取資料
    if (x=='\n') enter=true;//檢查是否有換行符號？
    else 
      if (isDigit(x))        //若讀取的資料是數字
          tmp0=tmp0*10+x-48;  //轉換數值
      else num=false;     //非數值
  } 
  if (enter){
    if (tmp0>255) tmp0=255;   //截掉超過部分
    if (num && tmp0!=tmp1){   //若輸入成功，且輸入數值與原數值不同
      tmp1=tmp0;      //儲存數值
      tmp0=0;      //tmp0歸零
      analogWrite(LED, 255-tmp1);  //驅動LED
      Serial.println(tmp1);     //展示輸入電壓，並換行
      Serial.println();     //空行，並換行
      enter=false;
    }
  } 
  delay(100);         //暫停0.1秒
}

