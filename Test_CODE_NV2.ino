#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SimpleKalmanFilter.h>
#include <stdint.h>

#include"Robot.h" 
#include"PS3_Index.h"   
#include "Arm_and_Hand.h"
LiquidCrystal_I2C lcd(0x27,20,4); 
SimpleKalmanFilter sick1_kal(2, 2, 0.01);
SimpleKalmanFilter sick2_kal(2, 2, 0.01);
SimpleKalmanFilter simpleKalmanFilter(2, 2, 0.01);

class motor{
  protected: 
    int m; 
    int d; 
  public: 
    motor(int ma, int da):m(ma),d(da){}

    void quaynghich(int speedd){
      int speed = 255 - speedd;
      if(speed == 2){
        speed = 3; 
      }
      analogWrite(m,speed); 
      digitalWrite(d,1); 
          
    }
    void quaythuan(int speedd){
      int speed = 255 - speedd;
      if(speed == 2){
        speed = 3; 
      }
      analogWrite(m,speed); 
      digitalWrite(d,0); 
      
    }
    void phanh(){
      analogWrite(m, 253); 
      digitalWrite(d, 0); 
    }
};

class basic_motor{
  protected: 
    int mc; 
    int md; 
    int dm; 
  public:     
    basic_motor(int mcc, int mdd, int dmm):mc(mcc),md(mdd),dm(dmm){}

    void quaynghich(int speed){
      analogWrite(dm, speed); 
      digitalWrite(mc,1); 
      digitalWrite(md,0);
    }
    void quaythuan(int speed){
      analogWrite(dm,speed); 
      digitalWrite(mc,0); 
      digitalWrite(md,1);
    }
};




arm_hand arm_l (arm_left,0); 
arm_hand arm_r (arm_right,0); 
arm_hand hand_l (hand_left,1); 
arm_hand hand_r (hand_right,1); 




motor dc1(m1, d1); 
motor dc2(m2, d2);    
motor dc3(m3, d3); 
motor dc4(m4, d4);

motor dcb1(8, d6); 
motor dcb2(9, d7); 

basic_motor dc11( m11, m12, pwm_m1);
basic_motor dc22( m21, m22, pwm_m2);

void setup(){
  // set 
  pinMode(47, INPUT); 
  // Set basic motor 
  pinMode(8, OUTPUT); 
  pinMode(9, OUTPUT); 
  pinMode(27, OUTPUT); 
  pinMode(29, OUTPUT); 
  //Set controller pin for PID driver 
  pinMode(m1, OUTPUT);
  pinMode(d1, OUTPUT);

  pinMode(m2, OUTPUT);
  pinMode(d2, OUTPUT);

  pinMode(m3, OUTPUT);
  pinMode(d3, OUTPUT);

  pinMode(m4, OUTPUT);
  pinMode(d4, OUTPUT);
  //Basic motor setup 
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(pwm_m1, OUTPUT);

  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  pinMode(pwm_m2, OUTPUT);
  // Air_press setup
  pinMode(k1, OUTPUT); 
  pinMode(k2, OUTPUT); 
  pinMode(k3, OUTPUT); 
  pinMode(k4, OUTPUT); 
  pinMode(k5, OUTPUT); 
  pinMode(k6, OUTPUT); 
  // Encoder setup
  pinMode(enb, INPUT); 
  pinMode(ena, INPUT); 
  // Open connector setup
  pinMode(cb13, INPUT); 
  pinMode(cb14, INPUT); 
  pinMode(cb15, INPUT); 
  pinMode(cb16, INPUT); 
  // SW NC setup 
  pinMode(ct3, INPUT); 
  pinMode(ct4, INPUT); 
 
  // lAZER 
  pinMode(lazer, OUTPUT); 


  Serial3.begin(115200);   // For EPS 32
  Serial2.begin(115200);   // Compass
  Serial1.begin(115200);   // 
  Serial.begin(115200);    // for debug 

  dc1.quaythuan(0);
  dc2.quaythuan(0);
  dc3.quaythuan(0);
  dc4.quaythuan(0);

  dcb1.quaythuan(0);
  dcb2.quaythuan(0);

  arm_l.stop(); 
  arm_r.stop(); 
  

  Serial3.println('a');
  lcd.init();                     
  lcd.backlight();
}
int angle_0 = 0; 

void loop(){
  ps3(); 
  // //display(); 
  // left_grip(); 
  // right_grip(); 
  if(button_select){
     Serial3.println('a');
  }

  // // dc22.quaythuan(255);  // sau 
  // // dc11.quaynghich(255);  // truoc 
  //  move_kv1(); 
  // kv2(); 
  //dc2.quaythuan(8);

 // dcb1.quaynghich(100); // tren
 // dcb2.quaythuan(100); // duoi
if(button_up){
  run_xy(0,1000, 1000);
   //move(0, 40, 3150, 40 , 10,10 ); // angle tt là góc * 10
 }else if(button_right){
  move(180, 60, 0, 40 , 10,10 );
 }else if(button_left){
  move(-90, 40, 1800, 60 , 10,10 );
 }else{
  up(0);
 }

  Serial.println(compass());
  //rundc1( 30, 1); 
}