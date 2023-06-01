#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* define a set element as a struct */
typedef struct SetElement {
    char data[51];
    struct SetElement* next;
} SET;

/* helper function to print action menu */
void printMenu();

/* helper function to add a string to a set*/
void addNode(SET** , char*);

/* helper function to print a set */
void print(SET* );

/* helper function to print all non-empty sets */
void printSets(SET**, int );

/* helper function to clear a set */
void clear(SET** );

/* helper function to copy sets */
void copy(SET** , SET** );

/* helper function to remove a string from a set */
void removeNode(SET** , char* );

/* helper function to perform union of two sets */
void unionSets(SET** , SET** , SET** );

/* helper function to perform intersection of two sets */
void intersection(SET** , SET** , SET** );

/* helper function to perform symmetric difference of two sets */
void symmetricdifference(SET** , SET** , SET** );

int main (int argc, char* argv[]) {
    
    /* array of pointers to sets (linked lists) */
    SET** headElements = NULL; 

    /* generic linked list pointer */
    SET* ptr = NULL;

    /* number of sets to create */
    int numSets = 0;
    
    /* character variable to store user choice */
    char option = 'a';

    /* user string input */
    char str[51];
    char num[] = "Hello";

    /* integer - ID of a set */
    int setID = 0;

    /* variables for copying sets */
    int copyFrom = 0;
    int copyTo = 0;

    /* loop counters */
    int i = 0;

    /* ask user how many sets to create */
    printf("Enter the number of sets to create: ");
    fgets(num, 5, stdin);
    printf("%s\n", num);
    sscanf(num, "%d", &numSets);
    
    /* flush input buffer */
    fflush(stdin);

    /* create sets
       - each sets is a linked list
       - initialize numSets pointers to linked lists  
    */
    headElements = malloc(numSets * sizeof(SET*));
    for (i = 0; i < numSets; i++) {
        headElements[i] = NULL;
    }

    /* main loop */
    while (1 > 0) {
            /* print menu of actions */
            printMenu();

            /* ask user to select an action */
            printf("Select an option: ");
            fgets(num, 5, stdin);

            /* check for valid option */
            if (strlen(num) > 2) {
                printf("Option not available. Please try again!\n");
                fflush(stdin);
                continue;
            }

            sscanf(num, "%c", &option);
            fflush(stdin);

            /* check if user wants to quit */
            if (option == 'q' || option == 'Q') {
                /* clear all sets */
                for (i = 0; i < numSets; i++)
                    clear(&headElements[i]);
                /* break out of the loop */
                break;
            }

            /* print a set */
            if (option == 'p') {
                /* get ID of set to print*/
                printf("Enter set to print: ");
                fgets(num, 5, stdin);
                sscanf(num, "%d", &setID);
                fflush(stdin);
                
                /* print the set */
                printf("Set %d: ", setID);
                ptr = headElements[setID];
                print(ptr);
                
                /* go to menu again */
                continue;
            }

            /* print all sets */
            if (option == 'P') {
                /* call function to print all non-empty sets*/
                printSets(headElements, numSets);
                /* go to action menu */
                continue;
            }
            
            option = tolower(option);
            switch (option) {
                /* add an element(string) to a set */
                case 'a':
                    /* set to add string to */
                    printf("Enter set to add to: ");
                    fgets(num, 5, stdin);
                    sscanf(num, "%d", &setID);
                    fflush(stdin);
                    
                    /* what string to add */
                    printf("Enter string to add: ");
                    fgets(str, 51, stdin);
                    fflush(stdin);

                    /* remove trailing newline */
                    str[strcspn(str, "\n")] = 0;

                    /* call function to add string to set */
                    ptr = headElements[setID];
                    addNode(&ptr, str);
                    headElements[setID] = ptr;
                    
                    break;

                case 'r':
                    /* get set ID and string for remove operation */
                    printf("Enter set to remove from: ");
                    fgets(num, 5, stdin);
                    sscanf(num, "%d", &setID);
                    fflush(stdin);
                    printf("Enter string to remove: ");
                    fgets(str, 51, stdin);
                    str[strcspn(str, "\n")] = 0;
                    
                    /* call function */
                    removeNode(&headElements[setID], str);
                    break;

                case 'u':
                    /* get set IDs for union and destination set ID */
                    printf("Enter destination set: ");
                    fgets(num, 5, stdin);
                    sscanf(num, "%d", &setID);
                    fflush(stdin);
                    printf("Enter first set to union: ");
                    fgets(num, 5, stdin);
                    sscanf(num, "%d", &copyTo);
                    fflush(stdin);
                    printf("Enter second set to union: ");
                    fgets(num, 5, stdin);
                    sscanf(num, "%d", &copyFrom);
                    fflush(stdin);

                    /* call function */
                    unionSets(&headElements[copyTo], &headElements[copyFrom], &headElements[setID]);

                    break;

                case 'i':
                    /* get set IDs for intersection and destination set ID */
                    printf("Enter destination set: ");
                    fgets(num, 5, stdin);
                    sscanf(num, "%d", &setID);
                    fflush(stdin);
                    printf("Enter first set to intersect from: ");
                    fgets(num, 5, stdin);
                    sscanf(num, "%d", &copyTo);
                    fflush(stdin);
                    printf("Enter second set to intersect from: ");
                    fgets(num, 5, stdin);
                    sscanf(num, "%d", &copyFrom);
                    fflush(stdin);

                    /* call function */
                    intersection(&headElements[copyTo], &headElements[copyFrom], &headElements[setID]);

                    break;
                
                case 's':
                    /* get set IDs for symmetric difference and destination set ID */
                    printf("Enter destination set: ");
                    fgets(num, 5, stdin);
                    sscanf(num, "%d", &setID);
                    fflush(stdin);
                    printf("Enter first set for symmetric difference: ");
                    fgets(num, 5, stdin);
                    sscanf(num, "%d", &copyTo);
                    fflush(stdin);
                    printf("Enter second set for symmetric difference: ");
                    fgets(num, 5, stdin);
                    sscanf(num, "%d", &copyFrom);
                    fflush(stdin);

                    /* call function */
                    symmetricdifference(&headElements[copyTo], &headElements[copyFrom], &headElements[setID]);

                    break;
                
                case 'c':
                    /* get set ids for copy*/
                    printf("Enter set to copy to: ");
                    fgets(num, 5, stdin);
                    sscanf(num, "%d", &copyTo);
                    fflush(stdin);
                    printf("Enter set to copy from: ");
                    fgets(num, 5, stdin);
                    sscanf(num, "%d", &copyFrom);
                    fflush(stdin);
                    /* call copy function */
                    copy(&headElements[copyTo], &headElements[copyFrom]);
                    
                    break;
                
                case 'z':
                    printf("Enter set to clear: ");
                    fgets(num, 5, stdin);
                    sscanf(num, "%d", &setID);
                    fflush(stdin);
                    /* clear the set - release all memory*/
                    clear(&headElements[setID]);

                    break;

                default:
                    break;
            }
    }

    /* free memory */
    free(headElements);

    return 0;
}

void addNode(SET** head, char* str) {
    /* create new mode and add string as node data */
    SET* newNode = malloc(sizeof(SET));
    strcpy(newNode->data, str);   
    
    /* make new node point to previous head */    
    newNode->next = *head;
    /* change head to new node */
    *head = newNode;
}

void print(SET* head) {
    SET* currentNode = head;

    if (currentNode == NULL) {
        printf("{}\n"); 
    }
    else {
        printf("{ ");
        do {
            printf("%s ", currentNode->data);
            currentNode = currentNode->next;
        } while (currentNode != NULL);
        printf("}\n");
    }

    /* free memory */
    free(currentNode);
}

void printSets(SET** heads, int numSets) {
    int i = 0;
    for (i = 0; i < numSets; i++) {
        if (heads[i] != NULL) {
            printf("Set %d: ", i);
            print(heads[i]);
        }
    }
}

void clear(SET** head) {
    SET* currentNode = *head;
    SET* nextNode = NULL;

    while (currentNode != NULL) {
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }

    *head = NULL;
}

void copy(SET** dest, SET** src) {
    char str[51];
    SET* currentNode = *src;
    
    /* clear destination set */
    clear(dest);

    /* read data from source set and add nodes to destination set accordingly */
    while (currentNode != NULL) {
        strcpy(str, currentNode->data);
        addNode(dest, str);
        currentNode = currentNode->next;
    }

    /* free memory */
    free(currentNode);
}

void removeNode(SET** head, char* str) {
    /* traverse the set and check if set element = str */
    SET* currentNode = *head;
    SET* previousNode = *head;

    /* check if first node needs to be removed */
    if (strcmp(currentNode->data, str) == 0) {
        currentNode = currentNode->next;
        free(*head);
        *head = currentNode;
        return;
    }   

    /* for other nodes */
    while (currentNode != NULL) {
        if (strcmp(currentNode->data, str) == 0) {
            previousNode->next = currentNode->next;
            currentNode->next = NULL;
            free(currentNode);
            return;
        }
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
}

void unionSets(SET** firstSet, SET** secondSet, SET** unionSet) {
    /* pointers to traverse the linked lists */
    SET* ptr1 = *firstSet;
    SET* ptr2 = *secondSet;

    /* flag to indicate uniqueness */
    int alreadyThere = 0;

    /* first copy all elements of firstSet into unionSet */
    clear(unionSet);
    copy(unionSet, firstSet);

    /* copy elements of secondSet which are not already present */
    while (ptr2 != NULL) {
        ptr1 = *firstSet;
        alreadyThere = 0;
        while (ptr1 != NULL) {
            if (strcmp(ptr1->data, ptr2->data) == 0) {
                alreadyThere = 1;
                break;
            }
            ptr1 = ptr1->next;    
        }
        if (alreadyThere == 0) 
            addNode(unionSet, ptr2->data);
        ptr2 = ptr2 -> next;
    } 
}

void intersection(SET** firstSet, SET** secondSet, SET** intersectionSet) {
    /* pointers to traverse the linked lists */
    SET* ptr1 = *firstSet;
    SET* ptr2 = *secondSet;

    /* flag to indicate uniqueness */
    int alreadyThere = 0;

    /* clear set before adding elements */
    clear(intersectionSet);

    /* look for common elements and add to destination set */
    while (ptr2 != NULL) {
        ptr1 = *firstSet;
        alreadyThere = 0;
        while (ptr1 != NULL) {
            if (strcmp(ptr1->data, ptr2->data) == 0) {
                alreadyThere = 1;
                break;
            }
            ptr1 = ptr1->next;    
        }
        if (alreadyThere == 1)
            addNode(intersectionSet, ptr2->data);
        ptr2 = ptr2 -> next;
    } 
}

void symmetricdifference(SET** firstSet, SET** secondSet, SET** destinationSet) {
    /* pointers to traverse the linked lists */
    SET* ptr1 = *firstSet;
    SET* ptr2 = *secondSet;

    /* flag to indicate uniqueness */
    int alreadyThere = 0;

    /* clear set before adding elements */
    clear(destinationSet);

    /* traverse first set, skip common elements with second set */
    while (ptr1 != NULL) {
        ptr2 = *secondSet;
        alreadyThere = 0;
        while (ptr2 != NULL) {
            if (strcmp(ptr1->data, ptr2->data) == 0) {
                alreadyThere = 1;
                break;
            }
            ptr2 = ptr2->next;    
        }
        if (alreadyThere == 0)
            addNode(destinationSet, ptr1->data);
        ptr1 = ptr1 -> next;
    }

    /* copy elements of second set which are not already present */
    ptr2 = *secondSet;
    while (ptr2 != NULL) {
        ptr1 = *firstSet;
        alreadyThere = 0;
        while (ptr1 != NULL) {
            if (strcmp(ptr1->data, ptr2->data) == 0) {
                alreadyThere = 1;
                break;
            }
            ptr1 = ptr1->next;    
        }
        if (alreadyThere == 0) 
            addNode(destinationSet, ptr2->data);
        ptr2 = ptr2 -> next;
    }     
}


void printMenu() {
    printf("Choose from the menu prompt below:\n");
    printf("\t*****Menu Options*****\n");
    printf("\tAdd String:            a or A\n");
    printf("\tRemove String:         r or R\n");
    printf("\tUnion:                 u or U\n");
    printf("\tIntersection:          i or I\n");
    printf("\tSymmetric Difference:  s or S\n");
    printf("\tCopy:                  c or C\n");
    printf("\tClear:                 z or Z\n");
    printf("\tPrint Set:             p     \n");
    printf("\tPrint All Sets:        P     \n");
    printf("\tQuit:                  q or Q\n");
}
