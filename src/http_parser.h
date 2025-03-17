#pragma once

#include <iostream>

class HTTPMessage
{
    std::string message;

    std::string resource_path;
    std::string method;
    std::string http_version;

    std::string content_type;
    std::string content_length;


    //Get message from user-agent request buffer
    //parse it
    //using if conditions and status codes, perform the appropriate actions
    //build the response
    //send back the response to the HTTP server
    //from there the http server sends the response to the user agent

};


class HTTPRequest : HTTPMessage
{

};


class HTTPResponse : HTTPMessage
{

};