#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    // Check if the user provided a directory argument
    if (argc != 2) {
        printf("Usage: myls <directory>\n", argv[0]);
        return 1;
    }

    printf("Listing contents of directory: %s\n", argv[1]);

    // Open the directory
    DIR *dir = opendir(argv[1]);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Read the directory entries
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);

    return 0;
}