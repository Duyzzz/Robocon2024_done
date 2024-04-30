#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SimpleKalmanFilter.h>
#include <stdint.h>
#include <PID_DCRv2.h>
#include "Robot.h" 
#include "PS3_Index.h"   
#include "Arm_and_Hand.h"
LiquidCrystal_I2C lcd(0x27,20,4); 
SimpleKalmanFilter headSickKal(2, 2, 0.01);
SimpleKalmanFilter rightSickKal(2, 2, 0.01);
SimpleKalmanFilter leftSickKal(2, 2, 0.01);
SimpleKalmanFilter simpleKalmanFilter(2, 2, 0.01);
class OutputControl{
  protected:
    unsigned char Pin;
    bool Act;
  public:
    OutputControl (unsigned char pin, bool act){
      Pin = pin;
      Act = act;
    }
    void active(){
      digitalWrite(Pin, Act);
    }
    void stop(){
      digitalWrite(Pin, !Act);
    }
    void config(int initialState){
      pinMode(Pin, initialState);
    }
};
class motor{
  protected: 
    int m; 
    int d; 
  public: 
    motor(int ma, int da):m(ma),d(da){}
    void config(){
      pinMode(m, OUTPUT);
      pinMode(d, OUTPUT);
    }
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


OutputControl dcHutTren(11, 1);
OutputControl dcHutDuoi(24, 1);

arm_hand arm_l (32,0); 
arm_hand arm_r (26,0); 
arm_hand hand_l_13 (13,1); 
arm_hand hand_l_24 (12,1); 
arm_hand hand_r_13 (28,1); 
arm_hand hand_r_24 (34,1); 




motor dc1(m1, d1); 
motor dc2(m2, d2);    
motor dc3(m3, d3); 
motor dc4(m4, d4);
motor dcbTren(m5, d5);
motor dcbDuoi(m6, d6);

void countEncoder(){
  encoder2++;
}
void setup(){
  // set 
  arm_l.config(OUTPUT);
  arm_r.config(OUTPUT);
  hand_l_13.config(OUTPUT);
  hand_l_24.config(OUTPUT);
  hand_r_13.config(OUTPUT);
  hand_r_24.config(OUTPUT);
  dcHutTren.config(OUTPUT);
  dcHutDuoi.config(OUTPUT);
  pinMode(47, INPUT); 
  // Set basic motor 
  //Set controller pin for PID driver 

  dc1.config();
  dc2.config();
  dc3.config();
  dc4.config();
  dcbTren.config();
  dcbDuoi.config();
  

  // Encoder setup
  //pinMode(enb, INPUT); 
  //pinMode(ena, INPUT); 
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
  headSickKal.updateEstimate(analogRead(A7));
  rightSickKal.updateEstimate(analogRead(A6));
 
  // dcb1.quaythuan(0); // dc duoi

  // dcb2.quaynghich(0); // dc tren
  encoder2 = 0;
  if(true){
    land = RED;
  }else {
    land = BLUE;
  }
  Serial.println("hello");
  // arm_l.action();
  // arm_r.action();
  // hand_l_13.action();
  // hand_l_24.action();
  // hand_r_13.action();
  // hand_r_24.action();
  dcHutTren.stop();
  dcHutDuoi.stop();
  dcbTren.quaynghich(0);
  dcbDuoi.quaythuan(0);
  pinMode(21, INPUT_PULLUP);
  arm_l.action();
  arm_r.action();
  hand_l_13.stop();
  hand_r_13.stop();
  hand_l_24.stop();
  hand_r_24.stop();
  attachInterrupt(digitalPinToInterrupt(21), countEncoder, FALLING);
}
int angle_0 = 0; 

void loop(){
  ps3(); 
  
  if(true){
    if(button_circle){
      if(toggle){
        toggle = false;
        cangPhai = !cangPhai;
        if(cangPhai){
          arm_r.action();
        }else {
          arm_r.stop();
        }
      }
    }else if(button_square){
      if(toggle){
        toggle = false;
        cangTrai = !cangTrai;
        if(cangTrai){
          arm_l.action();
        }else {
          arm_l.stop();
        }
      }
    }else if(ru){
      if(toggle){
        toggle = false;
        _13Phai = !_13Phai;
        if(_13Phai){
          hand_r_13.action();
        }else {
          hand_r_13.stop();
        }
      }
    }else if(rr){
      if(toggle){
        toggle = false;
        _24Phai = !_24Phai;
        if(_24Phai){
          hand_r_24.action();
        }else {
          hand_r_24.stop();
        }
      }
    }else if(rl){
      if(toggle){
        toggle = false;
        _13Trai = !_13Trai;
        if(_13Trai){
          hand_l_13.action();
        }else {
          hand_l_13.stop();
        }
      }
    }else if(rd){
      if(toggle){
        toggle = false;
        _24Trai = !_24Trai;
        if(_24Trai){
          hand_l_24.action();
        }else {
          hand_l_24.stop();
        }
      }
    }else {
      toggle = true;
    }
  }
  
  headSickKal.updateEstimate(analogRead(A11));
  rightSickKal.updateEstimate(analogRead(A9));
  // //display(); 
  // left_grip(); 
  // right_grip(); 
  if(button_select){
    Serial3.println('a');
    started = false;
    testVar = false;
    enableGoFarm = true;
    configuration = true;
    stopOnce = true;
    up(0);
  }


  if(testVar){
    Serial.println(encoder2);
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
    testToGetX = readRightSick();
    testToGetY = readHeadSick();
    Serial2.print(testToGetX);
    Serial2.print(" ");
    Serial2.println(testToGetY);
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
  if(button_start && !isAuto && !started){
    started = true;
    Serial3.println('a');
    testVar = true;
    v_bot = 0;
    //testTestTest = micros();
    stt_bot = 8;
    isAuto = true;
    start();
  }else if(button_triangle){
    testVar = false;
    up(0);
    Serial.println(encoder2);
    encoder2 = 0;
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
  }else {
    angle_bot = compass();
  }
  
}
