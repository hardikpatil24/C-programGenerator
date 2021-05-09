#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>

#define MAX_TEXT_LENGTH 1024

char* nlp_process(char* text) {
    /* Tokenize the text */
    char* tokens[MAX_TEXT_LENGTH];
    int num_tokens = tokenize(text, tokens);

    /* Remove stopwords */
    char processed_text[MAX_TEXT_LENGTH];
    int pos = 0;
    for (int i = 0; i < num_tokens; i++) {
        if (!is_stopword(tokens[i])) {
            strcpy(processed_text + pos, tokens[i]);
            pos += strlen(tokens[i]);
            processed_text[pos++] = ' ';
        }
    }
    processed_text[pos] = '\0';

    /* Copy the processed text to a new string */
    char* result = (char*) malloc(strlen(processed_text) + 1);
    strcpy(result, processed_text);

    return result;
}

int tokenize(char* text, char** tokens) {
    int num_tokens = 0;

    char* word = strtok(text, " \n\t\r");
    while (word != NULL) {
        /* Convert to lowercase */
        for (int i = 0; i < strlen(word); i++) {
            word[i] = tolower(word[i]);
        }

        tokens[num_tokens++] = word;
        word = strtok(NULL, " \n\t\r");
    }

    return num_tokens;
}

int is_stopword(char* word) {
    /* TODO: Implement stopword removal using a list of common stopwords */
    /* Return 1 if the word is a stopword, 0 otherwise */
    /* For example, you can check if the word is "the", "and", "of", etc. */
}

int is_file_matching_keyword(char* filename, char* keyword) {
    /* Check if the filename contains the keyword */
    if (strstr(filename, keyword) != NULL) {
        return 1;
    }
    return 0;
}

char* find_matching_file(char* keyword) {
    /* Open the program_data directory */
    DIR* dir = opendir("program_data");
    if (dir == NULL) {
        fprintf(stderr, "Error: Cannot open program_data directory\n");
        exit(1);
    }

    /* Loop through all the files in the directory */
    struct dirent* dp;
    while ((dp = readdir(dir)) != NULL) {
        /* Ignore special directories */
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
            continue;
        }

        /* Check if the file matches the keyword */
        if (is_file_matching_keyword(dp->d_name, keyword)) {
            /* Return the filename */
            char* filename = (char*) malloc(strlen(dp->d_name) + 1);
            strcpy(filename, dp->d_name);
            closedir(dir);
            return filename;
        }
    }

    /* No matching file found */
    closedir(dir);
    return NULL;
}

void copy_file_to_output(char* filename, char* output_filename) {
    /* Open the input file */
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "program_data/%s", filename);
    FILE* input_file = fopen(filepath, "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error: Cannot open file %s\n", filepath);
        exit(1);
    }

    /* Open the output file */
    FILE* output_file = fopen(output_filename, "w
