
// ========================  Quay góc ========================  //
void right_rotate( int v) {
  dc1.quaynghich(v); 
  dc2.quaynghich(v); 
  dc3.quaynghich(v); 
  dc4.quaynghich(v);
}
void left_rotate( int v) {
  dc1.quaythuan(v); 
  dc2.quaythuan(v); 
  dc3.quaythuan(v); 
  dc4.quaythuan(v); 
}

void rotare( int set_angle){
  static int v_rota = 0;
  if (millis() - last_time > T) {
    angle = compass()/10; 
    error = set_angle - angle;
    if( -10 < error && error < 10){
      kp = 1.25 ; ki = 0.029; kd = 0.0075; 
      v_rota = 65; 
    }
    else {
      kp = 1.5; ki = 0.06; kd = 0.008;
      v_rota = 75;
    }
    output = (kp) * error + kd * (error - last_error) + ki * (error + last_error);
    last_error = error;
    output = constrain(output, -v_rota, v_rota);
    if (output > 0 && output < 8 ) output = 8;
    if (output < 0 && output > -8) output = -8;
    if ( output < 1) {
      right_rotate(abs(output));
    }
    else if ( output > 1) {
      left_rotate(output);
    }
    else {
      stop(); 
    }
    last_time = millis();
    last_error1 = 0;
  }
}

//============================================ Goc quay ================================================//
void quay(int goc){
  while(abs(compass() - goc*10) > 35){
    rotare(goc);
    if(button_select) break;
    ps3();
    left_grip(); 
    right_grip();
  }
  angle_bot = compass();
}

//============================================//
void rotare_for( int set_angle){
  while(abs(set_angle - compass()/10 ) > 5){
  if (millis() - last_time > T) {
    angle = compass()/10; 
    error = set_angle - angle;
    // if( -4 < error < 4){
    //   kp = 1.8 ; ki = 0.4; kd = 0.001; 
    // }
    // else {
      kp = 1.5; ki = 0.17; kd = 0.008;

    output = (kp) * error + kd * (error - last_error) + ki * (error + last_error);
    last_error = error;
    output = constrain(output, -65, 65);
    if (output > 0 && output < 6 ) output = 6;
    if (output < 0 && output > -6) output = -6;
    if ( output < 1) {
      left_rotate(abs(output));
    }
    else if ( output > 1) {
      right_rotate(output);
    }
    else {
      // right_rotate(0);
      stop(); 
    }
    last_time = millis();
    last_error1 = 0;
  }
  if(abs(set_angle - compass())< 8){
    stop() ; 
    v_bot = 0;
    break; 
  }
}
}