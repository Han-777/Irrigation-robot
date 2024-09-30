#include "gyro.h"
#include "bsp_usart.h"
#include "daemon.h"
#include <string.h>
#include "controller.h"
#include "general_def.h"
// 方便数据转化的结构体
// static IMUData_Packet_t IMUData_Packet;
static AHRSData_Packet_t AHRSData_Packet;
// 最终数据
static GYRO_data_t *gyro_data;
static DaemonInstance *GYRO_daemon_instance;
static USARTInstance *gyro_instance;
/**
 * @brief transfer data from hexadecimaml to floating-point values
 * 实现16进制的can数据转换成浮点型数据
 */

static float DATA_Trans(uint8_t Data_1, uint8_t Data_2, uint8_t Data_3, uint8_t Data_4)
{
    long long transition_32;
    float tmp = 0;
    int sign = 0;
    int exponent = 0;
    float mantissa = 0;
    transition_32 = 0;
    transition_32 |= Data_4 << 24;
    transition_32 |= Data_3 << 16;
    transition_32 |= Data_2 << 8;
    transition_32 |= Data_1;
    sign = (transition_32 & 0x80000000) ? -1 : 1; // 符号位
    // 先右移操作，再按位与计算，出来结果是30到23位对应的e
    exponent = ((transition_32 >> 23) & 0xff) - 127;
    // 将22~0转化为10进制，得到对应的x系数
    mantissa = 1 + ((float)(transition_32 & 0x7fffff) / 0x7fffff);
    tmp = sign * mantissa * pow(2, exponent);
    return tmp;
}

static long long timestamp(uint8_t Data_1, uint8_t Data_2, uint8_t Data_3, uint8_t Data_4)
{
    uint32_t transition_32;
    transition_32 = 0;
    transition_32 |= Data_4 << 24;
    transition_32 |= Data_3 << 16;
    transition_32 |= Data_2 << 8;
    transition_32 |= Data_1;
    return transition_32;
}

#ifdef GYRO_INFO_HANDLE_OUT
static uint16_t gyro_data_size;
/**
 * @brief gyro data parses
 *
 * @param GYRO_buff 接收buffer
 */
static uint8_t gyro_buff[GYRO_FRAME_SIZE];

void GYRO_buff_to_data()
{
    static uint8_t initialized = 0;
    if ((gyro_buff[0] == FRAME_HEAD) && (gyro_buff[gyro_data_size - 1] == FRAME_END))
    {
#if defined(GYRO_RSIMU) || defined(GYRO_RSIMU_AHRS)
        if ((gyro_buff[1] = TYPE_IMU) && (gyro_buff[2] = IMU_LEN))
        {
            IMUData_Packet.gyroscope_x = DATA_Trans(gyro_buff[7], gyro_buff[8], gyro_buff[9], gyro_buff[10]); // 角速度
            IMUData_Packet.gyroscope_y = DATA_Trans(gyro_buff[11], gyro_buff[12], gyro_buff[13], gyro_buff[14]);
            IMUData_Packet.gyroscope_z = DATA_Trans(gyro_buff[15], gyro_buff[16], gyro_buff[17], gyro_buff[18]);

            IMUData_Packet.accelerometer_x = DATA_Trans(gyro_buff[19], gyro_buff[20], gyro_buff[21], gyro_buff[22]); // 线加速度
            IMUData_Packet.accelerometer_y = DATA_Trans(gyro_buff[23], gyro_buff[24], gyro_buff[25], gyro_buff[26]);
            IMUData_Packet.accelerometer_z = DATA_Trans(gyro_buff[27], gyro_buff[28], gyro_buff[29], gyro_buff[30]);

            IMUData_Packet.magnetometer_x = DATA_Trans(gyro_buff[31], gyro_buff[32], gyro_buff[33], gyro_buff[34]); // 磁力计数据
            IMUData_Packet.magnetometer_y = DATA_Trans(gyro_buff[35], gyro_buff[36], gyro_buff[37], gyro_buff[38]);
            IMUData_Packet.magnetometer_z = DATA_Trans(gyro_buff[39], gyro_buff[40], gyro_buff[41], gyro_buff[42]);

            IMUData_Packet.Timestamp = timestamp(gyro_buff[55], gyro_buff[56], gyro_buff[57], gyro_buff[58]); // 时间戳
        }
#endif
#if defined(GYRO_RSAHRS) || defined(GYRO_RSIMU_AHRS)
        if ((gyro_buff[1] == TYPE_AHRS) && (gyro_buff[2] == AHRS_LEN))
        {
            AHRSData_Packet.RollSpeed = DATA_Trans(gyro_buff[7], gyro_buff[8], gyro_buff[9], gyro_buff[10]);       // 横滚角速度
            AHRSData_Packet.PitchSpeed = DATA_Trans(gyro_buff[11], gyro_buff[12], gyro_buff[13], gyro_buff[14]);   // 俯仰角速度
            AHRSData_Packet.HeadingSpeed = DATA_Trans(gyro_buff[15], gyro_buff[16], gyro_buff[17], gyro_buff[18]); // 偏航角速度
            AHRSData_Packet.Roll = DATA_Trans(gyro_buff[19], gyro_buff[20], gyro_buff[21], gyro_buff[22]);         // 横滚角
            AHRSData_Packet.Pitch = DATA_Trans(gyro_buff[23], gyro_buff[24], gyro_buff[25], gyro_buff[26]);        // 俯仰角
            AHRSData_Packet.Heading = DATA_Trans(gyro_buff[27], gyro_buff[28], gyro_buff[29], gyro_buff[30]);      // 偏航角
            AHRSData_Packet.Qw = DATA_Trans(gyro_buff[31], gyro_buff[32], gyro_buff[33], gyro_buff[34]);           // 四元数
            AHRSData_Packet.Qx = DATA_Trans(gyro_buff[35], gyro_buff[36], gyro_buff[37], gyro_buff[38]);
            AHRSData_Packet.Qy = DATA_Trans(gyro_buff[39], gyro_buff[40], gyro_buff[41], gyro_buff[42]);
            AHRSData_Packet.Qz = DATA_Trans(gyro_buff[43], gyro_buff[44], gyro_buff[45], gyro_buff[46]);
            AHRSData_Packet.Timestamp = timestamp(gyro_buff[47], gyro_buff[48], gyro_buff[49], gyro_buff[50]); // 时间戳

            // 稳定性判断
            gyro_data->last_Pitch = gyro_data->Pitch;
            gyro_data->last_Roll = gyro_data->Roll;

            gyro_data->Pitch = AHRSData_Packet.Pitch * 180.0 / PI;
            gyro_data->PitchSpeed = AHRSData_Packet.PitchSpeed * 180.0 / PI;
            gyro_data->Roll = AHRSData_Packet.Roll * 180.0 / PI;
            gyro_data->RollSpeed = AHRSData_Packet.RollSpeed * 180.0 / PI;
            if (AHRSData_Packet.Heading <= PI2)
            {
                gyro_data->last_Yaw = gyro_data->Yaw;
                gyro_data->Yaw = AHRSData_Packet.Heading * 180.0 / PI;
                gyro_data->YawSpeed = AHRSData_Packet.HeadingSpeed * 180.0 / PI;
            }
            // gyro_data->Yaw1 = AHRSData_Packet.Heading * 180.0 / PI;
            // if (fabs(gyro_data->Yaw) < 360)
            // {
            //     gyro_data->Yaw = gyro_data->Yaw1;
            // }

            if (!initialized)
            {
                if (abs(gyro_data->Yaw - gyro_data->last_Yaw) < 0.1 && abs(gyro_data->Pitch - gyro_data->last_Pitch) < 0.1 && abs(gyro_data->last_Roll - gyro_data->Roll) < 0.1)
                {
                    gyro_data->ori_yaw = gyro_data->Yaw; // 陀螺仪初始值不为0,记录初始值
                    gyro_data->ori_pitch = gyro_data->Pitch;
                    gyro_data->ori_roll = gyro_data->Roll;
                    initialized = 1;
                }
            }
        }
    }
#endif
}
#else
static void GYRO_buff_to_data(const uint8_t *gyro_buff, uint16_t size)
{
    static uint8_t initialized = 0;
    if ((gyro_buff[0] == FRAME_HEAD) && (gyro_buff[size - 1] == FRAME_END))
    {
#if defined(GYRO_RSIMU) || defined(GYRO_RSIMU_AHRS)
        if ((gyro_buff[1] = TYPE_IMU) && (gyro_buff[2] = IMU_LEN))
        {
            IMUData_Packet.gyroscope_x = DATA_Trans(gyro_buff[7], gyro_buff[8], gyro_buff[9], gyro_buff[10]); // 角速度
            IMUData_Packet.gyroscope_y = DATA_Trans(gyro_buff[11], gyro_buff[12], gyro_buff[13], gyro_buff[14]);
            IMUData_Packet.gyroscope_z = DATA_Trans(gyro_buff[15], gyro_buff[16], gyro_buff[17], gyro_buff[18]);

            IMUData_Packet.accelerometer_x = DATA_Trans(gyro_buff[19], gyro_buff[20], gyro_buff[21], gyro_buff[22]); // 线加速度
            IMUData_Packet.accelerometer_y = DATA_Trans(gyro_buff[23], gyro_buff[24], gyro_buff[25], gyro_buff[26]);
            IMUData_Packet.accelerometer_z = DATA_Trans(gyro_buff[27], gyro_buff[28], gyro_buff[29], gyro_buff[30]);

            IMUData_Packet.magnetometer_x = DATA_Trans(gyro_buff[31], gyro_buff[32], gyro_buff[33], gyro_buff[34]); // 磁力计数据
            IMUData_Packet.magnetometer_y = DATA_Trans(gyro_buff[35], gyro_buff[36], gyro_buff[37], gyro_buff[38]);
            IMUData_Packet.magnetometer_z = DATA_Trans(gyro_buff[39], gyro_buff[40], gyro_buff[41], gyro_buff[42]);

            IMUData_Packet.Timestamp = timestamp(gyro_buff[55], gyro_buff[56], gyro_buff[57], gyro_buff[58]); // 时间戳
        }
#endif
#if defined(GYRO_RSAHRS) || defined(GYRO_RSIMU_AHRS)
        if ((gyro_buff[1] == TYPE_AHRS) && (gyro_buff[2] == AHRS_LEN))
        {
            // AHRSData_Packet.RollSpeed = DATA_Trans(gyro_buff[7], gyro_buff[8], gyro_buff[9], gyro_buff[10]);       // 横滚角速度
            // AHRSData_Packet.PitchSpeed = DATA_Trans(gyro_buff[11], gyro_buff[12], gyro_buff[13], gyro_buff[14]);   // 俯仰角速度
            // AHRSData_Packet.HeadingSpeed = DATA_Trans(gyro_buff[15], gyro_buff[16], gyro_buff[17], gyro_buff[18]); // 偏航角速度
            AHRSData_Packet.Roll = DATA_Trans(gyro_buff[19], gyro_buff[20], gyro_buff[21], gyro_buff[22]); // 横滚角
            // AHRSData_Packet.Pitch = DATA_Trans(gyro_buff[23], gyro_buff[24], gyro_buff[25], gyro_buff[26]);   // 俯仰角
            AHRSData_Packet.Heading = DATA_Trans(gyro_buff[27], gyro_buff[28], gyro_buff[29], gyro_buff[30]); // 偏航角
            // AHRSData_Packet.Qw = DATA_Trans(gyro_buff[31], gyro_buff[32], gyro_buff[33], gyro_buff[34]);           // 四元数
            // AHRSData_Packet.Qx = DATA_Trans(gyro_buff[35], gyro_buff[36], gyro_buff[37], gyro_buff[38]);
            // AHRSData_Packet.Qy = DATA_Trans(gyro_buff[39], gyro_buff[40], gyro_buff[41], gyro_buff[42]);
            // AHRSData_Packet.Qz = DATA_Trans(gyro_buff[43], gyro_buff[44], gyro_buff[45], gyro_buff[46]);
            AHRSData_Packet.Timestamp = timestamp(gyro_buff[47], gyro_buff[48], gyro_buff[49], gyro_buff[50]); // 时间戳

            // 稳定性判断
            // gyro_data->last_Pitch = gyro_data->Pitch;
            gyro_data->last_Roll = gyro_data->Roll;

            // gyro_data->Pitch = AHRSData_Packet.Pitch * 180.0 / PI;
            // gyro_data->PitchSpeed = AHRSData_Packet.PitchSpeed * 180.0 / PI;
            gyro_data->Roll = AHRSData_Packet.Roll * 180.0 / PI;
            // gyro_data->RollSpeed = AHRSData_Packet.RollSpeed * 180.0 / PI;
            if (AHRSData_Packet.Heading <= PI2)
            {
                gyro_data->last_Yaw = gyro_data->Yaw;
                gyro_data->Yaw = AHRSData_Packet.Heading * 180.0 / PI;
                // gyro_data->YawSpeed = AHRSData_Packet.HeadingSpeed * 180.0 / PI;
            }
            // gyro_data->Yaw1 = AHRSData_Packet.Heading * 180.0 / PI;
            // if (fabs(gyro_data->Yaw) < 360)
            // {
            //     gyro_data->Yaw = gyro_data->Yaw1;
            // }

            if (!initialized)
            {
                if (abs(gyro_data->Yaw - gyro_data->last_Yaw) < 0.02 && abs(gyro_data->last_Roll - gyro_data->Roll) < 0.02)
                {
                    gyro_data->ori_yaw = gyro_data->Yaw; // 陀螺仪初始值不为0,记录初始值
                    // gyro_data->ori_pitch = gyro_data->Pitch;
                    gyro_data->ori_roll = gyro_data->Roll;
                    initialized = 1;
                    gyro_data->gyro_Init_Flag = 1;
                }
            }
        }

#endif
    }
}
#endif

/**
 * @brief GYRO_buff_to_data,用于注册到bsp_usart的回调函数中
 *
 * @note huart2: the address of left lidar usart handle
 *       huart4: the address of right lidar usart handle
 */
static void GYRORxCallback(UART_HandleTypeDef *huart, uint16_t size) // 串口接收回调_
{
    DaemonReload(GYRO_daemon_instance);
#ifdef GYRO_INFO_HANDLE_OUT
    if ((gyro_instance->recv_buff[0] == FRAME_HEAD) && (gyro_instance->recv_buff[size - 1] == FRAME_END))
    {
        gyro_data_size = size;
        memset(gyro_buff, 0, GYRO_FRAME_SIZE);
        memcpy(gyro_buff, gyro_instance->recv_buff, size);
    }
#else
    GYRO_buff_to_data(gyro_instance->recv_buff, size);
#endif
}

/**
 * @brief 雷达离线的回调函数,注册到守护进程中,串口掉线时调用
 * @note huart2: the address of left lidar usart handle
 *       huart4: the address of right lidar usart handle
 */
static void GYROLostCallback(void *id) // id is corresponding usart handle
{
    memset(gyro_instance, 0, sizeof(gyro_instance));
    USARTServiceInit(gyro_instance);
}

GYRO_data_t *Gyro_Init(UART_HandleTypeDef *gyro_usart_handle)
{
    USART_Init_Config_s conf;
    conf.module_callback = GYRORxCallback;
    conf.usart_handle = gyro_usart_handle;
    conf.recv_buff_size = GYRO_FRAME_SIZE;
    gyro_instance = USARTRegister(&conf);

    Daemon_Init_Config_s daemon_conf = {
        .reload_count = 2, // 看门狗待了解_ 20ms没收到消息  输出频率默认为100Hz->10ms
        .callback = GYROLostCallback,
        .owner_id = gyro_usart_handle,
    };
    GYRO_daemon_instance = DaemonRegister(&daemon_conf);
    return gyro_data;
}
