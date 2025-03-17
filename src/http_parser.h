#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>


// Get message from user-agent request buffer (done)
// parse it
// using if conditions and status codes, perform the appropriate actions
// build the response
// send back the response to the HTTP server
// from there the http server sends the response to the user agent

//text --> normal read (.html, .css)
//binary --> binary read (.webp, .png, jpg, jpeg,...)


class HTTPMessage
{
public:
    std::string http_version;
    std::map<std::string, std::string> headers;
    std::string body;

    void printHeaders();
    void parseMessage();

};

class HTTPRequest : public HTTPMessage
{
public:
    std::string request;

    std::string method;
    std::string resource_path;

    std::string file_data;
    std::string image_data;

    std::map<std::string, std::string> headers;


    std::map<std::string, std::string> handleRequest();
    void fillMap(std::map<std::string, std::string> &http_response_info ,std::string content_type, const int found);
    void getUserAgentRequest(std::string request);
    void parseMessage();
    int getFileData();
    int getImageData();
};

class HTTPResponse : public HTTPMessage
{
public:
    int status_code;
    std::string reason_phrase;
    std::string body;

    std::string buildResponse(std::map<std::string, std::string> http_response_info);
};