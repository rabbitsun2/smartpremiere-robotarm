/*
 * Created Date: 2022-08-12 (Fri)
 * Author: Doyun Jung (정도윤) / rabbit.white@daum.net
 * Subject: Smart Logistics Robot Arm IoT
 * Filename: robot_control.h
 * Description:
 * 1. 로봇 컨트롤 영역 생성, 정도윤, 2022-08-10 (Wed)
 * 
 */
#ifndef ROBOT_CONTROL_H_
#define ROBOT_CONTROL_H_

class Robot_control{

public:
  void setHCPCA9685(HCPCA9685* hcp);
  
private:
  HCPCA9685* hcpca9685;
  
};

void Robot_control::setHCPCA9685(HCPCA9685* hcp){
  this->hcpca9685 = hcp;
}

#endif
