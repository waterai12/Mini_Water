/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Encoder_D_1_Pin GPIO_PIN_0
#define Encoder_D_1_GPIO_Port GPIOA
#define Encoder_D_2_Pin GPIO_PIN_1
#define Encoder_D_2_GPIO_Port GPIOA
#define Encoder_B_1_Pin GPIO_PIN_6
#define Encoder_B_1_GPIO_Port GPIOA
#define Encoder_B_2_Pin GPIO_PIN_7
#define Encoder_B_2_GPIO_Port GPIOA
#define MB_AIN_2_Pin GPIO_PIN_4
#define MB_AIN_2_GPIO_Port GPIOC
#define MB_AIN_1_Pin GPIO_PIN_5
#define MB_AIN_1_GPIO_Port GPIOC
#define PWM_MA_Pin GPIO_PIN_6
#define PWM_MA_GPIO_Port GPIOC
#define PWM_MB_Pin GPIO_PIN_7
#define PWM_MB_GPIO_Port GPIOC
#define PWM_MC_Pin GPIO_PIN_8
#define PWM_MC_GPIO_Port GPIOC
#define PWM_MD_Pin GPIO_PIN_9
#define PWM_MD_GPIO_Port GPIOC
#define Encoder_A_1_Pin GPIO_PIN_15
#define Encoder_A_1_GPIO_Port GPIOA
#define Encoder_A_2_Pin GPIO_PIN_3
#define Encoder_A_2_GPIO_Port GPIOB
#define Encoder_C_1_Pin GPIO_PIN_6
#define Encoder_C_1_GPIO_Port GPIOB
#define Encoder_C_2_Pin GPIO_PIN_7
#define Encoder_C_2_GPIO_Port GPIOB
#define OLED_SCL_Pin GPIO_PIN_8
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_9
#define OLED_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
