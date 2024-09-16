#ifndef EXPONENTIAL_BACKOFF_H
#define EXPONENTIAL_BACKOFF_H

// Defining the protocol for the algorithm being used in the rate limiter
typedef struct ExponentialBackoff {
    int (*retry_request)(int retries);
} ExponentialBackoff;

ExponentialBackoff* new_exponential_backoff(void);

void free_exponential_backoff(ExponentialBackoff* backoff);

#endif
