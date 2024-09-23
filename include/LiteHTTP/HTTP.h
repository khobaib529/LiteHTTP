/**
 * @file HTTP.h
 * @brief LiteHTTP Library Header
 *
 * This header defines the HTTP class for creating a high-performance 
 * HTTP server in C++. It supports a callback mechanism for handling 
 * requests and responses, aiming for a syntax similar to Node.js.
 */


#ifndef HTTP_H_
#define HTTP_H_

#include <LiteHTTP/Request.h>
#include <LiteHTTP/Response.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

namespace LiteHTTP {
class HTTP {
 public:
  using RequestResponseHandler = void (*)(Request &, Response &);

 public:
  HTTP() {}

  HTTP &create_server(RequestResponseHandler req_res_handler);
  void listen(short port, const char *ip_address, void (*)());

 private:
  int server_fd, new_socket;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);
  RequestResponseHandler req_res_handler;

  void bind_socket(const char* ip_address);
  void initialize_socket();
};

}  // namespace LiteHTTP

#endif
