#include <LiteHTTP/HTTP.h>

namespace LiteHTTP {

void HTTP::initialize_socket() {
    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set options for the socket to allow reuse of the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }
}

void HTTP::bind_socket(const char* ip_address) {
    // Convert IP address from text to binary form
    address.sin_addr.s_addr = inet_addr(ip_address);
    
    // Bind the socket to the specified IP address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

HTTP& HTTP::create_server(RequestResponseHandler handler) {
    // Set the request-response handler
    this->req_res_handler = handler;
    return *this;
}

void HTTP::listen(short port, const char *ip_address, void (*)()) {
    // Initialize and bind the socket
    initialize_socket();
    
    // Set up the address structure for listening
    address.sin_family = AF_INET;                // IPv4
    address.sin_addr.s_addr = INADDR_ANY;       // Accept connections from any IP address
    address.sin_port = htons(port);               // Convert port number to network byte order

    bind_socket(ip_address);

    // Start listening for incoming connections
    if (::listen(server_fd, 3) == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    while (true) {
        // Accept a new connection
        socklen_t addrlen = sizeof(address);
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) == -1) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        // Create request and response objects
        Request request; 
        Response response(new_socket);

        // Call the provided request-response handler
        req_res_handler(request, response);

        // Close the socket after handling the request
        close(new_socket);
    }
}

}  // namespace LiteHTTP
