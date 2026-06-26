//
//  JLBleEntity.m
//  JL_OTA
//
//  Created by the Jieli OTA sample on 2021/10/11.
//

#import "JLBleEntity.h"

@implementation JLBleEntity

- (nonnull id)copyWithZone:(nullable NSZone *)zone {
    JLBleEntity *entity = [[self class] allocWithZone:zone];
    entity.mRSSI = self.mRSSI;
    entity.mPeripheral = self.mPeripheral;
    entity.mName = self.mName;
    entity.bleMacAddress = self.bleMacAddress;
    entity.edrMacAddress = self.edrMacAddress;
    entity.pid = self.pid;
    entity.uid = self.uid;
    entity.mType = self.mType;
    return entity;
}

@end
