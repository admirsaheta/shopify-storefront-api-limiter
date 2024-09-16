#include "exponential_backoff.h"
#include <stdio.h>
#include <unistd.h>

// Exponential backoff function
static int retry_with_exponential_backoff(int retries) {
    int max_retries = 5;
    int delay = 1;  // Start with 1 second

    while (retries < max_retries) {
        printf("Retrying request in %d seconds...\n", delay);
        sleep(delay);  // Wait for the current delay duration
        delay *= 2;  // Exponentially increase the delay
        retries++;
    }

    if (retries >= max_retries) {
        printf("Max retries reached. Exiting...\n");
        return 0;  // Failure
    }

    return 1;  // Success after retry
}

// Initialize a new ExponentialBackoff with function pointers
ExponentialBackoff* new_exponential_backoff() {
    ExponentialBackoff* backoff = (ExponentialBackoff*) malloc(sizeof(ExponentialBackoff));
    backoff->retry_request = retry_with_exponential_backoff;
    return backoff;
}

// Free the resources for ExponentialBackoff
void free_exponential_backoff(ExponentialBackoff *backoff) {
    free(backoff);
}
