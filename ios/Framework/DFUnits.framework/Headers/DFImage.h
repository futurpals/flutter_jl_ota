//
//  DFImage.h
//  DFUnits
//
//  Created by DFung on 16/1/22.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface DFImage : NSObject



/**
 */
+(NSData*)compressImage:(UIImage *)srcImage Scale:(double)scale;


/**
 */
+(UIImage*)loadImage:(NSString*)image;


/**
 */
+(UIImage*)blurImage:(UIImage*)image Blur:(CGFloat)blur;

/**
 */
+(UIImage*)blurImage:(UIImage*)image Blur:(CGFloat)blur TintColor:(UIColor*)color;

/**
 */
+(UIImage*)screenshotSize:(CGSize)size OnView:(UIView*)view;


@end
