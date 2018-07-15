#include "global.h"
#include "main.h"
#include "palette.h"
#include "gpu_regs.h"
#include "bg.h"
#include "rtc.h"
#include "clock.h"
#include "wallclock.h"
#include "event_data.h"
#include "graphics.h"
#include "text.h"
#include "window.h"
#include "text_window.h"
#include "menu.h"
#include "scanline_effect.h"
#include "task.h"
#include "strings.h"
#include "sound.h"
#include "constants/songs.h"
#include "trig.h"
#include "decompress.h"

// static types

#define tMinuteHandAngle data[0]
#define tHourHandAngle   data[1]
#define tHours           data[2]
#define tMinutes         data[3]
#define tMvmtDir         data[4]
#define tPeriod          data[5]
#define tMvmtSpeed       data[6]

#define TAG_GFX_WALL_CLOCK_HAND 0x1000
#define TAG_PAL_WALL_CLOCK_HAND 0x1000

// static declarations

static void WallClockMainCallback(void);
static void Task_SetClock1(u8 taskId);
static void Task_SetClock2(u8 taskId);
static void Task_SetClock3(u8 taskId);
static void Task_SetClock4(u8 taskId);
static void Task_SetClock5(u8 taskId);
static void Task_SetClock6(u8 taskId);
static void Task_ViewClock1(u8 taskId);
static void Task_ViewClock2(u8 taskId);
static void Task_ViewClock3(u8 taskId);
static void Task_ViewClock4(u8 taskId);
static u16 CalcNewMinHandAngle(u16 a0, u8 command, u8 a2);
static bool32 AdvanceClock(u8 taskId, u8 command);
static void UpdateClockPeriod(u8 taskId, u8 command);
static void InitClockWithRtc(u8 taskId);
static void SpriteCB_MinuteHand(struct Sprite *sprite);
static void SpriteCB_HourHand(struct Sprite *sprite);
static void SpriteCB_AMIndicator(struct Sprite *sprite);
static void SpriteCB_PMIndicator(struct Sprite *sprite);

// rodata

static const u8 sUnknown_085B1F58[] = INCBIN_U8("graphics/wallclock/graphics_85b1f58.4bpp.lz");
static const u16 sUnknown_085B21D4[] = INCBIN_U16("graphics/wallclock/palette_85b21d4.gbapal");
static const struct WindowTemplate gUnknown_085B21DC[] = {
    { 0x00, 0x03, 0x11, 0x18, 0x02, 0x0e, 0x200 },
    { 0x02, 0x18, 0x10, 0x06, 0x02, 0x0c, 0x230 },
    DUMMY_WIN_TEMPLATE
};
static const struct WindowTemplate gUnknown_085B21F4 = {
    0x00, 0x18, 0x09, 0x05, 0x04, 0x0e, 0x23c
};
static const struct BgTemplate gUnknown_085B21FC[] = {
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 31,
        .priority = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 1,
        .mapBaseIndex = 8,
        .priority = 1
    },
    {
        .bg = 3,
        .charBaseIndex = 0,
        .mapBaseIndex = 7,
        .priority = 2
    }
};
static const struct CompressedSpriteSheet gUnknown_085B2208 = {
    sUnknown_085B1F58, 0x2000, TAG_GFX_WALL_CLOCK_HAND
};
static const u32 filler_85B2210[2] = {};
static const struct SpritePalette gUnknown_085B2218[] = {
    { gWallclockMale_Pal, TAG_PAL_WALL_CLOCK_HAND },
    { gWallclockFemale_Pal, 0x1001 },
    {}
};
static const struct OamData Unknown_085B2230 = {
    .y = 0xa0,
    .size = 3,
    .priority = 1
};
static const union AnimCmd Unknown_085B2238[] = {
    ANIMCMD_FRAME(0, 30),
    ANIMCMD_END
};
static const union AnimCmd Unknown_085B2240[] = {
    ANIMCMD_FRAME(64, 30),
    ANIMCMD_END
};
static const union AnimCmd *const gUnknown_085B2248[] = {
    Unknown_085B2238
};
static const union AnimCmd *const gUnknown_085B224C[] = {
    Unknown_085B2240
};
static const struct SpriteTemplate gUnknown_085B2250 = {
    TAG_GFX_WALL_CLOCK_HAND,
    TAG_PAL_WALL_CLOCK_HAND,
    &Unknown_085B2230,
    gUnknown_085B2248,
    NULL,
    gDummySpriteAffineAnimTable,
    SpriteCB_MinuteHand
};
static const struct SpriteTemplate gUnknown_085B2268 = {
    TAG_GFX_WALL_CLOCK_HAND,
    TAG_PAL_WALL_CLOCK_HAND,
    &Unknown_085B2230,
    gUnknown_085B224C,
    NULL,
    gDummySpriteAffineAnimTable,
    SpriteCB_HourHand
};
static const struct OamData Unknown_085B2280 = {
    .y = 0xa0,
    .size = 1,
    .priority = 3
};
static const union AnimCmd Unknown_085B2288[] = {
    ANIMCMD_FRAME(0x84, 30),
    ANIMCMD_END
};
static const union AnimCmd Unknown_085B2290[] = {
    ANIMCMD_FRAME(0x80, 30),
    ANIMCMD_END
};
static const union AnimCmd *const gUnknown_085B2298[] = {
    Unknown_085B2288
};
static const union AnimCmd *const gUnknown_085B229C[] = {
    Unknown_085B2290
};
static const struct SpriteTemplate gUnknown_085B22A0 = {
    TAG_GFX_WALL_CLOCK_HAND,
    TAG_PAL_WALL_CLOCK_HAND,
    &Unknown_085B2280,
    gUnknown_085B2298,
    NULL,
    gDummySpriteAffineAnimTable,
    SpriteCB_AMIndicator
};
static const struct SpriteTemplate gUnknown_085B22B8 = {
    TAG_GFX_WALL_CLOCK_HAND,
    TAG_PAL_WALL_CLOCK_HAND,
    &Unknown_085B2280,
    gUnknown_085B229C,
    NULL,
    gDummySpriteAffineAnimTable,
    SpriteCB_PMIndicator
};
static const s8 sClockHandCoords[][2] = {
    { 0x00, -0x18},
    { 0x01, -0x19},
    { 0x01, -0x19},
    { 0x02, -0x19},
    { 0x02, -0x19},
    { 0x02, -0x19},
    { 0x03, -0x18},
    { 0x03, -0x19},
    { 0x04, -0x19},
    { 0x04, -0x19},
    { 0x04, -0x19},
    { 0x05, -0x19},
    { 0x05, -0x19},
    { 0x06, -0x18},
    { 0x06, -0x18},
    { 0x06, -0x18},
    { 0x07, -0x18},
    { 0x07, -0x18},
    { 0x07, -0x18},
    { 0x08, -0x18},
    { 0x08, -0x18},
    { 0x09, -0x18},
    { 0x09, -0x18},
    { 0x0a, -0x17},
    { 0x0a, -0x17},
    { 0x0b, -0x16},
    { 0x0b, -0x16},
    { 0x0b, -0x16},
    { 0x0c, -0x16},
    { 0x0c, -0x15},
    { 0x0d, -0x15},
    { 0x0d, -0x15},
    { 0x0d, -0x15},
    { 0x0e, -0x15},
    { 0x0e, -0x15},
    { 0x0e, -0x14},
    { 0x0e, -0x14},
    { 0x0f, -0x14},
    { 0x0f, -0x13},
    { 0x10, -0x13},
    { 0x10, -0x13},
    { 0x10, -0x13},
    { 0x10, -0x12},
    { 0x10, -0x12},
    { 0x11, -0x12},
    { 0x11, -0x11},
    { 0x11, -0x11},
    { 0x12, -0x11},
    { 0x12, -0x11},
    { 0x12, -0x10},
    { 0x12, -0x10},
    { 0x13, -0x10},
    { 0x13, -0x0f},
    { 0x13, -0x0f},
    { 0x14, -0x0f},
    { 0x14, -0x0e},
    { 0x14, -0x0e},
    { 0x14, -0x0d},
    { 0x14, -0x0d},
    { 0x15, -0x0d},
    { 0x15, -0x0d},
    { 0x15, -0x0c},
    { 0x16, -0x0c},
    { 0x16, -0x0c},
    { 0x16, -0x0b},
    { 0x16, -0x0b},
    { 0x16, -0x0a},
    { 0x17, -0x0a},
    { 0x17, -0x09},
    { 0x17, -0x09},
    { 0x17, -0x09},
    { 0x17, -0x09},
    { 0x17, -0x08},
    { 0x17, -0x08},
    { 0x17, -0x07},
    { 0x17, -0x07},
    { 0x17, -0x06},
    { 0x18, -0x06},
    { 0x18, -0x06},
    { 0x19, -0x05},
    { 0x19, -0x05},
    { 0x18, -0x04},
    { 0x19, -0x04},
    { 0x18, -0x03},
    { 0x19, -0x03},
    { 0x19, -0x03},
    { 0x19, -0x02},
    { 0x19, -0x02},
    { 0x18, -0x01},
    { 0x19, -0x01},
    { 0x18,  0x00},
    { 0x18,  0x00},
    { 0x18,  0x00},
    { 0x18,  0x01},
    { 0x18,  0x01},
    { 0x19,  0x02},
    { 0x18,  0x02},
    { 0x19,  0x02},
    { 0x18,  0x03},
    { 0x18,  0x03},
    { 0x19,  0x04},
    { 0x18,  0x04},
    { 0x18,  0x05},
    { 0x18,  0x05},
    { 0x18,  0x05},
    { 0x18,  0x06},
    { 0x17,  0x06},
    { 0x17,  0x06},
    { 0x17,  0x07},
    { 0x17,  0x08},
    { 0x17,  0x08},
    { 0x17,  0x08},
    { 0x17,  0x09},
    { 0x17,  0x09},
    { 0x17,  0x0a},
    { 0x16,  0x0a},
    { 0x16,  0x0a},
    { 0x16,  0x0b},
    { 0x16,  0x0b},
    { 0x16,  0x0b},
    { 0x16,  0x0c},
    { 0x15,  0x0c},
    { 0x15,  0x0c},
    { 0x15,  0x0d},
    { 0x14,  0x0d},
    { 0x14,  0x0d},
    { 0x13,  0x0d},
    { 0x13,  0x0d},
    { 0x13,  0x0e},
    { 0x13,  0x0e},
    { 0x13,  0x0f},
    { 0x13,  0x0f},
    { 0x12,  0x0f},
    { 0x12,  0x10},
    { 0x11,  0x10},
    { 0x11,  0x10},
    { 0x11,  0x11},
    { 0x11,  0x11},
    { 0x10,  0x11},
    { 0x10,  0x12},
    { 0x10,  0x12},
    { 0x0f,  0x12},
    { 0x0e,  0x12},
    { 0x0f,  0x13},
    { 0x0e,  0x13},
    { 0x0e,  0x13},
    { 0x0d,  0x13},
    { 0x0d,  0x14},
    { 0x0d,  0x14},
    { 0x0d,  0x14},
    { 0x0c,  0x14},
    { 0x0c,  0x14},
    { 0x0c,  0x15},
    { 0x0b,  0x15},
    { 0x0b,  0x15},
    { 0x0b,  0x15},
    { 0x0a,  0x15},
    { 0x0a,  0x16},
    { 0x0a,  0x16},
    { 0x09,  0x16},
    { 0x09,  0x16},
    { 0x08,  0x16},
    { 0x07,  0x16},
    { 0x07,  0x17},
    { 0x07,  0x17},
    { 0x06,  0x17},
    { 0x06,  0x17},
    { 0x05,  0x17},
    { 0x05,  0x17},
    { 0x05,  0x18},
    { 0x04,  0x18},
    { 0x04,  0x18},
    { 0x04,  0x18},
    { 0x03,  0x18},
    { 0x02,  0x18},
    { 0x02,  0x18},
    { 0x01,  0x18},
    { 0x01,  0x18},
    { 0x00,  0x18},
    { 0x00,  0x18},
    {-0x01,  0x17},
    { 0x00,  0x18},
    { 0x00,  0x18},
    {-0x01,  0x18},
    {-0x01,  0x18},
    {-0x02,  0x18},
    {-0x02,  0x18},
    {-0x03,  0x18},
    {-0x03,  0x18},
    {-0x04,  0x18},
    {-0x04,  0x18},
    {-0x05,  0x18},
    {-0x05,  0x17},
    {-0x05,  0x17},
    {-0x06,  0x17},
    {-0x06,  0x17},
    {-0x07,  0x17},
    {-0x07,  0x17},
    {-0x07,  0x17},
    {-0x08,  0x17},
    {-0x08,  0x16},
    {-0x09,  0x16},
    {-0x09,  0x16},
    {-0x0a,  0x16},
    {-0x0a,  0x16},
    {-0x0a,  0x15},
    {-0x0b,  0x15},
    {-0x0b,  0x15},
    {-0x0b,  0x15},
    {-0x0b,  0x14},
    {-0x0c,  0x14},
    {-0x0c,  0x14},
    {-0x0d,  0x14},
    {-0x0d,  0x14},
    {-0x0d,  0x13},
    {-0x0e,  0x13},
    {-0x0e,  0x13},
    {-0x0e,  0x13},
    {-0x0e,  0x12},
    {-0x0f,  0x12},
    {-0x0f,  0x12},
    {-0x0f,  0x11},
    {-0x10,  0x11},
    {-0x10,  0x11},
    {-0x11,  0x11},
    {-0x11,  0x10},
    {-0x11,  0x10},
    {-0x12,  0x10},
    {-0x11,  0x0f},
    {-0x12,  0x0f},
    {-0x12,  0x0f},
    {-0x13,  0x0f},
    {-0x13,  0x0e},
    {-0x13,  0x0e},
    {-0x13,  0x0d},
    {-0x13,  0x0d},
    {-0x14,  0x0d},
    {-0x14,  0x0c},
    {-0x14,  0x0c},
    {-0x15,  0x0c},
    {-0x15,  0x0c},
    {-0x15,  0x0b},
    {-0x15,  0x0b},
    {-0x15,  0x0a},
    {-0x15,  0x0a},
    {-0x15,  0x09},
    {-0x16,  0x09},
    {-0x16,  0x09},
    {-0x16,  0x08},
    {-0x16,  0x08},
    {-0x16,  0x07},
    {-0x17,  0x07},
    {-0x17,  0x07},
    {-0x17,  0x06},
    {-0x17,  0x06},
    {-0x17,  0x05},
    {-0x18,  0x05},
    {-0x17,  0x04},
    {-0x17,  0x04},
    {-0x18,  0x04},
    {-0x18,  0x04},
    {-0x18,  0x03},
    {-0x18,  0x03},
    {-0x18,  0x02},
    {-0x18,  0x02},
    {-0x18,  0x01},
    {-0x18,  0x01},
    {-0x18,  0x01},
    {-0x18,  0x00},
    {-0x19,  0x00},
    {-0x18, -0x01},
    {-0x19, -0x01},
    {-0x18, -0x01},
    {-0x18, -0x02},
    {-0x18, -0x02},
    {-0x18, -0x03},
    {-0x18, -0x03},
    {-0x18, -0x04},
    {-0x18, -0x04},
    {-0x18, -0x04},
    {-0x18, -0x05},
    {-0x18, -0x05},
    {-0x18, -0x06},
    {-0x18, -0x06},
    {-0x17, -0x06},
    {-0x17, -0x07},
    {-0x17, -0x07},
    {-0x17, -0x08},
    {-0x17, -0x08},
    {-0x17, -0x09},
    {-0x17, -0x09},
    {-0x16, -0x09},
    {-0x16, -0x09},
    {-0x16, -0x0a},
    {-0x16, -0x0a},
    {-0x15, -0x0a},
    {-0x15, -0x0b},
    {-0x16, -0x0b},
    {-0x16, -0x0c},
    {-0x15, -0x0c},
    {-0x15, -0x0d},
    {-0x15, -0x0d},
    {-0x14, -0x0d},
    {-0x15, -0x0e},
    {-0x14, -0x0e},
    {-0x14, -0x0e},
    {-0x13, -0x0e},
    {-0x13, -0x0f},
    {-0x13, -0x0f},
    {-0x12, -0x10},
    {-0x12, -0x10},
    {-0x12, -0x10},
    {-0x12, -0x11},
    {-0x12, -0x11},
    {-0x11, -0x11},
    {-0x11, -0x12},
    {-0x11, -0x12},
    {-0x10, -0x12},
    {-0x10, -0x12},
    {-0x10, -0x13},
    {-0x10, -0x13},
    {-0x0f, -0x13},
    {-0x0f, -0x13},
    {-0x0f, -0x14},
    {-0x0e, -0x14},
    {-0x0e, -0x14},
    {-0x0e, -0x15},
    {-0x0d, -0x15},
    {-0x0d, -0x15},
    {-0x0d, -0x15},
    {-0x0c, -0x15},
    {-0x0c, -0x16},
    {-0x0b, -0x16},
    {-0x0b, -0x16},
    {-0x0b, -0x16},
    {-0x0a, -0x16},
    {-0x0a, -0x16},
    {-0x09, -0x16},
    {-0x09, -0x17},
    {-0x09, -0x17},
    {-0x08, -0x17},
    {-0x08, -0x17},
    {-0x07, -0x17},
    {-0x07, -0x17},
    {-0x07, -0x18},
    {-0x06, -0x18},
    {-0x06, -0x18},
    {-0x05, -0x18},
    {-0x05, -0x18},
    {-0x04, -0x18},
    {-0x04, -0x18},
    {-0x04, -0x18},
    {-0x04, -0x19},
    {-0x03, -0x19},
    {-0x02, -0x19},
    {-0x02, -0x18},
    {-0x02, -0x18},
    {-0x01, -0x19},
    {-0x01, -0x19},
    { 0x00, -0x19}
};

// text

static void WallClockVblankCallback(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void LoadWallClockGraphics(void)
{
    SetVBlankCallback(NULL);
    SetGpuReg(REG_OFFSET_DISPCNT, 0x0000);
    SetGpuReg(REG_OFFSET_BG3CNT, 0x0000);
    SetGpuReg(REG_OFFSET_BG2CNT, 0x0000);
    SetGpuReg(REG_OFFSET_BG1CNT, 0x0000);
    SetGpuReg(REG_OFFSET_BG0CNT, 0x0000);
    ChangeBgX(0, 0, 0);
    ChangeBgY(0, 0, 0);
    ChangeBgX(1, 0, 0);
    ChangeBgY(1, 0, 0);
    ChangeBgX(2, 0, 0);
    ChangeBgY(2, 0, 0);
    ChangeBgX(3, 0, 0);
    ChangeBgY(3, 0, 0);
    DmaFillLarge16(3, 0, (void *)VRAM, VRAM_SIZE, 0x1000);
    DmaClear32(3, (void *)OAM, OAM_SIZE);
    DmaClear16(3, (void *)PLTT, PLTT_SIZE);
    LZ77UnCompVram(gWallclock_Gfx, (void *)VRAM);
    if (gSpecialVar_0x8004 == 0)
    {
        LoadPalette(gWallclockMale_Pal, 0x00, 0x20);
    }
    else
    {
        LoadPalette(gWallclockFemale_Pal, 0x00, 0x20);
    }
    LoadPalette(GetOverworldTextboxPalettePtr(), 0xe0, 0x20);
    LoadPalette(sUnknown_085B21D4, 0xc0, 0x08);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, gUnknown_085B21FC, 3);
    InitWindows(gUnknown_085B21DC);
    DeactivateAllTextPrinters();
    LoadUserWindowBorderGfx(0, 0x250, 0xd0);
    clear_scheduled_bg_copies_to_vram();
    ScanlineEffect_Stop();
    ResetTasks();
    ResetSpriteData();
    ResetPaletteFade();
    FreeAllSpritePalettes();
    LoadCompressedObjectPic(&gUnknown_085B2208);
    LoadSpritePalettes(gUnknown_085B2218);
}

static void WallClockInit(void)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, 0);
    EnableInterrupts(INTR_FLAG_VBLANK);
    SetVBlankCallback(WallClockVblankCallback);
    SetMainCallback2(WallClockMainCallback);
    SetGpuReg(REG_OFFSET_BLDCNT, 0x0000);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0x0000);
    SetGpuReg(REG_OFFSET_BLDY, 0x0000);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
    ShowBg(0);
    ShowBg(2);
    ShowBg(3);
}

void Cb2_StartWallClock(void)
{
    u8 taskId;
    u8 spriteId;

    LoadWallClockGraphics();
    LZ77UnCompVram(gUnknown_08DCC648, (u16 *)BG_SCREEN_ADDR(7));

    taskId = CreateTask(Task_SetClock1, 0);
    gTasks[taskId].tHours = 10;
    gTasks[taskId].tMinutes = 0;
    gTasks[taskId].tMvmtDir = 0;
    gTasks[taskId].tPeriod = 0;
    gTasks[taskId].tMvmtSpeed = 0;
    gTasks[taskId].tMinuteHandAngle = 0;
    gTasks[taskId].tHourHandAngle = 300;

    spriteId = CreateSprite(&gUnknown_085B2250, 0x78, 0x50, 1);
    gSprites[spriteId].data[0] = taskId;
    gSprites[spriteId].oam.affineMode = ST_OAM_AFFINE_NORMAL;
    gSprites[spriteId].oam.matrixNum = 0;

    spriteId = CreateSprite(&gUnknown_085B2268, 0x78, 0x50, 0);
    gSprites[spriteId].data[0] = taskId;
    gSprites[spriteId].oam.affineMode = ST_OAM_AFFINE_NORMAL;
    gSprites[spriteId].oam.matrixNum = 1;

    spriteId = CreateSprite(&gUnknown_085B22A0, 0x78, 0x50, 2);
    gSprites[spriteId].data[0] = taskId;
    gSprites[spriteId].data[1] = 45;

    spriteId = CreateSprite(&gUnknown_085B22B8, 0x78, 0x50, 2);
    gSprites[spriteId].data[0] = taskId;
    gSprites[spriteId].data[1] = 90;

    WallClockInit();

    PrintTextOnWindow(1, 1, gText_Confirm3, 0, 1, 0, NULL);
    PutWindowTilemap(1);
    schedule_bg_copy_tilemap_to_vram(2);
}

void Cb2_ViewWallClock(void)
{
    u8 taskId;
    u8 spriteId;
    u8 angle1;
    u8 angle2;

    LoadWallClockGraphics();
    LZ77UnCompVram(gUnknown_08DCC908, (u16 *)BG_SCREEN_ADDR(7));

    taskId = CreateTask(Task_ViewClock1, 0);
    InitClockWithRtc(taskId);
    if (gTasks[taskId].tPeriod == 0)
    {
        angle1 = 45;
        angle2 = 90;
    }
    else
    {
        angle1 = 90;
        angle2 = 135;
    }

    spriteId = CreateSprite(&gUnknown_085B2250, 0x78, 0x50, 1);
    gSprites[spriteId].data[0] = taskId;
    gSprites[spriteId].oam.affineMode = ST_OAM_AFFINE_NORMAL;
    gSprites[spriteId].oam.matrixNum = 0;

    spriteId = CreateSprite(&gUnknown_085B2268, 0x78, 0x50, 0);
    gSprites[spriteId].data[0] = taskId;
    gSprites[spriteId].oam.affineMode = ST_OAM_AFFINE_NORMAL;
    gSprites[spriteId].oam.matrixNum = 1;

    spriteId = CreateSprite(&gUnknown_085B22A0, 0x78, 0x50, 2);
    gSprites[spriteId].data[0] = taskId;
    gSprites[spriteId].data[1] = angle1;

    spriteId = CreateSprite(&gUnknown_085B22B8, 0x78, 0x50, 2);
    gSprites[spriteId].data[0] = taskId;
    gSprites[spriteId].data[1] = angle2;

    WallClockInit();

    PrintTextOnWindow(1, 1, gText_Cancel4, 0, 1, 0, NULL);
    PutWindowTilemap(1);
    schedule_bg_copy_tilemap_to_vram(2);
}

static void WallClockMainCallback(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    do_scheduled_bg_tilemap_copies_to_vram();
    UpdatePaletteFade();
}

static void Task_SetClock1(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        gTasks[taskId].func = Task_SetClock2;
    }
}

static void Task_SetClock2(u8 taskId)
{
    if (gTasks[taskId].tMinuteHandAngle % 6)
    {
        gTasks[taskId].tMinuteHandAngle = CalcNewMinHandAngle(gTasks[taskId].tMinuteHandAngle, gTasks[taskId].tMvmtDir, gTasks[taskId].tMvmtSpeed);
    }
    else
    {
        gTasks[taskId].tMinuteHandAngle = gTasks[taskId].tMinutes * 6;
        gTasks[taskId].tHourHandAngle = (gTasks[taskId].tHours % 12) * 30 + (gTasks[taskId].tMinutes / 10) * 5;
        if (gMain.newKeys & A_BUTTON)
        {
            gTasks[taskId].func = Task_SetClock3;
        }
        else
        {
            gTasks[taskId].tMvmtDir = 0;
            if (gMain.heldKeys & DPAD_LEFT)
            {
                gTasks[taskId].tMvmtDir = 1;
            }
            if (gMain.heldKeys & DPAD_RIGHT)
            {
                gTasks[taskId].tMvmtDir = 2;
            }
            if (gTasks[taskId].tMvmtDir != 0)
            {
                if (gTasks[taskId].tMvmtSpeed < 0xFF)
                {
                    gTasks[taskId].tMvmtSpeed++;
                }
                gTasks[taskId].tMinuteHandAngle = CalcNewMinHandAngle(gTasks[taskId].tMinuteHandAngle, gTasks[taskId].tMvmtDir, gTasks[taskId].tMvmtSpeed);
                AdvanceClock(taskId, gTasks[taskId].tMvmtDir);
            }
            else
            {
                gTasks[taskId].tMvmtSpeed = 0;
            }
        }
    }
}

static void Task_SetClock3(u8 taskId)
{
    SetWindowBorderStyle(0, FALSE, 0x250, 0x0d);
    PrintTextOnWindow(0, 1, gText_IsThisTheCorrectTime, 0, 1, 0, NULL);
    PutWindowTilemap(0);
    schedule_bg_copy_tilemap_to_vram(0);
    CreateYesNoMenu(&gUnknown_085B21F4, 0x250, 0x0d, 1);
    gTasks[taskId].func = Task_SetClock4;
}

static void Task_SetClock4(u8 taskId)
{
    switch (ProcessMenuInputNoWrap_())
    {
        case 0:
            PlaySE(SE_SELECT);
            gTasks[taskId].func = Task_SetClock5;
            break;
        case 1:
        case -1:
            PlaySE(SE_SELECT);
            sub_8198070(0, FALSE);
            ClearWindowTilemap(0);
            gTasks[taskId].func = Task_SetClock2;
            break;
    }
}

static void Task_SetClock5(u8 taskId)
{
    RtcInitLocalTimeOffset(gTasks[taskId].tHours, gTasks[taskId].tMinutes);
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0);
    gTasks[taskId].func = Task_SetClock6;
}

static void Task_SetClock6(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        FreeAllWindowBuffers();
        SetMainCallback2(gMain.savedCallback);
    }
}

static void Task_ViewClock1(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        gTasks[taskId].func = Task_ViewClock2;
    }
}

static void Task_ViewClock2(u8 taskId)
{
    InitClockWithRtc(taskId);
    if (gMain.newKeys & (A_BUTTON | B_BUTTON))
    {
        gTasks[taskId].func = Task_ViewClock3;
    }
}

static void Task_ViewClock3(u8 taskId)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0);
    gTasks[taskId].func = Task_ViewClock4;
}

static void Task_ViewClock4(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(gMain.savedCallback);
    }
}

static u8 CalcMinHandDelta(u16 a0)
{
    if (a0 > 60)
    {
        return 6;
    }
    if (a0 > 30)
    {
        return 3;
    }
    if (a0 > 10)
    {
        return 2;
    }
    return 1;
}

static u16 CalcNewMinHandAngle(u16 a0, u8 command, u8 a2)
{
    u8 r1 = CalcMinHandDelta(a2);
    switch (command)
    {
        case 1:
            if (a0) a0 -= r1;
            else a0 = 360 - r1;
            break;
        case 2:
            if (a0 < 360 - r1) a0 += r1;
            else a0 = 0;
            break;
    }
    return a0;
}

static bool32 AdvanceClock(u8 taskId, u8 command)
{
    switch (command)
    {
        case 1:
            if (gTasks[taskId].tMinutes > 0)
            {
                gTasks[taskId].tMinutes--;
            }
            else
            {
                gTasks[taskId].tMinutes = 59;
                if (gTasks[taskId].tHours > 0)
                {
                    gTasks[taskId].tHours--;
                }
                else
                {
                    gTasks[taskId].tHours = 23;
                }
                UpdateClockPeriod(taskId, command);
            }
            break;
        case 2:
            if (gTasks[taskId].tMinutes < 59)
            {
                gTasks[taskId].tMinutes++;
            }
            else
            {
                gTasks[taskId].tMinutes = 0;
                if (gTasks[taskId].tHours < 23)
                {
                    gTasks[taskId].tHours++;
                }
                else
                {
                    gTasks[taskId].tHours = 0;
                }
                UpdateClockPeriod(taskId, command);
            }
            break;
    }
    return FALSE;
}

static void UpdateClockPeriod(u8 taskId, u8 command)
{
    u8 hours = gTasks[taskId].tHours;
    switch (command)
    {
        case 1:
            switch (hours)
            {
                case 11:
                    gTasks[taskId].tPeriod = FALSE;
                    break;
                case 23:
                    gTasks[taskId].tPeriod = TRUE;
                    break;
            }
            break;
        case 2:
            switch (hours)
            {
                case 0:
                    gTasks[taskId].tPeriod = FALSE;
                    break;
                case 12:
                    gTasks[taskId].tPeriod = TRUE;
                    break;
            }
            break;
    }
}

static void InitClockWithRtc(u8 taskId)
{
    RtcCalcLocalTime();
    gTasks[taskId].tHours = gLocalTime.hours;
    gTasks[taskId].tMinutes = gLocalTime.minutes;
    gTasks[taskId].tMinuteHandAngle = gTasks[taskId].tMinutes * 6;
    gTasks[taskId].tHourHandAngle = (gTasks[taskId].tHours % 12) * 30 + (gTasks[taskId].tMinutes / 10) * 5;
    if (gLocalTime.hours < 12)
    {
        gTasks[taskId].tPeriod = FALSE;
    }
    else
    {
        gTasks[taskId].tPeriod = TRUE;
    }
}

static void SpriteCB_MinuteHand(struct Sprite *sprite)
{
    u16 angle = gTasks[sprite->data[0]].tMinuteHandAngle;
    s16 sin = Sin2(angle) / 16;
    s16 cos = Cos2(angle) / 16;
    u16 xhat;
    u16 yhat;

    SetOamMatrix(0, cos, sin, -sin, cos);
    xhat = sClockHandCoords[angle][0];
    yhat = sClockHandCoords[angle][1];

    if (xhat > 0x80)
    {
        xhat |= 0xff00;
    }
    if (yhat > 0x80)
    {
        yhat |= 0xff00;
    }
    sprite->pos2.x = xhat;
    sprite->pos2.y = yhat;
}

static void SpriteCB_HourHand(struct Sprite *sprite)
{
    u16 angle = gTasks[sprite->data[0]].tHourHandAngle;
    s16 sin = Sin2(angle) / 16;
    s16 cos = Cos2(angle) / 16;
    u16 xhat;
    u16 yhat;

    SetOamMatrix(1, cos, sin, -sin, cos);
    xhat = sClockHandCoords[angle][0];
    yhat = sClockHandCoords[angle][1];
    if (xhat > 0x80)
    {
        xhat |= 0xff00;
    }
    if (yhat > 0x80)
    {
        yhat |= 0xff00;
    }
    sprite->pos2.x = xhat;
    sprite->pos2.y = yhat;
}

static void SpriteCB_AMIndicator(struct Sprite *sprite)
{
    if (gTasks[sprite->data[0]].tPeriod)
    {
        if (sprite->data[1] >= 60 && sprite->data[1] < 90)
        {
            sprite->data[1] += 5;
        }
        if (sprite->data[1] < 60)
        {
            sprite->data[1]++;
        }
    }
    else
    {
        if (sprite->data[1] >= 46 && sprite->data[1] < 76)
        {
            sprite->data[1] -= 5;
        }
        if (sprite->data[1] > 75)
        {
            sprite->data[1]--;
        }
    }
    sprite->pos2.x = Cos2(sprite->data[1]) * 30 / 0x1000;
    sprite->pos2.y = Sin2(sprite->data[1]) * 30 / 0x1000;
}

static void SpriteCB_PMIndicator(struct Sprite *sprite)
{
    if (gTasks[sprite->data[0]].tPeriod)
    {
        if (sprite->data[1] >= 105 && sprite->data[1] < 135)
        {
            sprite->data[1] += 5;
        }
        if (sprite->data[1] < 105)
        {
            sprite->data[1]++;
        }
    }
    else
    {
        if (sprite->data[1] >= 91 && sprite->data[1] < 121)
        {
            sprite->data[1] -= 5;
        }
        if (sprite->data[1] > 120)
        {
            sprite->data[1]--;
        }
    }
    sprite->pos2.x = Cos2(sprite->data[1]) * 30 / 0x1000;
    sprite->pos2.y = Sin2(sprite->data[1]) * 30 / 0x1000;
}
