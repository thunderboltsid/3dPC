#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>

class SocketClient {
    private:
        char* hostname;
        int portno;
        int sockfd;
    public:
        SocketClient(SocketClient const&);              // Don't Implement
        void operator=(SocketClient const&); // Don't implement
        static SocketClient& getInstance()
        {
            static SocketClient instance; // Guaranteed to be de
            return instance;
        }
        //returns sockfd
        SocketClient() {};
        void connect_socket(char* hostname, int portno) {
            int n;
            struct sockaddr_in serv_addr;
            struct hostent *server;

            char buffer[256];
            /* Create a socket point */
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (sockfd < 0)
            {
                perror("ERROR opening socket");
                exit(1);
            }
            server = gethostbyname(hostname);
            if (server == NULL) {
                fprintf(stderr,"ERROR, no such host\n");
                exit(1);
            }

            bzero((char *) &serv_addr, sizeof(serv_addr));
            serv_addr.sin_family = AF_INET;
            bcopy((char *)server->h_addr,
                   (char *)&serv_addr.sin_addr.s_addr,
                        server->h_length);
            serv_addr.sin_port = htons(portno);

            /* Now connect to the server */

            if (::connect(sockfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
            {
                 perror("ERROR connecting");

            }
        }
        template <class T>
        int send(T* buffer, int len) {
            int n = write(sockfd,buffer,sizeof(T)*len);
            if (n < 0)
            {
                 perror("ERROR writing to socket");
                 return -1;
            }
            return 0;
        }
        template <class T>
        int receive(T* buffer, int len) {  //for string len = buffer_length -1
            bzero(buffer,len);
            int n = read(sockfd,buffer,sizeof(T)*len);
            if (n<0) {
                perror("Read error");
            }
            else
                return 0;
        }

        // zero -> ok; -1 ->  bad
//        int sendCharBuff(char* buffer) {;
////            bzero(buffer,256);
////            fgets(buffer,255,stdin);
//            /* Send message to the server */
//            int n = write(sockfd,buffer,strlen(buffer));
//            if (n < 0)
//            {
//                 perror("ERROR writing to socket");
//                 return -1;
//            }
//            return 0;
//        }
//        int sendIntBuff(int* buffer) {
//            int n = send(my_socket, (char*)bmp_info_buff, 3*sizeof(int), 0);
//            if (n < 0)
//            {
//                 perror("ERROR writing to socket");
//                 return -1;
//            }
//            return 0;
//        }

            /* Now ask for a message from the user, this message
        * will be read by server
        */
//        int receiveCharBuff(char* buffer, int len) {
//            bzero(buffer,len);
//            int n = read(sockfd,buffer,len-1);
//            if (n<0) {
//                perror("Read error");
//            }
//            else
//                return 0;
//        }
//        int receiveIntBuff(int* buffer, int len) {
//            bzero(buffer,len);
//            int n = read(sockfd,buffer,sizeof(int)*len);
//            if (n<0) {
//                perror("Read error");
//            }
//            else
//                return 0;
//        }

};

int main(int argc, int* argv) {
    SocketClient::getInstance().connect_socket("localhost",3001);
    SocketClient::getInstance().send<char>("abc",3);
    int* p  = new int[3];
    SocketClient::getInstance().send<int>(p,3);
    char* buffer = new char[30];
    SocketClient::getInstance().receive<char>(buffer, 29);
    return 0;
}
