/*
    Author: Lucas Azevedo
*/
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <request.h>

// Callback function to handle the data received from the server during the request
// This function is called by the libcurl when it receives data from the server
// Parameters:
// - ptr: pointer to the data received
// - size: size of each element (bytes)
// - nmemb: number of elements received
// - data: pointer to the data buffer where the data will be stored
// Returns:
// The total size of bytes written to the data buffer, which will be used by the libcurl to determine if the write was successful
size_t write_callback(void *ptr, size_t size, size_t nmemb, char *data) {
    size_t total_size = size*nmemb;
    strncat(data, ptr, total_size);
    return total_size;
}

// Perform a request to the ipwho.is API to get information about an IP address
// Parameters:
// - ip: the IP address to be queried
// - response_data: pointer to the buffer where the response data will be stored
// Returns:
// The CURLcode returned by the libcurl after the request
CURLcode perform_whois_request(char *ip, char *response_data) {
    CURLcode ret;
    CURL *hnd;
    char url[256]= "http://ipwho.is/"; // URL to the ipwho.is API

    strcat(url, ip); // Concatenate the IP address to the URL
    
    // Initialize the libcurl handle
    hnd = curl_easy_init();
    if (hnd) {
        hnd = curl_easy_init();

        curl_easy_setopt(hnd, CURLOPT_BUFFERSIZE, 102400L); // Set the buffer size to 100KB
        curl_easy_setopt(hnd, CURLOPT_URL, url); // Set the URL to be queried
        curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L); // Disable progress meter
        curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.81.0"); // Set the user agent
        curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L); // Set the maximum number of redirections
        curl_easy_setopt(hnd, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2TLS); // Set the HTTP version
        curl_easy_setopt(hnd, CURLOPT_FTP_SKIP_PASV_IP, 1L); // Skip the IP address in the PASV response
        curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L); // Enable TCP keepalive
        curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_callback); // Set the callback function to handle the data received
        curl_easy_setopt(hnd, CURLOPT_WRITEDATA, response_data); // Set the buffer where the response data will be stored
        
        ret = curl_easy_perform(hnd); // Perform the request
        curl_easy_cleanup(hnd); // Cleanup the libcurl handle
    } else {
        ret = CURLE_FAILED_INIT; // Return an error if the libcurl handle could not be initialized
    }

    return ret;
}
