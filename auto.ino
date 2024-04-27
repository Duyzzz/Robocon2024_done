#include <Arduino.h>
class Task{
  protected:
    int Threading = -1;
    bool Configuration = true;
  public:
    Task();
    bool checkConfig(){
      return Configuration;
    }
    void disableConfig(){
      Configuration = false;
    }
    void jumpNextStep(){
      Configuration = true;
      Threading = Threading + 1;
    }
};



void thirdRiceTwo(){
  
}
//


//--------------------------------------------- end funcs --------------------------------------//

void run_distance(int dist, int angle, int speed, int end_speed,  int ac_run, int ac_stop, int ac_angle){
  static int last_dist = 0; 
  static uint8_t  speed_run = 0; 
  static uint8_t  speed_run_1 = 0; 
  static uint32_t time_seta = 0;
  if(dist_en < dist - ac_stop){
    if(speed_run < speed){
      if(millis() - time_seta >= ac_run){
        speed_run ++; 
        time_seta = millis();
        speed_run_1 = speed_run; 
      }
    }
  }else if(speed_run != 0 && dist_en >= dist - ac_stop){
    speed_run =  (dist - dist_en) * (speed_run_1 - end_speed)*1/ac_stop; 
  }else if(dist_en == dist){
    speed_run = 0; 
  }
  up_pid(0, speed_run, ac_angle, ac_angle + 20);
  Serial.println(speed_run);
}
// ------------------------------------------- end define ---------------------------------------//


void runTasks(){
  if(threading == 0){
    if(configuration){
      encoderPID.getSetPoint(1000);
      resetEncoder(true, true);
      triggerTime = micros();
      Serial.println("start");
      configuration = false;
      stopOnce = true;
      isAuto = true;
    }
    Serial.println("checking step 1");
    if(micros() - triggerTime > 5080000){
      // start step two here;
      resetEncoder(true, true);
      Serial.println("end 1");
      angle_bot = compass();
      configuration = true;
      if(stopOnce){
        stop();
        stopOnce = false;
        digitalWrite(m21, false);
      }
      threading = 1;
    }else {
      readEncoder();
      Serial.print("encoder2:  ");
      Serial.print(encoder2);
      Serial.print(" ");
      int speedJust = 0;
      int angleJust = 0;
      if(encoder2 < 0){
        encoder2 = 0;
      }else if(encoder2 >= 0 && encoder2 < 700){
        speedJust = map(encoder2, 0, 700, 30, 80);
      }else if(encoder2 >= 700 && encoder2 < 1550){
        speedJust = 80;
      }else if(encoder2 >= 1550 && encoder2 <= 3520){
        speedJust = 80 - map(encoder2, 1600, 4520, 0, 76);
      }else if(encoder2 > 3520){
        if(stopOnce){
          stop();
          threading = 1;
          configuration = true;
          stopOnce = false;
        }
      }
      angleJust = 1350 - map(encoder2, 0, 1820, 0, 450);
      Serial.print(angleJust);
      Serial.print(" ");
      Serial.println(speedJust);
      if(isAuto){
        move(0, 40, angleJust, speedJust, 0, 0);
      }
      
    }
  }
  if(threading == 1){
    if(configuration){
      digitalWrite(m21, true);
      stop();
      Serial.println("start get Rice");
      triggerTime = micros();
      enableConfigPosition = true;
      configuration = false;
      stopOnce = true;
    }
    if(micros() - triggerTime > 800000 && micros() - triggerTime < 1300000){
      Serial.println("check");
      digitalWrite(m21, false);
      digitalWrite(pwm13, 1);
      digitalWrite(m22, 1);
    }else if(micros() - triggerTime > 1300000 && micros() - triggerTime < 1800000){
      if(isAuto){
        move(0, 20, 1800, 40, 0, 0);
      }
    } else if(micros() - triggerTime >= 1800000){
      if(stopOnce){
        if(isAuto){
          stop();
          threading = 2;
          configuration = true;
          stopOnce = true;
        }
      }
      if(button_x){
        isAuto = true;
        stt_bot = 8;
        stopOnce = true;
        stop();
        Serial.println("test");
        // start step two here;
        configuration = true;
        threading = 2;
      }
    }
  }
  if(threading == 2){
    if(configuration){
      Serial.println("first turn");
      configuration = false;
      progress = 0;
      triggerTime = micros();
      resetEncoder(true, true);
    }
    readEncoder();
    if(abs(compass()) > 1500 && micros() - triggerTime > 2000){
      if(stopOnce){
        stop();
        stopOnce = true;
        threading = 3;
        configuration = true;
        angle_bot = -1800;
        stt_bot = 8;
        isAuto = true;
      }

    } else {
      progress = 1;
      if(stopOnce != false){
        digitalWrite(m52, 0);
        digitalWrite(pwm10, 0);
        digitalWrite(m51, 1);
        if(isAuto){
          move(-180, 50, 900, 45, 10, 10);
        }
      }
    }
    if(button_x && abs(encoder2) > 400 && progress == 1){
      isAuto = true;
      stt_bot = 8;
      angle_bot = compass();
      stopOnce = true;
      configuration = true;
      threading = 3;
      progress = 0;
    }
  }
  if(threading == 3){
    if(configuration){
      configuration = false;
      triggerTime = micros();
    }
    if(micros() - triggerTime > 500000 && micros() - triggerTime < 1000000){
      if(isAuto){
        move(-175, 20, -3600, 30, 0, 0);
      }
      
    } else if(micros() - triggerTime  >= 1000000 && micros() - triggerTime < 1600000){
      // gap
      if(isAuto){
        digitalWrite(m52, 1);
        digitalWrite(pwm10, 1);
        digitalWrite(m51, 0);
      }
    }else if(micros() - triggerTime > 1600000){
      if(stopOnce){
        stop();
        stopOnce = false;
      }
      if(button_x){
        configuration = true;
        stopOnce = true;
        isAuto = true;
        threading = 4;
      }
    }
  }
  // edit threading
  if(threading == 4){
    if(configuration){
      Serial.println("go to farm");
      resetEncoder(false, true);
      configuration = false;
      triggerTime = micros();
      enableConfigPosition = true;
    }
    readEncoder();
    if(isAuto == true){
      run(2630, 1502, 0, 0, "right");
    }
    
    if(button_x && micros() - triggerTime > 500000){
      stt_bot = 8;
      isAuto = true;
      stopOnce = true;
      resetEncoder(true, true);
      readEncoder();
      Serial.println("end rice one");
      stop();
      configuration = true;
      threading = 5;
    }
  }
  if(threading == 5){
    if(configuration){
      Serial.println("first rice 2");
      enableConfigPosition = true;
      resetEncoder(true, true);
      triggerTime = micros();
      configuration = false;
    }
    if(isAuto){
      run(2178, 1276, 0, 0, "right");
    }
   
    if(button_x && micros() - triggerTime > 500000){
      stt_bot = 8;
      isAuto = true;
      Serial.println("hello checking end rice2");
      stopOnce = true;
      stop();
      configuration = true;
      threading = 6;
    }
  }
  if(threading == 6){
    if(configuration){
      Serial.println("first rice 1 right");
      configuration = false;
      enableConfigPosition = true;
      resetEncoder(true, true);
      triggerTime = micros();
    }
    readEncoder();
    if(isAuto){
      run(1085, 1233, 0, 0, "right");
    }
    
    if(button_x && micros() - triggerTime > 500000){
      stt_bot = 8;
      isAuto = true;
      Serial.println("hello checking end rice3");
      stopOnce = true;
      stop();
      configuration = true;
      threading = 7;
    }
  }
  if(threading == 7){
    if(configuration){
      enableConfigPosition = true;
      configuration = false;
      triggerTime = micros();
      resetEncoder(true, true);
    }
    if(isAuto){
      run(1556, 1420, 0, 0, "right");
    }
    
    if(button_x && micros() - triggerTime > 500000){
      stt_bot = 8;
      isAuto = true;
      Serial.println("hello checking end rice4");
      stopOnce = true;
      stop();
      configuration = true;
      threading = 8;
    }
  }
}

void retry(){
  threading = -1;
}
void start(){
  threading = 0;
  isAuto = true;
}