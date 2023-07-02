#ifndef _APP_H_ /* _APP_H_ */
#define _APP_H_ /* _APP_H_ */

#include <stdint.h>

#define APP_VECTOR_TABLE_OFFSET  ((uint32_t)0x08003000)
#define sw1   HAL_GPIO_Read_Pin(GPIOA,GPIO_Pin_2)
/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 *@brief function init button,uart0, queue
 *@param
 */
void app_init(void);   

/*!
 *@brief function jump to Boot
 *@param
 */
void jump_To_Boot(void);

/*!
 *@brief function jump to App
 *@param
 */
void Jump_To_App(void);

#endif /* _APP_H_ */
