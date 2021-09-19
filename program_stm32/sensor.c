/*
 * sensor.c
 *
 *  Created on: Jan 24, 2020
 *      Author: Kacper
 */

#include "sensor.h"
#include "main.h"

I2C_HandleTypeDef hi2c1;
#define BH1750_ADDRESS (0x23 << 1)

void sensor_start()
{
	uint8_t Settings1 = 0x01;
	uint8_t Settings2 = 0x10;

	HAL_I2C_Master_Transmit(&hi2c1,BH1750_ADDRESS,&Settings1,1,0xffff);
	HAL_I2C_Master_Transmit(&hi2c1,BH1750_ADDRESS,&Settings2,1,0xffff);
}

float sensor_getdata(void)
{
	uint8_t Data[2];
	float result;

	HAL_I2C_Master_Receive(&hi2c1,BH1750_ADDRESS,Data,2,0xffff);

	result =  ((Data[0]<<8) | Data[1]) /1.2;

	return  result;
}
