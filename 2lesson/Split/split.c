#include <stdlib.h>
#include <stdio.h>
#include <string.h>


size_t Split(char* str, char* del, char** words)
{
    char* word = strtok(str, del);
    int i = 0;
    for (i = 0; word != NULL ; i++) {
        words[i] = word;
        word = strtok(NULL, del);
    }
    return i;
}

int main()
{
    char del[] = "!? :,;";

    FILE* file = fopen("input.txt", "r");
    if (!file) {
        printf("File not found\n");
        return 1;
    }

    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* str = (char*)calloc(size + 1, sizeof(char));
    fread(str, sizeof(char), size, file);
    fclose(file);

    char** words = (char**)calloc(size, sizeof(char*));
    size_t N = Split(str, del, words);

    for (size_t i = 0; i < N; i++)
        printf("%u : %s\n", i + 1, words[i]);

    return 0;
}
