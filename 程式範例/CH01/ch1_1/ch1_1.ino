// ===== ch1_1.ino =====
#define LED 3  //3腳連接LED

void setup() {
  pinMode(LED, OUTPUT);  //將LED腳規畫為輸出埠
  digitalWrite(LED, 1);  //關閉LED，電路裡LED採低態動作
}

void loop() {
  //慢慢變亮
  analogWrite(LED, 200);  //亮度約為20%
  delay(200);             //持續點亮0.2秒
  analogWrite(LED, 150);  //亮度約為40%
  delay(200);             //持續點亮0.2秒
  analogWrite(LED, 100);  //亮度約為60%
  delay(200);             //持續點亮0.2秒
  analogWrite(LED, 50);   //亮度約為80%
  delay(200);             //持續點亮0.2秒
  analogWrite(LED, 0);    //亮度約為100%
  delay(2000);            //持續點亮2秒
  //慢慢變暗
  analogWrite(LED, 50);   //亮度約為80%
  delay(200);             //持續點亮0.2秒
  analogWrite(LED, 100);  //亮度約為60%
  delay(200);             //持續點亮0.2秒
  analogWrite(LED, 150);  //亮度約為40%
  delay(200);             //持續點亮0.2秒
  analogWrite(LED, 200);  //亮度約為20%
  delay(200);             //持續點亮0.2秒
  analogWrite(LED, 255);  //關閉
  delay(1000);            //持續關閉1秒
}
