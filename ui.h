/* ui.h */
#ifndef UI_H
#define UI_H

#include "data.h"

/* Displays initial bilingual welcome */
void printWelcome(int lang);

/* Simple console “loading” animation */
void animateLoading(const char *msg);

/* Renders the main menu */
void displayMenu(int lang);

/* Prints all records in a colorized table */
void displayAll(void);

/* Sub-menus */
void promptSort(int lang);
void promptInsert(int lang);
void promptDelete(int lang);
void promptSearch(int lang);

#endif /* UI_H */
