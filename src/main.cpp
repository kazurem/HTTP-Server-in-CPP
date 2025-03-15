#include <iostream>
#include "http_server.h"
#include "logger.h"


int main(int argc, char* argv[])
{
    // Default values
    std::string ip_address = "127.0.0.1";
    int port = 8080;

    if (argc == 3) {
        ip_address = argv[1];
        try {
            port = std::stoi(argv[2]);
            if(port > 65535)
            {
                std::cerr << "Port number must be less than 65,535" << std::endl;
                exit(EXIT_FAILURE);
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid port number: " << argv[2] << std::endl;
            exit(EXIT_FAILURE);
        } catch (const std::out_of_range& e) {
            std::cerr << "Port number out of range for type int. : " << argv[2] << std::endl;
            exit(EXIT_FAILURE);
        }
    } else if (argc != 1) {
        std::cerr << "Usage: " << argv[0] << " [ip_address port]" << std::endl;
        exit(EXIT_FAILURE);
    }

    http::HTTPServer server(ip_address, port);
    server.startListeningSession();
    return 0;
}