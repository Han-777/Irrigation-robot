# robot_cmd

<p align='right'>neozng1@hnu.edu.cn</p>

## 运行流程

运行流程可以很直观的从`RobotCMDTask()`中看出。

1. 首先通过消息订阅机制，获取其他应用的反馈信息
2. 使用`CalcOffsetAngle()`计算底盘和云台的 offset angle（使得底盘始终获知当前的正方向）

### 陀螺仪控制模式

- 直线运动(A, B, C, D)
- cross 旋转
- cross to cross
