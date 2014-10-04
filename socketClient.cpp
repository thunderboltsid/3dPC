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
using namespace std;
std::mutex mtx;
void client_routine() {
    mtx.lock();
    SocketClient::getInstance().connect_socket("localhost",4200);
//    SocketClient::getInstance().send<char>("abc",3);
//    int* p  = new int[3];
//    SocketClient::getInstance().send<int>(p,3);
//    char* buffer = new char[30];
//    SocketClient::getInstance().receive<char>(buffer, 29);
    int* valPtr = new int[1];
    SocketClient::getInstance().receive<int>(valPtr,1);
    int length = valPtr[0];
    char* buffer = new char[length];

    delete valPtr;
    delete[] buffer;
    mtx.unlock();
}

int main ()
{
    std::thread curr_thread(client_routine);
    curr_thread.join();
}
