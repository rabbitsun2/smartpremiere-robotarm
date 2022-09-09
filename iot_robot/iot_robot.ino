/*
 * Created Date: 2022-08-10 (Wed)
 * Author: Doyun Jung (정도윤) / rabbit.white@daum.net
 * Subject: Smart Premiere Robot Arm IoT
 * Filename: iot_robot.ino
 * Description:
 * 1. 로봇 기초 생성, 정도윤, 2022-08-10 (Wed)
 * 
 * 
 */
#include <Servo.h>
#include "robotArm.h"

const int SERVO_CNT = 6;
const int SERVO_BASE = 0;


// 서보모터 채널 정의
const int CH_ROBOT_BASE = 3;
const int CH_ROBOT_SHOULDER = 4;
const int CH_ROBOT_ELBOW = 5;
const int CH_ROBOT_WRIST = 7;
const int CH_ROBOT_GRIP = 8;
const int CH_ROBOT_GRIPPER = 9;

// 서보모터 초기 각도
const int CH_ROBOT_BASE_INIT_ANGLE = 0;
const int CH_ROBOT_SHOULDER_INIT_ANGLE = 0;
const int CH_ROBOT_ELBOW_INIT_ANGLE = 0;
const int CH_ROBOT_WRIST_INIT_ANGLE = 0;
const int CH_ROBOT_GRIP_INIT_ANGLE = 0;
const int CH_ROBOT_GRIPPER_INIT_ANGLE = 0;

// 로봇 팔
RobotArm robotArm(6);

// 서보모터 최대 각도 정의
const int CH_ROBOT_BASE_MAX_ANGLE = 360;
const int CH_ROBOT_SHOULDER_MAX_ANGLE = 360;
const int CH_ROBOT_ELBOW_MAX_ANGLE = 360;
const int CH_ROBOT_WRIST_MAX_ANGLE = 360;
const int CH_ROBOT_GRIP_MAX_ANGLE = 360;
const int CH_ROBOT_GRIPPER_MAX_ANGLE = 360;

char recvData;


void setup() {

  // 시리얼 포트 초기화
  Serial.setTimeout(100);
  Serial.begin(9600);
  while(!Serial){
    ;
  }

  // 모터 초기화
  init_motor();   

  // 환영 인사
  welcome();

}

void welcome(){
  
  Serial.println("---------------------");
  Serial.println("Welcome");
  Serial.println("Robot Arm");
  Serial.println("...");
  Serial.println("Create date:2022-08-23");
  Serial.println("......");
  Serial.println("---------------------");
  Serial.println("ver 0.1");
  Serial.println("---------------------");
  Serial.println("Author: Smart Soft");
}

void init_motor(){

  // 모터 핀 설정
  robotArm.attachMotor(0, CH_ROBOT_BASE);
  robotArm.attachMotor(1, CH_ROBOT_SHOULDER);
  robotArm.attachMotor(2, CH_ROBOT_ELBOW);
  robotArm.attachMotor(3, CH_ROBOT_WRIST);
  robotArm.attachMotor(4, CH_ROBOT_GRIP);
  robotArm.attachMotor(5, CH_ROBOT_GRIPPER);

  // 최소 각도
  robotArm.setMin_angle(0, 0);
  robotArm.setMin_angle(1, 0);
  robotArm.setMin_angle(2, 0);
  robotArm.setMin_angle(3, 0);
  robotArm.setMin_angle(4, 0);
  robotArm.setMin_angle(5, 0);

  // 최대 각도
  robotArm.setMax_angle(0, CH_ROBOT_BASE_MAX_ANGLE);
  robotArm.setMax_angle(1, CH_ROBOT_SHOULDER_MAX_ANGLE);
  robotArm.setMax_angle(2, CH_ROBOT_ELBOW_MAX_ANGLE);
  robotArm.setMax_angle(3, CH_ROBOT_WRIST_MAX_ANGLE);
  robotArm.setMax_angle(4, CH_ROBOT_GRIP_MAX_ANGLE);
  robotArm.setMax_angle(5, CH_ROBOT_GRIPPER_MAX_ANGLE);

  // 초기 각도
  robotArm.setInit_angle(0, 0);
  robotArm.setInit_angle(1, 0);
  robotArm.setInit_angle(2, 0);
  robotArm.setInit_angle(3, 0);
  robotArm.setInit_angle(4, 0);
  robotArm.setInit_angle(5, 0);


}

void system_boot_start(){

  // 로봇 6축 다리 경로
  robotArm.updateMotor(0, 90, 0);   // (찾음) 
  robotArm.updateMotor(1, 70, 1);   // (찾음) 
  robotArm.updateMotor(2, 45, 0);   // (찾음) 
  robotArm.updateMotor(4, 45, 0);   // (찾음) 
  robotArm.updateMotor(5, 90, 0);   // (찾음) 
  
  robotArm.updateMotor(5, 90, 1);   // (찾음) 
  robotArm.updateMotor(4, 45, 1);   // (찾음) 
  robotArm.updateMotor(1, 70, 0);   // (찾음) 
  robotArm.updateMotor(0, 90, 1);   // (찾음)
  
}

void system_robot_motion(int index){
  
  switch(index){

    case 0:
      //시스템 시작
      system_boot_start();

      break;

    // 1번 동작
    case 1: 
      // 로봇 6축 다리 경로
      robotArm.updateMotor(0, 180, 0);   // (찾음) 
      robotArm.updateMotor(1, 55, 1);   // (찾음) 
      
      robotArm.updateMotor(1, 55, 0);   // (찾음) 
      robotArm.updateMotor(0, 90, 1);   // (찾음)

      break;

    // 2번 동작
    case 2:
      // 로봇 6축 다리 경로
      robotArm.updateMotor(1, 55, 1);   // (찾음) 
      robotArm.updateMotor(2, 45, 0);   // (찾음) 
      robotArm.updateMotor(5, 90, 0);   // (찾음) 
      robotArm.updateMotor(5, 45, 1);   // (찾음) 
      robotArm.updateMotor(5, 45, 0);   // (찾음) 
      robotArm.updateMotor(5, 90, 1);   // (찾음) 
      robotArm.updateMotor(1, 55, 0);   // (찾음) 
      robotArm.updateMotor(0, 90, 1);   // (찾음)
      
      break;

    // 3번 동작
    case 3:
      // 로봇 6축 다리 경로
      robotArm.updateMotor(0, 90, 0);   // (찾음)
      robotArm.updateMotor(1, 55, 1);   // (찾음)
      robotArm.updateMotor(4, 45, 0);   // (찾음)
      robotArm.updateMotor(5, 90, 0);   // (찾음)
    
      robotArm.updateMotor(5, 90, 1);   // (찾음)
      robotArm.updateMotor(4, 45, 1);   // (찾음)
      robotArm.updateMotor(1, 55, 0);   // (찾음)
      robotArm.updateMotor(0, 90, 1);   // (찾음)
  
      break;

    // 4번 동작
    case 4:      
      // 로봇 6축 다리 경로
      robotArm.updateMotor(1, 75, 1);   // (찾음)
      robotArm.updateMotor(3, 45, 0);   // (찾음)
      robotArm.updateMotor(5, 90, 0);   // (찾음)
    
      robotArm.updateMotor(5, 90, 1);   // (찾음)
      robotArm.updateMotor(4, 45, 1);   // (찾음)
      robotArm.updateMotor(1, 75, 0);   // (찾음)
      robotArm.updateMotor(0, 90, 1);   // (찾음)

      break;

    // 5번 동작
    case 5:
      // 로봇 6축 다리 경로
      robotArm.updateMotor(0, 90, 0);   // (찾음)
      robotArm.updateMotor(1, 45, 0);   // (찾음)
      robotArm.updateMotor(2, 90, 0);   // (찾음)
      robotArm.updateMotor(3, 45, 0);   // (찾음)
    
      robotArm.updateMotor(3, 45, 1);   // (찾음)
      robotArm.updateMotor(2, 90, 1);   // (찾음)
      robotArm.updateMotor(1, 45, 1);   // (찾음)
      robotArm.updateMotor(0, 90, 1);   // (찾음)
      
      break;

    // 6번 동작
    case 6:
      // 로봇 6축 다리 경로
      robotArm.updateMotor(0, 180, 0);   // (찾음)
      robotArm.updateMotor(0, 90, 1);   // (찾음)
      robotArm.updateMotor(1, 45, 1);   // (찾음)
      robotArm.updateMotor(2, 90, 0);   // (찾음)
      
      robotArm.updateMotor(2, 90, 1);   // (찾음)
      robotArm.updateMotor(1, 45, 1);   // (찾음)
      robotArm.updateMotor(0, 90, 1);   // (찾음)
      robotArm.updateMotor(1, 75, 0);   // (찾음)
  
      break;
     
  }
  
}

void loop(){
  
  String strVal;

  if( Serial.available() ){
  
    strVal = Serial.readStringUntil('\n');
    Serial.println(strVal);
    
    if ( strVal == "0" ){     
      // 1번 동작
      Serial.println("1-0/robot-motion-start");
      system_robot_motion(0);
    }
    else if ( strVal == "1" ){     
      // 1번 동작
      Serial.println("1-1/robot-motion-action");
      system_robot_motion(1);
    }
    else if ( strVal == "2" ){
      // 2번 동작
      Serial.println("1-2/robot-motion-action");
      system_robot_motion(2);
    }
    else if ( strVal == "3" ){
      // 3번 동작
      Serial.println("1-3/robot-motion-action");
      system_robot_motion(3);
    }
    else if ( strVal == "4" ){
      // 4번 동작
      Serial.println("1-4/robot-motion-action");
      system_robot_motion(4);
    }
    else if ( strVal == "5" ){
      // 5번 동작
      Serial.println("1-5/robot-motion-action");
      system_robot_motion(5);
    }
    else if ( strVal == "6" ){
      // 6번 동작
      Serial.println("1-6/robot-motion-action");
      system_robot_motion(6);
    }
    else if ( strVal == "7" ){
      Serial.println("2-motor-0/45deg/forward");
      robotArm.updateMotor(0, 45, 0);
    }
    else if ( strVal == "8" ){
      Serial.println("2-motor-0/45deg/reverse");
      robotArm.updateMotor(0, 45, 1);
    }
    else if ( strVal == "9" ){
      Serial.println("2-motor-0/90deg/forward");
      robotArm.updateMotor(0, 90, 0);
    }
    else if ( strVal == "10" ){
      Serial.println("2-motor-0/90deg/reverse");
      robotArm.updateMotor(0, 90, 1);
    }
    else if ( strVal == "11" ){
      Serial.println("2-motor-4/45deg/forward");
      robotArm.updateMotor(4, 45, 0);
    }
    else if ( strVal == "12" ){
      Serial.println("2-motor-4/45deg/reverse");
      robotArm.updateMotor(4, 45, 1);
    }
    else if ( strVal == "13" ){
      Serial.println("2-motor-5/45deg/forward");
      robotArm.updateMotor(5, 45, 0);
    }
    else if ( strVal == "14" ){
      Serial.println("2-motor-5/45deg/reverse");
      robotArm.updateMotor(5, 45, 1);
    }
    else if ( strVal == "15" ){
      Serial.println("2-motor-5/45deg/reverse");
      robotArm.updateMotor(0, 180, 1);
    }
    
  }

}
