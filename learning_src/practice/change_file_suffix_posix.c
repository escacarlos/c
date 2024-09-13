#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void change_file_suffix(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Check if it's a regular file
            const char *filename = entry->d_name;
            size_t len = strlen(filename);

            if (len > 3 && strcmp(filename + len - 3, ".cc") == 0) {
                char old_path[1024];
                snprintf(old_path, sizeof(old_path), "%s/%s", path, filename);

                char new_filename[1024];
                strncpy(new_filename, filename, len - 2);
                new_filename[len - 2] = '\0';
                strcat(new_filename, ".c");

                char new_path[1024];
                snprintf(new_path, sizeof(new_path), "%s/%s", path, new_filename);

                if (rename(old_path, new_path) != 0) {
                    perror("rename");
                } else {
                    printf("Renamed: %s -> %s\n", old_path, new_path);
                }
            }
        }
    }

    closedir(dir);
}

int main() {
    const char *root_directory = "."; // Change this to the root directory path
    change_file_suffix(root_directory);
    return 0;
}
