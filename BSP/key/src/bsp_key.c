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

