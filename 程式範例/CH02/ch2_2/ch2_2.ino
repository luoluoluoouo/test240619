// ===== ch2_2.ino =====
const int LED=7;      //7腳為LED
const int pbON=A0;    // A0腳為pbON
const int pbOFF=A1;   // A1腳為pbOFF

void setup() {
  pinMode(LED, OUTPUT); //將LED腳規畫為輸出埠
  digitalWrite(LED, 1); //關閉LED
  Serial.begin()
}

void loop() {
  int pb=digitalRead(pbOFF);  //讀取pbOFF鈕
  if (!pb)  {         //若按下pbOFF鈕
    while(!pb)  pb=digitalRead(pbOFF);  //等待pbOFF鈕放開
    digitalWrite(LED,1);  //關閉LED
  }
  else {
    int pb=digitalRead(pbON); //讀取pbON鈕
    if (!pb) {        //若按下pbON鈕
      while(!pb)  pb=digitalRead(pbON);//等待pbON鈕放開
      digitalWrite(LED,0);  //點亮LED
    }
  }

  delay(100); //暫停0.1秒
}

