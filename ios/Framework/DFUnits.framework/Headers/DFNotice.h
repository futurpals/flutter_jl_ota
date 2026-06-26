//
//  DFNotice.h
//  IPCamera
//
//  Created by DFung on 16/5/27.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <UserNotifications/UserNotifications.h>



@interface DFNotice : NSObject

/**
 *
 */
+(void)post:(NSString*)name Object:(id)object;

/**
 *
 */
+(void)add:(NSString*)name Action:(SEL)action Own:(id)own;

/**
 *
 */
+(void)remove:(NSString*)name Own:(id)own;

/** (iOS 10.0 。)
 *
 */
+(void)pushLocalNoticeDate:(NSString*)date
                        ID:(NSString*)noteId
                     Txt_0:(NSString*)txt_0
                     Txt_1:(NSString*)txt_1
                     Txt_2:(NSString*)txt_2
                     Badge:(NSNumber*)badge
                    Repeat:(BOOL)repeat;

@end
