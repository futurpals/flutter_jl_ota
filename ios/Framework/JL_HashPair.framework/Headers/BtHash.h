//
//  BtHash.h
//  BtHash
//
//  Created by EzioChan on 2022/6/29.
//

#import <Foundation/Foundation.h>

@interface BtHash : NSObject
/*
 */
+(int)decryptWithPlaintext:(unsigned char *)pt
           andPlaintextLen:(int)ptlen
                    andKey: (unsigned char *)key
                 andKeyLen: (int)keylen
                    andMac:(unsigned char *)mac;

@end
