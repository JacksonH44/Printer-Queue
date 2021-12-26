#include "headers.h"

/*!
  A function that dynamically creates a job in preparation to be put into the printer queue
  @author jhowe48, Jackson Howe

  @return job, new printer job
 */
JOB* createJob(void)
{
    JOB* newJob = (JOB*)malloc(sizeof(JOB));  // Dynamically allocate memory
    static int ID = 1;
    newJob->docID = ID;  // ID is a static variable
    ID++;
    
    int r = rand() % 100;

    // Generate a pseudorandom integer from 0 - 99 
    int y;
    if (r < 10)  // 10% chance
    {
        y = 1;
    }
    else if (r < 80)  // 70% chance
    {
        y = 2;
    }
    else  // 20% chance
    {
        y = 3;
    }

    newJob->reqPriority = y;  // Assign priority based on probability

    // Determine number of pages
    int pInt = (rand() % MAXPAGES) + 1;
    newJob->numPages = pInt;
    
    // Set cycles to zero
    newJob->numCycles = 0;
}

/*!
  A function that inserts a job into the printer queue in the correct order based on job attributes
  @author jhowe48, Jackson Howe

  @param queue, the printer queue

  @return true if the insertion was successful, false otherwise
 */
bool insert (LIST* queue)
{
    // Create a new node
    JOB* itemPtr = createJob();

    LIST_NODE* newPtr;
    if (!(newPtr = (LIST_NODE*)malloc(sizeof(LIST_NODE*))))
    {
        return false;
    }

    // Assign the new node's data with the itemPtr and update count
    newPtr->dataPtr = itemPtr;
    (queue->count)++;

    // If the debug is on, print out when a document is added
    #if DEBUG_ADDING
        printf("Adding to Queue - Doc: %d NoPages: %d Priority: %d\n", itemPtr->docID, itemPtr->numPages, itemPtr->reqPriority);
    #endif

    // If the list is empty make the new node the list's head
    if (queue->head == NULL)
    {
        newPtr->next = queue->head;
        queue->head = newPtr;
    }

    // If the list is not empty
    else
    {
        // One node that will point to the current node in the iteration,
        // one that will point to the previous node, and a boolean that will
        // indicate if the node has been placed
        LIST_NODE* current = queue->head;
        LIST_NODE* prev = NULL;
        bool placed = false;

        // While not at the end of the list and the node hasn't been placed
        while (current != NULL && !placed)
        {
            if (current->dataPtr->reqPriority < newPtr->dataPtr->reqPriority) // Go to next link
            {
                prev = current;
                current = current->next;
            }
            // Priority is the same
            else if (current->dataPtr->reqPriority = newPtr->dataPtr->reqPriority)
            {
                if (current->dataPtr->numPages <= newPtr->dataPtr->numPages)  // Go to next link
                {
                    prev = current;
                    current = current->next;
                }
                else  // Has fewer pages than the current node
                {
                    placed = true;
                }
            }
            else  // Priority is lower than the current node
            {
                placed = true;
            }
        }
        if (prev == NULL)  // Inserting at the head
        {
            newPtr->next = current;
            queue->head = newPtr;
        }
        else // Insert in the middle
        {
            newPtr->next = current;
            prev->next = newPtr;
        }
    }
    return true;
}  // Insert queue