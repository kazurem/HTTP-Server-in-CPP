#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "http_parser.h"
#include <map>

// Get message from user-agent request buffer (done)
// parse it
// using if conditions and status codes, perform the appropriate actions
// build the response
// send back the response to the HTTP server
// from there the http server sends the response to the user agent


void HTTPMessage::printHeaders()
{
    std::cout << "Headers:" << std::endl;
    for (const auto& header : headers) {
        std::cout << header.first << ": " << header.second << std::endl;
    }
}

void HTTPRequest::getUserAgentRequest(std::string request)
{
    std::cout << "request(in getUSERAGENTFUNCTION): " << request << std::endl; 
    this->request = request;
}

void HTTPRequest::parseMessage()
{
    std::istringstream request_message_stream(request);

    request_message_stream >> method >> resource_path >> http_version;
    
    // std::cout << "Method: " << method << std::endl;
    // std::cout << "Resource Path: " << resource_path << std::endl;
    // std::cout << "HTTP Version: " << http_version << std::endl;

    std::string header_line;

    while (std::getline(request_message_stream, header_line)) 
    {
        // Ignore empty lines (end of headers)
        if (header_line.empty()) continue;

        // Find the position of the first colon
        size_t colon_pos = header_line.find(':');
        if (colon_pos != std::string::npos) {
            std::string header_name = header_line.substr(0, colon_pos);
            std::string header_value = header_line.substr(colon_pos + 1);

            // Trim leading spaces in header value
            header_value.erase(0, header_value.find_first_not_of(" \t"));
            
            // Insert into map
            headers[header_name] = header_value;
        }
    }

    // // Print headers for verification
   
}

int HTTPRequest::getFileData()
{
    std::ifstream file(resource_path);
    if(file.is_open())
    {
        std::ostringstream osstr;
        osstr << file.rdbuf();

        file_data = osstr.str();
        return 1;
    }
    return -1;
}

int HTTPRequest::getImageData()
{
    //read image as binary (open in std::ios::binary)
    return 1;
}



std::map<std::string, std::string> HTTPRequest::handleRequest()
{
    parseMessage();
    std::map<std::string, std::string> http_response_info;

    if(method == "GET")
    {
        if(headers["Content-Type:"] == "text/html")
        {
            int found = getFileData();
            fillMap(http_response_info, "text/html", found);
            http_response_info["body"] = file_data;

            return http_response_info; //status code 200 OK
        }
        else if(headers["Content-Type:"] == "text/css")
        {
            int found = getFileData();
            fillMap(http_response_info, "text/css", found);
            http_response_info["body"] = file_data;

            return http_response_info; //status code 200 OK
        }
        else if(headers["Content-Type:"] == "image/webp")
        {
            int found = getImageData();
            fillMap(http_response_info, "image/webp", found);
            http_response_info["body"] = image_data;

            return http_response_info; //status code 200 OK
        }
    }
    return http_response_info;
}

void HTTPRequest::fillMap(std::map<std::string, std::string> &http_response_info,std::string content_type, const int found)
{
    http_response_info["http-version"] = http_version;
    http_response_info["content_type"] = "Content-Type: " + content_type;
    if(found < 0)
    {
            http_response_info["status-code"] = "404";
            http_response_info["reason_phrase"] = "Not Found";
            if(content_type == "text/html")
            {
                http_response_info["body"] = R"""(
                                                <!DOCTYPE html>
                                                <html>
                                                <head>
                                                    <title>404 Not Found</title>
                                                </head>
                                                <body>
                                                    <h1>Not Found</h1>
                                                    <p>The requested URL was not found on this server.</p>
                                                </body>
                                                </html>)""";
            }
            else
            {
                http_response_info["body"] = "";
            }
    }
    else
    {
        http_response_info["status_code"] = "200";
        http_response_info["reason_phrase"] = "OK";
    }        
}

std::string HTTPResponse::buildResponse(std::map<std::string, std::string> http_response_info)
{
    std::string response = "";
    response += http_response_info["http-version"] + " ";
    response += http_response_info["status-code"] + " ";
    response += http_response_info["reason-phrase"] + "\r\n";
    response += http_response_info["content-type"] + "\r\n\r\n";

    response += http_response_info["body"];

    return response;
}
