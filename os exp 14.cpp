#include <stdio.h>
#include <string.h>

#define MAX_FILES 10
#define MAX_NAME 30

int main() {
    char dirName[MAX_NAME], files[MAX_FILES][MAX_NAME];
    int fileCount = 0, choice;
    char file[MAX_NAME];

    printf("Enter directory name: ");
    scanf("%s", dirName);

    do {
        printf("\n1.Create 2.Delete 3.Search 4.Display 5.Exit\nChoice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: // Create File
            {
                if(fileCount < MAX_FILES) {
                    printf("File name: ");
                    scanf("%s", file);
                    strcpy(files[fileCount++], file);
                    printf("File created.\n");
                } else printf("Directory full!\n");
                break;
            }

            case 2: // Delete File
            {
                int i, j;
                printf("File name to delete: ");
                scanf("%s", file);
                int found = 0;
                for(i=0;i<fileCount;i++) {
                    if(strcmp(files[i], file) == 0) {
                        for(j=i;j<fileCount-1;j++)
                            strcpy(files[j], files[j+1]);
                        fileCount--;
                        found = 1;
                        printf("File deleted.\n");
                        break;
                    }
                }
                if(!found) printf("File not found.\n");
                break;
            }

            case 3: // Search File
            {
                int i, found = 0;
                printf("File name to search: ");
                scanf("%s", file);
                for(i=0;i<fileCount;i++)
                    if(strcmp(files[i], file)==0) { found=1; break; }
                printf(found ? "File found.\n" : "File not found.\n");
                break;
            }

            case 4: // Display Files
            {
                int i;
                printf("Files in %s:\n", dirName);
                for(i=0;i<fileCount;i++) printf("%s\n", files[i]);
                break;
            }

            case 5:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 5);

    return 0;
}


