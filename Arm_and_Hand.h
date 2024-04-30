// Điều khiển khí nén 
#define k1 13
#define k2 32 // 
#define k3 34
#define k4 2
#define k5 36
#define k6 38


#define arm_left 32
#define arm_right 36
#define hand_left 34
#define hand_right 38

// Cam biến có cách ly 
#define cb13 A12  // ss_lt
#define cb14 A13  // ss_ld
#define cb15 A14  // ss_rd 
#define cb16 A15  // ss_rt

#define ss_ld !(1 & digitalRead(cb14))
#define ss_lt !(1 & digitalRead(cb13))
#define ss_rd !(1 & digitalRead(cb15))
#define ss_rt !(1 & digitalRead(cb16))
// Công tắc hành trình 
#define ct3 A2
#define ct4 A0

#define ss_arm_r !(1 & digitalRead(ct4))
#define ss_arm_l !(1 & digitalRead(ct3))

class arm_hand{
  private:
    uint8_t pin; 
    bool act; // quyết định trạng thái action là 0 hay là 1 ( đảo đấy )
  public: 
    arm_hand(int pinn, bool actt):pin(pinn),act(actt){}
    void config(int type){
      pinMode(pin, type);
    }
    void action(){
      digitalWrite(pin,act); 
    }
    void stop (){
      digitalWrite(pin, !act); 
    }
}; 

