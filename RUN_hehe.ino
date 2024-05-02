double PI_const = 3.141592654; 
void move(int angle_rotare, int v_rotare, int angle_tt, int v_tt , int soft_start , int soft_stopp  ){   // angle tt là góc * 10
  int angle_compass = compass(); 
  int real_v_rotare = pid_cal(angle_rotare,angle_compass/10, v_rotare, 0.325, 0.14, 0.08); 
  int pwm1, pwm2, pwm3, pwm4;
  int vec1, vec2, vec3, vec4; 
  pwm1 = real_v_rotare + v_tt*cos((angle_tt - angle_compass + 450)*(PI_const/1800)); 
  pwm2 = real_v_rotare + v_tt*cos((angle_tt - angle_compass + 3150)*(PI_const/1800)); 
  pwm3 = real_v_rotare + v_tt*cos((angle_tt - angle_compass + 2250)*(PI_const/1800)); 
  pwm4 = real_v_rotare + v_tt*cos((angle_tt - angle_compass + 1350)*(PI_const/1800));

  if(pwm1 >  0 ){ vec1 = 1; }else { vec1 = 0 ; }
  if(pwm2 >  0 ){ vec2 = 1; }else { vec2 = 0 ; }
  if(pwm3 >  0 ){ vec3 = 1; }else { vec3 = 0 ; }
  if(pwm4 >  0 ){ vec4 = 1; }else { vec4 = 0 ; }

  rundc1(pwm1, vec1); 
  rundc2(pwm2, vec2); 
  rundc3(pwm3, vec3); 
  rundc4(pwm4, vec4); 
  //Serial.println(pwm4); 
}
/*

4        1        


3        2

*/ 

int pid_cal(int set_point, int input,int constrain_p,  double pP, double pI, double pD){   // goc quay, dau vao, toc do quay , 3 he so 
  int output = 0; 
  static long error_p, last_error_p; 
  error_p = set_point - input;
  if(error_p >  500){
    pP = 0.485,pI = 0.19,pD =  0.08;
  }else{
    pP = 0.585, pI = 0.17,pD = 0.09;
  }
    output = pP*error_p + pI*(error_p +  last_error_p) + pD*(error_p - last_error_p); 
  last_error_p = error_p; 
  output = -constrain(output, - constrain_p, constrain_p); 
  return output; 
}

void rundc1(int v, int vec){ v = abs(v);   if(vec == 1 ){  dc1.quaythuan(v);  }else if(vec == 0){  dc1.quaynghich(v);}}
void rundc2(int v, int vec){ v = abs(v);   if(vec == 1 ){  dc2.quaythuan(v);  }else if(vec == 0){  dc2.quaynghich(v);}}
void rundc3(int v, int vec){ v = abs(v);   if(vec == 1 ){  dc3.quaythuan(v);  }else if(vec == 0){  dc3.quaynghich(v);}}
void rundc4(int v, int vec){ v = abs(v);   if(vec == 1 ){  dc4.quaythuan(v);  }else if(vec == 0){  dc4.quaynghich(v);}}

