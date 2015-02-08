//
// Copyright (C) 2011 Vaugham Hong (vaughamhong@gmail.com)
//
// This file is subject to the terms and conditions defined in
// file 'license.txt', which is part of this source code package.
//

#import <UIKit/UIKit.h>
#import <sys/utsname.h>

//////////////////////////////////////////////////////////////////////////

#define DEVICEDETECTION_TUPLESET    DEVICEDETECTION_TUPLE(DEVICE_IPHONE_SIMULATOR,      @"iPhoneSim",      @"x86_64") \
                                    DEVICEDETECTION_TUPLE(DEVICE_IPHONE_3G,             @"iPhone3G",       @"iPhone1,2") \
                                    DEVICEDETECTION_TUPLE(DEVICE_IPHONE_3GS,            @"iPhone3GS",      @"iPhone2,1") \
                                    DEVICEDETECTION_TUPLE(DEVICE_IPHONE_4,              @"iPhone4",        @"iPhone3,1") \
                                    DEVICEDETECTION_TUPLE(DEVICE_IPHONE_4S,             @"iPhone4S",       @"iPhone3,1") \
                                    DEVICEDETECTION_TUPLE(DEVICE_IPHONE_5,              @"iPhone5",        @"iPhone5,1") \
                                    DEVICEDETECTION_TUPLE(DEVICE_IPAD_SIMULATOR,        @"iPadSim",        @"x86_64") \
                                    DEVICEDETECTION_TUPLE(DEVICE_IPAD_1,                @"iPad1",          @"iPad1,1") \
                                    DEVICEDETECTION_TUPLE(DEVICE_IPAD_2,                @"iPad2",          @"iPad2,1") \
                                    DEVICEDETECTION_TUPLE(DEVICE_IPOD_TOUCH_1,          @"iPodTouch1",     @"iPod1,1") \
                                    DEVICEDETECTION_TUPLE(DEVICE_IPOD_TOUCH_2,          @"iPodTouch2",     @"iPod2,1") \
                                    DEVICEDETECTION_TUPLE(DEVICE_IPOD_TOUCH_3,          @"iPodTouch3",     @"iPod3,1") \
                                    DEVICEDETECTION_TUPLE(DEVICE_IPOD_TOUCH_4,          @"iPodTouch4",     @"iPod4,1")

#define DEVICECLASS_TUPLESET        DEVICECLASS_TUPLE(CLASS_IPHONE,                     @"iPhone") \
                                    DEVICECLASS_TUPLE(CLASS_IPAD,                       @"iPad") \
                                    DEVICECLASS_TUPLE(CLASS_IPOD_TOUCH,                 @"iPodTouch")
                                    
//////////////////////////////////////////////////////////////////////////

#define DEVICEDETECTION_TUPLE(ENUM, deviceTypeString, MACHINESTRING) ENUM,
enum eDeviceType{
    DEVICE_INVALID = -1,
    DEVICEDETECTION_TUPLESET
    MAX_DEVICETYPES
};
#undef DEVICEDETECTION_TUPLE

#define DEVICECLASS_TUPLE(ENUM, deviceTypeString) ENUM,
enum eDeviceClass{
    CLASS_INVALID = -1,
    DEVICECLASS_TUPLESET
    MAX_CLASSES
};
#undef DEVICECLASS_TUPLE

//////////////////////////////////////////////////////////////////////////

@interface UIDevice(detect)
+ (eDeviceType) deviceType;
+ (eDeviceClass) deviceClass;

+ (NSString *) deviceTypeString;
+ (NSString *) deviceClassString;
- (NSString *) machine;

+ (BOOL) isIPhone;
+ (BOOL) isIPad;
+ (BOOL) isIPodTouch;
@end

//////////////////////////////////////////////////////////////////////////