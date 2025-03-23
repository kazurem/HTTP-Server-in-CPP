#pragma once
#include <fstream>
#include <iostream>
#include <sstream>

class ReadFileAndBuildResponse
{
public:
    std::string buildResponse();
    std::string file_to_read;
    void getHTMLCSSBody();

private:
    std::ifstream file;
    std::string css_body;
    std::string html_body;
};