//
//  main.m
//  Objective-C Runtime：深入理解类与对象
//
//  Created by Mac-Qke on 2019/7/10.
//  Copyright © 2019 Mac-Qke. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"
#import "TestMetaClass.h"
int main(int argc, char * argv[]) {
    @autoreleasepool {
        
        BOOL result1 = [(id)[NSObject class] isMemberOfClass:[NSObject class]];
        
        BOOL result2 = [(id)[NSObject class] isKindOfClass:[NSObject class]];
        
        BOOL result3 = [(id)[TestMetaClass class] isMemberOfClass:[TestMetaClass class]];
        
        BOOL result4 = [(id)[TestMetaClass class] isKindOfClass:[TestMetaClass class]];

        NSLog(@"%d %d %d %d", result1, result2, result3, result4);
        
        
        
        
        
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
