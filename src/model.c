#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "model.h"
#include "cJSON.h"

// Função auxiliar para strings
void set_json_string(cJSON *json, const char *key, char *dest, size_t size) {
    cJSON *item = cJSON_GetObjectItem(json, key);
    if (item && cJSON_IsString(item)) {
        strncpy(dest, item->valuestring, size - 1);
    }
}

// Função auxiliar para inteiros
void set_json_int(cJSON *json, const char *key, int *dest) {
    cJSON *item = cJSON_GetObjectItem(json, key);
    if (item && cJSON_IsNumber(item)) {
        *dest = item->valueint;
    }
}

// Função auxiliar para doubles
void set_json_double(cJSON *json, const char *key, double *dest) {
    cJSON *item = cJSON_GetObjectItem(json, key);
    if (item && cJSON_IsNumber(item)) {
        *dest = item->valuedouble;
    }
}

// Função auxiliar para booleanos
void set_json_bool(cJSON *json, const char *key, bool *dest) {
    cJSON *item = cJSON_GetObjectItem(json, key);
    if (item && cJSON_IsBool(item)) {
        *dest = cJSON_IsTrue(item);
    }
}

IPInfo parse_http_response(char *response) {
    IPInfo ipinfo = {0};  // Inicializa tudo zerado

    cJSON *json = cJSON_Parse(response);
    if (!json) {
        fprintf(stderr, "Erro ao parsear JSON\n");
        return ipinfo;
    }

    // Campos diretos
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

    // Flag
    cJSON *flag = cJSON_GetObjectItem(json, "flag");
    if (flag) {
        set_json_string(flag, "img", ipinfo.flag.img, sizeof(ipinfo.flag.img));
        set_json_string(flag, "emoji", ipinfo.flag.emoji, sizeof(ipinfo.flag.emoji));
        set_json_string(flag, "emoji_unicode", ipinfo.flag.emoji_unicode, sizeof(ipinfo.flag.emoji_unicode));
    }

    // Connection
    cJSON *connection = cJSON_GetObjectItem(json, "connection");
    if (connection) {
        set_json_int(connection, "asn", &ipinfo.connection.asn);
        set_json_string(connection, "org", ipinfo.connection.org, sizeof(ipinfo.connection.org));
        set_json_string(connection, "isp", ipinfo.connection.isp, sizeof(ipinfo.connection.isp));
        set_json_string(connection, "domain", ipinfo.connection.domain, sizeof(ipinfo.connection.domain));
    }

    // Timezone
    cJSON *timezone = cJSON_GetObjectItem(json, "timezone");
    if (timezone) {
        set_json_string(timezone, "id", ipinfo.timezone.id, sizeof(ipinfo.timezone.id));
        set_json_string(timezone, "abbr", ipinfo.timezone.abbr, sizeof(ipinfo.timezone.abbr));
        set_json_bool(timezone, "is_dst", &ipinfo.timezone.is_dst);
        set_json_int(timezone, "offset", &ipinfo.timezone.offset);
        set_json_string(timezone, "utc", ipinfo.timezone.utc, sizeof(ipinfo.timezone.utc));
        set_json_string(timezone, "current_time", ipinfo.timezone.current_time, sizeof(ipinfo.timezone.current_time));
    }

    cJSON_Delete(json);
    return ipinfo;
}

