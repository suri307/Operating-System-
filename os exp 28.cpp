#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    char filename[50], line[200], pattern[50];
    int line_no = 0, found = 0;

    // Input file name
    printf("Enter file name: ");
    scanf("%s", filename);

    // Input pattern to search
    printf("Enter string to search: ");
    scanf("%s", pattern);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("File not found!\n");
        return 1;
    }

    printf("\nMatching lines:\n");
    while (fgets(line, sizeof(line), fp)) {
        line_no++;
        if (strstr(line, pattern) != NULL) {
            printf("Line %d: %s", line_no, line);
            found = 1;
        }
    }

    if (!found)
        printf("No match found.\n");

    fclose(fp);
    return 0;
}

