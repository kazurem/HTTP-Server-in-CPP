#include "read_data_and_build_response.h"

void ReadFileAndBuildResponse::getHTMLCSSBody()
{
    // reading html content
    file.open(file_to_read);
    if (!file.is_open())
    {
        //default response
        html_body = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Document</title></head><body><h3>Hello!</h3><p>This is a default response!</p></body></html>";
        return;
    }

    std::ostringstream string_stream;

    // reading the whole buffer and converting it to a string
    string_stream << file.rdbuf();
    html_body = string_stream.str();
    file.close();

    // reading css content
    file.open("./website/style.css");

    // clearing string stream
    string_stream.str("");
    string_stream.clear(); // resetting error state

    string_stream << file.rdbuf();
    css_body = string_stream.str();
    file.close();
}

std::string ReadFileAndBuildResponse::buildResponse()
{
    std::string response;
    getHTMLCSSBody();

    int head_pos = html_body.find("</head>"); // find the position of the ending head tag

    if (head_pos != std::string::npos) // in case there is a head tag
    {
        std::string style_tag = "<style>" + css_body + "</style>";
        html_body.insert(head_pos, style_tag);
    }
    else // in case there is no head tag
    {
        std::string style_tag = "<head><style>" + css_body + "</style></head>";
        html_body.insert(head_pos, style_tag);
    }

    std::string http_headers = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " + std::to_string(html_body.size()) + "\r\nConnection: keep-alive\r\n\r\n";
    response = http_headers + html_body;

    return response;
}
