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
    screen = [NSScreen mainScreen];
    frame = screen.frame;
    screenNr = [screen.deviceDescription valueForKey:@"NSScreenNumber"];
    
    view = [[NSImageView alloc] initWithFrame:CGRectMake(0, 0, 400, 400)];
    [self.window.contentView addSubview:view];

    size.height = frame.size.height;
    size.width = frame.size.width;
    
    [self read];
}

-(void) read{
    CFReadStreamRef readStream;
    CFWriteStreamRef writeStream;
    CFStreamCreatePairWithSocketToHost(NULL,
                                       (CFStringRef) @"localhost",
                                       4200,
                                       &readStream,
                                       &writeStream);
    NSInputStream *inputStream = (__bridge NSInputStream *) readStream;
    NSOutputStream *outputStream = (__bridge NSOutputStream *) writeStream;
    
    [inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop]
                           forMode:NSDefaultRunLoopMode];
    [outputStream scheduleInRunLoop:[NSRunLoop currentRunLoop]
                            forMode:NSDefaultRunLoopMode];
    
    [outputStream open];
    [inputStream open];
    
    CGImageRef ref;
    while(1){
        ref = CGWindowListCreateImage(frame, nil, [screenNr unsignedIntegerValue], nil);
        
        view.image = [[NSImage alloc] initWithCGImage:ref size:size];
        
        ref = CGWindowListCreateImage(frame, nil, [screenNr unsignedIntegerValue], nil);
        view.image = [[NSImage alloc] initWithCGImage:ref size:size];

        CGDataProviderRef provider = CGImageGetDataProvider(ref);
        NSData* data = (id)CFBridgingRelease(CGDataProviderCopyData(provider));
        const uint8_t* bytes = [data bytes];
    
        int length = [data length];
        
        [outputStream write:&length maxLength:4];
        [outputStream write:bytes maxLength:length];
    }
}

@end
