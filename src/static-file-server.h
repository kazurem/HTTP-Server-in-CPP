#pragma once
#include <fstream>
#include <iostream>
#include <sstream>

class StaticFileServer
{
    public:
        std::string buildResponse();
        std::string file_to_read;
        void getHTMLBody();

    private:
        std::ifstream html_file;
        std::string html_body;

};