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
 * @author Xyp | R&D Dept. | EternalChip ��оǶ��ʽ
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
 #include "bsp_led.h"
  osThreadId_t led_TaskHandle;
  QueueHandle_t led_queue;
 
  //******************************* Global_Var ********************************//
 static uint32_t g_blink_times = 0;	//1:blink 1, 5:blink 5
 static uint32_t g_blink_order = 0;
 //******************************* Global_Var ********************************//
 
 const osThreadAttr_t led_Task_attributes = {
  .name = "led_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/**
 * @brief Instantiates the bsp_led_handler_t target.
 *
 * Steps:
 *  1. Adds Core interfaces into bsp_led_driver instance target.
 *  2. Adds OS interfaces into bsp_led_driver instance target.
 *  3. Adds timebase interfaces into bsp_led_driver instance target.
 *
 * @param[in] self        : Pointer to the target of handler.
 * @param[in] os_delay    : Pointer to the os_delay_interface.
 * @param[in] os_queue    : Pointer to the os_queue_interface.
 * @param[in] os_critical : Pointer to the os_critical_interface.
 * @param[in] os_thread   : Pointer to the os_thread_interface.
 * @param[in] time_base   : Pointer to the time_base_interface.
 *
 * @return led_handler_status_t : Status of the function.
 *
 */
led_status_t led_on_off(led_operation_t led_operation)
{
	led_status_t ret = LED_OK;
	
	if(LED_ON == led_operation)
	{
		//1.Make the LED ON
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
	}
	
	if(LED_OFF == led_operation)
	{
		//2.Make the LED OFF
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	}
	
	if(LED_TOGGLE == led_operation)
	{
		//2.Make the LED TOGGLE
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	}
	
	if(LED_BLINK_3_TIMES == led_operation)
	{
		//1.Make the LED bilnk 3 times
		for(int i = 0; i < 6; i++)
		{
			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
			vTaskDelay(300);
		}
	}
	
	return ret;
}

/**
 * @brief Instantiates the bsp_led_handler_t target.
 *
 * Steps:
 *  1. Adds Core interfaces into bsp_led_driver instance target.
 *  2. Adds OS interfaces into bsp_led_driver instance target.
 *  3. Adds timebase interfaces into bsp_led_driver instance target.
 *
 * @param[in] self        : Pointer to the target of handler.
 * @param[in] os_delay    : Pointer to the os_delay_interface.
 * @param[in] os_queue    : Pointer to the os_queue_interface.
 * @param[in] os_critical : Pointer to the os_critical_interface.
 * @param[in] os_thread   : Pointer to the os_thread_interface.
 * @param[in] time_base   : Pointer to the time_base_interface.
 *
 * @return led_handler_status_t : Status of the function.
 *
 */
led_status_t led_on_off_timer_irq(led_operation_t led_operation)
{
	led_status_t ret = LED_OK;
	
//	if(LED_ON == led_operation)
//	{
//		//1.Make the LED ON
//		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
//	}
//	
//	if(LED_OFF == led_operation)
//	{
//		//2.Make the LED OFF
//		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
//	}
	
//	if(LED_TOGGLE == led_operation)
//	{
//		//2.Make the LED TOGGLE
//		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//	}
	
	if(LED_BLINK_1_TIMES == led_operation)
	{
		g_blink_times = 1;	//1:blink 1, 5:blink 5
		g_blink_order = 0;
	}
	else if(LED_BLINK_3_TIMES == led_operation)
	{
		g_blink_times = 3;	//1:blink 1, 5:blink 5
		g_blink_order = 0;
	}
	else if(LED_BLINK_10_TIMES == led_operation)
	{
		g_blink_times = 10;	//1:blink 1, 5:blink 5
		g_blink_order = 0;
		
		
	}
	return ret;
}

  /**
 * @brief key thread function.
 * @param void *argument  
 * @return void
 *
 */
void led_task_Func(void *argument)
{
	led_status_t led_ret = LED_OK;
	led_operation_t led_value = LED_ON;
	led_queue = xQueueCreate( 10, sizeof( led_operation_t ));
	
	if(led_queue == NULL)
	{
		printf("key_queue created failed\r\n");
	}
	else
	{
		printf("key_queue created successfully\r\n");
	}
		
	for(;;)
	{
		printf("Hello led thread\r\n");
		
		if( led_queue != 0 )
		{
			// Receive a message on the created queue.  Block for 10 ticks if a
			// message is not immediately available.
			if(pdTRUE == xQueueReceive( led_queue, &( led_value ), ( TickType_t ) 0) )
			{
				// pcRxedMessage now points to the struct AMessage variable posted
				// by vATask.
				printf("received led_queue value = [%d] at time [%d]\r\n", led_value, HAL_GetTick());
				led_ret = led_on_off_timer_irq(led_value);
				if(LED_OK == led_ret)
				{
					printf("led_on_off successfully at time [%d]\r\n", HAL_GetTick());
				}	
			}
		}
		
		osDelay(100);
	}
}

/**
 * @brief led callback in timer2 for timer to run.
 *
 * Steps:
 *  1. doing the specific operation
 *
 * @param[in] void
 *
 * @return led handler status t : status of the function
 *
 */
led_status_t led_callback_in_timer(void)
{
	//1. if the g_blink_times is not zero, then start blink
	if(g_blink_times > 0)
	{
		if(g_blink_order %2 == 0)
		{
			led_on_off(LED_ON);
		}
		else
		{
			led_on_off(LED_OFF);
			g_blink_times--;
		}
		g_blink_order++;
		
		if(!g_blink_times)
		{
			g_blink_times = 0;
			g_blink_order = 0;
		}
	}
	return LED_OK;
}
	

