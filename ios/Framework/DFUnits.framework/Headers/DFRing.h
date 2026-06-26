//
//  DFRing.h
//  libDVRunning
//
//  Created by DFung on 2017/7/13.
//

#import <Foundation/Foundation.h>

@interface DFRing : NSObject
@property(assign,nonatomic)int32_t len_total;


/**
 */
-(uint32_t)ringUsable;

/**
 */
-(BOOL)ringMakeSize:(int32_t)size;

/**
 */
-(uint32_t)ringPut:(void*)buf Size:(uint32_t)size;

/**
 */
-(uint32_t)ringGet:(void*)buf Size:(uint32_t)size;

/**
 */
-(void)ringClean;

/**
 */
-(void)ringRelease;

@end
