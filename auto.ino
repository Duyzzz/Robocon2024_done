#include <Arduino.h>
class Task
{
protected:
    bool Start = false;
    bool Loop = false;
    bool End = true;
    bool AfterLoop = false;
    void (*StartFunction)();
    void (*LoopFunction)();
    void (*EndFunction)();
public:
    Task() : StartFunction(nullptr), LoopFunction(nullptr), EndFunction(nullptr) {}
    void startFunc(void(*startFunction)()){
        StartFunction = startFunction;
    }
    void loopingFunc(void(*loopingFunction)()){
        LoopFunction = loopingFunction;
    }
    void endFunc(void(*endFunction)()){
        EndFunction = endFunction;
    }
    void getFunction(void(*startFunction)(), void(*loopingFunction)(), void(*endFunction)()){
      StartFunction = startFunction;
      LoopFunction = loopingFunction;
      EndFunction = endFunction;
    }
    void start(){
        End = false;
        Start = true;
    }
    void end(){
        if(!End && AfterLoop){
            EndFunction();
            Loop = false;
            Start = false;
            End = true;
        }
        
    }
    void reset(){
      Start = false;
      Loop = false;
      End = true;
      AfterLoop = false;
    }
    void run(){
        //Serial.println("checking");
        if(!End){
            if(Start){
                StartFunction();
                Start = false;
                Loop = true;
            }
            if(Loop){
                LoopFunction();
                AfterLoop = true;
            }
        }
    }
};

Task rice1;
Task rice2;
Task startMove;
Task goUpGetRice;
Task grapRice;
Task turn;

//-------------------------------------------- step 1 funcs -------------------------------------//
void firstMoveStart(){
  encoderPID.getSetPoint(800);
  triggerTime = micros();
  Serial.println("start");
}
void secondMoveStart(){
  Serial.println("checking step 1");
  if(goEncoder(450, 820) || micros() - triggerTime > 1020000){
    startMove.end();
  }
}
void thirdMoveStart(){
  // start step two here;
  resetEncoder(true, true);
  Serial.println("end 1");
  goUpGetRice.start();
  angle_bot = compass();
}
//--------------------------------------------- step 2 funcs-------------------------------//
void firstGoUpGetRice(){
  stop();
  stopOnce = true;
  encoderPID.getSetPoint(2950);
  Serial.println("start get Rice");
  triggerTime = micros();
}
void secondGoUpGetRice(){
  if(micros() - triggerTime > 1300000){
    if(stopOnce){
      stop();
      angle_bot = compass();
      stopOnce = false;
    }
  } else if(goEncoder(0, 2950) && micros() - triggerTime > 200000){
    if(stopOnce){
      stop();
      angle_bot = compass();
      stopOnce = false;
    }
  }
  if(button_x){
    isAuto = true;
    stt_bot = 8;
    goUpGetRice.end();
  }
  //dist_en = abs(encoder2);
  //run_distance(3000, 0, 80, 10, 10, 10, 0);
}
void thirdGoUpGetRice(){
  stopOnce = true;
  stop();
  Serial.println("test");
  // start step two here;
  turn.start();
}
//--------------------------------------------- turn 180 -----------------------------------//
void firstTurn(){
  Serial.println("first turn");
}
void secondTurn(){
  if(abs(compass()) > 1550){
    if(stopOnce){
      stop();
      stopOnce = false;
      angle_bot = -1800;
    }
  } else {
    move(-180, 50, 0, 45, 10, 10);
  }
  if(button_x && abs(compass()) > 1550){
    isAuto = true;
    stt_bot = 8;
    angle_bot = compass();
    turn.end();
  }
}
void thirdTurn(){
  rice1.start();
  stopOnce = true;
}
//--------------------------------------------- step rice1 funcs-------------------------------//
void firstRiceOne(){
  Serial.println("go to farm");
  resetEncoder(false, true);
}
void secondRiceOne(){
  readEncoder();
  if(abs(encoder2) >= 5180){
    if(stopOnce){
      stop();
      stopOnce = false;
    }
    if(button_x){
      stt_bot = 8;
      isAuto = true;
      rice1.end();
    }
  }else {
    float temp = (float)abs(abs(encoder2) - 6050)/6050*60 + 15;
    int get = temp;
    int more = abs(temp);
    //move(-265, 30, 1210, more, 10, 10);
    move(-265, 25, 1200, more, 10, 10);
  }
  if(button_x && abs(encoder2) >= 4050){
    stt_bot = 8;
    isAuto = true;
    rice1.end();
  }
}
void thirdRiceOne(){
  stopOnce = true;
  resetEncoder(true, true);
  readEncoder();
  Serial.println("end rice one");
  stop();
  rice2.start();
}

//
//rice2. move(-262, 30, 350, 90, 10, 10);

//----------------------------------------------rice 24------------------------------------------//
void firstRiceTwo(){
  Serial.println("first rice 2");
}
void secondRiceTwo(){
  readEncoder();
  if(abs(encoder2) >= 870){
    if(stopOnce){
      stop();
      stopOnce = false;
    }
  }else {
    float temp = (float)abs(abs(encoder2) - 870)/870*60 + 15;
    int get = temp;
    int more = abs(temp);
    move(-262, 30, 350, more, 10, 10);
    Serial.println("hello checking loop rice2");
  }
  if(button_x && abs(encoder2) >= 700){
    stt_bot = 8;
    isAuto = true;
    Serial.println("hello checking end rice2");
    rice2.end();
  }
}
void thirdRiceTwo(){
  stopOnce = true;
  stop();
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
void autoConfiguration(){
  startMove.getFunction(&firstMoveStart, &secondMoveStart, &thirdMoveStart);
  goUpGetRice.getFunction(&firstGoUpGetRice, &secondGoUpGetRice, &thirdGoUpGetRice);
  turn.getFunction(&firstTurn, &secondTurn, &thirdTurn);
  rice1.getFunction(&firstRiceOne, &secondRiceOne, &thirdRiceOne);
  rice2.getFunction(&firstRiceTwo, &secondRiceTwo, &thirdRiceTwo);
}

void runTasks(){
  startMove.run();
  goUpGetRice.run();
  turn.run();
  rice1.run();
  rice2.run();
}
void retry(){
  startMove.reset();
  goUpGetRice.reset();
  turn.reset();
  rice1.reset();
}
void start(){
  startMove.start();
}