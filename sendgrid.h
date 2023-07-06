#ifndef SENDGRID_H
#define SENDGRID_H

#include <curl/curl.h>

typedef struct {
    const char* apiKey;
    const char* fromEmail;
    const char* toEmail;
    const char* subject;
    const char* content;
} EmailParams;

typedef struct {
    char* data;
    size_t size;
} ResponseData;

size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata);
CURLcode sendEmail(const EmailParams* params, ResponseData* response);

#endif
