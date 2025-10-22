#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int id;
    char name[30];
    float salary;
};

int main() {
    FILE *fp;
    struct Employee emp;
    int choice, rec, n;

    fp = fopen("employee.dat", "rb+");
    if (fp == NULL)
        fp = fopen("employee.dat", "wb+");

    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    do {
        printf("\n--- Employee Record Menu ---\n");
        printf("1. Add Employee\n2. Display All\n3. Update Salary\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number of employees: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    printf("\nEnter ID: ");
                    scanf("%d", &emp.id);
                    printf("Enter Name: ");
                    scanf("%s", emp.name);
                    printf("Enter Salary: ");
                    scanf("%f", &emp.salary);
                    fwrite(&emp, sizeof(emp), 1, fp);
                }
                break;

            case 2:
                rewind(fp);
                printf("\nEmployee Records:\n");
                while (fread(&emp, sizeof(emp), 1, fp))
                    printf("ID: %d | Name: %s | Salary: %.2f\n", emp.id, emp.name, emp.salary);
                break;

            case 3:
                printf("Enter record number to update (starting from 1): ");
                scanf("%d", &rec);
                fseek(fp, (rec - 1) * sizeof(emp), SEEK_SET);
                fread(&emp, sizeof(emp), 1, fp);
                printf("Current Salary: %.2f\n", emp.salary);
                printf("Enter new Salary: ");
                scanf("%f", &emp.salary);
                fseek(fp, (rec - 1) * sizeof(emp), SEEK_SET);
                fwrite(&emp, sizeof(emp), 1, fp);
                printf("Record updated successfully.\n");
                break;

            case 4:
                fclose(fp);
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    } while (1);

    return 0;
}

