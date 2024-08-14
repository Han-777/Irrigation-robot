#include "dji_motor.h"
#include "general_def.h"
#include "bsp_dwt.h"
// #include "bsp_log.h"
float speed_pid;
float current_pid;
float real_c;
float real_s;
float speed_err;
static uint8_t idx = 0; // register idx,是该文件的全局电机索引,在注册时使用
/* DJI电机的实例,此处仅保存指针,内存的分配将通过电机实例初始化时通过malloc()进行 */
static DJIMotorInstance *dji_motor_instance[DJI_MOTOR_CNT] = {NULL}; // 会在control任务中遍历该指针数组进行pid计算

/**
 * @brief 由于DJI电机发送以四个一组的形式进行,故对其进行特殊处理,用6个(2can*3group)can_instance专门负责发送
 *        该变量将在 DJIMotorControl() 中使用,分组在 MotorSenderGrouping()中进行
 *
 * @note  因为只用于发送,所以不需要在bsp_can中注册
 *
 * C610(m2006)/C620(m3508):0x1ff,0x200;
 * GM6020:0x1ff,0x2ff
 * 反馈(rx_id): GM6020: 0x204+id ; C610/C620: 0x200+id
 * can1: [0]:0x1FF,[1]:0x200,[2]:0x2FF
 * can2: [3]:0x1FF,[4]:0x200,[5]:0x2FF
 */
static CANInstance sender_assignment[6] = {
    [0] = {.can_handle = &hfdcan1, .txconf.Identifier = 0x1ff, .txconf.IdType = FDCAN_STANDARD_ID, .txconf.TxFrameType = FDCAN_DATA_FRAME, .txconf.DataLength = FDCAN_DLC_BYTES_8, .tx_buff = {0}},
    [1] = {.can_handle = &hfdcan1, .txconf.Identifier = 0x200, .txconf.IdType = FDCAN_STANDARD_ID, .txconf.TxFrameType = FDCAN_DATA_FRAME, .txconf.DataLength = FDCAN_DLC_BYTES_8, .tx_buff = {0}},
    [2] = {.can_handle = &hfdcan1, .txconf.Identifier = 0x2ff, .txconf.IdType = FDCAN_STANDARD_ID, .txconf.TxFrameType = FDCAN_DATA_FRAME, .txconf.DataLength = FDCAN_DLC_BYTES_8, .tx_buff = {0}},
    [3] = {.can_handle = &hfdcan2, .txconf.Identifier = 0x1ff, .txconf.IdType = FDCAN_STANDARD_ID, .txconf.TxFrameType = FDCAN_DATA_FRAME, .txconf.DataLength = FDCAN_DLC_BYTES_8, .tx_buff = {0}},
    [4] = {.can_handle = &hfdcan2, .txconf.Identifier = 0x200, .txconf.IdType = FDCAN_STANDARD_ID, .txconf.TxFrameType = FDCAN_DATA_FRAME, .txconf.DataLength = FDCAN_DLC_BYTES_8, .tx_buff = {0}},
    [5] = {.can_handle = &hfdcan2, .txconf.Identifier = 0x2ff, .txconf.IdType = FDCAN_STANDARD_ID, .txconf.TxFrameType = FDCAN_DATA_FRAME, .txconf.DataLength = FDCAN_DLC_BYTES_8, .tx_buff = {0}},
};

/**
 * @brief 6个用于确认是否有电机注册到sender_assignment中的标志位,防止发送空帧,此变量将在DJIMotorControl()使用
 *        flag的初始化在 MotorSenderGrouping()中进行
 */
static uint8_t sender_enable_flag[6] = {0};

/**
 * @brief 根据电调/拨码开关上的ID,根据说明书的默认id分配方式计算发送ID和接收ID,
 *        并对电机进行分组以便处理多电机控制命令
 */
static void MotorSenderGrouping(DJIMotorInstance *motor, CAN_Init_Config_s *config)
{
    uint8_t motor_id = config->tx_id - 1; // Start from zero index, subtract one for convenience
    uint8_t motor_send_num;
    uint8_t motor_grouping;

    switch (motor->motor_type)
    {
    case M2006:
    case M3508:
        if (motor_id < 4) // Grouping based on ID
        {
            motor_send_num = motor_id;
            motor_grouping = config->can_handle == &hfdcan1 ? 1 : 4;
        }
        else
        {
            motor_send_num = motor_id - 4;
            motor_grouping = config->can_handle == &hfdcan1 ? 0 : 3;
        }
        // Calculate receiving ID and set group sending ID
        config->rx_id = 0x200 + motor_id + 1;   // Add 1 to ID, and set group
        sender_enable_flag[motor_grouping] = 1; // Set sending flag to prevent sending empty frames
        motor->message_num = motor_send_num;
        motor->sender_group = motor_grouping;

        // Check for ID conflict
        for (size_t i = 0; i < idx; ++i)
        {
            if (dji_motor_instance[i]->motor_can_instance->can_handle == config->can_handle && dji_motor_instance[i]->motor_can_instance->rx_id == config->rx_id)
            {
                // LOGERROR("[dji_motor] ID crash. Check in debug mode, add dji_motor_instance to watch to get more information.");
                uint16_t can_bus = config->can_handle == &hfdcan1 ? 1 : 2;
                while (1)
                    ; // Conflict between IDs 1-4 of 6020 and IDs 5-8 of 2006/3508 (1!5, 2!6, 3!7, 4!8)
                      // LOGERROR("[dji_motor] id [%d], can_bus [%d]", config->rx_id, can_bus);
            }
        }
        break;

    case GM6020:
        if (motor_id < 4)
        {
            motor_send_num = motor_id;
            motor_grouping = config->can_handle == &hfdcan1 ? 0 : 3;
        }
        else
        {
            motor_send_num = motor_id - 4;
            motor_grouping = config->can_handle == &hfdcan1 ? 2 : 5;
        }

        config->rx_id = 0x204 + motor_id + 1;   // Add 1 to ID, and set group
        sender_enable_flag[motor_grouping] = 1; // Set sending flag to prevent sending empty frames
        motor->message_num = motor_send_num;
        motor->sender_group = motor_grouping;

        for (size_t i = 0; i < idx; ++i)
        {
            if (dji_motor_instance[i]->motor_can_instance->can_handle == config->can_handle && dji_motor_instance[i]->motor_can_instance->rx_id == config->rx_id)
            {
                // LOGERROR("[dji_motor] ID crash. Check in debug mode, add dji_motor_instance to watch to get more information.");
                uint16_t can_bus = config->can_handle == &hfdcan1 ? 1 : 2;
                while (1)
                    ; // Conflict between IDs 1-4 of 6020 and IDs 5-8 of 2006/3508 (1!5, 2!6, 3!7, 4!8)
                      // LOGERROR("[dji_motor] id [%d], can_bus [%d]", config->rx_id, can_bus);
            }
        }
        break;

    default: // other motors should not be registered here
        while (1)
            ;
        // LOGERROR("[dji_motor]You must not register other motors using the API of DJI motor."); // Other motors should not be registered here
    }
}

/**
 * @todo  是否可以简化多圈角度的计算？
 * @brief 根据返回的can_instance对反馈报文进行解析
 *
 * @param _instance 收到数据的instance,通过遍历与所有电机进行对比以选择正确的实例
 */
static void DecodeDJIMotor(CANInstance *_instance)
{
    // Here, the ID of the can instance is forcibly converted to get the motor instance address
    // _instance pointer points to the ID, which is the address of the corresponding motor instance. By forcibly converting it to a motor instance pointer,
    // we can access the motor member motor_measure and then get the pointer by taking the address.
    uint8_t *rxbuff = _instance->rx_buff;
    DJIMotorInstance *motor = (DJIMotorInstance *)_instance->id;
    DJI_Motor_Measure_s *measure = &motor->measure; // measure will be used multiple times, save the pointer to reduce access overhead

    DaemonReload(motor->daemon);
    motor->dt = DWT_GetDeltaT(&motor->feed_cnt);

    // Parse data and filter current and speed, the specific format of the motor feedback message is in the motor manual
    measure->last_ecd = measure->ecd;
    measure->ecd = ((uint16_t)rxbuff[0]) << 8 | rxbuff[1];
    measure->angle_single_round = ECD_ANGLE_COEF_DJI * (float)measure->ecd;
    measure->speed_aps = (1.0f - SPEED_SMOOTH_COEF) * measure->speed_aps +
                         RPM_2_ANGLE_PER_SEC * SPEED_SMOOTH_COEF * (float)((int16_t)(rxbuff[2] << 8 | rxbuff[3]));
    measure->real_current = (1.0f - CURRENT_SMOOTH_COEF) * measure->real_current +
                            CURRENT_SMOOTH_COEF * (float)((int16_t)(rxbuff[4] << 8 | rxbuff[5]));
    measure->temperature = rxbuff[6];

    // Multi-turn angle calculation, assuming the motor rotates less than 180° between two samples, draw a graph to understand the calculation process.
    if (measure->ecd - measure->last_ecd > 4096)
        measure->total_round--;
    else if (measure->ecd - measure->last_ecd < -4096)
        measure->total_round++;
    measure->total_angle = measure->total_round * 360 + measure->angle_single_round;
}

static void DJIMotorLostCallback(void *motor_ptr)
{
    DJIMotorInstance *motor = (DJIMotorInstance *)motor_ptr;
    uint16_t can_bus = motor->motor_can_instance->can_handle == &hfdcan1 ? 1 : 2;
    // LOGWARNING("[dji_motor] Motor lost, can bus [%d], id [%d]", can_bus, motor->motor_can_instance->tx_id);
}

// 电机初始化,返回一个电机实例
DJIMotorInstance *DJIMotorInit(Motor_Init_Config_s *config)
{
    DJIMotorInstance *instance = (DJIMotorInstance *)malloc(sizeof(DJIMotorInstance));
    memset(instance, 0, sizeof(DJIMotorInstance));

    // motor basic setting 电机基本设置
    instance->motor_type = config->motor_type;                         // 6020 or 2006 or 3508
    instance->motor_settings = config->controller_setting_init_config; // 正反转,闭环类型等

    // motor controller init 电机控制器初始化
    PIDInit(&instance->motor_controller.current_PID, &config->controller_param_init_config.current_PID);
    PIDInit(&instance->motor_controller.speed_PID, &config->controller_param_init_config.speed_PID);
    PIDInit(&instance->motor_controller.angle_PID, &config->controller_param_init_config.angle_PID);
    instance->motor_controller.other_angle_feedback_ptr = config->controller_param_init_config.other_angle_feedback_ptr;
    instance->motor_controller.other_speed_feedback_ptr = config->controller_param_init_config.other_speed_feedback_ptr;
    instance->motor_controller.current_feedforward_ptr = config->controller_param_init_config.current_feedforward_ptr;
    instance->motor_controller.speed_feedforward_ptr = config->controller_param_init_config.speed_feedforward_ptr;
    // 后续增加电机前馈控制器(速度和电流)

    // 电机分组,因为至多4个电机可以共用一帧CAN控制报文
    MotorSenderGrouping(instance, &config->can_init_config);

    // 注册电机到CAN总线
    config->can_init_config.can_module_callback = DecodeDJIMotor; // set callback
    config->can_init_config.id = instance;                        // set id,eq to address(it is identity)
    instance->motor_can_instance = CANRegister(&config->can_init_config);

    // 注册守护线程
    Daemon_Init_Config_s daemon_config = {
        .callback = DJIMotorLostCallback,
        .owner_id = instance,
        .reload_count = 2, // 20ms未收到数据则丢失
    };
    instance->daemon = DaemonRegister(&daemon_config);

    // (instance);
    dji_motor_instance[idx++] = instance;
    return instance;
}

/* 电流只能通过电机自带传感器监测,后续考虑加入力矩传感器应变片等 */
void DJIMotorChangeFeed(DJIMotorInstance *motor, Closeloop_Type_e loop, Feedback_Source_e type)
{
    if (loop == ANGLE_LOOP)
        motor->motor_settings.angle_feedback_source = type;
    else if (loop == SPEED_LOOP)
        motor->motor_settings.speed_feedback_source = type;
    // LOGERROR("[dji_motor] loop type error, check memory access and func param"); // 检查是否传入了正确的LOOP类型,或发生了指针越界
}

void DJIMotorStop(DJIMotorInstance *motor)
{
    motor->stop_flag = MOTOR_STOP;
}

void DJIMotorEnable(DJIMotorInstance *motor)
{
    motor->stop_flag = MOTOR_ENALBED;
}

/* 修改电机的实际闭环对象 */
void DJIMotorOuterLoop(DJIMotorInstance *motor, Closeloop_Type_e outer_loop)
{
    motor->motor_settings.outer_loop_type = outer_loop;
}

// 为所有电机实例计算三环PID,发送控制报文
void DJIMotorSetRef(DJIMotorInstance *motor, float ref)
{
    motor->motor_controller.pid_ref = ref;
}

// Calculate three-loop PID for all motor instances and send control messages
void DJIMotorControl()
{
    // Save a pointer reference once to reduce memory access overhead and also improve readability
    uint8_t group, num; // Motor group number and group internal number
    int16_t set;        // Motor control CAN transmission setting value
    DJIMotorInstance *motor;
    Motor_Control_Setting_s *motor_setting; // Motor control parameters
    Motor_Controller_s *motor_controller;   // Motor controller
    DJI_Motor_Measure_s *measure;           // Motor measurements
    float pid_measure, pid_ref;             // Motor PID measurement and reference values

    // Traverse all motor instances, calculate cascade PID, and set the transmission message value
    for (size_t i = 0; i < idx; ++i)
    { // Reduce memory access overhead, save pointer references first
        motor = dji_motor_instance[i];
        motor_setting = &motor->motor_settings;
        motor_controller = &motor->motor_controller;
        measure = &motor->measure;
        pid_ref = motor_controller->pid_ref; // Save reference value to prevent motor_controller->pid_ref from being modified during calculation
        if (motor_setting->motor_reverse_flag == MOTOR_DIRECTION_REVERSE)
            pid_ref *= -1; // Set reverse

        // pid_ref will successively act as a carrier for data through enabled closed loops
        // Calculate position loop, only when position loop is enabled and the outer closed loop is position will the speed loop output be calculated
        if ((motor_setting->close_loop_type & ANGLE_LOOP) && motor_setting->outer_loop_type == ANGLE_LOOP)
        {
            if (motor_setting->angle_feedback_source == OTHER_FEED)
                pid_measure = *motor_controller->other_angle_feedback_ptr;
            else
                pid_measure = measure->total_angle; // MOTOR_FEED, closed-loop on total angle to prevent sudden jumps at the boundary
            // Update pid_ref to enter the next loop
            pid_ref = PIDCalculate(&motor_controller->angle_PID, pid_measure, pid_ref);
        }

        // Calculate speed loop, (outer closed loop is speed or position) and (speed loop is enabled) will calculate speed loop
        if ((motor_setting->close_loop_type & SPEED_LOOP) && (motor_setting->outer_loop_type & (ANGLE_LOOP | SPEED_LOOP)))
        {
            if (motor_setting->feedforward_flag & SPEED_FEEDFORWARD)
                pid_ref += *motor_controller->speed_feedforward_ptr;

            if (motor_setting->speed_feedback_source == OTHER_FEED)
                pid_measure = *motor_controller->other_speed_feedback_ptr;
            else // MOTOR_FEED
                pid_measure = measure->speed_aps;
            // Update pid_ref to enter the next loop
            pid_ref = PIDCalculate(&motor_controller->speed_PID, pid_measure, pid_ref);
            speed_pid = pid_ref;
            real_s = pid_measure;
            speed_err = motor_controller->speed_PID.Err;
        }

        // Calculate current loop, currently calculated as long as the current loop is enabled, regardless of the outer closed loop, and current only has feedback from the motor's own sensor
        if (motor_setting->feedforward_flag & CURRENT_FEEDFORWARD)
            pid_ref += *motor_controller->current_feedforward_ptr;
        if (motor_setting->close_loop_type & CURRENT_LOOP)
        {
            pid_ref = PIDCalculate(&motor_controller->current_PID, measure->real_current, pid_ref);
            current_pid = pid_ref;
            real_c = measure->real_current;
        }
        //
        if (motor_setting->feedback_reverse_flag == FEEDBACK_DIRECTION_REVERSE)
            pid_ref *= -1;

        // Get the final output
        set = (int16_t)pid_ref;

        // Fill in the sending data by group
        group = motor->sender_group;
        num = motor->message_num;
        sender_assignment[group].tx_buff[2 * num] = (uint8_t)(set >> 8);         // High eight bits
        sender_assignment[group].tx_buff[2 * num + 1] = (uint8_t)(set & 0x00ff); // Low eight bits

        // If the motor is in stop state, directly set the buff to zero
        if (motor->stop_flag == MOTOR_STOP)
            memset(sender_assignment[group].tx_buff + 2 * num, 0, 16u);
    }

    // Traverse the flags, check if this frame of message should be sent
    for (size_t i = 0; i < 6; ++i)
    {
        if (sender_enable_flag[i])
        {
            CANTransmit(&sender_assignment[i], 1);
        }
    }
}