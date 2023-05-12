#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100

typedef struct {
    char filename[50];
    int size;
} File;

typedef struct {
    char dirname[50];
    File files[MAX_FILES];
    int fileCount;
} Directory;

void createFile(Directory *directory, const char *filename, int size) {
    if (directory->fileCount >= MAX_FILES) {
        printf("Directory is full. Cannot create more files.\n");
        return;
    }

    strcpy(directory->files[directory->fileCount].filename, filename);
    directory->files[directory->fileCount].size = size;
    directory->fileCount++;

    printf("File '%s' created successfully.\n", filename);
}

void listFiles(const Directory *directory) {
    printf("Files in directory '%s':\n", directory->dirname);
    if (directory->fileCount == 0) {
        printf("No files found.\n");
        return;
    }

    for (int i = 0; i < directory->fileCount; i++) {
        printf("File: %s, Size: %d bytes\n", directory->files[i].filename, directory->files[i].size);
    }
}

int main() {
    Directory directory;
    strcpy(directory.dirname, "MyDirectory");
    directory.fileCount = 0;

    createFile(&directory, "file1.txt", 1024);
    createFile(&directory, "file2.jpg", 2048);
    createFile(&directory, "file3.doc", 512);

    listFiles(&directory);

    return 0;
}
