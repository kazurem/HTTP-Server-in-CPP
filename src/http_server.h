#pragma once

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>
#include "logger.h"
#include "static-file-server.h"

namespace http
{
    class HTTPServer
    {
        public:
            HTTPServer(std::string ip_addr, int port, Logger &logger, std::string file_to_read = "index.html");
            HTTPServer(std::string path_to_config, Logger &logger, std::string file_to_read = "index.html");
            ~HTTPServer();
            void startListeningSession(Logger &logger);
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
            void acceptConnection(int &new_socket_fd, Logger &logger);
            void sendResponse(std::string message, Logger &logger);
            void startServer(Logger &logger);
            StaticFileServer sfs;
            
    };
}