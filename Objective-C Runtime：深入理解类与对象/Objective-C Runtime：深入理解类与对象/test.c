//
//  test.c
//  Objective-C Runtime：深入理解类与对象
//
//  Created by Mac-Qke on 2019/7/10.
//  Copyright © 2019 Mac-Qke. All rights reserved.
//

#include "test.h"
//类与对象
//
//1.类的数据结构(Class)
struct {
    //isa指针指向Class
   //  Class _Nonnull isa  OBJC_ISA_AVAILABILITY;
    
#if !__OBJC2__
//    Class _Nullable super_class  OBJC2_UNAVAILABLE; // 父类
//    const char * _Nonnull name OBJC2_UNAVAILABLE; // 类名
//    long version  OBJC2_UNAVAILABLE; // 类的版本信息，默认为0
//    long info  OBJC2_UNAVAILABLE; // 类信息，供运行时使用的一些位标识
//    long instance_size  OBJC2_UNAVAILABLE; // 类的实例变量大小
//    // 类的成员变量列表
//    struct objc_ivar_list * _Nullable ivars  OBJC2_UNAVAILABLE;
//    // 方法定义列表
//    struct objc_method_list * _Nullable * _Nullable methodLists  OBJC2_UNAVAILABLE;
//    // 方法缓存
//    struct objc_cache * _Nonnull cache  OBJC2_UNAVAILABLE;
//    // 协议列表
//    struct objc_protocol_list * _Nullable protocols OBJC2_UNAVAILABLE;
#endif
    
} OBJC2_UNAVAIABLE;

//在Objective-C中类是由Class表示的，Class是一个指向struct objc_class的指针
typedef struct objc_class *class;

//struct objc_cache {
//    unsigned int mask /* total = mask + 1 */                 OBJC2_UNAVAILABLE;
//    unsigned int occupied                                    OBJC2_UNAVAILABLE;
//    Method buckets[1]                                        OBJC2_UNAVAILABLE;
//};
/*
 字段的具体描述如下：
 
 mask：整数类型，指定分配的缓存bucket的总数。在方法查找过程中，Objective-C runtime使用这个字段来确定开始线性查找数组的索引位置。指向方法selector的指针与该字段做一个AND位操作(index = (mask & selector))。这可以看作为一个简单的hash散列算法;
 occupied:一个整数，指定实际占用的缓存bucket的总数;
 buckets：指向Method数据结构指针的数组。这个数组可能包含不超过mask+1个元素。需要注意的是，指针可能是NULL，表示这个缓存bucket没有被占用。另外被占用的bucket可能是不连续的。这个数组可能会随着时间而增长。
 
 关于上文object_class中结构体中的cache字段，对它的解释如下：
 
 cache：用于缓存最近使用的方法，一个对象可响应的方法列表中通常只有一部分是经常被调用的，cache 则是用来缓存最常调用的方法，从而避免每次方法调用时都去查找对象的整个方法列表，提升性能。
 在一些结构较为复杂的类关系中，一个对象的响应方法可能来自于继承的类结构中，此情况下查找相应的响应方法时就会比较耗时，通常使用cache缓存可以减低查找时间；
 
 */

//2.元类(Meta Class)

//3类的实例数据结构
/// Represents an instance of a class.
//struct objc_object {
//    Class _Nonnull isa  OBJC_ISA_AVAILABILITY;
//};

typedef struct objc_object *id;

//3.1相关函数
//3.1.1类相关函数
// 获取类的类名
//const char * class_getName ( Class cls );
//父类(super_class)和元类(meta_class)
// 获取类的父类
//Class class_getSuperclass ( Class cls );
//// 判断给定的Class是否是一个元类
//BOOL class_isMetaClass ( Class cls );
//实例变量大小(instance_size)
// 获取实例大小
//size_t class_getInstanceSize ( Class cls );
//成员变量(ivars)及属性

//// 获取类中指定名称实例成员变量的信息
//Ivar class_getInstanceVariable ( Class cls, const char *name );
//// 获取类成员变量的信息
//Ivar class_getClassVariable ( Class cls, const char *name );
//// 添加成员变量
//BOOL class_addIvar ( Class cls, const char *name, size_t size, uint8_t alignment, const char *types );
//// 获取整个成员变量列表
//Ivar * class_copyIvarList ( Class cls, unsigned int *outCount );


// 获取指定的属性
//objc_property_t class_getProperty ( Class cls, const char *name );
//// 获取属性列表
//objc_property_t * class_copyPropertyList ( Class cls, unsigned int *outCount );
//// 为类添加属性
//BOOL class_addProperty ( Class cls, const char *name, const objc_property_attribute_t *attributes, unsigned int attributeCount );
//// 替换类的属性
//void class_replaceProperty ( Class cls, const char *name, const objc_property_attribute_t *attributes, unsigned int attributeCount );


//方法(methodLists)
// 添加方法
//BOOL class_addMethod ( Class cls, SEL name, IMP imp, const char *types );
//// 获取实例方法
//Method class_getInstanceMethod ( Class cls, SEL name );
//// 获取类方法
//Method class_getClassMethod ( Class cls, SEL name );
//// 获取所有方法的数组
//Method * class_copyMethodList ( Class cls, unsigned int *outCount );
//// 替代方法的实现
//IMP class_replaceMethod ( Class cls, SEL name, IMP imp, const char *types );
//// 返回方法的具体实现
//IMP class_getMethodImplementation ( Class cls, SEL name );
//IMP class_getMethodImplementation_stret ( Class cls, SEL name );
//// 类实例是否响应指定的selector
//BOOL class_respondsToSelector ( Class cls, SEL sel );

//void myMethodIMP(id self, SEL _cmd)
//{
//    // implementation ....
//}

// 添加协议
//BOOL class_addProtocol ( Class cls, Protocol *protocol );
//// 返回类是否实现指定的协议
//BOOL class_conformsToProtocol ( Class cls, Protocol *protocol );
//// 返回类实现的协议列表
//Protocol * class_copyProtocolList ( Class cls, unsigned int *outCount );

// 获取版本号
//int class_getVersion ( Class cls );
//// 设置版本号
//void class_setVersion ( Class cls, int version );


//动态创建类与对象
// 创建一个新类和元类
//Class objc_allocateClassPair ( Class superclass, const char *name, size_t extraBytes );
//// 销毁一个类及其相关联的类
//void objc_disposeClassPair ( Class cls );
//// 在应用中注册由objc_allocateClassPair创建的类
//void objc_registerClassPair ( Class cls );


//// 创建类实例
//id class_createInstance ( Class cls, size_t extraBytes );
//// 在指定位置创建类实例
//id objc_constructInstance ( Class cls, void *bytes );
//// 销毁类实例
//void * objc_destructInstance ( id obj );


// 实例操作函数
// 返回指定对象的一份拷贝
//id object_copy ( id obj, size_t size );
//// 释放指定对象占用的内存
//id object_dispose ( id obj );
//
//修改类实例的实例变量的值
//Ivar object_setInstanceVariable ( id obj, const char *name, void *value );
//// 获取对象实例变量的值
//Ivar object_getInstanceVariable ( id obj, const char *name, void **outValue );
//// 返回指向给定对象分配的任何额外字节的指针
//void * object_getIndexedIvars ( id obj );
//// 返回对象中实例变量的值
//id object_getIvar ( id obj, Ivar ivar );
//// 设置对象中实例变量的值
//void object_setIvar ( id obj, Ivar ivar, id value );


// 返回给定对象的类名
//const char * object_getClassName ( id obj );
//// 返回对象的类
//Class object_getClass ( id obj );
//// 设置对象的类
//Class object_setClass ( id obj, Class cls );

//获取类定义
//// 获取已注册的类定义的列表
//int objc_getClassList ( Class *buffer, int bufferCount );
//// 创建并返回一个指向所有已注册类的指针列表
//Class * objc_copyClassList ( unsigned int *outCount );
//// 返回指定类的类定义
//Class objc_lookUpClass ( const char *name );
//Class objc_getClass ( const char *name );
//Class objc_getRequiredClass ( const char *name );
//// 返回指定类的元类
//Class objc_getMetaClass ( const char *name );

//动态创建类的源码
/***********************************************************************
 * _objc_allocateFutureClass
 * Allocate an unresolved future class for the given class name.
 * Returns any existing allocation if one was already made.
 * Assumes the named class doesn't exist yet.
 * Locking: acquires runtimeLock
 **********************************************************************/
//Class _objc_allocateFutureClass(const char *name)
//{
//    rwlock_writer_t lock(runtimeLock);
//
//    Class cls;
//    NXMapTable *map = futureNamedClasses();
//
//    if ((cls = (Class)NXMapGet(map, name))) {
//        // Already have a future class for this name.
//        return cls;
//    }
//
//    cls = _calloc_class(sizeof(objc_class));
//    addFutureNamedClass(name, cls);
//
//    return cls;
//}

