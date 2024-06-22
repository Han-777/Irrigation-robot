#ifndef __ARM_H
#define __ARM_H

#include "sys.h"
#include "servo.h"
#include "run.h"
#include "photoelectric.h"
#include "openmv.h"
#include "bluetooth.h"
#include "mp3.h"
#include "lidar.h"
#define plant_found !PE_NOZZLE
#define lidar_water_dist_threshold 30
typedef struct
{
    u8 left_water_scan_finish;
    u8 right_water_scan_finish;
    u8 left_water_finish;
    u8 right_water_finish;
} water_finish_Structure_TypeDef;
extern water_finish_Structure_TypeDef water_finish_structure;
// �ϵ�Ƕ�
#define pitch_mid 120 // 150
#define yaw_mid 40

// yaw scan angle
#define left_scan_begin 80
#define left_scan_end 40

#define right_scan_begin 200
#define right_scan_end 240

#define left_scan_mid 150  // ������
#define right_scan_mid 150 // �Ҳ����

#define left_D_angle 80
#define right_D_angle 150
#define pitch_D_water_angle 120
// pitch scan angle
#define pitch_scan_angle 120

#define length_A 27.50 // ��ˮ�Ļ�е�۳���
#define H 32.50        // ��������������̨�Ĵ�ֱ  HҪ������
#define D_d 20.00      // ���ļ������ĵ���������
#define R_R 9.50       // Բ�λ���İ뾶

#define pitch_lift_angle 170 // ̧�߽Ƕ�//��е�۵Ĵ�ֱ�Ƕ� 90Ϊֱ��,
#define Balance_angle 195    // ƽ��Ƕ�    max

// ��̨�Ƕ�
#define Left_D 202 // D����̨
#define Right_D 98 // D����̨

#define Mid 150 // ����//��̨������Ƕ�

int water_finish(void);
void arm_water_task(void);

#endif
