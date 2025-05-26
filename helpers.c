/* helpers.c */

#include <stdio.h>      /* FILE, fopen, fprintf, printf */
#include <stdlib.h>     /* system, EXIT_FAILURE */
#include <string.h>     /* strcpy, snprintf, strcspn */
#include <limits.h>     /* PATH_MAX */

#ifdef _WIN32
  #include <direct.h>   /* _getcwd */
  #define getcwd _getcwd
#else
  #include <unistd.h>   /* getcwd */
#endif

#include "helpers.h"
#include "data.h"       /* for head and struct State */

/* Fallback if PATH_MAX isn't defined */
#ifndef PATH_MAX
  #define PATH_MAX 260
#endif

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

/* Wrapper for C searchByName(), prints the one record or “not found” */
void js_search(const char *name) {
    struct State *r = searchByName(name);
    if (r) {
        printf("\033[1;32m%-15s  %-6s  %-10s  %10s\n\033[0m", "Name", "Year", "Area(km2)", "Population");
        printf("\033[1;36m%-15s\033[0m  %-6d  %10.1f  %10ld\n",
               r->name, r->year, r->area, r->population);
    } else {
        printf("Record not found.\n");
    }
}


