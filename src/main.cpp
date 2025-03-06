#include <iostream>
#include "http_server.h"
#include "logger.h"


int main()
{
    Logger logger("./log.txt", true);
    http::HTTPServer server("0.0.0.0", 8080, logger);
    server.startListeningSession(logger);
    return 0;
}