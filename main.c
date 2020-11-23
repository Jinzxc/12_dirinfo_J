#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry = readdir(dir);
    struct stat info;
    int size = 0;
    
    printf("Statistics for directory: %s\n", entry -> d_name);

    while(entry) {
        if(entry->d_type == DT_REG) {
            stat(entry->d_name, &info);
            size += info.st_size;
        }

        entry = readdir(dir);
    }

    printf("Total Directory Size: %d Bytes\n", size);
    
    rewinddir(dir);
    entry = readdir(dir);

    printf("Directories:\n");

    while(entry) {
        if(entry->d_type == DT_DIR) {
            printf("\t%s\n", entry -> d_name);
        }

        entry = readdir(dir);
    }

    rewinddir(dir);
    entry = readdir(dir);

    printf("Regular Files:\n");

    while(entry) {
        if(entry->d_type == DT_REG) {
            printf("\t%s\n", entry -> d_name);
        }

        entry = readdir(dir);
    }

    closedir(dir);
    return 0;
}