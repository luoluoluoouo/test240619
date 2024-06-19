const int PB[4]={A0,A1,A2,A3};    //宣告A0腳~A3腳為PB[0]~PB[3]

int sw=0,pp=0;     

void shutdown(){
  for(int i=0;i<8;i++) {
    digitalWrite(LED[i], Off);    //關閉LED[0]~LED[7]
  }
}

void setup() {

}

void loop() {
  readPb(); //讀取按鈕

  while(pp==1) {

  }
  shutdown ();
  while(pp==2) {

  }

  while(pp==3) {
    
  }

  while(pp==4) {
    
  }
  //關閉所有LED
  

}
//=================================================
//讀取按鍵
void readPb(void){
  if(!digitalRead(PB[0]))  pp=1;       //若按下，則執行指標pp=1
  else if(!digitalRead(PB[1])) pp=2;       //若按下，則執行指標pp=2
  else if(!digitalRead(PB[2])) pp=3;       //若按下，則執行指標pp=3 
  else if(!digitalRead(PB[3])) pp=4;     //若按下，則執行指標pp=0 
  return;           //返回
}

