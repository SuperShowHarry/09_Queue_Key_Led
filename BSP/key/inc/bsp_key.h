/***************************************************************************
 *
 * Copyright (C) 2024 EternalChip, Inc.(Gmbh) or its affiliates.
 *
 * All Rights Reserved.
 *
 * @file key.h
 *
 * @par dependencies
 * - bsp_key.h
 * - stdio.h
 * - stdint.h
 *
 * @author Xyp | R&D Dept. | EternalChip 立芯嵌入式
 *
 * @brief Provide the HAL APIs of key and corresponding opetions.
 *
 * Processing flow:
 *
 * call directly.
 *
 * @version V1.0 2026-10-23
 *
 * @note 1 tab == 4 spaces!
 *
 ***************************************************************************/
 #ifndef __BSP_KEY_H__
 #define __BSP_KEY_H__
/****************************** Includes ******************************/
#include <stdint.h>                   // the compiling lib
#include <stdio.h>

#include "main.h"											//Core / OS layer
#include "cmsis_os.h"

#include "queue.h"										//specific file for operation
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
/****************************** Includes ******************************/
 
 //******************************* Defines ********************************//
 //************* thread *************//
extern osThreadId_t key_TaskHandle;
extern const osThreadAttr_t key_Task_attributes;
//************* thread *************//
 
//************* queue *************//
extern QueueHandle_t key_queue;
//************* queue *************//
 
/*  函数返回状态枚举                       */
typedef enum
{
    KEY_OK              = 0,          /* Operation completed successfully.  */
    KEY_ERROR           = 1,          /* Run-time error without case matched*/
    KEY_ERRORTIMEOUT    = 2,          /* Operation failed with timeout      */
    KEY_ERRORRESOURCE   = 3,          /* Resource not available.             */
    KEY_ERRORPARAMETER  = 4,          /* Parameter error.                    */
    KEY_ERRORNOMEMORY   = 5,          /* Out of memory.                      */
    KEY_ERRORISR        = 6,          /* Not allowed in ISR context          */
    KEY_RESERVED        = 0x7FFFFFFF  /* Reserved                            */
} key_status_t;

typedef enum
{
    KEY_PRESSED         = 0,          /* Operation completed successfully.  */
    KEY_NOT_PRESSED     = 1,          /* Run-time error without case matched*/
	  KEY_SHORT_PRESSED   = 2,
		KEY_LONG_PRESSED 		= 3,
} key_press_status_t;
//******************************* Defines ********************************//
//******************************* Declaring *******************************//
 key_status_t key_scan(key_press_status_t * key_value);

 key_status_t key_scan_short_long_press(key_press_status_t * key_value, uint32_t short_press_time);

void key_task_Func(void *argument);
//******************************* Declaring *******************************//
 
 #endif

