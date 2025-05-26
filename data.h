/* data.h */
#ifndef DATA_H
#define DATA_H

/* Node structure for a Malaysian state/federal territory */
struct State {
    char name[50];
    int year;               /* Creation year */
    double area;            /* Area in km² */
    long population;        /* Population count */
    struct State *next;     /* Pointer to next node */
};

/* Head pointer of the linked list */
extern struct State *head;

/* Creates a new node with given data */
struct State* createNode(const char *name, int year, double area, long population);

/* Initializes list with 16 hardcoded Malaysian states/territories */
void initData(void);

/* Inserts a new record at the end of the list */
void insertEnd(const char *name, int year, double area, long population);

/* Deletes a record matching the given name; returns 1 if deleted, 0 if not found */
int deleteByName(const char *name);

/* Sorts list on field (1=name,2=year,3=area,4=population); ascending if asc=1 */
void sortList(int field, int ascending);

/* Searches for a record by name (case-insensitive); returns pointer or NULL */
struct State* searchByName(const char *name);

/* Frees all nodes and resets list */
void freeList(void);

#endif /* DATA_H */
