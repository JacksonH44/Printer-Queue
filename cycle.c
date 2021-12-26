/*!
  A function that updates the cycles in the print queue
  @author jhowe48, Jackson Howe

  @param queue, the printer queue
 */

#include "headers.h"

void cycle(LIST* queue)
{
    LIST_NODE* current = queue->head;
    LIST_NODE* prev = NULL;

    // Iterate through the list
    while (current != NULL)
    {
        // Increment the number of cycles
        current->dataPtr->numCycles++;

        #if DEBUG_SHOW_CYCLES
            printf("Increment Cycle - Document: %d Pages: %d Priority: %d Cycle Count: %d\n", current->dataPtr->docID,
                current->dataPtr->numPages, current->dataPtr->reqPriority, current->dataPtr->numCycles);
        #endif

        // The equality sign ensures that a statement is only printed out once, if at all
        if (current->dataPtr->numCycles == MAXCYCLES)
        {
            #if DEBUG_SHOW_EXCEEDED
                printf("EXCEEDED CYCLE COUNT - Document: %d   Pages: %d   Priority: %d   Cycle Count: %d\n", current->dataPtr->docID,
                current->dataPtr->numPages, current->dataPtr->reqPriority, current->dataPtr->numCycles);
            #endif
            current->dataPtr->reqPriority = 0;  // BONUS: Switch the priority to 0
            if (prev == NULL)
            {
                // Do nothing, the node is already at the front of the list
            }
            else
            {
                prev->next = current->next;  // Remove node
                current->next = queue->head;  // Point node in question to the front of the queue

                // Declare two new traversing nodes
                LIST_NODE* newPrev = NULL;
                LIST_NODE* newCurrent = queue->head;
                
                // Traverse over all other emergency priority nodes
                while (current->dataPtr->reqPriority == newCurrent->dataPtr->reqPriority)
                {
                    newPrev = newCurrent;
                    newCurrent = newCurrent->next;
                }

                if (newPrev == NULL)  // Front of the queue
                {
                    queue->head = current;  // Point the head of the queue to current
                }
                else  // Insert the node
                {
                    newPrev->next = current;
                    current->next = newCurrent->next;
                }
            }
        }
        // Traverse over the rest of the list, after all emergency cycles have been taken care of
        prev = current;
        current = current->next;
    }
}