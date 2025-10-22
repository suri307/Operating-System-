#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("."); // Open current directory
    if (dir == NULL) {
        printf("Unable to open directory!\n");
        return 1;
    }

    printf("Files in current directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        // Skip . and .. if you want only actual files
        if (entry->d_name[0] != '.')
            printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}

