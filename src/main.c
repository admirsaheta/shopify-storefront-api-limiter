#include "rate_limiter.h"
#include "exponential_backoff.h"
#include <stdio.h>

int main(int argc, char **argv) {
    if(argc < 2) {
        fprintf(stderr, "Usage: %s <shopify_api_url>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];

    // Initialize protocols
    RateLimiter *rate_limiter = new_rate_limiter();
    ExponentialBackoff *backoff = new_exponential_backoff();

    // Simulate making 5 requests with rate limiting and retry logic
    int retries = 0;
    for (int i = 0; i < 5; i++) {
        printf("Sending API request %d...\n", i + 1);
        rate_limiter->limit(url);

        // Simulate a failed request that requires retries
        if (i % 2 == 0) {
            printf("Request %d failed. Applying exponential backoff...\n", i + 1);
            if (!backoff->retry_request(retries)) {
                break;
            }
        }

        rate_limiter->handle_rate_limit(rand() % 40);
    }

    // Clean up resources
    free_rate_limiter(rate_limiter);
    free_exponential_backoff(backoff);

    return 0;
}
