#pragma once

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>

namespace http
{
    class HTTPServer
    {
        public:
            HTTPServer(std::string ip_addr, int port);
            ~HTTPServer();
            void startListeningSession();
            void stopListeningSession();

        private:
            int port;
            std::string ip_address;
            int socket_file_descriptor;
            int new_socket_file_descriptor;
            struct sockaddr_in socket_address;
            unsigned int socket_address_length;
            int BUFFER_SIZE;
            std::string server_message;
            void acceptConnection(int &new_socket_fd);
            void sendResponse(std::string message);
    };
}