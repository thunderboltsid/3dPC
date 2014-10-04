//
//  AppDelegate.h
//  BufferReader
//
//  Created by Alexandru Barbarosie on 04/10/14.
//  Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <strings.h>

#define MY_PORT 4242
#define HEIGHT 1180
#define WIDTH 2020
#define MAXBUF HEIGHT*WIDTH


@interface AppDelegate : NSObject <NSApplicationDelegate>{
    NSScreen *screen;
    NSRect frame;
    NSNumber *screenNr;
    NSSize size;
    NSImageView *view;
    
    
    int clientfd;
    int sockfd;
	struct sockaddr_in slf;
	size_t height;
	size_t width;
	char buffer[MAXBUF];
}

@property (assign) IBOutlet NSWindow *window;

@end
