
// Includes
#include "global.h"
#include "main.h"
#include "malloc.h"
#include "gpu_regs.h"
#include "bg.h"
#include "text.h"
#include "window.h"
#include "text_window.h"
#include "palette.h"
#include "menu.h"
#include "strings.h"
#include "international_string_util.h"
#include "region_map.h"

// Static type declarations

// Static RAM declarations

static EWRAM_DATA struct {
    MainCallback callback;
    u32 filler_004;
    struct RegionMap regionMap;
    u16 state;
} *sFieldRegionMapHandler = NULL;

// Static ROM declarations

static void MCB2_InitRegionMapRegisters(void);
static void VBCB_FieldUpdateRegionMap(void);
static void MCB2_FieldUpdateRegionMap(void);
static void FieldUpdateRegionMap(void);
static void PrintRegionMapSecName(void);

// .rodata

static const struct BgTemplate gUnknown_085E5068[] = {
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    }, {
        .bg = 2,
        .charBaseIndex = 2,
        .mapBaseIndex = 28,
        .screenSize = 2,
        .paletteMode = 1,
        .priority = 2,
        .baseTile = 0
    }
};

static const struct WindowTemplate gUnknown_085E5070[] = {
    { 0, 17, 17, 12,  2, 15, 0x0001 },
    { 0, 22,  1,  7,  2, 15, 0x0019 },
    DUMMY_WIN_TEMPLATE
};

// .text

void sub_817018C(MainCallback callback)
{
    SetVBlankCallback(NULL);
    sFieldRegionMapHandler = malloc(sizeof(*sFieldRegionMapHandler));
    sFieldRegionMapHandler->state = 0;
    sFieldRegionMapHandler->callback = callback;
    SetMainCallback2(MCB2_InitRegionMapRegisters);
}

static void MCB2_InitRegionMapRegisters(void)
{
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_BG0HOFS, 0);
    SetGpuReg(REG_OFFSET_BG0VOFS, 0);
    SetGpuReg(REG_OFFSET_BG1HOFS, 0);
    SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    SetGpuReg(REG_OFFSET_BG2HOFS, 0);
    SetGpuReg(REG_OFFSET_BG2VOFS, 0);
    SetGpuReg(REG_OFFSET_BG3HOFS, 0);
    SetGpuReg(REG_OFFSET_BG3VOFS, 0);
    ResetSpriteData();
    FreeAllSpritePalettes();
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(1, gUnknown_085E5068, 2);
    InitWindows(gUnknown_085E5070);
    DeactivateAllTextPrinters();
    LoadUserWindowBorderGfx(0, 0x27, 0xd0);
    clear_scheduled_bg_copies_to_vram();
    SetMainCallback2(MCB2_FieldUpdateRegionMap);
    SetVBlankCallback(VBCB_FieldUpdateRegionMap);
}

static void VBCB_FieldUpdateRegionMap(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void MCB2_FieldUpdateRegionMap(void)
{
    FieldUpdateRegionMap();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
    do_scheduled_bg_tilemap_copies_to_vram();
}

static void FieldUpdateRegionMap(void)
{
    u8 offset;

    switch (sFieldRegionMapHandler->state)
    {
        case 0:
            InitRegionMap(&sFieldRegionMapHandler->regionMap, 0);
            CreateRegionMapPlayerIcon(0, 0);
            CreateRegionMapCursor(1, 1);
            sFieldRegionMapHandler->state++;
            break;
        case 1:
            SetWindowBorderStyle(1, 0, 0x27, 0xd);
            offset = GetStringCenterAlignXOffset(1, gText_Hoenn, 0x38);
            PrintTextOnWindow(1, 1, gText_Hoenn, offset, 1, 0, NULL);
            schedule_bg_copy_tilemap_to_vram(0);
            SetWindowBorderStyle(0, 0, 0x27, 0xd);
            PrintRegionMapSecName();
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, 0);
            sFieldRegionMapHandler->state++;
            break;
        case 2:
            SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
            ShowBg(0);
            ShowBg(2);
            sFieldRegionMapHandler->state++;
            break;
        case 3:
            if (!gPaletteFade.active)
            {
                sFieldRegionMapHandler->state++;
            }
            break;
        case 4:
            switch (sub_81230AC())
            {
                case INPUT_EVENT_MOVE_END:
                    PrintRegionMapSecName();
                    break;
                case INPUT_EVENT_A_BUTTON:
                case INPUT_EVENT_B_BUTTON:
                    sFieldRegionMapHandler->state++;
                    break;
            }
            break;
        case 5:
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0);
            sFieldRegionMapHandler->state++;
            break;
        case 6:
            if (!gPaletteFade.active)
            {
                FreeRegionMapIconResources();
                SetMainCallback2(sFieldRegionMapHandler->callback);
                if (sFieldRegionMapHandler != NULL)
                {
                    free(sFieldRegionMapHandler);
                    sFieldRegionMapHandler = NULL;
                }
                FreeAllWindowBuffers();
            }
            break;
    }
}

static void PrintRegionMapSecName(void)
{
    if (sFieldRegionMapHandler->regionMap.iconDrawType != MAPSECTYPE_NONE)
    {
        FillWindowPixelBuffer(0, 0x11);
        PrintTextOnWindow(0, 1, sFieldRegionMapHandler->regionMap.mapSecName, 0, 1, 0, NULL);
        schedule_bg_copy_tilemap_to_vram(0);
    }
    else
    {
        FillWindowPixelBuffer(0, 0x11);
        CopyWindowToVram(0, 3);
    }
}
