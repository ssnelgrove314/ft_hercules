#include "hydra.h"

void die_with_error(char *errmsg)
{
    printf("%s\n", errmsg);
    exit(EXIT_FAILURE);
}

struct sockaddr_in *init_sockaddr(t_client *cli)
{
    struct sockaddr_in *ret;

    ret = (struct sockaddr_in *)calloc(sizeof(struct sockaddr_in), 1);
    ret->sin_family = AF_INET;
    ret->sin_addr.s_addr = inet_addr(cli->serv_ip);
    ret->sin_port = htons(cli->echo_server_port);
    return (ret);
}

int main(int argc, char **argv)
{
    t_client *cli;
    
    // check args
    cli = (t_client *)calloc(sizeof(t_client), 1);
    if ((argc < 3) || (argc > 4))
    {
        fprintf(stderr, "Usage: %s <Server IP> <Echo Word> [<Echo Port>]\n", argv[0]);
        exit (1);
    }

    // set args from argv
    cli->serv_ip = argv[1]; //first arg: server ip (dotted quad)
    cli->echo_msg = argv[2]; //second arg: message to echo
    if (argc == 4)
        cli->echo_server_port = atoi(argv[3]);
    else
        cli->echo_server_port = PORT;

    //create tcp socket
    if ((cli->sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        die_with_error("socket() failed\n");
    
    //set the sockaddr
    cli->echo_server_addr = init_sockaddr(cli);

    //connect
    if (connect(cli->sock, (struct sockaddr *)cli->echo_server_addr, sizeof(*cli->echo_server_addr)) < 0)
        die_with_error("connect() failed\n");

    //send the string to the server
    cli->echo_msg_len = strlen(cli->echo_msg);
    if (send(cli->sock, cli->echo_msg, cli->echo_msg_len, 0) != cli->echo_msg_len)
        die_with_error("send() sent a different number of bytes than expected");
    
    //recieve results;
    cli->total_bytes_rcvd = 0;
    printf("Recieved: ");
    while (cli->total_bytes_rcvd < cli->echo_msg_len)
    {
        if ((cli->bytes_rcvd = recv(cli->sock, cli->client_buffer, BUFFER_SIZE - 1, 0)) <= 0)
            die_with_error("recv() failed or connection closed prematurely");
        cli->total_bytes_rcvd += cli->bytes_rcvd;
        cli->client_buffer[cli->bytes_rcvd] = '\0';
        printf("%s", cli->client_buffer);
    }
    printf("\n");

    close(cli->sock);
    exit(0);
}