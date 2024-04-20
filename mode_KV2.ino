bool btbb = false; 
bool stt_bb; 
bool ttb = false; 
uint32_t delay_ban = 0; 
uint32_t delay_led1 = 0;
uint32_t delay_led2 = 0;  
bool state_lazer = 1;
bool last_lazer = 0; 
int aaaa = 1;  

void  bynk_lazer(){
  if(state_lazer ) {
    digitalWrite(lazer,1); 
    if(millis() - delay_led1 >= aaaa){
      delay_led2 = millis(); 
      last_lazer = 1;
      state_lazer = 0;  
    }
  }

  if(last_lazer){
    digitalWrite(lazer, 0); 
    if(millis() - delay_led2 >= aaaa){
      delay_led1 = millis(); 
      last_lazer = 0;
      state_lazer = 1;  
    }
  }

  digitalWrite(lazer, state_lazer); 

}
void kv2(){
// =================== Bắn , delay quay truoc hai con lo sau do moi ban2 
  if(button_triangle){
    
    if(millis() - delay_ban < 200){
      dcb1.quaythuan(50); // tren
      dcb2.quaythuan(210); // duoi
    }else{
      dc11.quaynghich(255);
      ttb = true; 
    }
  }else{
    ttb = false; 
    dc11.quaynghich(0); 
    dcb1.quaynghich(0); // tren
    dcb2.quaythuan(0); // duoi
    delay_ban = millis();
  }
// ================== Bat tat lay bong 
  if(button_x){
    if(btbb){
      if(stt_bb){
        stt_bb = false; 
      }else{
        stt_bb = true; 
      }
      btbb = false; 
    }
  }else{
    btbb = true; 
  }


// ================== Lấy bóng   
  if(stt_bb && !cbb || ttb){
    dc22.quaythuan(255);
     bynk_lazer(); 
  }else{
    dc22.quaythuan(0);
    digitalWrite(lazer, 0); 
  }

}