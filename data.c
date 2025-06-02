/* data.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>    /* for strcasecmp */
#include "data.h"

/* Head pointer */
struct State *head = NULL;

/* Create and populate a new node */
struct State* createNode(const char *name, int year, double area, long population) {
    struct State *node = malloc(sizeof(struct State));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strncpy(node->name, name, sizeof(node->name)-1);
    node->name[sizeof(node->name)-1] = '\0';
    node->year = year;
    node->area = area;
    node->population = population;
    node->next = NULL;
    return node;
}

/* Append node to end of list */
void insertEnd(const char *name, int year, double area, long population) {
    struct State *node = createNode(name, year, area, population);
    if (!head) {
        head = node;
    } else {
        struct State *cur = head;
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = node;
    }
}

/* Hardcode 16 Malaysian states and territories */
void initData(void) {
    printf("initData CALLED!\n");
    // Entries: name, creation year, area(km2), population
    insertEnd("Johore",          1528, 19166.0,   4009670L);
    insertEnd("Kelantan",        1267, 15040.0,   1812300L);
    insertEnd("Sabah",           1963, 73631.0,   3580000L);
    insertEnd("Perak",           1528, 21005.0,   2503000L);
    insertEnd("Kedah",           1136, 9425.0,    2071900L);
    insertEnd("Malacca",         1400, 1660.0,     933000L);
    insertEnd("Putrajaya",       2001, 49.0,       109000L);
    insertEnd("Pahang",          1470, 35825.0,   1688000L);
    insertEnd("Perlis",          1947, 810.0,      255000L);
    insertEnd("Labuan",          1984, 92.0,        99000L);
    insertEnd("Negeri Sembilan", 1773, 6624.0,    1117000L);
    insertEnd("Sarawak",         1841, 124450.0,  2818000L);
    insertEnd("Penang",          1786, 1048.0,    1767000L);
    insertEnd("Selangor",        1766, 8104.0,    6412000L);
    insertEnd("Terengganu",      1724, 13035.0,   1149000L);
    insertEnd("Kuala Lumpur",    1974, 243.0,     1793000L);
}

/* Deletes node by exact name match (case-sensitive) */
int deleteByName(const char *name) {
    struct State *cur = head, *prev = NULL;
    while (cur) {
        if (strcmp(cur->name, name) == 0) {
            if (prev) prev->next = cur->next;
            else head = cur->next;
            free(cur);
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

void sortList(int field, int ascending) {
    head = mergeSortList(head, field, ascending);
}

/* Case-insensitive search */
// Print all matches for substring search
void searchByPartialName(const char *query) {
    struct State *cur = head;
    int found = 0;
    while (cur) {
        // strcasestr is GNU/POSIX, for Windows use your own case-insensitive strstr
        if (strcasestr(cur->name, query) != NULL) {
            printf("%-17s %-8d %-12.1f %-12ld\n", cur->name, cur->year, cur->area, cur->population);
            found = 1;
        }
        cur = cur->next;
    }
    if (!found) {
        printf("No matching state or territory found.\n");
    }
}

/* Free entire list */
void freeList(void) {
    struct State *cur = head, *tmp;
    while (cur) {
        tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    head = NULL;
}