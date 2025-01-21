#include <stdio.h>
#include <string.h>
#include "request.h"
#include "cJSON.h"
#include "model.h"
#include "asciiart.h"

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

    print_country_art(ipinfo.country_code);
    printf("IP: %s\n", ipinfo.ip);
    printf("Country: %s (%s)\n", ipinfo.country, ipinfo.country_code);
    printf("Region: %s (%s)\n", ipinfo.region, ipinfo.region_code);
    printf("City: %s\n", ipinfo.city);
    printf("Location: %f %f\n", ipinfo.latitude, ipinfo.longitude);
    printf("Zip Code: %s\n", ipinfo.postal);
    printf("ASN: %d %s\n", ipinfo.connection.asn, ipinfo.connection.org);
    printf("ISP: %s\n", ipinfo.connection.isp);
    printf("TZ: %s\n", ipinfo.timezone.id);

    return 0;
}

