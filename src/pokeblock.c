#include "global.h"
#include "pokeblock.h"
#include "bg.h"
#include "strings.h"
#include "text.h"
#include "menu.h"
#include "task.h"
#include "menu_helpers.h"
#include "pokemon.h"
#include "graphics.h"
#include "malloc.h"
#include "main.h"
#include "battle.h"
#include "battle_controllers.h"
#include "palette.h"
#include "scanline_effect.h"
#include "list_menu.h"
#include "gpu_regs.h"
#include "decompress.h"
#include "international_string_util.h"
#include "item.h"
#include "constants/items.h"
#include "string_util.h"
#include "constants/songs.h"
#include "sound.h"
#include "berry.h"
#include "event_data.h"
#include "battle_message.h"
#include "safari_zone.h"
#include "lilycove_lady.h"
#include "overworld.h"

#define POKEBLOCK_MAX_FEEL 99
#define FIELD_E75_COUNT 7

struct PokeblockMenuStruct
{
    u8 tilemap[0x800];
    void (*callbackOnUse)(void);
    const u8 *pokeblockOptionsIds;
    u8 optionsNo;
    u8 caseId;
    u8 itemsNo;
    u8 maxShowed;
    struct ListMenuItem items[POKEBLOCKS_COUNT + 1];
    u8 menuItemsStrings[POKEBLOCKS_COUNT + 1][0x20]; // + 1 because of STOW CASE item
    u8 pokeblockCaseSpriteId;
    u8 field_E75[FIELD_E75_COUNT];
    u8 unkTaskId;
    bool8 isSwapping;
    s16 gfxState;
    u8 unused[8];
};

struct PokeblockSavedData
{
    void (*callback)(void);
    u16 lastItemPos;
    u16 lastItemPage;
};

enum
{
    PKBL_USE_ON_FIELD,
    PKBL_TOSS,
    PKBL_CANCEL,
    PKBL_USE_IN_BATTLE,
    PKBL_USE_ON_FEEDER,
    PKBL_GIVE_TO_LADY
};

extern u16 gSpecialVar_ItemId;

extern const u16 gUnknown_0860F074[];

extern void CB2_ReturnToField(void);
extern bool8 sub_81221EC(void);
extern void LoadUserWindowBorderGfx(u8, u16, u8);
extern void copy_textbox_border_tile_patterns_to_vram(u8, u16, u8);
extern void sub_80AF168(void);

// this file's functions
static void CB2_InitPokeblockMenu(void);
static bool8 InitPokeblockMenu(void);
static bool8 LoadPokeblockMenuGfx(void);
static void HandleInitBackgrounds(void);
static void HandleInitWindows(void);
static void SetMenuItemsCountAndMaxShowed(void);
static void sub_81362E0(void);
static void sub_8136344(void);
static void HandlePokeblockListMenuItems(void);
static void sub_81363BC(void);
static void MovePokeblockMenuCursor(s32 pkblId, bool8 arg1, struct ListMenu *arg2);
static void PutPokeblockInfoText(void);
static void HandlePokeblockMenuCursor(u16 cursorPos, u16 arg1);
static void PutPokeblockListMenuString(u8 *dst, u16 pkblId);
static void Task_HandlePokeblockMenuInput(u8 taskId);
static void PokeblockAction_UseOnField(u8 taskId);
static void PokeblockAction_Toss(u8 taskId);
static void PokeblockAction_Cancel(u8 taskId);
static void PokeblockAction_UseInBattle(u8 taskId);
static void PokeblockAction_UseOnPokeblockFeeder(u8 taskId);
static void PokeblockAction_GiveToContestLady(u8 taskId);
static void TossPokeblockChoice_Yes(u8 taskId);
static void TossPokeblockChoice_No(u8 taskId);
static void Task_FreeDataAndExitPokeblockCase(u8 taskId);
static void Task_HandlePokeblockOptionsInput(u8 taskId);
static void PutPokeblockOptionsWindow(u8 taskId);
static void Task_HandlePokeblocksSwapInput(u8 taskId);
static void sub_8136470(struct Sprite *sprite);
static void sub_8135FCC(s32 pkblId);
static void HandlePokeblocksSwap(u8 taskId, bool8 noSwap);
static void UsePokeblockOnField(void);
static void ReturnToPokeblockCaseOnField(void);
static void CreateTossPokeblockYesNoMenu(u8 taskId);
static void HandleErasePokeblock(u8 taskId);

// ram variables
EWRAM_DATA static struct PokeblockSavedData sSavedPokeblockData = {0};
EWRAM_DATA static struct PokeblockMenuStruct *sPokeblockMenu = NULL;

// const rom data
const s8 gPokeblockFlavorCompatibilityTable[] =
{
    // Cool, Beauty, Cute, Smart, Tough
          0,      0,    0,     0,     0, // Hardy
          1,      0,    0,     0,    -1, // Lonely
          1,      0,   -1,     0,     0, // Brave
          1,     -1,    0,     0,     0, // Adamant
          1,      0,    0,    -1,     0, // Naughty
         -1,      0,    0,     0,     1, // Bold
          0,      0,    0,     0,     0, // Docile
          0,      0,   -1,     0,     1, // Relaxed
          0,     -1,    0,     0,     1, // Impish
          0,      0,    0,    -1,     1, // Lax
         -1,      0,    1,     0,     0, // Timid
          0,      0,    1,     0,    -1, // Hasty
          0,      0,    0,     0,     0, // Serious
          0,     -1,    1,     0,     0, // Jolly
          0,      0,    1,    -1,     0, // Naive
         -1,      1,    0,     0,     0, // Modest
          0,      1,    0,     0,    -1, // Mild
          0,      1,   -1,     0,     0, // Quiet
          0,      0,    0,     0,     0, // Bashful
          0,      1,    0,    -1,     0, // Rash
         -1,      0,    0,     1,     0, // Calm
          0,      0,    0,     1,    -1, // Gentle
          0,      0,   -1,     1,     0, // Sassy
          0,     -1,    0,     1,     0, // Careful
          0,      0,    0,     0,     0  // Quirky
};

static const struct BgTemplate sBgTemplatesForPokeblockMenu[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    },
    {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 3,
        .mapBaseIndex = 29,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0
    }
};

const u8 *const gPokeblockNames[] =
{
    NULL,
    gText_RedPokeblock,
    gText_BluePokeblock,
    gText_PinkPokeblock,
    gText_GreenPokeblock,
    gText_YellowPokeblock,
    gText_PurplePokeblock,
    gText_IndigoPokeblock,
    gText_BrownPokeblock,
    gText_LiteBluePokeblock,
    gText_OlivePokeblock,
    gText_GrayPokeblock,
    gText_BlackPokeblock,
    gText_WhitePokeblock,
    gText_GoldPokeblock
};

static const struct MenuAction sPokeblockMenuActions[] =
{
    {gMenuText_Use, PokeblockAction_UseOnField},
    {gMenuText_Toss, PokeblockAction_Toss},
    {gText_Cancel2, PokeblockAction_Cancel},
    {gMenuText_Use, PokeblockAction_UseInBattle},
    {gMenuText_Use, PokeblockAction_UseOnPokeblockFeeder},
    {gMenuText_Give2, PokeblockAction_GiveToContestLady},
};

static const u8 sActionsOnField[] = {PKBL_USE_ON_FIELD, PKBL_TOSS, PKBL_CANCEL};
static const u8 sActionsInBattle[] = {PKBL_USE_IN_BATTLE, PKBL_CANCEL};
static const u8 sActionsOnPokeblockFeeder[] = {PKBL_USE_ON_FEEDER, PKBL_CANCEL};
static const u8 sActionsWhenGivingToLady[] = {PKBL_GIVE_TO_LADY, PKBL_CANCEL};

static const struct YesNoFuncTable sTossYesNoFuncTable = {TossPokeblockChoice_Yes, TossPokeblockChoice_No};

static const u8 sContestStatsMonData[] = {MON_DATA_COOL, MON_DATA_BEAUTY, MON_DATA_CUTE, MON_DATA_SMART, MON_DATA_TOUGH};

static const struct OamData sOamData_PokeblockCase =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 0,
    .x = 0,
    .matrixNum = 0,
    .size = 3,
    .tileNum = 0,
    .priority = 2,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sSpriteAnim_PokeblockCase[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_PokeblockCase[] =
{
    sSpriteAnim_PokeblockCase
};

static const union AffineAnimCmd sSpriteAffineAnim_85B26C8[] =
{
    AFFINEANIMCMD_FRAME(0, 0, -2,  2),
    AFFINEANIMCMD_FRAME(0, 0,  2,  4),
    AFFINEANIMCMD_FRAME(0, 0, -2,  4),
    AFFINEANIMCMD_FRAME(0, 0,  2,  2),
    AFFINEANIMCMD_END
};

static const union AffineAnimCmd *const sSpriteAffineAnimTable_85B26F0[] =
{
    sSpriteAffineAnim_85B26C8
};

const struct CompressedSpriteSheet gPokeblockCase_SpriteSheet =
{
    gMenuPokeblockDevice_Gfx, 0x800, GFX_TAG_POKEBLOCK_CASE
};

const struct CompressedSpritePalette gPokeblockCase_SpritePal =
{
    gMenuPokeblockDevice_Pal, GFX_TAG_POKEBLOCK_CASE
};

static const struct SpriteTemplate sSpriteTemplate_PokeblockCase =
{
    GFX_TAG_POKEBLOCK_CASE,
    GFX_TAG_POKEBLOCK_CASE,
    &sOamData_PokeblockCase,
    sSpriteAnimTable_PokeblockCase,
    NULL,
    gDummySpriteAffineAnimTable,
    SpriteCallbackDummy
};

static const u8 sTextColorInPokeblockMenu[3] = {0, 2, 3};

static const struct Pokeblock sFavoritePokeblocksTable[] =
{
    { PBLOCK_CLR_RED,    20,  0,  0,  0,  0, 20},
    { PBLOCK_CLR_BLUE,    0, 20,  0,  0,  0, 20},
    { PBLOCK_CLR_PINK,    0,  0, 20,  0,  0, 20},
    { PBLOCK_CLR_GREEN,   0,  0,  0, 20,  0, 20},
    { PBLOCK_CLR_YELLOW,  0,  0,  0,  0, 20, 20}
};

static const struct WindowTemplate sWindowTemplatesForPokeblockMenu[] =
{
    {0, 2, 1, 9, 2, 0xF, 0x1E},
    {0, 0xF, 1, 0xE, 0x12, 0xF, 0x30},
    {0, 2, 0xD, 5, 2, 0xF, 0x12C},
    {0, 2, 0xF, 5, 2, 0xF, 0x136},
    {0, 2, 0x11, 5, 2, 0xF, 0x140},
    {0, 8, 0xD, 5, 2, 0xF, 0x14A},
    {0, 8, 0xF, 5, 2, 0xF, 0x154},
    {0, 0xB, 0x11, 2, 2, 0xF, 0x15E},
    {1, 7, 5, 6, 6, 0xF, 0x162},
    {1, 7, 7, 6, 4, 0xF, 0x186},
    {1, 2, 0xF, 0x1B, 4, 0xF, 0x19E},
    DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sTossPkblockWindowTemplate = {1, 0x15, 9, 5, 4, 0xF, 0x20A};

static const struct ListMenuTemplate sPokeblockListMenuTemplate =
{
    .items = NULL,
    .moveCursorFunc = MovePokeblockMenuCursor,
    .itemPrintFunc = NULL,
    .totalItems = 0,
    .maxShowed = 0,
    .windowId = 1,
    .header_X = 0,
    .item_X = 1,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 0,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_MULTIPLE_SCROLL_DPAD,
    .fontId = 1,
    .cursorKind = 1
};

// code
void OpenPokeblockCase(u8 caseId, void (*callback)(void))
{
    sPokeblockMenu = Alloc(sizeof(*sPokeblockMenu));
    sPokeblockMenu->caseId = caseId;
    sPokeblockMenu->callbackOnUse = NULL;
    sPokeblockMenu->unkTaskId = 0xFF;
    sPokeblockMenu->isSwapping = FALSE;
    sSavedPokeblockData.callback = callback;

    switch (sPokeblockMenu->caseId)
    {
    case PBLOCK_CASE_BATTLE:
        sPokeblockMenu->pokeblockOptionsIds = sActionsInBattle;
        sPokeblockMenu->optionsNo = ARRAY_COUNT(sActionsInBattle);
        break;
    case PBLOCK_CASE_FEEDER:
        sPokeblockMenu->pokeblockOptionsIds = sActionsOnPokeblockFeeder;
        sPokeblockMenu->optionsNo = ARRAY_COUNT(sActionsOnPokeblockFeeder);
        break;
    case PBLOCK_CASE_GIVE:
        sPokeblockMenu->pokeblockOptionsIds = sActionsWhenGivingToLady;
        sPokeblockMenu->optionsNo = ARRAY_COUNT(sActionsWhenGivingToLady);
        break;
    default:
        sPokeblockMenu->pokeblockOptionsIds = sActionsOnField;
        sPokeblockMenu->optionsNo = ARRAY_COUNT(sActionsOnField);
        break;
    }

    SetMainCallback2(CB2_InitPokeblockMenu);
}

void OpenPokeblockCaseInBattle(void)
{
    OpenPokeblockCase(PBLOCK_CASE_BATTLE, SetCB2ToReshowScreenAfterMenu2);
}

void OpenPokeblockCaseOnFeeder(void)
{
    OpenPokeblockCase(PBLOCK_CASE_FEEDER, CB2_ReturnToField);
}

static void CB2_PokeblockMenu(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    do_scheduled_bg_tilemap_copies_to_vram();
    UpdatePaletteFade();
}

static void VBlankCB_PokeblockMenu(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void CB2_InitPokeblockMenu(void)
{
    while (1)
    {
        if (sub_81221EC() == TRUE)
            break;
        if (InitPokeblockMenu() == TRUE)
            break;
        if (sub_81221AC() == TRUE)
            break;
    }
}

static bool8 InitPokeblockMenu(void)
{
    u8 taskId;

    switch (gMain.state)
    {
    case 0:
        SetVBlankHBlankCallbacksToNull();
        clear_scheduled_bg_copies_to_vram();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        gMain.state++;
        break;
    case 2:
        FreeAllSpritePalettes();
        gMain.state++;
        break;
    case 3:
        ResetPaletteFade();
        gPaletteFade.bufferTransferDisabled = 1;
        gMain.state++;
        break;
    case 4:
        ResetSpriteData();
        gMain.state++;
        break;
    case 5:
        if (sPokeblockMenu->caseId != PBLOCK_CASE_BATTLE)
            ResetTasks();
        gMain.state++;
        break;
    case 6:
        HandleInitBackgrounds();
        sPokeblockMenu->gfxState = 0;
        gMain.state++;
        break;
    case 7:
        if (!LoadPokeblockMenuGfx())
            return FALSE;
        gMain.state++;
        break;
    case 8:
        SetMenuItemsCountAndMaxShowed();
        sub_81362E0();
        sub_8136344();
        gMain.state++;
        break;
    case 9:
        sPokeblockMenu->pokeblockCaseSpriteId = CreatePokeblockCaseSprite(56, 64, 0);
        gMain.state++;
        break;
    case 10:
        sub_8122344(sPokeblockMenu->field_E75, FIELD_E75_COUNT);
        gMain.state++;
        break;
    case 11:
        HandlePokeblockMenuCursor(sSavedPokeblockData.lastItemPos, 0x1005);
        gMain.state++;
        break;
    case 12:
        HandleInitWindows();
        gMain.state++;
        break;
    case 13:
        HandlePokeblockListMenuItems();
        gMain.state++;
        break;
    case 14:
        sub_81363BC();
        gMain.state++;
        break;
    case 15:
        taskId = CreateTask(Task_HandlePokeblockMenuInput, 0);
        gTasks[taskId].data[0] = ListMenuInit(&gMultiuseListMenuTemplate, sSavedPokeblockData.lastItemPage, sSavedPokeblockData.lastItemPos);
        gMain.state++;
        break;
    case 16:
        PutPokeblockInfoText();
        gMain.state++;
        break;
    case 17:
        BlendPalettes(-1, 0x10, 0);
        gMain.state++;
        break;
    case 18:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0x10, 0, 0);
        gPaletteFade.bufferTransferDisabled = 0;
        gMain.state++;
        break;
    default:
        SetVBlankCallback(VBlankCB_PokeblockMenu);
        SetMainCallback2(CB2_PokeblockMenu);
        return TRUE;
    }

    return FALSE;
}

static void HandleInitBackgrounds(void)
{
    ResetVramOamAndBgCntRegs();
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sBgTemplatesForPokeblockMenu, ARRAY_COUNT(sBgTemplatesForPokeblockMenu));
    SetBgTilemapBuffer(2, sPokeblockMenu->tilemap);
    ResetAllBgsCoordinates();
    schedule_bg_copy_tilemap_to_vram(2);

    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);

    ShowBg(0);
    ShowBg(1);
    ShowBg(2);

    SetGpuReg(REG_OFFSET_BLDCNT, 0);
}

static bool8 LoadPokeblockMenuGfx(void)
{
    switch (sPokeblockMenu->gfxState)
    {
    case 0:
        reset_temp_tile_data_buffers();
        decompress_and_copy_tile_data_to_vram(2, gMenuPokeblock_Gfx, 0, 0, 0);
        sPokeblockMenu->gfxState++;
        break;
    case 1:
        if (free_temp_tile_data_buffers_if_possible() != TRUE)
        {
            LZDecompressWram(gMenuPokeblock_Tilemap, sPokeblockMenu->tilemap);
            sPokeblockMenu->gfxState++;
        }
        break;
    case 2:
        LoadCompressedPalette(gMenuPokeblock_Pal, 0, 0xC0);
        sPokeblockMenu->gfxState++;
        break;
    case 3:
        LoadCompressedObjectPic(&gPokeblockCase_SpriteSheet);
        sPokeblockMenu->gfxState++;
        break;
    case 4:
        LoadCompressedObjectPalette(&gPokeblockCase_SpritePal);
        sPokeblockMenu->gfxState++;
        break;
    case 5:
        LoadListMenuArrowsGfx();
        sPokeblockMenu->gfxState = 0;
        return TRUE;
    }

    return FALSE;
}

static void HandleInitWindows(void)
{
    u8 i;

    InitWindows(sWindowTemplatesForPokeblockMenu);
    DeactivateAllTextPrinters();
    LoadUserWindowBorderGfx(0, 1, 0xE0);
    copy_textbox_border_tile_patterns_to_vram(0, 0xA, 0xD0);
    LoadPalette(gUnknown_0860F074, 0xF0, 0x20);

    for (i = 0; i < ARRAY_COUNT(sWindowTemplatesForPokeblockMenu) - 1; i++)
    {
        FillWindowPixelBuffer(i, 0);
    }

    schedule_bg_copy_tilemap_to_vram(0);
    schedule_bg_copy_tilemap_to_vram(1);
}

static void PrintOnPokeblockWindow(u8 windowId, const u8 *string, s32 x)
{
    AddTextPrinterParameterized2(windowId, 1, x, 1, 0, 0, sTextColorInPokeblockMenu, 0, string);
}

static void PutPokeblockInfoText(void)
{
    u8 i;

    const u8 *itemName = ItemId_GetName(ITEM_POKEBLOCK_CASE);
    PrintOnPokeblockWindow(0, itemName, GetStringCenterAlignXOffset(1, itemName, 0x48));

    PrintOnPokeblockWindow(2, gText_Spicy, 0);
    PrintOnPokeblockWindow(3, gText_Dry, 0);
    PrintOnPokeblockWindow(4, gText_Sweet, 0);
    PrintOnPokeblockWindow(5, gText_Bitter, 0);
    PrintOnPokeblockWindow(6, gText_Sour, 0);

    for (i = 0; i < 8; i++)
    {
        PutWindowTilemap(i);
    }
}

static void HandlePokeblockListMenuItems(void)
{
    u16 i;

    for (i = 0; i < sPokeblockMenu->itemsNo - 1; i++)
    {
        PutPokeblockListMenuString(sPokeblockMenu->menuItemsStrings[i], i);
        sPokeblockMenu->items[i].name = sPokeblockMenu->menuItemsStrings[i];
        sPokeblockMenu->items[i].id = i;
    }

    StringCopy(sPokeblockMenu->menuItemsStrings[i], gText_StowCase);
    sPokeblockMenu->items[i].name = sPokeblockMenu->menuItemsStrings[i];
    sPokeblockMenu->items[i].id = LIST_B_PRESSED;

    gMultiuseListMenuTemplate = sPokeblockListMenuTemplate;
    gMultiuseListMenuTemplate.fontId = 7;
    gMultiuseListMenuTemplate.totalItems = sPokeblockMenu->itemsNo;
    gMultiuseListMenuTemplate.items = sPokeblockMenu->items;
    gMultiuseListMenuTemplate.maxShowed = sPokeblockMenu->maxShowed;
}

static void PutPokeblockListMenuString(u8 *dst, u16 pkblId)
{
    struct Pokeblock *pkblock = &gSaveBlock1Ptr->pokeblocks[pkblId];
    u8 *txtPtr = StringCopy(dst, gPokeblockNames[pkblock->color]);

    *(txtPtr++) = EXT_CTRL_CODE_BEGIN;
    *(txtPtr++) = 0x12;
    *(txtPtr++) = 0x57;

    ConvertIntToDecimalStringN(gStringVar1, GetHighestPokeblocksFlavorLevel(pkblock), STR_CONV_MODE_LEFT_ALIGN, 3);
    StringExpandPlaceholders(txtPtr, gText_LvVar1);
}

static void MovePokeblockMenuCursor(s32 pkblId, bool8 arg1, struct ListMenu *arg2)
{
    if (arg1 != TRUE)
    {
        PlaySE(SE_SELECT);
        gSprites[sPokeblockMenu->pokeblockCaseSpriteId].callback = sub_8136470;
    }

    if (!sPokeblockMenu->isSwapping)
        sub_8135FCC(pkblId);
}

static void sub_8135FCC(s32 pkblId)
{
    u8 i;
    struct Pokeblock *pokeblock;
    u16 rectTilemapSrc[2];

    FillWindowPixelBuffer(7, 0);

    if (pkblId != LIST_B_PRESSED)
    {
        pokeblock = &gSaveBlock1Ptr->pokeblocks[pkblId];
        rectTilemapSrc[0] = 0x17;
        rectTilemapSrc[1] = 0x18;
        for (i = 0; i < FLAVOR_COUNT; i++)
        {
            if (GetPokeblockData(pokeblock, PBLOCK_SPICY + i) > 0)
            {
                rectTilemapSrc[0] = (i << 0xC) + 0x17;
                rectTilemapSrc[1] = (i << 0xC) + 0x18;
            }
            else
            {
                rectTilemapSrc[0] = 0xF;
                rectTilemapSrc[1] = 0xF;
            }
            CopyToBgTilemapBufferRect(2, rectTilemapSrc, (i / 3 * 6) + 1, (i % 3 * 2) + 13, 1, 2);
        }
        ConvertIntToDecimalStringN(gStringVar1, GetPokeblocksFeel(pokeblock), STR_CONV_MODE_RIGHT_ALIGN, 2);
        PrintOnPokeblockWindow(7, gStringVar1, 4);
    }
    else
    {
        rectTilemapSrc[0] = 0xF;
        rectTilemapSrc[1] = 0xF;

        for (i = 0; i < FLAVOR_COUNT; i++)
        {
            CopyToBgTilemapBufferRect(2, rectTilemapSrc, (i / 3 * 6) + 1, (i % 3 * 2) + 13, 1, 2);
        }
        CopyWindowToVram(7, 2);
    }

    schedule_bg_copy_tilemap_to_vram(0);
    schedule_bg_copy_tilemap_to_vram(2);
}

static void HandlePokeblockMenuCursor(u16 cursorPos, u16 arg1)
{
    FillBgTilemapBufferRect_Palette0(2, arg1, 0xF, (cursorPos * 2) + 1, 0xE, 2);
    schedule_bg_copy_tilemap_to_vram(2);
}

static void CompactPokeblockSlots(void)
{
    u16 i, j;

    for (i = 0; i < POKEBLOCKS_COUNT - 1; i++)
    {
        for (j = i + 1; j < POKEBLOCKS_COUNT; j++)
        {
            if (gSaveBlock1Ptr->pokeblocks[i].color == 0)
            {
                struct Pokeblock temp = gSaveBlock1Ptr->pokeblocks[i];
                gSaveBlock1Ptr->pokeblocks[i] = gSaveBlock1Ptr->pokeblocks[j];
                gSaveBlock1Ptr->pokeblocks[j] = temp;
            }
        }
    }
}

static void SwapSortPokeblocksInternalData(u32 id1, u32 id2)
{
    s16 i, count;
    struct Pokeblock *pokeblocks = gSaveBlock1Ptr->pokeblocks;
    struct Pokeblock *copyPokeblock1;

    if (id1 == id2)
        return;

    copyPokeblock1 = Alloc(sizeof(struct Pokeblock));
    *copyPokeblock1 = pokeblocks[id1];

    if (id2 > id1)
    {
        id2--;
        for (count = id2, i = id1; i < count; i++)
            pokeblocks[i] = pokeblocks[i + 1];
    }
    else
    {
        for (count = id2, i = id1; i > count; i--)
            pokeblocks[i] = pokeblocks[i - 1];
    }

    pokeblocks[id2] = *copyPokeblock1;
    Free(copyPokeblock1);
}

void ResetPokeblockScrollPositions(void)
{
    sSavedPokeblockData.lastItemPos = 0;
    sSavedPokeblockData.lastItemPage = 0;
}

static void SetMenuItemsCountAndMaxShowed(void)
{
    u16 i;

    CompactPokeblockSlots();

    for (sPokeblockMenu->itemsNo = 0, i = 0; i < POKEBLOCKS_COUNT; i++)
    {
        if (gSaveBlock1Ptr->pokeblocks[i].color != 0)
            sPokeblockMenu->itemsNo++;
    }

    sPokeblockMenu->itemsNo++; // STOW CASE menu item

    if (sPokeblockMenu->itemsNo > 9)
        sPokeblockMenu->maxShowed = 9;
    else
        sPokeblockMenu->maxShowed = sPokeblockMenu->itemsNo;
}

static void sub_81362E0(void)
{
    if (sSavedPokeblockData.lastItemPage != 0)
    {
        if (sSavedPokeblockData.lastItemPage + sPokeblockMenu->maxShowed > sPokeblockMenu->itemsNo)
            sSavedPokeblockData.lastItemPage = sPokeblockMenu->itemsNo - sPokeblockMenu->maxShowed;
    }

    if (sSavedPokeblockData.lastItemPage + sSavedPokeblockData.lastItemPos >= sPokeblockMenu->itemsNo)
    {
        if (sPokeblockMenu->itemsNo == 0)
            sSavedPokeblockData.lastItemPos = 0;
        else
            sSavedPokeblockData.lastItemPos = sPokeblockMenu->itemsNo - 1;
    }
}

static void sub_8136344(void)
{
    if (sSavedPokeblockData.lastItemPos > 4)
    {
        u8 i;

        for (i = 0;
             (i < sSavedPokeblockData.lastItemPos - 4) && (sSavedPokeblockData.lastItemPage + sPokeblockMenu->maxShowed != sPokeblockMenu->itemsNo);
             sSavedPokeblockData.lastItemPos--, sSavedPokeblockData.lastItemPage++, i++);
    }
}

static void sub_81363BC(void)
{
    if (sPokeblockMenu->unkTaskId == 0xFF)
    {
        sPokeblockMenu->unkTaskId = AddScrollIndicatorArrowPairParameterized(SCROLL_ARROW_UP, 0xB0, 8, 0x98, sPokeblockMenu->itemsNo - sPokeblockMenu->maxShowed,
                                                                            0x456, 0x456, &sSavedPokeblockData.lastItemPage);
    }
}

static void sub_8136418(void)
{
    if (sPokeblockMenu->unkTaskId != 0xFF)
    {
        RemoveScrollIndicatorArrowPair(sPokeblockMenu->unkTaskId);
        sPokeblockMenu->unkTaskId = 0xFF;
    }
}

u8 CreatePokeblockCaseSprite(s16 x, s16 y, u8 subpriority)
{
    return CreateSprite(&sSpriteTemplate_PokeblockCase, x, y, subpriority);
}

static void sub_8136470(struct Sprite *sprite)
{
    if (sprite->data[0] > 1)
        sprite->data[0] = 0;

    switch (sprite->data[0])
    {
    case 0:
        sprite->oam.affineMode = 1;
        sprite->affineAnims = sSpriteAffineAnimTable_85B26F0;
        InitSpriteAffineAnim(sprite);
        sprite->data[0] = 1;
        sprite->data[1] = 0;
        break;
    case 1:
        if (++sprite->data[1] > 11)
        {
            sprite->oam.affineMode = 0;
            sprite->data[0] = 0;
            sprite->data[1] = 0;
            FreeOamMatrix(sprite->oam.matrixNum);
            sprite->callback = SpriteCallbackDummy;
        }
        break;
    }
}

static void FadePaletteAndSetTaskToClosePokeblockCase(u8 taskId)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 0x10, 0);
    gTasks[taskId].func = Task_FreeDataAndExitPokeblockCase;
}

static void Task_FreeDataAndExitPokeblockCase(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        if (sPokeblockMenu->caseId == PBLOCK_CASE_FEEDER || sPokeblockMenu->caseId == PBLOCK_CASE_GIVE)
            gFieldCallback = sub_80AF168;

        DestroyListMenuTask(data[0], &sSavedPokeblockData.lastItemPage, &sSavedPokeblockData.lastItemPos);
        sub_8136418();
        ResetSpriteData();
        FreeAllSpritePalettes();

        if (sPokeblockMenu->callbackOnUse != NULL)
            SetMainCallback2(sPokeblockMenu->callbackOnUse);
        else
            SetMainCallback2(sSavedPokeblockData.callback);

        FreeAllWindowBuffers();
        Free(sPokeblockMenu);
        DestroyTask(taskId);
    }
}

static void Task_HandlePokeblockMenuInput(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (!gPaletteFade.active && sub_81221EC() != TRUE)
    {
        if (gMain.newKeys & SELECT_BUTTON)
        {
            ListMenuGetScrollAndRow(data[0], &sSavedPokeblockData.lastItemPage, &sSavedPokeblockData.lastItemPos);
            if (sSavedPokeblockData.lastItemPage + sSavedPokeblockData.lastItemPos != sPokeblockMenu->itemsNo - 1)
            {
                PlaySE(SE_SELECT);
                HandlePokeblockMenuCursor(sSavedPokeblockData.lastItemPos, 0x2005);
                data[2] = sSavedPokeblockData.lastItemPage + sSavedPokeblockData.lastItemPos;
                sPokeblockMenu->isSwapping = TRUE;
                gTasks[taskId].func = Task_HandlePokeblocksSwapInput;
            }
        }
        else
        {
            u16 oldPosition = sSavedPokeblockData.lastItemPos;
            s32 itemId = ListMenuHandleInputGetItemId(data[0]);

            ListMenuGetScrollAndRow(data[0], &sSavedPokeblockData.lastItemPage, &sSavedPokeblockData.lastItemPos);
            if (oldPosition != sSavedPokeblockData.lastItemPos)
            {
                HandlePokeblockMenuCursor(oldPosition, 5);
                HandlePokeblockMenuCursor(sSavedPokeblockData.lastItemPos, 0x1005);
            }

            switch (itemId)
            {
            case LIST_NOTHING_CHOSEN:
                break;
            case LIST_B_PRESSED:
                PlaySE(SE_SELECT);
                gSpecialVar_Result = 0xFFFF;
                gSpecialVar_ItemId = 0;
                FadePaletteAndSetTaskToClosePokeblockCase(taskId);
                break;
            default:
                PlaySE(SE_SELECT);
                gSpecialVar_ItemId = itemId;
                PutPokeblockOptionsWindow(taskId);
                break;
            }
        }
    }
}

static void Task_HandlePokeblocksSwapInput(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (sub_81221EC() == TRUE)
        return;

    if (gMain.newKeys & SELECT_BUTTON)
    {
        PlaySE(SE_SELECT);
        ListMenuGetScrollAndRow(data[0], &sSavedPokeblockData.lastItemPage, &sSavedPokeblockData.lastItemPos);
        HandlePokeblocksSwap(taskId, FALSE);
    }
    else
    {
        u16 i = sSavedPokeblockData.lastItemPage;
        u16 var = sSavedPokeblockData.lastItemPos;
        s32 itemId = ListMenuHandleInputGetItemId(data[0]);

        ListMenuGetScrollAndRow(data[0], &sSavedPokeblockData.lastItemPage, &sSavedPokeblockData.lastItemPos);
        if (i != sSavedPokeblockData.lastItemPage || var != sSavedPokeblockData.lastItemPos)
        {
            for (i = 0; i < 9; i++)
            {
                var = i + sSavedPokeblockData.lastItemPage;
                if (var == data[2])
                    HandlePokeblockMenuCursor(i, 0x2005);
                else
                    HandlePokeblockMenuCursor(i, 5);
            }
        }

        sub_81223FC(sPokeblockMenu->field_E75, FIELD_E75_COUNT, 0);
        sub_8122448(sPokeblockMenu->field_E75, FIELD_E75_COUNT, 0x80, (sSavedPokeblockData.lastItemPos * 16) + 8);

        switch (itemId)
        {
        case LIST_NOTHING_CHOSEN:
            break;
        case LIST_B_PRESSED: // same id as STOW CASE field
            PlaySE(SE_SELECT);
            if (gMain.newKeys & A_BUTTON)
                HandlePokeblocksSwap(taskId, FALSE);
            else
                HandlePokeblocksSwap(taskId, TRUE);
            break;
        default:
            PlaySE(SE_SELECT);
            HandlePokeblocksSwap(taskId, FALSE);
            break;
        }
    }
}

static void HandlePokeblocksSwap(u8 taskId, bool8 noSwap)
{
    u8 i;
    s16 *data = gTasks[taskId].data;
    u16 swappedFromId = sSavedPokeblockData.lastItemPage + sSavedPokeblockData.lastItemPos;

    sPokeblockMenu->isSwapping = FALSE;
    DestroyListMenuTask(data[0], &sSavedPokeblockData.lastItemPage, &sSavedPokeblockData.lastItemPos);

    if (!noSwap && data[2] != swappedFromId && data[2] != swappedFromId - 1)
    {
        SwapSortPokeblocksInternalData(data[2], swappedFromId);
        HandlePokeblockListMenuItems();
    }

    if (data[2] < swappedFromId)
        sSavedPokeblockData.lastItemPos--;

    data[0] = ListMenuInit(&gMultiuseListMenuTemplate, sSavedPokeblockData.lastItemPage, sSavedPokeblockData.lastItemPos);
    schedule_bg_copy_tilemap_to_vram(0);
    sub_81223FC(sPokeblockMenu->field_E75, FIELD_E75_COUNT, 1);

    for (i = 0; i < 9; i++)
        HandlePokeblockMenuCursor(i, 5);

    HandlePokeblockMenuCursor(sSavedPokeblockData.lastItemPos, 0x1005);
    gTasks[taskId].func = Task_HandlePokeblockMenuInput;
}

static void PutPokeblockOptionsWindow(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (sPokeblockMenu->optionsNo == 3)
        data[1] = 8;
    else
        data[1] = 9;

    sub_8136418();
    SetWindowBorderStyle(data[1], 0, 1, 0xE);
    sub_81995E4(data[1], sPokeblockMenu->optionsNo, sPokeblockMenuActions, sPokeblockMenu->pokeblockOptionsIds);
    InitMenuInUpperLeftCornerPlaySoundWhenAPressed(data[1], sPokeblockMenu->optionsNo, 0);
    PutWindowTilemap(data[1]);
    schedule_bg_copy_tilemap_to_vram(1);

    gTasks[taskId].func = Task_HandlePokeblockOptionsInput;
}

static void Task_HandlePokeblockOptionsInput(u8 taskId)
{
    s8 itemId;

    if (sub_81221EC() == TRUE)
        return;

    itemId = ProcessMenuInputNoWrapAround();
    if (itemId == MENU_NOTHING_CHOSEN)
    {
        return;
    }
    else if (itemId == MENU_B_PRESSED)
    {
        PlaySE(SE_SELECT);
        PokeblockAction_Cancel(taskId);
    }
    else
    {
        PlaySE(SE_SELECT);
        sPokeblockMenuActions[sPokeblockMenu->pokeblockOptionsIds[itemId]].func.void_u8(taskId);
    }
}

static void PokeblockAction_UseOnField(u8 taskId)
{
    sPokeblockMenu->callbackOnUse = UsePokeblockOnField;
    FadePaletteAndSetTaskToClosePokeblockCase(taskId);
}

static void UsePokeblockOnField(void)
{
    ChooseMonToGivePokeblock(&gSaveBlock1Ptr->pokeblocks[gSpecialVar_ItemId], ReturnToPokeblockCaseOnField);
}

static void ReturnToPokeblockCaseOnField(void)
{
    OpenPokeblockCase(PBLOCK_CASE_FIELD, sSavedPokeblockData.callback);
}

static void PokeblockAction_Toss(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    sub_8198070(data[1], FALSE);
    StringCopy(gStringVar1, gPokeblockNames[gSaveBlock1Ptr->pokeblocks[gSpecialVar_ItemId].color]);
    StringExpandPlaceholders(gStringVar4, gText_ThrowAwayVar1);
    DisplayMessageAndContinueTask(taskId, 10, 10, 13, 1, GetPlayerTextSpeed(), gStringVar4, CreateTossPokeblockYesNoMenu);
}

static void CreateTossPokeblockYesNoMenu(u8 taskId)
{
    CreateYesNoMenuWithCallbacks(taskId, &sTossPkblockWindowTemplate, 1, 0, 2, 1, 0xE, &sTossYesNoFuncTable);
}

static void TossPokeblockChoice_Yes(u8 taskId)
{
    StringExpandPlaceholders(gStringVar4, gText_Var1ThrownAway);
    DisplayMessageAndContinueTask(taskId, 10, 10, 13, 1, GetPlayerTextSpeed(), gStringVar4, HandleErasePokeblock);
}

static void HandleErasePokeblock(u8 taskId)
{
    if (gMain.newKeys & (A_BUTTON | B_BUTTON))
    {
        s16 *data;
        u16 *lastPage, *lastPos;

        TryClearPokeblock(gSpecialVar_ItemId);
        PlaySE(SE_SELECT);

        lastPage = &sSavedPokeblockData.lastItemPage;
        lastPos = &sSavedPokeblockData.lastItemPos;
        data = gTasks[taskId].data;

        DestroyListMenuTask(data[0], lastPage, lastPos);
        HandlePokeblockMenuCursor(*lastPos, 5);
        SetMenuItemsCountAndMaxShowed();
        sub_81362E0();
        HandlePokeblockListMenuItems();
        data[0] = ListMenuInit(&gMultiuseListMenuTemplate, *lastPage, *lastPos);
        HandlePokeblockMenuCursor(*lastPos, 0x1005);
        schedule_bg_copy_tilemap_to_vram(0);
        schedule_bg_copy_tilemap_to_vram(1);
        TossPokeblockChoice_No(taskId);
    }
}

static void TossPokeblockChoice_No(u8 taskId)
{
    sub_8197DF8(10, FALSE);
    schedule_bg_copy_tilemap_to_vram(1);
    sub_81363BC();
    gTasks[taskId].func = Task_HandlePokeblockMenuInput;
}

static void PokeblockAction_UseInBattle(u8 taskId)
{
    u8 nature = GetNature(&gEnemyParty[0]);
    s16 gain = PokeblockGetGain(nature, &gSaveBlock1Ptr->pokeblocks[gSpecialVar_ItemId]);
    StringCopy(gBattleTextBuff1, gPokeblockNames[gSaveBlock1Ptr->pokeblocks[gSpecialVar_ItemId].color]);
    TryClearPokeblock(gSpecialVar_ItemId);

    gSpecialVar_ItemId = gSaveBlock1Ptr->pokeblocks[gSpecialVar_ItemId].color << 8;
    if (gain == 0)
        gSpecialVar_ItemId += 1;
    else if (gain > 0)
        gSpecialVar_ItemId += 2;
    else
        gSpecialVar_ItemId += 3;

    FadePaletteAndSetTaskToClosePokeblockCase(taskId);
}

static void PokeblockAction_UseOnPokeblockFeeder(u8 taskId)
{
    SafariZoneActivatePokeblockFeeder(gSpecialVar_ItemId);
    StringCopy(gStringVar1, gPokeblockNames[gSaveBlock1Ptr->pokeblocks[gSpecialVar_ItemId].color]);
    gSpecialVar_Result = gSpecialVar_ItemId;
    TryClearPokeblock(gSpecialVar_ItemId);
    gSpecialVar_ItemId = 0;
    FadePaletteAndSetTaskToClosePokeblockCase(taskId);
}

static void PokeblockAction_GiveToContestLady(u8 taskId)
{
    gSpecialVar_0x8004 = GivePokeblockToContestLady(&gSaveBlock1Ptr->pokeblocks[gSpecialVar_ItemId]);
    gSpecialVar_Result = gSpecialVar_ItemId;
    TryClearPokeblock(gSpecialVar_ItemId);
    gSpecialVar_ItemId = 0;
    FadePaletteAndSetTaskToClosePokeblockCase(taskId);
}

static void PokeblockAction_Cancel(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    sub_8198070(data[1], FALSE);
    schedule_bg_copy_tilemap_to_vram(1);
    sub_81363BC();
    gTasks[taskId].func = Task_HandlePokeblockMenuInput;
}

static void ClearPokeblock(u8 pkblId)
{
    gSaveBlock1Ptr->pokeblocks[pkblId].color = 0;
    gSaveBlock1Ptr->pokeblocks[pkblId].spicy = 0;
    gSaveBlock1Ptr->pokeblocks[pkblId].dry = 0;
    gSaveBlock1Ptr->pokeblocks[pkblId].sweet = 0;
    gSaveBlock1Ptr->pokeblocks[pkblId].bitter = 0;
    gSaveBlock1Ptr->pokeblocks[pkblId].sour = 0;
    gSaveBlock1Ptr->pokeblocks[pkblId].feel = 0;
}

void ClearPokeblocks(void)
{
    u8 i;

    for (i = 0; i < POKEBLOCKS_COUNT; i++)
        ClearPokeblock(i);
}

u8 GetHighestPokeblocksFlavorLevel(const struct Pokeblock *pokeblock)
{
    u8 i;
    u8 maxFlavor = GetPokeblockData(pokeblock, PBLOCK_SPICY);

    for (i = PBLOCK_SPICY; i < FLAVOR_COUNT; i++)
    {
        u8 currFlavor = GetPokeblockData(pokeblock, PBLOCK_SPICY + i);
        if (maxFlavor < currFlavor)
            maxFlavor = currFlavor;
    }

    return maxFlavor;
}

u8 GetPokeblocksFeel(const struct Pokeblock *pokeblock)
{
    u8 feel = GetPokeblockData(pokeblock, PBLOCK_FEEL);
    if (feel > POKEBLOCK_MAX_FEEL)
        feel = POKEBLOCK_MAX_FEEL;

    return feel;
}

s8 GetFirstFreePokeblockSlot(void)
{
    u8 i;

    for (i = 0; i < POKEBLOCKS_COUNT; i++)
    {
        if (gSaveBlock1Ptr->pokeblocks[i].color == 0)
            return i;
    }

    return -1;
}

bool32 AddPokeblock(const struct Pokeblock *pokeblock)
{
    s8 slot = GetFirstFreePokeblockSlot();

    if (slot == -1)
    {
        return FALSE;
    }
    else
    {
        gSaveBlock1Ptr->pokeblocks[slot] = *pokeblock;
        return TRUE;
    }
}

bool32 TryClearPokeblock(u8 pkblId)
{
    if (gSaveBlock1Ptr->pokeblocks[pkblId].color == 0)
    {
        return FALSE;
    }
    else
    {
        ClearPokeblock(pkblId);
        return TRUE;
    }
}

s16 GetPokeblockData(const struct Pokeblock *pokeblock, u8 field)
{
    if (field == PBLOCK_COLOR)
        return pokeblock->color;
    if (field == PBLOCK_SPICY)
        return pokeblock->spicy;
    if (field == PBLOCK_DRY)
        return pokeblock->dry;
    if (field == PBLOCK_SWEET)
        return pokeblock->sweet;
    if (field == PBLOCK_BITTER)
        return pokeblock->bitter;
    if (field == PBLOCK_SOUR)
        return pokeblock->sour;
    if (field == PBLOCK_FEEL)
        return pokeblock->feel;

    return 0;
}

s16 PokeblockGetGain(u8 nature, const struct Pokeblock *pokeblock)
{
    u8 flavor;
    s16 curGain, totalGain = 0;

    for (flavor = 0; flavor < FLAVOR_COUNT; flavor++)
    {
        curGain = GetPokeblockData(pokeblock, flavor + PBLOCK_SPICY);
        if (curGain > 0)
            totalGain += curGain * gPokeblockFlavorCompatibilityTable[5 * nature + flavor];
    }

    return totalGain;
}

void PokeblockCopyName(const struct Pokeblock *pokeblock, u8 *dest)
{
    u8 color = GetPokeblockData(pokeblock, PBLOCK_COLOR);
    StringCopy(dest, gPokeblockNames[color]);
}

bool8 CopyMonFavoritePokeblockName(u8 nature, u8 *dest)
{
    u8 i;

    for (i = 0; i < FLAVOR_COUNT; i++)
    {
        if (PokeblockGetGain(nature, &sFavoritePokeblocksTable[i]) > 0)
        {
            StringCopy(dest, gPokeblockNames[i + 1]);
            return TRUE;
        }
    }

    return FALSE;
}

u8 GetPokeblocksFlavor(const struct Pokeblock *pokeblock)
{
    s16 bestFlavor = 0;
    s16 i;

    for (i = 0; i < FLAVOR_COUNT; i++)
    {
        if (GetPokeblockData(pokeblock, bestFlavor + 1) < GetPokeblockData(pokeblock, i + 1))
            bestFlavor = i;
    }

    return bestFlavor;
}
