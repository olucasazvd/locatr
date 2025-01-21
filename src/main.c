#include <stdio.h>
#include "request.h"
#include "cJSON.h"
#include "model.h"

int main() {
    
    CURLcode ret;
    char response_data[4096] = "";
    char ip[16];

    ret = perform_request(ip, response_data);
    
    IPInfo ipinfo = parse_http_response(response_data);

}
