
void runTasks(){
  if(land == RED){
    if(threading == 0){
      if(configuration){
        encoder2 = 0;
        triggerTime = micros();
        Serial.println("start");
        configuration = false;
        stopOnce = true;
        isAuto = true;
      }
      Serial.println("checking step 1");
      if(micros() - triggerTime > 5080000){
        // start step two here;
        encoder2 = 0;
        Serial.println("end 1");
        angle_bot = compass();
        configuration = true;
        if(stopOnce){
          stop();
          stopOnce = false;
          arm_r.stop();
        }
        threading = 1;
        isAuto = true;
      }else {
        int speedJust = 0;
        int angleJust = 0;
        if(encoder2 < 0){
          encoder2 = 0;
        }else if(encoder2 >= 0 && encoder2 < 175){
          speedJust = map(encoder2, 0, 175, 30, 80);
        }else if(encoder2 >= 175 && encoder2 < 387){
          speedJust = 80;
        }else if(encoder2 >= 387 && encoder2 <= 880){
          speedJust = 80 - map(encoder2, 400, 1130, 0, 76);
        }else if(encoder2 > 880){
          if(stopOnce){
            stop();
            threading = 1;
            configuration = true;
            stopOnce = false;
          }
        }
        angleJust = 1350 - map(encoder2, 0, 455, 0, 450);
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
        arm_r.stop();
        stop();
        Serial.println("start get Rice");
        triggerTime = micros();
        enableConfigPosition = true;
        configuration = false;
        stopOnce = true;
        isAuto = true;
      }
      if(micros() - triggerTime > 800000 && micros() - triggerTime < 1300000){
        Serial.println("check");
        arm_r.action();
        hand_r_13.action();
        hand_r_24.action();
      }else if(micros() - triggerTime > 1300000 && micros() - triggerTime < 1800000){
        if(isAuto){
          move(0, 25, 1800, 35, 0, 0);
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
        if(button_start && micros() - triggerTime > 1000000){
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
        encoder2 = 0;
      }
      if(abs(compass()) > 1650 && micros() - triggerTime > 2000){
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
            move(-180, 51, 900, 40, 10, 10);
          }
        }
      }
      if(button_start && abs(encoder2) > 400 && progress == 1){
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
      if(micros() - triggerTime > 500000 && micros() - triggerTime < 1300000){
        if(isAuto){
          move(-175, 30, -3600, 25, 0, 0);
        }
      } else if(micros() - triggerTime  >= 1300000 && micros() - triggerTime < 1700000){
        // gap
        if(isAuto){
          arm_l.action();
          hand_l_13.action();
          hand_l_24.action();
        }
      }else if(micros() - triggerTime > 1700000){
        if(stopOnce){
          stop();
          configuration = true;
          stopOnce = true;
          isAuto = true;
          threading = 4;
        }
        Serial.println("check example");
        if(button_start){
          configuration = true;
          stopOnce = true;
          isAuto = true;
          threading = 4;
        }
      }
    }
    if(threading == 4){
      if(configuration){
        configuration = false;
        stopOnce = true;
        Serial3.write('a');
        triggerTime = micros();
        endWait = false;
      }
      if(micros() - triggerTime > 1000000 && micros() - triggerTime < 1500000){
        move(-90, 30, 280, 50, 0, 0); 
      }else if(micros() - triggerTime >= 1500000 && micros() - triggerTime <2800000){
        // stop();
        run(3602, 1372, -90, -900, "right");
      }else if(micros() - triggerTime >= 2800000){
        if(stopOnce){
          stop();
          stopOnce = false;
        }
        isAuto = false;
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
          encoder2 = 0;
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
        encoder2 = 0;
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
          encoder2 = 0;
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
        encoder2 = 0;
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
          encoder2 = 0;
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
        encoder2 = 0;
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
          encoder2 = 0;
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
        encoder2 = 0;
        triggerTime = micros();
        Serial.println("start blue");
        configuration = false;
        stopOnce = true;
        isAuto = true;
      }
      Serial.println("checking step 1");
      if(micros() - triggerTime > 5080000){
        // start step two here;
        encoder2 = 0;
        Serial.println("end 1");
        angle_bot = compass();
        configuration = true;
        if(stopOnce){
          stop();
          stopOnce = false;
          arm_r.action();
        }
        threading = 1;
      }else {
        int speedJust = 0;
        int angleJust = 0;
        if(encoder2 < 0){
          encoder2 = 0;
        }else if(encoder2 >= 0 && encoder2 < 175){
          speedJust = map(encoder2, 0, 175, 30, 80);
        }else if(encoder2 >= 175 && encoder2 < 387){
          speedJust = 80;
        }else if(encoder2 >= 387 && encoder2 <= 880){
          speedJust = 80 - map(encoder2, 400, 1130, 0, 76);
        }else if(encoder2 > 880){
          if(stopOnce){
            stop();
            threading = 1;
            configuration = true;
            stopOnce = false;
          }
        }
        angleJust = map(encoder2, 0, 455, 450, 900);
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
        arm_r.action();
        stop();
        Serial.println("start get Rice");
        triggerTime = micros();
        enableConfigPosition = true;
        configuration = false;
        stopOnce = true;
      }
      if(micros() - triggerTime > 800000 && micros() - triggerTime < 1300000){
        Serial.println("check");
        arm_l.stop();
        hand_l_13.action();
        hand_l_24.action();
      }else if(micros() - triggerTime > 1300000 && micros() - triggerTime < 1800000){
        if(isAuto){
          move(0, 20, 0, 40, 0, 0);
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
        encoder2 = 0;
      }
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
          arm_l.stop();
          hand_l_13.stop();
          hand_l_24.stop();
          if(isAuto){
            move(180, 50, 900, 45, 10, 10);
          }
        }
      }
      if(button_x && abs(encoder2) > 50 && progress == 1){
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
          move(180, 20, 1800, 30, 0, 0);
        }
      } else if(micros() - triggerTime  >= 1000000 && micros() - triggerTime < 1600000){
        // gap
        if(isAuto){
          arm_l.stop();
          hand_l_13.stop();
          hand_l_24.stop();
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
    // chua test"
    // lui sang phai
    if(threading == 4){
      if(configuration){
        configuration = false;
        stopOnce = true;
        triggerTime = micros();
        encoder2 = 0;
      }
      if(micros() - triggerTime > 0 && micros() - triggerTime < 500000){
        if(isAuto){
          move(270, 40, 3600, 20, 0, 0);
        }
      }else if(micros() - triggerTime > 500000 && micros() - triggerTime < 600000){
        if(isAuto){
          move(270, 10, 4500, 20, 0, 0);
        }
      }else {
        if(stopOnce){
          stop();
          Serial3.print('a');
          stopOnce = false;
          if(micros() - triggerTime > 1600000){
            configuration = true;
            stopOnce = true;
            threading = 5;
          }
        }
      }
    }
    // quay 90 
    // toc do tang cua encoder ...
    // lui cham
    // reset goc
    
    // edit threading
    if(threading == 5){
      if(configuration){
        Serial.println("go to farm");
        encoder2 = 0;
        configuration = false;
        triggerTime = micros();
        enableConfigPosition = true;
      }
      if(isAuto == true){
        run(2630, 1502, 0, 0, "right");
      }
      if(button_x && micros() - triggerTime > 500000){
        stt_bot = 8;
        isAuto = true;
        stopOnce = true;
        encoder2 = 0;
        Serial.println("end rice one");
        stop();
        configuration = true;
        threading = 6;
      }
    }
    if(threading == 6){
      if(configuration){
        Serial.println("first rice 2");
        enableConfigPosition = true;
        encoder2 = 0;
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
        threading = 7;
      }
    }
    if(threading == 7){
      if(configuration){
        Serial.println("first rice 1 right");
        configuration = false;
        enableConfigPosition = true;
        encoder2 = 0;
        triggerTime = micros();
      }
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
        threading = 8;
      }
    }
    if(threading == 8){
      if(configuration){
        enableConfigPosition = true;
        configuration = false;
        triggerTime = micros();
        encoder2 = 0;
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
        threading = 9;
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