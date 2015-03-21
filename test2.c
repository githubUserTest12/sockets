#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BACKLOG 10
#define PORT "3490"

int main() {
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	struct addrinfo hints, *res;
	int sockfd, new_fd;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype= SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, PORT, &hints, &res);

	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	bind(sockfd, res->ai_addr, res->ai_addrlen);

	struct sockaddr *tmp;
	int sockaddrlen = sizeof tmp;;

	int status;
	status = getpeername(sockfd, (struct sockaddr *) tmp, &sockaddrlen);
	/*
	listen(sockfd, BACKLOG);

	addr_size = sizeof their_addr;

	new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &addr_size);

	int bytes_received;
	char *buf;
	int len;

	bytes_received = recv(sockfd, buf, len, 0);
	*/

	return 0;
}
