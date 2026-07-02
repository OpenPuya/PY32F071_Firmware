/**
  ******************************************************************************
  * @file    main.h
  * @author  MCU Application Team
  * @brief   Header for main.c file.
  *          This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx_hal.h"
#include "py32f071xx_Start_Kit.h"

/* Private includes ----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define NSS_PORT    GPIOB
#define NSS_PIN     GPIO_PIN_6

#define P25Q128_WRITE_ENABLE             0x06
#define P25Q128_WRITE_DISABLE            0x04
#define P25Q128_PAGE_PROGRAM             0x02
#define P25Q128_SECTOR_ERASE             0x20
#define P25Q128_READ_DATA                0x03
#define P25Q128_READ_STATUS_REGISTER     0x05

#define BLOCK_SIZE  4096
#define DISK_PAGE_SIZE 256

typedef enum {
  SPI_UNLOCKED= 0,
  SPI_LOCKED,
} SPIState;

/* Exported variables prototypes ---------------------------------------------*/
extern SPI_HandleTypeDef hSPI1;
extern uint8_t USBconfState;

/* Exported functions prototypes ---------------------------------------------*/
void APP_ErrorHandler(void);
void APP_P25Q128_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count);
void APP_P25Q128_SectorErase(uint32_t Address);
void APP_P25Q128_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count);
void SPILock(void);
void SPIUnlock(void);
SPIState SPIIsLocked(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
