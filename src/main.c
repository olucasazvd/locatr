/*
* Author: Lucas Azevedo
*/
// External headers
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Local headers
#include "request.h"
#include "model.h"
#include "asciiart.h"
#include "cJSON.h"
#include "ANSI-color-codes.h"

// Print two strings side by side with a given spacing; the first string is the ASCII art and the second is the information text
void print_side_by_side(const char *ascii_art, const char *info, int spacing) {    
    char ascii_lines[100][256];  
    char info_lines[100][256];   
    int ascii_count = 0, info_count = 0;
    int max_ascii_width = 0;

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

    start = info;
    while (*start && info_count < 100) {
        char *end = strchr(start, '\n');
        int len = end ? (end - start) : strlen(start);
        strncpy(info_lines[info_count], start, len);
        info_lines[info_count][len] = '\0';
        info_count++;
        start = end ? (end + 1) : NULL;
    }

    int padding_top = (ascii_count - info_count) / 2;
    if (padding_top < 0) padding_top = 0;

    for (int i = 0; i < ascii_count; i++) {
        printf("%-*s", max_ascii_width + spacing, ascii_lines[i]);

        if (i >= padding_top && (i - padding_top) < info_count) {
            printf("%s", info_lines[i - padding_top]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    
    if (argc != 2) {
        printf("Usage: locatr <IP>\n");
        return 1;
    }
    
    CURLcode ret;
    char response_data[4096] = "";
    char ip[16];

    strncpy(ip, argv[1], sizeof(ip) - 1);
    ip[sizeof(ip) - 1] = '\0';

    ret = perform_request(ip, response_data);

    IPInfo ipinfo = parse_http_response(response_data);
    
    char *ascii_art = get_country_art(ipinfo.country_code);
    char *info_text = get_main_info(ipinfo);

    print_side_by_side(ascii_art, info_text, 7);

    free(ascii_art);
    free(info_text);


    return 0;
}

