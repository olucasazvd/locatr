#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

size_t write_callback(void *ptr, size_t size, size_t nmemb, char *data) {
    size_t total_size = size*nmemb;
    strncat(data, ptr, total_size);
    return total_size;
}

CURLcode perform_request(char *ip, char *response_data) {
    CURLcode ret;
    CURL *hnd;
    char url[256]= "http://ipwho.is/";

    strcat(url, ip);
    
    hnd = curl_easy_init();
    if (hnd) {
        hnd = curl_easy_init();

        curl_easy_setopt(hnd, CURLOPT_BUFFERSIZE, 102400L); 
        curl_easy_setopt(hnd, CURLOPT_URL, url);
        curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.81.0");
        curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(hnd, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2TLS);
        curl_easy_setopt(hnd, CURLOPT_FTP_SKIP_PASV_IP, 1L);
        curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(hnd, CURLOPT_WRITEDATA, response_data);
        
        ret = curl_easy_perform(hnd);
        curl_easy_cleanup(hnd);
    } else {
        ret = CURLE_FAILED_INIT;
    }

    return ret;
}
