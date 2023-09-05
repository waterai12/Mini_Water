
/*
 * motor.c
 *
 *  Created on: 2023?7?17?
 *      Author: Qi520503
 */

#include "motor.h"
#include "tim.h"

/*
*	函数功能：取绝对值
*	入口参数：int
*	返回值：无 unsingned int
*/
int myabs(int num)
{
	int temp;
	if(num<0)	temp=-num;
	else temp =num;
	return temp;
}

/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：PWM
返回  值：无
**************************************************************************/
void Set_Pwmb(int motor_right)//赋值给PWM寄存器
{
	int pwmb_abs;
	if(motor_right>0) Motor_Right(1);
	else      Motor_Right(0);
	pwmb_abs=myabs(motor_right);
	__HAL_TIM_SET_COMPARE(&htim8,TIM_CHANNEL_2,pwmb_abs);
}

void Motor_forward()
{
		HAL_GPIO_WritePin(MB_AIN_1_GPIO_Port,MB_AIN_1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MB_AIN_2_GPIO_Port,MB_AIN_2_Pin,GPIO_PIN_SET);//即01，正转
}


