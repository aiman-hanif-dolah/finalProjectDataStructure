/* helpers.c */

#include <stdio.h>      // FILE, fopen, fprintf, printf
#include <stdlib.h>     // system, EXIT_FAILURE
#include <string.h>     // strcpy, snprintf, strcspn
#include <limits.h>
#include <ctype.h>

#ifdef _WIN32
  #include <direct.h>   /* _getcwd */
  #define getcwd _getcwd
#else
  #include <unistd.h>   /* getcwd */
#endif

#include "helpers.h"

#include <stddef.h>

#include "data.h"       /* for head and struct State */

/* Fallback if PATH_MAX isn't defined */
#ifndef PATH_MAX
  #define PATH_MAX 260
#endif

char *strcasestr(const char *haystack, const char *needle) {
    if (!*needle)
        return (char *)haystack;
    for (; *haystack; ++haystack) {
        const char *h = haystack;
        const char *n = needle;
        while (*h && *n && tolower((unsigned char)*h) == tolower((unsigned char)*n)) {
            ++h;
            ++n;
        }
        if (!*n)
            return (char *)haystack;
    }
    return NULL;
}

int compareStates(struct State *a, struct State *b, int field, int ascending) {
    int cmp = 0;
    switch (field) {
        case 1: cmp = strcasecmp(a->name, b->name); break;
        case 2: cmp = a->year - b->year; break;
        case 3: cmp = (a->area < b->area) ? -1 : (a->area > b->area) ? 1 : 0; break;
        case 4: cmp = (a->population < b->population) ? -1 : (a->population > b->population) ? 1 : 0; break;
        default: cmp = 0;
    }
    return ascending ? cmp : -cmp;
}

struct State* mergeSortedLists(struct State *a, struct State *b, int field, int ascending) {
    if (!a) return b;
    if (!b) return a;
    struct State *result = NULL;

    if (compareStates(a, b, field, ascending) <= 0) {
        result = a;
        result->next = mergeSortedLists(a->next, b, field, ascending);
    } else {
        result = b;
        result->next = mergeSortedLists(a, b->next, field, ascending);
    }
    return result;
}


void splitList(struct State *source, struct State **front, struct State **back) {
    struct State *slow = source;
    struct State *fast = source->next;
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = source;
    *back = slow->next;
    slow->next = NULL;
}


struct State* mergeSortList(struct State *head, int field, int ascending) {
    if (!head || !head->next) return head;
    struct State *a, *b;
    splitList(head, &a, &b);
    a = mergeSortList(a, field, ascending);
    b = mergeSortList(b, field, ascending);
    return mergeSortedLists(a, b, field, ascending);
}


/* Discard leftover input until newline */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* Read an integer between min and max (inclusive) */
int readIntInRange(int min, int max) {
    int x;
    while (1) {
        if (scanf("%d", &x) != 1) {
            clearInputBuffer();
            printf("Invalid input, try again: ");
        } else if (x < min || x > max) {
            printf("Please enter a number between %d and %d: ", min, max);
        } else {
            clearInputBuffer();
            return x;
        }
    }
}

/* Read a double, reprompting on invalid input */
double readDouble(const char *prompt) {
    double x;
    printf("%s", prompt);
    while (scanf("%lf", &x) != 1) {
        clearInputBuffer();
        printf("Invalid input, try again: ");
    }
    clearInputBuffer();
    return x;
}

/* Read a long integer, reprompting on invalid input */
long readLong(const char *prompt) {
    long x;
    printf("%s", prompt);
    while (scanf("%ld", &x) != 1) {
        clearInputBuffer();
        printf("Invalid input, try again: ");
    }
    clearInputBuffer();
    return x;
}

/* Read a line of text (up to size-1 chars), strips newline */
void readString(const char *prompt, char *buffer, int size) {
    if (prompt && *prompt) {
        printf("%s", prompt);
    }
    if (fgets(buffer, size, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

/* Generate CSV report, show its path, and open Explorer (Windows) */
void generateReport(void) {
    char cwd[PATH_MAX];
    if (!getcwd(cwd, sizeof(cwd))) {
        /* Fallback if retrieval fails */
        strcpy(cwd, ".");
    }

    char csvPath[PATH_MAX];
    snprintf(csvPath, sizeof(csvPath), "%s/report.csv", cwd);

    FILE *fp = fopen(csvPath, "w");
    if (!fp) {
        printf("Failed to create %s\n", csvPath);
        return;
    }

    /* CSV header */
    fprintf(fp, "Name,Year,Area(km2),Population\n");

    /* Data rows */
    struct State *cur = head;
    while (cur) {
        fprintf(fp, "\"%s\",%d,%.1f,%ld\n",
                cur->name,
                cur->year,
                cur->area,
                cur->population);
        cur = cur->next;
    }
    fclose(fp);

    /* Inform user */
    printf("Report saved as %s\n", csvPath);

    /* Open folder in Explorer on Windows; on other platforms this will do nothing */
#ifdef _WIN32
    char cmd[PATH_MAX + 32];
    snprintf(cmd, sizeof(cmd),
             "explorer \"%s\"", cwd);
    system(cmd);
#endif
}

/* Wrapper for C deleteByName(), prints C-style feedback */
void js_delete(const char *name) {
    if (deleteByName(name)) {
        printf("Record deleted.\n");
    } else {
        printf("Record not found.\n");
    }
}

void js_search(const char *name) {
    struct State *cur = head;
    int found = 0;
    // Print header once if any match found
    while (cur) {
        // Use strcasestr for case-insensitive partial match
        if (strcasestr(cur->name, name) != NULL) {
            if (!found) {
                printf("\033[1;32m%-15s  %-6s  %-10s  %10s\n\033[0m", "Name", "Year", "Area(km2)", "Population");
            }
            printf("\033[1;36m%-15s\033[0m  %-6d  %10.1f  %10ld\n",
                   cur->name, cur->year, cur->area, cur->population);
            found = 1;
        }
        cur = cur->next;
    }
    if (!found) {
        printf("Record not found.\n");
    }
}