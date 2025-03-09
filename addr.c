#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#define TRUE 1
#define FALSE 2
#define typename(x) _Generic((x), \
    unsigned short: "unsigned short int", \
    unsigned long: "unsigned long int", \
    default: "unknown")

typedef enum 
{
    HOST,
    IP
} ADDR_TYPE;

typedef struct
{
    size_t id;
    uint16_t port;
    bool closed;
    ADDR_TYPE addr_type;
    union 
    {
        char host[256];
        char ip[24];
    };
} CONN;

inline static const char* addr(const CONN* conn)
{
    assert(conn);
    return conn->addr_type == HOST ? conn->host : conn->ip;
}

int main(int argc, char const *argv[])
{
    _Static_assert(sizeof(CONN) <= 0x400, "Invalid CONN");
    const CONN conns[] = {
        [2] = { .id = 1, .port = 80, .closed = TRUE, .addr_type = IP, { .ip = "127.0.0.1" } },
        [0] = { .id = 2, .port = 8080, .closed = FALSE, .addr_type = IP, { .ip = "192.168.1.1" } },
        { .id = 3, .port = 8088, .closed = FALSE, .addr_type = HOST, { .host = "http://localhost/" } }
    };

    for (size_t i = 0; i < (sizeof(conns) / sizeof(CONN)); ++i)
    {
        printf("Port: %d\n" "Host/Addr: %s\n" "Internal type of `id` is: %s\n\n", conns[i].port, addr(&conns[i]), typename(conns[i].id));
    }
    
    return EXIT_SUCCESS;
}

