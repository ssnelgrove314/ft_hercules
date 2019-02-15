#ifndef HYDRA_H
#define HYDRA_H

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
# define PORT 8080
# define BUFFER_SIZE 1024

typedef struct s_server
{
    int server_fd;
    int new_socket;
    int valread;
    struct sockaddr_in address;
    int addrlen;
    char buffer[BUFFER_SIZE];
}               t_server;

typedef struct s_client
{
    int sock; //socket descriptor
    struct sockaddr_in *echo_server_addr;
    unsigned short echo_server_port;
    char *serv_ip; //dotted quad server ip 10.0.1.69
    char client_buffer[BUFFER_SIZE]; //buffer
    char *echo_msg;
    unsigned int echo_msg_len; //length of string to echo;
    int bytes_rcvd;
    int total_bytes_rcvd;
}               t_client;

#endif