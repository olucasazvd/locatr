#include <stdio.h>
#include "../include/model.h"
#include "../lib/CJSON.c"
#include <stdlib.h>
#include <string.h>

IPInfo parse_http_response(char *response){
    
    IPInfo ipinfo;
    
    cJSON *json = cJSON_Parse(response);
    
    // cJSON_GetObjectItem(json, "continent")->valuestring
    //
    //

    
    
}


