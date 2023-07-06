#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "sendgrid.h"

size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    size_t dataSize = size * nmemb;
    ResponseData* response = (ResponseData*)userdata;

    response->data = realloc(response->data, response->size + dataSize + 1);
    if (response->data == NULL) {
        fprintf(stderr, "Failed to allocate memory for response data.\n");
        return 0;
    }
    memcpy(&(response->data[response->size]), ptr, dataSize);
    response->size += dataSize;
    response->data[response->size] = '\0';

    return dataSize;
}

// Calculate full header size for the Auth header (api key length + "Authorization: Bearer ")
char * calculateAuthHeaderSize(const char* apiKey) {
    size_t authHeaderSize = strlen(apiKey) + 23;
    char* authHeader = malloc(authHeaderSize);
    snprintf(authHeader, authHeaderSize, "Authorization: Bearer %s", apiKey);
    return authHeader;
}

CURLcode sendEmail(const EmailParams* params, ResponseData* response) {
    CURL *curl = curl_easy_init();
    CURLcode res;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.sendgrid.com/v3/mail/send");
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        
        
        char* authHeader = calculateAuthHeaderSize(params->apiKey);
        if (authHeader == NULL) {
            fprintf(stderr, "Failed to allocate memory for auth header.\n");
            return 1;
        }        

        headers = curl_slist_append(headers, authHeader);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        char data[4096];
        snprintf(data, sizeof(data), "{\"personalizations\": [{\"to\": [{\"email\": \"%s\"}]}], \"from\": {\"email\": \"%s\"}, \"subject\": \"%s\", \"content\": [{\"type\": \"text/plain\", \"value\": \"%s\"}]}", params->toEmail, params->fromEmail, params->subject, params->content);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
        free(authHeader);
    } else {
        fprintf(stderr, "Failed to initialize CURL.\n");
        res = CURLE_FAILED_INIT;
    }

    return res;
}
