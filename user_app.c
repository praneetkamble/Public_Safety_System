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


int generate_case_id() {
    FILE *fp = fopen(CASE_DB, "rb");
    Case c;
    int id = 1000;

    if (fp) {
        while (fread(&c, sizeof(Case), 1, fp))
            id = c.case_id + 1;
        fclose(fp);
    }
    return id;
}


void report_case() {
    clear_screen();

    Case c;
    c.case_id = generate_case_id();
    c.created_time = time(NULL);
    c.status = REGISTERED;

   
    do {
        printf("REPORT EMERGENCY / CIVIC ISSUE\n");
        printf("--------------------------------\n");
        printf("1. Medical\n2. Police\n3. Fire\n4. Utility\n5. Disaster\n6. Complaint\n");
        printf("Select Type (1–6): ");
        scanf("%d", (int*)&c.type);

        if (c.type < 1 || c.type > 6)
            printf("❌ Invalid type! Please select between 1 and 6.\n\n");
    } while (c.type < 1 || c.type > 6);

    printf("Enter Location: ");
    scanf(" %[^\n]", c.location);

  
    do {
        printf("Enter Severity (1–5): ");
        scanf("%d", &c.severity);

        if (c.severity < 1 || c.severity > 5)
            printf("❌ Invalid severity! Please enter between 1 and 5.\n");
    } while (c.severity < 1 || c.severity > 5);

    FILE *fp = fopen(CASE_DB, "ab");
    fwrite(&c, sizeof(Case), 1, fp);
    fclose(fp);

    printf("\n✅ Case Registered Successfully!");
    printf("\nCase ID   : %d", c.case_id);
    printf("\nType      : %s", type_to_string(c.type));
    printf("\nSeverity  : %d", c.severity);
    printf("\nStatus    : %s\n", status_to_string(c.status));

    pause_screen();
}


void check_status() {
    clear_screen();

    int id, found = 0;
    Case c;

    printf("CHECK CASE STATUS\n");
    printf("------------------\n");
    printf("Enter Case ID: ");
    scanf("%d", &id);

    FILE *fp = fopen(CASE_DB, "rb");
    if (!fp) {
        printf("No records found.\n");
        pause_screen();
        return;
    }

    while (fread(&c, sizeof(Case), 1, fp)) {
        if (c.case_id == id) {
            printf("\nCase ID   : %d", c.case_id);
            printf("\nType      : %s", type_to_string(c.type));
            printf("\nLocation  : %s", c.location);
            printf("\nSeverity  : %d", c.severity);
            printf("\nStatus    : %s", status_to_string(c.status));
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("\n❌ Case not found.");

    pause_screen();
}


int main() {
    int choice;

    while (1) {
        clear_screen();
        printf("====================================\n");
        printf("   PUBLIC SAFETY USER APPLICATION\n");
        printf("====================================\n");
        printf("1. Report Emergency / Issue\n");
        printf("2. Check Case Status\n");
        printf("3. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: report_case(); break;
            case 2: check_status(); break;
            case 3: exit(0);
            default:
                printf("❌ Invalid choice!");
                pause_screen();
        }
    }
}

