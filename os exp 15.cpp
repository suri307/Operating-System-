#include <stdio.h>
#include <string.h>

#define MAX_USERS 5
#define MAX_FILES 10
#define MAX_NAME 30

typedef struct {
    char userName[MAX_NAME];
    char files[MAX_FILES][MAX_NAME];
    int fileCount;
} UserDirectory;

int main() {
    UserDirectory users[MAX_USERS];
    int userCount = 0;
    int choice, i, j;
    char name[MAX_NAME], file[MAX_NAME];

    do {
        printf("\nMenu:\n1.Create User\n2.Create File\n3.Delete File\n4.Search File\n5.Display Files\n6.Exit\nChoice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: { // Create User
                if(userCount < MAX_USERS) {
                    printf("Enter user name: ");
                    scanf("%s", name);
                    strcpy(users[userCount].userName, name);
                    users[userCount].fileCount = 0;
                    userCount++;
                    printf("User created successfully.\n");
                } else printf("Maximum users reached!\n");
                break;
            }

            case 2: { // Create File
                int foundUser = -1;
                printf("Enter user name: ");
                scanf("%s", name);
                for(i=0;i<userCount;i++)
                    if(strcmp(users[i].userName, name) == 0) { foundUser=i; break; }
                if(foundUser == -1) { printf("User not found!\n"); break; }

                if(users[foundUser].fileCount < MAX_FILES) {
                    printf("Enter file name: ");
                    scanf("%s", file);
                    strcpy(users[foundUser].files[users[foundUser].fileCount], file);
                    users[foundUser].fileCount++;
                    printf("File created successfully.\n");
                } else printf("User's directory full!\n");
                break;
            }

            case 3: { // Delete File
                int foundUser=-1, foundFile=0;
                printf("Enter user name: ");
                scanf("%s", name);
                for(i=0;i<userCount;i++)
                    if(strcmp(users[i].userName, name) == 0) { foundUser=i; break; }
                if(foundUser == -1) { printf("User not found!\n"); break; }

                printf("Enter file name to delete: ");
                scanf("%s", file);
                for(j=0;j<users[foundUser].fileCount;j++) {
                    if(strcmp(users[foundUser].files[j], file) == 0) {
                        int k;
                        for(k=j;k<users[foundUser].fileCount-1;k++)
                            strcpy(users[foundUser].files[k], users[foundUser].files[k+1]);
                        users[foundUser].fileCount--;
                        foundFile=1;
                        printf("File deleted successfully.\n");
                        break;
                    }
                }
                if(!foundFile) printf("File not found.\n");
                break;
            }

            case 4: { // Search File
                int foundUser=-1, foundFile=0;
                printf("Enter user name: ");
                scanf("%s", name);
                for(i=0;i<userCount;i++)
                    if(strcmp(users[i].userName, name) == 0) { foundUser=i; break; }
                if(foundUser == -1) { printf("User not found!\n"); break; }

                printf("Enter file name to search: ");
                scanf("%s", file);
                for(j=0;j<users[foundUser].fileCount;j++)
                    if(strcmp(users[foundUser].files[j], file) == 0) { foundFile=1; break; }
                printf(foundFile ? "File found.\n" : "File not found.\n");
                break;
            }

            case 5: { // Display Files
                int foundUser=-1;
                printf("Enter user name: ");
                scanf("%s", name);
                for(i=0;i<userCount;i++)
                    if(strcmp(users[i].userName, name) == 0) { foundUser=i; break; }
                if(foundUser == -1) { printf("User not found!\n"); break; }

                printf("Files of user %s:\n", name);
                for(j=0;j<users[foundUser].fileCount;j++)
                    printf("%s\n", users[foundUser].files[j]);
                break;
            }

            case 6:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 6);

    return 0;
}
1
