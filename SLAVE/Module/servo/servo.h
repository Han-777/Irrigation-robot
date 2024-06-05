#ifndef __SERVO_H
#define __SERVO_H
#include "sys.h"

void servoInit();
void ServoControl(float angel1, float angel2, float angel3, float angel4);
void Servo1Control(uint16_t Compare);
void Servo2Control(uint16_t Compare);
void Servo3Control(uint16_t Compare);
void Servo4Control(uint16_t Compare);

#endif
