#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "queue.h"

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
uint16_t dataIndex = 0;

queue_struct_t s_queueList;

/* fuction initiallize a queue with no data*/
void queue_init(void)
{
    s_queueList.getIndex = 0;
    s_queueList.putIndex = 0;
    s_queueList.size = 0;
}


/* Check if queue is empty or not */
bool queue_isEmpty()
{
    bool returnValue = false;
    if(s_queueList.size == 0)
    {
        returnValue = true;
    }

    return returnValue;
}

/* Check if queue is full or not */
bool queue_isFull(void)
{
    bool returnValue = false;
    if(s_queueList.size == MAX_QUEUE_SIZE)
    {
        returnValue = true;
    }

    return returnValue;
}

/*function increase index and size when put data to queue*/
bool queue_put_newLine(void)
{
    bool val = true;
    if(queue_isFull() == false) /*if queue list not full*/
    {
        s_queueList.putIndex++;
        s_queueList.size++;
        dataIndex=0;
    }
    else
    {
        val = false;
    }

    return val;
}

/*function increase index and reduce size when get data from queue*/
bool queue_get(void)
{
    bool val = true;
    if(queue_isEmpty() == false) /*if queue list not empty*/
    {
        s_queueList.getIndex++;
        s_queueList.size--;
    }
    else
    {
        val = false;
    }

    return val;
}


/* function push data to each line */ 
void queue_push_data(uint8_t data)
{
    uint8_t putIndex = 0xFF;
    putIndex = s_queueList.putIndex % MAX_QUEUE_SIZE;
    s_queueList.queue_data[putIndex][dataIndex] = data;
    dataIndex++;
}

/* fuction pop data line in order to parse data */
uint8_t* queue_pop(void)
{
    uint8_t *ptrReturn;
    uint8_t getIndex = 0xFF;
    getIndex = s_queueList.getIndex % MAX_QUEUE_SIZE;
    ptrReturn = s_queueList.queue_data[getIndex];

    return ptrReturn;
}
