/*!
  A header file that holds all definitions
  @author jhwoe48, Jackson Howe
 */

#ifndef DEF_H_INCLUDED
#define DEF_H_INCLUDED

    #include <stdbool.h>

    // Constants
    #define PAGESPERMINUTE 1
    #define MAXCYCLES 200
    #define MAXPAGES 30
    #define ITERATIONS 1000

    // Debug Statements
    #define DEBUG_LIST 0
    #define DEBU_ADDING 0
    #define DEBUG_PRINT_PROCESS 0
    #define DEBUG_SHOW_CYCLES 0
    #define DEBUG_SHOW_EXCEEDED 0

    // Create a structure that represents a print job
    typedef struct printJob {
        int docID;
        int reqPriority;
        int numPages;
        int numCycles;
    } JOB;

    // Create a structure that represents a node in the queue
    typedef struct node {
        struct printJob*   dataPtr;  // pointer to document structure
        struct node*       next;  
    } LIST_NODE;

    // Create a structure that represents a printer queue
    typedef struct list {
        struct node* head;
        int count;
    } LIST;

    // Function prototypes
    JOB* createJob();
    LIST* createQueue();
    bool insert(LIST*);
    void printQueue(LIST*);
    void printer(LIST*);
    void cycle(LIST*);
    void freeQueue(LIST*);

#endif