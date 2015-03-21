#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {
	struct addrinfo hints, *res, *p;
	int status;
	char ipstr[INET6_ADDRSTRLEN];
	
	if(argc != 2) {
		fprintf(stderr, "usage: test hostname\n");
		return 1;
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 1;
	}

	printf("IP addresses for %s\n\n", argv[1]);

	for(p = res; p != NULL; p = p->ai_next) {
		void *addr;
		char *ipver;
		int sockfd;

		if(p->ai_family == AF_INET) {
			struct sockaddr_in *ipv4 = (struct sockaddr_in *) p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		}
		else {
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}

		inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
		printf("  %s: %s\n", ipver, ipstr);

		sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

		char hbuf[1024], sbuf[20];
		struct sockaddr_in *tmp = ipv4;
		socklen_t sockaddrlen = sizeof tmp;
		getpeername(sockfd, (struct sockaddr *) tmp, &sockaddrlen);

		getnameinfo((struct sockaddr *) tmp, sockaddrlen, hbuf, sizeof hbuf, sbuf, sizeof sbuf, 0);
		printf("host=%s, serv=%s\n", hbuf, sbuf);

		/*
		int stat;
		struct sockaddr *tmp;
		socklen_t sockaddrlen = sizeof tmp;

		stat = getpeername(sockfd, (struct sockaddr *) tmp, &sockaddrlen);
		inet_ntop(tmp->sin_family, &(tmp->sin_addr), ipstr, sizeof ipstr);
		printf(" getpeername: %s\n", ipstr);
		*/

		//bind(sockfd, p->ai_addr, p->ai_addrlen);

		//connect(sockfd, p->ai_addr, p->ai_addrlen);

		//listen(sockfd, 10);
	}

	freeaddrinfo(res);

	return 0;
}
