#ifndef RATE_LIMITER_H
#define RATE_LIMITER_H

#include <curl/curl.h>

// Since I am testing around protocol-oriented programming in C, here's a protocol implementation
// Most of the time, I would use a interface in C++ 
typedef struct RateLimiter {
    void (*limit)(const char* url);
    int  (*handle_rate_limit)(int retries);  
} RateLimiter;

// We need to initialize the rate limiter because C doesn't have constructors
RateLimiter* new_rate_limiter(void);

// Release the rate limiter because C doesn't have destructors
void free_rate_limiter(RateLimiter* limiter);

#endif