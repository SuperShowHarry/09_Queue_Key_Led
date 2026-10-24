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
 #include "bsp_key.h"
 
 osThreadId_t key_TaskHandle;
 QueueHandle_t key_queue;
 
const osThreadAttr_t key_Task_attributes = {
  .name = "key_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
 
 key_status_t key_scan(key_press_status_t * key_value)
 {
	 uint32_t counter = 0;
	 key_press_status_t key_status_value = KEY_NOT_PRESSED;
	 
		while(counter < 1000)
		{
			//2.如果按键（PA0)的电平为低，则说明按键被按下了。
			//2.1 如果按键被按下，则发送对应的消息队列
			if(HAL_GPIO_ReadPin(Key_GPIO_Port, Key_Pin) == GPIO_PIN_RESET)
			{
				key_status_value = KEY_PRESSED;
				*key_value = key_status_value;
				return KEY_OK;
					// //2.1 LED亮起
					// HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
					// //2.2 延时500ms
					// HAL_Delay(500);
					// //2.3 LED熄灭
					// HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
					// //2.4 延时500ms
					// HAL_Delay(500);
			}
			//2.2如果按键没有被按下
			counter++;
		}
		*key_value = key_status_value;
		return KEY_ERRORTIMEOUT;	//始终没有按键按下返回超时
 }

  /**
 * @brief key thread function.
 * @param void *argument  
 * @return void
 *
 */
void key_task_Func(void *argument)
{
	key_status_t key_ret = KEY_OK;
	key_press_status_t key_status = KEY_NOT_PRESSED;
	key_queue = xQueueCreate( 10, sizeof( key_press_status_t ));
	uint32_t send_value = 0;
	
	if(key_queue == NULL)
	{
		printf("key_queue created failed\r\n");
	}
	else
	{
		printf("key_queue created successfully\r\n");
	}
		
	for(;;)
	{
		//printf("Hello key thread\r\n");
		send_value++;
		key_ret = key_scan(&key_status);
		
		if(KEY_OK == key_ret)
		{
			if(KEY_PRESSED == key_status)
			{
				printf("Key_Pressed\r\n");
				if(pdTRUE == xQueueSend(key_queue,&send_value,0))
				{
					printf("send successfully\r\n");
				}
			}
		}
		if(KEY_OK != key_ret)
		{
//			printf("Key_not_Pressed\r\n");
		}
		
		osDelay(10);
	}
}

