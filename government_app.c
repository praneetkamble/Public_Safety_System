#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shared.h"

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause_screen() {
    printf("\nPress ENTER to continue...");
    getchar();
    getchar();
}


void view_all_cases() {
    clear_screen();

    Case c;
    FILE *fp = fopen(CASE_DB, "rb");

    if (!fp) {
        printf("No cases found.\n");
        pause_screen();
        return;
    }

    printf("ALL REGISTERED CASES\n");
    printf("--------------------\n");

    while (fread(&c, sizeof(Case), 1, fp)) {
        printf("\nID:%d | %s | %s | Sev:%d | %s",
               c.case_id,
               type_to_string(c.type),
               c.location,
               c.severity,
               status_to_string(c.status));
    }

    fclose(fp);
    pause_screen();
}


void update_case_status() {
    clear_screen();

    int id;
    Case c;

    printf("UPDATE CASE STATUS\n");
    printf("------------------\n");
    printf("Enter Case ID: ");
    scanf("%d", &id);

    FILE *fp = fopen(CASE_DB, "rb+");
    if (!fp) return;

    while (fread(&c, sizeof(Case), 1, fp)) {
        if (c.case_id == id) {
            printf("Current Status: %s\n", status_to_string(c.status));

           
            do {
                printf("New Status:\n");
                printf("1.Registered 2.Dispatched 3.In Progress 4.Resolved 5.Closed\n");
                scanf("%d", (int*)&c.status);

                if (c.status < 1 || c.status > 5)
                    printf("❌ Invalid status! Choose between 1 and 5.\n");
            } while (c.status < 1 || c.status > 5);

            fseek(fp, -sizeof(Case), SEEK_CUR);
            fwrite(&c, sizeof(Case), 1, fp);
            fclose(fp);

            printf("✅ Status Updated Successfully!");
            pause_screen();
            return;
        }
    }

    fclose(fp);
    printf("❌ Case not found!");
    pause_screen();
}


void generate_analytics() {
    clear_screen();

    Case c;
    int total = 0, pending = 0, closed = 0;

    FILE *fp = fopen(CASE_DB, "rb");
    if (!fp) return;

    while (fread(&c, sizeof(Case), 1, fp)) {
        total++;
        if (c.status < RESOLVED) pending++;
        if (c.status == CLOSED) closed++;
    }
    fclose(fp);

    FILE *rep = fopen("analytics.txt", "w");
    fprintf(rep, "PUBLIC SAFETY SYSTEM ANALYTICS\n");
    fprintf(rep, "-----------------------------\n");
    fprintf(rep, "Total Cases : %d\n", total);
    fprintf(rep, "Pending     : %d\n", pending);
    fprintf(rep, "Closed      : %d\n", closed);
    fclose(rep);

    printf("📊 Analytics generated (analytics.txt)");
    pause_screen();
}


int main() {
    int choice;

    while (1) {
        clear_screen();
        printf("====================================\n");
        printf("  GOVERNMENT CONTROL APPLICATION\n");
        printf("====================================\n");
        printf("1. View All Cases\n");
        printf("2. Update Case Status\n");
        printf("3. Generate Analytics\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: view_all_cases(); break;
            case 2: update_case_status(); break;
            case 3: generate_analytics(); break;
            case 4: exit(0);
            default:
                printf("❌ Invalid choice!");
                pause_screen();
        }
    }
}

