#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    char filename[50], data[200];
    int choice;

    while (1) {
        printf("\n--- FILE MANAGEMENT MENU ---\n");
        printf("1. Create File\n");
        printf("2. Write to File\n");
        printf("3. Read File\n");
        printf("4. Append to File\n");
        printf("5. Delete File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline left by scanf

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0; // remove newline
                fp = fopen(filename, "w");
                if (fp == NULL) {
                    printf("Error creating file!\n");
                } else {
                    printf("File '%s' created successfully.\n", filename);
                    fclose(fp);
                }
                break;

            case 2:
                printf("Enter file name: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;
                fp = fopen(filename, "w");
                if (fp == NULL) {
                    printf("File not found!\n");
                } else {
                    printf("Enter data to write: ");
                    fgets(data, sizeof(data), stdin);
                    fprintf(fp, "%s", data);
                    fclose(fp);
                    printf("Data written successfully.\n");
                }
                break;

            case 3:
                printf("Enter file name: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;
                fp = fopen(filename, "r");
                if (fp == NULL) {
                    printf("File not found!\n");
                } else {
                    printf("File content:\n");
                    while (fgets(data, sizeof(data), fp) != NULL) {
                        printf("%s", data);
                    }
                    fclose(fp);
                }
                break;

            case 4:
                printf("Enter file name: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;
                fp = fopen(filename, "a");
                if (fp == NULL) {
                    printf("File not found!\n");
                } else {
                    printf("Enter data to append: ");
                    fgets(data, sizeof(data), stdin);
                    fprintf(fp, "%s", data);
                    fclose(fp);
                    printf("Data appended successfully.\n");
                }
                break;

            case 5:
                printf("Enter file name to delete: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;
                if (remove(filename) == 0)
                    printf("File deleted successfully.\n");
                else
                    printf("Error deleting file.\n");
                break;

            case 6:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

