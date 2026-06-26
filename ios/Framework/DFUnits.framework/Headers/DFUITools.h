//
//  DFUITools.h
//  DFUnits
//
//  Created by DFung on 2016/12/9.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef void (^TipsCompletion) (void);


@class DFTips;
@interface DFUITools : NSObject

#define kDF_SCR_W_0         (int)[DFUITools screen_W]
#define kDF_SCR_H_0         (int)[DFUITools screen_H]

#define kDF_SCR_W_1         (int)[DFUITools screen_1_W]
#define kDF_SCR_H_1         (int)[DFUITools screen_1_H]
#define kDF_RGBA(r,g,b,a)   [UIColor colorWithRed:((r)/255.0) green:((g)/255.0) blue:((b)/255.0) alpha:(a)]

#pragma mark - Vendor SDK
/**
 */
+(CGFloat)screen_W;

/**
 */
+(CGFloat)screen_H;

/**
 */
+(float)screen_1_W;

/**
 */
+(float)screen_1_H;

/**
 */
+(float)screen_2_W;

/**
 */
+(float)screen_2_H;

/**
 */
+(float)getVersion;

/**
 */
+(NSString*)getUUID;

/**
 */
+(UIWindow*)getWindow;

/**
 */
+(NSString*)systemLanguage;

/**
 */
+(void)languageSet:(NSString*)lan;

/**
 */
+(NSString*)languageText:(NSString*)key Table:(NSString*)table;

/**
 */
+(void)setButton:(UIButton*)btn Image:(NSString*)image;
+(void)setButton:(UIButton*)btn Image_1:(UIImage*)image;

/**
 */
+(void)setButton:(UIButton*)btn Text:(NSString*)text;

/**
 */
+(void)setButton:(UIButton*)btn Color:(UIColor*)color;

/**
 */
+ (CGFloat)labelHeightByWidth:(CGFloat)width Text:(NSString *)text Font:(UIFont *)font;

/**
 */
+ (CGFloat)labelWidthByWidth:(CGFloat)width Text:(NSString *)text Font:(UIFont *)font;

/**
 */
+(id)loadNib:(NSString*)name;


/**
 */
+(UITapGestureRecognizer*)addSingleTaps:(int)taps
                                   View:(UIView*)view
                                 Target:(id)target
                                 Action:(SEL)action;


/**
 */
+(UIColor*)colorR:(float)r G:(float)g B:(float)b AP:(float)ap;




#pragma mark >>> DFTips___APIs___
+ (DFTips *)showHUDWithLabel:(NSString *)labelText
                      onView:(UIView *)view;

+ (DFTips *)showHUDWithLabel_1:(NSString *)labelText
                        onView:(UIView *)view;

+ (DFTips *)showHUDWithDetailLabel:(NSString *)detailLabelText
                            onView:(UIView *)view;

+ (DFTips *)showHUDOnWindowWithLabel:(NSString *)labelText;

+ (DFTips *)showHUDWithLabel:(NSString *)labelText
                      onView:(UIView *)view
                            color:(UIColor *)color;

+ (DFTips *)showHUDWithLabel:(NSString *)labelText
                      onView:(UIView *)view
                       color:(UIColor *)color
              labelTextColor:(UIColor *)textColor
      activityIndicatorColor:(UIColor *)actIndicatorColor;

+ (DFTips *)showHUDWithLabel:(NSString *)labelText
                onView:(UIView *)view
                 alpha:(float)alpha
                 color:(UIColor *)color
        labelTextColor:(UIColor *)textColor
      activityIndicatorColor:(UIColor *)actIndicatorColor;

+ (DFTips *)showHUDOnWindowWithLabel:(NSString *)labelText
                               color:(UIColor *)color;

+ (DFTips *)showTransparentHUDWithLabel:(NSString *)labelText
                                 onView:(UIView *)view;

+ (DFTips *)showTransparentHUDOnWindowWithLabel:(NSString *)labelText
                                 labelTextColor:(UIColor *)textColor;

+ (DFTips *)showTransparentHUDOnWindowWithLabel:(NSString *)labelText;

+ (DFTips *)changeLabelText:(NSString *)labelText;

+ (DFTips *)changeDetailLabelText:(NSString *)labelText;

+ (void)removeHUD;

+ (void)removeHUDWithDelay:(float)time;

+ (void)removeHUDWithDelay:(float)time
                completion:(TipsCompletion)completion;

+ (void)showText:(NSString *)text
          onView:(UIView *)view
           delay:(float)time;

+ (void)showText:(NSString *)text
          onView:(UIView *)view
           delay:(float)time
      completion:(TipsCompletion)completion;

+ (void)showText_1:(NSString *)text
            onView:(UIView *)view
             delay:(float)time;

+ (void)showDetailText:(NSString *)text
                onView:(UIView *)view
                 delay:(float)time;

+ (void)showDetailText:(NSString *)text
                onView:(UIView *)view
                 delay:(float)time
            completion:(TipsCompletion)completion;

+(void)showClearLayer;
+(void)showClearLayerDelay:(NSTimeInterval)time;

+(void)openWaittting:(NSString*)text delay:(NSTimeInterval)time;
+(void)closeWaitting:(NSTimeInterval)time;


@end
