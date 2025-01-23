#ifndef REQUEST_H
#define REQUEST_H

#include <curl/curl.h>

size_t write_callback(void *ptr, size_t size, size_t nmemb, char *data);

CURLcode perform_whois_request(char *ip, char *response_data);

#endif // REQUEST_H

