//
//  ViewController.m
//  Objective-C Runtime：深入理解类与对象
//
//  Created by Mac-Qke on 2019/7/10.
//  Copyright © 2019 Mac-Qke. All rights reserved.
//

#import "ViewController.h"
#import <objc/runtime.h>
#import <objc/message.h>
#import "Dog.h"
#import "Animal.h"
@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    //[self testInstanceMethod];
//    [self dynamicAddMethod];
}



- (void)verifyClassTypeRelation{
    //Use `object_getClass` get Class's `isa`
    
    Dog *aDog = [[Dog alloc] init];
    Class dogCls = object_getClass(aDog);
    NSLog(@"isa->%@ , super_class->%@", dogCls, class_getSuperclass(dogCls));
    // print:isa->Dog, super_class->Animal
    
    
    
    Class dogMetaCls = objc_getMetaClass([NSStringFromClass(dogCls) UTF8String]);
    if (class_isMetaClass(dogMetaCls)) {
      NSLog(@"YES, metaCls->%@ , metaCls's super_Class->%@, metaCls's isa->%@", dogMetaCls, class_getSuperclass(dogMetaCls), object_getClass(dogMetaCls));
       //print: YES, metaCls->Dog , metaCls's super_Class->Animal, metaCls's isa->NSObject
    }else{
        NSLog(@"NO");
    }
    
    
    
    
    Animal *animal = [[Animal alloc] init];
    Class animalCls = object_getClass(animal);
    NSLog(@"isa->%@ , super_class->%@", animalCls, class_getSuperclass(animalCls));
    //print: isa->Animal , super_class->NSObject
    
    Class animalMetaCls = objc_getMetaClass([NSStringFromClass(animalCls) UTF8String]);
    if (class_isMetaClass(animalMetaCls)) {
        NSLog(@"YES, metaCls->%@ , metaCls's super_Class->%@, metaCls's isa->%@", animalMetaCls, class_getSuperclass(animalMetaCls), object_getClass(animalMetaCls));
        //print:YES, metaCls->Animal , metaCls's super_Class->NSObject, metaCls's isa->NSObject
    }else{
         NSLog(@"NO");
    }
    
    
    Class viewMetaCls = objc_getMetaClass([NSStringFromClass([UIView class]) UTF8String]);
    if (class_isMetaClass(viewMetaCls)) {
        NSLog(@"YES, metaCls->%@ , metaCls's super_Class->%@, metaCls's isa->%@", viewMetaCls, class_getSuperclass(viewMetaCls), object_getClass(viewMetaCls));
        //print:YES, metaCls->UIView , metaCls's super_Class->UIResponder, metaCls's isa->NSObject
    }
    
    
    Class rootMetaCls = objc_getMetaClass([NSStringFromClass([NSObject class]) UTF8String]);
    if (class_isMetaClass(rootMetaCls)) {
         NSLog(@"YES, metaCls->%@ , metaCls's super_Class->%@, metaCls's isa->%@", rootMetaCls, class_getSuperclass(rootMetaCls), object_getClass(rootMetaCls));
        //print:YES, metaCls->NSObject , metaCls's super_Class->NSObject, metaCls's isa->NSObject
    }
    
    
}


- (void)dynamicAddMethod{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundeclared-selector"
    
    //1、Create and register class, add method to class
    Class cls = objc_allocateClassPair([Animal class], "Lion", 0);
    
    
    // 当为`Cat`时，返回的创建类cat地址为0x0,将`Cat`作为关键字
    //method: 返回`int32_t`,type使用`i`;参数：`id self`,type使用`@`;`SEL _cmd`,type使用`:`;
    //`NSDictionary *dic`,type使用`@`.综上，type使用'i@:@'
    ///具体类型可参照 https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/ObjCRuntimeGuide/Articles/ocrtTypeEncodings.html
    
//    BOOL isAddSuccess = class_addMethod(cls, @selector(howlMethod), (IMP)verifyClassTypeRelation, "i@:@");
//    NSLog(@"%@", isAddSuccess ? @"添加方法成功" : @"添加方法失败");
    //You can only register a class once.
    objc_registerClassPair(cls);
    
    //2、Create instance of class
    id whiteCat = [[cls alloc] init];
    NSLog(@"%@, %@", object_getClass(whiteCat), class_getSuperclass(object_getClass(whiteCat)));
    // Print: Lion, Animal
    
    Class whiteCatCls = object_getClass(whiteCat);
    Class metaCls = objc_getMetaClass([NSStringFromClass(whiteCatCls) UTF8String]);
    if (class_isMetaClass(metaCls)) {
        NSLog(@"YES, %@, %@, %@", metaCls, class_getSuperclass(metaCls), object_getClass(metaCls));
        // Print: YES, Lion, Animal, NSObject
    }else{
         NSLog(@"NO");
    }
    
    //3、Method of class
    unsigned int methodCount = 0;
    Method *methods = class_copyMethodList(cls, &methodCount);
    for (int32_t i = 0; i < methodCount; i++) {
        Method aMethod = methods[i];
        NSLog(@"%@, %s", NSStringFromSelector(method_getName(aMethod)), method_getTypeEncoding(aMethod));
        //print:howlMethod, I@:@
    }
    free(methods);
    
    //4、call method
    int32_t result = (int)[whiteCat performSelector:@selector(howlMethod) withObject:@{@"name":@"lion",@"sex":@"male"}];
     NSLog(@"%d", result);//print:9
    
    
     //5、destory instance and class
    whiteCat = nil;
    
     // Do not call this function if instances of the cls class or any subclass exist.
    objc_disposeClassPair(cls);
    
    #pragma clang diagnostic pop
    
    
}

- (void)howlMethod{
    
}


- (void)testInstanceMethod {
    id theObject = class_createInstance([NSString class], sizeof(unsigned));
    
    id str1 = [theObject init];
    
    NSLog(@"%@",[str1 class]);
    
    id str2 = [[NSString alloc] initWithString:@"test"];
    
    NSLog(@"%@",[str2 class]);
    
    
}


- (void)test1{
//    NSObject *a = [[NSObject alloc] init];
//    id newB = object_copy(a, class_getInstanceSize(self.class));
//    object_setClass(newB, self.class);
//    object_dispose(a);
}


- (void)testGetNumberClass {
    int numClasses;
    Class *classes = NULL;
    
    numClasses = objc_getClassList(NULL, 0);
    if (numClasses > 0) {
        classes = (Class *) malloc(sizeof(Class) * numClasses);
        NSLog(@"count of classes:%d",numClasses);
        
        for (int i = 0; i < numClasses; i ++) {
            Class cls = classes[i];
            NSLog(@"class name: %s", class_getName(cls));
        }
    }
    
    free(classes);
}

@end
