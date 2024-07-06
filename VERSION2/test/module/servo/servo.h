#ifndef __SERVO_H
#define __SERVO_H

#include "sys.h"

typedef enum
{
    pitch_servo = 0x01, // 01
    yaw_servo = 0x02,   // 10
} servoName;

void servo_Init_All(void);
void Servo_Pitch_Control(uint16_t Compare);
void Servo_Yaw_Control(uint16_t Compare);
void ServoMove(uint16_t angel1, uint16_t angel2);
void ServoControl(servoName name, uint16_t currentAngle, uint16_t targetAngle, uint16_t delay_time);

#endif
