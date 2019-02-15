#include "hydra.h"

int main(void)
{
    t_server serv;
    if ((serv.server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0)
    {
        perror("socket failed");
        exit (EXIT_FAILURE);
    }
    if (setsockopt(serv.server_fd, SQL_SOCKET))
}