#include <stdio.h>
#include <stdlib.h>

struct SLnode {
  int key;
  struct SLnode *next;
};
typedef struct SLnode *SLnodePtr;

struct HBnode {
  int key;
  struct HBnode *next;
  struct HBnode *bottom;
};

typedef struct HBnode *HBnodePtr;
// Sorting algorithm
void bubbleSort(int arr[], int n) {
  int i, j, temp;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        temp = arr[j + 1];
        arr[j + 1] = arr[j];
        arr[j] = temp;
      }
    }
  }
}

// MAKE THE BOTTOM LINKED LIST
struct HBnode *
createBottom(int m, int q) // FUNCTION RETURNS A POINTER POINTING AT SOME  NODE
// TAKES IN VALUES M, WILL CREATE [0, M] NODES
{
  struct HBnode *headBottom =
      NULL; // makes pointer to node head node pointing nowhere
  // THE SAME AS *head, head = NULL
  struct HBnode *temp = NULL; // makes pointer to node temp pointing nowhere
  struct HBnode *p = NULL;    // makes pointer to node p pointing nowhere
  // RANDOM ARRAY GENERATOR
  int i;
  int n;
  n = rand() % m;         // creats random number n in range 0 to m
  int randList[n];        // makes array of size n
  for (i = 0; i < n; i++) // iterates thru n
  {
    randList[i] =
        (rand() % 1000) +
        q; // sets each value in randList to some number between 0 and 999
  }
  bubbleSort(randList, n); // sorts the array

  // Bottom Node Creator
  for (i = 0; i < n; i++) {
    temp = malloc(sizeof(struct HBnode)); // temp now points a block of memory
                                          // initialized by malloc
    // printf("Enter node value");
    // scanf("%d",&(temp->key) ); //gets the value of scanf and stores it in key
    temp->key = randList[i]; // sets the key equal to the ith value in rand list
    temp->next = NULL;       // makes next point to null

    if (headBottom == NULL) // if list is initially empty
    {
      headBottom = temp; // set head pointer equal temp
    }

    else // if we already got a head node
    {
      p = headBottom;         // set pointer p to point at starting node
      while (p->next != NULL) // while p still points to a node
      {
        p = p->next; // set p equal to the pointer of the next node
      }
      // When loop breaks, p will now point to null.  p will now be at the last
      // element in the linked list
      p->next = temp;
    }
  }
  return headBottom; // returns address of linked list
}
// Make The HBLIST
HBnodePtr createHBlist(int n, int m) {
  struct HBnode *headHB =
      NULL; // makes pointer to node head node pointing nowhere
  // THE SAME AS *head, head = NULL
  struct HBnode *temp = NULL; // makes pointer to node temp pointing nowhere
  struct HBnode *p = NULL;    // makes pointer to node p pointing nowhere
  int i;
  int randList[n];
  for (i = 0; i < n; i++) {
    randList[i] = rand() % 1000;
  }
  bubbleSort(randList, n);

  for (i = 0; i < n; i++) {
    temp = malloc(sizeof(struct HBnode)); // temp now points a block of memory
                                          // initialized by malloc
    // printf("Enter node value");
    // scanf("%d",&(temp->key) ); //gets the value of scanf and stores it in key
    temp->key = randList[i]; // sets the key equal to the ith value in rand list
    temp->next = NULL;       // makes next point to null
    temp->bottom = createBottom(
        m, temp->key); // makes bottom point to head node of SL *(temp).bottom

    if (headHB == NULL) // if list is initially empty
    {
      headHB = temp; // set head pointer equal temp
    }

    else // if we already got a head node
    {
      p = headHB;             // set pointer p to point at starting node
      while (p->next != NULL) // while p still points to a node
      {
        p = p->next; // set p equal to the pointer of the next node
      }
      // When loop breaks, p will now point to null.  p will now be at the last
      // element in the linked list
      p->next = temp;
    }
  }
  return headHB; // returns address of linked list
}

// PRINT THE FUNCTION
void printList(struct HBnode *headBottom) {
  printf("BOTTOM Start\n");
  struct HBnode *p = headBottom; // SAME AS *p, p = head
  while (p != NULL) // while (*p).next does not equal NULL, or while the node
                    // still points to another node
  {
    printf("%d ->", p->key); // prints p->key, or *(head).key
    p = p->next;
  }
  printf("\nBOTTOM END\n");
}

// PRINT HB
void printHBlist(struct HBnode *headHB) {
  struct HBnode *p = headHB; // SAME AS *p, p = head
  while (p != NULL) // while (*p).next does not equal NULL, or while the node
                    // still points to another node
  {
    printf("%d\n", p->key); // prints p->key, or *(head).key
    printList(p->bottom);
    p = p->next;
    printf("\n");
  }
}
// COPY LINKED LIST
struct HBnode *copyList(struct HBnode *list) {
  struct HBnode *copyHead = NULL;
  struct HBnode *p = NULL;
  struct HBnode *temp1 = NULL;
  while (list != NULL) {
    temp1 = malloc(sizeof(struct HBnode));
    temp1->key = list->key;
    temp1->next = NULL;

    if (copyHead == NULL) {
      copyHead = temp1;
    } else {
      p = copyHead;
      while (p->next != NULL) {
        p = p->next;
      }
      p->next = temp1;
    }
    list = list->next;
  }
  return copyHead;
}
// MERGE TWO LINKED LISTS
struct HBnode *merge(struct HBnode *a, struct HBnode *b) {
  struct HBnode *result = NULL;
  if (a == NULL) {
    return (b);
  } else if (b == NULL) {
    return (a);
  }
  if (a->key <= b->key) {
    result = a;
    result->next = merge(a->next, b);
  } else {
    result = b;
    result->next = merge(a, b->next);
  }
  return (result);
}
// Flattens an HB list
SLnodePtr flattenList(const HBnodePtr L) {
  struct HBnode *HBlist = L; // takes in L, stores it at HBlist
  struct HBnode *headSL =
      copyList(HBlist); // makes a copy of HBlist called headSL
  int i;
  while (HBlist != NULL) {
    struct HBnode *copyBottom =
        copyList(HBlist->bottom); // copies the bottom list
    struct HBnode *p = NULL;
    p = merge(headSL, copyBottom);
    headSL = p;
    HBlist = HBlist->next;
  }

  return (struct SLnode *)headSL;
}
// Free the nodes in SL list
void freeSLlist(SLnodePtr L) {
  struct SLnode *SLlist = L;
  struct SLnode *temp;

  while (SLlist != NULL) {
    temp = SLlist;
    SLlist = SLlist->next;
    free(temp);
  }
}

// Free the nodes in HB list
void freeHBlist(HBnodePtr L) {
  HBnodePtr HB = L;
  HBnodePtr temp;

  while (HB != NULL) {
    freeSLlist((SLnodePtr)HB->bottom);
    temp = HB;
    HB = HB->next;
    free(temp);
  }
}
// Prints SL list
void printSLlist(struct HBnode *headBottom) {
  printf("Flattened List\n");
  struct HBnode *p = headBottom; // SAME AS *p, p = head
  while (p != NULL) // while (*p).next does not equal NULL, or while the node
                    // still points to another node
  {
    printf("%d ->", p->key); // prints p->key, or *(head).key
    p = p->next;
  }
}

int main(void) {
  int n;
  int m;
  printf("Enter n: ");
  scanf("%d", &n);
  printf("Enter m: ");
  scanf("%d", &m);
  struct HBnode *HEADHB = NULL;
  HEADHB = createHBlist(n, m);
  printf("HBlist: \n");
  printHBlist(HEADHB);
  printf("\n");
  struct SLnode *test = NULL;
  test = flattenList(HEADHB);
  printSLlist((HBnodePtr)test);
  freeSLlist(test);
  freeHBlist(HEADHB);

  return 0;
}
