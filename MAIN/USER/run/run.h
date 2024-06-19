#ifndef __RUN_H
#define __RUN_H

#include "stm32f4xx.h"                  // Device header

// extern u8 color_Index;


typedef enum{
	qrcodeMode = 0,
	objMode,
	roughMode,
	depositMode,
	backObjMode,
	objMode2,
	depositMode2,
	homeMode
}runState;

typedef enum{
	back,
	changeDir,
	object_Pos,
	corner1_Pos,
	corner2_Pos,
	corner3_Pos,
	deposit_Up_Pos,
	deposit_Down_Pos,
	home_Pos
}positionDes;

typedef enum{
	red = 0xA0,
	green,
	blue, 
	yellow,
	black // black indecate nothing
} colorIndex;


void Run(void);

extern colorIndex colorIdx;
#endif