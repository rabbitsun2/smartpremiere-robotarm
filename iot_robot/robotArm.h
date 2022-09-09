/*
 * Created Date: 2022-08-10 (Wed)
 * Author: Doyun Jung (정도윤) / rabbit.white@daum.net
 * Subject: Smart Premiere Robot Arm IoT
 * Filename: robotArm.h
 * Description:
 * 1. 로봇 기초 생성, 정도윤, 2022-08-10 (Wed)
 * 2. 로봇 각도(정방향) 조정, 정도윤, 2022-08-23 (Tue)
 * 3. 로봇 각도(역방향) 조정, 정도윤, 2022-08-29 (Tue)
 * 
 */
#ifndef ROBOT_ARM_H_
#define ROBOT_ARM_H_

class RobotArm{

  int axis;                     // 축 크기
  Servo* servo;                 // the servo

  const int adj_angle1 = 18;     // 모터 조정값
  const int adj_angle2 = 43;     // 모터 조정값

  int* pin;                     // 핀
  int* current_pos;             // current servo position 
  int* prev_pos;                // prev servo position
  int* init_angle;
  int* min_angle;
  int* max_angle;
  
public: 
  RobotArm(int axis)
  {
    this->setAxis(axis);
    servo = new Servo[axis];
    pin = new int[axis];
    current_pos = new int[axis];
    prev_pos = new int[axis];
    init_angle = new int[axis];
    min_angle = new int[axis];
    max_angle = new int[axis];
  }

  void setAxis(int axis){
    this->axis = axis;
  }

  void setMin_angle(int index, int angle){
    this->min_angle[index] = angle;
  }

  void setMax_angle(int index, int angle){
    this->max_angle[index] = angle;
  }
  
  void attachMotor(int index, int pin){
    this->pin[index] = pin;
    servo[index].attach(pin);
  }

  void setInit_angle(int index, int angle){
    this->init_angle[index] = angle;
    this->current_pos[index] = angle;
    this->prev_pos[index] = angle;
    servo[index].write( angle );
    servo[index].detach();
  }
  
  void detachMotor(int index){
    servo[index].detach();
  }
  
  void updateMotor(int index, int angle, int direction = 1){

    int tmp_angle = 0;
    //int adj_angle = 38;
    
    servo[index].attach( pin[index] );

    current_pos[index] = servo[index].read();
    
    // 왼쪽
    if ( direction == 1 ){

      // 초기 시작일 때 버그 개선
      if ( current_pos[index] == 0 ){
        tmp_angle = max_angle[index] - 55 - angle;
        servo[index].write( tmp_angle - 30 );
      }
      
      if ( angle <= 30 ){
        tmp_angle = max_angle[index] - 60 - angle;
        delay(230);                                   // 지연값(모터 속도와 시간관계 조절)
      }
      else if ( angle <= 45 ){
        tmp_angle = max_angle[index] - 45 - angle;
        delay(250);                                   // 지연값(모터 속도와 시간관계 조절)
      }
      else if ( angle <= 60 ){
        tmp_angle = max_angle[index] - 35 - angle;
        delay(310);                                   // 지연값(모터 속도와 시간관계 조절)
      }
      else if ( angle <= 90 ){
        tmp_angle = max_angle[index] - 35 - angle;
        delay(455);                                   // 지연값(모터 속도와 시간관계 조절)
      }
      else if ( angle <= 110 ){
        tmp_angle = max_angle[index] - 35 - angle;
        delay(465);                                   // 지연값(모터 속도와 시간관계 조절)
      }
      else if ( angle <= 135 ){
        tmp_angle = max_angle[index] - 35 - angle;
        delay(465);                                   // 지연값(모터 속도와 시간관계 조절)
      }
      else if ( angle <= 150 ){
        tmp_angle = max_angle[index] - 35 - angle;
        delay(695);                                   // 지연값(모터 속도와 시간관계 조절)
      }
      else if ( angle <= 165 ){
        tmp_angle = max_angle[index] - 35 - angle;
        delay(1150);                                   // 지연값(모터 속도와 시간관계 조절)
      }
      else if ( angle >= 180 ){
        tmp_angle = max_angle[index] - 20 - angle;
        delay(850);                                   // 지연값(모터 속도와 시간관계 조절)
      }
      
      servo[index].write( tmp_angle );              // tell servo to go to position in variable 'pos'

      prev_pos[index] = tmp_angle;  

    }
    // 오른쪽
    else if ( direction == 0 ){
      
      servo[index].write( prev_pos[index] );              // tell servo to go to position in variable 'pos'
      delay(20);                       // waits 15 ms for the servo to reach the position

      if ( angle <= 45 ){
        tmp_angle = angle - 60;
        servo[index].write( tmp_angle );
        delay(180);       
      }else if ( angle <= 75 ){
        tmp_angle = angle - adj_angle2;
        servo[index].write( tmp_angle );
        delay(320);
      }else if ( angle <= 90 ){
        tmp_angle = angle - adj_angle2;
        servo[index].write( tmp_angle );
        delay(410);
      }else if ( angle <= 130 ){
        tmp_angle = angle - 90;
        servo[index].write( tmp_angle );
        delay(530);
      }else if ( angle <= 150 ){
        tmp_angle = angle - 90;
        servo[index].write( tmp_angle );
        delay(800);
      }else if ( angle <= 165 ){
        tmp_angle = angle - 110;
        servo[index].write( tmp_angle );
        delay(790);
      }else if ( angle >= 180 ){
        tmp_angle = angle - 120;
        servo[index].write( tmp_angle );
        delay(990);
      }
      
      prev_pos[index] = angle;

    }

    Serial.print("[index]:");
    Serial.print(index);

    
    Serial.print(" / angle:");
    Serial.print(angle);
    Serial.print(" / tmp_angle:");
    Serial.println(tmp_angle);

    servo[index].detach();
    
  }
  
};


#endif
