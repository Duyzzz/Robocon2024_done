String encoderData = "";

void readEncoder(){
  Serial2.print('d');
  Serial.print("reading encoder");
  if(Serial2.available()){
    encoderData = Serial2.readStringUntil('}');
    if(encoderData[0] == '{'){
      String enReader1 = "";
      int index = encoderData.indexOf(';');
      for(int i = 1; i < index; i++){
        enReader1 = enReader1 + encoderData[i];
      }
      encoder1 = enReader1.toInt();
      String enReader2 = "";
      int len = encoderData.length();
      for(int i = index + 1; i < len; i++){
        enReader2 = enReader2 + encoderData[i];
      }
      encoder2 = enReader2.toInt();
    }
  }
}
void resetEncoder(bool Encoder1_, bool Encoder2_){
  if(Encoder1_){
    Serial2.print('a');
    Serial.println("encoder 1 rested");
  } 
  if(Encoder2_){
    Serial.println("encoder 2 rested");
    Serial2.print('b');
  }
}
void goEncoder(int requireValue){
  //Serial.println("chec check");
  if(encoderPID.checkTime()){
    readEncoder();
    encoderPID.getInput(abs(encoder2));
    if(encoderPID.error() < 300 && encoderPID.error() > 300){
      encoderPID.SetTunings(0.16, 0.05, 0.002);
      encoderPID.SetOutputLimits(-40, 40);
    }else {
      encoderPID.SetTunings(0.1, 0.05, 0.004);
      encoderPID.SetOutputLimits(-90, 90);

    }
    encoderPID.Compute();
    encoderPID.resetTimeSample();
  }
  Serial.print(encoderPID.setPointOut());
  Serial.print(" ");
  Serial.print(encoderPID.inputOut());
  Serial.print(" ");
  Serial.println(encoderPID.out());
  if(encoderPID.out() > 2){
    soft_start(12, encoderPID.out());
    up_pid(0, v_bot, 100, 100);
    Serial.println("up");
  }else if(encoderPID.out() < -2){
    soft_start(12, -encoderPID.out());
    down_pid(0, v_bot, 100, 100);
    Serial.println("down");
  }else {
    stop();
  }
}
bool goEncoder(int requireDirection, int requireValue){
  //Serial.println("chec check");
  if(encoderPID.checkTime()){
    readEncoder();
    //Serial.println(encoder2);
    encoderPID.getInput(abs(encoder2));
    Serial.print(encoderPID.setPointOut());
    Serial.print(" ");
    Serial.print(encoderPID.inputOut());
    Serial.print(" ");
    Serial.println(encoderPID.out());
    if(encoderPID.error() < 50 && encoderPID.error() > -50){
      encoderPID.SetTunings(0.74, 0.05, 0.14);
      encoderPID.SetOutputLimits(-13, 13);
    }else if(encoderPID.error() < 100 && encoderPID.error() > -100){
      encoderPID.SetTunings(0.78, 0.15, 0.09);
      encoderPID.SetOutputLimits(-20, 20);
    }else if(encoderPID.error() < 200 && encoderPID.error() > -200){
      encoderPID.SetTunings(0.65, 0.2, 0.005);
      encoderPID.SetOutputLimits(-25, 25);
    }else if(encoderPID.error() < 300 && encoderPID.error() > -300){
      encoderPID.SetTunings(0.65, 0.2, 0.005);
      encoderPID.SetOutputLimits(-30, 30);
    }else if(encoderPID.error() < 500 && encoderPID.error() > -500){
      encoderPID.SetTunings(0.65, 0.2, 0.005);
      encoderPID.SetOutputLimits(-35, 35);
    }else if(encoderPID.error() < 1000 && encoderPID.error() > -1000){
      encoderPID.SetTunings(0.61, 0.2, 0.001);
      encoderPID.SetOutputLimits(-50, 50);
    }else if(encoderPID.error() < 1500 && encoderPID.error() > -1500){
      encoderPID.SetTunings(0.8, 0.08, 0.008);
      encoderPID.SetOutputLimits(-60, 60);
    }else if(encoderPID.error() < 2000 && encoderPID.error() > -2000){
      encoderPID.SetTunings(0.8, 0.08, 0.008);
      encoderPID.SetOutputLimits(-80, 80);
    }
    else if(encoderPID.error() < 3500 && encoderPID.error() > -3500){
      encoderPID.SetTunings(0.8, 0.4, 0.008);
      encoderPID.SetOutputLimits(-70, 70);
    }else {
      encoderPID.SetTunings(0.54, 0.05, 0.004);
      encoderPID.SetOutputLimits(-60, 60);
    }
    encoderPID.Compute();
    encoderPID.resetTimeSample();
  }

  if(encoderPID.out() > 1){
    move(0, 40, requireDirection , encoderPID.out(), 10, 10);
    // Serial.println("up");
  }else if(encoderPID.out() < -1){
    move(0, 40, requireDirection + 1800, -encoderPID.out(), 10, 10);
    // Serial.println("down");
  }else if(encoderPID.out() <= 0.5 && encoderPID.out() > -0.5 && abs(encoderPID.error()) < 25){
    stop();
    Serial.println("check exam");
    return true;
  }
  return false;
}