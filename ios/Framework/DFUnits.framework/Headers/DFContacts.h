//
//  DFContacts.h
//  DFUnits
//
//  Created by DFung on 2018/4/19.
//

#import <Foundation/Foundation.h>
//#define JL_CONTACTS_ENABLE

#ifdef JL_CONTACTS_ENABLE
#import <Contacts/Contacts.h>

@interface DFContacts : NSObject
/**
 *
 */
+(void)scanContactsWithKeys:(NSArray*)keys
                     Result:(void(^)(NSArray*contacts,
                                     int flag))result;

/**
 *  {@"FamilyName":@"...",
 *   @"GivenName":@"...",
 *   @"Phones":@[@"iphone":@"110",@"home":@"456",...]}
 */
+(NSDictionary*)openContact:(CNContact*)contact;

@end
#endif
