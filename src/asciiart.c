/*
* Author: Lucas Azevedo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "asciiart.h"

// Function to convert a string to lowercase
// This function modifies the input string in place
// Parameters:
// - str: A pointer to the string to be converted to lowercase
void ToLowercase(char* str) {
    // Iterate over each character in the string
    while (*str) {
        *str = tolower((unsigned char) *str);
        str++;
    }
}

// Function to retrieve ASCII art for a specific country based on its continent code
// It constructs the filename from the continent code and tries to read the corresponding ASCII art
// Parameters:
// - continent_code: A string containing the continent code of the country
// Returns:
// - A string containing the ASCII art for the country
char *FetchCountryASCII(const char* continent_code) {

    // Convert the continent code to lowercase
    char continent_code_lower[10];
    snprintf(continent_code_lower, sizeof(continent_code_lower), "%s", continent_code);
    ToLowercase(continent_code_lower);

    // Construct the filename based on the continent code
    char filename[256];
    snprintf(filename, sizeof(filename), "assets/countries_ascii/%s/%s.txt", continent_code_lower, continent_code_lower);

    // Attempt to open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return strdup("Cannot find any art for this country"); // Return an error message if the file cannot be opened
    }

    // Seek to the end of the file to determine its size
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    // Allocate memory to store the ASCII art
    char *art = malloc(filesize + 1); // +1 for null terminator
    if (art == NULL) {
        fclose(file);
        return strdup("Memory allocation failed"); 
    }

    // Read the contents of the file into the art buffer
    fread(art, 1, filesize, file);
    art[filesize] = '\0'; // Null-terminate the string

    fclose(file); // Close the file
    return art; // Return the ASCII art
}