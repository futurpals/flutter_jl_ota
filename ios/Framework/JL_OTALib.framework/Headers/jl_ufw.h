/**
 * Des: 
 * author: Bob
 * date: 2022/11/29
 * Copyright: Jieli Technology
 */

#ifndef NATIVEAPPLICATION_JL_UFW_H
#define NATIVEAPPLICATION_JL_UFW_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <android/log.h>
//#include <jni.h>
//
//#define tag "myJNI"
//#define logi(TAG, ...)  ((void)__android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__))
//#define logw(TAG, ...)  ((void)__android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__))
//#define loge(TAG, ...)  ((void)__android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__))

int parse_fw_info(const char *data, int size, uint8_t *resultBuff, uint32_t buffSize);
#define     BIT(n)	            (1 << n)

// for FW file
enum eFW_FILE_TYPE {

    FILE_TYPE_FW_FLASH_BIN = 0,
    FILE_TYPE_FW_OTP_BIN = 1,
    FILE_TYPE_FW_INFO_LOG = 2,
    FILE_TYPE_FW_BURN_CFG = 3,
    FILE_TYPE_FW_SCRIPT_DATA = 4,
    FILE_TYPE_FW_SRC = 5,
    FILE_TYPE_FW_NAME_BIN = 6,
    FILE_TYPE_FW_OTP_VER_BIN = 7,
    FILE_TYPE_FW_OTPCFG_BIN = 8,
    FILE_TYPE_FW_OTP_CHIP_CONTROL_BIN = 9,

    FILE_TYPE_FW_OTP_MINI_UBOOT = 0xA,
    FILE_TYPE_FW_OTP_FIX_UBOOT = 0xB,
    FILE_TYPE_FW_FLASH_2_BIN = 0xC,
    FILE_TYPE_FW_BR18_EFUSE_CONFIG_BIN = 0xD,
    FILE_TYPE_FW_RESOURCE_FILE = 0xE,
    FILE_TYPE_FW_2018KEY_INFO = 0xF,

    FILE_TYPE_FW_BURNER_CUSTOMER_DATA = 0x10,
    FILE_TYPE_FW_BURNER_DV15_FLASH_BIN = 0x11,
    FILE_TYPE_FW_BURNER_APP_FLASH_BIN = 0x12,
    FILE_TYPE_FW_BURNER_DATA_FLASH_BIN = 0x13,
    FILE_TYPE_FW_BURNER_BR21_FLASH_BIN = 0x14,

    FILE_TYPE_FW_FLASH_BIN_2 = 0x20,
    FILE_TYPE_FW_FLASH_BIN_3,
    FILE_TYPE_FW_FLASH_BIN_4,

    FILE_TYPE_FW_LOADER_BIN = 0x31,

    FILE_TYPE_FW_TEST_BOX_OTA_BIN = 0x64,

    FILE_TYPE_FW_3RD_DATA_FILE = 0x71,

    FILE_TYPE_FW_OTA_TARGET_DEVICE_INFO = 0xA0,
    FILE_TYPE_FW_BURN_COUNT_LIMIT = 0xA1,

    FILE_TYPE_FW_ADDITIONAL_FILE = 0xEE,
    FILE_TYPE_FW_PASSTHROUGH_DATA = 0xEF,
    FILE_TYPE_FW_HIDDEN_CFG_BIN = 0xFA,
    FILE_TYPE_FW_INVISIBLE_DATA = 0xFB,
    FILE_TYPE_FW_VISIBLE_DATA = 0xFE,

    FILE_TYPE_FW_TAIL = 0xFF,
};

typedef struct U16BIT
{
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;
    unsigned char b8 : 1;
    unsigned char b9 : 1;
    unsigned char b10 : 1;
    unsigned char b11 : 1;
    unsigned char b12 : 1;
    unsigned char b13 : 1;
    unsigned char b14 : 1;
    unsigned char b15 : 1;

} U16BIT;
typedef union UBIT16
{
    U16BIT bits;
    uint16_t val;
} UBIT16;

typedef struct stRES_FILE_HEAD {
    uint32_t u32Tag;
    uint16_t u16Crc;
    uint16_t u16CrcOfItems;
    uint32_t u32Len;
    uint16_t u16Count;
    uint16_t u16Res;
    uint8_t u8Res16[16];
}RES_FILE_HEAD;

typedef struct stRES_CONFIG_ITEM {
    uint16_t u16Index;
    uint16_t u16Type;
    uint32_t u32Addr;
    uint32_t u32Len;
    uint16_t u16CrcOfData;
    uint16_t u16Res;
    char szName[16];
}RES_CONFIG_ITEM;
static uint16_t m_u16ChipKey = 0xFFFF;
static uint16_t m_u16DefaultKey = 0xFFFF;


#pragma pack(1)
#define JL_FILE_ITEM_NAME_MAX_LEN 16
#define JL_CHIP_KEY_ENC_LENGTH 32

typedef struct stUFW_SYD_HEAD_V1 {
    uint16_t u16Crc;          // crc16 for this struct
    uint16_t u16CrcOfSydFileHead;
    uint32_t u32FileLength;  // file length
    uint16_t u16FileCount;
    uint16_t u16Version;
    uint32_t u32Res;
    char    szChipName[16];
    uint32_t u32Res2[4];
    uint32_t u32Res3[4];
}UFW_SYD_HEAD_V1;

typedef struct stUFW_FILE_HEAD_V1 {
    uint8_t u8FileType;
    uint8_t u8Res;
    uint16_t u16Index;
    uint16_t u16Crc;
    uint16_t u16Version;
    uint32_t u32Addr;
    uint32_t u32Length;
    uint32_t u32AllLength;
    uint32_t u32EncryptedAddr;
    uint32_t u32EncryptedLength;
    uint32_t u32Res;
    uint32_t u64Res1[4];
    uint32_t u64Res2[4];
    char name[JL_FILE_ITEM_NAME_MAX_LEN];

}UFW_FILE_HEAD_V1;

typedef struct stJL_FILE_TAIL {
    char    szChipKey[JL_CHIP_KEY_ENC_LENGTH];
    uint16_t u16ChipKeyCRC16;
    uint8_t  u8Magic[6];
    uint8_t  u8Res8[8];          // 48
    char    szTailChipName[6];
    uint8_t  u8Reserv10[10];     // 64
}JL_FILE_TAIL;

typedef struct {
    char szName[3];
    char szVersion[3];
    uint8_t  u8Flag;
    uint8_t u8Res;
    uint32_t u32Crc;
    uint16_t u16Crc;
    uint16_t u16Res;
}JL_FLASH_BIN_TAIL;

typedef UFW_SYD_HEAD_V1 jl_ufw_syd_head;
typedef UFW_FILE_HEAD_V1 jl_ufw_file_head;
typedef JL_FILE_TAIL jl_ufw_tail;

typedef struct stJL_BR22_FLASH_HEAD {
    uint16_t u16Crc;
    uint8_t  u8SizeForBurner;
    uint8_t  u8Version;
    char vid[4];
    uint32_t u32FlashSize;
    uint8_t u8FsVersion;
    uint8_t u8BlockAlingnModulus;
    uint8_t u8Res;
    uint8_t u8SpecialOptFlag;
    char pid[16];
}JL_BR22_FLASH_HEAD;










#pragma pack()


#endif //NATIVEAPPLICATION_JL_UFW_H
