#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "asciiart.h"

void to_lowercase(char* str) {
    while (*str) {
        *str = tolower((unsigned char) *str);
        str++;
    }
}

char *get_country_art(const char* continent_code) {
    char continent_code_lower[10];
    snprintf(continent_code_lower, sizeof(continent_code_lower), "%s", continent_code);
    to_lowercase(continent_code_lower);

    char filename[256];
    snprintf(filename, sizeof(filename), "assets/countries_ascii/%s/%s.txt", continent_code_lower, continent_code_lower);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return strdup("Cannot find any art for this country");
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    char *art = malloc(filesize + 1);
    if (art == NULL) {
        fclose(file);
        return strdup("Memory allocation failed");
    }

    fread(art, 1, filesize, file);
    art[filesize] = '\0';

    fclose(file);
    return art;
}