void takeBall(){
  digitalWrite(mt, 0);
  digitalWrite(mn, 1);
}
void stopTakeBall(){
  digitalWrite(mt, 1);
  digitalWrite(mn, 1);
}
void returnBall(){
  digitalWrite(mt, 1);
  digitalWrite(mn, 0);
}
void ballFiringConfig(){
  pinMode(mn, OUTPUT);
  pinMode(mt, OUTPUT);
  pinMode(ruloTren, OUTPUT);
}
void ruloTrenQuay(){
  digitalWrite(ruloTren, 1);
}
void dungRuloTren(){
  digitalWrite(ruloTren, 0);
}

void modeBanBong(){
  if(button_r2){
    dcbTren.quaythuan(123);
  }else {
    dcbTren.quaythuan(0);
  }
}