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
    NSScreen *screen = [NSScreen mainScreen];
    NSRect frame = screen.frame;
    NSNumber *screenNr = [screen.deviceDescription valueForKey:@"NSScreenNumber"];
    
    NSImageView *view = [[NSImageView alloc] initWithFrame:CGRectMake(0, 0, 400, 400)];
    [self.window.contentView addSubview:view];
    CGImageRef ref;
    
    ref = CGWindowListCreateImage(frame, nil, [screenNr unsignedIntegerValue], nil);
    NSSize size;
    size.height = frame.size.height;
    size.width = frame.size.width;
    view.image = [[NSImage alloc] initWithCGImage:ref size:size];
    
    sleep(2);
    
    ref = CGWindowListCreateImage(frame, nil, [screenNr unsignedIntegerValue], nil);
    view.image = [[NSImage alloc] initWithCGImage:ref size:size];
}

@end
