CC = gcc
CFLAGS = -Wall -I./include
LDFLAGS = -L/usr/lib -lcurl 

SRC = src/main.c src/rate_limiter.c src/exponential_backoff.c
OBJ = rate_limiter.o exponential_backoff.o
OUT = shopify_rate_limiter

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)

clean:
	rm -f $(OUT)
