/***************************************************************************
 *
 * Copyright (C) 2024 EternalChip, Inc.(Gmbh) or its affiliates.
 *
 * All Rights Reserved.
 *
 * @file led.h
 *
 * @par dependencies
 * - bsp_led.h
 * - stdio.h
 * - stdint.h
 *
 * @author Xyp | R&D Dept. | EternalChip 锟斤拷芯嵌锟斤拷式
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
 #ifndef __BSP_LED_H__
 #define __BSP_LED_H__
/****************************** Includes ******************************/
#include <stdint.h>                   // the compiling lib
#include <stdio.h>

#include "main.h"											//Core / OS layer
#include "cmsis_os.h"
#include "queue.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
/****************************** Includes ******************************/
 
 //******************************* Defines ********************************//

 //************* thread *************//
extern osThreadId_t led_TaskHandle;
extern const osThreadAttr_t led_Task_attributes;
//************* thread *************//
 
//************* queue *************//
extern QueueHandle_t led_queue;
//************* queue *************//
//******************************* Defines ********************************//
//******************************* Declaring *******************************//
/*  function resturn status                       */
typedef enum
{
    LED_OK              = 0,          /* Operation completed successfully.  */
    LED_ERROR           = 1,          /* Run-time error without case matched*/
    LED_ERRORTIMEOUT    = 2,          /* Operation failed with timeout      */
    LED_ERRORRESOURCE   = 3,          /* Resource not available.             */
    LED_ERRORPARAMETER  = 4,          /* Parameter error.                    */
    LED_ERRORNOMEMORY   = 5,          /* Out of memory.                      */
    LED_ERRORISR        = 6,          /* Not allowed in ISR context          */
    LED_RESERVED        = 0x7FFFFFFF  /* Reserved                            */
} led_status_t;

typedef enum
{
    LED_ON              = 0,          /* Operation completed successfully.  */
    LED_OFF             = 1,          /* Operation completed successfully.  */
		LED_TOGGLE          = 2,          /* Operation completed successfully.  */
		LED_BLINK_1_TIMES		= 3,
		LED_BLINK_3_TIMES		= 4,
		LED_BLINK_10_TIMES	= 5,
		LED_INITED_VALUE		= 0XFF,
} led_operation_t;
//******************************* Declaring *******************************//
//******************************* Declaring *******************************//
led_status_t led_on_off(led_operation_t led_operation);
void led_task_Func(void *argument);

extern led_status_t led_callback_in_timer(void);
//******************************* Declaring *******************************//
 #endif

