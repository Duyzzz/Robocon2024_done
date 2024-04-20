int sick1(){   //( truc y )
  return sick1_kal.updateEstimate(analogRead(A7))*one_dist + 200;
}
int sick2(){   // san phai gan den xa: 355 , 1150, 1910, 2670, 3410   ( truc x )
  return sick2_kal.updateEstimate(analogRead(A6))*one_dist + 200;
}



void run_xy(int angle_set, int x, int y){
  float er_x = abs(sick2() - x); 
  float er_y = abs(sick1() - y); 
  int angle_run = atan(er_x / er_y)*1800/PI_const ; 
  if(sick1() > y && sick2() > x){
    angle_run = angle_run + 1800;
  }else if(sick1() > y && sick2() < x){
    angle_run = angle_run  + 900; 
  }else if(sick1() < y && sick2() < x){
    angle_run = angle_run; 
  }else if(sick1() < y && sick2() > x){
    angle_run = angle_run + 2700; 
  }
  if(abs(sick1() - y) < 200 && abs(sick2() -x) < 200 ) {
    stop();
  }else{
    move(0, 40, angle_run , 50 , 10,10 );
  }
  Serial.println( angle_run);
  
}