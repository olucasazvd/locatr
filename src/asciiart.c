#include <stdio.h>
#include <stdlib.h>
#include "asciiart.h"

void to_lowercase(char* str) {
	while (*str) {
		*str = tolower((unsigned char) *str);
		str++;
	}
}

void print_country_art(const char* continent_code) {
	
	char continent_code_lower[10];
	snprintf(continent_code_lower, sizeof(continent_code_lower), "%s", continent_code);

	to_lowercase(continent_code_lower);

	char filename[256];
	snprintf(filename, sizeof(filename), "assets/countries_ascii/%s/%s.txt", continent_code_lower, continent_code_lower);

	FILE *file = fopen(filename, "r");
	if(file == NULL) {
		printf("Cannot find any art for this country");
		return;
	}

	char ch;
	while ((ch = fgetc(file)) != EOF) {
		putchar(ch);
	}

	fclose(file);
}
