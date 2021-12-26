#include "headers.h"

/*!
  A function that prints out the printer queue if debugging mode is on
  @author jhowe48, Jackson Howe

  @param queue, the printer queue
 */
void printQueue (LIST* queue)  // A function that is called if DEBUG_LIST is set to 1
{
    LIST_NODE* currentNode = queue->head;
    if (currentNode == NULL)  // Queue is empty
    {
        printf("EMPTY QUEUE - no print jobs currently in queue\n");
    }
    else
    {
        printf("Current Printer Queue Size: %3d\n", queue->count);  // Displays size
        while (currentNode != NULL)  // Iterate through the list 
        {
            // Print list info
            printf("Current Printer Queue : DocNum: %3d NumofPages %3d PriorityLevel %3d NumOfCycles %3d\n", 
            currentNode->dataPtr->docID, currentNode->dataPtr->numPages, currentNode->dataPtr->reqPriority, currentNode->dataPtr->numCycles);
            currentNode = currentNode->next;
        }
        printf("END OF LIST\n\n");
    }
}

/*!
  A function that acts as a printer (in somewhat of an OOP sense) that will print out the current print job
  @author jhowe48, Jackson Howe

  @param queue, the printer queue
 */
void printer(LIST* queue)
{
    static LIST_NODE* currentPrint = NULL;  // Declare a static print document so the document doesn't need to be passed 
    if (currentPrint == NULL)  // There's no print job in the printer
    {
        currentPrint = queue->head;  // Get the next print job waiting
        if (currentPrint != NULL)
        {
            queue->head = currentPrint->next;  // Update the queue
            (queue->count)--;

            #if DEBUG_PRINT_PROCESS
                printf("PRINTING - DOCUMENT: %d   PAGE: %d  priority: %d\n", currentPrint->dataPtr->docID, currentPrint->dataPtr->numPages, currentPrint->dataPtr->reqPriority);
            #endif

            currentPrint->dataPtr->numPages = currentPrint->dataPtr->numPages - PAGESPERMINUTE;  // Decrement the pages left to be printed
            if (currentPrint->dataPtr->numPages <= 0)  // The document is finished printing
            {
                printf("Print Job Completed - DocumentNumber: %d   -   Cycle Count: %d\n", currentPrint->dataPtr->docID, currentPrint->dataPtr->numCycles);
                free(currentPrint->dataPtr);
                currentPrint = NULL;
            }
        }
    }
    else  // There is already a print job waiting to be finished
    {
        currentPrint->dataPtr->numPages = currentPrint->dataPtr->numPages - PAGESPERMINUTE;  // Decrement the pages left to be printed
        if (currentPrint->dataPtr->numPages <= 0)  // The document is finished printing
            {
                printf("Print Job Completed - DocumentNumber: %d   -   Cycle Count: %d\n", currentPrint->dataPtr->docID, currentPrint->dataPtr->numCycles);
                currentPrint = NULL;
            }
    }
    // Update the remaining printer cycles
    cycle(queue);
}