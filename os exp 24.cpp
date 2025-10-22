#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char write_buf[] = "Hello, this is a UNIX file system call demo!";
    char read_buf[100];

    // Create and open file for writing
    fd = open("demo.txt", O_CREAT | O_RDWR, 0777);
    if (fd < 0) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write to the file
    write(fd, write_buf, sizeof(write_buf));
    printf("Data written to file successfully.\n");

    // Move file pointer to beginning
    lseek(fd, 0, SEEK_SET);

    // Read data from file
    read(fd, read_buf, sizeof(write_buf));
    printf("Data read from file: %s\n", read_buf);

    // Close file
    close(fd);
    printf("File closed successfully.\n");

    return 0;
}

