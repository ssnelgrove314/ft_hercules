#include "hydra.h"

void die_with_error(char *errmsg)
{
    printf("%s\n", errmsg);
    exit(EXIT_FAILURE);
}
// https://stackoverflow.com/questions/16508685/understanding-inaddr-any-for-socket-programming
struct sockaddr_in *init_serv_sockaddr(t_server *serv)
{
    struct sockaddr_in *ret;

    ret = (struct sockaddr_in *)calloc(sizeof(struct sockaddr_in), 1);
    ret->sin_family = AF_INET;
    ret->sin_addr.s_addr = inet_addr("10.113.6.4");
    ret->sin_port = htons(serv->echo_serv_port);
    return (ret);
}

void handle_tcp_client(t_server *serv)
{
    char echo_buffer[BUFFER_SIZE * 2];
    int recv_msg_len;

    if ((recv_msg_len = recv(serv->clnt_sock, echo_buffer, BUFFER_SIZE, 0)) < 0)
        die_with_error("recv() failed");
    
    while(recv_msg_len > 0)
    {
         // duplicate the message here

        //
        
        //echo once
            if (send(serv->clnt_sock, echo_buffer, recv_msg_len, 0) != recv_msg_len)
                die_with_error("send() failed");
        //check to see if there is more to the message.
            if ((recv_msg_len = recv(serv->clnt_sock, echo_buffer, BUFFER_SIZE, 0)) < 0)
                die_with_error("recv() failed");
    }
    close(serv->clnt_sock);
}

int main(int argc, char **argv)
{
    t_server *serv;

    serv = (t_server *)calloc(sizeof(t_server), 1);
    if (argc != 2)
    {
        printf("Usage: %s <Server Port> \n", argv[0]);
        exit(1);
    }
    
    serv->echo_serv_port = atoi(argv[1]);

    //create socket
    if ((serv->serv_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        die_with_error("socket() failed");
    
    serv->echo_serv_addr = init_serv_sockaddr(serv);

    //bind local addr
    if (bind(serv->serv_sock, (const struct sockaddr *)serv->echo_serv_addr, sizeof(*serv->echo_serv_addr)) < 0)
        die_with_error("bind() failed");

    //mark the socket so it will listen for incoming connections
    if (listen(serv->serv_sock, MAX_PENDING) < 0)
        die_with_error("bind() failed");
    
    printf("Server is running on %s\n", inet_ntoa(serv->echo_serv_addr->sin_addr));
    while (42) //main execution loop
    {
        //set the size of the in-out parameter
        serv->clnt_len = sizeof(*serv->echo_clnt_addr);

        //wait for the client to connect
        if ((serv->clnt_sock = accept(serv->serv_sock, (struct sockaddr *)serv->echo_clnt_addr, &serv->clnt_len)) < 0)
            die_with_error("accept() failed");
        //clntsock is connected to a client!
        //printf("Handling clietn %s\n", inet_ntoa(serv->echo_clnt_addr->sin_addr));
        handle_tcp_client(serv);
    }
}