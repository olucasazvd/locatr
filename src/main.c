/*
* Author: Lucas Azevedo
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "request.h"
#include "model.h"
#include "asciiart.h"
#include "cJSON.h"
#include "ANSI-color-codes.h"

// Function to print ASCII art and IP information side by side, with specified spacing; Without ANSI color codes
// Parameters:
// - ascii_art: A string contianing the ASCII art to be printed
// - info: A string containing the informating text associated with the ASCII art
// - spacing: The number of spaces between the ASCII art and the information text
void RenderASCIIAndIPInfoPlain(const char *ascii_art, const char *info, int spacing) {    
    char ascii_lines[100][256];  
    char info_lines[100][256];   
    int ascii_count = 0, info_count = 0;
    int max_ascii_width = 0;

    // Split the ASCII art and information text into lines and store them in ascii_lines
    const char *start = ascii_art;
    while (*start && ascii_count < 100) {
        char *end = strchr(start, '\n');
        int len = end ? (end - start) : strlen(start);
        strncpy(ascii_lines[ascii_count], start, len);
        ascii_lines[ascii_count][len] = '\0';
        if (len > max_ascii_width) max_ascii_width = len;
        ascii_count++;
        start = end ? (end + 1) : NULL;
    }

    // Split the information text into lines and store them in info_lines
    start = info;
    while (*start && info_count < 100) {
        char *end = strchr(start, '\n');
        int len = end ? (end - start) : strlen(start);
        strncpy(info_lines[info_count], start, len);
        info_lines[info_count][len] = '\0';
        info_count++;
        start = end ? (end + 1) : NULL;
    }

    // Calculate the number of lines to pad the ASCII art with
    int padding_top = (ascii_count - info_count) / 2;
    if (padding_top < 0) padding_top = 0;

    // Print the ASCII art and information text side by side
    for (int i = 0; i < ascii_count; i++) {
        printf("%-*s", max_ascii_width + spacing, ascii_lines[i]);

        if (i >= padding_top && (i - padding_top) < info_count) {
            printf("%s", info_lines[i - padding_top]);
        }
        printf("\n");
    }
}

// Main function
int main(int argc, char* argv[]) {

    // Check if the user provided an IP address    
    if (argc != 2) {
        printf("Usage: locatr <IP>\n");
        return 1;
    }
    
    CURLcode ret; // Variable to store the return code of the curl request
    char response_data[4096] = ""; // Pre-allocate a buffer to store the response data
    char ip[16]; // Pre-allocate a buffer to store the IP address

    strncpy(ip, argv[1], sizeof(ip) - 1); // Copy the IP address provided by the user to the ip buffer
    ip[sizeof(ip) - 1] = '\0'; // Null-terminate the ip buffer

    ret = perform_whois_request(ip, response_data); // Perform the request to the IP geolocation API

    IPInfo ipinfo = ParseIpDataFromApi(response_data); // Parse the response data into an IPInfo struct
    
    // Print the ASCII art and IP information
    char *ascii_art = FetchCountryASCII(ipinfo.country_code); 
    char *info_text = GenerateIPInfoSnippet(ipinfo);
    RenderASCIIAndIPInfoPlain(ascii_art, info_text, 7);

    // Free the allocated memory
    free(ascii_art);
    free(info_text);


    return 0;
}

