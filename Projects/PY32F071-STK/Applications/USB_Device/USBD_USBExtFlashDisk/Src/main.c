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
#include "ff.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hSPI1;
FATFS fs;                         /* FatFs File system object.*/
FIL fnew;                         /* File object. */
FRESULT res_flash;                /* File operation result. */
UINT fnum;                        /* Number of files successfully read/written. */
BYTE ReadBuffer[1024]= {0};       /* Read buffer. */
uint8_t USBconfState = 0;
static __IO SPIState SPILockState = SPI_UNLOCKED;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_USBInit(void);
static void APP_SPIInit(void);

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
  
  BSP_USART_Config();
  printf("\r\n****** This is an FLASH file system experiment. ******\r\n");
  
  /* Initialize SPI peripheral */
  APP_SPIInit();

  /* Initialize USB peripheral */
  APP_USBInit();

  while(USBconfState == 0);

  /* Mount the file system on the external SPI Flash. The SPI device will be initialized during the file system mounting process. */
  res_flash = f_mount(&fs,"1:",1);

  /*------------------ File system test: Read test.--------------------------*/
  printf("****** About to conduct a file reading test.... ******\r\n");
  res_flash=f_open(&fnew,"1:Test.txt",FA_OPEN_EXISTING|FA_READ);
  if (res_flash == FR_OK) {
      printf("The file has been successfully opened.\r\n");
      res_flash = f_read(&fnew, ReadBuffer, sizeof(ReadBuffer), &fnum);
      if (res_flash==FR_OK) {
          printf("File read successfully. Bytes read:%d\r\n",fnum);
          printf("The data read from the file is:\r\n%s \r\n", ReadBuffer);
      } else {
          printf("File read failed:(%d)\n",res_flash);
      }
  } else {
      printf("Failed to open the file.\r\n");
  }
  /* No more reading or writing. Close the file. */
  f_close(&fnew);
  
  /* No longer use the file system. Unmount the file system. */
  f_mount(NULL,"1:",1);
  
  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  USB peripheral initialization function
  * @param  None
  * @retval None
  */
static void APP_USBInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();

  __HAL_RCC_USB_CLK_ENABLE();

  msc_ram_init();

  /* Enable USB interrupt */
  NVIC_EnableIRQ(USBD_IRQn);
}

/**
  * @brief  SPI peripheral initialization function
  * @param  None
  * @retval None
  */
static void APP_SPIInit(void)
{
  /*Deinitialize SPI configuration*/
  hSPI1.Instance               = SPI1;                       /* SPI1 */
  hSPI1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;   /* Prescaler: 16 */
  hSPI1.Init.Direction         = SPI_DIRECTION_2LINES;       /* Full-duplex */
  hSPI1.Init.CLKPolarity       = SPI_POLARITY_LOW;           /* Clock polarity: Low */
  hSPI1.Init.CLKPhase          = SPI_PHASE_1EDGE ;           /* Data sampling on the first clock edge */
  hSPI1.Init.DataSize          = SPI_DATASIZE_8BIT;          /* SPI data size: 8-bit */
  hSPI1.Init.FirstBit          = SPI_FIRSTBIT_MSB;           /* MSB transmitted first */
  hSPI1.Init.NSS               = SPI_NSS_SOFT;               /* NSS software mode */
  hSPI1.Init.Mode = SPI_MODE_MASTER;                         /* Configured as master */
  hSPI1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;    /* The CRC check is disabled */
  if (HAL_SPI_DeInit(&hSPI1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* SPI initialization */
  if (HAL_SPI_Init(&hSPI1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

void SPILock(void)
{
  SPILockState = SPI_LOCKED;
}

void SPIUnlock(void)
{
  SPILockState = SPI_UNLOCKED;
}

SPIState SPIIsLocked(void)
{
  return SPILockState;
}

/**
  * @brief  This function transmit one byte.
  * @param  pTxData: pointer to transmission data buffer
  * @retval None
  */
static void APP_SPITransmit(uint8_t *pTxData)
{
  uint8_t temp = 0;
  if (HAL_SPI_TransmitReceive(&hSPI1, pTxData, &temp, 1, 100) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  This function receive one byte.
  * @param  pRxData: pointer to reception data buffer
  * @retval None
  */
static void APP_SPIReceive(uint8_t *pRxData)
{
  uint8_t temp = 0xFF;
  if (HAL_SPI_TransmitReceive(&hSPI1, &temp, pRxData, 1, 100) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  Read flash status reg.
  * @param  None
  * @retval Flash status reg value
  */
static uint8_t GetStatus(void)
{
  uint8_t cmd = 0;
  uint8_t status;
  
  /*Pull down NSS*/
  HAL_GPIO_WritePin(NSS_PORT, NSS_PIN, GPIO_PIN_RESET);
  
  /*Send read status register instruction*/
  cmd = P25Q128_READ_STATUS_REGISTER;
  
  APP_SPITransmit(&cmd);
  
  /*Read flash status reg*/
  APP_SPIReceive(&status);
  
  /*Pull up NSS*/
  HAL_GPIO_WritePin(NSS_PORT, NSS_PIN, GPIO_PIN_SET);
  
  return status;
}

/**
  * @brief  Send write enale instruction.
  * @param  None
  * @retval None
  */
static void WriteEnable(void)
{
  uint8_t cmd = 0;
  
  /*Pull down NSS*/
  HAL_GPIO_WritePin(NSS_PORT, NSS_PIN, GPIO_PIN_RESET);
  
  /*Write enable*/
  cmd = P25Q128_WRITE_ENABLE;
  
  APP_SPITransmit(&cmd);
  
  /*Pull up NSS*/
  HAL_GPIO_WritePin(NSS_PORT, NSS_PIN, GPIO_PIN_SET);
  
  /* Wait for the operation to complete. */
  while((GetStatus() & 0x01) != 0);

}

/**
  * @brief  Write an amount of data
  * @param  Address page address
  * @param  DataArray Data to be written
  * @param  Count Number of bytes
  * @retval None
  */
void APP_P25Q128_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count)
{
  uint8_t cmd[3] = {0};
  uint8_t *pbuf = DataArray;
  uint32_t txcnt = Count;
  
  WriteEnable();
  
  /*Pull down NSS*/
  HAL_GPIO_WritePin(NSS_PORT, NSS_PIN, GPIO_PIN_RESET);
  
  /*Send write instruction*/
  cmd[0] = P25Q128_PAGE_PROGRAM;
  
  APP_SPITransmit(&cmd[0]);
  
  /*Send address*/
  cmd[0] = (uint8_t)(Address >> 16);
  cmd[1] = (uint8_t)(Address >> 8);
  cmd[2] = (uint8_t)Address;
  APP_SPITransmit(&cmd[0]);
  APP_SPITransmit(&cmd[1]);
  APP_SPITransmit(&cmd[2]);
  
  /* Write data */
  while(txcnt > 0)
  {
    APP_SPITransmit(pbuf);
    pbuf++;
    txcnt--;
  }
  
  /*Pull up NSS*/
  HAL_GPIO_WritePin(NSS_PORT, NSS_PIN, GPIO_PIN_SET);
  
  /* Wait for the operation to complete. */
  while((GetStatus() & 0x01) != 0);

}

/**
  * @brief  Erases data in the specified Sector
  * @param  Address Sector address
  * @retval None
  */
void APP_P25Q128_SectorErase(uint32_t Address)
{
  uint8_t cmd[3] = {0};
  
  WriteEnable();

  /*Pull down NSS*/
  HAL_GPIO_WritePin(NSS_PORT, NSS_PIN, GPIO_PIN_RESET);
  
  /*Send erase instruction*/
  cmd[0] = P25Q128_SECTOR_ERASE;
  
  APP_SPITransmit(&cmd[0]);
  
  /*Send address*/
  cmd[0] = (uint8_t)(Address >> 16);
  cmd[1] = (uint8_t)(Address >> 8);
  cmd[2] = (uint8_t)Address;
  APP_SPITransmit(&cmd[0]);
  APP_SPITransmit(&cmd[1]);
  APP_SPITransmit(&cmd[2]);
  
  /*Pull up NSS*/
  HAL_GPIO_WritePin(NSS_PORT, NSS_PIN, GPIO_PIN_SET);
  
  /* Wait for the operation to complete. */
  while((GetStatus() & 0x01) != 0);
  
}
  
/**
  * @brief  Read an amount of data
  * @param  Address start address
  * @param  DataArray Data being read out
  * @param  Count Number of bytes
  * @retval None
  */
void APP_P25Q128_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
  uint8_t cmd[3] = {0};
  uint8_t *pbuf = DataArray;
  uint32_t rxcnt = Count;
  
  WriteEnable();
  
  /*Pull down NSS*/
  HAL_GPIO_WritePin(NSS_PORT, NSS_PIN, GPIO_PIN_RESET);
  
  /*Send read instruction*/
  cmd[0] = P25Q128_READ_DATA;
  APP_SPITransmit(&cmd[0]);
  
  /*Send address*/
  cmd[0] = (uint8_t)(Address >> 16);
  cmd[1] = (uint8_t)(Address >> 8);
  cmd[2] = (uint8_t)Address;
  APP_SPITransmit(&cmd[0]);
  APP_SPITransmit(&cmd[1]);
  APP_SPITransmit(&cmd[2]);
  
  /*read data*/
  while(rxcnt > 0)
  {
    APP_SPIReceive(pbuf);
    pbuf++;
    rxcnt--;
  }
  
  /*Pull up NSS*/
  HAL_GPIO_WritePin(NSS_PORT, NSS_PIN, GPIO_PIN_SET);

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
