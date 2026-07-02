/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_config.h"
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PWR_StopModeConfigTypeDef PwrStopModeConf = {0};
__IO uint8_t ueRemotewakeup = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_USBInit(void);
static void APP_USBEnterStop(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick. */
  HAL_Init();

  /* System clock configuration */
  APP_SystemClockConfig();
  
  /* Initialize button */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);
  
  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Off(LED_GREEN);

  /* Initialize USB peripheral */
  APP_USBInit();
  
  /* Infinite loop */
  while (1)
  {
    /* Check if is in the suspend state */
    if(suspend_state == 1)
    {
      BSP_LED_On(LED_GREEN);
      /* Enter stop mode */
      APP_USBEnterStop();
      BSP_LED_Off(LED_GREEN);
      
      /* Check if need to send remote wakeup signal */
      if(ueRemotewakeup == 1)
      {
        ueRemotewakeup = 0;
        usb_sendresume();
        /* Report that button A has been pressed */
        hid_keyboard_test();
      }
      suspend_state = 0;
    }
  }
}

static void APP_USBEnterStop(void)
{
  RCC_OscInitTypeDef RCCOscConfig = {0};
  RCC_ClkInitTypeDef RCCClkConfig = {0};
  GPIO_InitTypeDef   GpioConfig = {0};
  
  /* Config PA11 for external wakeup mode */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  GpioConfig.Pin  = GPIO_PIN_11;
  GpioConfig.Pull = GPIO_NOPULL;
  GpioConfig.Mode = GPIO_MODE_IT_RISING;
  HAL_GPIO_Init(GPIOA, &GpioConfig);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
  
  /* Clock source configuration */
  RCCClkConfig.ClockType = RCC_CLOCKTYPE_SYSCLK; /* Configure clock types SYSCLK */
  RCCClkConfig.SYSCLKSource = RCC_SYSCLKSOURCE_HSISYS; /* Select HSISYS as system clock */
  if (HAL_RCC_ClockConfig(&RCCClkConfig, FLASH_LATENCY_0) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  __HAL_RCC_USB_CLK_DISABLE();
  /* Pause systick */
  HAL_SuspendTick();

  /* VCORE = 0.8V  when enter stop mode */
  PwrStopModeConf.LPVoltSelection     =  PWR_STOPMOD_LPR_VOLT_0P8V;
  PwrStopModeConf.FlashDelay          =  PWR_WAKEUP_HSIEN_AFTER_MR;
  PwrStopModeConf.WakeUpHsiEnableTime =  PWR_WAKEUP_FLASH_DELAY_1US;
  HAL_PWR_ConfigStopMode(&PwrStopModeConf);

  /* Entering STOP mode */
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
  
  /* Restore systick */
  HAL_ResumeTick();
  __HAL_RCC_USB_CLK_ENABLE();
  
  RCCOscConfig.PLL.PLLState = RCC_PLL_ON;                       /* Enable PLL */
  RCCOscConfig.PLL.PLLSource = RCC_PLLSOURCE_HSI;               /* PLL source is HSI */
  RCCOscConfig.PLL.PLLMUL = RCC_PLL_MUL2;                       /* PLL multiplication factor is 2 */
  /* Configure oscillator */
  if (HAL_RCC_OscConfig(&RCCOscConfig) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* Clock source configuration */
  RCCClkConfig.ClockType = RCC_CLOCKTYPE_SYSCLK; /* Configure clock types SYSCLK */
  RCCClkConfig.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; /* Select PLL as system clock */
  if (HAL_RCC_ClockConfig(&RCCClkConfig, FLASH_LATENCY_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* Config PA11 for analog mode */
  GpioConfig.Pin  = GPIO_PIN_11;
  GpioConfig.Pull = GPIO_NOPULL;
  GpioConfig.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(GPIOA, &GpioConfig);

}

/**
  * @brief  USB peripheral initialization function
  * @param  None
  * @retval None
  */
static void APP_USBInit(void)
{
  GPIO_InitTypeDef   GpioConfig = {0};
  /* Enable USB pull up */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  GpioConfig.Pin  = GPIO_PIN_1;
  GpioConfig.Pull = GPIO_NOPULL;
  GpioConfig.Mode = GPIO_MODE_OUTPUT_OD;
  GpioConfig.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GpioConfig);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
  
  __HAL_RCC_USB_CLK_ENABLE();

  hid_keyboard_init();

  /* Enable USB interrupt */
  NVIC_EnableIRQ(USBD_IRQn);
}

/**
  * @brief  System clock configuration function
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* Oscillator configuration */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE; /* Select oscillators HSE, HSI, LSI, LSE */
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                           /* Enable HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                           /* HSI not divided */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_24MHz;  /* Configure HSI clock as 24MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                          /* Disable HSE */
  /*RCC_OscInitStruct.HSEFreq = RCC_HSE_16_32MHz;*/
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                          /* Disable LSI */
  RCC_OscInitStruct.LSEState = RCC_LSE_OFF;                          /* Disable LSE */
  /*RCC_OscInitStruct.LSEDriver = RCC_LSEDRIVE_MEDIUM;*/
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;                       /* Enable PLL */
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;               /* PLL source is HSI */
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;                       /* PLL multiplication factor is 2 */
  /* Configure oscillator */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* Clock source configuration */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1; /* Configure clock types HCLK, SYSCLK, PCLK1 */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; /* Select PLL as system clock */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;        /* AHB clock not divided */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;         /* APB clock not divided */
  /* Configure clock source */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  /* Infinite loop */
  while (1)
  {
  }
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
