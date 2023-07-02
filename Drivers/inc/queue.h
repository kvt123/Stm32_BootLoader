#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include <stdint.h>


/*******************************************************************************
* Definitions
******************************************************************************/
#define MAX_DATA_SREC_SIZE   524
#define MAX_QUEUE_SIZE       4

/*******************************************************************************
* Struct
******************************************************************************/
struct queue
{
    uint8_t getIndex;
    uint8_t putIndex;
    uint8_t size;
    uint8_t queue_data[MAX_QUEUE_SIZE][MAX_DATA_SREC_SIZE];
};
typedef struct queue queue_struct_t;

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 *@brief fuction initiallize a queue with no data 
 *@param
 */
void queue_init(void);

/*!
 *@brief Check if queue is empty or not
 *@param
 */
bool queue_isEmpty(void);

/*!
 *@brief Check if queue is full or not
 *@param
 */
bool queue_isFull(void);

/*!
 *@brief function increase index and size when put data to queue
 *@param
 */
bool queue_put_newLine(void);

/*!
 *@brief function increase index and reduce size when get data from queue
 *@param
 */
bool queue_get(void);

/*!
 *@brief function push data to each line
 *@param
 */
void queue_push_data(uint8_t data);

/*!
 *@brief fuction pop data line in order to parse data
 *@param
 */
uint8_t* queue_pop(void);

#endif /* _QUEUE_H_ */
