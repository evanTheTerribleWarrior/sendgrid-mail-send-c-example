#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sendgrid.h"

int main(int argc, char* argv[]) {
    if (argc < 6) {
        printf("Usage: ./sendgrid_send_email -f <from_email> -t <to_email> -s <subject> -c <content>\n");
        return 1;
    }

    EmailParams params;
    memset(&params, 0, sizeof(EmailParams));

    int i;
    for (i = 1; i < argc; i += 2) {
        if (strncmp(argv[i], "-f", 2) == 0)
            params.fromEmail = argv[i + 1];
        else if (strncmp(argv[i], "-t", 2) == 0)
            params.toEmail = argv[i + 1];
        else if (strncmp(argv[i], "-s", 2) == 0)
            params.subject = argv[i + 1];
        else if (strncmp(argv[i], "-c", 2) == 0)
            params.content = argv[i + 1];
    }

    params.apiKey = "API_KEY";

    CURLcode res;
    ResponseData response;
    response.data = NULL;
    response.size = 0;

    res = sendEmail(&params, &response);

    if (res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

    printf("Response: %s\n", response.data);

    free(response.data);

    return 0;
}