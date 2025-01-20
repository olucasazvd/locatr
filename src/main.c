#include <stdio.h>
#include "request.c"
#include "../lib/cJSON.c"

int main() {
    
    CURLcode ret;
    char response_data[4096] = "";
    char *ip = "8.8.8.8";
    ret = perform_request(ip, response_data);
    
    /*
    cJSON *request_json = cJSON_Parse(response_data);
    cJSON *continent = cJSON_GetObjectItem(request_json, "continent");

    printf("%s", continent->valuestring);
    */
}
