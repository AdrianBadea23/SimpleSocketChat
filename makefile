CC = gcc

TARGETS = tcp_client tpc_server

all: $(TARGETS)

tcp_client: tcp_client.c
	$(CC) -o tcp_client tcp_client.c

tpc_server: tpc_server.c
	$(CC) -o tpc_server tpc_server.c

clean:
	rm -f $(TARGETS)
