//
//  AppDelegate.m
//  BufferReader
//
//  Created by Alexandru Barbarosie on 04/10/14.
//  Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#import "AppDelegate.h"

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    clientfd = -1;
    screen = [NSScreen mainScreen];
    frame = screen.frame;
    screenNr = [screen.deviceDescription valueForKey:@"NSScreenNumber"];
    
    view = [[NSImageView alloc] initWithFrame:CGRectMake(0, 0, 400, 400)];
    [self.window.contentView addSubview:view];

    size.height = frame.size.height;
    size.width = frame.size.width;
    NSAlert *alert = [[NSAlert alloc] init];
    NSString *message = NSStringFromRect(frame);
    [alert setAlertStyle:NSInformationalAlertStyle];
    [alert setMessageText:@"Results"];
    [alert setInformativeText:message];
    [alert runModal];
    
    
    [self initialize];
    [self performSelectorInBackground:@selector(run) withObject:nil];
    [self read];
}

-(void) read{
    CGImageRef ref;
    while(1){
        if (clientfd == -1)
            continue;
        
        ref = CGWindowListCreateImage(frame, nil, [screenNr unsignedIntegerValue], nil);
        
        view.image = [[NSImage alloc] initWithCGImage:ref size:size];
        
        ref = CGWindowListCreateImage(frame, nil, [screenNr unsignedIntegerValue], nil);
        view.image = [[NSImage alloc] initWithCGImage:ref size:size];
        
        CGDataProviderRef provider = CGImageGetDataProvider(ref);
        NSData* data = (id)CFBridgingRelease(CGDataProviderCopyData(provider));
        const uint8_t* bytes = [data bytes];
    
        int length = [data length];
        
        send(clientfd, &length, 4, 0);
        send(clientfd, bytes, length, 0);
        
        sleep(1);
    }
}

- (void) click_left: (int) x  andY: (int) y{
    CGEventRef click = CGEventCreateMouseEvent(
                                               NULL, kCGEventLeftMouseDown,
                                               CGPointMake(x, y),
                                               kCGMouseButtonLeft
                                               );
    CGEventPost(kCGHIDEventTap, click);
}

- (void) click_right: (int) x andY: (int) y{
    CGEventRef click = CGEventCreateMouseEvent(
                                               NULL, kCGEventLeftMouseDown,
                                               CGPointMake(250, 250),
                                               kCGMouseButtonRight
                                               );
    CGEventPost(kCGHIDEventTap, click);
}

- (void) initialize{
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

- (void) run{
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
        // listen here
        
        ;
    }
}

@end
