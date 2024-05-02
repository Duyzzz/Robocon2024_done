float interpolate(float x, float x0, float x1, float y0, float y1) {
    return y0 + (y1 - y0) * ((x - x0) / (x1 - x0));
}

float getFirstSpeed(float initialDistanceSet){
  if(initialDistanceSet >= 3872.66){
    return 50;
  }else if(initialDistanceSet < 3872.66 && initialDistanceSet >= 2943.25){
    return interpolate(initialDistanceSet, 2943.25, 3872.66, 49, 50);
  }else if(initialDistanceSet < 2943.25 && initialDistanceSet >= 2550.06){
    return interpolate(initialDistanceSet, 2550.06, 2943.25, 48, 49);
  }else if(initialDistanceSet < 2550.06 && initialDistanceSet >= 2155.55){
    return interpolate(initialDistanceSet, 2155.55, 2550.06, 47, 48);
  }else if(initialDistanceSet < 2155.55 && initialDistanceSet >= 1731.81){
    return interpolate(initialDistanceSet, 1731.81, 2155.55, 45, 47);
  }else if(initialDistanceSet < 1731.81 && initialDistanceSet >= 1341.02){
    return interpolate(initialDistanceSet, 1341.02, 1731.81, 42, 45);
  }else if(initialDistanceSet < 1341.02 && initialDistanceSet >= 1001.45){
    return interpolate(initialDistanceSet, 1001.45, 1341.02, 34, 42);
  }else if(initialDistanceSet < 1001.45 && initialDistanceSet >= 528.34){
    return interpolate(initialDistanceSet, 528.34, 1001.45, 28, 34);
  }else if(initialDistanceSet < 528.34 && initialDistanceSet >= 473.85){
    return interpolate(initialDistanceSet, 473.85, 528.34, 24, 28);
  }else if(initialDistanceSet < 473.85 && initialDistanceSet >= 288){
    return interpolate(initialDistanceSet, 288, 473.85, 20, 24);
  }
}float getMaxSpeed(float initialDistanceSet){
  if(initialDistanceSet >= 3872.66){
    return 135;
  }else if(initialDistanceSet < 3872.66 && initialDistanceSet >= 2943.25){
    return interpolate(initialDistanceSet, 2943.25, 3872.66, 119, 135);
  }else if(initialDistanceSet < 2943.25 && initialDistanceSet >= 2550.06){
    return interpolate(initialDistanceSet, 2550.06, 2943.25, 110, 119);
  }else if(initialDistanceSet < 2550.06 && initialDistanceSet >= 2155.55){
    return interpolate(initialDistanceSet, 2155.55, 2550.06, 100, 110);
  }else if(initialDistanceSet < 2155.55 && initialDistanceSet >= 1731.81){
    return interpolate(initialDistanceSet, 1731.81, 2155.55, 90, 100);
  }else if(initialDistanceSet < 1731.81 && initialDistanceSet >= 1341.02){
    return interpolate(initialDistanceSet, 1341.02, 1731.81, 78, 90);
  }else if(initialDistanceSet < 1341.02 && initialDistanceSet >= 1001.45){
    return interpolate(initialDistanceSet, 1001.45, 1341.02, 64, 78);
  }else if(initialDistanceSet < 1001.45 && initialDistanceSet >= 528.34){
    return interpolate(initialDistanceSet, 528.34, 1001.45, 40, 64);
  }else if(initialDistanceSet < 528.34 && initialDistanceSet >= 473.85){
    return interpolate(initialDistanceSet, 473.85, 528.34, 34, 40);
  }else if(initialDistanceSet < 473.85 && initialDistanceSet >= 288){
    return interpolate(initialDistanceSet, 288, 473.85, 28, 34);
  }
}

// void run(int needX, int needY, int firstSpeed, int expectedSpeed, String request){
//   signed long x;
//   signed long y;
//   if(request == "right"){
//     x = readRightSick() - needX;
//     y = readHeadSick() - needY;
//   }else if(request == "left"){
//     x = readLeftSick() - needX;
//     y = readHeadSick() - needY;
//   }
//   float nowDistance = sqrt(abs(x*x) + abs(y*y));
//   if(enableConfigPosition){
//     // Serial.print(firstSpeedForPosition);
//     // Serial.print(" ");
//     // Serial.println(expectedSpeedForPosition);
//     initialDistance = nowDistance;
//     timeSoft = 0;
//     enableConfigPosition = false;
//   }
//   if(nowDistance >= initialDistance*8/10){
//     speed = map(abs(initialDistance - nowDistance), 0, initialDistance*2/10, firstSpeed, expectedSpeed);
//   }else if(nowDistance < initialDistance*1/3){
//     speed = expectedSpeed + 4 - map(abs(initialDistance*1/3 - nowDistance), 0, initialDistance*1/3, 19, expectedSpeed);
//   }else if(nowDistance >= initialDistance*1/3 && nowDistance < initialDistance*8/10){
//     speed = expectedSpeed;
//   }
//     speed = constrain(speed, 0, expectedSpeed);
//   int tempSpeed = speed;
//   Serial.println(tempSpeed);
//   if(y != 0){
//     float oket = (float)abs(x)/(float)abs(y);
//     float alpha = (float)atan(oket)*1800/PI;
//     //Serial.println(alpha);
//     if(x < 10 && x > -10 && y > -10 && y < 10){
//       stop();
//       Serial.print("check 0 ");
//       enableGoFarm = true;
//     }else if(x > 0 && y > 0){
//        Serial.print("check 1 ");
//       move(0, 50, -alpha, tempSpeed, 0, 0);
//     }else if(x < 0 && y > 0){
//        Serial.print("check 2 ");
//       move(0, 50, alpha, tempSpeed, 0, 0);
//     }else if(x > 0 && y < 0){
//        Serial.print("check 3 ");
//       move(0, 50, alpha - 1800, tempSpeed, 0, 0);
//     } else if(x < 0 && y < 0){
//       Serial.print("check 4 ");
//       move(0, 50, 1800 - alpha, tempSpeed, 0, 0);
//     } else if(x == 0 && y > 0){
//        Serial.print("check 5 ");
//       move(0, 50, 0, tempSpeed, 0, 0);
//     } else if(x == 0 && y < 0){
//        Serial.print("check 6 ");
//       move(0, 50, 1800, tempSpeed, 0, 0);
//     }
//   }else {
//     if(x > 0){
//       Serial.print("check 7 ");
//        move(0, 50, -900, tempSpeed, 0, 0);
//     }else if(x < 0){
//       Serial.print("check 8 ");
//       move(0, 50, 900, tempSpeed, 0, 0);
//     }else {
//       Serial.print("check 9 ");
//       stop();
//     }
//   }
// }


void run(int needX, int needY, int direction, int change, String request){
  signed long x;
  signed long y;
  if(request == "right"){
    x = readRightSick() - needX;
    y = readHeadSick() - needY;
    float nowDistance = sqrt(abs(x*x) + abs(y*y));
  Serial.println(nowDistance);
  if(enableConfigPosition){
    firstSpeedForPosition = getFirstSpeed(nowDistance);
    expectedSpeedForPosition = getMaxSpeed(nowDistance);
    // Serial.print(firstSpeedForPosition);
    // Serial.print(" ");
    // Serial.println(expectedSpeedForPosition);
    initialDistance = nowDistance;
    timeSoft = 0;
    enableConfigPosition = false;
  }
  /*Serial.print(firstSpeedForPosition);
  Serial.print(" ");
  Serial.print(expectedSpeedForPosition);
  Serial.print(" ");*/
  if(nowDistance >= initialDistance*8/10){
    speed = map(abs(initialDistance - nowDistance), 0, initialDistance*2/10, firstSpeedForPosition, expectedSpeedForPosition);
  }else if(nowDistance < initialDistance*1/3){
    speed = expectedSpeedForPosition + 5 - map(abs(initialDistance*1/3 - nowDistance), 0, initialDistance*1/3, 19, expectedSpeedForPosition);
  }else if(nowDistance >= initialDistance*1/3 && nowDistance < initialDistance*8/10){
    speed = expectedSpeedForPosition;
  }
    speed = constrain(speed, 0, expectedSpeedForPosition);
  int tempSpeed = speed;
  //Serial.println(tempSpeed);
  if(y != 0){
    float oket = (float)abs(x)/(float)abs(y);
    float alpha = (float)atan(oket)*1800/PI;
    //Serial.println(alpha);
    if(x < 10 && x > -10 && y > -10 && y < 10){
      stop();
      Serial.print("check 0 ");
      enableGoFarm = true;
    }else if(x > 0 && y > 0){
       Serial.print("check 1 ");
      move(0, 50, -alpha, tempSpeed, 0, 0);
    }else if(x < 0 && y > 0){
       Serial.print("check 2 ");
      move(0, 50, alpha, tempSpeed, 0, 0);
    }else if(x > 0 && y < 0){
       Serial.print("check 3 ");
      move(0, 50, alpha - 1800, tempSpeed, 0, 0);
    } else if(x < 0 && y < 0){
      Serial.print("check 4 ");
      move(0, 50, 1800 - alpha, tempSpeed, 0, 0);
    } else if(x == 0 && y > 0){
       Serial.print("check 5 ");
      move(0, 50, 0, tempSpeed, 0, 0);
    } else if(x == 0 && y < 0){
       Serial.print("check 6 ");
      move(0, 50, 1800, tempSpeed, 0, 0);
    }
  }else {
    if(x > 0){
      Serial.print("check 7 ");
       move(0, 50, -900, tempSpeed, 0, 0);
    }else if(x < 0){
      Serial.print("check 8 ");
      move(0, 50, 900, tempSpeed, 0, 0);
    }else {
      Serial.print("check 9 ");
      stop();
    }
  }
  }else if(request == "left"){
    x = readLeftSick() - needX;
    y = readHeadSick() - needY;
    float nowDistance = sqrt(abs(x*x) + abs(y*y));
  Serial.println(nowDistance);
  if(enableConfigPosition){
    firstSpeedForPosition = getFirstSpeed(nowDistance);
    expectedSpeedForPosition = getMaxSpeed(nowDistance);
    // Serial.print(firstSpeedForPosition);
    // Serial.print(" ");
    // Serial.println(expectedSpeedForPosition);
    initialDistance = nowDistance;
    timeSoft = 0;
    enableConfigPosition = false;
  }
  /*Serial.print(firstSpeedForPosition);
  Serial.print(" ");
  Serial.print(expectedSpeedForPosition);
  Serial.print(" ");*/
  if(nowDistance >= initialDistance*8/10){
    speed = map(abs(initialDistance - nowDistance), 0, initialDistance*2/10, firstSpeedForPosition, expectedSpeedForPosition);
  }else if(nowDistance < initialDistance*1/3){
    speed = expectedSpeedForPosition + 5 - map(abs(initialDistance*1/3 - nowDistance), 0, initialDistance*1/3, 19, expectedSpeedForPosition);
  }else if(nowDistance >= initialDistance*1/3 && nowDistance < initialDistance*8/10){
    speed = expectedSpeedForPosition;
  }
    speed = constrain(speed, 0, expectedSpeedForPosition);
  int tempSpeed = speed;
  //Serial.println(tempSpeed);
  if(y != 0){
    float oket = (float)abs(x)/(float)abs(y);
    float alpha = (float)atan(oket)*1800/PI;
    //Serial.println(alpha);
    if(x < 10 && x > -10 && y > -10 && y < 10){
      stop();
      Serial.print("check 0 ");
    }else if(x > 0 && y > 0){
       Serial.print("check 1 ");
      move(0, 50, alpha, tempSpeed, 0, 0);
    }else if(x < 0 && y > 0){
       Serial.print("check 2 ");
      move(0, 50, -alpha, tempSpeed, 0, 0);
    }else if(x > 0 && y < 0){
       Serial.print("check 3 ");
      move(0, 50, 1800 - alpha, tempSpeed, 0, 0);
    } else if(x < 0 && y < 0){
      Serial.print("check 4 ");
      move(0, 50, alpha - 1800, tempSpeed, 0, 0);
    } else if(x == 0 && y > 0){
       Serial.print("check 5 ");
      move(0, 50, 0, tempSpeed, 0, 0);
    } else if(x == 0 && y < 0){
       Serial.print("check 6 ");
      move(0, 50, 1800, tempSpeed, 0, 0);
    }
  }else {
    if(x > 0){
      Serial.print("check 7 ");
       move(0, 50, 900, tempSpeed, 0, 0);
    }else if(x < 0){
      Serial.print("check 8 ");
      move(0, 50, -900, tempSpeed, 0, 0);
    }else {
      Serial.print("check 9 ");
      stop();
    }
  }
  }
}


// void run(int needX, int needY, String request){
//   signed long x;
//   signed long y;
//   if(request == "right"){
//     x = readRightSick() - needX;
//     y = readHeadSick() - needY;
//   }else if(request == "left"){
//     x = readLeftSick() - needX;
//     y = readHeadSick() - needY;
//   }
//   float nowDistance = sqrt(abs(x*x) + abs(y*y));
//   if(enableConfigPosition){
//     firstSpeedForPosition = getFirstSpeed(nowDistance);
//     expectedSpeedForPosition = getMaxSpeed(nowDistance);
//     // Serial.print(firstSpeedForPosition);
//     // Serial.print(" ");
//     // Serial.println(expectedSpeedForPosition);
//     initialDistance = nowDistance;
//     timeSoft = 0;
//     enableConfigPosition = false;
//   }
//   Serial.print(firstSpeedForPosition);
//   Serial.print(" ");
//   Serial.print(expectedSpeedForPosition);
//   Serial.print(" ");
//   if(nowDistance >= initialDistance*8/10){
//     speed = map(abs(initialDistance - nowDistance), 0, initialDistance*2/10, firstSpeedForPosition, expectedSpeedForPosition);
//   }else if(nowDistance < initialDistance*1/3){
//     speed = expectedSpeedForPosition + 5 - map(abs(initialDistance*1/3 - nowDistance), 0, initialDistance*1/3, 19, expectedSpeedForPosition);
//   }else if(nowDistance >= initialDistance*1/3 && nowDistance < initialDistance*8/10){
//     speed = expectedSpeedForPosition;
//   }
//     speed = constrain(speed, 0, expectedSpeedForPosition);
//   int tempSpeed = speed;
//   Serial.println(tempSpeed);
//   if(y != 0){
//     float oket = (float)abs(x)/(float)abs(y);
//     float alpha = (float)atan(oket)*1800/PI;
//     //Serial.println(alpha);
//     if(x < 10 && x > -10 && y > -10 && y < 10){
//       stop();
//       Serial.print("check 0 ");
//       enableGoFarm = true;
//     }else if(x > 0 && y > 0){
//        Serial.print("check 1 ");
//       move(0, 50, 1800 + alpha, tempSpeed, 0, 0);
//     }else if(x < 0 && y > 0){
//        Serial.print("check 2 ");
//       move(0, 50, 1800 - alpha, tempSpeed, 0, 0);
//     }else if(x > 0 && y < 0){
//        Serial.print("check 3 ");
//       move(0, 50, 3600 - alpha, tempSpeed, 0, 0);
//     } else if(x < 0 && y < 0){
//       Serial.print("check 4 ");
//       move(0, 50, alpha, tempSpeed, 0, 0);
//     } else if(x == 0 && y > 0){
//        Serial.print("check 5 ");
//       move(0, 50, 1800, tempSpeed, 0, 0);
//     } else if(x == 0 && y < 0){
//        Serial.print("check 6 ");
//       move(0, 50, 0, tempSpeed, 0, 0);
//     }
//   }else {
//     if(x > 0){
//       Serial.print("check 7 ");
//        move(0, 50, 2700, tempSpeed, 0, 0);
//     }else if(x < 0){
//       Serial.print("check 8 ");
//       move(0, 50, 900, tempSpeed, 0, 0);
//     }else {
//       Serial.print("check 9 ");
//       stop();
//     }
//   }
// }



