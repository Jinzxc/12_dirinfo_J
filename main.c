#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char **argv) {
    char cdir[100];
    char path[100];
    int size = 0;
    struct dirent *entry;
    struct stat info;

    if(argc > 1) {
        strncpy(cdir, argv[1], sizeof(cdir) - 1);
    } else {
        printf("Input directory to search: ");
        fgets(cdir, sizeof(cdir), stdin);
    }

    char *nl = strrchr(cdir, '\n');

    if(nl) {
        *nl = '\0';
    }

    DIR *dir = opendir(cdir);

    if(dir == NULL) {
        printf("%s as %s\n", strerror(errno), cdir);
        return 0;
    }

    entry = readdir(dir);
    
    printf("Statistics for directory: %s\n", cdir);

    while(entry) {
        if(entry->d_type == DT_REG) {
            strcpy(path, cdir);
            strcat(path, "/");
            strcat(path, entry->d_name);
            stat(path, &info);
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