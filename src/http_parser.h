#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <filesystem>


class HTTPMessage
{
public:
    std::string message; //request for HTTPRequest and response for HTTPResponse
    std::string http_version;
    std::map<std::string, std::string> headers;
    std::string body;

    void printHeaders();
    void parseMessage();

};

class HTTPRequest : public HTTPMessage
{
public:
    std::string method;
    std::string resource_path;
    std::string resource_extension;

    std::map<std::string, std::string> handleRequest();
    void fillMap(std::map<std::string, std::string> &http_response_info ,std::string content_type, const int found);
    void getUserAgentRequest(std::string request);
    void parseMessage();
    int getFileData();
    int getImageData();
    void getResourceExtension();
    void makeHTTPResponseInfo(std::map<std::string, std::string> &http_response_info, std::string content_type);
};

class HTTPResponse : public HTTPMessage
{
public:
    std::string status_code;
    std::string reason_phrase;

    std::string buildResponse(std::map<std::string, std::string> http_response_info);
};

