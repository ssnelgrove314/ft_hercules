SERVER_NAME := hydra_server
CLIENT_NAME := hydra_client
CC		:=	gcc
CFLAGS	:=	-Wall -Werror -Wextra -g

SERVER_SRC := hydra_server.c
CLIENT_SRC := hydra_client.c

SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

all: $(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME): $(SERVER_OBJ) 
	$(CC) -o $@ $^ $(CFLAGS)

$(CLIENT_NAME): $(CLIENT_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean fclean re
clean:
	rm -f $(SERVER_OBJ)
	rm -f $(CLIENT_OBJ)

fclean:
	rm -f $(SERVER_NAME)
	rm -f $(CLIENT_NAME)

re: fclean all