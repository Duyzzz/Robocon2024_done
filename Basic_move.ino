// ========================  Di chuyển cơ bản ========================  //
void soft_start(int ac_start, int speedv){ 
    if(v_bot < speedv){
      if( millis() - timea > ac_start){
        v_bot ++; 
        timea = millis(); 
      }
    }
}

void soft_end(int ac_end, int speedv){ 
  //if(!soft_state) speedv1 = 0; 
    if(v_bot > speedv && v_bot > 0){
      if( micros() - timea > ac_end){
        v_bot -- ; 
        timea = micros(); 
      }
    }
}

void rota_l_r(int set_speed_rota){
  if(millis() - timea > set_speed_rota && button_l2){
    angle_bot = angle_bot + 1; 
    timea = millis(); 
  }
  if(millis() - timeb > set_speed_rota && button_r2){
    angle_bot = angle_bot - 1;
    timeb = millis();  
  }
}

void up(int v){
  dc1.quaythuan(v); 
  dc3.quaynghich(v); 
  dc2.quaythuan(v); 
  dc4.quaynghich(v); 
}

void down(int v){
  dc2.quaynghich(v); 
  dc4.quaythuan(v); 
  dc1.quaynghich(v); 
  dc3.quaythuan(v); 
}

void right(int v){
  dc1.quaythuan(v); 
  dc4.quaythuan(v); 
  dc2.quaynghich(v); 
  dc3.quaynghich(v); 
}

void left(int v){
  dc2.quaythuan(v); 
  dc3.quaythuan(v); 
  dc1.quaynghich(v); 
  dc4.quaynghich(v); 
}

void rota_l(int v){
  dc1.quaynghich(v); 
  dc3.quaynghich(v); 
  dc2.quaynghich(v); 
  dc4.quaynghich(v); 
}

void rota_r(int v){
  dc1.quaythuan(v); 
  dc3.quaythuan(v); 
  dc2.quaythuan(v); 
  dc4.quaythuan(v); 
}

void stop(){
  dc1.phanh();
  dc2.phanh();
  dc3.phanh();
  dc4.phanh();
}
