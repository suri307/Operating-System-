#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    int fd;
    char buffer[100];
    struct stat fileStat;

    // ---- Open file and write ----
    fd = open("demo.txt", O_CREAT | O_RDWR, 0777);
    if (fd < 0) {
        printf("Error opening file!\n");
        return 1;
    }

    write(fd, "Operating Systems Lab", 22);
    printf("Data written successfully.\n");

    // ---- lseek() demonstration ----
    lseek(fd, 0, SEEK_SET);  // Move to start of file
    read(fd, buffer, 22);
    buffer[22] = '\0';
    printf("Data read from file: %s\n", buffer);

    // ---- Simulated fcntl() equivalent ----
    printf("File opened in read/write mode (simulated fcntl info).\n");

    close(fd);

    // ---- stat() demonstration ----
    if (stat("demo.txt", &fileStat) < 0) {
        printf("Error retrieving file information!\n");
        return 1;
    }
    printf("\nFile Size: %ld bytes", fileStat.st_size);
    printf("\nNumber of Links: %ld", fileStat.st_nlink);
    printf("\nFile Permissions: %o\n", fileStat.st_mode & 0777);

    // ---- opendir() and readdir() demonstration ----
    DIR *dir;
    struct dirent *entry;
    dir = opendir(".");
    if (dir == NULL) {
        printf("Unable to open directory!\n");
        return 1;
    }

    printf("\nFiles in current directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);

    return 0;
}

