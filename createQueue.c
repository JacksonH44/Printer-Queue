/*!
  A function that creates a new printer queue
  @author jhwoe48, Jackson Howe
  
  @return queue, a printer queue
 */
#include "headers.h"

LIST* createQueue(void)
{
    LIST* queue;
    queue = (LIST*)malloc(sizeof(LIST));

    if (queue)  // There were no errors in memory allocation
    {
        // Initialize queue
        queue->head = NULL;
        queue->count = 0;
    }
    return queue;
}  // Create queue