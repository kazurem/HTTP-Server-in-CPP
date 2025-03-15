#include "static-file-server.h"


void StaticFileServer::getHTMLBody()
{
    html_file.open(file_to_read);
    if(!html_file.is_open())
    {
        html_body = "";
    }

    std::ostringstream string_stream;
    string_stream << html_file.rdbuf();
    html_body = string_stream.str();
}


std::string StaticFileServer::buildResponse()
{
    std::string response;
    getHTMLBody();
    std::string http_headers = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " + std::to_string(html_body.size()) + "\r\n\r\n";
    response = http_headers + html_body;
    return response;
}

    