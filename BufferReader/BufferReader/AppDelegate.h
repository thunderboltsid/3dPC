//
//  AppDelegate.h
//  BufferReader
//
//  Created by Alexandru Barbarosie on 04/10/14.
//  Copyright (c) 2014 ___FULLUSERNAME___. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>{
    NSScreen *screen;
    NSRect frame;
    NSNumber *screenNr;
    NSSize size;
    NSImageView *view;
}

@property (assign) IBOutlet NSWindow *window;

@end
