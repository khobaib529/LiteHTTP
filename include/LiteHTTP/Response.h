#ifndef RESPONSE_H_
#define RESPONSE_H_

#include <LiteHTTP/Request.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

/**
 * @file Response.h
 * @brief LiteHTTP Response Class Header
 *
 * This header defines the Response class for the LiteHTTP library.
 * The Response class is responsible for sending HTTP responses to 
 * clients. It includes a method to write a response based on the 
 * received request.
 */

namespace LiteHTTP {

class Response {
 private:
    int client_socket;

 public:
    // Constructor to initialize with client socket
    Response(int client_socket) : client_socket(client_socket) {}

    // Method to write an HTTP response
    void write() {
        char buffer[2048];
        read(client_socket, buffer, 2048);
        
        std::cout << "Received request:\n" << buffer << std::endl;

        const char *response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<html><body><h1>Hello, World!</h1></body></html>";
        
        ::write(client_socket, response, strlen(response));
        close(client_socket);
    }
};

}  // namespace LiteHTTP

#endif
