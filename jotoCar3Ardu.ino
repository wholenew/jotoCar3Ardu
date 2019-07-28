#include <Servo.h>
#include <Wire.h>

#define R_STEP 11
#define R_DIRECTION 5
//#define R_IN2 6
#define L_STEP 10
#define L_DIRECTION 2
//#define L_IN2 4
//#define STEERING_PWM 9


int SLAVE_ADDRESS = 0x04;   //I2Cのアドレス『0x04』
Servo servo;
byte value=0;
int r_pwm = 125;
int l_pwm = 125;
//int steering = 0;
int stopFlag=0;

void setup() {
   Serial.begin(9600);
   //I2C接続を開始する 
   Wire.begin(SLAVE_ADDRESS);
  
   Wire.onReceive(ReceiveMassage); 
  
    //I2Cでリクエスト受信したときに呼び出す関数を登録する 
   Wire.onRequest(RequestMassage);
   
   pinMode(R_DIRECTION, OUTPUT);
   pinMode(L_DIRECTION, OUTPUT);
//   pinMode(R_IN2, OUTPUT);
//   pinMode(L_IN2, OUTPUT);
   pinMode(R_STEP, OUTPUT);
   pinMode(L_STEP, OUTPUT); 
//   pinMode(STEERING_PWM, OUTPUT); 
   
//   servo.attach(STEERING_PWM);
//   servo.write(28);//右2中央28左53
   delay(3000);
}

void loop() {
    switch(value){
      case 'f':
//        steering = 28; //右2中央28左53
        l_pwm = 125; //大きいほど強くなる
        r_pwm = 125;
  
        //左正転
        digitalWrite(L_DIRECTION, HIGH);
//        digitalWrite(L_IN2, LOW);
//        digitalWrite(L_PWM, HIGH);
        analogWrite(L_STEP, l_pwm);
        //右正転
        digitalWrite(R_DIRECTION, HIGH);
//        digitalWrite(R_IN2, LOW);
//        digitalWrite(R_PWM, HIGH);
        analogWrite(R_STEP, r_pwm);
        break;
        
      case 'b':
//        steering = 28; //右2中央28左53
        l_pwm = 125; //小さいほど強くなる
        r_pwm = 125;
  
        //左正転
        digitalWrite(L_DIRECTION, LOW);
//        digitalWrite(L_IN2, HIGH);
//        digitalWrite(L_PWM, LOW);
        analogWrite(L_STEP, l_pwm);
        //右正転
        digitalWrite(R_DIRECTION, LOW);
//        digitalWrite(R_IN2, HIGH);
//        digitalWrite(R_PWM, LOW);
        analogWrite(R_STEP, r_pwm);

        break;
        
      case 'r':
        l_pwm = 125;
        r_pwm = 125; //小さいほど強くなる

        //左正転
        digitalWrite(L_DIRECTION, HIGH);
//        digitalWrite(L_IN2, LOW);
//        digitalWrite(L_PWM, HIGH);
        analogWrite(L_STEP, l_pwm);
        //右正転
        digitalWrite(R_DIRECTION, LOW);
//        digitalWrite(R_IN2, LOW);
//        digitalWrite(R_PWM, HIGH);
        analogWrite(R_STEP, r_pwm);
        break;
        
      case 'l':
        l_pwm = 0; //小さいほど強くなる
        r_pwm = 0;

        //左正転
        digitalWrite(L_DIRECTION, LOW);
//        digitalWrite(L_IN2, LOW);
//        digitalWrite(L_PWM, HIGH);
        analogWrite(L_STEP, l_pwm);
        //右正転
        digitalWrite(R_DIRECTION, HIGH);
//        digitalWrite(R_IN2, LOW);
//        digitalWrite(R_PWM, HIGH);
        analogWrite(R_STEP, r_pwm);
        break;

      case 's':
        brake();
    }
}

// ブレーキ
void brake() {
  l_pwm = 0; //小さいほど強くなる
  r_pwm = 0;
  digitalWrite(L_STEP, LOW);
  digitalWrite(R_STEP, LOW);
//  analogWrite(L_STEP, l_pwm);
//  analogWrite(L_STEP, r_pwm);
}

void ReceiveMassage(int n){
  char cmd = Wire.read();
  Serial.println(cmd);
  value=cmd;
}

void RequestMassage(){
//  Wire.write("j");            
}
