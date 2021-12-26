/*!
  A function that controls the whole program
  @author jhowe48, Jackson Howe

  @return 0 if the execution was successful, non-zero integer if not
 */
#include <stdio.h>
#include "headers.h"

int main(void)
{
    LIST* queue = createQueue();

    // We have a 1 in 10 chance of creating a new job
    for (int i = 0; i < ITERATIONS; i++)
    {
        int random = rand() % 100;
        if (random < 10)
        {
            // Insert the new job into the queue
            insert(queue);
        }
        // Process the print queue (no matter if a new job was added or not)
        printer(queue);
        #if DEBUG_LIST
            printQueue(queue);
        #endif
    }
    // End the program
    printf("End of Program - Jackson Howe\n");
    printf("Number of printer jobs left in the queue: %3d\n", queue->count);
    freeQueue(queue);
    return 0;
}