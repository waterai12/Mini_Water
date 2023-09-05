
/*
 * motor.c
 *
 *  Created on: 2023?7?17?
 *      Author: Qi520503
 */

#include "motor.h"
#include "tim.h"

/*
*	�������ܣ�ȡ����ֵ
*	��ڲ�����int
*	����ֵ���� unsingned int
*/
int myabs(int num)
{
	int temp;
	if(num<0)	temp=-num;
	else temp =num;
	return temp;
}

/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ�����PWM
����  ֵ����
**************************************************************************/
void Set_Pwmb(int motor_right)//��ֵ��PWM�Ĵ���
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
		HAL_GPIO_WritePin(MB_AIN_2_GPIO_Port,MB_AIN_2_Pin,GPIO_PIN_SET);//��01����ת
}


