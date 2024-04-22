
double kp1 = 0.05, kd1 = 0.01, ki1 = 0.02;    // thoong so mac dinh

// ========================  PID chạy thẳng ========================  //
void balance(int set_angle, int v, int ac, int out){
  if (micros() - last_time > T1){
    angle = compass() ;
    error = set_angle - angle;
    if(stt_bot == 1){
      if(error > -80 && error < 80){
        kp1 = 0.0006, kd1 = 0.005, ki1 = 0.086; 
      }else{
        kp1 = 0.001, kd1 = 0.005, ki1 = 0.08; 
      }
    }else if(stt_bot == 2 || stt_bot == 3){
      if(error > -40 && error < 40){
        kp1 = 0.08, kd1 = 0.008, ki1 = 0.012; 
      }else{
        kp1 = 0.05, kd1 = 0.005, ki1 = 0.008; 
      }
    }else if(stt_bot == 4){
      if(error > -40 && error < 40){
        kp1 = 0.08, kd1 = 0.008, ki1 = 0.012; 
      }else{
        kp1 = 0.05, kd1 = 0.005, ki1 = 0.008; 
      }
    }
    
    output = kp1 * error + kd1 * (error - last_error) + ki1 * (error + last_error1);
    last_error = error;
    output = constrain(output, -out, out);
    if (output != 0)
    {
      v11 = v + output;
      v22 = v - output;
    }
    else
    {
      v11 = v22 = v;
    }
    last_time = micros(); 
    v11 = constrain(v11, 0, v+ac);
    v22 = constrain(v22, 0, v+ac);
    if(v11 == 2) v11 = 3;
    if(v22 == 2) v22 = 3;    Serial.println(output);
  }
}

// mình sẽ tạo một biến toàn cục điều khiển tốc độ của robot, biến này tên là v_bot 
// sau đó, mình sẽ gọi các hàm làm thay đổi giá trị của biến toàn cụ này, đầu tiên mình cần làm là v_bot cần phải được reset về 0  sau mỗi lần nhả nút hoặc bị gặp phải điều kiện nào đó, có thể là kết thúc quá trình 
// bÙ TRÁI theo hướng chuyển động là V22
// Chiều thuận động cơ là robot quay theo hướng kim đh

void down_pid(int set_angle, int v_bott, int ac_balance, int out_set){
  stt_bot = 4; 
  balance(set_angle, v_bott, ac_balance, out_set);
  dc4.quaynghich(v22); 
  dc2.quaythuan(v11); 
  dc1.quaynghich(v22); 
  dc3.quaythuan(v11);
}

void up_pid(int set_angle, int v_bott, int ac_balance , int out_set){
  stt_bot = 1; 
  balance(set_angle, v_bott, ac_balance, out_set);
  dc4.quaythuan(v11); 
  dc2.quaynghich(v22); 
  dc1.quaythuan(v11); 
  dc3.quaynghich(v22);
}

void left_pid(int set_angle, int v_bott, int ac_balance, int out_set){
  stt_bot = 2; 
  balance(set_angle, v_bott, ac_balance, out_set);
  dc4.quaynghich(v22); 
  dc2.quaythuan(v11); 
  dc1.quaythuan(v11); 
  dc3.quaynghich(v22);
}


void right_pid(int set_angle, int v_bott, int ac_balance, int out_set){
  stt_bot = 3; 
  balance(set_angle, v_bott, ac_balance, out_set);
  dc4.quaythuan(v11); 
  dc2.quaynghich(v22); 
  dc1.quaynghich(v22); 
  dc3.quaythuan(v11);
}




