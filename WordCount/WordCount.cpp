#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 1000
#define MAX_WORD_LENGTH 100

int countCharacters(FILE* file) {
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    return count;
}

int countWords(FILE* file) {
    int count = 0;
    char line[MAX_WORD_LENGTH];
    while (fgets(line, MAX_WORD_LENGTH, file) != NULL) {
        char* token;
        char* next_token = NULL;
        token = strtok_s(line, " ,\n", &next_token);
        while (token != NULL) {
            count++;
            token = strtok_s(NULL, " ,\n", &next_token);
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s [-c | -w] [input_file_name]\n", argv[0]);
        return 1;
    }

    char* option = argv[1];
    char* filename = argv[2];

    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        printf("Error opening file.\n");
        return 1;
    }

    int count = 0;
    if (strcmp(option, "-c") == 0) {
        count = countCharacters(file);
        printf("字符数：%d\n", count);
    }
    else if (strcmp(option, "-w") == 0) {
        count = countWords(file);
        printf("单词数：%d\n", count);
    }
    else {
        printf("Invalid option. Please use -c or -w.\n");
        return 1;
    }

    fclose(file);
    return 0;
}