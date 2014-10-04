#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <cstdlib>
#include <mutex>
#include <thread>
#include "socketClient.h"
#include <vector>

#define WIDTH 1920
#define HEIGHT 1080

typedef struct{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
}Pixel;

std::vector<Pixel> image;

using namespace std;
std::mutex mtx;
void client_routine() {
    mtx.lock();
    SocketClient::getInstance().connect_socket("localhost",4242);
//    SocketClient::getInstance().send<char>("abc",3);
//    int* p  = new int[3];
//    SocketClient::getInstance().send<int>(p,3);
//    char* buffer = new char[30];
//    SocketClient::getInstance().receive<char>(buffer, 29);
    int* valPtr = new int[1];
    SocketClient::getInstance().receive<int>(valPtr,1);
    int length = valPtr[0];
    printf("Lenght: %d\n",length);
    
    unsigned char *buf = new unsigned char [length];
    SocketClient::getInstance().receive<unsigned char>(buf,length);
    
    delete [] buf;
    delete valPtr;
    mtx.unlock();
    sleep(20);
}

int main ()
{
    std::thread curr_thread(client_routine);
    curr_thread.join();
}
