#include <iostream>
#include "http_server.h"
#include "logger.h"
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <signal.h>

int main()
{
    http::HTTPServer server("./server_config.txt");
    server.startListeningSession();
    return 0;
}