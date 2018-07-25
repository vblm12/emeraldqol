
// Includes
#include "global.h"
#include "malloc.h"
#include "battle.h"
#include "berry_blender.h"
#include "task.h"
#include "random.h"
#include "decompress.h"
#include "text.h"
#include "string_util.h"
#include "event_data.h"
#include "overworld.h"
#include "link.h"
#include "librfu.h"
#include "rom_8011DC0.h"
#include "link_rfu.h"

extern u16 gUnknown_03005DA8;

// Static type declarations

// Static RAM declarations

struct UnkRfuStruct_1 gUnknown_03004140;
struct UnkRfuStruct_2 gUnknown_03005000;

IWRAM_DATA u8 gUnknown_03000D74;
ALIGNED(4) IWRAM_DATA u8 gUnknown_03000D78[8];
IWRAM_DATA u8 gUnknown_03000D80[16];
IWRAM_DATA u16 gUnknown_03000D90[8];

EWRAM_DATA u8 gWirelessStatusIndicatorSpriteId = 0;
EWRAM_DATA ALIGNED(4) struct UnkLinkRfuStruct_02022B14 gUnknown_02022B14 = {};
EWRAM_DATA ALIGNED(2) u8 gUnknown_02022B22[8] = {};
EWRAM_DATA struct UnkLinkRfuStruct_02022B2C gUnknown_02022B2C = {};
EWRAM_DATA struct UnkLinkRfuStruct_02022B44 gUnknown_02022B44 = {};

// Static ROM declarations

static void sub_800C000(void);
static void sub_800C7B4(u16 r8, u16 r6);
static void sub_800C744(u32 a0);
static void sub_800CEB0(u16 r6);
static void sub_800CF34(void);
static void sub_800D158(void);
static void sub_800D20C(void);
static void sub_800D268(void);
static u8 sub_800D294(void);
static void sub_800D30C(u8 a0, u8 a1);
static void sub_800D334(u8 a0);
static void sub_800D358(u8 a0);
static void sub_800D434(void);
static void sub_800D610(void);
void sub_800D630(void);
static bool8 sub_800DAC8(struct UnkRfuStruct_2_Sub_c1c *q1, u8 *q2);
static void sub_800EAB4(void);
static void sub_800EAFC(void);
void sub_800ED34(u16 unused);
static void sub_800EDBC(u16 unused);
static void sub_800F048(void);
static void sub_800F86C(u8 unused);
static void sub_800FCC4(struct UnkRfuStruct_2_Sub_6c *data);
void sub_800FD14(u16 command);
static void rfufunc_80F9F44(void);
static void sub_800FFB0(void);
static void rfufunc_80FA020(void);
bool32 sub_8010454(u32 a0);
static void sub_8010528(void);
void sub_8010750(void);
int sub_80107A0(void);
void sub_801084C(u8 taskId);
void sub_80109E8(u16 a0);
void sub_8010A70(void *a0);
void sub_8010AAC(u8 taskId);
void sub_8010D0C(u8 taskId);
void sub_80115EC(u16 a0);
u8 sub_8011CE4(const u8 *a0, u16 a1);
void sub_8011D6C(u8 a0);
void sub_8011E94(u8 a0, u8 a1);
u8 sub_8012224(void);
void sub_801227C(void);

// .rodata

const u16 gWirelessLinkIconPalette[] = INCBIN_U16("graphics/interface/wireless_link_icon.gbapal");
const u8 gWirelessLinkIconPic[] = INCBIN_U8("graphics/interface/wireless_link_icon.4bpp.lz");
const u8 sWireless_ASCIItoRSETable[] = {
    0xff, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x37,
    0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
    0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
    0x00, 0xab, 0xb5, 0xb6, 0xb1, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xb2, 0xf1, 0x00, 0xae, 0xad, 0xba,
    0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8,
    0xa9, 0xaa, 0x00, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
    0x00, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf, 0xc0, 0xc1,
    0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9,
    0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1,
    0xd2, 0xd3, 0xd4, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6,
    0x00, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb,
    0xdc, 0xdd, 0xde, 0xdf, 0xe0, 0xe1, 0xe2, 0xe3,
    0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb,
    0xec, 0xed, 0xee, 0x2d, 0x2f, 0x30, 0x31, 0x32,
    0x33, 0x34, 0x35, 0x36, 0x50, 0x00, 0x01, 0x02,
    0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
    0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12,
    0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a,
    0x1b, 0xad, 0xb3, 0xb4, 0x00, 0xaf, 0x7d, 0x7f,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0xa0,
    0xae, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
    0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7e, 0xb0, 0xac,
    0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23,
    0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b,
    0x2c, 0x2e, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c,
    0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94
};
const u8 sWireless_RSEtoASCIITable[] = {
    0x20, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c,
    0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
    0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c,
    0x9d, 0x9e, 0x9f, 0xa0, 0xe0, 0xe1, 0xe2, 0xe3,
    0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb,
    0xec, 0xed, 0xee, 0xef, 0xf0, 0x7b, 0xf1, 0x7c,
    0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x82, 0x83, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    0x84, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7,
    0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
    0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
    0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
    0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xa6, 0xdd, 0xa7,
    0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xf2,
    0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa,
    0xfb, 0xfc, 0xfd, 0xfe, 0xff, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
    0xaf, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,
    0x37, 0x38, 0x39, 0x21, 0xdf, 0xa1, 0xb0, 0xa5,
    0xde, 0x24, 0x2a, 0xa2, 0xa3, 0x22, 0x23, 0x20,
    0xa4, 0x20, 0x2f, 0x41, 0x42, 0x43, 0x44, 0x45,
    0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d,
    0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55,
    0x56, 0x57, 0x58, 0x59, 0x5a, 0x61, 0x62, 0x63,
    0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b,
    0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73,
    0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x20,
    0x20, 0x2b, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00
};
const struct OamData sWirelessStatusIndicatorOamData = {
    .size = 1
};
static const union AnimCmd sWirelessStatusIndicatorAnim0[] = {
    // 3 bars
    ANIMCMD_FRAME( 4,  5),
    ANIMCMD_FRAME( 8,  5),
    ANIMCMD_FRAME(12,  5),
    ANIMCMD_FRAME(16, 10),
    ANIMCMD_FRAME(12,  5),
    ANIMCMD_FRAME( 8,  5),
    ANIMCMD_JUMP(0)
};
static const union AnimCmd sWirelessStatusIndicatorAnim1[] = {
    // 2 bars
    ANIMCMD_FRAME( 4,  5),
    ANIMCMD_FRAME( 8,  5),
    ANIMCMD_FRAME(12, 10),
    ANIMCMD_FRAME( 8,  5),
    ANIMCMD_JUMP(0)
};
static const union AnimCmd sWirelessStatusIndicatorAnim2[] = {
    // 1 bar
    ANIMCMD_FRAME(4, 5),
    ANIMCMD_FRAME(8, 5),
    ANIMCMD_JUMP(0)
};
static const union AnimCmd sWirelessStatusIndicatorAnim3[] = {
    // searching
    ANIMCMD_FRAME( 4, 10),
    ANIMCMD_FRAME(20, 10),
    ANIMCMD_JUMP(0)
};
static const union AnimCmd sWirelessStatusIndicatorAnim4[] = {
    // error
    ANIMCMD_FRAME(24, 10),
    ANIMCMD_FRAME( 4, 10),
    ANIMCMD_JUMP(0)
};
static const union AnimCmd *const sWirelessStatusIndicatorAnims[] = {
    sWirelessStatusIndicatorAnim0,
    sWirelessStatusIndicatorAnim1,
    sWirelessStatusIndicatorAnim2,
    sWirelessStatusIndicatorAnim3,
    sWirelessStatusIndicatorAnim4
};
const struct CompressedSpriteSheet sWirelessStatusIndicatorSpriteSheet = {
    gWirelessLinkIconPic, 0x0380, 0xD431
};
const struct SpritePalette sWirelessStatusIndicatorSpritePalette = {
    gWirelessLinkIconPalette, 0xD432
};
static const struct SpriteTemplate sWirelessStatusIndicatorSpriteTemplate = {
    0xD431,
    0xD432,
    &sWirelessStatusIndicatorOamData,
    sWirelessStatusIndicatorAnims,
    NULL,
    gDummySpriteAffineAnimTable,
    SpriteCallbackDummy
};

const struct UnkLinkRfuStruct_02022B2C gUnknown_082ED608 = {
    0x04, 0x20, 0x00, 0x00, 0x02,
    &gUnknown_02022B14,
    gUnknown_02022B22,
    0x01, 0x00, 0x258, 0x12c
};
const u8 gUnknown_082ED620[] = {
    0, 3, 2, 1, 0
};
const u32 gUnknown_082ED628[] = {
    0x000000,
    0x000001,
    0x000003,
    0x000007,
    0x00000f,
    0x00001f,
    0x00003f,
    0x00007f,
    0x0000ff,
    0x0001ff,
    0x0003ff,
    0x0007ff,
    0x000fff,
    0x001fff,
    0x003fff,
    0x007fff,
    0x00ffff,
    0x01ffff,
    0x03ffff,
    0x07ffff,
    0x0fffff,
    0x1fffff,
    0x3fffff,
    0x7fffff,
    0xffffff
};
const u8 gUnknown_082ED68C[] = {
    0, 0, 1,
    1, 2, 2,
    2, 2, 3
};
const u8 gUnknown_082ED695[] = {
    0, 1, 1, 2,
    1, 2, 2, 3,
    1, 2, 2, 3,
    2, 3, 3, 4
};
const u8 gUnknown_082ED6A5[] = {
    0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};
const struct {
    u8 *buffer;
    u32 size;
} gUnknown_082ED6B8[] = {
    { gBlockSendBuffer, 200 },
    { gBlockSendBuffer, 200 },
    { gBlockSendBuffer, 100 },
    { gBlockSendBuffer, 220 },
    { gBlockSendBuffer,  40 }
};
const u16 gUnknown_082ED6E0[] = {
    0x0002, 0x7f7d, 0x0000, 0xffff
};

const char sUnref_082ED6E8[][15] = {
    "RFU WAIT",
    "RFU BOOT",
    "RFU ERROR",
    "RFU RESET",
    "RFU CONFIG",
    "RFU START",
    "RFU SC POLL",
    "RFU SP POLL",
    "RFU START",
    "RFU SEND ERR",
    "RFU CP POLL"
};
const char sUnref_082ED6E9[][16] = {
    "              ",
    "RECOVER START ",
    "DISSCONECT    ",
    "RECOVER SUUSES",
    "RECOVER FAILED"
};
const TaskFunc gUnknown_082ED7E0[] = {
    sub_801084C,
    sub_8010AAC,
    sub_8010D0C
};
const char gUnknown_082ED7EC[] = "PokemonSioInfo";
const char gUnknown_082ED7FC[] = "LINK LOSS DISCONNECT!";
const char gUnknown_082ED814[] = "LINK LOSS RECOVERY NOW";

// .text

u32 sub_800BEC0(void)
{
    u32 r4;

    r4 = rfu_REQBN_softReset_and_checkID();
    if (r4 == 0x8001)
    {
        gUnknown_03004140.unk_08 = 1;
    }
    if (gUnknown_03004140.unk_04 != 0x17 && gUnknown_03004140.unk_04 != 0x01)
    {
        gUnknown_03004140.unk_05 = 0;
        gUnknown_03004140.unk_04 = 0;
    }
    gUnknown_03004140.unk_07 = 0;
    gUnknown_03004140.unk_0d = 0;
    gUnknown_03004140.unk_01 = 0;
    gUnknown_03004140.unk_00 = 0;
    gUnknown_03004140.unk_06 = -1;
    sub_800D610();
    return r4;
}

void rfu_REQ_sendData_wrapper(u8 r2)
{
    u8 val;
    if (!gUnknown_03007890->unk_00)
    {
        val = gUnknown_03004140.unk_02;
        r2 = 0;
        if (val == 1)
        {
            r2 = 1;
        }
    }
    else
    {
        gUnknown_03004140.unk_03 = 0;
    }
    rfu_REQ_sendData(r2);
}

int sub_800BF4C(void (*func1)(u8, u8), void (*func2)(u16))
{
    if (func1 == NULL)
    {
        return 4;
    }
    CpuFill16(0, &gUnknown_03004140, offsetof(struct UnkRfuStruct_1, filler_48));
    gUnknown_03004140.unk_06 = -1;
    gUnknown_03004140.unk_40 = func1;
    gUnknown_03004140.unk_44 = func2;
    rfu_setMSCCallback(sub_800CEB0);
    rfu_setREQCallback(sub_800C7B4);
    return 0;
}

void sub_800BFA0(void)
{
    CpuFill16(0, &gUnknown_03004140, offsetof(struct UnkRfuStruct_1, unk_40));
    gUnknown_03004140.unk_06 = -1;
}

void sub_800BFCC(const struct UnkLinkRfuStruct_02022B2C *unk0)
{
    sub_800C000();
    gUnknown_03004140.unk_04 = 1;
    gUnknown_03004140.unk_05 = 2;
    gUnknown_03004140.unk_3c = unk0;
    gUnknown_03004140.unk_09 = unk0->unk_11;
    gUnknown_03004140.unk_32 = unk0->unk_12;
    gUnknown_03004140.unk_18 = unk0->unk_14;
    if (unk0->unk_10)
    {
        gUnknown_03004140.unk_0b = 1;
    }
}

static void sub_800C000(void)
{
    u8 i;

    gUnknown_03004140.unk_05 = 0;
    gUnknown_03004140.unk_04 = 0;
    gUnknown_03004140.unk_06 = -1;
    gUnknown_03004140.unk_07 = 0;
    gUnknown_03004140.unk_10 = 0;
    gUnknown_03004140.unk_0c = 0;
    gUnknown_03004140.unk_24 = 0;
    gUnknown_03004140.unk_30 = 0;
    for (i = 0; i < 4; i++)
    {
        gUnknown_03004140.unk_28[i] = 0;
        gUnknown_03004140.unk_34[i] = 0;
    }
}

void sub_800C048(void)
{
    gUnknown_03004140.unk_04 = 0x15;
}

u8 sub_800C054(u8 r5, u16 r7, u16 r8, const u16 *r6)
{
    u8 i;
    const u16 *buffer;

    if (gUnknown_03004140.unk_04 != 0 && (gUnknown_03004140.unk_04 != 0x08 || r5 != 1))
    {
        gUnknown_03004140.unk_14 = 1;
        sub_800D30C(0xf3, 0x01);
        return 1;
    }
    if (!rfu_getMasterSlave())
    {
        gUnknown_03004140.unk_14 = 2;
        sub_800D30C(0xf3, 0x01);
        return 2;
    }
    for (i = 0, buffer = r6; i < 16; i++)
    {
        if (*buffer++ == 0xFFFF)
        {
            break;
        }
    }
    if (i == 16)
    {
        gUnknown_03004140.unk_14 = 4;
        sub_800D30C(0xf3, 0x01);
        return 4;
    }
    if (r5 > 1)
    {
        gUnknown_03004140.unk_07 = 1;
        r5 = 1;
        r7 = 0;
    }
    else
    {
        gUnknown_03004140.unk_07 = 0;
    }
    if (r5 != 0)
    {
        gUnknown_03004140.unk_04 = 5;
    }
    else
    {
        gUnknown_03004140.unk_04 = 9;
        if (gUnknown_03004140.unk_0b)
        {
            gUnknown_03004140.unk_0b = 2;
        }
    }
    gUnknown_03004140.unk_06 = r5;
    gUnknown_03004140.unk_1a = r7;
    gUnknown_03004140.unk_26 = r8;
    gUnknown_03004140.unk_20 = r6;
    return 0;
}

u8 sub_800C12C(u16 r6, u16 r8)
{
    u8 i;
    struct RfuUnk5 *tmp;

    if (gUnknown_03004140.unk_04 != 0 && (gUnknown_03004140.unk_04 < 9 || gUnknown_03004140.unk_04 > 11))
    {
        gUnknown_03004140.unk_14 = 1;
        sub_800D30C(0xF3, 0x01);
        return 1;
    }
    if (!rfu_getMasterSlave())
    {
        gUnknown_03004140.unk_14 = 2;
        sub_800D30C(0xF3, 0x01);
        return 2;
    }
    for (i = 0; i < gUnknown_03007890->unk_08; i++)
    {
        if (gUnknown_03007890->unk_14[i].unk_00 == r6)
        {
            break;
        }
    }
    if (gUnknown_03007890->unk_08 == 0 || i == gUnknown_03007890->unk_08)
    {
        gUnknown_03004140.unk_14 = 3;
        sub_800D30C(0xF3, 0x01);
        return 3;
    }
    if (gUnknown_03004140.unk_04 == 0 || gUnknown_03004140.unk_04 == 9)
    {
        gUnknown_03004140.unk_04 = 12;
        gUnknown_03004140.unk_05 = 13;
    }
    else
    {
        gUnknown_03004140.unk_04 = 11;
        gUnknown_03004140.unk_05 = 12;
    }
    gUnknown_03004140.unk_1e = r6;
    gUnknown_03004140.unk_1a = r8;
    if (gUnknown_03004140.unk_07 != 0)
    {
        gUnknown_03004140.unk_07 = 7;
    }
    return 0;
}

void sub_800C210(u8 a0)
{
    u8 i;

    if (a0 & gUnknown_03004140.unk_30)
    {
        gUnknown_03004140.unk_30 &= ~a0;
        for (i = 0; i < 4; i++)
        {
            if ((a0 >> i) & 1)
            {
                gUnknown_03004140.unk_34[i] = 0;
            }
        }
        i = gUnknown_03007890->unk_03 & a0;
        if (i)
        {
            sub_800D334(i);
        }
        gUnknown_03004140.unk_14 = i;
        sub_800D30C(0x33, i);
    }
}

void sub_800C27C(bool8 a0)
{
    u8 r2;

    r2 = 0;
    gUnknown_03004140.unk_07 = 0;
    if (a0)
    {
        sub_800C000();
        gUnknown_03004140.unk_04 = 23;
    }
    else
    {
        switch (gUnknown_03004140.unk_04)
        {
            case 5:
                gUnknown_03004140.unk_04 = 8;
                gUnknown_03004140.unk_05 = 0;
                r2 = 0x13;
                break;
            case 6:
                gUnknown_03004140.unk_04 = 7;
                gUnknown_03004140.unk_05 = 8;
                break;
            case 7:
                gUnknown_03004140.unk_04 = 7;
                gUnknown_03004140.unk_05 = 8;
                break;
            case 8:
                break;
            case 9:
                gUnknown_03004140.unk_05 = 0;
                gUnknown_03004140.unk_04 = 0;
                r2 = 0x21;
                break;
            case 10:
                gUnknown_03004140.unk_04 = 11;
                gUnknown_03004140.unk_05 = 0;
                break;
            case 11:
                gUnknown_03004140.unk_04 = 11;
                gUnknown_03004140.unk_05 = 0;
                break;
            case 12:
                gUnknown_03004140.unk_05 = 0;
                gUnknown_03004140.unk_04 = 0;
                r2 = 0x23;
                break;
            case 13:
                gUnknown_03004140.unk_04 = 14;
                break;
            case 14:
                gUnknown_03004140.unk_04 = 14;
                break;
            case 15:
                break;
            case 16:
                gUnknown_03004140.unk_04 = gUnknown_03004140.unk_11;
                gUnknown_03004140.unk_05 = gUnknown_03004140.unk_12;
                sub_800D334(gUnknown_03007890->unk_03);
                gUnknown_03004140.unk_14 = gUnknown_03007890->unk_03;
                sub_800D30C(0x33, 0x01);
                return;
            case 17:
                gUnknown_03004140.unk_04 = 18;
                break;
            case 18:
                gUnknown_03004140.unk_04 = 18;
                break;
            default:
                gUnknown_03004140.unk_05 = 0;
                gUnknown_03004140.unk_04 = 0;
                r2 = 0x43;
                break;
        }
        if (gUnknown_03004140.unk_04 == 0)
        {
            sub_800D30C(r2, 0);
        }
    }
}

bool8 sub_800C36C(u16 a0)
{
    bool8 retVal;
    u8 i;
    u8 sp0;
    u8 sp1;
    u8 sp2;
    u8 flags;

    retVal = FALSE;
    rfu_REQBN_watchLink(a0, &sp0, &sp1, &sp2);
    if (sp0)
    {
        gUnknown_03004140.unk_14 = sp0;
        gUnknown_03004140.unk_16 = sp1;
        if (gUnknown_03004140.unk_09)
        {
            gUnknown_03004140.unk_0a = 1;
            if (gUnknown_03004140.unk_06 == 0 && sp1 == 0)
            {
                gUnknown_03004140.unk_0a = 4;
            }
            if (gUnknown_03004140.unk_0a == 1)
            {
                for (i = 0; i < 4; i++)
                {
                    if ((sp0 >> i) & 1)
                    {
                        gUnknown_03004140.unk_30 |= (1 << i);
                        gUnknown_03004140.unk_34[i] = gUnknown_03004140.unk_32;
                    }
                }
                sub_800D30C(0x31, 0x01);
            }
            else
            {
                gUnknown_03004140.unk_0a = 0;
                sub_800D334(sp0);
                retVal = TRUE;
                sub_800D30C(0x33, 0x01);
            }
        }
        else
        {
            sub_800D334(sp0);
            retVal = TRUE;
            sub_800D30C(0x30, 0x02);
        }
        sub_800D610();
    }
    if (gUnknown_03007890->unk_00 == 1)
    {
        if (sp2)
        {
            for (i = 0; i < 4; i++)
            {
                if ((gUnknown_03004140.unk_30 >> i) & 1 && (sp2 >> i) & 1)
                {
                    gUnknown_03004140.unk_34[i] = 0;
                }
            }
            gUnknown_03004140.unk_30 &= ~sp2;
            gUnknown_03004140.unk_14 = sp2;
            sub_800D30C(0x32, 0x01);
        }
        if (gUnknown_03004140.unk_30)
        {
            flags = 0;
            for (i = 0; i < 4; i++)
            {
                if ((gUnknown_03004140.unk_30 >> i) & 1 && gUnknown_03004140.unk_34[i] && --gUnknown_03004140.unk_34[i] == 0)
                {
                    gUnknown_03004140.unk_30 &= ~(1 << i);
                    flags |= (1 << i);
                }
            }
            if (flags)
            {
                sub_800D334(flags);
                retVal = TRUE;
                gUnknown_03004140.unk_14 = flags;
                sub_800D30C(0x33, 0x01);
            }
        }
        if (!gUnknown_03004140.unk_30)
        {
            gUnknown_03004140.unk_0a = 0;
        }
    }
    return retVal;
}

void rfu_syncVBlank_(void)
{
    if (rfu_syncVBlank())
    {
        sub_800D30C(0xF1, 0x00);
        sub_800D610();
    }
}

void sub_800C54C(u32 a0)
{
    u8 r2;

    if (gUnknown_03004140.unk_40 == NULL && gUnknown_03004140.unk_04 != 0)
    {
        gUnknown_03004140.unk_04 = 0;
    }
    else
    {
        if (gUnknown_03004140.unk_07 != 0)
        {
            sub_800C744(a0);
        }
        do
        {
            if (gUnknown_03004140.unk_04 != 0)
            {
                rfu_waitREQComplete();
                gUnknown_03004140.unk_0e = 1;
                switch (gUnknown_03004140.unk_04)
                {
                    case 23:
                        r2 = sub_800BEC0() == 0x8001 ? 0x44 : 0xFF;
                        gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05 = 0;
                        sub_800D30C(r2, 0);
                        break;
                    case 1:
                        if (sub_800BEC0() == 0x8001)
                        {
                            gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05;
                            gUnknown_03004140.unk_05 = 3;
                        }
                        else
                        {
                            gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05 = 0;
                            sub_800D30C(0xFF, 0);
                        }
                        break;
                    case 2:
                        rfu_REQ_reset();
                        break;
                    case 3:
                        rfu_REQ_configSystem(gUnknown_03004140.unk_3c->unk_02, gUnknown_03004140.unk_3c->unk_00, gUnknown_03004140.unk_3c->unk_01);
                        break;
                    case 4:
                        rfu_REQ_configGameData(gUnknown_03004140.unk_3c->unk_04, gUnknown_03004140.unk_3c->unk_06, gUnknown_03004140.unk_3c->unk_08, gUnknown_03004140.unk_3c->unk_0c);
                        break;
                    case 5:
                        rfu_REQ_startSearchChild();
                        break;
                    case 6:
                        rfu_REQ_pollSearchChild();
                        break;
                    case 7:
                        rfu_REQ_endSearchChild();
                        break;
                    case 8:
                        break;
                    case 9:
                        rfu_REQ_startSearchParent();
                        break;
                    case 10:
                        rfu_REQ_pollSearchParent();
                        break;
                    case 11:
                        rfu_REQ_endSearchParent();
                        break;
                    case 12:
                        rfu_REQ_startConnectParent(gUnknown_03004140.unk_1e);
                        break;
                    case 13:
                        rfu_REQ_pollConnectParent();
                        break;
                    case 14:
                        rfu_REQ_endConnectParent();
                        break;
                    case 15:
                        break;
                    case 16:
                        rfu_REQ_CHILD_startConnectRecovery(gUnknown_03007890->unk_03);
                        break;
                    case 17:
                        rfu_REQ_CHILD_pollConnectRecovery();
                        break;
                    case 18:
                        rfu_REQ_CHILD_endConnectRecovery();
                        break;
                    case 19:
                        rfu_REQ_changeMasterSlave();
                        break;
                    case 20:
                        break;
                    case 21:
                        rfu_REQ_stopMode();
                        break;
                    case 22:
                        break;
                }
                rfu_waitREQComplete();
                gUnknown_03004140.unk_0e = 0;
            }
        } while (gUnknown_03004140.unk_04 == 18 || gUnknown_03004140.unk_04 == 19);
        if (gUnknown_03007890->unk_00 != 1 || !sub_800C36C(0))
        {
            sub_800CF34();
            sub_800D158();
            sub_800D268();
            sub_800D434();
        }
    }
}

static void sub_800C744(u32 a0)
{
    if (gUnknown_03004140.unk_07 == 5)
    {
        gUnknown_03004140.unk_06 = 1;
        gUnknown_03004140.unk_04 = 5;
        gUnknown_03004140.unk_1a = gUnknown_03004140.unk_1c;
        if (gUnknown_03004140.unk_1a)
        {
            gUnknown_03004140.unk_07 = 6;
        }
        else
        {
            gUnknown_03004140.unk_07 = 1;
        }
    }
    if (gUnknown_03004140.unk_07 == 1)
    {
        gUnknown_03004140.unk_06 = 1;
        gUnknown_03004140.unk_04 = 5;
        gUnknown_03004140.unk_1a = a0 % 140;
        gUnknown_03004140.unk_1c = 140 - gUnknown_03004140.unk_1a;
        if (gUnknown_03004140.unk_1a)
        {
            gUnknown_03004140.unk_07 = 2;
        }
        else
        {
            gUnknown_03004140.unk_07 = 3;
        }
    }
    if (gUnknown_03004140.unk_07 == 3)
    {
        gUnknown_03004140.unk_06 = 0;
        gUnknown_03004140.unk_1a = 40;
        gUnknown_03004140.unk_07 = 4;
        gUnknown_03004140.unk_04 = 9;
    }
}

static void sub_800C7B4(u16 r8, u16 r6)
{
    u8 sp0;
    register u8 *stwiRecvBuffer asm("r0");
    u8 *tmp;
    u8 i;

    if (gUnknown_03004140.unk_0e != 0)
    {
        gUnknown_03004140.unk_0e = 0;
        switch (r8)
        {
            case 16:
                if (r6 == 0)
                {
                    gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05;
                    gUnknown_03004140.unk_05 = 4;
                }
                break;
            case 23:
                if (r6 == 0)
                {
                    gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05;
                    gUnknown_03004140.unk_05 = 0;
                }
                break;
            case 22:
                if (r6 == 0)
                {
                    gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05 = 0;
                    sub_800D30C(0x00, 0x00);
                }
                break;
            case 25:
                if (r6 == 0)
                {
                    gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05 = 6;
                }
                break;
            case 26:
                if (gUnknown_03004140.unk_1a && --gUnknown_03004140.unk_1a == 0)
                {
                    gUnknown_03004140.unk_04 = 7;
                    gUnknown_03004140.unk_05 = 8;
                }
                break;
            case 27:
                if (r6 == 0)
                {
                    gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05;
                    gUnknown_03004140.unk_05 = 0;
                    if (gUnknown_03004140.unk_07 == 0)
                    {
                        sub_800D30C(0x13, 0x00);
                    }
                }
                break;
            case 28:
                if (r6 == 0)
                {
                    if (gUnknown_03004140.unk_0b == 1 && gUnknown_03004140.unk_1a > 1)
                    {
                        gUnknown_03004140.unk_1a--;
                    }
                    gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05 = 10;
                }
                break;
            case 29:
                if (r6 == 0)
                {
                    sp0 = sub_800D294();
                    gUnknown_03004140.unk_14 = sp0;
                    if (sp0)
                    {
                        sub_800D30C(0x20, 0x01);
                    }
                    if (gUnknown_03004140.unk_0b && gUnknown_03004140.unk_1a != 1 && gUnknown_03007890->unk_08 == 4)
                    {
                        rfu_REQ_endSearchParent();
                        rfu_waitREQComplete();
                        gUnknown_03004140.unk_04 = 9;
                        gUnknown_03004140.unk_0b = 1;
                    }
                }
                if (gUnknown_03004140.unk_1a && --gUnknown_03004140.unk_1a == 0)
                {
                    gUnknown_03004140.unk_04 = 11;
                    gUnknown_03004140.unk_05 = 0;
                }
                break;
            case 30:
                if (r6 == 0)
                {
                    gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05;
                    if (gUnknown_03004140.unk_07 == 0)
                    {
                        if (gUnknown_03004140.unk_04 == 0)
                        {
                            sub_800D30C(0x21, 0x00);
                        }
                    }
                    else if (gUnknown_03004140.unk_07 != 7)
                    {
                        gUnknown_03004140.unk_04 = 5;
                        gUnknown_03004140.unk_07 = 5;
                    }
                }
                break;
            case 31:
                if (r6 == 0)
                {
                    gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05 = 13;
                }
                break;
            case 32:
                if (r6 == 0 && !rfu_getConnectParentStatus(&sp0, &gUnknown_03004140.unk_10) && !sp0)
                {
                    gUnknown_03004140.unk_04 = 14;
                }
                if (gUnknown_03004140.unk_1a && --gUnknown_03004140.unk_1a == 0)
                {
                    gUnknown_03004140.unk_04 = 14;
                }
                break;
            case 33:
                if (r6 == 0 && !rfu_getConnectParentStatus(&sp0, &gUnknown_03004140.unk_10))
                {
                    if (!sp0)
                    {
                        gUnknown_03004140.unk_04 = 19;
                        gUnknown_03004140.unk_05 = 15;
                        gUnknown_03004140.unk_1e = 0x22;
                        gUnknown_03004140.unk_14 = gUnknown_03004140.unk_10;
                    }
                    else
                    {
                        gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05 = 0;
                        gUnknown_03004140.unk_1e = 0x23;
                        gUnknown_03004140.unk_14 = sp0;
                        if (gUnknown_03004140.unk_07)
                        {
                            gUnknown_03004140.unk_07 = 3;
                            gUnknown_03004140.unk_04 = 9;
                        }
                    }
                    sub_800D30C(gUnknown_03004140.unk_1e, 0x01);
                    gUnknown_03004140.unk_1e = 0;
                }
                break;
            case 50:
                if (r6 == 0)
                {
                    gUnknown_03004140.unk_14 = gUnknown_03007890->unk_03;
                    gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05 = 17;
                    for (gUnknown_03004140.unk_10 = 0; gUnknown_03004140.unk_10 < 4; gUnknown_03004140.unk_10 ++)
                    {
                        if ((gUnknown_03007890->unk_03 >> gUnknown_03004140.unk_10) & 1)
                        {
                            break;
                        }
                    }
                }
                break;
            case 51:
                if (r6 == 0 && !rfu_CHILD_getConnectRecoveryStatus(&sp0) && sp0 < 2)
                {
                    gUnknown_03004140.unk_04 = 18;
                }
                if (gUnknown_03004140.unk_34[gUnknown_03004140.unk_10] && --gUnknown_03004140.unk_34[gUnknown_03004140.unk_10] == 0)
                {
                    gUnknown_03004140.unk_04 = 18;
                }
                break;
            case 52:
                if (r6 == 0 && !rfu_CHILD_getConnectRecoveryStatus(&sp0))
                {
                    if (!sp0)
                    {
                        gUnknown_03004140.unk_04 = 19;
                        gUnknown_03004140.unk_05 = 22;
                        gUnknown_03004140.unk_1e = 0x32;
                    }
                    else
                    {
                        gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05 = 0;
                        sub_800D334(gUnknown_03007890->unk_03);
                        gUnknown_03004140.unk_1e = 0x33;
                    }
                    gUnknown_03004140.unk_34[gUnknown_03004140.unk_10] = 0;
                    gUnknown_03004140.unk_30 = 0;
                    gUnknown_03004140.unk_0a = 0;
                    sub_800D30C(gUnknown_03004140.unk_1e, 0x01);
                    gUnknown_03004140.unk_1e = 0;
                }
                break;
            case 39:
                if (r6 == 0)
                {
                    if (gUnknown_03004140.unk_05 == 22)
                    {
                        gUnknown_03004140.unk_04 = gUnknown_03004140.unk_11;
                        gUnknown_03004140.unk_05 = gUnknown_03004140.unk_12;
                        gUnknown_03004140.unk_02 = 1;
                        sub_800D30C(0x41, 0x00);
                    }
                    else if (gUnknown_03004140.unk_05 == 15)
                    {
                        gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05;
                        gUnknown_03004140.unk_02 = 1;
                        sub_800D30C(0x41, 0x00);
                        gUnknown_03004140.unk_24 |= 1 << gUnknown_03004140.unk_10;
                        gUnknown_03004140.unk_28[gUnknown_03004140.unk_10] = gUnknown_03004140.unk_26;
                        rfu_clearSlot(4, gUnknown_03004140.unk_10);
                        tmp = &sp0;
                        *tmp = rfu_NI_CHILD_setSendGameName(gUnknown_03004140.unk_10, 0x0e);
                        if (*tmp)
                        {
                            gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05 = 0;
                            sub_800D610();
                            sub_800D334(gUnknown_03007890->unk_02 | gUnknown_03007890->unk_03);
                            gUnknown_03004140.unk_14 = sp0;
                            sub_800D30C(0x25, 0x01);
                        }
                    }
                }
                break;
            case 61:
                if (r6 == 0)
                {
                    gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05 = 0;
                    sub_800D30C(0x42, 0x00);
                }
                break;
        }
        gUnknown_03004140.unk_0e = 1;
    }
    else if (r6 == 3 && gUnknown_03004140.unk_0f && (r8 == 0x24 || r8 == 0x26 || r8 == 0x27))
    {
        rfu_REQ_RFUStatus();
        rfu_waitREQComplete();
        rfu_getRFUStatus(&sp0);
        if (sp0 == 0 && gUnknown_03007890->unk_00 == 0)
        {
            stwiRecvBuffer = rfu_getSTWIRecvBuffer();
            stwiRecvBuffer[4] = gUnknown_03007890->unk_02;
            stwiRecvBuffer[5] = 1;
            sub_800C36C(0x29);
            r6 = 0;
        }
    }
    switch (r8)
    {
        case 48:
            if (r6 == 0)
            {
                stwiRecvBuffer = rfu_getSTWIRecvBuffer();
                gUnknown_03004140.unk_14 = stwiRecvBuffer[8];
                sub_800D358(gUnknown_03004140.unk_14);
                if (gUnknown_03004140.unk_30)
                {
                    gUnknown_03004140.unk_30 &= ~gUnknown_03004140.unk_14;
                    for (i = 0; i < 4; i++)
                    {
                        if ((gUnknown_03004140.unk_14 >> i) & 1)
                        {
                            gUnknown_03004140.unk_34[i] = 0;
                        }
                    }
                    if (gUnknown_03004140.unk_06 == 0)
                    {
                        gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05 = 0;
                    }
                }
                sp0 = gUnknown_03004140.unk_00 & gUnknown_03004140.unk_14;
                for (i = 0; i < 4; i++)
                {
                    if ((sp0 >> i) & 1 && gUnknown_03004140.unk_01)
                    {
                        gUnknown_03004140.unk_01--;
                    }
                }
                gUnknown_03004140.unk_00 &= ~gUnknown_03004140.unk_14;
                if (gUnknown_03004140.unk_07)
                {
                    if (gUnknown_03007890->unk_00 == 0xFF)
                    {
                        if (gUnknown_03004140.unk_07 == 8)
                        {
                            gUnknown_03004140.unk_1a = gUnknown_03004140.unk_1c;
                            gUnknown_03004140.unk_07 = 6;
                            gUnknown_03004140.unk_04 = 6;
                        }
                        else if (gUnknown_03004140.unk_04 != 6 && gUnknown_03004140.unk_04 != 7)
                        {
                            gUnknown_03004140.unk_07 = 1;
                            gUnknown_03004140.unk_04 = 5;
                        }
                    }
                }
                if (gUnknown_03007890->unk_00 == 0xFF)
                {
                    if (gUnknown_03004140.unk_04 == 0)
                    {
                        gUnknown_03004140.unk_06 = -1;
                    }
                }
                if (gUnknown_03004140.unk_0e == 0)
                {
                    sub_800D30C(0x40, 0x01);
                }
            }
            break;
        case 38:
            sub_800D20C();
            if (gUnknown_03007890->unk_00 != 0xFF)
            {
                sub_800D30C(0x50, 0x00);
            }
            break;
        case 16:
        case 61:
            if (r6 == 0)
            {
                gUnknown_03004140.unk_0d = 0;
                gUnknown_03004140.unk_01 = 0;
                gUnknown_03004140.unk_00 = 0;;
                gUnknown_03004140.unk_06 = -1;
                sub_800D610();
                if (r8 == 61)
                {
                    sub_800BFA0();
                }
            }
            break;
    }
    if (r6 != 0)
    {
        if (r8 == 28 && r6 != 0 && gUnknown_03004140.unk_07 == 4)
        {
            gUnknown_03007890->unk_00 = 1;
            gUnknown_03007890->unk_02 = 15;
            sub_800D334(15);
            rfu_waitREQComplete();
            return;
        }
        else
        {
            gUnknown_03004140.unk_14 = r8;
            gUnknown_03004140.unk_16 = r6;
            if (gUnknown_03004140.unk_0e)
            {
                gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05 = 0;
            }
            sub_800D30C(0xf0, 0x02);
            sub_800D610();
        }
    }
    if (r8 == 0xFF)
    {
        sub_800D30C(0xf2, 0x00);
        sub_800D610();
    }
}

static void sub_800CEB0(u16 r6)
{
    u8 r7;
    u8 sp0;

    r7 = gUnknown_03004140.unk_0e;
    gUnknown_03004140.unk_0e = 0;
    gUnknown_03004140.unk_0f = 1;
    if (gUnknown_03007890->unk_00 == 0)
    {
        sub_800C36C(r6);
        if (gUnknown_03004140.unk_02 != 1)
        {
            sub_800D610();
            gUnknown_03004140.unk_0f = 0;
            gUnknown_03004140.unk_0e = r7;
            return;
        }
    }
    else
    {
        if (!rfu_UNI_PARENT_getDRAC_ACK(&sp0))
        {
            gUnknown_03004140.unk_03 |= sp0;
        }
    }
    if (gUnknown_03004140.unk_44 != NULL)
    {
        gUnknown_03004140.unk_44(r6);
        rfu_waitREQComplete();
        if (gUnknown_03004140.unk_02 == 2)
        {
            sub_800D610();
        }
    }
    gUnknown_03004140.unk_0f = 0;
    gUnknown_03004140.unk_0e = r7;
}

static void sub_800CF34(void)
{
    u8 flags;
    u8 sp0;
    u8 i;
    u8 r5;
    u8 r4;
    const u16 *ptr;

    if (gUnknown_03004140.unk_04 == 5 || gUnknown_03004140.unk_04 == 6 || gUnknown_03004140.unk_04 == 7 || gUnknown_03004140.unk_04 == 8)
    {
        flags = ((gUnknown_03007890->unk_02 ^ gUnknown_03004140.unk_0c) & gUnknown_03007890->unk_02) & ~gUnknown_03007890->unk_07;
        gUnknown_03004140.unk_0c = gUnknown_03007890->unk_02;
        if (flags)
        {
            gUnknown_03004140.unk_14 = flags;
            sub_800D30C(0x10, 0x01);
        }
        sp0 = 0x00;
        for (i = 0; i < 4; i++)
        {
            r4 = 1 << i;
            r5 = 0x00;
            if (flags & r4)
            {
                gUnknown_03004140.unk_28[i] = gUnknown_03004140.unk_26;
                gUnknown_03004140.unk_24 |= r4;
            }
            else if (gUnknown_03004140.unk_24 & r4)
            {
                if (gUnknown_03007880[i]->unk_34 == 0x46)
                {
                    if (gUnknown_03007880[i]->unk_61 == 1)
                    {
                        r5 = 0x02;
                        for (ptr = gUnknown_03004140.unk_20; *ptr != 0xFFFF; ptr++)
                        {
                            if (gUnknown_03007890->unk_14[i].unk_04 == *ptr)
                            {
                                gUnknown_03004140.unk_00 |= r4;
                                gUnknown_03004140.unk_01++;
                                sp0 |= r4;
                                r5 |= 0x01;
                                break;
                            }
                        }
                        if (!(r5 & 0x01))
                        {
                            r5 |= 0x04;
                        }
                    }
                }
                else if (--gUnknown_03004140.unk_28[i] == 0)
                {
                    r5 = 0x06;
                }
                if (r5 & 0x02)
                {
                    gUnknown_03004140.unk_24 &= ~r4;
                    gUnknown_03004140.unk_28[i] = 0;
                    rfu_clearSlot(0x08, i);
                }
                if (r5 & 0x04)
                {
                    gUnknown_03004140.unk_0d |= r4;
                }
            }
        }
        if (sp0)
        {
            gUnknown_03004140.unk_14 = sp0;
            sub_800D30C(0x11, 0x01);
        }
        if (gUnknown_03004140.unk_0d)
        {
            r5 = 0x01;
            if (gUnknown_03007890->unk_06 && ((gUnknown_03004140.unk_03 & gUnknown_03004140.unk_00) != gUnknown_03004140.unk_00))
            {
                r5 = 0x00;
            }
            if (r5)
            {
                sub_800D334(gUnknown_03004140.unk_0d);
                gUnknown_03004140.unk_14 = gUnknown_03004140.unk_0d;
                gUnknown_03004140.unk_0d = 0;
                sub_800D30C(0x12, 0x01);
            }
        }
        if (gUnknown_03004140.unk_24 == 0 && gUnknown_03004140.unk_04 == 8)
        {
            if (gUnknown_03004140.unk_07 == 0)
            {
                gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05 = 0;
                sub_800D30C(0x14, 0x00);
            }
            else
            {
                if (gUnknown_03004140.unk_07 == 2)
                {
                    gUnknown_03004140.unk_07 = 3;
                    gUnknown_03004140.unk_04 = 9;
                }
                else
                {
                    gUnknown_03004140.unk_07 = 1;
                    gUnknown_03004140.unk_04 = 5;
                }
                if (gUnknown_03004140.unk_00)
                {
                    gUnknown_03004140.unk_1a = 0;
                    gUnknown_03004140.unk_07 = 8;
                    gUnknown_03004140.unk_04 = 5;
                }
            }
        }
    }
}

static void sub_800D158(void)
{
    u16 imeBak = REG_IME;
    REG_IME = 0;
    if (gUnknown_03004140.unk_04 == 15)
    {
        if (--gUnknown_03004140.unk_28[gUnknown_03004140.unk_10] == 0 || gUnknown_03007880[gUnknown_03004140.unk_10]->unk_0 == 0x27)
        {
            sub_800D630();
            gUnknown_03004140.unk_04 = 24;
            rfu_clearSlot(4, gUnknown_03004140.unk_10);
            gUnknown_03004140.unk_24 &= ~(1 << gUnknown_03004140.unk_10);
            gUnknown_03004140.unk_28[gUnknown_03004140.unk_10] = 0;
        }
    }
    REG_IME = imeBak;
    if (gUnknown_03004140.unk_04 == 24)
    {
        if (gUnknown_03004140.unk_02 == 1)
        {
            sub_800D630();
        }
        if (gUnknown_03004140.unk_02 == 0)
        {
            gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05 = 0;
            sub_800D334(gUnknown_03007890->unk_02 | gUnknown_03007890->unk_03);
            gUnknown_03004140.unk_14 = 0;
            sub_800D30C(0x25, 0x01);
        }
    }
}

static void sub_800D20C(void)
{
    if (gUnknown_03004140.unk_04 == 15 && gUnknown_03007880[gUnknown_03004140.unk_10]->unk_0 == 0x26)
    {
        gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05 = 0;
        rfu_clearSlot(4, gUnknown_03004140.unk_10);
        gUnknown_03004140.unk_24 &= ~(1 << gUnknown_03004140.unk_10);
        gUnknown_03004140.unk_28[gUnknown_03004140.unk_10] = 0;
        sub_800D30C(0x24, 0x00);
    }
}

static void sub_800D268(void)
{
    if (gUnknown_03004140.unk_06 == 0 && gUnknown_03004140.unk_0a == 1)
    {
        gUnknown_03004140.unk_11 = gUnknown_03004140.unk_04;
        gUnknown_03004140.unk_12 = gUnknown_03004140.unk_05;
        gUnknown_03004140.unk_04 = 16;
        gUnknown_03004140.unk_05 = 17;
        gUnknown_03004140.unk_0a = 2;
    }
}

static u8 sub_800D294(void)
{
    u8 i;
    const u16 *ptr;
    u8 flags = 0x00;

    for (i = 0; i < gUnknown_03007890->unk_08; i++)
    {
        for (ptr = gUnknown_03004140.unk_20; *ptr != 0xffff; ptr++)
        {
            if (gUnknown_03007890->unk_14[i].unk_04 == *ptr)
            {
                flags |= (1 << i);
            }
        }
    }
    return flags;
}

static void sub_800D30C(u8 a0, u8 a1)
{
    if (gUnknown_03004140.unk_40 != NULL)
    {
        gUnknown_03004140.unk_40(a0, a1);
    }
    gUnknown_03004140.unk_14 = gUnknown_03004140.unk_16 = 0;
}

static void sub_800D334(u8 a0)
{
    u8 unk_0e_bak = gUnknown_03004140.unk_0e;
    gUnknown_03004140.unk_0e = 1;
    rfu_REQ_disconnect(a0);
    rfu_waitREQComplete();
    gUnknown_03004140.unk_0e = unk_0e_bak;
}

static void sub_800D358(u8 a0)
{
    u8 i;

    if (gUnknown_03007890->unk_04)
    {
        for (i = 0; i < 4; i++)
        {
            if (gUnknown_03007880[i]->unk_0 & 0x8000 && gUnknown_03007880[i]->unk_1a & a0)
            {
                rfu_changeSendTarget(0x20, i, gUnknown_03007880[i]->unk_1a & ~a0);
            }
        }
    }
    if (gUnknown_03007890->unk_05)
    {
        for (i = 0; i < 4; i++)
        {
            if (gUnknown_03007880[i]->unk_34 & 0x8000 && gUnknown_03007880[i]->unk_4e & a0)
            {
                rfu_NI_stopReceivingData(i);
            }
        }
    }
    if (gUnknown_03007890->unk_06)
    {
        gUnknown_03007890->unk_06 &= ~a0;
        for (i = 0; i < 4; i++)
        {
            if (gUnknown_03007870[i]->unk_0 == 0x8024 && a0 & gUnknown_03007870[i]->unk_3)
            {
                gUnknown_03007870[i]->unk_3 &= ~a0;
            }
        }
    }
}

static void sub_800D434(void)
{
    u8 i;
    u8 j;
    u8 flags;

    if (gUnknown_03004140.unk_18)
    {
        if (gUnknown_03007890->unk_04)
        {
            for (i = 0; i < 4; i ++)
            {
                if (gUnknown_03007880[i]->unk_0 & 0x8000)
                {
                    flags = 0;
                    for (j = 0; j < 4; j++)
                    {
                        if ((gUnknown_03007880[i]->unk_1a >> j) & 1 && gUnknown_03007880[j]->unk_2 > gUnknown_03004140.unk_18)
                        {
                            flags |= (1 << j);
                        }
                        if (flags)
                        {
                            rfu_changeSendTarget(0x20, i, flags ^ gUnknown_03007880[i]->unk_1a);
                        }
                    }
                }
            }
        }
        if (gUnknown_03007890->unk_05)
        {
            for (i = 0; i < 4; i++)
            {
                if (gUnknown_03007880[i]->unk_34 & 0x8000 && gUnknown_03007880[i]->unk_36 > gUnknown_03004140.unk_18)
                {
                    rfu_NI_stopReceivingData(i);
                }
            }
        }
    }
}

void sub_800D52C(void (*func)(u16))
{
    gUnknown_03004140.unk_44 = func;
    rfu_setMSCCallback(sub_800CEB0);
}

void sub_800D544(void (*func)(u8, u8))
{
    gUnknown_03004140.unk_40 = func;
}

u8 sub_800D550(u8 a0, u16 a1)
{
    u16 imeBak;
    if (gUnknown_03004140.unk_09 && a0 == 0 && gUnknown_03004140.unk_30)
    {
        return 5;
    }
    imeBak = REG_IME;
    REG_IME = 0;
    gUnknown_03004140.unk_09 = a0;
    gUnknown_03004140.unk_32 = a1;
    REG_IME = imeBak;
    return 0;
}

u8 sub_800D594(u16 a0)
{
    if (gUnknown_03007890->unk_04 | gUnknown_03007890->unk_05)
    {
        gUnknown_03004140.unk_14 = 6;
        sub_800D30C(0xf3, 0x01);
        return 6;
    }
    gUnknown_03004140.unk_18 = a0;
    return 0;
}

u8 sub_800D5D0(u8 a0)
{
    if (gUnknown_03004140.unk_04 == 9 || gUnknown_03004140.unk_04 == 10 || gUnknown_03004140.unk_04 == 11)
    {
        gUnknown_03004140.unk_14 = 7;
        sub_800D30C(0xf3, 0x01);
        return 7;
    }
    if (a0)
    {
        gUnknown_03004140.unk_0b = 1;
    }
    else
    {
        gUnknown_03004140.unk_0b = 0;
    }
    return 0;
}

static void sub_800D610(void)
{
    if (gUnknown_03004140.unk_02)
    {
        gUnknown_03004140.unk_02 = 0;
        sub_800D30C(0x45, 0x00);
    }
}

void sub_800D630(void)
{
    if (gUnknown_03004140.unk_02 == 0)
    {
        sub_800D30C(0x45, 0x00);
    }
    else if (gUnknown_03004140.unk_02 == 1)
    {
        gUnknown_03004140.unk_02 = 2;
    }
}

void sub_800D658(void)
{
    if (gUnknown_03004140.unk_07)
    {
        switch (gUnknown_03004140.unk_04)
        {
            case 5:
                gUnknown_03004140.unk_07 = 3;
                gUnknown_03004140.unk_04 = 9;
                break;
            case 6:
                gUnknown_03004140.unk_07 = 2;
                gUnknown_03004140.unk_1a = 1;
                break;
            case 7:
            case 8:
                gUnknown_03004140.unk_07 = 2;
                break;
            case 9:
            case 10:
                gUnknown_03004140.unk_1a = 40;
                break;
            case 11:
                gUnknown_03004140.unk_1a = 40;
                gUnknown_03004140.unk_04 = 10;
                break;
        }
    }
}

// TODO: Is there a file boundary here?

void sub_800D6C8(struct UnkRfuStruct_2_Sub_124 *ptr)
{
    int i;
    int j;

    for (i = 0; i < 32; i++)
    {
        for (j = 0; j < 70; j++)
        {
            ptr->unk_00[i][j] = 0;
        }
    }
    ptr->unk_8c1 = 0;
    ptr->unk_8c0 = 0;
    ptr->unk_8c2 = 0;
    ptr->unk_8c3 = 0;
}

void sub_800D724(struct UnkRfuStruct_2_Sub_9e8 *ptr)
{
    int i;
    int j;

    for (i = 0; i < 40; i++)
    {
        for (j = 0; j < 14; j++)
        {
            ptr->unk_00[i][j] = 0;
        }
    }
    ptr->unk_231 = 0;
    ptr->unk_230 = 0;
    ptr->unk_232 = 0;
    ptr->unk_233 = 0;
}

void sub_800D780(struct UnkRfuStruct_Sub_Unused *ptr)
{
    int i;
    int j;

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 256; j++)
        {
            ptr->unk_00[i][j] = 0;
        }
    }
    ptr->unk_201 = 0;
    ptr->unk_200 = 0;
    ptr->unk_202 = 0;
    ptr->unk_203 = 0;
}

void sub_800D7D8(struct UnkRfuStruct_2_Sub_124 *q1, u8 *q2)
{
    int i;
    u16 imeBak;
    u8 count;

    if (q1->unk_8c2 < 32)
    {
        imeBak = REG_IME;
        REG_IME = 0;
        count = 0;
        for (i = 0; i < 70; i += 14)
        {
            if (q2[i] == 0 && q2[i + 1] == 0)
            {
                count++;
            }
        }
        if (count != 5)
        {
            for (i = 0; i < 70; i++)
            {
                q1->unk_00[q1->unk_8c0][i] = q2[i];
            }
            q1->unk_8c0++;
            q1->unk_8c0 %= 32;
            q1->unk_8c2++;
            for (i = 0; i < 70; i++)
            {
                q2[i] = 0;
            }
        }
        REG_IME = imeBak;
    }
    else
    {
        q1->unk_8c3 = 1;
    }
}

void sub_800D888(struct UnkRfuStruct_2_Sub_9e8 *q1, u8 *q2)
{
    int i;
    u16 imeBak;

    if (q1->unk_232 < 40)
    {
        imeBak = REG_IME;
        REG_IME = 0;
        for (i = 0; i < 14; i++)
        {
            if (q2[i] != 0)
            {
                break;
            }
        }
        if (i != 14)
        {
            for (i = 0; i < 14; i++)
            {
                q1->unk_00[q1->unk_230][i] = q2[i];
            }
            q1->unk_230++;
            q1->unk_230 %= 40;
            q1->unk_232++;
            for (i = 0; i < 14; i++)
            {
                q2[i] = 0;
            }
        }
        REG_IME = imeBak;
    }
    else
    {
        q1->unk_233 = 1;
    }
}

bool8 sub_800D934(struct UnkRfuStruct_2_Sub_124 *q1, u8 *q2)
{
    u16 imeBak;
    int i;

    imeBak = REG_IME;
    REG_IME = 0;
    if (q1->unk_8c0 == q1->unk_8c1 || q1->unk_8c3 != 0)
    {
        for (i = 0; i < 70; i++)
        {
            q2[i] = 0;
        }
        REG_IME = imeBak;
        return FALSE;
    }
    for (i = 0; i < 70; i++)
    {
        q2[i] = q1->unk_00[q1->unk_8c1][i];
    }
    q1->unk_8c1++;
    q1->unk_8c1 %= 32;
    q1->unk_8c2--;
    REG_IME = imeBak;
    return TRUE;
}

bool8 sub_800D9DC(struct UnkRfuStruct_2_Sub_9e8 *q1, u8 *q2)
{
    int i;
    u16 imeBak;

    if (q1->unk_230 == q1->unk_231 || q1->unk_233 != 0)
    {
        return FALSE;
    }
    imeBak = REG_IME;
    REG_IME = 0;
    for (i = 0; i < 14; i++)
    {
        q2[i] = q1->unk_00[q1->unk_231][i];
    }
    q1->unk_231++;
    q1->unk_231 %= 40;
    q1->unk_232--;
    REG_IME = imeBak;
    return TRUE;
}

void sub_800DA68(struct UnkRfuStruct_2_Sub_c1c *q1, const u8 *q2)
{
    int i;

    if (q2[1] == 0)
    {
        sub_800DAC8(q1, NULL);
    }
    else
    {
        for (i = 0; i < 14; i++)
        {
            q1->unk_00[q1->unk_1c][i] = q2[i];
        }
        q1->unk_1c++;
        q1->unk_1c %= 2;
        if (q1->unk_1e < 2)
        {
            q1->unk_1e++;
        }
        else
        {
            q1->unk_1d = q1->unk_1c;
        }
    }
}

static bool8 sub_800DAC8(struct UnkRfuStruct_2_Sub_c1c *q1, u8 *q2)
{
    int i;

    if (q1->unk_1e == 0)
    {
        return FALSE;
    }
    if (q2 != NULL)
    {
        for (i = 0; i < 14; i++)
        {
            q2[i] = q1->unk_00[q1->unk_1d][i];
        }
    }
    q1->unk_1d++;
    q1->unk_1d %= 2;
    q1->unk_1e--;
    return TRUE;
}

void sub_800DB18(struct UnkRfuStruct_Sub_Unused *q1, u8 *q2)
{
    int i;

    if (q1->unk_202 < 2)
    {
        for (i = 0; i < 256; i++)
        {
            q1->unk_00[q1->unk_200][i] = q2[i];
        }
        q1->unk_200++;
        q1->unk_200 %= 2;
        q1->unk_202++;
    }
    else
    {
        q1->unk_203 = 1;
    }
}

bool8 sub_800DB84(struct UnkRfuStruct_Sub_Unused *q1, u8 *q2)
{
    int i;

    if (q1->unk_200 == q1->unk_201 || q1->unk_203)
    {
        return FALSE;
    }
    for (i = 0; i < 256; i++)
    {
        q2[i] = q1->unk_00[q1->unk_201][i];
    }
    q1->unk_201++;
    q1->unk_201 %= 2;
    q1->unk_202--;
    return TRUE;
}

void sub_800DBF8(u8 *q1, u8 mode)
{
    int i;
    u8 rval;
    u16 r5 = 0;
    switch (mode)
    {
        case 0:
            for (i = 0; i < 200; i++)
            {
                q1[i] = i + 1;
                r5 += i + 1;
            }
            *((u16 *)(q1 + i)) = r5;
            break;
        case 1:
            for (i = 0; i < 100; i++)
            {
                q1[i] = i + 1;
                r5 += i + 1;
            }
            *((u16 *)(q1 + 200)) = r5;
            break;
        case 2:
            for (i = 0; i < 200; i++)
            {
                rval = Random();
                q1[i] = rval;
                r5 += rval;
            }
            *((u16 *)(q1 + i)) = r5;
            break;
        case 3:
            for (i = 0; i < 200; i++)
            {
                q1[i] = i + 1 + gUnknown_03000D74;
                r5 += (i + 1 + gUnknown_03000D74) & 0xFF;
            }
            *((u16 *)(q1 + i)) = r5;
            gUnknown_03000D74++;
            break;
    }
}

void PkmnStrToASCII(u8 *q1, const u8 *q2)
{
    int i;

    for (i = 0; q2[i] != EOS; i++)
    {
        q1[i] = sWireless_RSEtoASCIITable[q2[i]];
    }
    q1[i] = 0;
}

void ASCIIToPkmnStr(u8 *q1, const u8 *q2)
{
    int i;

    for (i = 0; q2[i] != 0; i++)
    {
        q1[i] = sWireless_ASCIItoRSETable[q2[i]];
    }
    q1[i] = EOS;
}

#ifdef NONMATCHING
u8 sub_800DD1C(u8 maxFlags)
{
    u8 flagCount = 0;
    u8 flags = gUnknown_03007890->unk_02;
    u8 i;

    if (gUnknown_03007890->unk_00 == 1)
    {
        i = 0;
        for (i = 0; i < 4; flags >>= 1, i++)
        {
            if (flags & 1)
            {
                if (maxFlags == flagCount + 1)
                {
                    return gUnknown_03007890->unk_0a[i];
                }
                flagCount++;
            }
        }
    }
    else
    {
        for (i = 0; i < 4; flags >>= 1, i++)
        {
            if (flags & 1)
            {
                return gUnknown_03007890->unk_0a[i];
            }
        }
    }
    return 0;
}
#else
NAKED u8 sub_800DD1C(u8 maxFlags)
{
    asm_unified("\tpush {r4-r7,lr}\n"
                    "\tlsls r0, 24\n"
                    "\tlsrs r5, r0, 24\n"
                    "\tmovs r6, 0\n"
                    "\tldr r0, =gUnknown_03007890\n"
                    "\tldr r4, [r0]\n"
                    "\tldrb r2, [r4, 0x2]\n"
                    "\tldrb r1, [r4]\n"
                    "\tadds r7, r0, 0\n"
                    "\tcmp r1, 0x1\n"
                    "\tbne _0800DD72\n"
                    "\tmovs r3, 0\n"
                    "\tands r1, r2\n"
                    "\tcmp r1, 0\n"
                    "\tbeq _0800DD4E\n"
                    "\tcmp r5, 0x1\n"
                    "\tbne _0800DD48\n"
                    "\tldrb r0, [r4, 0xA]\n"
                    "\tb _0800DD8C\n"
                    "\t.pool\n"
                    "_0800DD48:\n"
                    "\tadds r0, r6, 0x1\n"
                    "\tlsls r0, 24\n"
                    "\tlsrs r6, r0, 24\n"
                    "_0800DD4E:\n"
                    "\tlsrs r2, 1\n"
                    "\tadds r0, r3, 0x1\n"
                    "\tlsls r0, 24\n"
                    "\tlsrs r3, r0, 24\n"
                    "\tcmp r3, 0x3\n"
                    "\tbhi _0800DD8A\n"
                    "\tmovs r0, 0x1\n"
                    "\tands r0, r2\n"
                    "\tcmp r0, 0\n"
                    "\tbeq _0800DD4E\n"
                    "\tadds r0, r6, 0x1\n"
                    "\tcmp r5, r0\n"
                    "\tbne _0800DD48\n"
                    "_0800DD68:\n"
                    "\tldr r0, [r7]\n"
                    "\tadds r0, 0xA\n"
                    "\tadds r0, r3\n"
                    "\tldrb r0, [r0]\n"
                    "\tb _0800DD8C\n"
                    "_0800DD72:\n"
                    "\tmovs r3, 0\n"
                    "\tmovs r1, 0x1\n"
                    "_0800DD76:\n"
                    "\tadds r0, r2, 0\n"
                    "\tands r0, r1\n"
                    "\tcmp r0, 0\n"
                    "\tbne _0800DD68\n"
                    "\tlsrs r2, 1\n"
                    "\tadds r0, r3, 0x1\n"
                    "\tlsls r0, 24\n"
                    "\tlsrs r3, r0, 24\n"
                    "\tcmp r3, 0x3\n"
                    "\tbls _0800DD76\n"
                    "_0800DD8A:\n"
                    "\tmovs r0, 0\n"
                    "_0800DD8C:\n"
                    "\tpop {r4-r7}\n"
                    "\tpop {r1}\n"
                    "\tbx r1");
}
#endif

void sub_800DD94(struct UnkLinkRfuStruct_02022B14 *data, u8 r9, bool32 r2, int r3)
{
    int i;

    for (i = 0; i < 2; i++)
    {
        data->unk_00.playerTrainerId[i] = gSaveBlock2Ptr->playerTrainerId[i];
    }
    for (i = 0; i < 4; i++)
    {
        data->unk_04[i] = r3;
        r3 >>= 8;
    }
    data->playerGender = gSaveBlock2Ptr->playerGender;
    data->unk_0a_0 = r9;
    data->unk_0a_7 = r2;
    data->unk_00.unk_00_0 = 2;
    data->unk_00.unk_01_2 = 3;
    data->unk_00.unk_00_4 = 0;
    data->unk_00.unk_00_5 = 0;
    data->unk_00.unk_00_6 = 0;
    data->unk_00.unk_00_7 = FlagGet(FLAG_0x87F);
    data->unk_00.unk_01_0 = IsNationalPokedexEnabled();
    data->unk_00.unk_01_1 = FlagGet(FLAG_SYS_GAME_CLEAR);
}

bool8 sub_800DE7C(struct UnkLinkRfuStruct_02022B14 *buff1, u8 *buff2, u8 idx)
{
    bool8 retVal;

    if (gUnknown_03004140.unk_06 == 1)
    {
        retVal = TRUE;
        if (sub_8010454(gUnknown_03007890->unk_14[idx].unk_04) && ((gUnknown_03007890->unk_07 >> idx) & 1))
        {
            memcpy(buff1, &gUnknown_03007890->unk_14[idx].unk_06, 0xD);
            memcpy(buff2, gUnknown_03007890->unk_14[idx].unk_15, sizeof(gUnknown_03007890->unk_14[idx].unk_15));
        }
        else
        {
            memset(buff1, 0, 0xD);
            memset(buff2, 0, sizeof(gUnknown_03007890->unk_14[idx].unk_15));
        }
    }
    else
    {
        retVal = FALSE;
        if (sub_8010454(gUnknown_03007890->unk_14[idx].unk_04))
        {
            memcpy(buff1, &gUnknown_03007890->unk_14[idx].unk_06, 0xD);
            memcpy(buff2, gUnknown_03007890->unk_14[idx].unk_15, sizeof(gUnknown_03007890->unk_14[idx].unk_15));
        }
        else
        {
            memset(buff1, 0, 0xD);
            memset(buff2, 0, sizeof(gUnknown_03007890->unk_14[idx].unk_15));
        }
    }
    return retVal;
}

bool8 sub_800DF34(struct UnkLinkRfuStruct_02022B14 *buff1, u8 *buff2, u8 idx)
{
    bool8 retVal = FALSE;
    if (gUnknown_03007890->unk_14[idx].unk_04 == 0x7F7D)
    {
        *buff1 = gUnknown_03007890->unk_14[idx].unk_06;
        memcpy(buff2, gUnknown_03007890->unk_14[idx].unk_15, 8);
        retVal = TRUE;
    }
    else
    {
        *buff1 = (struct UnkLinkRfuStruct_02022B14){};
        memset(buff2, 0, 8);
    }
    return retVal;
}

void sub_800DF90(struct UnkLinkRfuStruct_02022B14 *buff1, u8 *buff2)
{
    *buff1 = gUnknown_02022B14;
    memcpy(buff2, gUnknown_02022B22, 8);
}

void CreateWirelessStatusIndicatorSprite(u8 x, u8 y)
{
    u8 sprId;

    if (x == 0 && y == 0)
    {
        x = 0xE7;
        y = 0x08;
    }
    if (gUnknown_03007890->unk_00 == 1)
    {
        sprId = CreateSprite(&sWirelessStatusIndicatorSpriteTemplate, x, y, 0);
        gSprites[sprId].data[7] = 0x1234;
        gSprites[sprId].data[6] = GetSpriteTileStartByTag(sWirelessStatusIndicatorSpriteSheet.tag);
        gSprites[sprId].invisible = TRUE;
        gWirelessStatusIndicatorSpriteId = sprId;
    }
    else
    {
        gWirelessStatusIndicatorSpriteId = CreateSprite(&sWirelessStatusIndicatorSpriteTemplate, x, y, 0);
        gSprites[gWirelessStatusIndicatorSpriteId].data[7] = 0x1234;
        gSprites[gWirelessStatusIndicatorSpriteId].data[6] = GetSpriteTileStartByTag(sWirelessStatusIndicatorSpriteSheet.tag);
        gSprites[gWirelessStatusIndicatorSpriteId].invisible = TRUE;
    }
}

void sub_800E084(void)
{
    if (gSprites[gWirelessStatusIndicatorSpriteId].data[7] == 0x1234)
    {
        gSprites[gWirelessStatusIndicatorSpriteId].data[7] = 0;
        DestroySprite(&gSprites[gWirelessStatusIndicatorSpriteId]);
        gMain.oamBuffer[125] = gDummyOamData;
        CpuCopy16(&gDummyOamData, (struct OamData *)OAM + 125, sizeof(struct OamData));
    }
}

void sub_800E0E8(void)
{
    if (GetSpriteTileStartByTag(sWirelessStatusIndicatorSpriteSheet.tag) == 0xFFFF)
    {
        LoadCompressedObjectPic(&sWirelessStatusIndicatorSpriteSheet);
    }
    LoadSpritePalette(&sWirelessStatusIndicatorSpritePalette);
    gWirelessStatusIndicatorSpriteId = 0xFF;
}

u8 sub_800E124(void)
{
    u8 i;
    u8 flags = gUnknown_03007890->unk_02;
    for (i = 0; i < 4; i++)
    {
        if (flags & 1)
        {
            return gUnknown_03007890->unk_0a[i];
        }
        flags >>= 1;
    }
    return 0;
}

void sub_800E15C(struct Sprite *sprite, int signalStrengthAnimNum)
{
    if (sprite->data[2] != signalStrengthAnimNum)
    {
        sprite->data[2] = signalStrengthAnimNum;
        sprite->data[3] = 0;
        sprite->data[4] = 0;
    }
}

void sub_800E174(void)
{
    if (gWirelessStatusIndicatorSpriteId != 0xFF && gSprites[gWirelessStatusIndicatorSpriteId].data[7] == 0x1234)
    {
        struct Sprite *sprite = &gSprites[gWirelessStatusIndicatorSpriteId];
        u8 signalStrength = 255;
        u8 i = 0;
        if (gUnknown_03007890->unk_00 == 1)
        {
            for (i = 0; i < GetLinkPlayerCount() - 1; i++)
            {
                if (signalStrength >= sub_800DD1C(i + 1))
                {
                    signalStrength = sub_800DD1C(i + 1);
                }
            }
        }
        else
        {
            signalStrength = sub_800E124();
        }
        if (sub_8012224() == TRUE)
        {
            sprite->data[0] = 4;
        }
        else if (signalStrength < 25)
        {
            sprite->data[0] = 3;
        }
        else if (signalStrength >= 25 && signalStrength < 127)
        {
            sprite->data[0] = 2;
        }
        else if (signalStrength >= 127 && signalStrength < 229)
        {
            sprite->data[0] = 1;
        }
        else if (signalStrength >= 229)
        {
            sprite->data[0] = 0;
        }
        if (sprite->data[0] != sprite->data[1])
        {
            sub_800E15C(sprite, sprite->data[0]);
            sprite->data[1] = sprite->data[0];
        }
        if (sprite->anims[sprite->data[2]][sprite->data[4]].frame.duration < sprite->data[3])
        {
            sprite->data[4]++;
            sprite->data[3] = 0;
            if (sprite->anims[sprite->data[2]][sprite->data[4]].type == -2)
            {
                sprite->data[4] = 0;
            }
        }
        else
        {
            sprite->data[3]++;
        }
        gMain.oamBuffer[125] = sWirelessStatusIndicatorOamData;
        gMain.oamBuffer[125].x = sprite->pos1.x + sprite->centerToCornerVecX;
        gMain.oamBuffer[125].y = sprite->pos1.y + sprite->centerToCornerVecY;
        gMain.oamBuffer[125].paletteNum = sprite->oam.paletteNum;
        gMain.oamBuffer[125].tileNum = sprite->data[6] + sprite->anims[sprite->data[2]][sprite->data[4]].frame.imageValue;
        CpuCopy16(gMain.oamBuffer + 125, (struct OamData *)OAM + 125, sizeof(struct OamData));
        if (sub_8011A74() == 1)
        {
            sub_800E084();
        }
    }
}

void sub_800E378(struct UnkSaveSubstruct_3b98 *dest, u32 trainerId, const u8 *name)
{
    dest->trainerId = trainerId;
    StringCopy(dest->trainerName, name);
}

bool32 sub_800E388(const u8 *name)
{
    int i;

    for (i = 0; i < 8; i++)
    {
        if (name[i] != 0)
        {
            return TRUE;
        }
    }
    return FALSE;
}

void sub_800E3A8(void)
{
    if (gWirelessCommType != 0)
    {
        int i;
        int j;
        int cnt;
        int sp0[5];
        struct UnkSaveSubstruct_3b98 *sp14 = calloc(20, sizeof(struct UnkSaveSubstruct_3b98));
        for (i = 0; i < GetLinkPlayerCount(); i++)
        {
            sp0[i] = -1;
            for (j = 0; j < 20; j++)
            {
                if ((u16)gLinkPlayers[i].trainerId ==  gSaveBlock1Ptr->unk_3B98[j].trainerId && StringCompare(gLinkPlayers[i].name, gSaveBlock1Ptr->unk_3B98[j].trainerName) == 0)
                {
                    sp0[i] = j;
                }
            }
        }
        cnt = 0;
        for (i = 0; i < GetLinkPlayerCount(); i++)
        {
            if (i != GetMultiplayerId() && gLinkPlayers[i].language != LANGUAGE_JAPANESE)
            {
                sub_800E378(&sp14[cnt], (u16)gLinkPlayers[i].trainerId, gLinkPlayers[i].name);
                if (sp0[i] >= 0)
                {
                    memset(gSaveBlock1Ptr->unk_3B98[sp0[i]].trainerName, 0, 8);
                }
                cnt++;
            }
        }
        for (i = 0; i < 20; i++)
        {
            if (sub_800E388(gSaveBlock1Ptr->unk_3B98[i].trainerName))
            {
                sub_800E378(&sp14[cnt], gSaveBlock1Ptr->unk_3B98[i].trainerId, gSaveBlock1Ptr->unk_3B98[i].trainerName);
                if (++cnt >= 20)
                {
                    break;
                }
            }
        }
        memcpy(gSaveBlock1Ptr->unk_3B98, sp14, 20 * sizeof(struct UnkSaveSubstruct_3b98));
        free(sp14);
    }
}

bool32 sub_800E540(u16 id, u8 *name)
{
    int i;

    for (i = 0; i < 20; i++)
    {
        if (StringCompare(gSaveBlock1Ptr->unk_3B98[i].trainerName, name) == 0 && gSaveBlock1Ptr->unk_3B98[i].trainerId == id)
        {
            return TRUE;
        }
        if (!sub_800E388(gSaveBlock1Ptr->unk_3B98[i].trainerName))
        {
            return FALSE;
        }
    }
    return FALSE;
}

void sub_800E5AC(void)
{
    int i;

    for (i = 0; i < 20; i++)
    {
        gSaveBlock1Ptr->unk_3B98[i].trainerId = 0;
        CpuFill16(0, gSaveBlock1Ptr->unk_3B98[i].trainerName, 8);
    }
}

void nullsub_5(void *unused_0, u8 unused_1, u8 unused_2)
{
    // debug?
}

void nullsub_13(u8 unused_0, u8 unused_1, u8 unused_2, u8 unused_3)
{

}

void sub_800E604(void)
{
    int i;
    u8 unk_ee_bak = gUnknown_03005000.unk_ee;
    CpuFill16(0, &gUnknown_03005000, sizeof gUnknown_03005000);
    gUnknown_03005000.unk_ee = unk_ee_bak;
    gUnknown_03005000.unk_0c = 0xFF;
    if (gUnknown_03005000.unk_ee != 4)
    {
        gUnknown_03005000.unk_ee = 0;
    }
    for (i = 0; i < 5; i++)
    {
        sub_800FCC4(gUnknown_03005000.unk_80 + i);
    }
    sub_800FCC4(&gUnknown_03005000.unk_6c);
    sub_800D6C8(&gUnknown_03005000.unk_124);
    sub_800D724(&gUnknown_03005000.unk_9e8);
    CpuFill16(0, gSendCmd, sizeof gSendCmd);
    CpuFill16(0, gRecvCmds, sizeof gRecvCmds);
    CpuFill16(0, gLinkPlayers, sizeof gLinkPlayers)
}

void sub_800E6D0(void)
{
    IntrFunc serialIntr = gIntrTable[1];
    IntrFunc timerIntr = gIntrTable[2];
    sub_800E700();
    rfu_REQ_stopMode();
    rfu_waitREQComplete();
    REG_IME = 0;
    gIntrTable[1] = serialIntr;
    gIntrTable[2] = timerIntr;
    REG_IME = INTR_FLAG_VBLANK;
}

void sub_800E700(void)
{
    if (!rfu_initializeAPI(gUnknown_03004140.unk_50, sizeof gUnknown_03004140.unk_50, gIntrTable + 1, TRUE))
    {
        gLinkType = 0;
        sub_800AAF4();
        sub_80111B0(0);
        sub_800E604();
        rfu_setTimerInterrupt(3, gIntrTable + 2);
    }
}

void sub_800E748(u8 taskId)
{
    sub_8010750();
    switch (gUnknown_03005000.unk_04)
    {
        case 0:
            sub_800BFCC(&gUnknown_02022B2C);
            gUnknown_03005000.unk_04 = 1;
            gTasks[taskId].data[1] = 1;
            break;
        case 1:
            break;
        case 2:
            sub_800C054(gUnknown_03005000.unk_0c, 0, 240, gUnknown_082ED6E0);
            gUnknown_03005000.unk_04 = 3;
            gTasks[taskId].data[1] = 6;
            break;
        case 3:
            break;
        case 4:
            sub_800C27C(FALSE);
            gUnknown_03005000.unk_04 = 5;
            break;
        case 5:
            break;
        case 18:
            gUnknown_03005000.unk_cdb = 0;
            sub_800D52C(sub_800EDBC);
            sub_800EAB4();
            sub_800EAFC();
            gUnknown_03005000.unk_04 = 20;
            gTasks[taskId].data[1] = 8;
            CreateTask(sub_801084C, 5);
            DestroyTask(taskId);
            break;
    }
}

u8 sub_800E87C(u8 idx)
{
    return gUnknown_082ED6A5[idx];
}

void sub_800E88C(int r2, int r5)
{
    u8 i;
    u8 r4 = 1;
    int r1 = r2;
    int r6 = 0;
    if (r5 == -1)
    {
        for (i = 0; i < 4; r2 >>= 1, i++)
        {
            if (r2 & 1)
            {
                gUnknown_03005000.unk_cde[i] = r4;
                r4++;
            }
        }
    }
    else
    {
        for (i = 0; i < 4; r1 >>= 1, i++)
        {
            if (!(r1 & 1))
            {
                gUnknown_03005000.unk_cde[i] = 0;
            }
        }
        for (r4 = 4; r4 != 0; r4--)
        {
            for (i = 0; i < 4 && gUnknown_03005000.unk_cde[i] != r4; i++);
            if (i == 4)
            {
                r6 = r4;
            }
        }
        for (r5 &= ~r2, i = 0; i < 4; r5 >>= 1, i++)
        {
            if (r5 & 1)
            {
                gUnknown_03005000.unk_cde[i] = r6++;
            }
        }
    }
}

void sub_800E94C(u8 taskId)
{
    switch (gUnknown_03005000.unk_04)
    {
        case 0:
            sub_800BFCC(&gUnknown_082ED608);
            gUnknown_03005000.unk_04 = 1;
            gTasks[taskId].data[1] = 1;
            break;
        case 1:
            break;
        case 6:
            sub_800C054(gUnknown_03005000.unk_0c, 0, 0xf0, gUnknown_082ED6E0);
            gUnknown_03005000.unk_04 = 7;
            gTasks[taskId].data[1] = 7;
            break;
        case 7:
            break;
        case 9:
            gTasks[taskId].data[1] = 10;
            break;
        case 11:
            switch (sub_80107A0())
            {
                case 5:
                    gUnknown_03005000.unk_04 = 12;
                    break;
                case 6:
                case 9:
                    sub_800D630();
                    gUnknown_03005000.unk_ce4 = 2;
                    DestroyTask(taskId);
                    break;
            }
            break;
        case 12:
        {
            u8 r5 = 1 << gUnknown_03005000.unk_c3e;
            rfu_clearSlot(12, gUnknown_03005000.unk_c3e);
            rfu_setRecvBuffer(16, gUnknown_03005000.unk_c3e, gUnknown_03005000.unk_c3f, 70);
            rfu_UNI_setSendData(r5, gUnknown_03005000.unk_4c, 14);
            gTasks[taskId].data[1] = 8;
            DestroyTask(taskId);
            if (gUnknown_02022B44.unk_0f == 0)
            {
                sub_801227C();
                gUnknown_02022B44.unk_0f++;
            }
            CreateTask(sub_801084C, 5);
            break;
        }
    }
}

static void sub_800EAB4(void)
{
    u8 i;
    u8 r5 = gUnknown_03004140.unk_00;
    for (i = 0; i < 4; i++)
    {
        if (r5 & 1)
        {
            rfu_setRecvBuffer(16, i, gUnknown_03005000.unk_14[i], 14);
            rfu_clearSlot(3, i);
        }
        r5 >>= 1;
    }
}

static void sub_800EAFC(void)
{
    u8 r5 = gUnknown_03004140.unk_00;
    rfu_UNI_setSendData(r5, gUnknown_03005000.unk_c87, 70);
    gUnknown_03005000.unk_cda = sub_800E87C(r5);
    gUnknown_03005000.unk_ce2 = r5;
    sub_800E88C(r5, -1);
    gUnknown_03005000.unk_0c = 1;
}

void sub_800EB44(u8 taskId)
{
    if (sub_800F7DC()->unk_0a_0 == 0x54 && sub_8011A74() == 4)
    {
        rfu_REQ_disconnect(gUnknown_03004140.unk_00);
        rfu_waitREQComplete();
        sub_8011A64(0, 0);
    }
    switch (gUnknown_03005000.unk_04)
    {
        case 0:
            sub_800BFCC(&gUnknown_02022B2C);
            gUnknown_03005000.unk_04 = 1;
            gTasks[taskId].data[1] = 1;
            break;
        case 1:
            break;
        case 17:
            sub_800C054(2, 0, 240, gUnknown_082ED6E0);
            sub_800D52C(sub_800ED34);
            gUnknown_03005000.unk_04 = 18;
            break;
        case 18:
            break;
        case 13:
            if (rfu_UNI_setSendData(1 << gUnknown_03005000.unk_c3e, gUnknown_03005000.unk_4c, 14) == 0)
            {
                gUnknown_03005000.unk_0c = 0;
                DestroyTask(taskId);
                if (gTasks[taskId].data[7])
                {
                    CreateTask(sub_8010D0C, 1);
                }
                else
                {
                    CreateTask(sub_801084C, 5);
                }
            }
            break;
        case 14:
            sub_800C27C(0);
            gUnknown_03005000.unk_04 = 15;
            break;
        case 15:
            break;
        case 16:
            gUnknown_03005000.unk_cdb = 0;
            sub_800D52C(sub_800EDBC);
            sub_8011068(1);
            sub_800EAB4();
            sub_800EAFC();
            gUnknown_03005000.unk_04 = 20;
            gTasks[taskId].data[1] = 8;
            gUnknown_03005000.unk_0c = 1;
            CreateTask(sub_801084C, 5);
            gUnknown_03005000.unk_ce8 = 1;
            DestroyTask(taskId);
            break;
    }
}

void sub_800ED10(void)
{
    sub_800C054(1, 0, 240, gUnknown_082ED6E0);
}

void sub_800ED28(void)
{
    sub_800C27C(FALSE);
}

void sub_800ED34(u16 unused)
{
    int i;

    for (i = 0; i < 14; i++)
    {
        gUnknown_03005000.unk_4c[i] = 0;
    }
    rfu_REQ_recvData();
    rfu_waitREQComplete();
    if (gUnknown_03007870[gUnknown_03005000.unk_c3e]->unk_12)
    {
        gUnknown_03005000.unk_cd0++;
        sub_800D7D8(&gUnknown_03005000.unk_124, gUnknown_03005000.unk_c3f);
        gUnknown_02022B44.unk_06++;
        sub_800F048();
        rfu_UNI_readySendData(gUnknown_03005000.unk_c3e);
        rfu_UNI_clearRecvNewDataFlag(gUnknown_03005000.unk_c3e);
    }
    rfu_REQ_sendData_wrapper(1);
}

static void sub_800EDBC(u16 unused)
{
    gUnknown_03005000.unk_cdb = 1;
}

void sub_800EDD4(void)
{
    u8 i;

    sub_800C048();
    if (gUnknown_03005000.unk_0c == 1)
    {
        if (FuncIsActiveTask(sub_800E748) == TRUE)
        {
            DestroyTask(gUnknown_03005000.unk_67);
            sub_800E604();
        }
    }
    else if (gUnknown_03005000.unk_0c == 0)
    {
        if (FuncIsActiveTask(sub_800E94C) == TRUE)
        {
            DestroyTask(gUnknown_03005000.unk_67);
            sub_800E604();
        }
    }
    else if (gUnknown_03005000.unk_0c == 2)
    {
        if (FuncIsActiveTask(sub_800EB44) == TRUE)
        {
            DestroyTask(gUnknown_03005000.unk_67);
            sub_800E604();
        }
    }
    for (i = 0; i < 3; i++)
    {
        if (FuncIsActiveTask(gUnknown_082ED7E0[i]) == TRUE)
        {
            DestroyTask(FindTaskIdByFunc(gUnknown_082ED7E0[i]));
        }
    }
}

void sub_800EE78(void)
{
    gUnknown_03005000.unk_67 = CreateTask(sub_800E748, 1);
}

bool8 sub_800EE94(void)
{
    if (gUnknown_03005000.unk_04 == 7 && gUnknown_03005000.unk_ccd)
    {
        return TRUE;
    }
    return FALSE;
}

bool8 sub_800EEBC(void)
{
    if (gUnknown_03005000.unk_04 == 7 && !sub_800C12C(gUnknown_03007890->unk_14[gUnknown_03005000.unk_c3d].unk_00, 240))
    {
        gUnknown_03005000.unk_04 = 9;
        return TRUE;
    }
    return FALSE;
}

void sub_800EF00(void)
{
    gUnknown_03005000.unk_67 = CreateTask(sub_800E94C, 1);
}

bool8 sub_800EF1C(void)
{
    if (gUnknown_03004140.unk_00)
    {
        return TRUE;
    }
    return FALSE;
}

void sub_800EF38(void)
{
    gUnknown_03005000.unk_04 = 4;
    gUnknown_03005000.unk_ce7 = gUnknown_03004140.unk_00;
}

bool32 sub_800EF58(bool32 a0)
{
    if (gUnknown_03005000.unk_04 == 17 || a0)
    {
        gUnknown_03005000.unk_04 = 18;
        return TRUE;
    }
    return FALSE;
}

void sub_800EF7C(void)
{
    gUnknown_03005000.unk_04 = 14;
}

void sub_800EF88(u8 a0)
{
    u8 i;

    for (i = 0; i < 4; i++)
    {
        if (a0 & 1)
        {
            rfu_UNI_readySendData(i);
            break;
        }
        a0 >>= 1;
    }
}

#ifdef NONMATCHING
// FIXME: gUnknown_03005000.unk_c87 should be in r5
// FIXME: gRecvCmds should be in r6 and r7
void sub_800EFB0(void)
{
    int i, j;
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 7; j++)
        {
            gUnknown_03005000.unk_c87[i][j][1] = gRecvCmds[i][j] >> 8;
            gUnknown_03005000.unk_c87[i][j][0] = gRecvCmds[i][j];
        }
    }
    CpuFill16(0, gRecvCmds, sizeof gRecvCmds);
}
#else
NAKED void sub_800EFB0(void)
{
    asm_unified("\tpush {r4-r7,lr}\n"
                    "\tsub sp, 0x4\n"
                    "\tmovs r2, 0\n"
                    "\tldr r7, =gRecvCmds\n"
                    "\tldr r0, =gUnknown_03005000\n"
                    "\tadds r6, r7, 0\n"
                    "\tldr r1, =0x00000c87\n"
                    "\tadds r5, r0, r1\n"
                    "_0800EFC0:\n"
                    "\tmovs r3, 0\n"
                    "\tlsls r0, r2, 3\n"
                    "\tlsls r1, r2, 4\n"
                    "\tadds r4, r2, 0x1\n"
                    "\tsubs r0, r2\n"
                    "\tlsls r0, 1\n"
                    "\tadds r2, r0, r5\n"
                    "\tadds r1, r6\n"
                    "_0800EFD0:\n"
                    "\tldrh r0, [r1]\n"
                    "\tlsrs r0, 8\n"
                    "\tstrb r0, [r2, 0x1]\n"
                    "\tldrh r0, [r1]\n"
                    "\tstrb r0, [r2]\n"
                    "\tadds r2, 0x2\n"
                    "\tadds r1, 0x2\n"
                    "\tadds r3, 0x1\n"
                    "\tcmp r3, 0x6\n"
                    "\tble _0800EFD0\n"
                    "\tadds r2, r4, 0\n"
                    "\tcmp r2, 0x4\n"
                    "\tble _0800EFC0\n"
                    "\tmovs r0, 0\n"
                    "\tmov r1, sp\n"
                    "\tstrh r0, [r1]\n"
                    "\tldr r2, =0x01000028\n"
                    "\tmov r0, sp\n"
                    "\tadds r1, r7, 0\n"
                    "\tbl CpuSet\n"
                    "\tadd sp, 0x4\n"
                    "\tpop {r4-r7}\n"
                    "\tpop {r0}\n"
                    "\tbx r0\n"
                    "\t.pool");
}
#endif

void sub_800F014(void)
{
    int i;
    for (i = 0; i < 7; i++)
    {
        gRecvCmds[0][i] = gSendCmd[i];
    }
    for (i = 0; i < 7; i++)
    {
        gSendCmd[i] = 0;
    }
}

static void sub_800F048(void)
{
    if (gUnknown_03005000.unk_c3c)
    {
        u8 r2 = sub_800DAC8(&gUnknown_03005000.unk_c1c, gUnknown_03005000.unk_4c);
        if (gUnknown_03005000.unk_c1c.unk_1e == 0)
        {
            gUnknown_03005000.unk_c3c = 0;
        }
        if (r2)
        {
            return;
        }
    }
    if (gUnknown_03005000.unk_c3c == 0)
    {
        sub_800D9DC(&gUnknown_03005000.unk_9e8, gUnknown_03005000.unk_4c);
        sub_800DA68(&gUnknown_03005000.unk_c1c, gUnknown_03005000.unk_4c);
    }
}

bool32 sub_800F0B8(void)
{
    int i;
    int j;

    if (gUnknown_03007890->unk_06 == 0)
    {
        return FALSE;
    }
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 7; j++)
        {
            if (gRecvCmds[i][j] != 0)
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

bool32 sub_800F0F8(void)
{
    if (gUnknown_03005000.unk_04 < 20)
    {
        rfu_REQ_recvData();
        rfu_waitREQComplete();
        rfu_REQ_sendData_wrapper(0);
    }
    else
    {
        gUnknown_03005000.unk_cdb = 0;
        if ((gUnknown_03005000.unk_ce2 & gUnknown_03007890->unk_02) == gUnknown_03005000.unk_ce2 && (gUnknown_03005000.unk_ce2 & gUnknown_03007890->unk_02))
        {
            if (!gUnknown_03005000.unk_cdc)
            {
                if (gUnknown_03005000.unk_ce3)
                {
                    sub_8011D6C(gUnknown_03005000.unk_ce3);
                    gUnknown_03005000.unk_ce3 = 0;
                    if (gUnknown_03005000.unk_ce4 == 1)
                    {
                        sub_8011A64(2, 0x8000);
                        sub_8011170(0x8000);
                        return FALSE;
                    }
                    if (!gUnknown_03004140.unk_00)
                    {
                        sub_800EDD4();
                        gReceivedRemoteLinkPlayers = 0;
                        return FALSE;
                    }
                }
                sub_800EFB0();
                rfu_UNI_readySendData(gUnknown_03005000.unk_cda);
                rfu_REQ_sendData_wrapper(1);
            }
            else
            {
                rfu_REQ_PARENT_resumeRetransmitAndChange();
            }
            gUnknown_03005000.unk_0e = 1;
        }
    }
    return FALSE;
}

bool32 sub_800F1E0(void)
{
    u16 i;
    u16 flags;
    u8 r0;
    u16 j;
    u8 retval;

    if (gUnknown_03005000.unk_04 >= 20 && gUnknown_03005000.unk_0e == 1)
    {
        rfu_waitREQComplete();
        while (gUnknown_03005000.unk_cdb == 0)
        {
            if (gUnknown_03005000.unk_ee != 0)
            {
                return FALSE;
            }
        }
        rfu_REQ_recvData();
        rfu_waitREQComplete();
        if ((gUnknown_03004140.unk_03 & gUnknown_03005000.unk_ce2) == gUnknown_03005000.unk_ce2)
        {
            gUnknown_03005000.unk_cdc = 0;
            gUnknown_02022B44.unk_06++;
            flags = gUnknown_03004140.unk_00;
            for (i = 0; i < 4; i++)
            {
                if (flags & 1)
                {
                    if (gUnknown_03005000.unk_14[i][1])
                    {
                        if (gUnknown_03005000.unk_cee[i] != 0xff && (gUnknown_03005000.unk_14[i][0] >> 5) != ((gUnknown_03005000.unk_cee[i] + 1) & 7))
                        {
                            if (++gUnknown_03005000.unk_cea[i] > 4)
                                sub_8011170(0x8100);
                        }
                        else
                        {
                            gUnknown_03005000.unk_cee[i] = gUnknown_03005000.unk_14[i][0] / 32;
                            gUnknown_03005000.unk_cea[i] = 0;
                            gUnknown_03005000.unk_14[i][0] &= 0x1f;
                            r0 = gUnknown_03005000.unk_cde[i];
                            for (j = 0; j < 7; j++)
                            {
                                gRecvCmds[r0][j] = (gUnknown_03005000.unk_14[i][(j << 1) + 1] << 8) | gUnknown_03005000.unk_14[i][(j << 1) + 0];
                                gUnknown_03005000.unk_14[i][(j << 1) + 1] = 0;
                                gUnknown_03005000.unk_14[i][(j << 1) + 0] = 0;
                            }
                        }
                    }
                    rfu_UNI_clearRecvNewDataFlag(i);
                }
                flags >>= 1;
            }
            sub_800F014();
            sub_800F86C(0);
            sub_8010528();
            if (gUnknown_03005000.unk_ce5 && !gUnknown_03005000.unk_cd9)
            {
                gUnknown_02022B44.unk_0e = 0;
                rfu_clearSlot(3, gUnknown_03005000.unk_cda);
                for (i = 0; i < 4; i++)
                {
                    if ((gUnknown_03005000.unk_ce5 >> i) & 1)
                    {
                        rfu_setRecvBuffer(0x10, i, gUnknown_03005000.unk_14[i], 14);
                    }
                }
                sub_800E88C(gUnknown_03005000.unk_ce2, gUnknown_03005000.unk_ce2 | gUnknown_03005000.unk_ce5);
                gUnknown_03005000.unk_ce9 = gUnknown_03005000.unk_ce5;
                gUnknown_03005000.unk_ce2 |= gUnknown_03005000.unk_ce5;
                gUnknown_03005000.unk_ce5 = 0;
                rfu_UNI_setSendData(gUnknown_03005000.unk_ce2, gUnknown_03005000.unk_c87, 70);
                gUnknown_03005000.unk_cda = sub_800E87C(gUnknown_03005000.unk_ce2);
                CreateTask(sub_8010AAC, 0);
            }
        }
        else
        {
            gUnknown_03005000.unk_cdc = 1;
            gUnknown_03005000.unk_0e = 0;
        }
        gUnknown_03005000.unk_0e = 0;
    }
    retval = gUnknown_03005000.unk_cdc;
    return gUnknown_03007890->unk_06 ? retval & 1 : FALSE;
}

void sub_800F498(u16 *a0, u8 *a1)
{
    int i;

    if (a0[0])
    {
        a0[0] |= (gUnknown_03005000.unk_102 << 5);
        gUnknown_03005000.unk_102 = (gUnknown_03005000.unk_102 + 1) & 7;
        for (i = 0; i < 7; i++)
        {
            a1[2 * i + 1] = a0[i] >> 8;
            a1[2 * i + 0] = a0[i];
        }
    }
    else
    {
        for (i = 0; i < 14; i++)
            a1[i] = 0;
    }
}

bool32 sub_800F4F0(void)
{
    u8 i;
    u8 j;
    u8 sp00[MAX_RFU_PLAYERS * (2 * (CMD_LENGTH - 1))];
    u8 sp48[2 * (CMD_LENGTH - 1)];
    u8 switchval;

    sub_800D934(&gUnknown_03005000.unk_124, sp00);
    for (i = 0; i < MAX_RFU_PLAYERS; i++)
    {
        for (j = 0; j < CMD_LENGTH - 1; j++)
        {
            gRecvCmds[i][j] = (sp00[i * 14 + (j << 1) + 1] << 8) | sp00[i * 14 + (j << 1) + 0];
        }
    }
    sub_800F86C(0);
    if (gUnknown_03004140.unk_02 == 0 && gUnknown_03005000.unk_ce4)
    {
        rfu_REQ_disconnect(gUnknown_03007890->unk_02 | gUnknown_03007890->unk_03);
        rfu_waitREQComplete();
        switchval = sub_8011A74();
        if (switchval != 1 && switchval != 6 && switchval != 9)
            sub_8011A64(2, 0x9000);
        rfu_clearAllSlot();
        gReceivedRemoteLinkPlayers = FALSE;
        gUnknown_03005000.unk_00 = 0;
        if (gUnknown_03005000.unk_ce4 == 1)
        {
            sub_8011A64(2, 0x9000);
            sub_8011170(0x9000);
        }
        gUnknown_03004140.unk_04 = gUnknown_03004140.unk_05 = 0;
        gUnknown_03005000.unk_ce4 = 0;
    }
    if (gUnknown_03005000.unk_cd0)
    {
        gUnknown_03005000.unk_cd0--;
        sub_8010528();
        sub_800F498(gSendCmd, sp48);
        sub_800D888(&gUnknown_03005000.unk_9e8, sp48);
        for (i = 0; i < CMD_LENGTH - 1; i++)
            gSendCmd[i] = 0;
    }
    return sub_800F0B8();
}

#ifdef NONMATCHING
void sub_800F638(u8 unused, u32 flags)
{
    int i;
    int j;

    u8 *r10 = gUnknown_03005000.unk_6c.unk_04;
    for (i = 0; i < gUnknown_03005000.unk_6c.unk_02; i++)
    {
        if (!(flags & 1))
        {
            gUnknown_03000D90[0] = (~0x76ff) | i;
            for (j = 0; j < 7; j++)
            {
                gUnknown_03000D90[j + 1] = (r10[12 * i + (j << 1) + 1] << 8) | r10[12 * i + (j << 1) + 0];
            }
            for (j = 0; j < 7; j++)
            // This should be an ascending loop.
            // GCC compiles this as descending.
            {
                gUnknown_03000D80[2 * j + 1] = gUnknown_03000D90[j] >> 8;
                gUnknown_03000D80[2 * j + 0] = gUnknown_03000D90[j];
            }
            sub_800D888(&gUnknown_03005000.unk_9e8, gUnknown_03000D80);
            gUnknown_03005000.unk_6c.unk_0c |= (1 << i);
        }
        flags >>= 1;
    }
}
#else
NAKED void sub_800F638(u8 unused, u32 flags)
{
    asm_unified("\tpush {r4-r7,lr}\n"
                    "\tmov r7, r10\n"
                    "\tmov r6, r9\n"
                    "\tmov r5, r8\n"
                    "\tpush {r5-r7}\n"
                    "\tldr r0, =gUnknown_03005000\n"
                    "\tldr r2, [r0, 0x70]\n"
                    "\tmov r10, r2\n"
                    "\tmovs r5, 0\n"
                    "\tadds r2, r0, 0\n"
                    "\tadds r2, 0x6E\n"
                    "\tldrh r3, [r2]\n"
                    "\tcmp r5, r3\n"
                    "\tbge _0800F6D4\n"
                    "\tmov r9, r0\n"
                    "\tldr r0, =gUnknown_03000D90\n"
                    "\tmov r8, r0\n"
                    "_0800F65A:\n"
                    "\tmovs r0, 0x1\n"
                    "\tands r0, r1\n"
                    "\tlsrs r7, r1, 1\n"
                    "\tadds r6, r5, 0x1\n"
                    "\tcmp r0, 0\n"
                    "\tbne _0800F6C8\n"
                    "\tldr r1, =0xffff8900\n"
                    "\tadds r0, r1, 0\n"
                    "\tadds r1, r5, 0\n"
                    "\torrs r1, r0\n"
                    "\tmov r2, r8\n"
                    "\tstrh r1, [r2]\n"
                    "\tmovs r4, 0\n"
                    "\tlsls r0, r5, 1\n"
                    "\tldr r3, =gUnknown_03000D80\n"
                    "\tmov r12, r3\n"
                    "\tadds r0, r5\n"
                    "\tlsls r0, 2\n"
                    "\tmov r1, r10\n"
                    "\tadds r2, r0, r1\n"
                    "\tmov r3, r8\n"
                    "\tadds r3, 0x2\n"
                    "_0800F686:\n"
                    "\tldrb r1, [r2, 0x1]\n"
                    "\tlsls r1, 8\n"
                    "\tldrb r0, [r2]\n"
                    "\torrs r0, r1\n"
                    "\tstrh r0, [r3]\n"
                    "\tadds r2, 0x2\n"
                    "\tadds r3, 0x2\n"
                    "\tadds r4, 0x1\n"
                    "\tcmp r4, 0x6\n"
                    "\tble _0800F686\n"
                    "\tmovs r4, 0\n"
                    "\tldr r2, =gUnknown_03000D90\n"
                    "\tldr r1, =gUnknown_03000D80\n"
                    "_0800F6A0:\n"
                    "\tldrh r0, [r2]\n"
                    "\tlsrs r0, 8\n"
                    "\tstrb r0, [r1, 0x1]\n"
                    "\tldrh r0, [r2]\n"
                    "\tstrb r0, [r1]\n"
                    "\tadds r2, 0x2\n"
                    "\tadds r1, 0x2\n"
                    "\tadds r4, 0x1\n"
                    "\tcmp r4, 0x6\n"
                    "\tble _0800F6A0\n"
                    "\tldr r0, =gUnknown_03005000+0x9E8\n"
                    "\tmov r1, r12\n"
                    "\tbl sub_800D888\n"
                    "\tmovs r1, 0x1\n"
                    "\tlsls r1, r5\n"
                    "\tmov r2, r9\n"
                    "\tldr r0, [r2, 0x78]\n"
                    "\torrs r0, r1\n"
                    "\tstr r0, [r2, 0x78]\n"
                    "_0800F6C8:\n"
                    "\tadds r1, r7, 0\n"
                    "\tadds r5, r6, 0\n"
                    "\tldr r3, =gUnknown_03005000+0x6E\n"
                    "\tldrh r3, [r3]\n"
                    "\tcmp r5, r3\n"
                    "\tblt _0800F65A\n"
                    "_0800F6D4:\n"
                    "\tpop {r3-r5}\n"
                    "\tmov r8, r3\n"
                    "\tmov r9, r4\n"
                    "\tmov r10, r5\n"
                    "\tpop {r4-r7}\n"
                    "\tpop {r0}\n"
                    "\tbx r0\n"
                    "\t.pool");
}
#endif

void sub_800F6FC(u8 a0)
{
    if (gUnknown_03005000.unk_0c == 1 && a0)
        gUnknown_03005000.unk_61[a0] = 1;
    else
        gUnknown_03005000.unk_5c[a0] = 1;
}

void sub_800F728(u8 a0)
{
    gUnknown_03005000.unk_5c[a0] = 0;
    gUnknown_03005000.unk_80[a0].unk_12 = 0;
}

u8 sub_800F74C(const u8 *a0)
{
    u8 i;

    if (gUnknown_03005000.unk_0c == 1)
        return FALSE;
    for (i = 0; i < 4; i++)
    {
        gUnknown_03005000.unk_cde[i] = a0[i];
    }
    return a0[gUnknown_03005000.unk_c3e];
}

void rfu_func_080F97B8(void)
{
    if (gReceivedRemoteLinkPlayers && gUnknown_03005DA8 && gLinkTransferringData != 1)
    {
        gUnknown_03000D78[0]++;
        gUnknown_03005DA8 |= (gUnknown_03000D78[0] << 8);
        sub_800FD14(0xbe00);
    }
}

struct UnkLinkRfuStruct_02022B14 *sub_800F7DC(void)
{
    return &gUnknown_02022B14;
}

bool32 sub_800F7E4(void)
{
    return gUnknown_03005000.unk_00 == rfu_func_080F97B8;
}

void sub_800F804(void)
{
    gUnknown_03005000.unk_00 = rfu_func_080F97B8;
}

void Rfu_set_zero(void)
{
    gUnknown_03005000.unk_00 = NULL;
}

void sub_800F820(void)
{
    sub_800FD14(0x4400);
    if (GetMultiplayerId() == 0)
        gSendCmd[6] = GetBlenderArrowPosition();
    gUnknown_020223C0++;
}

void sub_800F850(void)
{
    if (gUnknown_03005000.unk_00 == NULL)
        gUnknown_03005000.unk_00 = sub_800F820;
}

static void sub_800F86C(u8 unused)
{
    u16 i;
    u16 j;

    for (i = 0; i < MAX_RFU_PLAYERS; i++)
    {
        switch (gRecvCmds[i][0] & 0xff00)
        {
            case 0x7800:
                if (gUnknown_03005000.unk_0c == 0 && gReceivedRemoteLinkPlayers != 0)
                    return;
                // fallthrough
            case 0x7700:
                if (gUnknown_03007890->unk_00 == 0)
                {
                    gUnknown_03005000.playerCount = gRecvCmds[i][1];
                    gUnknown_03005000.unk_cce = sub_800F74C((u8 *)(gRecvCmds[i] + 2));
                }
                break;
            case 0x8800:
                if (gUnknown_03005000.unk_80[i].unk_12 == 0)
                {
                    gUnknown_03005000.unk_80[i].unk_00 = 0;
                    gUnknown_03005000.unk_80[i].unk_02 = gRecvCmds[i][1];
                    gUnknown_03005000.unk_80[i].unk_11 = gRecvCmds[i][2];
                    gUnknown_03005000.unk_80[i].unk_08 = 0;
                    gUnknown_03005000.unk_80[i].unk_12 = 1;
                    gUnknown_03005000.unk_5c[i] = 0;
                }
                break;
            case 0x8900:
                if (gUnknown_03005000.unk_80[i].unk_12 == 1)
                {
                    gUnknown_03005000.unk_80[i].unk_00 = gRecvCmds[i][0] & 0xff;
                    gUnknown_03005000.unk_80[i].unk_08 |= (1 << gUnknown_03005000.unk_80[i].unk_00);
                    for (j = 0; j < 6; j++)
                        gBlockRecvBuffer[i][gUnknown_03005000.unk_80[i].unk_00 * 6 + j] = gRecvCmds[i][j + 1];
                    if (gUnknown_03005000.unk_80[i].unk_08 == gUnknown_082ED628[gUnknown_03005000.unk_80[i].unk_02])
                    {
                        gUnknown_03005000.unk_80[i].unk_12 = 2;
                        sub_800F6FC(i);
                        if (sub_800F7DC()->unk_0a_0 == 0x45 && gReceivedRemoteLinkPlayers != 0 && gUnknown_03005000.unk_0c == 0)
                            sub_8010A70(gBlockRecvBuffer);
                    }
                }
                break;
            case 0xa100:
                sub_800FE84(gUnknown_082ED6B8[gRecvCmds[i][1]].buffer, (u16)gUnknown_082ED6B8[gRecvCmds[i][1]].size);
                break;
            case 0x5f00:
                gUnknown_03005000.unk_e4[i] = 1;
                break;
            case 0x6600:
                if (gUnknown_03005000.unk_100 == gRecvCmds[i][1])
                    gUnknown_03005000.unk_e9[i] = 1;
                break;
            case 0xed00:
                if (gUnknown_03005000.unk_0c == 0)
                {
                    if (gReceivedRemoteLinkPlayers != 0)
                    {
                        if (gRecvCmds[i][1] & gUnknown_03007890->unk_02)
                        {
                            gReceivedRemoteLinkPlayers = 0;
                            sub_800D630();
                            gUnknown_03005000.unk_ce4 = gRecvCmds[i][2];
                        }
                        gUnknown_03005000.playerCount = gRecvCmds[i][3];
                        sub_80109E8(gRecvCmds[i][1]);
                    }
                }
                else
                {
                    sub_800FD14(0xee00);
                    gSendCmd[1] = gRecvCmds[i][1];
                    gSendCmd[2] = gRecvCmds[i][2];
                    gSendCmd[3] = gRecvCmds[i][3];
                }
                break;
            case 0xee00:
                if (gUnknown_03005000.unk_0c == 1)
                {
                    gUnknown_03005000.unk_ce3 |= gRecvCmds[i][1];
                    gUnknown_03005000.unk_ce4 = gRecvCmds[i][2];
                    sub_80109E8(gRecvCmds[i][1]);
                }
                break;
            case 0x4400:
            case 0xbe00:
                gLinkPartnersHeldKeys[i] = gRecvCmds[i][1];
                break;
        }
        if (gUnknown_03005000.unk_0c == 1 && gUnknown_03005000.unk_61[i])
        {
            if (gUnknown_03005000.unk_61[i] == 4)
            {
                gUnknown_03005000.unk_5c[i] = 1;
                gUnknown_03005000.unk_61[i] = 0;
            }
            else
                gUnknown_03005000.unk_61[i]++;
        }
    }
}

bool8 sub_800FC60(void)
{
    int i;

    for (i = 0; i < 5; i++)
    {
        if (gUnknown_03005000.unk_80[i].unk_12)
            return FALSE;
    }
    return TRUE;
}

bool8 sub_800FC88(void)
{
    int i;

    for (i = 0; i < gUnknown_03005000.playerCount; i++)
    {
        if (gUnknown_03005000.unk_80[i].unk_12 != 2 || gUnknown_03005000.unk_5c[i] != 1)
            return FALSE;
    }
    return TRUE;
}

static void sub_800FCC4(struct UnkRfuStruct_2_Sub_6c *data)
{
    data->unk_00 = 0;
    data->unk_02 = 0;
    data->unk_04 = NULL;
    data->unk_08 = 0;
    data->unk_10 = 0;
    data->unk_11 = 0;
    data->unk_12 = 0;
}

u8 sub_800FCD8(void)
{
    u8 flags = 0;
    int i;

    for (i = 0; i < 5; i++)
    {
        if (gUnknown_03005000.unk_80[i].unk_12 == 2 && gUnknown_03005000.unk_5c[i] == 1)
        {
            flags |= (1 << i);
        }
    }
    return flags;
}

#ifdef NONMATCHING
// The switch tree is incorrect
void sub_800FD14(u16 command)
{
    u8 i;
    u8 *buff;
    u8 tmp;

    gSendCmd[0] = command;
    switch (command)
    {
        case 0x8800:
            gSendCmd[1] = gUnknown_03005000.unk_6c.unk_02;
            gSendCmd[2] = gUnknown_03005000.unk_6c.unk_11 + 0x80;
            break;
        case 0xa100:
            if (sub_800FC60())
                gSendCmd[1] = gUnknown_03005000.unk_5a;
            break;
        case 0x7800:
        case 0x7700:
            tmp = gUnknown_03005000.unk_ce2 ^ gUnknown_03005000.unk_ce3;
            gUnknown_03005000.playerCount = gUnknown_082ED695[tmp] + 1;
            gSendCmd[1] = gUnknown_03005000.playerCount;
            buff = (u8 *)(gSendCmd + 2);
            for (i = 0; i < 4; i++)
                buff[i] = gUnknown_03005000.unk_cde[i];
            break;
        case 0x6600:
        case 0x5f00:
            gSendCmd[1] = gUnknown_03005000.unk_100;
            break;
        case 0x4400:
            gSendCmd[0] = 0x4400;
            gSendCmd[1] = gMain.heldKeys;
            break;
        case 0x2f00:
            for (i = 0; i < 6; i++)
                gSendCmd[1 + i] = gUnknown_03005000.unk_f2[i];
            break;
        case 0xbe00:
            gSendCmd[1] = gUnknown_03005DA8;
            break;
    }
}
#else
NAKED void sub_800FD14(u16 command)
{
    asm_unified("\tpush {r4,r5,lr}\n"
                    "\tlsls r0, 16\n"
                    "\tlsrs r1, r0, 16\n"
                    "\tldr r5, =gSendCmd\n"
                    "\tstrh r1, [r5]\n"
                    "\tmovs r0, 0xF0\n"
                    "\tlsls r0, 7\n"
                    "\tadds r4, r5, 0\n"
                    "\tcmp r1, r0\n"
                    "\tbeq _0800FDB0_case_7700_case_7800\n"
                    "\tcmp r1, r0\n"
                    "\tbgt _0800FD62\n"
                    "\tmovs r0, 0xBE\n"
                    "\tlsls r0, 7\n"
                    "\tcmp r1, r0\n"
                    "\tbeq _0800FE00_case_5f00_case_6600\n"
                    "\tcmp r1, r0\n"
                    "\tbgt _0800FD50\n"
                    "\tmovs r0, 0xBC\n"
                    "\tlsls r0, 6\n"
                    "\tcmp r1, r0\n"
                    "\tbeq _0800FE20_case_2f00\n"
                    "\tmovs r0, 0x88\n"
                    "\tlsls r0, 7\n"
                    "\tcmp r1, r0\n"
                    "\tbeq _0800FE14_case_4400\n"
                    "\tb _0800FE46_break\n"
                    "\t.pool\n"
                    "_0800FD50:\n"
                    "\tmovs r0, 0xCC\n"
                    "\tlsls r0, 7\n"
                    "\tcmp r1, r0\n"
                    "\tbeq _0800FE00_case_5f00_case_6600\n"
                    "\tmovs r0, 0xEE\n"
                    "\tlsls r0, 7\n"
                    "\tcmp r1, r0\n"
                    "\tbeq _0800FDB0_case_7700_case_7800\n"
                    "\tb _0800FE46_break\n"
                    "_0800FD62:\n"
                    "\tmovs r0, 0xBE\n"
                    "\tlsls r0, 8\n"
                    "\tcmp r1, r0\n"
                    "\tbeq _0800FE40_case_be00\n"
                    "\tcmp r1, r0\n"
                    "\tbgt _0800FE46_break\n"
                    "\tmovs r0, 0x88\n"
                    "\tlsls r0, 8\n"
                    "\tcmp r1, r0\n"
                    "\tbeq _0800FD80_case_8800\n"
                    "\tmovs r0, 0xA1\n"
                    "\tlsls r0, 8\n"
                    "\tcmp r1, r0\n"
                    "\tbeq _0800FD98_case_a100\n"
                    "\tb _0800FE46_break\n"
                    "_0800FD80_case_8800:\n"
                    "\tldr r0, =gUnknown_03005000\n"
                    "\tadds r1, r0, 0\n"
                    "\tadds r1, 0x6E\n"
                    "\tldrh r1, [r1]\n"
                    "\tstrh r1, [r5, 0x2]\n"
                    "\tadds r0, 0x7D\n"
                    "\tldrb r0, [r0]\n"
                    "\tadds r0, 0x80\n"
                    "\tstrh r0, [r5, 0x4]\n"
                    "\tb _0800FE46_break\n"
                    "\t.pool\n"
                    "_0800FD98_case_a100:\n"
                    "\tbl sub_800FC60\n"
                    "\tlsls r0, 24\n"
                    "\tcmp r0, 0\n"
                    "\tbeq _0800FE46_break\n"
                    "\tldr r0, =gUnknown_03005000\n"
                    "\tadds r0, 0x5A\n"
                    "\tldrb r0, [r0]\n"
                    "\tb _0800FE44_str_break\n"
                    "\t.pool\n"
                    "_0800FDB0_case_7700_case_7800:\n"
                    "\tldr r3, =gUnknown_03005000\n"
                    "\tldr r1, =0x00000ce2\n"
                    "\tadds r0, r3, r1\n"
                    "\tldr r2, =0x00000ce3\n"
                    "\tadds r1, r3, r2\n"
                    "\tldrb r2, [r0]\n"
                    "\tldrb r0, [r1]\n"
                    "\teors r0, r2\n"
                    "\tldr r1, =gUnknown_082ED695\n"
                    "\tadds r0, r1\n"
                    "\tldrb r0, [r0]\n"
                    "\tadds r0, 0x1\n"
                    "\tstrb r0, [r3, 0xD]\n"
                    "\tldrb r0, [r3, 0xD]\n"
                    "\tstrh r0, [r4, 0x2]\n"
                    "\tadds r2, r4, 0x4\n"
                    "\tmovs r4, 0\n"
                    "\tldr r0, =0x00000cde\n"
                    "\tadds r3, r0\n"
                    "_0800FDD6:\n"
                    "\tadds r1, r2, r4\n"
                    "\tadds r0, r4, r3\n"
                    "\tldrb r0, [r0]\n"
                    "\tstrb r0, [r1]\n"
                    "\tadds r0, r4, 0x1\n"
                    "\tlsls r0, 24\n"
                    "\tlsrs r4, r0, 24\n"
                    "\tcmp r4, 0x3\n"
                    "\tbls _0800FDD6\n"
                    "\tb _0800FE46_break\n"
                    "\t.pool\n"
                    "_0800FE00_case_5f00_case_6600:\n"
                    "\tldr r0, =gUnknown_03005000\n"
                    "\tmovs r1, 0x80\n"
                    "\tlsls r1, 1\n"
                    "\tadds r0, r1\n"
                    "\tldrh r0, [r0]\n"
                    "\tstrh r0, [r4, 0x2]\n"
                    "\tb _0800FE46_break\n"
                    "\t.pool\n"
                    "_0800FE14_case_4400:\n"
                    "\tstrh r1, [r5]\n"
                    "\tldr r0, =gMain\n"
                    "\tldrh r0, [r0, 0x2C]\n"
                    "\tb _0800FE44_str_break\n"
                    "\t.pool\n"
                    "_0800FE20_case_2f00:\n"
                    "\tmovs r4, 0\n"
                    "\tldr r3, =gUnknown_03005000+0xF2\n"
                    "_0800FE24:\n"
                    "\tadds r2, r4, 0x1\n"
                    "\tlsls r1, r2, 1\n"
                    "\tadds r1, r5\n"
                    "\tlsls r0, r4, 1\n"
                    "\tadds r0, r3\n"
                    "\tldrh r0, [r0]\n"
                    "\tstrh r0, [r1]\n"
                    "\tlsls r2, 24\n"
                    "\tlsrs r4, r2, 24\n"
                    "\tcmp r4, 0x5\n"
                    "\tbls _0800FE24\n"
                    "\tb _0800FE46_break\n"
                    "\t.pool\n"
                    "_0800FE40_case_be00:\n"
                    "\tldr r0, =gUnknown_03005DA8\n"
                    "\tldrh r0, [r0]\n"
                    "_0800FE44_str_break:\n"
                    "\tstrh r0, [r5, 0x2]\n"
                    "_0800FE46_break:\n"
                    "\tpop {r4,r5}\n"
                    "\tpop {r0}\n"
                    "\tbx r0\n"
                    "\t.pool");
}
#endif

void sub_800FE50(u16 *a0)
{
    if (gSendCmd[0] == 0 && sub_8011A80() == 0)
    {
        memcpy(gUnknown_03005000.unk_f2, a0, sizeof(gUnknown_03005000.unk_f2));
        sub_800FD14(0x2f00);
    }
}

bool32 sub_800FE84(const u8 *src, size_t size)
{
    bool8 r4;
    if (gUnknown_03005000.unk_00 != NULL)
        return FALSE;
    if (gSendCmd[0] != 0)
        return FALSE;
    if (gUnknown_03005000.unk_6c.unk_10 != 0)
    {
        gUnknown_02022B44.unk_83++;
        return FALSE;
    }
    r4 = (size % 12) != 0;
    gUnknown_03005000.unk_6c.unk_11 = GetMultiplayerId();
    gUnknown_03005000.unk_6c.unk_10 = 1;
    gUnknown_03005000.unk_6c.unk_02 = (size / 12) + r4;
    gUnknown_03005000.unk_6c.unk_00 = 0;
    if (size > 0x100)
        gUnknown_03005000.unk_6c.unk_04 = src;
    else
    {
        if (src != gBlockSendBuffer)
            memcpy(gBlockSendBuffer, src, size);
        gUnknown_03005000.unk_6c.unk_04 = gBlockSendBuffer;
    }
    sub_800FD14(0x8800);
    gUnknown_03005000.unk_00 = rfufunc_80F9F44;
    gUnknown_03005000.unk_5b = 0;
    return TRUE;
}

static void rfufunc_80F9F44(void)
{
    if (gSendCmd[0] == 0)
    {
        sub_800FD14(0x8800);
        if (gUnknown_03005000.unk_0c == 1)
        {
            if (++gUnknown_03005000.unk_5b > 2)
                gUnknown_03005000.unk_00 = sub_800FFB0;
        }
        else
        {
            if ((gRecvCmds[GetMultiplayerId()][0] & 0xff00) == 0x8800)
                gUnknown_03005000.unk_00 = sub_800FFB0;
        }
    }
}

static void sub_800FFB0(void)
{
    int i;
    const u8 *src = gUnknown_03005000.unk_6c.unk_04;
    gSendCmd[0] = 0x8900 | gUnknown_03005000.unk_6c.unk_00;
    for (i = 0; i < 7; i++)
        gSendCmd[i + 1] = (src[(i << 1) + gUnknown_03005000.unk_6c.unk_00 * 12 + 1] << 8) | src[(i << 1) + gUnknown_03005000.unk_6c.unk_00 * 12 + 0];
    gUnknown_03005000.unk_6c.unk_00++;
    if (gUnknown_03005000.unk_6c.unk_02 <= gUnknown_03005000.unk_6c.unk_00)
    {
        gUnknown_03005000.unk_6c.unk_10 = 0;
        gUnknown_03005000.unk_00 = rfufunc_80FA020;
    }
}

static void rfufunc_80FA020(void)
{
    const u8 *src = gUnknown_03005000.unk_6c.unk_04;
    u8 mpId = GetMultiplayerId();
    int i;
    if (gUnknown_03005000.unk_0c == 0)
    {
        gSendCmd[0] = (~0x76ff) | (gUnknown_03005000.unk_6c.unk_02 - 1);
        for (i = 0; i < 7; i++)
            gSendCmd[i + 1] = (src[(i << 1) + (gUnknown_03005000.unk_6c.unk_02 - 1) * 12 + 1] << 8) | src[(i << 1) + (gUnknown_03005000.unk_6c.unk_02 - 1) * 12 + 0];
        if ((u8)gRecvCmds[mpId][0] == gUnknown_03005000.unk_6c.unk_02 - 1)
        {
            if (gUnknown_03005000.unk_80[mpId].unk_08 != gUnknown_082ED628[gUnknown_03005000.unk_80[mpId].unk_02])
            {
                sub_800F638(mpId, gUnknown_03005000.unk_80[mpId].unk_08);
                gUnknown_02022B44.unk_64++;
            }
            else
                gUnknown_03005000.unk_00 = NULL;
        }
    }
    else
        gUnknown_03005000.unk_00 = NULL;
}

bool8 sub_8010100(u8 a0)
{
    gUnknown_03005000.unk_5a = a0;
    sub_800FD14(0xa100);
    return TRUE;
}

void sub_801011C(void)
{
    rfu_clearAllSlot();
    sub_800C048();
    gReceivedRemoteLinkPlayers = 0;
    gUnknown_03005000.unk_ef = 1;
    gUnknown_03005000.unk_00 = NULL;
}

void sub_8010148(void)
{
    rfu_REQ_disconnect(gUnknown_03007890->unk_02 | gUnknown_03007890->unk_03);
    rfu_waitREQComplete();
    sub_801011C();
}

void sub_8010168(void)
{
    if (gUnknown_03005000.unk_0c == 0)
    {
        sub_800D630();
        gUnknown_03005000.unk_ce4 = 2;
    }
    else
        gUnknown_03005000.unk_00 = sub_8010148;
}

void sub_8010198(void)
{
    sub_800D630();
    gUnknown_03005000.unk_ce4 = 1;
    gUnknown_03005000.unk_ce3 = gUnknown_03007890->unk_02 | gUnknown_03007890->unk_03;
}

void sub_80101CC(void)
{
    int i;
    u8 playerCount = gUnknown_03005000.playerCount;
    int count = 0;

    for (i = 0; i < MAX_RFU_PLAYERS; i++)
    {
        if (gUnknown_03005000.unk_e4[i])
            count++;
    }
    if (count == playerCount)
    {
        gBattleTypeFlags &= ~BATTLE_TYPE_20;
        if (gUnknown_03005000.unk_0c == 0)
        {
            gUnknown_03005000.unk_ee = 3;
            sub_8010168();
        }
        else
            gUnknown_03005000.unk_00 = sub_8010168;
    }
}

void sub_801022C(void)
{
    if (gSendCmd[0] == 0 && gUnknown_03005000.unk_ce8 == 0)
    {
        sub_800FD14(0x5f00);
        gUnknown_03005000.unk_00 = sub_80101CC;
    }
}

void sub_8010264(u8 taskId)
{
    if (gUnknown_03005000.unk_00 == NULL)
    {
        gUnknown_03005000.unk_cd9 = 1;
        gUnknown_03005000.unk_00 = sub_801022C;
        DestroyTask(taskId);
    }
}

void task_add_05_task_del_08FA224_when_no_RfuFunc(void)
{
    if (!FuncIsActiveTask(sub_8010264))
        CreateTask(sub_8010264, 5);
}

void sub_80102B8(void)
{
    u8 playerCount;
    u8 i;

    if (GetMultiplayerId() != 0)
    {
        u8 r4 = gUnknown_03005000.unk_124.unk_8c2;
        if (r4 == 0 && gUnknown_03005000.unk_fe > 0x3c)
        {
            sub_800FD14(0x6600);
            gUnknown_03005000.unk_fe = r4;
        }
    }
    playerCount = GetLinkPlayerCount();
    for (i = 0; i < playerCount; i++)
    {
        if (gUnknown_03005000.unk_e9[i] == 0)
            break;
    }
    if (i == playerCount)
    {
        for (i = 0; i < MAX_RFU_PLAYERS; i++)
            gUnknown_03005000.unk_e9[i] = 0;
        gUnknown_03005000.unk_100++;
        gUnknown_03005000.unk_00 = NULL;
    }
    gUnknown_03005000.unk_fe++;
}

void sub_8010358(void)
{
    if (gUnknown_03005000.unk_124.unk_8c2 == 0 && gSendCmd[0] == 0)
    {
        sub_800FD14(0x6600);
        gUnknown_03005000.unk_00 = sub_80102B8;
    }
}

void sub_8010390(void)
{
    u8 i;
    u8 playerCount;

    if (GetMultiplayerId() != 0)
    {
        if (gUnknown_03005000.unk_124.unk_8c2 == 0 && gSendCmd[0] == 0)
        {
            sub_800FD14(0x6600);
            gUnknown_03005000.unk_00 = sub_80102B8;
        }
    }
    else
    {
        playerCount = GetLinkPlayerCount();
        for (i = 1; i < playerCount; i++)
        {
            if (gUnknown_03005000.unk_e9[i] == 0)
                break;
        }
        if (i == playerCount)
        {
            if (gUnknown_03005000.unk_124.unk_8c2 == 0 && gSendCmd[0] == 0)
            {
                sub_800FD14(0x6600);
                gUnknown_03005000.unk_00 = sub_8010358;
            }
        }
    }
}

void sub_8010434(void)
{
    if (gUnknown_03005000.unk_00 == NULL)
    {
        gUnknown_03005000.unk_00 = sub_8010390;
        gUnknown_03005000.unk_fe = 0;
    }
}

bool32 sub_8010454(u32 a0)
{
    int i;
    for (i = 0; gUnknown_082ED6E0[i] != a0; i++)
    {
        if (gUnknown_082ED6E0[i] == 0xffff)
            return FALSE;
    }
    return TRUE;
}

u8 sub_801048C(bool32 a0)
{
    if (a0 == 0)
        return sub_800D550(0, 0);
    sub_800D550(1, 0x258);
    return FALSE;
}

void sub_80104B0(void)
{
    gUnknown_03005000.unk_cd9 = 1;
    sub_800C27C(FALSE);
}

u8 rfu_get_multiplayer_id(void)
{
    if (gUnknown_03005000.unk_0c == 1)
        return 0;
    return gUnknown_03005000.unk_cce;
}

u8 sub_80104F4(void)
{
    return gUnknown_03005000.playerCount;
}

bool8 sub_8010500(void)
{
    if (gUnknown_03005000.unk_f1 == 2)
        return FALSE;
    return gUnknown_03005000.unk_00 ? FALSE : TRUE;
}

static void sub_8010528(void)
{
    if (gUnknown_03005000.unk_00)
        gUnknown_03005000.unk_00();
}

bool8 sub_8010540(void)
{
    int i;
    bool8 retval = FALSE;
    for (i = 0; i < 4; i++)
    {
        if (gUnknown_03005000.unk_cd1[i] < 5 || gUnknown_03005000.unk_cd1[i] > 6)
        {
            if (gUnknown_03007880[i]->unk_34 == 0x46 || gUnknown_03007880[i]->unk_34 == 0x48)
            {
                if (gUnknown_03005000.unk_cd5[i] == 8)
                {
                    gUnknown_03005000.unk_cd1[i] = 9;
                    gUnknown_03005000.unk_cd5[i] = 10;
                    rfu_clearSlot(8, i);
                    rfu_NI_setSendData(1 << i, 8, gUnknown_03005000.unk_cd1 + i, 1);
                    retval = TRUE;
                }

            }
            else if (gUnknown_03007880[gUnknown_03005000.unk_c3e]->unk_34 == 0x47)
                rfu_clearSlot(8, i);
            {

            }
        }
    }
    return retval;
}

bool32 sub_80105EC(void)
{
    u8 flags = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (gUnknown_03005000.unk_cd5[i] == 11)
        {
            flags |= (1 << i);
            gUnknown_03005000.unk_cd5[i] = 0;
        }
    }
    if (flags)
    {
        rfu_REQ_disconnect(flags);
        rfu_waitREQComplete();
    }
    for (i = 0; i < 4; i++)
    {
        if (gUnknown_03005000.unk_cd5[i] == 10 || gUnknown_03005000.unk_cd5[i] == 11)
            return TRUE;
    }
    return FALSE;
}

bool32 sub_801064C(u16 a0, const u8 *a1)
{
    u8 r1 = sub_8011CE4(a1, a0);
    if (r1 == 0xFF)
        return TRUE;
    if (gUnknown_03005000.unk_cd1[r1] == 9)
        return TRUE;
    return FALSE;
}

void sub_8010688(u8 a0, u16 a1, const u8 *a2)
{
    u8 r4 = sub_8011CE4(a2, a1);
    gUnknown_03005000.unk_cd1[r4] = a0;
    rfu_clearSlot(4, r4);
    rfu_NI_setSendData(1 << r4, 8, gUnknown_03005000.unk_cd1 + r4, 1);
}

void sub_80106D4(void)
{
    gUnknown_03005000.unk_c85 = 8;
    rfu_clearSlot(4, gUnknown_03005000.unk_c3e);
    rfu_NI_setSendData(1 << gUnknown_03005000.unk_c3e, 8, &gUnknown_03005000.unk_c85, 1);
}

u32 sub_8010714(u16 a0, const u8 *a1)
{
    u8 r0 = sub_8011CE4(a1, a0);
    if (r0 == 0xff)
        return 2;
    if (gUnknown_03007880[r0]->unk_0 == 0)
        return 1;
    return 0;
}

void sub_8010750(void)
{
    int i;

    sub_8010540();
    for (i = 0; i < 4; i++)
    {
        if (gUnknown_03007880[i]->unk_0 == 0x26 || gUnknown_03007880[i]->unk_0 == 0x27)
        {
            if (gUnknown_03005000.unk_cd5[i] == 10)
                gUnknown_03005000.unk_cd5[i] = 11;
            rfu_clearSlot(4, i);
        }
    }
}

int sub_80107A0(void)
{
    int retval = 0;
    if (gUnknown_03005000.unk_c85 == 8)
    {
        if (gUnknown_03007880[gUnknown_03005000.unk_c3e]->unk_0 == 0x26 || gUnknown_03007880[gUnknown_03005000.unk_c3e]->unk_0 == 0x27)
            rfu_clearSlot(4, gUnknown_03005000.unk_c3e);
    }
    if (gUnknown_03007880[gUnknown_03005000.unk_c3e]->unk_34 == 0x46 || gUnknown_03007880[gUnknown_03005000.unk_c3e]->unk_34 == 0x48)
    {
        rfu_clearSlot(8, gUnknown_03005000.unk_c3e);
        sub_8011A64(gUnknown_03005000.unk_c86, 0);
        retval = gUnknown_03005000.unk_c86;
    }
    else if (gUnknown_03007880[gUnknown_03005000.unk_c3e]->unk_34 == 0x47)
    {
        rfu_clearSlot(8, gUnknown_03005000.unk_c3e);
        retval = 6;
    }
    return retval;
}

void sub_801084C(u8 taskId)
{
    int i;

    if (gUnknown_03005000.unk_f1 == 1 || gUnknown_03005000.unk_f1 == 2)
    {
        gUnknown_03005000.unk_ce8 = 0;
        DestroyTask(taskId);
    }
    switch (gTasks[taskId].data[0])
    {
        case 0:
            if (sub_800FC60())
            {
                ResetBlockReceivedFlags();
                sub_800B348();
                gTasks[taskId].data[0]++;
            }
            break;
        case 1:
            if (gUnknown_03005000.unk_0c == 1)
            {
                if (gReceivedRemoteLinkPlayers)
                    sub_800FD14(0x7800);
                else
                    sub_800FD14(0x7700);
                gTasks[taskId].data[0] = 101;
            }
            else
                gTasks[taskId].data[0] = 2;
            break;
        case 101:
            if (gSendCmd[0] == 0)
                gTasks[taskId].data[0] = 2;
            break;
        case 2:
            if (gUnknown_03005000.playerCount)
                gTasks[taskId].data[0]++;
            break;
        case 3:
            if (gUnknown_03005000.unk_0c == 1)
            {
                if (sub_800FC60())
                {
                    gUnknown_03005000.unk_5a = 0;
                    sub_800FD14(0xa100);
                    gTasks[taskId].data[0]++;
                }
            }
            else
                gTasks[taskId].data[0]++;
            break;
        case 4:
            if (sub_800FC88())
                gTasks[taskId].data[0]++;
            break;
        case 5:
            for (i = 0; i < gUnknown_03005000.playerCount; i++)
            {
                sub_800B3A4(i);
                sub_800F728(i);
            }
            gTasks[taskId].data[0]++;
            break;
        case 6:
            DestroyTask(taskId);
            gReceivedRemoteLinkPlayers = 1;
            gUnknown_03005000.unk_ce8 = 0;
            sub_800D550(1, 0x258);
            if (gUnknown_03005000.unk_ce6)
            {
                for (i = 0; i < 4; i++)
                {
                    if ((gUnknown_03005000.unk_ce6 >> i) & 1)
                    {
                        gUnknown_03005000.unk_ce5 = 1 << i;
                        gUnknown_03005000.unk_ce6 ^= (1 << i);
                    }
                }
            }
            break;
    }
}

void sub_80109E8(u16 a0)
{
    int i;

    for (i = 0; i < 4; i++)
    {
        if ((a0 >> i) & 1)
            gUnknown_03005000.unk_cde[i] = 0;
    }
}

void sub_8010A14(const struct UnkRfuStruct_8010A14 *a0)
{
    int i;
    gUnknown_03005000.playerCount = a0->unk_0f;
    for (i = 0; i < 4; i++)
        gUnknown_03005000.unk_cde[i] = a0->unk_10[i];
    for (i = 0; i < MAX_RFU_PLAYERS; i++)
    {
        gLinkPlayers[i] = a0->unk_14[i];
        sub_800B524(gLinkPlayers + i);
    }
}

void sub_8010A70(void *a0)
{
    if (strcmp(gUnknown_082ED7EC, a0) == 0)
    {
        sub_8010A14(a0);
        CpuFill16(0, a0, sizeof(struct UnkRfuStruct_8010A14));
        ResetBlockReceivedFlag(0);
    }
}

void sub_8010AAC(u8 taskId)
{
    int i;
    struct LinkPlayerBlock *r2;
    struct UnkRfuStruct_8010A14 *r5;
    u8 r4 = gUnknown_03005000.unk_cde[gUnknown_082ED68C[gUnknown_03005000.unk_ce9]];
    if (gUnknown_03005000.unk_f1 == 1 || gUnknown_03005000.unk_f1 == 2)
    {
        gUnknown_03005000.unk_ce8 = 0;
        DestroyTask(taskId);
    }
    switch (gTasks[taskId].data[0])
    {
        case 0:
            if (gSendCmd[0] == 0)
            {
                ResetBlockReceivedFlag(r4);
                sub_800FD14(0x7800);
                gTasks[taskId].data[0]++;
            }
            break;
        case 1:
            if (gSendCmd[0] == 0)
                gTasks[taskId].data[0]++;
            break;
        case 2:
            if ((GetBlockReceivedStatus() >> r4) & 1)
            {
                ResetBlockReceivedFlag(r4);
                r2 = (struct LinkPlayerBlock *)gBlockRecvBuffer[r4];
                gLinkPlayers[r4] = r2->linkPlayer;
                sub_800B524(gLinkPlayers + r4);
                gTasks[taskId].data[0]++;
            }
            break;
        case 3:
            r5 = (struct UnkRfuStruct_8010A14 *)gBlockSendBuffer;
            memcpy(r5->unk_00, gUnknown_082ED7EC, sizeof gUnknown_082ED7EC);
            r5->unk_0f = gUnknown_03005000.playerCount;
            for (i = 0; i < 4; i++)
                r5->unk_10[i] = gUnknown_03005000.unk_cde[i];
            memcpy(r5->unk_14, gLinkPlayers, sizeof gLinkPlayers);
            gTasks[taskId].data[0]++;
            // fallthrough
        case 4:
            r5 = (struct UnkRfuStruct_8010A14 *)gBlockSendBuffer;
            r5->unk_0f = gUnknown_03005000.playerCount;
            for (i = 0; i < 4; i++)
                r5->unk_10[i] = gUnknown_03005000.unk_cde[i];
            memcpy(r5->unk_14, gLinkPlayers, sizeof gLinkPlayers);
            if (SendBlock(0, gBlockSendBuffer, 0xa0))
                gTasks[taskId].data[0]++;
            break;
        case 5:
            if (sub_800A520() && GetBlockReceivedStatus() & 1)
            {
                CpuFill16(0, gBlockRecvBuffer, sizeof(struct UnkRfuStruct_8010A14));
                ResetBlockReceivedFlag(0);
                gUnknown_03005000.unk_ce8 = 0;
                if (gUnknown_03005000.unk_ce6)
                {
                    for (i = 0; i < 4; i++)
                    {
                        if ((gUnknown_03005000.unk_ce6 >> i) & 1)
                        {
                            gUnknown_03005000.unk_ce5 = 1 << i;
                            gUnknown_03005000.unk_ce6 ^= (1 << i);
                            gUnknown_03005000.unk_ce8 = 1;
                            break;
                        }
                    }
                }
                DestroyTask(taskId);
            }
            break;
    }
}

void sub_8010D0C(u8 taskId)
{
    if (gUnknown_03005000.unk_f1 == 1 || gUnknown_03005000.unk_f1 == 2)
        DestroyTask(taskId);
    switch (gTasks[taskId].data[0])
    {
        case 0:
            if (gUnknown_03005000.playerCount)
            {
                sub_800B348();
                SendBlock(0, gBlockSendBuffer, sizeof(struct LinkPlayerBlock));
                gTasks[taskId].data[0]++;
            }
            break;
        case 1:
            if (sub_800A520())
                gTasks[taskId].data[0]++;
            break;
        case 2:
            if (GetBlockReceivedStatus() & 1)
            {
                sub_8010A14((const struct UnkRfuStruct_8010A14 *)gBlockRecvBuffer);
                ResetBlockReceivedFlag(0);
                gReceivedRemoteLinkPlayers = 1;
                DestroyTask(taskId);
            }
            break;
    }
}

void sub_8010DB4(void)
{
    if (gUnknown_03005000.unk_ee == 1 && gUnknown_03004140.unk_02 == 0)
    {
        if (gMain.callback2 == sub_8018438 || gUnknown_03004140.unk_3c->unk_04)
            gWirelessCommType = 2;
        SetMainCallback2(CB2_LinkError);
        gMain.savedCallback = CB2_LinkError;
        sub_800AF18((gUnknown_03005000.unk_0a << 16) | (gUnknown_03005000.unk_10 << 8) | gUnknown_03005000.unk_12, gUnknown_03005000.unk_124.unk_8c2, gUnknown_03005000.unk_9e8.unk_232, sub_8011A74() == 2);
        gUnknown_03005000.unk_ee = 2;
        CloseLink();
    }
    else if (gUnknown_03005000.unk_9e8.unk_233 == 1 || gUnknown_03005000.unk_124.unk_8c3 == 1)
    {
        if (gUnknown_03004140.unk_02)
            sub_800D630();
        sub_8011A64(1, 0x7000);
        sub_8011170(0x7000);
    }
}

void rfu_REQ_recvData_then_sendData(void)
{
    if (gUnknown_03004140.unk_06 == 1)
    {
        rfu_REQ_recvData();
        rfu_waitREQComplete();
        rfu_REQ_sendData_wrapper(0);
    }
}

bool32 sub_8010EC0(void)
{
    bool32 retval = FALSE;
    gUnknown_03005000.unk_ccd = 0;
    sub_800C54C(Random2());
    if (gUnknown_03005000.unk_ef == 0)
    {
        switch (gUnknown_03005000.unk_0c)
        {
            case 1:
                sub_800F0F8();
                break;
            case 0:
                retval = sub_800F4F0();
                break;
            case 2:
                rfu_REQ_recvData_then_sendData();
                break;
        }
    }
    return retval;
}

bool32 sub_8010F1C(void)
{
    bool32 retval = FALSE;
    if (gUnknown_03005000.unk_ef == 0)
    {
        if (gUnknown_03005000.unk_0c == 1)
            retval = sub_800F1E0();
        sub_8010DB4();
    }
    return retval;
}

void sub_8010F48(void)
{
    StringCopy(gUnknown_02022B22, gSaveBlock2Ptr->playerName);
}

void sub_8010F60(void)
{
    gUnknown_02022B14 = (struct UnkLinkRfuStruct_02022B14){};
    sub_800DD94(&gUnknown_02022B14, 0, 0, 0);
}

void sub_8010F84(u8 a0, u32 a1, u32 a2)
{
    sub_800DD94(&gUnknown_02022B14, a0, a2, a1);
}

void sub_8010FA0(bool32 a0, bool32 a1)
{
    gUnknown_02022B14.unk_00.unk_00_4 = a0;
    gUnknown_02022B14.unk_00.unk_00_5 = a1;
}

void sub_8010FCC(u32 a0, u32 a1, u32 a2)
{
    gUnknown_02022B14.type = a0;
    gUnknown_02022B14.species = a1;
    gUnknown_02022B14.unk_0b_1 = a2;
}

u8 sub_801100C(int a0)
{
    u8 retval = 0x80;
    retval |= (gLinkPlayers[a0].gender << 3);
    retval |= (gLinkPlayers[a0].trainerId & 7);
    return retval;
}

void sub_801103C(void)
{
    struct UnkLinkRfuStruct_02022B14 *r5 = &gUnknown_02022B14;
    int i;

    for (i = 1; i < GetLinkPlayerCount(); i++)
        r5->unk_04[i - 1] = sub_801100C(i);
}

void sub_8011068(u8 a0)
{
    gUnknown_02022B14.unk_0a_7 = a0;
    rfu_REQ_configGameData(0, 2, &gUnknown_02022B14, gUnknown_02022B22);
}

void sub_8011090(u8 a0, u32 a1, u32 a2)
{
    if (a0)
        sub_8010F84(a0, a1, a2);
    rfu_REQ_configGameData(0, 2, &gUnknown_02022B14, gUnknown_02022B22);
}

void sub_80110B8(u32 a0)
{
    int i;
    u32 r5;
    u32 r7;
    int r8;

    if (sub_800F7DC()->unk_0a_0 == 0x45)
    {
        r5 = 0;
        r7 = 0;
        r8 = gUnknown_03005000.unk_ce2 ^ gUnknown_03005000.unk_ce3;
        for (i = 0; i < 4; i++)
        {
            if ((r8 >> i) & 1)
            {
                r7 |= ((0x80 | ((gLinkPlayers[gUnknown_03005000.unk_cde[i]].gender & 1) << 3) | (gLinkPlayers[gUnknown_03005000.unk_cde[i]].trainerId & 7)) << (r5 << 3));
                r5++;
                if (r5 == a0 - 1)
                    break;
            }
        }
        sub_8011090(0x45, r7, 0);
    }
}

void sub_8011170(u32 a0)
{
    if (gUnknown_03005000.unk_ee == 0)
    {
        gUnknown_03005000.unk_10 = gUnknown_03004140.unk_14;
        gUnknown_03005000.unk_12 = gUnknown_03004140.unk_16;
        gUnknown_03005000.unk_0a = a0;
        gUnknown_03005000.unk_ee = 1;
    }
}

void sub_80111A0(void)
{
    gUnknown_03005000.unk_ee = 0;
}

void sub_80111B0(bool32 a0)
{
    if (!a0)
        gUnknown_03005000.unk_ee = 0;
    else
        gUnknown_03005000.unk_ee = 4;
}

void sub_80111DC(void)
{
    sub_8011E94(gUnknown_03004140.unk_00, 1);
    gUnknown_03005000.unk_00 = NULL;
}

void sub_80111FC(void)
{
    gUnknown_03005000.unk_00 = sub_80111DC;
}

#ifdef NONMATCHING
void sub_801120C(u8 a0)
{
    u8 i;
    u8 r6 = 0;
    struct RfuUnk5Sub *unk5Sub;
    switch (a0)
    {
        case 0x00:
            gUnknown_03005000.unk_04 = 2;
            break;
        case 0x10:
            break;
        case 0x11:
            sub_80115EC(gUnknown_03004140.unk_14);
            for (i = 0; i < 4; i++)
            {
                if ((gUnknown_03004140.unk_14 >> i) & 1)
                {
                    unk5Sub = &gUnknown_03007890->unk_14[i];
                    if (unk5Sub->unk_06.unk_0a_0 == sub_800F7DC()->unk_0a_0)
                    {
                        gUnknown_03005000.unk_cd1[i] = 0;
                        gUnknown_03005000.unk_cd5[i] = 0;
                        rfu_setRecvBuffer(0x20, i, gUnknown_03005000.unk_cd5 + i, 1);
                    }
                    else
                    {
                        r6 |= (1 << i);
                    }
                }
            }
            if (r6)
            {
                rfu_REQ_disconnect(r6);
                rfu_waitREQComplete();
            }
            break;
        case 0x12:
            break;
        case 0x13:
            break;
        case 0x14:
            if (gUnknown_03005000.unk_ce7 != gUnknown_03004140.unk_00)
            {
                rfu_REQ_disconnect(gUnknown_03005000.unk_ce7 ^ gUnknown_03004140.unk_00);
                rfu_waitREQComplete();
            }
            gUnknown_03005000.unk_04 = 0x11;
            break;
        case 0x31:
            gUnknown_03005000.unk_f0 = 1;
            break;
        case 0x32:
            gUnknown_03005000.unk_f0 = 3;
            break;
        case 0x30:
        case 0x33:
            gUnknown_03005000.unk_f0 = 4;
            gUnknown_03005000.unk_ce2 &= ~gUnknown_03004140.unk_14;
            if (gReceivedRemoteLinkPlayers == 1)
            {
                if (gUnknown_03005000.unk_ce2 == 0)
                    sub_8011170(a0);
                else
                    sub_80111FC();
            }
            sub_8011A64(2, a0);
            break;
        case 0x42 ... 0x44:
            break;
        case 0xf3:
            sub_8011A64(1, a0);
            sub_8011170(a0);
            gUnknown_03005000.unk_ef = 1;
            break;
        case 0xf0 ... 0xf2:
        case 0xff:
            sub_8011170(a0);
            sub_8011A64(1, a0);
            gUnknown_03005000.unk_cdb = 1;
            break;
    }
}
#else
NAKED void sub_801120C(u8 a0)
{
    asm_unified("\tpush {r4-r7,lr}\n"
                    "\tmov r7, r10\n"
                    "\tmov r6, r9\n"
                    "\tmov r5, r8\n"
                    "\tpush {r5-r7}\n"
                    "\tlsls r0, 24\n"
                    "\tlsrs r4, r0, 24\n"
                    "\tmovs r6, 0\n"
                    "\tcmp r4, 0x32\n"
                    "\tbne _08011222\n"
                    "\tb _08011360_case_32\n"
                    "_08011222:\n"
                    "\tcmp r4, 0x32\n"
                    "\tbgt _08011252\n"
                    "\tcmp r4, 0x13\n"
                    "\tbgt _08011240\n"
                    "\tcmp r4, 0x12\n"
                    "\tblt _08011230\n"
                    "\tb _080113EE_break\n"
                    "_08011230:\n"
                    "\tcmp r4, 0x10\n"
                    "\tbne _08011236\n"
                    "\tb _080113EE_break\n"
                    "_08011236:\n"
                    "\tcmp r4, 0x10\n"
                    "\tbgt _0801128C_case_11\n"
                    "\tcmp r4, 0\n"
                    "\tbeq _0801127E_case_00\n"
                    "\tb _080113EE_break\n"
                    "_08011240:\n"
                    "\tcmp r4, 0x30\n"
                    "\tbne _08011246\n"
                    "\tb _0801136C_case_30_case_33\n"
                    "_08011246:\n"
                    "\tcmp r4, 0x30\n"
                    "\tble _0801124C\n"
                    "\tb _08011354_case_31\n"
                    "_0801124C:\n"
                    "\tcmp r4, 0x14\n"
                    "\tbeq _08011328_case_14\n"
                    "\tb _080113EE_break\n"
                    "_08011252:\n"
                    "\tcmp r4, 0x44\n"
                    "\tbgt _08011264\n"
                    "\tcmp r4, 0x42\n"
                    "\tblt _0801125C\n"
                    "\tb _080113EE_break\n"
                    "_0801125C:\n"
                    "\tcmp r4, 0x33\n"
                    "\tbne _08011262\n"
                    "\tb _0801136C_case_30_case_33\n"
                    "_08011262:\n"
                    "\tb _080113EE_break\n"
                    "_08011264:\n"
                    "\tcmp r4, 0xF3\n"
                    "\tbne _0801126A\n"
                    "\tb _080113BA_case_f3\n"
                    "_0801126A:\n"
                    "\tcmp r4, 0xF3\n"
                    "\tbgt _08011276\n"
                    "\tcmp r4, 0xF0\n"
                    "\tbge _08011274\n"
                    "\tb _080113EE_break\n"
                    "_08011274:\n"
                    "\tb _080113D4_case_f0_f1_f2_ff\n"
                    "_08011276:\n"
                    "\tcmp r4, 0xFF\n"
                    "\tbne _0801127C\n"
                    "\tb _080113D4_case_f0_f1_f2_ff\n"
                    "_0801127C:\n"
                    "\tb _080113EE_break\n"
                    "_0801127E_case_00:\n"
                    "\tldr r1, =gUnknown_03005000\n"
                    "\tmovs r0, 0x2\n"
                    "\tstrh r0, [r1, 0x4]\n"
                    "\tb _080113EE_break\n"
                    "\t.pool\n"
                    "_0801128C_case_11:\n"
                    "\tldr r0, =gUnknown_03004140\n"
                    "\tldrh r0, [r0, 0x14]\n"
                    "\tbl sub_80115EC\n"
                    "\tmovs r5, 0\n"
                    "\tmovs r0, 0x1\n"
                    "\tmov r8, r0\n"
                    "\tldr r1, =gUnknown_03005000\n"
                    "\tmov r9, r1\n"
                    "\tldr r3, =0x00000cd5\n"
                    "\tadd r3, r9\n"
                    "\tmov r10, r3\n"
                    "\tmovs r7, 0x7F\n"
                    "_080112A6:\n"
                    "\tldr r0, =gUnknown_03004140\n"
                    "\tldrh r0, [r0, 0x14]\n"
                    "\tasrs r0, r5\n"
                    "\tmov r1, r8\n"
                    "\tands r0, r1\n"
                    "\tcmp r0, 0\n"
                    "\tbeq _0801130E\n"
                    "\tldr r0, =gUnknown_03007890\n"
                    "\tlsls r1, r5, 5\n"
                    "\tadds r1, 0x14\n"
                    "\tldr r0, [r0]\n"
                    "\tadds r0, r1\n"
                    "\tldrb r0, [r0, 0x10]\n"
                    "\tadds r4, r7, 0\n"
                    "\tands r4, r0\n"
                    "\tbl sub_800F7DC\n"
                    "\tldrb r1, [r0, 0xA]\n"
                    "\tadds r0, r7, 0\n"
                    "\tands r0, r1\n"
                    "\tcmp r4, r0\n"
                    "\tbne _08011304\n"
                    "\tldr r0, =0x00000cd1\n"
                    "\tadd r0, r9\n"
                    "\tadds r0, r5, r0\n"
                    "\tmovs r1, 0\n"
                    "\tstrb r1, [r0]\n"
                    "\tmov r3, r10\n"
                    "\tadds r2, r5, r3\n"
                    "\tstrb r1, [r2]\n"
                    "\tmovs r0, 0x20\n"
                    "\tadds r1, r5, 0\n"
                    "\tmovs r3, 0x1\n"
                    "\tbl rfu_setRecvBuffer\n"
                    "\tb _0801130E\n"
                    "\t.pool\n"
                    "_08011304:\n"
                    "\tmov r0, r8\n"
                    "\tlsls r0, r5\n"
                    "\torrs r6, r0\n"
                    "\tlsls r0, r6, 24\n"
                    "\tlsrs r6, r0, 24\n"
                    "_0801130E:\n"
                    "\tadds r0, r5, 0x1\n"
                    "\tlsls r0, 24\n"
                    "\tlsrs r5, r0, 24\n"
                    "\tcmp r5, 0x3\n"
                    "\tbls _080112A6\n"
                    "\tcmp r6, 0\n"
                    "\tbeq _080113EE_break\n"
                    "\tadds r0, r6, 0\n"
                    "\tbl rfu_REQ_disconnect\n"
                    "\tbl rfu_waitREQComplete\n"
                    "\tb _080113EE_break\n"
                    "_08011328_case_14:\n"
                    "\tldr r4, =gUnknown_03005000\n"
                    "\tldr r1, =0x00000ce7\n"
                    "\tadds r0, r4, r1\n"
                    "\tldr r1, =gUnknown_03004140\n"
                    "\tldrb r2, [r0]\n"
                    "\tldrb r0, [r1]\n"
                    "\tcmp r2, r0\n"
                    "\tbeq _08011342\n"
                    "\teors r0, r2\n"
                    "\tbl rfu_REQ_disconnect\n"
                    "\tbl rfu_waitREQComplete\n"
                    "_08011342:\n"
                    "\tmovs r0, 0x11\n"
                    "\tstrh r0, [r4, 0x4]\n"
                    "\tb _080113EE_break\n"
                    "\t.pool\n"
                    "_08011354_case_31:\n"
                    "\tldr r0, =gUnknown_03005000\n"
                    "\tadds r0, 0xF0\n"
                    "\tb _080113EA\n"
                    "\t.pool\n"
                    "_08011360_case_32:\n"
                    "\tldr r0, =gUnknown_03005000\n"
                    "\tadds r0, 0xF0\n"
                    "\tmovs r1, 0x3\n"
                    "\tb _080113EC\n"
                    "\t.pool\n"
                    "_0801136C_case_30_case_33:\n"
                    "\tldr r1, =gUnknown_03005000\n"
                    "\tadds r2, r1, 0\n"
                    "\tadds r2, 0xF0\n"
                    "\tmovs r0, 0x4\n"
                    "\tstrb r0, [r2]\n"
                    "\tldr r3, =0x00000ce2\n"
                    "\tadds r1, r3\n"
                    "\tldr r0, =gUnknown_03004140\n"
                    "\tldrb r2, [r0, 0x14]\n"
                    "\tldrb r0, [r1]\n"
                    "\tadds r3, r0, 0\n"
                    "\tbics r3, r2\n"
                    "\tadds r2, r3, 0\n"
                    "\tstrb r2, [r1]\n"
                    "\tldr r0, =gReceivedRemoteLinkPlayers\n"
                    "\tldrb r0, [r0]\n"
                    "\tcmp r0, 0x1\n"
                    "\tbne _080113B0\n"
                    "\tcmp r2, 0\n"
                    "\tbne _080113AC\n"
                    "\tadds r0, r4, 0\n"
                    "\tbl sub_8011170\n"
                    "\tb _080113B0\n"
                    "\t.pool\n"
                    "_080113AC:\n"
                    "\tbl sub_80111FC\n"
                    "_080113B0:\n"
                    "\tmovs r0, 0x2\n"
                    "\tadds r1, r4, 0\n"
                    "\tbl sub_8011A64\n"
                    "\tb _080113EE_break\n"
                    "_080113BA_case_f3:\n"
                    "\tmovs r0, 0x1\n"
                    "\tmovs r1, 0xF3\n"
                    "\tbl sub_8011A64\n"
                    "\tmovs r0, 0xF3\n"
                    "\tbl sub_8011170\n"
                    "\tldr r0, =gUnknown_03005000\n"
                    "\tadds r0, 0xEF\n"
                    "\tb _080113EA\n"
                    "\t.pool\n"
                    "_080113D4_case_f0_f1_f2_ff:\n"
                    "\tadds r0, r4, 0\n"
                    "\tbl sub_8011170\n"
                    "\tmovs r0, 0x1\n"
                    "\tadds r1, r4, 0\n"
                    "\tbl sub_8011A64\n"
                    "\tldr r0, =gUnknown_03005000\n"
                    "\tldr r1, =0x00000cdb\n"
                    "\tadds r0, r1\n"
                    "\tldrb r1, [r0]\n"
                    "_080113EA:\n"
                    "\tmovs r1, 0x1\n"
                    "_080113EC:\n"
                    "\tstrb r1, [r0]\n"
                    "_080113EE_break:\n"
                    "\tpop {r3-r5}\n"
                    "\tmov r8, r3\n"
                    "\tmov r9, r4\n"
                    "\tmov r10, r5\n"
                    "\tpop {r4-r7}\n"
                    "\tpop {r0}\n"
                    "\tbx r0\n"
                    "\t.pool");
}
#endif
