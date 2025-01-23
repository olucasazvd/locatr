/*
    Author: Lucas Azevedo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "model.h"
#include "cJSON.h"

// Set a string value from a JSON object to a destination buffer
// Parameters:
// - json: cJSON object containing the JSON data
// - key: key to search in the JSON object
// - dest: destination buffer where the string will be copied
// - size: size of the destination buffer to avoid buffer overflow
void set_json_string(cJSON *json, const char *key, char *dest, size_t size) {
    cJSON *item = cJSON_GetObjectItem(json, key);
    if (item && cJSON_IsString(item)) {
        strncpy(dest, item->valuestring, size - 1);
    }
}

// Set an integer value from a JSON object to a destination variable
// Parameters:
// - json: cJSON object containing the JSON data
// - key: key to search in the JSON object
// - dest: destination variable where the integer will be stored
void set_json_int(cJSON *json, const char *key, int *dest) {
    cJSON *item = cJSON_GetObjectItem(json, key);
    if (item && cJSON_IsNumber(item)) {
        *dest = item->valueint;
    }
}

// Set a double value from a JSON object to a destination double pointer
// Parameters:
// - json: cJSON object containing the JSON data
// - key: key to search in the JSON object
// - dest: destination double pointer where the double will be stored
void set_json_double(cJSON *json, const char *key, double *dest) {
    cJSON *item = cJSON_GetObjectItem(json, key);
    if (item && cJSON_IsNumber(item)) {
        *dest = item->valuedouble;
    }
}

// Set a boolean value from a JSON object to a destination boolean pointer
// Parameters:
// - json: cJSON object containing the JSON data
// - key: key to search in the JSON object
// - dest: destination boolean pointer where the boolean will be stored
void set_json_bool(cJSON *json, const char *key, bool *dest) {
    cJSON *item = cJSON_GetObjectItem(json, key);
    if (item && cJSON_IsBool(item)) {
        *dest = cJSON_IsTrue(item);
    }
}

// Function to format and return the main information of the IP address as a string
// Parameters:
// - ipinfo: IPInfo structure containing the IP address information
// Returns:
// - a string containing the main information of the IP address
char *GenerateIPInfoSnippet(IPInfo ipinfo) {
    char *info = malloc(1024);
    snprintf(info, 1024, "IP: %s\nCountry: %s (%s)\nRegion: %s (%s)\nCity: %s\nLocation: %f %f\nZip Code: %s\nASN: %d %s\nISP: %s\nTZ: %s\n",
        ipinfo.ip, ipinfo.country, ipinfo.country_code, ipinfo.region, ipinfo.region_code, ipinfo.city, ipinfo.latitude, ipinfo.longitude, ipinfo.postal, ipinfo.connection.asn, ipinfo.connection.org, ipinfo.connection.isp, ipinfo.timezone.id);
    return info;
}

// Function to parse the JSON response from the API and store it in an IPInfo structure
// Parameters:
// - response: string containing the JSON response from the API
// Returns:
// - an IPInfo structure containing the parsed information
IPInfo ParseIpDataFromApi(char *response) {
    IPInfo ipinfo = {0};  

    cJSON *json = cJSON_Parse(response);
    if (!json) {
        fprintf(stderr, "Erro ao parsear JSON\n");
        return ipinfo;
    }

    // Populate the IPInfo structure with the JSON data
    set_json_string(json, "ip", ipinfo.ip, sizeof(ipinfo.ip));
    set_json_bool(json, "success", &ipinfo.success);
    set_json_string(json, "type", ipinfo.type, sizeof(ipinfo.type));
    set_json_string(json, "continent", ipinfo.continent, sizeof(ipinfo.continent));
    set_json_string(json, "continent_code", ipinfo.continent_code, sizeof(ipinfo.continent_code));
    set_json_string(json, "country", ipinfo.country, sizeof(ipinfo.country));
    set_json_string(json, "country_code", ipinfo.country_code, sizeof(ipinfo.country_code));
    set_json_string(json, "region", ipinfo.region, sizeof(ipinfo.region));
    set_json_string(json, "region_code", ipinfo.region_code, sizeof(ipinfo.region_code));
    set_json_string(json, "city", ipinfo.city, sizeof(ipinfo.city));
    set_json_double(json, "latitude", &ipinfo.latitude);
    set_json_double(json, "longitude", &ipinfo.longitude);
    set_json_bool(json, "is_eu", &ipinfo.is_eu);
    set_json_string(json, "postal", ipinfo.postal, sizeof(ipinfo.postal));
    set_json_string(json, "calling_code", ipinfo.calling_code, sizeof(ipinfo.calling_code));
    set_json_string(json, "capital", ipinfo.capital, sizeof(ipinfo.capital));
    set_json_string(json, "borders", ipinfo.borders, sizeof(ipinfo.borders));

    // Handle the flag object
    cJSON *flag = cJSON_GetObjectItem(json, "flag");
    if (flag) {
        set_json_string(flag, "img", ipinfo.flag.img, sizeof(ipinfo.flag.img));
        set_json_string(flag, "emoji", ipinfo.flag.emoji, sizeof(ipinfo.flag.emoji));
        set_json_string(flag, "emoji_unicode", ipinfo.flag.emoji_unicode, sizeof(ipinfo.flag.emoji_unicode));
    }

    // Handle the connection object
    cJSON *connection = cJSON_GetObjectItem(json, "connection");
    if (connection) {
        set_json_int(connection, "asn", &ipinfo.connection.asn);
        set_json_string(connection, "org", ipinfo.connection.org, sizeof(ipinfo.connection.org));
        set_json_string(connection, "isp", ipinfo.connection.isp, sizeof(ipinfo.connection.isp));
        set_json_string(connection, "domain", ipinfo.connection.domain, sizeof(ipinfo.connection.domain));
    }

    // Handle the timezone object
    cJSON *timezone = cJSON_GetObjectItem(json, "timezone");
    if (timezone) {
        set_json_string(timezone, "id", ipinfo.timezone.id, sizeof(ipinfo.timezone.id));
        set_json_string(timezone, "abbr", ipinfo.timezone.abbr, sizeof(ipinfo.timezone.abbr));
        set_json_bool(timezone, "is_dst", &ipinfo.timezone.is_dst);
        set_json_int(timezone, "offset", &ipinfo.timezone.offset);
        set_json_string(timezone, "utc", ipinfo.timezone.utc, sizeof(ipinfo.timezone.utc));
        set_json_string(timezone, "current_time", ipinfo.timezone.current_time, sizeof(ipinfo.timezone.current_time));
    }

    cJSON_Delete(json); // Free the cJSON object
    return ipinfo; // Return the IPInfo structure
}

