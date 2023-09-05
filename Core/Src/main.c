/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "oled.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/**************************************************************************
函数功能：OLED显示
入口参数：无
返回  值：�?
**************************************************************************/
void OLED_ShowInt(u8 x,u8 y,long int num,u8 len)
{
	if(num < 0)
	{
		num *= -1;
		OLED_ShowString(x, y, "-",12,1);
	}
	else
	{
		OLED_ShowString(x, y, "+",12,1);
	}
	OLED_ShowNum(x + 15, y ,num, len, 12, 1);
}

void oled_show(float Pitch, float Roll, float Yaw, int Encoder_A, int Encoder_B, int Encoder_C, int Encoder_D, int Voltage)
{			
  long int Target_A = 6, Target_B = 6, Target_C = 6, Target_D = 6;	//电机目标�?

  //=============�?1行显�?3轴角�?===============//	
	OLED_ShowString(0,0,"X:",12,1);
	if(Pitch<0)		OLED_ShowNum(15,0,Pitch+360,3,12,1);
	else			OLED_ShowNum(15,0,Pitch,3,12,1);	
	OLED_ShowString(40,0,"Y:",12,1);
	if(Roll<0)		OLED_ShowNum(55,0,Roll+360,3,12,1);
	else			OLED_ShowNum(55,0,Roll,3,1,1);	
	OLED_ShowString(80,0,"Z:",12,1);
	if(Yaw<0)		OLED_ShowNum(95,0,Yaw+360,3,12,1);
	else			OLED_ShowNum(95,0,Yaw,3,12,1);		

	//=============显示电机状�??=======================//	
	OLED_ShowInt(0,  10, Target_A, 5);
	OLED_ShowInt(80, 10, Encoder_A, 5);
	OLED_ShowInt(0,  20, Target_B, 5);
	OLED_ShowInt(80, 20, Encoder_B, 5);
	OLED_ShowInt(0,  30, Target_C, 5);
	OLED_ShowInt(80, 30, Encoder_C, 5);
	OLED_ShowInt(0,  40, Target_D, 5);
	OLED_ShowInt(80, 40, Encoder_D, 5);

	//=============显示电压=======================//
	OLED_ShowString(00,50,"VELOCITY",12,1);
	OLED_ShowString(88,50,".",12,1);
	OLED_ShowString(110,50,"V",12,1);
	OLED_ShowNum(75,50,Voltage/100,2,12,1);
	OLED_ShowNum(98,50,Voltage%100,2,12,1);
	if(Voltage%100<10) 	OLED_ShowNum(92,50,0,2,12,1);
}
/* USER CODE END PFP */
short Get_Encoder_C(void)
{
  int Encoder_C_speed;
  Encoder_C_speed = (short)__HAL_TIM_GET_COUNTER(&htim4);
  __HAL_TIM_SET_COUNTER(&htim4, 0);
  return Encoder_C_speed;
}
/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();

  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
  int Voltage=780;										//电池电压采样相关的变�?
  float Pitch, Roll, Yaw;		//三轴角度和XYZ轴目标�?�度
  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);//?pwm??

  // HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
  // HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
  // HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
  // HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
  // __HAL_TIM_SET_COUNTER(&htim3,0);
  // HAL_TIM_Base_Start_IT(&htim3);
//�?启TIM3的编码器模式，用于读取正交编码器
	OLED_Init();
  OLED_ColorTurn(0);
  OLED_DisplayTurn(0);
  // oled_show(Pitch, Roll, Yaw, 10, 10, 10, 10, Voltage);
  OLED_Refresh();
  int Encoder_A=0, Encoder_B=0, Encoder_C=0, Encoder_D=0;
  int pwm_c=0;
  while (1)
  { 
    // int NUM = GetLeftEncoder();
    Encoder_A = (short)__HAL_TIM_GET_COUNTER(&htim2);
    Encoder_B = (short)__HAL_TIM_GET_COUNTER(&htim3);
    Encoder_C = Get_Encoder_C(); // (short)__HAL_TIM_GET_COUNTER(&htim4);
    Encoder_D = (short)__HAL_TIM_GET_COUNTER(&htim5);

    u8 xa=0, ya=0;
    xa = Encoder_A/4+64;
    ya = Encoder_B/4+32;
    // OLED_DrawPoint(xa, ya, 1);
    // OLED_DrawPoint(xa+1, ya+1, 1);
    // OLED_DrawPoint(xa+1, ya+1, 1);
    OLED_Refresh();
    HAL_GPIO_WritePin(MB_AIN_1_GPIO_Port,MB_AIN_1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MB_AIN_2_GPIO_Port,MB_AIN_2_Pin,GPIO_PIN_SET);
    
    if(Encoder_C<30) pwm_c+=2*(30-Encoder_C);
    else pwm_c-=2*(Encoder_C-30);
    if (pwm_c<0) pwm_c=0;
    if (pwm_c>1000) pwm_c=1000;
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, pwm_c);
        oled_show(Pitch, Roll, Yaw, Encoder_A, Encoder_B, Encoder_C, pwm_c, Voltage);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
