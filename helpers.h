#ifndef HELPERS_H
#define HELPERS_H

struct State; // Forward declaration for struct State pointer usage

/* Clears any leftover characters from stdin buffer */
void clearInputBuffer(void);

/* Reads an integer between min and max (inclusive), reprompts on invalid input */
int readIntInRange(int min, int max);

/* Reads a double value, reprompts on invalid input */
double readDouble(const char *prompt);

/* Reads a long integer value, reprompts on invalid input */
long readLong(const char *prompt);

/* Reads a line of text (up to size-1 characters), strips trailing newline */
void readString(const char *prompt, char *buffer, int size);

/* Generates a CSV report (text-based) from current records */
void generateReport(void);

/* Deletes a state record by exact name, printing feedback */
void js_delete(const char *name);

/* Performs a partial, case-insensitive substring search and prints all matching records */
void js_search(const char *name);

/* Performs merge sort on the linked list by specified field and order */
struct State* mergeSortList(struct State *head, int field, int ascending);

/* Case-insensitive substring search utility */
char *strcasestr(const char *haystack, const char *needle);

#endif /* HELPERS_H */
