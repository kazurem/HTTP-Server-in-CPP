#include "http_server.h"

namespace http
{

    HTTPServer::HTTPServer(std::string path_to_config, Logger &logger, std::string file_to_read)
    {
        std::ifstream config_file(path_to_config);
        config_file >> ip_address;
        sfs.file_to_read = file_to_read;
        config_file >> port;
        socket_address_length = sizeof(socket_address);
        BUFFER_SIZE = 30760;
        
        //initializing the sockaddr_in struct
        socket_address.sin_family = AF_INET;
        socket_address.sin_port = htons(this->port);
        socket_address.sin_addr.s_addr = inet_addr(ip_address.c_str());
        startServer(logger);
    }

    HTTPServer::HTTPServer(std::string ip_address, int port, Logger &logger, std::string file_to_read)
    {
        this->ip_address = ip_address;
        this->port = port;
        sfs.file_to_read = file_to_read;
        socket_address_length = sizeof(socket_address);
        sfs.file_to_read = "index.html";

        BUFFER_SIZE = 30760;
        
        //initializing the sockaddr_in struct
        socket_address.sin_family = AF_INET;
        socket_address.sin_port = htons(this->port);
        socket_address.sin_addr.s_addr = inet_addr(ip_address.c_str()); 
        startServer(logger);
    }


    HTTPServer::~HTTPServer()
    {
        stopListeningSession();
    }

    void HTTPServer::startServer(Logger &logger)
    {
        //creating the socket   
        socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0); 
        if(socket_file_descriptor < 0)
        {
            logger.log("Socket creation failed!");            
            exit(1); 
        }


        //bind the socket to the address
        if(bind(socket_file_descriptor, (sockaddr *)&socket_address, socket_address_length) < 0)
        {
            std::ostringstream osstr;
            osstr << "Socket could not be bound to ADDRESS " << inet_ntoa(socket_address.sin_addr) << " on PORT " << ntohs(socket_address.sin_port);
            logger.log(osstr.str());
            exit(1);
        }
    }


    void HTTPServer::stopListeningSession()
    {
        close(socket_file_descriptor);
        close(new_socket_file_descriptor);
        exit(0);
    }


    void HTTPServer::startListeningSession(Logger &logger)
    {
        std::ostringstream osstr;
        osstr << "Starting listening session at address " << inet_ntoa(socket_address.sin_addr) << " on port " << ntohs(socket_address.sin_port) << " (http://" << inet_ntoa(socket_address.sin_addr)<< ":" << ntohs(socket_address.sin_port) << "/)";
        logger.log(osstr.str());
        std::cout << "\n\n";


        if(listen(socket_file_descriptor, 100) < 0)
        {
            logger.log("Socket was not able to start listening!");
            exit(1);
        }

        int bytes_received;

        while(true)
        {
            acceptConnection(new_socket_file_descriptor, logger);
            char buffer[BUFFER_SIZE] = {0};
            bytes_received = read(new_socket_file_descriptor, buffer, BUFFER_SIZE);
            if(bytes_received < 0)
            {
                logger.log("Socket was not able to read data!");
                exit(-1);
            }

            sendResponse("World!", logger);

            close(new_socket_file_descriptor);
        }

    }

    void HTTPServer::sendResponse(std::string message, Logger &logger)
    {
        std::string response = sfs.buildResponse();
       
        server_message = response;

        int bytes_sent = write(new_socket_file_descriptor, server_message.c_str(), server_message.size());

        if(bytes_sent != server_message.size())
        {
            logger.log("Socket was not able to send data!");
            exit(1);
        }
        logger.log("Response sent successfully!");
    }

    
    void HTTPServer::acceptConnection(int &new_socket_fd, Logger &logger)
    {
        new_socket_fd = accept(socket_file_descriptor, (sockaddr*)&socket_address, &socket_address_length);

        if(new_socket_fd < 0)
        {
            logger.log("Socket was not able to accept the connection!");
            exit(1);
        }
        logger.log("Connection accepted!");
    }
}