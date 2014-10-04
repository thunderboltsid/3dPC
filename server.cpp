#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <strings.h>
#include <vector>

#define MY_PORT		4242
#define HEIGHT 1080
#define WIDTH 1920
#define MAXBUF HEIGHT*WIDTH


class Server{
private:
	int sockfd;
	struct sockaddr_in slf;
	size_t height;
	size_t width;
	char buffer[MAXBUF];

public:
	void init(){
		/*---Create streaming socket---*/
	    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
		{
			perror("Socket");
			exit(errno);
		}

		/*---Initialize address/port structure---*/
		bzero(&slf, sizeof(slf));
		slf.sin_family = AF_INET;
		slf.sin_port = htons(MY_PORT);
		slf.sin_addr.s_addr = INADDR_ANY;

		/*---Assign a port number to the socket---*/
	    if ( bind(sockfd, (struct sockaddr*)&slf, sizeof(slf)) != 0 )
		{
			perror("socket--bind");
			exit(errno);
		}

		/*---Make it a "listening socket"---*/
		if ( listen(sockfd, 20) != 0 )
		{
			perror("socket--listen");
			exit(errno);
		}
	}
	void run(){
		int clientfd = -1;
		struct sockaddr_in client_addr;
		socklen_t addrlen=sizeof(client_addr);
		while(1){
			/*---accept a connection (creating a data pipe)---*/
			clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
			if (clientfd != -1){
				// connected
				break;
			}
		}

		/*---Forever... ---*/
		while (1){
			// read frame buffer;

			// update buffer field 

			// send
			send(clientfd, buffer, (height*width*3*4)+2*4, 0);
		}
	}

	~Server(){
		/*---Clean up (should never get here!)---*/
		close(sockfd);
	}

	void click_left(int x, int y){
		CGEventRef click = CGEventCreateMouseEvent(
        	NULL, kCGEventLeftMouseDown,
        	CGPointMake(x, y),
        	kCGMouseButtonLeft
    	);
    	CGEventPost(kCGHIDEventTap, click);
	}

	void click_right(int x, int y){
		CGEventRef click = CGEventCreateMouseEvent(
        	NULL, kCGEventLeftMouseDown,
        	CGPointMake(250, 250),
        	kCGMouseButtonRight
    	);
    	CGEventPost(kCGHIDEventTap, click);
	}

};

int main(int Count, char *Strings[])
{   
	Server serv;
	serv.init();
	serv.run();
	

	
	return 0;
}
