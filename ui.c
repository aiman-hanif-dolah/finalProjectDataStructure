/* ui.c */
#include <stdio.h>
#include <unistd.h>    /* usleep */
#include <string.h>
#include "ui.h"
#include "helpers.h"
#include "data.h"

/* Welcome message (bilingual) */
void printWelcome(int lang) {
    if (lang == 1) {
        printf("\033[1;34mWelcome to Malaysian States Manager!\033[0m\n");
        printf("Manage 13 states and 3 federal territories.\n");
    } else {
        printf("\033[1;34mSelamat datang ke Pengurusan Negeri & Wilayah Malaysia!\033[0m\n");
        printf("Urus 13 negeri dan 3 wilayah persekutuan.\n");
    }
}

/* Spinner animation */
void animateLoading(const char *msg) {
    const char spinner[] = "|/-\\";
    printf("%s ", msg);
    fflush(stdout);
    for (int i = 0; i < 8; i++) {
        printf("\b%c", spinner[i % 4]);
        fflush(stdout);
        usleep(100000);
    }
    printf("\b \n");
}

/* Main menu */
void displayMenu(int lang) {
    if (lang == 1) {
        printf("\n\033[1;33mMain Menu (Enter choice):\033[0m\n");
        printf("1. Display all records\n");
        printf("2. Sort records\n");
        printf("3. Insert a record\n");
        printf("4. Delete a record\n");
        printf("5. Search / Quick Query\n");
        printf("6. Generate report (CSV)\n");
        printf("0. Exit\n");
        /* New prompt */
        printf("Your Choice: ");
    } else {
        printf("\n\033[1;33mMenu Utama (Pilih):\033[0m\n");
        printf("1. Papar semua rekod\n");
        printf("2. Susun rekod\n");
        printf("3. Masukkan rekod\n");
        printf("4. Padam rekod\n");
        printf("5. Cari / Soal Segera\n");
        printf("6. Hasilkan laporan (CSV)\n");
        printf("0. Keluar\n");
        /* New prompt */
        printf("Pilihan anda: ");
    }
    fflush(stdout);
}

/* Display all records in a colorized table */
void displayAll(void) {
    printf("\n\033[1;32m%-15s  %-6s  %-10s  %10s\n\033[0m",
           "Name", "Year", "Area(km2)", "Population");
    struct State *cur = head;
    while (cur) {
        printf("\033[1;36m%-15s\033[0m  ", cur->name);
        printf("%-6d  ", cur->year);
        printf("%10.1f  ", cur->area);
        printf("%10ld\n", cur->population);
        cur = cur->next;
    }
}

/* Sort submenu */
void promptSort(int lang) {
    int field, order;
    if (lang == 1) {
        printf("Sort by:\n1. Name\n2. Creation Year\n3. Area\n4. Population\n0. Back\nYour Choice: ");
    } else {
        printf("Susun mengikut:\n1. Nama\n2. Tahun Penubuhan\n3. Kawasan\n4. Populasi\n0. Kembali\nPilihan anda: ");
    }
    field = readIntInRange(0, 4);
    if (field == 0) return;

    if (lang == 1) printf("1. Ascending\n2. Descending\nYour Choice: ");
    else           printf("1. Menaik\n2. Menurun\nPilihan anda: ");
    order = readIntInRange(1, 2);

    animateLoading("Sorting");
    sortList(field, order == 1);

    /* Show sorted list immediately */
    displayAll();

    if (lang == 1) printf("Sorted successfully.\n");
    else           printf("Susunan selesai.\n");
}

/* Insert submenu */
void promptInsert(int lang) {
    char name[50];
    int year;
    double area;
    long pop;
    if (lang == 1) printf("Enter state name (0 to cancel): ");
    else           printf("Masukkan nama negeri (0 untuk batalkan): ");
    readString("", name, sizeof(name));
    if (strcmp(name, "0") == 0) return;

    if (lang == 1) printf("Enter creation year: ");
    else           printf("Masukkan tahun penubuhan: ");
    year = readIntInRange(1000, 3000);

    area = readDouble(lang == 1 ? "Enter area (km2): " : "Masukkan kawasan (km2): ");
    pop  = readLong  (lang == 1 ? "Enter population: " : "Masukkan populasi: ");

    insertEnd(name, year, area, pop);
    if (lang == 1) printf("Record inserted.\n");
    else           printf("Rekod ditambah.\n");
}

/* Delete submenu */
void promptDelete(int lang) {
    char name[50];
    if (lang == 1) printf("Enter state name to delete (0 to cancel): ");
    else           printf("Masukkan nama negeri untuk dipadam (0 untuk batalkan): ");
    readString("", name, sizeof(name));
    if (strcmp(name, "0") == 0) return;

    if (deleteByName(name)) {
        if (lang == 1) printf("Record deleted.\n");
        else           printf("Rekod dipadam.\n");
    } else {
        if (lang == 1) printf("Record not found.\n");
        else           printf("Rekod tidak dijumpai.\n");
    }
}

/* Search submenu */
void promptSearch(int lang) {
    char name[50];
    if (lang == 1) printf("Enter state name to search (0 to cancel): ");
    else           printf("Masukkan nama negeri untuk cari (0 untuk batalkan): ");
    readString("", name, sizeof(name));
    if (strcmp(name, "0") == 0) return;

    if (lang == 1)
        printf("Search results (partial match, case-insensitive):\n");
    else
        printf("Keputusan carian (padanan separa, tidak sensitif huruf):\n");

    js_search(name); // uses your strcasestr-based search, prints all matches
}
