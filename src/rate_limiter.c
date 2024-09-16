#include "rate_limiter.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// Static function for internal use only
static void make_api_request(const char* url) {
    CURL *curl;
    CURLcode res;
    long rate_limit, rate_limit_remaining;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Simulating API calls here
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            rate_limit = 40;
            rate_limit_remaining = rand() % 40; // Randomize the remaining requests
            printf("API Request Successful: Remaining Requests: %ld/%ld\n", rate_limit_remaining, rate_limit);
        } else {
            fprintf(stderr, "API Request Failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

}

// Handle rate limiting by pausing if necessary
static void handle_rate_limt(long remaining_requests) {
    if (remaining_requests < 5) {
        printf("Rate Limit Exceeded. Waiting for 10 seconds...\n");
        sleep(10);
    }
}

// Initialize a new rate limiter
RateLimiter* new_rate_limiter(void) {
    RateLimiter* limiter = (RateLimiter*)malloc(sizeof(RateLimiter));
    limiter->limit = make_api_request;
    limiter->handle_rate_limit = handle_rate_limt;
    return limiter;
}

// Free the rate limiter
void free_rate_limiter(RateLimiter* limiter) {
    free(limiter);
}