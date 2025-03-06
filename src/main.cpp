#include <iostream>
#include "http_server.h"


int main()
{
    http::HTTPServer server("0.0.0.0", 8080);
    server.startListeningSession();
    return 0;
}