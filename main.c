/* main.c */
#include <stdio.h>
#include "data.h"
#include "ui.h"
#include "helpers.h"

int main(void) {
    int lang, choice;
    /* Initialize with hardcoded data */
    initData();
    animateLoading("Loading data");
    /* Language selector */
    printf("1. English\n2. Bahasa Melayu\nSelect language: ");
    lang = readIntInRange(1, 2);
    printWelcome(lang);

    /* Main control loop */
    do {
        displayMenu(lang);
        choice = readIntInRange(0, 6);
        switch (choice) {
            case 1: displayAll();          break;
            case 2: promptSort(lang);      break;
            case 3: promptInsert(lang);    break;
            case 4: promptDelete(lang);    break;
            case 5: promptSearch(lang);    break;
            case 6: generateReport();      break;
            case 0:
                if (lang == 1) printf("Exiting...\n");
                else           printf("Keluar...\n");
                break;
            default: break;
        }
    } while (choice != 0);

    /* Clean up */
    freeList();
    return 0;
}
