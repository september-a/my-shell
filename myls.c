#include <stdio.h>
#include <dirent.h>
#include <string.h>


int main(int argc, char *argv[]) {
    int show_all = 0; // Flag to indicate whether to show hidden files

    // Check if the user provided a directory argument
    if ((argc < 2) || (argc > 3)) {
        printf("Usage: myls [-a] <directory>\n");
        return 1;
    }

    // Check if the "-a" option is provided
    if (argc == 3 && strcmp(argv[1], "-a") == 0) {
        show_all = 1;
    } else if (argc == 3) {
        printf("Invalid option: %s\n", argv[1]);
        printf("Usage: myls [-a] <directory>\n");
        return 1;
    }

    // Determine the index of the directory argument based on whether "-a" is provided
    int dir_index = show_all ? 2 : 1;

    printf("Listing contents of directory: %s\n", argv[dir_index]);

    // Open the directory
    DIR *dir = opendir(argv[dir_index]);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Read the directory entries
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (show_all || entry->d_name[0] != '.') { // Check if "-a" is provided or if entry is not hidden
            printf("%s\n", entry->d_name);
        }
    }

    // Close the directory
    closedir(dir);

    return 0;
}