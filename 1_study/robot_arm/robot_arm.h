/*
 * Created Date: 2022-08-10 (Wed)
 * Author: Doyun Jung (정도윤) / rabbit.white@daum.net
 * Subject: Smart Logistics Robot Arm IoT
 * Filename: robot_arm.h
 * Description:
 * 1. 로봇 기초 생성, 정도윤, 2022-08-10 (Wed)
 * 
 */
#ifndef ROBOT_ARM_H_
#define ROBOT_ARM_H_

class RobotArm{

  public:
    void setArm(double x, double y, double z, double grip_degree, int _gripper, int de);
    double getX();
    double getY();
    double getZ();
    double getGripDegree();
    int getGripper();
    int getDe();
    
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setGripDegree(double grip_degree);
    void setGripper(int gripper);
    void setDe(int de);

    void calculate();

    double getBaseAngle();
    double getShoulderAngle();
    double getElbowAngle();
    double getWristAngle();
    
    void setBaseAngle(double base_angle);
    void setShoulderAngle(double shoulder_angle);
    void setElbowAngle(double elbow_angle);
    void setWristAngle(double wrist_angle);
    
  private:
    double x;
    double y;
    double z;
    double grip_degree;
    int _gripper;
    int de;

    double base_angle;
    double shoulder_angle;
    double elbow_angle;
    double wrist_angle;
    
};

void RobotArm::setArm(double x, double y, double z, double grip_degree, int _gripper, int de){
  this->setX(x);
  this->setY(y);
  this->setZ(z);
  this->setGripDegree(grip_degree);
  this->setGripper(_gripper);
  this->setDe(de);
}

double RobotArm::getX(){
  return this->x;
}

double RobotArm::getY(){
  return this->y;
}

double RobotArm::getZ(){
  return this->z;
}

double RobotArm::getGripDegree(){
  return this->grip_degree;
}

int RobotArm::getGripper(){
  return this->_gripper;
}

int RobotArm::getDe(){
  return this->de;
}

void RobotArm::setX(double x){
  this->x = x;
}

void RobotArm::setY(double y){
  this->y = y;
}

void RobotArm::setZ(double z){
  this->z = z;
}

void RobotArm::setGripDegree(double grip_degree){
  this->grip_degree = grip_degree;
}

void RobotArm::setGripper(int _gripper){
  this->_gripper = _gripper;
}

void RobotArm::setDe(int de){
  this->de = de;
}

void RobotArm::calculate(){

  // 사용자 입력 값
  double usr_x = this->getX();
  double usr_y = this->getY();
  double usr_z = this->getZ();
  double usr_grip_degree = this->getGripDegree();
  int usr_gripper = this->getGripper();
  int usr_de = this->getDe();

  double USR_PI = 3.14159;
  double BASE_HEIGHT = 100.0;
  double SHOULDER_LENGTH = 120.0;
  double ARM_LENGTH = 120.0;
  double GRIP_LENGTH = 140.0;

  double BASE_ANGLE = atan(usr_y / usr_x);                                   // 몸통 각도(Base Degree) = atan(Y/X)
  double R = sqrt( (usr_x * usr_x) + ( usr_y * usr_y ) );                    // 로봇의 반경(R) = sqrt(X^2 + Y^2)
  double GRIP_ANGLE = radians(usr_grip_degree);
  double RSIN = sin(GRIP_ANGLE) * GRIP_LENGTH;
  double R1 = R - RSIN;                                                      // R` = R - (sin(손 각도) * 손목 길이)

  double ZCOS = cos(GRIP_ANGLE) * GRIP_LENGTH;
  double Z1 = usr_z - BASE_HEIGHT + (ZCOS * GRIP_LENGTH);                    // Z` = Z - 몸통 높이 + (cos(손 각도) * 손목길이)

  double A = sqrt(( usr_z * usr_z ) * (R * R)) / 2;                          // A = sqrt(Z`^2 * R`^2) / 2
  
  double ELBOW_ANGLE = asin(ARM_LENGTH / A) * 2;                             // 팔 각도 = asin(A / 팔 길이) * 2
  double SHOULDER_ANGLE = atan2(Z1, R1) + ((USR_PI - ELBOW_ANGLE) / 2);      // 어깨 각도 = atan2(Z` / R`) + ((PI - 팔 각도) / 2)
  double WRIST_ANGLE = USR_PI + GRIP_ANGLE - SHOULDER_ANGLE - ELBOW_ANGLE;   // 손목 각도 = PI + 손 각도 - 어깨 각도 - 팔 각도

  
  this->setBaseAngle(BASE_ANGLE);
  this->setShoulderAngle(SHOULDER_ANGLE);
  this->setElbowAngle(ELBOW_ANGLE);
  this->setWristAngle(WRIST_ANGLE);
  
}

double RobotArm::getBaseAngle(){
  return this->base_angle;
}

double RobotArm::getShoulderAngle(){
  return this->shoulder_angle;
}

double RobotArm::getElbowAngle(){
  return this->elbow_angle;
}

double RobotArm::getWristAngle(){
  return this->wrist_angle;
}

void RobotArm::setBaseAngle(double base_angle){
  this->base_angle = base_angle;
}

void RobotArm::setShoulderAngle(double shoulder_angle){
  this->shoulder_angle = shoulder_angle;
}

void RobotArm::setElbowAngle(double elbow_angle){
  this->elbow_angle = elbow_angle;
}

void RobotArm::setWristAngle(double wrist_angle){
  this->wrist_angle = wrist_angle;
}


#endif
