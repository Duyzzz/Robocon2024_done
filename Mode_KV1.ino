// ============================== MOde chạy khu vực 1, dùng để lấy lúa các kiểu dung cho tay trai =============================//
// ở trạng thái không kích k, tay kẹp mở và nâng lên. 
bool L1_1 = true; 
bool L1_2 = true; 
bool L1_3 = false; 
bool L1_4 = false; 

uint32_t bt_l = 0 ; 
bool btq = true; 
bool btq1 = true; 

bool stt_arml= 0;
bool stt_handl = 0;

uint32_t t_delay_arml1= 0;
uint32_t t_delay_handl1 = 0;

uint32_t  t_delay_grip = 1; 
uint32_t  t_delay_arm = 1; 

uint32_t t_run_right = 0; 
bool er_ll = true; 



void left_grip(){

  if(!stt_arml && ss_ld + ss_lt && !L1_3  ){   // them dieu kien cuoi 
    stt_handl = true; 
  }
//============================== arm
  if(button_square){
    if(btq){
      if(stt_arml){
        stt_arml = false; 
      }else{
        stt_arml = true; 
      }
      btq = false; 
    }
  }else{
    btq = true; 
  }

  if(stt_arml){
    arm_l.action(); 
  }else{
    arm_l.stop(); 
  }
//=============================== hand 
  if(rl ){
    if(btq1){
      if(stt_handl){
        stt_handl = false; 
      }else{
        stt_handl = true; 
      }
      btq1 = false; 
    }
  }else{
    btq1 = true; 
  }

  if(stt_handl){
    hand_l.action(); 
  }else{
    hand_l.stop(); 
  }

//===============================
  if(ss_arm_l && L1_1 && ss_ld && ss_lt){
    if(millis() - t_delay_grip >= 200){
      stt_handl = true; 
    }
  }else{
    t_delay_grip = millis();
  }

  if(stt_handl && L1_2 ){
    if(millis() - t_delay_arm >= 200){
      stt_arml = false;   //  Nang len  
      L1_2 = false; 
    }
  }else{
    t_delay_arm = millis(); 
  }

//===============================
  if(!L1_2 && button_r3 && rl && ss_arm_l || L1_3){
      L1_3 = true; 
      L1_1 = false;   
    if(millis() - t_delay_arml1 >= 200 ){
      stt_handl = false;
      stt_arml = false;
      soft_start(2, 40); 
      right_pid(angle_bot, v_bot, 80, 80); 
    }
    if(!stt_handl && millis() - t_delay_handl1 >= 800){
      L1_2 = true; 
      L1_3 = false;
      L1_4 = false;    
      int last_angle = angle_bot; 
      // while((abs(angle_bot - last_angle) < 1850)  && (abs(angle_bot - last_angle) >  1750)){
      //   angle_bot = compass(); 
      //   rotare(last_angle/10 + 180); 
      // }
      up(0);
    }
  }else{
    er_ll = true; 
    L1_1 = true; 
    t_delay_handl1 = millis(); 
    t_delay_arml1 = millis(); 
  }
}

// ============================== MOde chạy khu vực 1, dùng để lấy lúa các kiểu  Dùng cho tay  phair=============================//
bool R1_1 = true; 
bool R1_2 = true; 
bool R1_3 = false; 

uint32_t bt_r = 0 ; 
bool btc = true; 
bool btc1 = true; 

bool stt_armr= 0;
bool stt_handr = 0;

uint32_t t_delay_armr1= 0;
uint32_t t_delay_handr1 = 0;

uint32_t  t_delay_grip_r = 1; 
uint32_t  t_delay_arm_r = 1; 

void right_grip(){

  if(!stt_armr && ss_rd + ss_rt && !R1_3){
    stt_handr = true; 
  }
  //==============================
  if(button_circle){
    if(btc){
      if(stt_armr){
        stt_armr = false; 
      }else{
        stt_armr = true; 
      }
      btc = false; 
    }
  }else{
    btc = true; 
  }

  if(stt_armr){
    arm_r.action(); 
  }else{
    arm_r.stop(); 
  }

//===============================
  if(rr){
    if(btc1){
      if(stt_handr){
        stt_handr = false; 
      }else{
        stt_handr = true; 
      }
      btc1 = false; 
    }
  }else{
    btc1 = true; 
  }

  if(stt_handr){
    hand_r.action(); 
  }else{
    hand_r.stop(); 
  }

//===============================
  if(ss_arm_r && R1_1 && ss_rd && ss_rt){
    if(millis() - t_delay_grip_r >= 200){
      stt_handr = true; 
    }
  }else{
    t_delay_grip_r = millis();
  }

  if(stt_handr && R1_2 ){
    if(millis() - t_delay_arm_r >= 200){
      stt_armr = false;   //  Nang len  
      R1_2 = false; 
    }
  }else{
    t_delay_arm_r = millis(); 
  }

//==========================
  if(!R1_2 && button_r3 && rr && ss_arm_r || R1_3){
      R1_3 = true; 
      R1_1 = false;   
    if(millis() - t_delay_armr1 >= 200 ){
      stt_handr = false;
      stt_armr = false;
      soft_start(2, 40); 
      left_pid(angle_bot, v_bot, 80, 80);
    }

    if(!stt_handr && millis() - t_delay_handr1 >= 800){
      R1_2 = true; 
      R1_3 = false;    
      up(0);
    }
  }else{
    R1_1 = true; 
    t_delay_handr1 = millis(); 
    t_delay_armr1 = millis(); 
  }
}

//============================================= Set goc 0 ================================================//
void goto_0_angle(){
  int set_0 = compass() % 3600  ; 
  if(abs(set_0) <= 1800){
    angle_0 = compass() -set_0; 
  }else if(set_0 > 1800){
    angle_0 = compass() + (3600 - set_0); 
  }else if(set_0 < -1800){
    angle_0 = compass() - set_0 - 3600; 
  }
}

//============================================= Di chuyen ================================================//
int a_bt_up = 0; 
bool bt0 = false; 
bool stt_0 = true; 

void move_kv1(){

//================ Xac dinh goc quay ==================//
  if(lu){
    if(bt0){
      if(stt_0){
        stt_0 = false; 
      }else{
        stt_0 = true; 
      }
      bt0 = false; 
    }
  }else{
    bt0 = true; 
  }

  if(stt_0){
    a_bt_up = 180;
  }else{
    a_bt_up = 0;
  }
  

//================== Thuc thi =========================//
  if(lu){
    quay(0);
    v_bot = 0;
    angle_bot = compass();
  }else if(lr){
    if(lu){} else {quay(-90);}
    v_bot = 0;
    angle_bot = compass(); 
  }else if(ll){
    if(lu){} else {quay(90);}
    v_bot = 0;
    angle_bot = compass(); 
  // }
  // else if(ld){  
  //   angle_bot = compass(); 
  //   if(compass() < 0){
  //     rotare( - 180);
  //   }else if( compass() >0){
  //     rotare( + 180);
  // }
  }else if(button_up){ 
    soft_start(12,V1); 
    up_pid(angle_bot,v_bot, 100,100);
  }else if(button_down){
    soft_start(12,V1); 
    down_pid(angle_bot,v_bot, 100,100);
  }else if(button_left){
    soft_start(12,V1); 
    left_pid(angle_bot,v_bot, 100,100);
  }else if(button_right){
    soft_start(12,V1); 
    right_pid(angle_bot,v_bot, 100,100);
  } else if(button_l1){
    soft_start(12,V1);
    rota_l(v_bot);
    angle_bot = compass();  
    stt_bot = 0;
  }else if(button_r1){
    soft_start(12    ,V1);
    rota_r(v_bot); 
    angle_bot = compass(); 
    stt_bot = 0; 
  }else if(button_r3){
    // khong lam gi 
  }else {   
    if(v_bot != 0){  
      soft_end(1200, 0); 
      switch(stt_bot){
      case 1: up_pid(angle_bot, v_bot, 100, 100);
              break; 
      case 2: left_pid(angle_bot, v_bot, 100, 100);
              break; 
      case 3: right_pid(angle_bot, v_bot, 100, 100); 
              break; 
      case 4: down_pid(angle_bot, v_bot, 100, 100); 
              break; 
      case 0: v_bot = 0; 
              up(0);
              break;  
      }
    }else{
      angle_bot = compass();
      one_1 = true; 
      stop(); 
    }   
  }

  if(button_select){
    Serial1.println("a");\
  }else{
    
  }
//=============== Chinh toc do =============//
  if(button_r2){
    V1= 150; 
  }else{      
    V1= 55;
  }
}

