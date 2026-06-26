//
//  DFTime.h
//  
//
//  Created by Mac on 15/12/10.
//
//

#import <Foundation/Foundation.h>

@interface DFTime : NSObject
/**
 （：）
*/
+(long)dateCurrent;

/**
 */
+(NSArray*)dateMembers;

/**
 */
+ (NSString*)dateString;

/**
 */
+(NSDate*)makeDateYear:(int)y
                 Month:(int)mo
                   Day:(int)d
                  Hour:(int)h
                   Min:(int)m
                   Sec:(int)s;

/**
 */
+ (NSArray*)divideDateMembers:(NSString*)time;

/**
 */
+ (NSString*)addSec:(NSTimeInterval)sec OnDate:(NSString *)date;

/**
 */
+(NSTimeInterval)differenceOfDateA:(NSString*)timeA AndDateB:(NSString*)timeB;

/**
 */
+(NSTimeInterval)gapOfDateA:(NSDate*)dateA DateB:(NSDate*)dateB;


/**
 */
+ (NSInteger)day:(NSDate *)date;

/**
 */
+ (NSInteger)month:(NSDate *)date;

/**
 */
+ (NSInteger)year:(NSDate *)date;

/**
 */
+ (NSInteger)weekday:(NSDate *)date;

/**
 */
+ (NSInteger)firstWeekdayInThisMonth:(NSDate *)date;

/**
 */
+ (NSInteger)totaldaysInMonth:(NSDate *)date;

/**
 */
+ (NSDate *)changeMonth:(int)m onDate:(NSDate *)date;

/**
 */
+ (NSDate *)changeDay:(int)d onDate:(NSDate *)date;

/**
 */
+(NSString*)stringFromSec:(uint32_t)sec;

@end
