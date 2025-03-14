#include <iostream>
#include "http_server.h"
#include "logger.h"


int main()
{
    Logger logger("./log.txt", true);
    http::HTTPServer server("./server_config.txt", logger);
    server.startListeningSession(logger);
    return 0;
}