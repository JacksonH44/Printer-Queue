/*!
  A function that frees the memory associated with a printer queue
  @author jhwoe48, Jackson Howe

  @param queue, printer queue
 */
#include "headers.h"

void freeQueue(LIST* queue)
{
    // Declare traversing nodes
    LIST_NODE* current = queue->head;
    LIST_NODE* next;

    // Iterate through the list and free memory
    while (current != NULL)
    {
        next = current->next;
        free(current->dataPtr);
        free(current);
        current = next;
    }

    queue->head = NULL;

    // Free the memory associated with the queue itself
    free(queue);
}