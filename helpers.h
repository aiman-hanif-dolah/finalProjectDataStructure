/* helpers.h */
#ifndef HELPERS_H
#define HELPERS_H

/* Clears stdin buffer */
void clearInputBuffer(void);

/* Reads an integer between min and max (inclusive) */
int readIntInRange(int min, int max);

/* Reads a double, reprompting on invalid input */
double readDouble(const char *prompt);

/* Reads a long integer, reprompting on invalid input */
long readLong(const char *prompt);

/* Reads a line of text (up to size-1 chars), strips newline */
void readString(const char *prompt, char *buffer, int size);

/* Generates a PDF-style report (text‐based) of current records */
void generateReport(void);

void js_delete(const char *name);
void js_search(const char *name);

#endif /* HELPERS_H */
