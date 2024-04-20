
// ========================  Hien thi  ========================  //
void display(){
  if( millis() % 300 == 0){
    char txt_gyro[14]="""";
    sprintf(txt_gyro,"Angle:%d     ",compass());
     char txt_[20]="""";
    sprintf(txt_,"%d   , %d       " );
    // char txt_ps3[5]="""";
    // sprintf(txt_ps3,"|PS3:%d ",buttonIndex);
    //char txt_line[20]="""";
    //sprintf(txt_line,"%d:%d:%d:%d:%d:%d",analogRead(A11)/10,analogRead(A10)/10,analogRead(A9)/10,analogRead(A8)/10,analogRead(A7)/10,analogRead(A6)/10);

    // lcd.setCursor(0,0);   lcd.print();
    lcd.setCursor(0,0);   lcd.print("ag_bo : ");
    //lcd.setCursor(8,0);   lcd.print(angle_bot);
    lcd.setCursor(0,1);   lcd.print("V_bot :");
    lcd.setCursor(8,1);   lcd.print(v_bot);
    // lcd.setCursor(8,0);   lcd.print(ss_ld);
    // lcd.setCursor(12,0);   lcd.print(ss_rt);
    // lcd.setCursor(16,0);   lcd.print(ss_rd);
     //lcd.setCursor(0,1);   lcd.print(sick2());
    
    lcd.setCursor(0,3);   lcd.print(angle_bot);
    //lcd.setCursor(13,3);   lcd.print(txt_ps3);
    // Serial.println(analogRead(A6));
    // Serial.print("V11:   "); Serial.println(v11); 

  }
}

