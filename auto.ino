
void runTasks(){
  if(land == RED){
    if(threading == 0){
      if(configuration){
        pushOut.action();
        hand_r_13.stop();
        hand_r_24.stop();
        triggerTime = micros();
        Serial.println("start");
        configuration = false;
        stopOnce = true;
        isAuto = true;
        runStart = 0;
      }
      int speedJust = 0;
      int angleJust = 0;
      unsigned long exchange = micros() - triggerTime;
      if(exchange > 0 && exchange < 1380000){
        angleJust = -map(exchange, 0, 1380000, -450, 280);
        if(exchange < 1010000){
          speedJust = map(exchange, 0, 1010000, 20, 102);
        }else {
          speedJust = 100 - map(exchange, 1010000, 1380000, 0, 90);
        }
        move(0, 30, angleJust, speedJust, 0, 0);
      }else if(exchange >= 1380000){
        if(stopOnce){
          stop();
          stopOnce = false;
        }
        insideRight.action();
      }
      if(button_start && exchange > 1000000){
        stopOnce = true;
        configuration = true;
        isAuto = true;
        enableConfigPosition = true;
        threading = 1;
      }
    }
    if(threading == 1){
      if(configuration){
        arm_r.stop();
        insideRight.action();
        stop();
        Serial.println("start get Rice");
        triggerTime = micros();
        enableConfigPosition = true;
        configuration = false;
        stopOnce = true;
      }
      if(micros() - triggerTime > 200000 && micros() - triggerTime < 700000){
        Serial.println("check");
        
        hand_r_13.action();
        hand_r_24.action();
      }else if(micros() - triggerTime > 700000 && micros() - triggerTime < 900000){
        if(isAuto){
          arm_r.action();
        }
      }else if(micros() - triggerTime > 900000 && micros() - triggerTime < 1400000){
        if(isAuto){
          move(0, 20, 900, 40, 0, 0);
        }
      }else if(micros() - triggerTime >= 1400000){
        if(stopOnce){
          if(isAuto){
            stop();
            threading = 2;
            configuration = true;
            stopOnce = true;
          }
        }
        if(button_start){
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
      }
      if(abs(compass()) > 1650 && micros() - triggerTime > 2000 || micros() - triggerTime >1000000){
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
          arm_l.stop();
          hand_l_13.stop();
          hand_l_24.stop();
          if(isAuto){
            move(-180, 60, 0, 45, 10, 10);
          }
        }
      }
      if(button_start && progress == 1){
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
        stopOnce = true;
      }
      if(micros() - triggerTime > 500000 && micros() - triggerTime < 1300000){
        if(isAuto){
          move(-175, 30, -900, 40, 0, 0);
        }
      }else if(micros() - triggerTime > 1400000){
        if(stopOnce){
          stop();
          stopOnce = false;
          isAuto = true;
        }
        Serial.println("check example");
        if(button_start){
          configuration = true;
          stopOnce = true;
          isAuto = true;
          threading = 4;
          // gap
          arm_l.action();
          hand_l_13.action();
          hand_l_24.action();
        }
      }
    }
    if(threading == 4){
      if(configuration){
        configuration = false;
        stopOnce = true;
        triggerTime = micros();
        endWait = false;
        enableConfigPosition =  true;
        Serial.println("check compass()");
        isAuto = true;
      }
      if(micros() - triggerTime <= 600000){
        
      }else if(micros() - triggerTime > 600000 && micros() - triggerTime < 1000000){
        move(-270, 30, -1800, 20, 0, 0);
      }else if(micros() - triggerTime >= 1000000 && micros() - triggerTime < 1500000){
        move(-270, 20, -900, 20, 0, 0);
      }else if(micros() - triggerTime >= 1500000 && micros() - triggerTime < 1500000){
        if(stopOnce){
          stop();
          stopOnce = false;
        }
      }
      
      if(micros() - triggerTime >=1500000 && button_start){
        if(enableTimeEnd){
            timeAutoRice = micros();
            enableTimeEnd = false;
          }
      }
      if(timeAutoRice != 0){
        if(micros() - timeAutoRice > 0 && micros() - timeAutoRice < 350000){
          arm_l.stop();
        }else if(micros() - timeAutoRice >= 350000 && micros() - timeAutoRice < 700000){
          hand_l_13.stop();
        }else if(micros() - timeAutoRice >= 700000){
          arm_l.action();
          endWait = true;
          stt_bot = 8;
          isAuto = true;
          stopOnce = true;
          Serial.println("end rice one");
          stop();
          configuration = true;
          threading = 6;
          timeAutoRice = 0;
          enableTimeEnd = true;
        }
      }
    }
    // edit threading
    if(threading == 6){
      if(configuration){
        Serial.println("first rice 2");
        enableConfigPosition = true;
        configuration = false;
        triggerTime = micros();
      }
        
      if(micros() - triggerTime > 0 && micros() - triggerTime < 1000000){
        run(2997, 1114, -90, -900, "right");
      }else if(micros() - triggerTime >= 1000000){
        if(stopOnce){
          stop();
          stopOnce = false;
        }
      }
      
      if(micros() - triggerTime >=1000000 && button_start){
        if(enableTimeEnd){
            timeAutoRice = micros();
            enableTimeEnd = false;
          }
      }
      if(timeAutoRice != 0){
        if(micros() - timeAutoRice > 0 && micros() - timeAutoRice < 350000){
          arm_l.stop();
        }else if(micros() - timeAutoRice >= 350000 && micros() - timeAutoRice < 700000){
          hand_l_24.stop();
        }else if(micros() - timeAutoRice >= 700000){
          arm_l.action();
          endWait = true;
          stt_bot = 8;
          isAuto = true;
          stopOnce = true;
          Serial.println("end rice one");
          stop();
          configuration = true;
          threading = 7;
          timeAutoRice = 0;
          enableTimeEnd = true;
        }
      }
    }
    if(threading == 7){
      if(configuration){
        Serial.println("first rice 2");
        enableConfigPosition = true;
        configuration = false;
        triggerTime = micros();
      }
        
      if(micros() - triggerTime > 0 && micros() - triggerTime < 2000000){
        run(1492, 1350, -90, -900, "right");
      }else if(micros() - triggerTime >= 2000000){
        if(stopOnce){
          stop();
          stopOnce = false;
        }
      }
      
      if(micros() - triggerTime >=1000000 && button_start){
        if(enableTimeEnd){
            timeAutoRice = micros();
            enableTimeEnd = false;
          }
      }
      if(timeAutoRice != 0){
        if(micros() - timeAutoRice > 0 && micros() - timeAutoRice < 350000){
          arm_r.stop();
        }else if(micros() - timeAutoRice >= 350000 && micros() - timeAutoRice < 700000){
          hand_r_13.stop();
        }else if(micros() - timeAutoRice >= 700000){
          arm_r.action();
          endWait = true;
          stt_bot = 8;
          isAuto = true;
          stopOnce = true;
          Serial.println("end rice one");
          stop();
          configuration = true;
          threading = 8;
          timeAutoRice = 0;
          enableTimeEnd = true;
        }
      }
    }
    if(threading == 8){
      if(configuration){
        Serial.println("first rice 2");
        enableConfigPosition = true;
        configuration = false;
        triggerTime = micros();
      }
        
      if(micros() - triggerTime > 0 && micros() - triggerTime < 1200000){
        run(2099, 1102, -90, -900, "right");
      }else if(micros() - triggerTime >= 1200000){
        if(stopOnce){
          stop();
          stopOnce = false;
        }
      }
      
      if(micros() - triggerTime >=1000000 && button_start){
        if(enableTimeEnd){
            timeAutoRice = micros();
            enableTimeEnd = false;
          }
      }
      if(timeAutoRice != 0){
        if(micros() - timeAutoRice > 0 && micros() - timeAutoRice < 350000){
          arm_r.stop();
        }else if(micros() - timeAutoRice >= 350000 && micros() - timeAutoRice < 700000){
          hand_r_24.stop();
        }else if(micros() - timeAutoRice >= 700000){
          arm_r.action();
          endWait = true;
          stt_bot = 8;
          isAuto = true;
          stopOnce = true;
          Serial.println("end rice one");
          stop();
          configuration = true;
          threading = 9;
          timeAutoRice = 0;
          enableTimeEnd = true;
        }
      }
    }
  } else if(land == BLUE){
    if(threading == 0){
      if(configuration){
        pushOut.action();
        hand_l_13.stop();
        hand_l_24.stop();
        triggerTime = micros();
        Serial.println("start");
        configuration = false;
        stopOnce = true;
        isAuto = true;
        runStart = 0;
      }
      int speedJust = 0;
      int angleJust = 0;
      unsigned long exchange = micros() - triggerTime;
      if(exchange > 0 && exchange < 1400000){
        angleJust = map(exchange, 0, 1380000, -450, 280);
        if(exchange < 1050000){
          speedJust = map(exchange, 0, 1050000, 20, 100);
        }else {
          speedJust = 100 - map(exchange, 1050000, 1400000, 0, 90);
        }
        move(0, 30, angleJust, speedJust, 0, 0);
      }else if(exchange >= 1400000){
        if(stopOnce){
          stop();
          stopOnce = false;
        }
        insideLeft.action();
      }
      if(button_start && exchange > 1000000){
        stopOnce = true;
        configuration = true;
        isAuto = true;
        enableConfigPosition = true;
        threading = 1;
      }
      // move(-90, 40, 0, 50, 0, 0);


    }
    
    if(threading == 1){
      if(configuration){
        arm_l.stop();
        insideLeft.action();
        stop();
        Serial.println("start get Rice");
        triggerTime = micros();
        enableConfigPosition = true;
        configuration = false;
        stopOnce = true;
      }
      if(micros() - triggerTime > 200000 && micros() - triggerTime < 700000){
        Serial.println("check");
        
        hand_l_13.action();
        hand_l_24.action();
      }else if(micros() - triggerTime > 700000 && micros() - triggerTime < 900000){
        if(isAuto){
          arm_l.action();
        }
      }else if(micros() - triggerTime > 900000 && micros() - triggerTime < 1400000){
        if(isAuto){
          move(0, 20, 2700, 40, 0, 0);
        }
      }else if(micros() - triggerTime >= 1400000){
        if(stopOnce){
          if(isAuto){
            stop();
            threading = 2;
            configuration = true;
            stopOnce = true;
          }
        }
        if(button_start){
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
      }
      if(abs(compass()) > 1700 && micros() - triggerTime > 2000 ||  micros() - triggerTime > 1100000){
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
          arm_r.stop();
          hand_r_13.stop();
          hand_r_24.stop();
          if(isAuto){
            move(180, 60, 0, 65, 10, 10);
          }
        }
      }
      if(button_start && progress == 1){
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
        isAuto = true;
      }
      if(micros() - triggerTime > 500000 && micros() - triggerTime < 1600000){
        if(isAuto){
          move(180, 20, 900, 26, 0, 0);
        }
      } else if(micros() - triggerTime  >= 1600000){
        if(stopOnce){
          stop();
          stopOnce = false;
        }
        // gap
        if(button_start){
          configuration = true;
          stopOnce = true;
          isAuto = true;
          threading = 5;
        }
      }
    }
    
    // chua test"
    // lui sang phai
    if(threading == 5){
      if(configuration){
        configuration = false;
        stopOnce = true;
        triggerTime = micros();
        endWait = false;
        enableConfigPosition =  true;
        Serial.println("check compass()");
        isAuto = true;
      }
      if(micros() - triggerTime < 450000){
        insideRight.action();
      }else if(micros() - triggerTime >= 450000 && micros() - triggerTime <= 750000){
        hand_r_13.action();
        hand_r_24.action();
      }else if(micros() - triggerTime >= 750000 && micros() - triggerTime <= 1400000){
        arm_r.action();
      }else if(micros() - triggerTime > 1400000 && micros() - triggerTime < 1700000){
        move(270, 50, 1800, 40, 0, 0);
      }else if(micros() - triggerTime >= 1700000 && micros() - triggerTime < 2200000){
        move(270, 40, 900, 40, 0, 0);
      }else if(micros() - triggerTime >= 2200000){
        if(stopOnce){
          stop();
          stopOnce = false;
        }
      }
      if(button_start && micros() - triggerTime > 500000){
        isAuto = true;
        stopOnce = true;
        configuration = true;
        threading = 6;
      }
      
      // if(micros() - triggerTime >=3000000 && button_start){
      //   if(enableTimeEnd){
      //       timeAutoRice = micros();
      //       enableTimeEnd = false;
      //     }
      // }
      // if(timeAutoRice != 0){
      //   if(micros() - timeAutoRice > 0 && micros() - timeAutoRice < 350000){
      //     arm_l.stop();
      //   }else if(micros() - timeAutoRice >= 350000 && micros() - timeAutoRice < 700000){
      //     hand_l_13.stop();
      //   }else if(micros() - timeAutoRice >= 700000){
      //     arm_l.action();
      //     endWait = true;
      //     stt_bot = 8;
      //     isAuto = true;
      //     stopOnce = true;
      //     Serial.println("end rice one");
      //     stop();
      //     configuration = true;
      //     threading = 6;
      //     timeAutoRice = 0;
      //     enableTimeEnd = true;
      //   }
      // }
    }
    if(threading == 6){
      if(configuration){
        Serial.println("first rice 2");
        enableConfigPosition = true;
        configuration = false;
        triggerTime = micros();
        enableTimeEnd = true;
        timeAutoRice = 0;
      }
      if(micros() - triggerTime > 0 && micros() - triggerTime < 5000000){
        run(4099, 1523, 0, 0, "left");
      }else if(micros() - triggerTime >= 5000000){
        if(stopOnce){
          stop();
          stopOnce = false;
        }
      }
      if(micros() - triggerTime >=1000000 && button_start){
        if(enableTimeEnd){
            timeAutoRice = micros();
            enableTimeEnd = false;
          }
      }
      if(timeAutoRice != 0){
        if(micros() - timeAutoRice > 0 && micros() - timeAutoRice < 350000){
          arm_r.stop();
        }else if(micros() - timeAutoRice >= 350000 && micros() - timeAutoRice < 700000){
          hand_r_13.stop();
        }else if(micros() - timeAutoRice >= 700000){
          arm_r.action();
          endWait = true;
          stt_bot = 8;
          isAuto = true;
          stopOnce = true;
          Serial.println("end rice one");
          stop();
          configuration = true;
          threading = 7;
          timeAutoRice = 0;
          enableTimeEnd = true;
        }
      }
    }
    // edit threading
    if(threading == 7){
      if(configuration){
        Serial.println("first rice 2");
        enableConfigPosition = true;
        configuration = false;
        triggerTime = micros();
      }
        
      if(micros() - triggerTime > 0 && micros() - triggerTime < 1000000){
        run(3365, 1307, 0, 0, "left");
      }else if(micros() - triggerTime >= 1000000){
        if(stopOnce){
          stop();
          stopOnce = false;
        }
      }
      
      if(micros() - triggerTime >=1000000 && button_start){
        if(enableTimeEnd){
            timeAutoRice = micros();
            enableTimeEnd = false;
          }
      }
      if(timeAutoRice != 0){
        if(micros() - timeAutoRice > 0 && micros() - timeAutoRice < 350000){
          arm_r.stop();
        }else if(micros() - timeAutoRice >= 350000 && micros() - timeAutoRice < 700000){
          hand_r_24.stop();
        }else if(micros() - timeAutoRice >= 700000){
          arm_r.action();
          endWait = true;
          stt_bot = 8;
          isAuto = true;
          stopOnce = true;
          Serial.println("end rice one");
          stop();
          configuration = true;
          threading = 8;
          timeAutoRice = 0;
          enableTimeEnd = true;
        }
      }
    }
    if(threading == 8){
      if(configuration){
        Serial.println("first rice 2");
        enableConfigPosition = true;
        configuration = false;
        triggerTime = micros();
      }
        
      if(micros() - triggerTime > 0 && micros() - triggerTime < 2000000){
        run(1548, 1314, 0, 0, "left");
      }else if(micros() - triggerTime >= 2000000){
        if(stopOnce){
          stop();
          stopOnce = false;
        }
      }
      
      if(micros() - triggerTime >=1000000 && button_start){
        if(enableTimeEnd){
            timeAutoRice = micros();
            enableTimeEnd = false;
          }
      }
      if(timeAutoRice != 0){
        if(micros() - timeAutoRice > 0 && micros() - timeAutoRice < 350000){
          arm_l.stop();
        }else if(micros() - timeAutoRice >= 350000 && micros() - timeAutoRice < 700000){
          hand_l_24.stop();
        }else if(micros() - timeAutoRice >= 700000){
          arm_l.action();
          endWait = true;
          stt_bot = 8;
          isAuto = true;
          stopOnce = true;
          Serial.println("end rice one");
          stop();
          configuration = true;
          threading = 9;
          timeAutoRice = 0;
          enableTimeEnd = true;
        }
      }
    }
    if(threading == 9){
      if(configuration){
        Serial.println("first rice 2");
        enableConfigPosition = true;
        configuration = false;
        triggerTime = micros();
      }
        
      if(micros() - triggerTime > 0 && micros() - triggerTime < 1200000){
        run(2306, 1561, 0, 0, "left");
      }else if(micros() - triggerTime >= 1200000){
        if(stopOnce){
          stop();
          stopOnce = false;
        }
      }
      
      if(micros() - triggerTime >=1000000 && button_start){
        if(enableTimeEnd){
            timeAutoRice = micros();
            enableTimeEnd = false;
          }
      }
      if(timeAutoRice != 0){
        if(micros() - timeAutoRice > 0 && micros() - timeAutoRice < 350000){
          arm_l.stop();
        }else if(micros() - timeAutoRice >= 350000 && micros() - timeAutoRice < 700000){
          hand_l_13.stop();
        }else if(micros() - timeAutoRice >= 700000){
          arm_l.action();
          endWait = true;
          stt_bot = 8;
          isAuto = true;
          stopOnce = true;
          Serial.println("end rice one");
          stop();
          configuration = true;
          threading = 10;
          timeAutoRice = 0;
          enableTimeEnd = true;
        }
      }
    }
  }
}
// 13 left a15
//24 left a14
// 13 right a13
// 24 right a12
void retry(){
  threading = -1;
}
void start(){
  threading = 0;
  isAuto = true;
}