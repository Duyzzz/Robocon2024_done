#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SimpleKalmanFilter.h>
#include <stdint.h>
#include <PID_DCRv2.h>
#include"Robot.h" 
#include"PS3_Index.h"   
#include "Arm_and_Hand.h"
LiquidCrystal_I2C lcd(0x27,20,4); 
SimpleKalmanFilter headSickKal(2, 2, 0.01);
SimpleKalmanFilter rightSickKal(2, 2, 0.01);
SimpleKalmanFilter leftSickKal(2, 2, 0.01);
SimpleKalmanFilter simpleKalmanFilter(2, 2, 0.01);
PID encoderPID(0.1, 0.01, 0.07);

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

motor dcb1(m5, d5); 
motor dcb2(m6, d6); 

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

  pinMode(m5, OUTPUT);
  pinMode(d5, OUTPUT);
  pinMode(m6, OUTPUT);
  pinMode(d6, OUTPUT);
  //Basic motor setup 
  // pinMode(m11, OUTPUT);
  // pinMode(m12, OUTPUT);
  // pinMode(pwm_m1, OUTPUT);

  // pinMode(m21, OUTPUT);
  // pinMode(m22, OUTPUT);
  // pinMode(pwm_m2, OUTPUT);
  // Air_press setup
  // pinMode(k1, OUTPUT); 
  // pinMode(k2, OUTPUT); 
  // pinMode(k3, OUTPUT); 
  // pinMode(k4, OUTPUT); 
  // pinMode(k5, OUTPUT); 
  // pinMode(k6, OUTPUT); 
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
 

  Serial3.begin(115200);   // For EPS 32
  Serial2.begin(115200);   // Compass
  Serial1.begin(115200);   // 
  Serial.begin(115200);    // for debug 

  dc1.quaythuan(0);
  dc2.quaythuan(0);
  dc3.quaythuan(0);
  dc4.quaythuan(0);


  

  Serial3.println('a');
  lcd.init();                     
  lcd.backlight();
  resetEncoder(true, true);
  encoderPID.SetOutputLimits(-100, 100);
  encoderPID.setSampleTime(1);
  encoderPID.setStart();
  headSickKal.updateEstimate(analogRead(A7));
  rightSickKal.updateEstimate(analogRead(A6));
  pinMode(m51, OUTPUT);
  pinMode(m52, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  pinMode(pwm10, OUTPUT);
  pinMode(pwm13, OUTPUT);
  digitalWrite(m52, 0); // 13 trai
  digitalWrite(m51, 0);  // nang ha trai
  digitalWrite(m22, 0); // 24 trai

  digitalWrite(pwm10, 0); // 24 phai
  digitalWrite(pwm13, 0); // 13 phai
  digitalWrite(m21, 0); // nang ha phai
  dcb1.quaythuan(0); // dc duoi

  dcb2.quaynghich(0); // dc tren
}
int angle_0 = 0; 

void loop(){
  // readEncoder();
  // Serial.println(encoder2);
  ps3(); 
  if(button_square){
    if(toggle){
      toggle = false;
      cangTrai = !cangTrai;
      digitalWrite(m51, cangTrai);
    }
  }else if(button_circle){
    if(toggle){
      toggle = false;
      cangPhai = !cangPhai;
      digitalWrite(m21, cangPhai);
    }
  }else if(lu){
    if(toggle){
      toggle = false;
      _13Trai = !_13Trai;
      digitalWrite(m52, _13Trai);
    }
  }else if(ld){
    if(toggle){
      toggle = false;
      _24Trai = !_24Trai;
      digitalWrite(pwm10, _24Trai);
    }
  }else if(ll){
    if(toggle){
      toggle = false;
      _13Phai = !_13Phai;
      digitalWrite(pwm13, _13Phai);
    }
  }else if(lr){
    if(toggle){
      toggle = false;
      _24Phai = !_24Phai;
      digitalWrite(m22, _24Phai);
    }
  }else {
    toggle = true;
  }
  headSickKal.updateEstimate(analogRead(A7));
  rightSickKal.updateEstimate(analogRead(A6));
  // //display(); 
  // left_grip(); 
  // right_grip(); 
  if(button_select){
     Serial3.println('a');
  }
  if(button_triangle){
    testVar = false;
    enableGoFarm = true;
    up(0);
  }
  if(testVar){
    //run(500, 500, 0, "right");
    //move(0, 40, 450, 50, 10, 10);
    //secondRiceOne();
    // xoay 180:  move(-180, 50, 0, 40, 10, 10);
    //Serial.println(encoder2);
    // chay ra dat lua 1:   move(-270, 20, 1200, 70, 10, 10); // 6140 xung thi dung
    // if(micros() - testTestTest > 2500000){
    //   stop();
    //   testVar = false;
    //   readEncoder();
    //   Serial.println(encoder2);
    // }else {
    //   move(-260, 20, 1200, 70, 10, 10);
    // }
    runTasks();
    //Serial.print("tasking: ");
    //run(1000, 1000, 0, "right");
    
    /*if(ricePosition == 1){
      run(2630, 1502, 0, "right"); // lua 1
    }else if(ricePosition == 2){
      run(2178, 1296, 0, "right"); // lua 1
    }else if(ricePosition == 3){
      run(1085, 1293, 0, "right");
       // lua 1
    }else if(ricePosition == 4){
      run(1549, 1836, 0, "right"); // lua 1
    }else if(ricePosition == 5){
      // go get rice
      //run(2459, 593);
      ricePosition = 1;
    }*/
    //move(-270, 40, 0, 50, 0, 0);
  }
    // testToGetX = readRightSick();
    // testToGetY = readHeadSick();
    // Serial.print(testToGetX);
    // Serial.print(" ");
    // Serial.println(testToGetY);
  // float testDistance = sqrt(abs(testToGetX*testToGetX) + abs(testToGetY*testToGetY));
  // Serial.println(testDistance);
  //Serial.println(readHeadSick());
  /*if(button_x && enableGoFarm){
    testVar = true;
    isAuto = true;
    enableConfigPosition = true;
    ricePosition++;
    enableGoFarm = false;
  }*/
  if(button_start && !isAuto){
    Serial3.println('a');
    testVar = true;
    v_bot = 0;
    encoderPID.setStart();
    resetEncoder(true, true);
    //testTestTest = micros();
    stt_bot = 8;
    isAuto = true;
    start();
  }else if(button_triangle){
    testVar = false;
    up(0);
    readEncoder();
    Serial.println(encoder2);
    resetEncoder(true, true);
    retry();
  }else if(button_up){ 
    isAuto = false;
    soft_start(12,V1); 
    up_pid(angle_bot,v_bot, 100,100);
  }else if(button_down){
    isAuto = false;
    soft_start(12,V1); 
    down_pid(angle_bot,v_bot, 100,100);
  }else if(button_left){
    isAuto = false;
    soft_start(12,V1); 
    left_pid(angle_bot,v_bot, 100,100);
  }else if(button_right){
    isAuto = false;
    soft_start(12,V1); 
    right_pid(angle_bot,v_bot, 100,100);
  } else if(button_l1){
    isAuto = false;
    soft_start(12,V1);
    rota_l(v_bot);
    angle_bot = compass();  
    stt_bot = 0;
  }else if(button_r1){
    isAuto = false;
    soft_start(12    ,V1);
    rota_r(v_bot); 
    angle_bot = compass(); 
    stt_bot = 0; 
  }else if(button_r3){
    // khong lam gi 
  }else if(!isAuto ){   
    if(v_bot != 0){  
      soft_end(900, 0); 
      if(stt_bot == 1){
        up_pid(angle_bot, v_bot, 100, 100);
        Serial.println("up");
      }else if(stt_bot == 2){
        Serial.println("left");
        left_pid(angle_bot, v_bot, 100, 100);
      }else if(stt_bot == 3){
        Serial.println("right");
        right_pid(angle_bot, v_bot, 100, 100); 
      }else if(stt_bot == 4){
        Serial.println("down");
        down_pid(angle_bot, v_bot, 100, 100); 
      }else if(stt_bot == 0){
        Serial.println("stop");
        v_bot = 0; 
        up(0);
      }
    }else if(stt_bot != 8){
      angle_bot = compass();
      one_1 = true; 
      stop(); 
    }   
  }
  //readEncoder();
  //Serial.println(encoder2);
  // // dc22.quaythuan(255);  // sau 
  // // dc11.quaynghich(255);  // truoc 
  //  move_kv1(); 
  // kv2(); 
  //dc2.quaythuan(8);

/*if(button_up){
  run_xy(0,1000, 1000);
   //move(0, 40, 3150, 40 , 10,10 ); // angle tt là góc * 10
 }else if(button_right){
  move(180, 60, 0, 40 , 10,10 );
 }else if(button_left){
  move(-90, 40, 1800, 60 , 10,10 );
 }else{
  up(0);
 }*/

  //Serial.println(compass());
  //rundc1( 30, 1); 
  
}