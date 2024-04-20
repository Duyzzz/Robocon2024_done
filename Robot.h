#define m1 3  // pwm 1
#define m2 4
#define m3 5 
#define m4 6

#define d1 52
#define d2 53
#define d3 51
#define d4 49
#define d5 31
#define d6 29
#define d7 27
#define d8 25

#define ena 18
#define enb 22

#define m51 24 
#define m52 26 

#define pwm5 7
#define pwm6 8
#define pwm7 9
#define pwm8 10
#define pwm9 44
#define pwm10 2
// Laxer blynk
#define lazer 42


// Động cơ thường 
#define m11 24
#define m12 26

#define m21 28
#define m22 30

#define pwm_m3 13
#define pwm_m2 12
#define pwm_m1 11

// Cảm biến nhận bóng 
#define cbb !(1 & digitalRead(47))


uint32_t  fourBytes; 
long numof_rotary = 0; 
bool find_high_f = true; 
double  dv = 0.377;
double distance = 0 ;  

int angleg = 0; 
char robot = 'z';
int angle = 0; 

// Thông số chung robot 
int v_bot = 0; 
int angle_bot = 0; 
uint8_t stt_bot = 0; // 1up, 2 left, 3 right, 4 down. 

// PS3
String command= ""; 
bool enable = true ; 
uint32_t fourBytes_a = 0;
uint32_t bt_in = 0;
uint8_t analogButton = 0;

// ========================  PID chạy thẳng ========================  //

// ========================  Quay góc ========================  //
int v11 = 0; 
int v22 = 0; 
double kp = 2.5, ki = 0.02, kd = 0.01;
int error, last_error, last_error1; 
int output; 
int T = 1;
int T1 = 200; 
int set_point = 0;
unsigned long last_time = 0;

// trang thai quay goc 
bool tt_quay = false; 
// ========================  Line ========================  //
int ab6 = 0, ab7 = 0, ab8 = 0, ab9 = 0, ab10 = 0, ab11 = 0;
int aa6 = 0, aa7 = 0, aa8 = 0, aa9 = 0, aa10 = 0, aa11 = 0;
int a6 = 730, a7 = 840, a8 = 790, a9 = 705, a10 = 840, a11 = 860;
// ========================  Di chuyển cơ bản ========================  //
unsigned long timea; 
unsigned long timeb; 
unsigned long timec; 

int a = 10; 
bool soft_state = true; 
// sick
int solan_sick2 = 0;  
int solan_sick22 = 0;  
double one_dist = 10000/1024; 

// ========================  Các hàm  ========================  //
void balance(int set_angle, int v, int ac);
void rota_r(int v);
void stop();
void rota_l(int va);
void right(int va);
void left(int va);
void up(int va);
void down(int va);
int soft_start(int speedv);
int compass();
int eror_line();
void rotare( int set_angle);
int sick1();
void display();

int h3h =1; 
/* for mega 2560 
// cách chân pwm 
#define pwm5 7
#define pwm6 8
#define pwm7 9
#define pwm8 10
#define pwm9 44 // dc1
#define pwm10 2
#define pwm11 13
#define pwm12 12
#define pwm13 11
 
// các chân điều khiển động cơ động cơ không PID 
// pwm 9 trở đi tương đương số thứu tự động cơ 1  trở đi 
#define m11 40 
#define m12 42
#define m21 36
#define m22 38 
#define m31 32
#define m32 34
#define m41 28
#define m42 30 
#define m51 24 
#define m52 26 

//uart 
#define tx1 19
#define rx1 18 

#define tx2 16
#define rx2 17 

#define tx3 14
#define rx3 15

// i2c 

#define sda 20 
#define scl 21


// ENcoder 
#define int1 18  /// int 5
#define int2 19  /// int 4
#define en1 22
#define en2 23

// Cam biến có cách ly 
#define cb13 A12
#define cb14 A13
#define cb15 A14
#define cb16 A15

// Cảm biến vào 5V
#define cb1 33
#define cb2 35 
#define cb3 37
#define cb4 39 
#define cb5 41
#define cb6 43
#define cb7 45
#define cb8 47

// Công tắc hành trình ( cảm biến 3 chân bên cạnh )
#define ct1 A0
#define ct2 A1
#define ct3 A2
#define ct4 A3

// ADC 3.81
#define adc6 A6
#define adc7 A7
#define adc8 A8
#define adc9 A9
#define adc10 A10
#define adc11 A11

// ADC 2.54 từ A4 -> A7 

*/

