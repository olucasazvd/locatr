#ifndef MODEL_H
#define MODEL_H

#include <stdbool.h>

typedef struct {
    char img[256];
    char emoji[16];
    char emoji_unicode[32];
} Flag;

typedef struct {
    int asn;
    char org[128];
    char isp[128];
    char domain[128];
} Connection;

typedef struct {
    char id[64];
    char abbr[8];
    bool is_dst;
    int offset;
    char utc[8];
    char current_time[32];
} Timezone;

typedef struct {
    char ip[16];
    bool success;
    char type[16];
    char continent[64];
    char continent_code[4];
    char country[64];
    char country_code[4];
    char region[64];
    char region_code[4];
    char city[64];
    double latitude;
    double longitude;
    bool is_eu;
    char postal[16];
    char calling_code[8];
    char capital[64];
    char borders[16];
    Flag flag;
    Connection connection;
    Timezone timezone;
} IPInfo;

char *GenerateIPInfoSnippet(IPInfo ipinfo);

IPInfo ParseIpDataFromApi(char *response);

#endif /* MODEL_H */

