#include "http_server.h"

namespace http
{
    HTTPServer::HTTPServer(std::string ip_address, int port)
    {
        this->ip_address = ip_address;
        this->port = port;
        socket_address_length = sizeof(socket_address);
        BUFFER_SIZE = 30760;
        socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0); //creating the socket
        if(socket_file_descriptor < 0)
        {
            std::cout << "couldn't create socket!" << std::endl;
            exit(1); 
        }
        
        
        //initializing the sockaddr_in struct
        socket_address.sin_family = AF_INET;
        socket_address.sin_port = htons(this->port);
        socket_address.sin_addr.s_addr = inet_addr(ip_address.c_str());


        //bind the socket to the address
        if(bind(socket_file_descriptor, (sockaddr *)&socket_address, socket_address_length) < 0)
        {
            std::cout << "couldn't bind socket!" << std::endl;
            exit(1);
        }
    }


    HTTPServer::~HTTPServer()
    {
        stopListeningSession();
    }


    void HTTPServer::stopListeningSession()
    {
        close(socket_file_descriptor);
        close(new_socket_file_descriptor);
        exit(0);
    }


    void HTTPServer::startListeningSession()
    {
        std::cout << "Starting listening session at address " << inet_ntoa(socket_address.sin_addr) << " on port " << ntohs(socket_address.sin_port) << std::endl;
        if(listen(socket_file_descriptor, 100) < 0)
        {
            std::cout << "couldn't start listening!" << std::endl;
            exit(1);
        }

        int bytes_received;

        while(true)
        {
            acceptConnection(new_socket_file_descriptor);
            char buffer[BUFFER_SIZE] = {0};
            bytes_received = read(new_socket_file_descriptor, buffer, BUFFER_SIZE);
            if(bytes_received < 0)
            {
                std::cout << "couldn't read data!" << std::endl;
                exit(-1);
            }

            sendResponse("World!");

            close(new_socket_file_descriptor);
        }

    }

    void HTTPServer::sendResponse(std::string message)
    {
        std::string html_message = "<!DOCTYPE html><html lang=\"en\"><head><body><h1>Hello " + message + "!</h1></body></html>";
        std::string http_headers = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " + std::to_string(html_message.size()) + "\r\n\r\n";
        std::string response = http_headers + html_message;

        // string htmlFile = "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1></body></html>";
       
        server_message = response;

        int bytes_sent = write(new_socket_file_descriptor, server_message.c_str(), server_message.size());

        if(bytes_sent != server_message.size())
        {
            std::cout << "failed to send data!" << std::endl;
            exit(-1);
        }
        std::cout << "Response sent!" << std::endl;
    }

    
    void HTTPServer::acceptConnection(int &new_socket_fd)
    {
        new_socket_fd = accept(socket_file_descriptor, (sockaddr*)&socket_address, &socket_address_length);

        if(new_socket_fd < 0)
        {
            std::cout << "couldn't accept connection!" << std::endl;
            exit(1);
        }
    }
}