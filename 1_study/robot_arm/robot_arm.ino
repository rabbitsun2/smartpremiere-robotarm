/*
 * Created Date: 2022-08-10 (Wed)
 * Author: Doyun Jung (정도윤) / rabbit.white@daum.net
 * Subject: Smart Logistics Robot Arm IoT
 * Filename: robot_arm.ino
 * Description:
 * 1. 로봇 기초 생성, 정도윤, 2022-08-10 (Wed)
 * 2. HCPCA9685 16채널 서보모터 드라이버 지원, 정도윤, 2022-08-12 (Fri)
 */
 
#include "HCPCA9685.h"
#include "robot_arm.h"
#include "robot_control.h"

/* I2C slave address for the device/module. For the HCMODU0097 the default I2C address
   is 0x40 */
#define  I2CAdd 0x40

/* Create an instance of the library */
HCPCA9685 hcpca9685(I2CAdd);


// 서보모터 채널 정의
const int CH_ROBOT_BASE = 4;
const int CH_ROBOT_SHOULDER = 5;
const int CH_ROBOT_ELBOW = 6;
const int CH_ROBOT_WRIST = 7;
const int CH_ROBOT_GRIP = 8;
const int CH_ROBOT_GRIPPER = 9;

const int RANGE_START_NUM = 1;
const int RANGE_END_NUM = 13;


RobotArm robotArm;

int ardu_status;

int deg1;   // 1번 모터 (Base / 기초)
int deg2;   // 2번 모터 (Shoulder / 어깨)
int deg3;   // 3번 모터 (Elbow / 팔꿈치)
int deg4;   // 4번 모터 (Wrist / 손목)
int deg5;   // 5번 모터 (Grip / 손잡이)
int deg6;   // 6번 모터 (Gripper / 손가락)

void setup() {

  // 시리얼 포트 초기화
  Serial.setTimeout(100);
  Serial.begin(9600);
  while(!Serial){
    ;
  }
    
  // 모터 초기화
  init_motor();

  // 모터 각도 초기화
  init_motor_degree();
  
}

void init_motor(){

  unsigned int pos;
  
  /* Initialise the library and set it to 'servo mode' */ 
  hcpca9685.Init(SERVO_MODE);

  /* Wake the device up */
  hcpca9685.Sleep(false);

  pos = 360;   // 위치값의 초기값을 360으로 설정함.

  // 서보모터 기본 위치 정의
  hcpca9685.Servo(CH_ROBOT_BASE, pos);        // 기초
  hcpca9685.Servo(CH_ROBOT_SHOULDER, pos);    // 어깨
  hcpca9685.Servo(CH_ROBOT_ELBOW, pos);       // 팔꿈치
  hcpca9685.Servo(CH_ROBOT_WRIST, pos);       // 손목
  hcpca9685.Servo(CH_ROBOT_GRIP, pos);        // 손잡이
  hcpca9685.Servo(CH_ROBOT_GRIPPER, pos);     // 손가락
  
}

void init_motor_degree(){
  
  deg1 = 0;
  deg2 = 0;
  deg3 = 0;
  deg4 = 0;
  deg5 = 0;
  deg6 = 0;
  
}

void loop() {

  String recvData = "";
  String splitData = "";
  String tmpData = "";
  String tmpData2 = "";
  double tmpFloat;
  int tmpInt;

  // 시리얼 포트 사용가능 여부
  if(Serial.available()){

    recvData = Serial.readStringUntil('\r');
    
    if ( recvData.compareTo("1") == 0 ){
      // 모터(Base) 기초 - Up
      ardu_status = 1;
    }
    else if ( recvData.compareTo("2") == 0 ){
      // 모터(Base) 기초 - Down
      ardu_status = 2;
    }
    else if ( recvData.compareTo("3") == 0 ){
      // 모터(Shoulder) 어깨 - Up
      ardu_status = 3;
    }
    else if ( recvData.compareTo("4") == 0 ){
      // 모터(Shoulder) 어깨 - Down
      ardu_status = 4;
    }
    else if ( recvData.compareTo("5") == 0 ){
      // 모터(Elbow) 팔꿈치 - Up
      ardu_status = 5;
    }
    else if ( recvData.compareTo("6") == 0 ){
      // 모터(Elbow) 팔꿈치 - Down
      ardu_status = 6;
    }
    else if ( recvData.compareTo("7") == 0 ){
      // 모터(Wrist) 손목 - Up
      ardu_status = 7;
    }
    else if ( recvData.compareTo("8") == 0 ){
      // 모터(Wrist) 손목 - Down
      ardu_status = 8;
    }
    else if ( recvData.compareTo("9") == 0 ){
      // 모터(Grip) 손잡이 - Up
      ardu_status = 9;
    }
    else if ( recvData.compareTo("10") == 0 ){
      // 모터(Grip) 손잡이 - Down
      ardu_status = 10;
    }
    else if ( recvData.compareTo("11") == 0 ){
      // 모터(Gripper) 손가락 - Up
      ardu_status = 11;
    }
    else if ( recvData.compareTo("12") == 0 ){
      // 모터(Gripper) 손가락 - Down
      ardu_status = 12;
    }
    else{
      // 받은 데이터 값 임시 변수 가져오기
      tmpData = recvData;

      // 로봇팔 설정
      if (tmpData.indexOf("13") != -1){

        ardu_status = 13;
        
        // X축 입력
        tmpData = tmpData.substring(tmpData.indexOf(';') + 1, tmpData.indexOf(','));
        robotArm.setX(tmpData.toFloat());

        // Y축 입력
        tmpData = recvData;
        tmpData = tmpData.substring(tmpData.indexOf(',') + 1, tmpData.indexOf('/'));
        robotArm.setY(tmpData.toFloat());

        // Z축 입력
        tmpData = recvData;
        tmpData = tmpData.substring(tmpData.indexOf('/') + 1, tmpData.indexOf('<'));
        robotArm.setZ(tmpData.toFloat());

        // Grip_Degree 입력
        tmpData = recvData;
        tmpData = tmpData.substring(tmpData.indexOf('<') + 1, tmpData.indexOf('>'));
        robotArm.setGripDegree(tmpData.toFloat());

        // Gripper 입력
        tmpData = recvData;
        tmpData = tmpData.substring(tmpData.indexOf('>') + 1, tmpData.indexOf('('));
        robotArm.setGripper(tmpData.toInt());

        // De 입력
        tmpData = recvData;
        tmpData = tmpData.substring(tmpData.indexOf('(') + 1, tmpData.indexOf(')'));
        robotArm.setDe(tmpData.toInt());

      }
      // 유효하지 않은 데이터 값
      else{
        ardu_status = -1;
      }
      
    }
    
  }

  // 프로그램 실행
  control_servo(ardu_status);
  delay(100);
  
}

void control_servo(int status){

  // 1번 모터 Up (Base / 기초)
  if ( status == 1 ){
    
    if ( validateDegree(deg1 + 1) ){
      deg1++;
      Serial.println(deg1);
      hcpca9685.Servo(CH_ROBOT_BASE, deg1);        // 기초
    }
    
  }
  // 1번 모터 Down (Base / 기초)
  else if ( status == 2 ){
    
    if ( validateDegree(deg1 - 1) ){
      deg1--;
      Serial.println(deg1);
      hcpca9685.Servo(CH_ROBOT_BASE, deg1);        // 기초
    }
    
  }
  // 2번 모터 Up (Shoulder / 어깨)
  else if ( status == 3 ){
    
    if ( validateDegree(deg2 + 1) ){
      deg2++;
      Serial.println(deg2);
      hcpca9685.Servo(CH_ROBOT_SHOULDER, deg2);    // 어깨
    }
    
  }
  // 2번 모터 Down (Shoulder / 어깨)
  else if ( status == 4 ){
    
    if ( validateDegree(deg2 - 1) ){
      deg2--;
      Serial.println(deg2);
      hcpca9685.Servo(CH_ROBOT_SHOULDER, deg2);    // 어깨
    }
    
  }
  // 3번 모터 Up (Elbow / 팔꿈치)
  else if ( status == 5 ){
    
    if ( validateDegree(deg3 + 1) ){
      deg3++;
      Serial.println(deg3);
      hcpca9685.Servo(CH_ROBOT_ELBOW, deg3);       // 팔꿈치
    }
    
  }
  // 3번 모터 Down (Elbow / 팔꿈치)
  else if ( status == 6 ){
    
    if ( validateDegree(deg3 - 1) ){
      deg3--;
      Serial.println(deg3);
      hcpca9685.Servo(CH_ROBOT_ELBOW, deg3);       // 팔꿈치
    }
    
  }
  // 4번 모터 Up (Wrist / 손목)
  else if ( status == 7 ){
    
    if ( validateDegree(deg4 + 1) ){
      deg4++;
      Serial.println(deg4);
      hcpca9685.Servo(CH_ROBOT_WRIST, deg4);       // 손목
    }
    
  }
  // 4번 모터 Down (Wrist / 손목)
  else if ( status == 8 ){
    
    if ( validateDegree(deg4 - 1) ){
      deg4--;
      Serial.println(deg4);
      hcpca9685.Servo(CH_ROBOT_WRIST, deg4);       // 손목
    }
    
  }
  // 5번 모터 Up (Grip / 손잡이)
  else if ( status == 9 ){
    
    if ( validateDegree(deg5 + 1) ){
      deg5++;
      Serial.println(deg5);
      hcpca9685.Servo(CH_ROBOT_GRIP, deg5);        // 손잡이
    }
    
  }
  // 5번 모터 Down (Grip / 손잡이)
  else if ( status == 10 ){
    
    if ( validateDegree(deg5 - 1) ){
      deg5--;
      Serial.println(deg5);
      hcpca9685.Servo(CH_ROBOT_GRIP, deg5);        // 손잡이
    }
    
  }
  // 6번 모터 Up (Gripper / 손가락)
  else if ( status == 11 ){
    
    if ( validateDegree(deg6 + 1) ){
      deg6++;
      Serial.println(deg6);
      hcpca9685.Servo(CH_ROBOT_GRIPPER, deg6);     // 손가락
    }
    
  }
  // 6번 모터 Down (Gripper / 손가락)
  else if ( status == 12 ){
    
    if ( validateDegree(deg6 - 1) ){
      deg6--;
      Serial.println(deg6);
      hcpca9685.Servo(CH_ROBOT_GRIPPER, deg6);     // 손가락
    }
    
  }
  // 로봇 역학
  else if ( status == 13 ){

    // 로봇 인체 계산
    robotArm.calculate();

    // 1번
    hcpca9685.Servo(CH_ROBOT_BASE, degrees( robotArm.getBaseAngle() ) );            // 기초
    Serial.println( degrees( robotArm.getBaseAngle() ) );

    // 2번
    hcpca9685.Servo(CH_ROBOT_SHOULDER, degrees( robotArm.getShoulderAngle() ));     // 어깨
    Serial.println( degrees( robotArm.getShoulderAngle() ) );

    // 3번
    hcpca9685.Servo(CH_ROBOT_ELBOW, degrees( robotArm.getElbowAngle() ));           // 팔꿈치
    Serial.println("3번");
    Serial.println( robotArm.getElbowAngle() );
    Serial.println( degrees( robotArm.getElbowAngle() ) );

    // 4번
    hcpca9685.Servo(CH_ROBOT_WRIST, degrees( robotArm.getWristAngle() ) );          // 손목
    Serial.println("4번");
    Serial.println( robotArm.getWristAngle() );

    // 5번
    hcpca9685.Servo(CH_ROBOT_GRIP, robotArm.getGripDegree() );                      // 손잡이
    Serial.println( robotArm.getGripDegree() );

    // 6번
    hcpca9685.Servo(CH_ROBOT_GRIPPER, robotArm.getGripper() );                      // 손가락
    Serial.println( robotArm.getGripper() );
    
  }

  // 유효 범위 체크
  if ( validateRangeNum( status ) ){
     ardu_status = 0;
  }
 
}

bool validateDegree(int deg){

  if ( deg >= 0 && deg <= 360 ){
    return true;
  }else{
    return false;
  }
  
}

bool validateRangeNum(int status){
  
  if ( status >= RANGE_START_NUM && 
      status <= RANGE_END_NUM ){
    return true;
  }else{
    return false;
  }
  
}
