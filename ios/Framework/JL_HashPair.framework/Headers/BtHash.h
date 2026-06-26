//
//  BtHash.h
//  BtHash
//
//  Created by EzioChan on 2022/6/29.
//

#import <Foundation/Foundation.h>

@interface BtHash : NSObject
/*
 @param [in]  pt[*1]      The plaintext
 @param ptlen       The length of the plaintext(octets)    range: 1~32
 @param [in]  key[*1]     The key for encrypt
 @param keylen[*1]  The length of the key(octets)          range: 1~32
 @param [out] mac[*1]     output : The Message Authentication Code    16 bytes.
 @return error if < 0, 0 is normal.
 */
+(int)decryptWithPlaintext:(unsigned char *)pt
           andPlaintextLen:(int)ptlen
                    andKey: (unsigned char *)key
                 andKeyLen: (int)keylen
                    andMac:(unsigned char *)mac;

@end
