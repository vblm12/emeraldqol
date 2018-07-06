
// Includes
#include "global.h"
#include "field_effect.h"
#include "battle_dome_cards.h"
#include "decompress.h"
#include "field_camera.h"
#include "field_effect_helpers.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "field_screen.h"
#include "field_weather.h"
#include "fieldmap.h"
#include "fldeff_groundshake.h"
#include "gpu_regs.h"
#include "main.h"
#include "menu.h"
#include "metatile_behavior.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "pokemon.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "trig.h"
#include "util.h"
#include "constants/rgb.h"
#include "constants/songs.h"

#define subsprite_table(ptr) {.subsprites = ptr, .subspriteCount = (sizeof ptr) / (sizeof(struct Subsprite))}

EWRAM_DATA s32 gFieldEffectArguments[8] = {0};

// Static type declarations

// Static RAM declarations

static IWRAM_DATA u8 sActiveList[32];

// Static ROM declarations

extern u8 *gFieldEffectScriptPointers[];

// .rodata
const u32 gNewGameBirchPic[] = INCBIN_U32("graphics/birch_speech/birch.4bpp");
const u32 gUnusedBirchBeauty[] = INCBIN_U32("graphics/unused/intro_birch_beauty.4bpp");
const u16 gNewGameBirchPalette[16] = INCBIN_U16("graphics/birch_speech/birch.gbapal");
const u32 gSpriteImage_855A970[] = INCBIN_U32("graphics/misc/pokeball_glow.4bpp");
const u16 gFieldEffectObjectPalette4[16] = INCBIN_U16("graphics/event_objects/palettes/field_effect_object_palette_04.gbapal");
const u32 gSpriteImage_855A9B0[] = INCBIN_U32("graphics/misc/pokecenter_monitor/0.4bpp");
const u32 gSpriteImage_855AA70[] = INCBIN_U32("graphics/misc/pokecenter_monitor/1.4bpp");
const u32 gSpriteImage_855AB30[] = INCBIN_U32("graphics/misc/big_hof_monitor.4bpp");
const u8 gSpriteImage_855AD30[] = INCBIN_U8("graphics/misc/small_hof_monitor.4bpp");
const u16 gFieldEffectObjectPalette5[16] = INCBIN_U16("graphics/event_objects/palettes/field_effect_object_palette_05.gbapal");

// Graphics for the lights streaking past your Pokemon when it uses a field move.
const u32 gFieldMoveStreaksTiles[] = INCBIN_U32("graphics/misc/field_move_streaks.4bpp");
const u16 gFieldMoveStreaksPalette[16] = INCBIN_U16("graphics/misc/field_move_streaks.gbapal");
const u16 gFieldMoveStreaksTilemap[] = INCBIN_U16("graphics/misc/field_move_streaks_map.bin");

// The following light streaks effect is used when the map is dark (e.g. a cave).
const u32 gDarknessFieldMoveStreaksTiles[] = INCBIN_U32("graphics/misc/darkness_field_move_streaks.4bpp");
const u16 gDarknessFieldMoveStreaksPalette[16] = INCBIN_U16("graphics/misc/darkness_field_move_streaks.gbapal");
const u16 gDarknessFieldMoveStreaksTilemap[] = INCBIN_U16("graphics/misc/darkness_field_move_streaks_map.bin");

const u16 gUnknown_0855B610[16] = INCBIN_U16("graphics/misc/spotlight.gbapal");
const u8 gUnknown_0855B630[] = INCBIN_U8("graphics/misc/spotlight.4bpp");
const u8 gUnknown_0855C170[] = INCBIN_U8("graphics/unknown/unknown_55C170.4bpp");
const u8 gUnknown_0855C190[] = INCBIN_U8("graphics/unknown/unknown_55C190.4bpp");
const u8 gUnknown_0855C1B0[] = INCBIN_U8("graphics/unknown/unknown_55C1B0.4bpp");
const u8 gUnknown_0855C1D0[] = INCBIN_U8("graphics/unknown/unknown_55C1D0.4bpp");

bool8 (*const gFieldEffectScriptFuncs[])(u8 **, u32 *) = {
    FieldEffectCmd_loadtiles,
    FieldEffectCmd_loadfadedpal,
    FieldEffectCmd_loadpal,
    FieldEffectCmd_callnative,
    FieldEffectCmd_end,
    FieldEffectCmd_loadgfx_callnative,
    FieldEffectCmd_loadtiles_callnative,
    FieldEffectCmd_loadfadedpal_callnative,
};

const struct OamData gNewGameBirchOamAttributes = {.size = 3};
const struct OamData gOamData_855C218 = {.size = 0};
const struct OamData gOamData_855C220 = {.size = 1};

const struct SpriteFrameImage gNewGameBirchPicTable[] = {
    obj_frame_tiles(gNewGameBirchPic)
};
const struct SpritePalette gNewGameBirchObjectPaletteInfo = {.data = gNewGameBirchPalette, .tag = 0x1006};

const union AnimCmd gNewGameBirchImageAnim[] = {
    ANIMCMD_FRAME(.imageValue = 0, .duration = 1),
    ANIMCMD_END
};

const union AnimCmd *const gNewGameBirchImageAnimTable[] = {
    gNewGameBirchImageAnim
};

const struct SpriteTemplate gNewGameBirchObjectTemplate = {
    .tileTag = 0xffff,
    .paletteTag = 4102,
    .oam = &gNewGameBirchOamAttributes,
    .anims = gNewGameBirchImageAnimTable,
    .images = gNewGameBirchPicTable,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

const struct SpritePalette gFieldEffectObjectPaletteInfo4 = {.data = gFieldEffectObjectPalette4, .tag = 0x1007};
const struct SpritePalette gFieldEffectObjectPaletteInfo5 = {.data = gFieldEffectObjectPalette5, .tag = 0x1010};
const struct OamData gOamData_855C26C = {
    .shape = 1,
    .size = 2
};

const struct SpriteFrameImage gSpriteImageTable_855C274[] = {
    obj_frame_tiles(gSpriteImage_855A970)
};

const struct SpriteFrameImage gSpriteImageTable_855C27C[] = {
    obj_frame_tiles(gSpriteImage_855A9B0),
    obj_frame_tiles(gSpriteImage_855AA70)
};

const struct SpriteFrameImage gSpriteImageTable_855C28C[] = {
    obj_frame_tiles(gSpriteImage_855AB30)
};

const struct SpriteFrameImage gSpriteImageTable_855C294[] = {
    {.data = gSpriteImage_855AD30, .size = 0x200} // the macro breaks down here
};

const struct Subsprite gSubspriteTable_855C29C[] = {
    {.x = -12, .y = -8, .priority = 2, .tileOffset = 0, .shape = 1, .size = 0},
    {.x =   4, .y = -8, .priority = 2, .tileOffset = 2, .shape = 0, .size = 0},
    {.x = -12, .y =  0, .priority = 2, .tileOffset = 3, .shape = 1, .size = 0},
    {.x =   4, .y =  0, .priority = 2, .tileOffset = 5, .shape = 0, .size = 0}
};

const struct SubspriteTable gUnknown_0855C2AC = subsprite_table(gSubspriteTable_855C29C);

const struct Subsprite gSubspriteTable_855C2B4[] = {
    {.x = -32, .y = -8, .priority = 2, .tileOffset =  0, .shape = 1, .size = 1},
    {.x =   0, .y = -8, .priority = 2, .tileOffset =  4, .shape = 1, .size = 1},
    {.x = -32, .y =  0, .priority = 2, .tileOffset =  8, .shape = 1, .size = 1},
    {.x =   0, .y =  0, .priority = 2, .tileOffset = 12, .shape = 1, .size = 1}
};

const struct SubspriteTable gUnknown_0855C2C4 = subsprite_table(gSubspriteTable_855C2B4);

const union AnimCmd gSpriteAnim_855C2CC[] = {
    ANIMCMD_FRAME(.imageValue = 0, .duration = 1),
    ANIMCMD_JUMP(0)
};

const union AnimCmd gSpriteAnim_855C2D4[] = {
    ANIMCMD_FRAME(.imageValue = 0, .duration = 16),
    ANIMCMD_FRAME(.imageValue = 1, .duration = 16),
    ANIMCMD_FRAME(.imageValue = 0, .duration = 16),
    ANIMCMD_FRAME(.imageValue = 1, .duration = 16),
    ANIMCMD_FRAME(.imageValue = 0, .duration = 16),
    ANIMCMD_FRAME(.imageValue = 1, .duration = 16),
    ANIMCMD_FRAME(.imageValue = 0, .duration = 16),
    ANIMCMD_FRAME(.imageValue = 1, .duration = 16),
    ANIMCMD_END
};

const union AnimCmd *const gSpriteAnimTable_855C2F8[] = {
    gSpriteAnim_855C2CC,
    gSpriteAnim_855C2D4
};

const union AnimCmd *const gSpriteAnimTable_855C300[] = {
    gSpriteAnim_855C2CC
};

const struct SpriteTemplate gSpriteTemplate_855C304 = {
    .tileTag = 0xffff,
    .paletteTag = 4103,
    .oam = &gOamData_855C218,
    .anims = gSpriteAnimTable_855C2F8,
    .images = gSpriteImageTable_855C274,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_PokeballGlow
};

const struct SpriteTemplate gSpriteTemplate_855C31C = {
    .tileTag = 0xffff,
    .paletteTag = 4100,
    .oam = &gOamData_855C220,
    .anims = gSpriteAnimTable_855C2F8,
    .images = gSpriteImageTable_855C27C,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_PokecenterMonitor
};

const struct SpriteTemplate gSpriteTemplate_855C334 = {
    .tileTag = 0xffff,
    .paletteTag = 4112,
    .oam = &gOamData_855C220,
    .anims = gSpriteAnimTable_855C300,
    .images = gSpriteImageTable_855C28C,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_HallOfFameMonitor
};

const struct SpriteTemplate gSpriteTemplate_855C34C = {
    .tileTag = 0xffff,
    .paletteTag = 4112,
    .oam = &gOamData_855C26C,
    .anims = gSpriteAnimTable_855C300,
    .images = gSpriteImageTable_855C294,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_HallOfFameMonitor
};

void (*const gUnknown_0855C364[])(struct Task *) = {
    PokecenterHealEffect_0,
    PokecenterHealEffect_1,
    PokecenterHealEffect_2,
    PokecenterHealEffect_3
};

void (*const gUnknown_0855C374[])(struct Task *) = {
    HallOfFameRecordEffect_0,
    HallOfFameRecordEffect_1,
    HallOfFameRecordEffect_2,
    HallOfFameRecordEffect_3
};

void (*const gUnknown_0855C384[])(struct Sprite *) = {
    PokeballGlowEffect_0,
    PokeballGlowEffect_1,
    PokeballGlowEffect_2,
    PokeballGlowEffect_3,
    PokeballGlowEffect_4,
    PokeballGlowEffect_5,
    PokeballGlowEffect_6,
    PokeballGlowEffect_7
};

const struct Coords16 gUnknown_0855C3A4[] = {
    {.x = 0, .y = 0},
    {.x = 6, .y = 0},
    {.x = 0, .y = 4},
    {.x = 6, .y = 4},
    {.x = 0, .y = 8},
    {.x = 6, .y = 8}
};

const u8 gUnknown_0855C3BC[] = {16, 12, 8, 0};
const u8 gUnknown_0855C3C0[] = {16, 12, 8, 0};
const u8 gUnknown_0855C3C4[] = { 0,  0, 0, 0};

bool8 (*const gUnknown_0855C3C8[])(struct Task *) = {
    sub_80B6BCC,
    sub_80B6C74,
    sub_80B6C90,
    sub_80B6D04,
    sub_80B6DBC,
    sub_80B6DD8,
    sub_80B6E18,
};

bool8 (*const gUnknown_0855C3E4[])(struct Task *) = {
    sub_80B6EC0,
    sub_80B6EE0,
    sub_80B6F50,
    sub_80B6F74,
    sub_80B6F84,
    sub_80B6FA8,
};

bool8 (*const gUnknown_0855C3FC[])(struct Task *) = {
    sub_80B7114,
    sub_80B7190,
    sub_80B71D0,
    sub_80B7230,
    sub_80B7270,
    sub_80B72D0,
    sub_80B72F4,
};

bool8 (*const gUnknown_0855C418[])(struct Task *, struct EventObject *) = {
    sub_80B73D0,
    waterfall_1_do_anim_probably,
    waterfall_2_wait_anim_finish_probably,
    sub_80B7450,
    sub_80B7478,
};

bool8 (*const gUnknown_0855C42C[])(struct Task *) = {
    dive_1_lock,
    dive_2_unknown,
    dive_3_unknown,
};

bool8 (*const gUnknown_0855C438[])(struct Task *, struct EventObject *, struct Sprite *) = {
    sub_80B764C,
    sub_80B7684,
    sub_80B76B8,
    sub_80B7704,
    sub_80B77F8,
    sub_80B7814,
};

bool8 (*const gUnknown_0855C450[])(struct Task *, struct EventObject *, struct Sprite *) = {
    sub_80B78EC,
    sub_80B791C,
    sub_80B7968,
    sub_80B79BC,
};

bool8 (*const gUnknown_0855C460[])(struct Task *, struct EventObject *, struct Sprite *) = {
    sub_80B7AE8,
    sub_80B7B18,
    sub_80B7B94,
    sub_80B7BCC,
    sub_80B7BF4,
};

void (*const gUnknown_0855C474[])(struct Task *) = {
    sub_80B7D14,
    sub_80B7D34,
};

// .text

u32 FieldEffectStart(u8 id)
{
    u8 *script;
    u32 val;

    FieldEffectActiveListAdd(id);

    script = gFieldEffectScriptPointers[id];

    while (gFieldEffectScriptFuncs[*script](&script, &val))
        ;

    return val;
}

bool8 FieldEffectCmd_loadtiles(u8 **script, u32 *val)
{
    (*script)++;
    FieldEffectScript_LoadTiles(script);
    return TRUE;
}

bool8 FieldEffectCmd_loadfadedpal(u8 **script, u32 *val)
{
    (*script)++;
    FieldEffectScript_LoadFadedPalette(script);
    return TRUE;
}

bool8 FieldEffectCmd_loadpal(u8 **script, u32 *val)
{
    (*script)++;
    FieldEffectScript_LoadPalette(script);
    return TRUE;
}

bool8 FieldEffectCmd_callnative(u8 **script, u32 *val)
{
    (*script)++;
    FieldEffectScript_CallNative(script, val);
    return TRUE;
}

bool8 FieldEffectCmd_end(u8 **script, u32 *val)
{
    return FALSE;
}

bool8 FieldEffectCmd_loadgfx_callnative(u8 **script, u32 *val)
{
    (*script)++;
    FieldEffectScript_LoadTiles(script);
    FieldEffectScript_LoadFadedPalette(script);
    FieldEffectScript_CallNative(script, val);
    return TRUE;
}

bool8 FieldEffectCmd_loadtiles_callnative(u8 **script, u32 *val)
{
    (*script)++;
    FieldEffectScript_LoadTiles(script);
    FieldEffectScript_CallNative(script, val);
    return TRUE;
}

bool8 FieldEffectCmd_loadfadedpal_callnative(u8 **script, u32 *val)
{
    (*script)++;
    FieldEffectScript_LoadFadedPalette(script);
    FieldEffectScript_CallNative(script, val);
    return TRUE;
}

u32 FieldEffectScript_ReadWord(u8 **script)
{
    return (*script)[0]
         + ((*script)[1] << 8)
         + ((*script)[2] << 16)
         + ((*script)[3] << 24);
}

void FieldEffectScript_LoadTiles(u8 **script)
{
    struct SpriteSheet *sheet = (struct SpriteSheet *)FieldEffectScript_ReadWord(script);
    if (GetSpriteTileStartByTag(sheet->tag) == 0xFFFF)
        LoadSpriteSheet(sheet);
    (*script) += 4;
}

void FieldEffectScript_LoadFadedPalette(u8 **script)
{
    struct SpritePalette *palette = (struct SpritePalette *)FieldEffectScript_ReadWord(script);
    LoadSpritePalette(palette);
    UpdateSpritePaletteWithWeather(IndexOfSpritePaletteTag(palette->tag));
    (*script) += 4;
}

void FieldEffectScript_LoadPalette(u8 **script)
{
    struct SpritePalette *palette = (struct SpritePalette *)FieldEffectScript_ReadWord(script);
    LoadSpritePalette(palette);
    (*script) += 4;
}

void FieldEffectScript_CallNative(u8 **script, u32 *val)
{
    u32 (*func)(void) = (u32 (*)(void))FieldEffectScript_ReadWord(script);
    *val = func();
    (*script) += 4;
}

void FieldEffectFreeGraphicsResources(struct Sprite *sprite)
{
    u16 sheetTileStart = sprite->sheetTileStart;
    u32 paletteNum = sprite->oam.paletteNum;
    DestroySprite(sprite);
    FieldEffectFreeTilesIfUnused(sheetTileStart);
    FieldEffectFreePaletteIfUnused(paletteNum);
}

void FieldEffectStop(struct Sprite *sprite, u8 id)
{
    FieldEffectFreeGraphicsResources(sprite);
    FieldEffectActiveListRemove(id);
}

void FieldEffectFreeTilesIfUnused(u16 tileStart)
{
    u8 i;
    u16 tag = GetSpriteTileTagByTileStart(tileStart);

    if (tag != 0xFFFF)
    {
        for (i = 0; i < MAX_SPRITES; i++)
            if (gSprites[i].inUse && gSprites[i].usingSheet && tileStart == gSprites[i].sheetTileStart)
                return;
        FreeSpriteTilesByTag(tag);
    }
}

void FieldEffectFreePaletteIfUnused(u8 paletteNum)
{
    u8 i;
    u16 tag = GetSpritePaletteTagByPaletteNum(paletteNum);

    if (tag != 0xFFFF)
    {
        for (i = 0; i < MAX_SPRITES; i++)
            if (gSprites[i].inUse && gSprites[i].oam.paletteNum == paletteNum)
                return;
        FreeSpritePaletteByTag(tag);
    }
}

void FieldEffectActiveListClear(void)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(sActiveList); i++)
        sActiveList[i] = 0xFF;
}

void FieldEffectActiveListAdd(u8 id)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(sActiveList); i++)
    {
        if (sActiveList[i] == 0xFF)
        {
            sActiveList[i] = id;
            return;
        }
    }
}

void FieldEffectActiveListRemove(u8 id)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(sActiveList); i++)
    {
        if (sActiveList[i] == id)
        {
            sActiveList[i] = 0xFF;
            return;
        }
    }
}

bool8 FieldEffectActiveListContains(u8 id)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(sActiveList); i++)
        if (sActiveList[i] == id)
            return TRUE;
    return FALSE;
}

u8 CreateTrainerSprite(u8 trainerSpriteID, s16 x, s16 y, u8 subpriority, u8 *buffer)
{
    struct SpriteTemplate spriteTemplate;
    LoadCompressedObjectPaletteOverrideBuffer(&gTrainerFrontPicPaletteTable[trainerSpriteID], buffer);
    LoadCompressedObjectPicOverrideBuffer(&gTrainerFrontPicTable[trainerSpriteID], buffer);
    spriteTemplate.tileTag = gTrainerFrontPicTable[trainerSpriteID].tag;
    spriteTemplate.paletteTag = gTrainerFrontPicPaletteTable[trainerSpriteID].tag;
    spriteTemplate.oam = &gNewGameBirchOamAttributes;
    spriteTemplate.anims = gDummySpriteAnimTable;
    spriteTemplate.images = NULL;
    spriteTemplate.affineAnims = gDummySpriteAffineAnimTable;
    spriteTemplate.callback = SpriteCallbackDummy;
    return CreateSprite(&spriteTemplate, x, y, subpriority);
}

void LoadTrainerGfx_TrainerCard(u8 gender, u16 palOffset, u8 *dest)
{
    LZDecompressVram(gTrainerFrontPicTable[gender].data, dest);
    LoadCompressedPalette(gTrainerFrontPicPaletteTable[gender].data, palOffset, 0x20);
}

u8 AddNewGameBirchObject(s16 x, s16 y, u8 subpriority)
{
    LoadSpritePalette(&gNewGameBirchObjectPaletteInfo);
    return CreateSprite(&gNewGameBirchObjectTemplate, x, y, subpriority);
}

#ifdef NONMATCHING
u8 CreateMonSprite_PicBox(u16 species, s16 x, s16 y)
{
    u16 spriteId = sub_818D7D8(species, 0, 0x8000, 1, x, y, 0, gMonPaletteTable[species].tag);
    PreservePaletteInWeather(IndexOfSpritePaletteTag(gMonPaletteTable[species].tag) + 0x10);
    if (spriteId == 0xFFFF)
        return 0x40;

    return spriteId;
}
#else
NAKED
u8 CreateMonSprite_PicBox(u16 species, s16 x, s16 y)
{
    asm_unified("push {r4,r5,lr}\n\
	sub sp, 0x10\n\
	lsls r0, 16\n\
	lsrs r0, 16\n\
	movs r3, 0x80\n\
	lsls r3, 8\n\
	lsls r1, 16\n\
	asrs r1, 16\n\
	str r1, [sp]\n\
	lsls r2, 16\n\
	asrs r2, 16\n\
	str r2, [sp, 0x4]\n\
	movs r1, 0\n\
	str r1, [sp, 0x8]\n\
	ldr r1, =gMonPaletteTable\n\
	lsls r4, r0, 3\n\
	adds r4, r1\n\
	ldrh r1, [r4, 0x4]\n\
	str r1, [sp, 0xC]\n\
	movs r1, 0\n\
	adds r2, r3, 0\n\
	movs r3, 0x1\n\
	bl sub_818D7D8\n\
	lsls r0, 16\n\
	lsrs r5, r0, 16\n\
	ldrh r0, [r4, 0x4]\n\
	bl IndexOfSpritePaletteTag\n\
	adds r0, 0x10\n\
	lsls r0, 24\n\
	lsrs r0, 24\n\
	bl PreservePaletteInWeather\n\
	ldr r0, =0x0000ffff\n\
	cmp r5, r0\n\
	beq _080B5FDC\n\
	lsls r0, r5, 24\n\
	lsrs r0, 24\n\
	b _080B5FDE\n\
	.pool\n\
_080B5FDC:\n\
	movs r0, 0x40\n\
_080B5FDE:\n\
	add sp, 0x10\n\
	pop {r4,r5}\n\
	pop {r1}\n\
	bx r1");
}
#endif //NONMATCHING

u8 CreateMonSprite_FieldMove(u16 species, u32 d, u32 g, s16 x, s16 y, u8 subpriority)
{
    const struct CompressedSpritePalette *spritePalette = GetMonSpritePalStructFromOtIdPersonality(species, d, g);
    u16 spriteId = sub_818D7D8(species, d, g, 1, x, y, 0, spritePalette->tag);
    PreservePaletteInWeather(IndexOfSpritePaletteTag(spritePalette->tag) + 0x10);
    if (spriteId == 0xFFFF)
        return 0x40;

    return spriteId;
}

void FreeResourcesAndDestroySprite(struct Sprite *sprite, u8 spriteId)
{
    ResetPreservedPalettesInWeather();
    if (sprite->oam.affineMode != 0)
    {
        FreeOamMatrix(sprite->oam.matrixNum);
    }
    sub_818D820(spriteId);
}

#ifdef NONMATCHING
void MultiplyInvertedPaletteRGBComponents(u16 i, u8 r, u8 g, u8 b)
{
    int curRed;
    int curGreen;
    int curBlue;

    curRed = gPlttBufferUnfaded[i] & 0x1f;
    curGreen = (gPlttBufferUnfaded[i] & (0x1f << 5)) >> 5;
    curBlue = (gPlttBufferUnfaded[i] & (0x1f << 10)) >> 10;
    curRed += (((0x1f - curRed) * r) >> 4);
    curGreen += (((0x1f - curGreen) * g) >> 4);
    curBlue += (((0x1f - curBlue) * b) >> 4);
    gPlttBufferFaded[i] = RGB(curRed, curGreen, curBlue);
}

void MultiplyPaletteRGBComponents(u16 i, u8 r, u8 g, u8 b)
{
    int curRed;
    int curGreen;
    int curBlue;

    curRed = gPlttBufferUnfaded[i] & 0x1f;
    curGreen = (gPlttBufferUnfaded[i] & (0x1f << 5)) >> 5;
    curBlue = (gPlttBufferUnfaded[i] & (0x1f << 10)) >> 10;
    curRed -= ((curRed * r) >> 4);
    curGreen -= ((curGreen * g) >> 4);
    curBlue -= ((curBlue * b) >> 4);
    gPlttBufferFaded[i] = RGB(curRed, curGreen, curBlue);
}
#else
NAKED
void MultiplyInvertedPaletteRGBComponents(u16 i, u8 r, u8 g, u8 b)
{
    asm(".syntax unified\n"
    "\tpush {r4-r7,lr}\n"
    "\tmov r7, r9\n"
    "\tmov r6, r8\n"
    "\tpush {r6,r7}\n"
    "\tlsls r0, 16\n"
    "\tlsls r1, 24\n"
    "\tlsrs r1, 24\n"
    "\tlsls r2, 24\n"
    "\tlsrs r2, 24\n"
    "\tlsls r3, 24\n"
    "\tlsrs r3, 24\n"
    "\tldr r4, _08085D00 @ =gPlttBufferUnfaded\n"
    "\tlsrs r0, 15\n"
    "\tadds r4, r0, r4\n"
    "\tldrh r4, [r4]\n"
    "\tmovs r5, 0x1F\n"
    "\tmov r9, r5\n"
    "\tmov r8, r4\n"
    "\tmov r6, r8\n"
    "\tands r6, r5\n"
    "\tmov r8, r6\n"
    "\tmovs r6, 0xF8\n"
    "\tlsls r6, 2\n"
    "\tands r6, r4\n"
    "\tlsrs r6, 5\n"
    "\tmovs r5, 0xF8\n"
    "\tlsls r5, 7\n"
    "\tands r4, r5\n"
    "\tlsrs r4, 10\n"
    "\tmov r7, r9\n"
    "\tmov r5, r8\n"
    "\tsubs r7, r5\n"
    "\tmov r12, r7\n"
    "\tmov r7, r12\n"
    "\tmuls r7, r1\n"
    "\tadds r1, r7, 0\n"
    "\tasrs r1, 4\n"
    "\tadd r8, r1\n"
    "\tmov r5, r9\n"
    "\tsubs r1, r5, r6\n"
    "\tmuls r1, r2\n"
    "\tasrs r1, 4\n"
    "\tadds r6, r1\n"
    "\tsubs r5, r4\n"
    "\tmov r9, r5\n"
    "\tmov r1, r9\n"
    "\tmuls r1, r3\n"
    "\tasrs r1, 4\n"
    "\tadds r4, r1\n"
    "\tmov r7, r8\n"
    "\tlsls r7, 16\n"
    "\tlsls r6, 21\n"
    "\torrs r6, r7\n"
    "\tlsls r4, 26\n"
    "\torrs r4, r6\n"
    "\tlsrs r4, 16\n"
    "\tldr r1, _08085D04 @ =gPlttBufferFaded\n"
    "\tadds r0, r1\n"
    "\tstrh r4, [r0]\n"
    "\tpop {r3,r4}\n"
    "\tmov r8, r3\n"
    "\tmov r9, r4\n"
    "\tpop {r4-r7}\n"
    "\tpop {r0}\n"
    "\tbx r0\n"
    "\t.align 2, 0\n"
    "_08085D00: .4byte gPlttBufferUnfaded\n"
    "_08085D04: .4byte gPlttBufferFaded\n"
    ".syntax divided");
}

NAKED
void MultiplyPaletteRGBComponents(u16 i, u8 r, u8 g, u8 b)
{
    asm(".syntax unified\n"
    "\tpush {r4-r6,lr}\n"
    "\tmov r6, r8\n"
    "\tpush {r6}\n"
    "\tlsls r0, 16\n"
    "\tlsls r1, 24\n"
    "\tlsrs r1, 24\n"
    "\tlsls r2, 24\n"
    "\tlsrs r2, 24\n"
    "\tlsls r3, 24\n"
    "\tlsrs r3, 24\n"
    "\tldr r4, _08085D78 @ =gPlttBufferUnfaded\n"
    "\tlsrs r0, 15\n"
    "\tadds r4, r0, r4\n"
    "\tldrh r4, [r4]\n"
    "\tmovs r5, 0x1F\n"
    "\tmov r8, r5\n"
    "\tmov r6, r8\n"
    "\tands r6, r4\n"
    "\tmov r8, r6\n"
    "\tmovs r5, 0xF8\n"
    "\tlsls r5, 2\n"
    "\tands r5, r4\n"
    "\tlsrs r5, 5\n"
    "\tmovs r6, 0xF8\n"
    "\tlsls r6, 7\n"
    "\tands r4, r6\n"
    "\tlsrs r4, 10\n"
    "\tmov r6, r8\n"
    "\tmuls r6, r1\n"
    "\tadds r1, r6, 0\n"
    "\tasrs r1, 4\n"
    "\tmov r6, r8\n"
    "\tsubs r6, r1\n"
    "\tadds r1, r5, 0\n"
    "\tmuls r1, r2\n"
    "\tasrs r1, 4\n"
    "\tsubs r5, r1\n"
    "\tadds r1, r4, 0\n"
    "\tmuls r1, r3\n"
    "\tasrs r1, 4\n"
    "\tsubs r4, r1\n"
    "\tlsls r6, 16\n"
    "\tlsls r5, 21\n"
    "\torrs r5, r6\n"
    "\tlsls r4, 26\n"
    "\torrs r4, r5\n"
    "\tlsrs r4, 16\n"
    "\tldr r1, _08085D7C @ =gPlttBufferFaded\n"
    "\tadds r0, r1\n"
    "\tstrh r4, [r0]\n"
    "\tpop {r3}\n"
    "\tmov r8, r3\n"
    "\tpop {r4-r6}\n"
    "\tpop {r0}\n"
    "\tbx r0\n"
    "\t.align 2, 0\n"
    "_08085D78: .4byte gPlttBufferUnfaded\n"
    "_08085D7C: .4byte gPlttBufferFaded\n"
    ".syntax divided");
}
#endif

void Task_PokecenterHeal(u8 taskId);
u8 CreatePokeballGlowSprite(s16, s16, s16, u16);
u8 PokecenterHealEffectHelper(s16, s16);

bool8 FldEff_PokecenterHeal(void)
{
    u8 nPokemon;
    struct Task *task;

    nPokemon = CalculatePlayerPartyCount();
    task = &gTasks[CreateTask(Task_PokecenterHeal, 0xff)];
    task->data[1] = nPokemon;
    task->data[2] = 0x5d;
    task->data[3] = 0x24;
    task->data[4] = 0x7c;
    task->data[5] = 0x18;
    return FALSE;
}

void Task_PokecenterHeal(u8 taskId)
{
    struct Task *task;
    task = &gTasks[taskId];
    gUnknown_0855C364[task->data[0]](task);
}

void PokecenterHealEffect_0(struct Task *task)
{
    task->data[0]++;
    task->data[6] = CreatePokeballGlowSprite(task->data[1], task->data[2], task->data[3], 1);
    task->data[7] = PokecenterHealEffectHelper(task->data[4], task->data[5]);
}

void PokecenterHealEffect_1(struct Task *task)
{
    if (gSprites[task->data[6]].data[0] > 1)
    {
        gSprites[task->data[7]].data[0]++;
        task->data[0]++;
    }
}

void PokecenterHealEffect_2(struct Task *task)
{
    if (gSprites[task->data[6]].data[0] > 4)
    {
        task->data[0]++;
    }
}

void PokecenterHealEffect_3(struct Task *task)
{
    if (gSprites[task->data[6]].data[0] > 6)
    {
        DestroySprite(&gSprites[task->data[6]]);
        FieldEffectActiveListRemove(FLDEFF_POKECENTER_HEAL);
        DestroyTask(FindTaskIdByFunc(Task_PokecenterHeal));
    }
}

void Task_HallOfFameRecord(u8 taskId);
void HallOfFameRecordEffectHelper(s16, s16, s16, u8);

bool8 FldEff_HallOfFameRecord(void)
{
    u8 nPokemon;
    struct Task *task;

    nPokemon = CalculatePlayerPartyCount();
    task = &gTasks[CreateTask(Task_HallOfFameRecord, 0xff)];
    task->data[1] = nPokemon;
    task->data[2] = 0x75;
    task->data[3] = 0x34;
    return FALSE;
}

void Task_HallOfFameRecord(u8 taskId)
{
    struct Task *task;
    task = &gTasks[taskId];
    gUnknown_0855C374[task->data[0]](task);
}

void HallOfFameRecordEffect_0(struct Task *task)
{
    u8 taskId;
    task->data[0]++;
    task->data[6] = CreatePokeballGlowSprite(task->data[1], task->data[2], task->data[3], 0);
    taskId = FindTaskIdByFunc(Task_HallOfFameRecord);
    HallOfFameRecordEffectHelper(taskId, 0x78, 0x18, 0);
    HallOfFameRecordEffectHelper(taskId, 0x28, 0x08, 1);
    HallOfFameRecordEffectHelper(taskId, 0x48, 0x08, 1);
    HallOfFameRecordEffectHelper(taskId, 0xa8, 0x08, 1);
    HallOfFameRecordEffectHelper(taskId, 0xc8, 0x08, 1);
}

void HallOfFameRecordEffect_1(struct Task *task)
{
    if (gSprites[task->data[6]].data[0] > 1)
    {
        task->data[15]++; // was this ever initialized? is this ever used?
        task->data[0]++;
    }
}

void HallOfFameRecordEffect_2(struct Task *task)
{
    if (gSprites[task->data[6]].data[0] > 4)
    {
        task->data[0]++;
    }
}

void HallOfFameRecordEffect_3(struct Task *task)
{
    if (gSprites[task->data[6]].data[0] > 6)
    {
        DestroySprite(&gSprites[task->data[6]]);
        FieldEffectActiveListRemove(FLDEFF_HALL_OF_FAME_RECORD);
        DestroyTask(FindTaskIdByFunc(Task_HallOfFameRecord));
    }
}

void SpriteCB_PokeballGlowEffect(struct Sprite *);

u8 CreatePokeballGlowSprite(s16 data6, s16 x, s16 y, u16 data5)
{
    u8 spriteId;
    struct Sprite *sprite;
    spriteId = CreateInvisibleSprite(SpriteCB_PokeballGlowEffect);
    sprite = &gSprites[spriteId];
    sprite->pos2.x = x;
    sprite->pos2.y = y;
    sprite->data[5] = data5;
    sprite->data[6] = data6;
    sprite->data[7] = spriteId;
    return spriteId;
}

void SpriteCB_PokeballGlowEffect(struct Sprite *sprite)
{
    gUnknown_0855C384[sprite->data[0]](sprite);
}

void PokeballGlowEffect_0(struct Sprite *sprite)
{
    u8 endSpriteId;
    if (sprite->data[1] == 0 || (--sprite->data[1]) == 0)
    {
        sprite->data[1] = 25;
        endSpriteId = CreateSpriteAtEnd(&gSpriteTemplate_855C304, gUnknown_0855C3A4[sprite->data[2]].x + sprite->pos2.x, gUnknown_0855C3A4[sprite->data[2]].y + sprite->pos2.y, 0);
        gSprites[endSpriteId].oam.priority = 2;
        gSprites[endSpriteId].data[0] = sprite->data[7];
        sprite->data[2]++;
        sprite->data[6]--;
        PlaySE(SE_BOWA);
    }
    if (sprite->data[6] == 0)
    {
        sprite->data[1] = 32;
        sprite->data[0]++;
    }
}

void PokeballGlowEffect_1(struct Sprite *sprite)
{
    if ((--sprite->data[1]) == 0)
    {
        sprite->data[0]++;
        sprite->data[1] = 8;
        sprite->data[2] = 0;
        sprite->data[3] = 0;
        if (sprite->data[5])
        {
            PlayFanfare(MUS_ME_ASA);
        }
    }
}

void PokeballGlowEffect_2(struct Sprite *sprite)
{
    u8 phase;
    if ((--sprite->data[1]) == 0)
    {
        sprite->data[1] = 8;
        sprite->data[2]++;
        sprite->data[2] &= 3;
        if (sprite->data[2] == 0)
        {
            sprite->data[3]++;
        }
    }
    phase = (sprite->data[2] + 3) & 3;
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(0x1007) << 4) + 0x108, gUnknown_0855C3BC[phase], gUnknown_0855C3C0[phase], gUnknown_0855C3C4[phase]);
    phase = (sprite->data[2] + 2) & 3;
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(0x1007) << 4) + 0x106, gUnknown_0855C3BC[phase], gUnknown_0855C3C0[phase], gUnknown_0855C3C4[phase]);
    phase = (sprite->data[2] + 1) & 3;
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(0x1007) << 4) + 0x102, gUnknown_0855C3BC[phase], gUnknown_0855C3C0[phase], gUnknown_0855C3C4[phase]);
    phase = sprite->data[2];
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(0x1007) << 4) + 0x105, gUnknown_0855C3BC[phase], gUnknown_0855C3C0[phase], gUnknown_0855C3C4[phase]);
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(0x1007) << 4) + 0x103, gUnknown_0855C3BC[phase], gUnknown_0855C3C0[phase], gUnknown_0855C3C4[phase]);
    if (sprite->data[3] > 2)
    {
        sprite->data[0]++;
        sprite->data[1] = 8;
        sprite->data[2] = 0;
    }
}

void PokeballGlowEffect_3(struct Sprite *sprite)
{
    u8 phase;
    if ((--sprite->data[1]) == 0)
    {
        sprite->data[1] = 8;
        sprite->data[2]++;
        sprite->data[2] &= 3;
        if (sprite->data[2] == 3)
        {
            sprite->data[0]++;
            sprite->data[1] = 30;
        }
    }
    phase = sprite->data[2];
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(0x1007) << 4) + 0x108, gUnknown_0855C3BC[phase], gUnknown_0855C3C0[phase], gUnknown_0855C3C4[phase]);
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(0x1007) << 4) + 0x106, gUnknown_0855C3BC[phase], gUnknown_0855C3C0[phase], gUnknown_0855C3C4[phase]);
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(0x1007) << 4) + 0x102, gUnknown_0855C3BC[phase], gUnknown_0855C3C0[phase], gUnknown_0855C3C4[phase]);
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(0x1007) << 4) + 0x105, gUnknown_0855C3BC[phase], gUnknown_0855C3C0[phase], gUnknown_0855C3C4[phase]);
    MultiplyInvertedPaletteRGBComponents((IndexOfSpritePaletteTag(0x1007) << 4) + 0x103, gUnknown_0855C3BC[phase], gUnknown_0855C3C0[phase], gUnknown_0855C3C4[phase]);
}

void PokeballGlowEffect_4(struct Sprite *sprite)
{
    if ((--sprite->data[1]) == 0)
    {
        sprite->data[0]++;
    }
}

void PokeballGlowEffect_5(struct Sprite *sprite)
{
    sprite->data[0]++;
}

void PokeballGlowEffect_6(struct Sprite *sprite)
{
    if (sprite->data[5] == 0 || IsFanfareTaskInactive())
    {
        sprite->data[0]++;
    }
}

void PokeballGlowEffect_7(struct Sprite *sprite)
{
}

void SpriteCB_PokeballGlow(struct Sprite *sprite)
{
    if (gSprites[sprite->data[0]].data[0] > 4)
    {
        FieldEffectFreeGraphicsResources(sprite);
    }
}

u8 PokecenterHealEffectHelper(s16 x, s16 y)
{
    u8 spriteIdAtEnd;
    struct Sprite *sprite;
    spriteIdAtEnd = CreateSpriteAtEnd(&gSpriteTemplate_855C31C, x, y, 0);
    sprite = &gSprites[spriteIdAtEnd];
    sprite->oam.priority = 2;
    sprite->invisible = 1;
    SetSubspriteTables(sprite, &gUnknown_0855C2AC);
    return spriteIdAtEnd;
}

void SpriteCB_PokecenterMonitor(struct Sprite *sprite)
{
    if (sprite->data[0] != 0)
    {
        sprite->data[0] = 0;
        sprite->invisible = 0;
        StartSpriteAnim(sprite, 1);
    }
    if (sprite->animEnded)
    {
        FieldEffectFreeGraphicsResources(sprite);
    }
}

void HallOfFameRecordEffectHelper(s16 a0, s16 a1, s16 a2, u8 a3)
{
    u8 spriteIdAtEnd;
    if (!a3)
    {
        spriteIdAtEnd = CreateSpriteAtEnd(&gSpriteTemplate_855C334, a1, a2, 0);
        SetSubspriteTables(&gSprites[spriteIdAtEnd], &gUnknown_0855C2C4);
    } else
    {
        spriteIdAtEnd = CreateSpriteAtEnd(&gSpriteTemplate_855C34C, a1, a2, 0);
    }
    gSprites[spriteIdAtEnd].invisible = 1;
    gSprites[spriteIdAtEnd].data[0] = a0;
}

void SpriteCB_HallOfFameMonitor(struct Sprite *sprite)
{
    if (gTasks[sprite->data[0]].data[15])
    {
        if (sprite->data[1] == 0 || (--sprite->data[1]) == 0)
        {
            sprite->data[1] = 16;
            sprite->invisible ^= 1;
        }
        sprite->data[2]++;
    }
    if (sprite->data[2] > 127)
    {
        FieldEffectFreeGraphicsResources(sprite);
    }
}

void mapldr_080842E8(void);
void mapldr_08084390(void);
void task00_8084310(u8);
void c3_080843F8(u8);

void sub_80B69DC(void)
{
    SetMainCallback2(CB2_ReturnToField);
    gFieldCallback = mapldr_080842E8;
}

void mapldr_080842E8(void)
{
    pal_fill_black();
    CreateTask(task00_8084310, 0);
    ScriptContext2_Enable();
    FreezeEventObjects();
    gFieldCallback = NULL;
}

void task00_8084310(u8 taskId)
{
    struct Task *task;
    task = &gTasks[taskId];
    if (!task->data[0])
    {
        if (!IsWeatherNotFadingIn())
        {
            return;
        }
        gFieldEffectArguments[0] = GetCursorSelectionMonId();
        if ((int)gFieldEffectArguments[0] > 5)
        {
            gFieldEffectArguments[0] = 0;
        }
        FieldEffectStart(FLDEFF_USE_FLY);
        task->data[0]++;
    }
    if (!FieldEffectActiveListContains(FLDEFF_USE_FLY))
    {
        Overworld_ResetStateAfterFly();
        warp_in();
        SetMainCallback2(CB2_LoadMap);
        gFieldCallback = mapldr_08084390;
        DestroyTask(taskId);
    }
}

void mapldr_08084390(void)
{
    Overworld_PlaySpecialMapMusic();
    pal_fill_black();
    CreateTask(c3_080843F8, 0);
    gEventObjects[gPlayerAvatar.eventObjectId].invisible = 1;
    if (gPlayerAvatar.flags & 0x08)
    {
        EventObjectTurn(&gEventObjects[gPlayerAvatar.eventObjectId], DIR_WEST);
    }
    ScriptContext2_Enable();
    FreezeEventObjects();
    gFieldCallback = NULL;
}

void c3_080843F8(u8 taskId)
{
    struct Task *task;
    task = &gTasks[taskId];
    if (task->data[0] == 0)
    {
        if (gPaletteFade.active)
        {
            return;
        }
        FieldEffectStart(FLDEFF_FLY_IN);
        task->data[0]++;
    }
    if (!FieldEffectActiveListContains(FLDEFF_FLY_IN))
    {
        ScriptContext2_Disable();
        UnfreezeEventObjects();
        DestroyTask(taskId);
    }
}

extern void pal_fill_for_maplights(void);
void sub_80B6B94(u8);
extern void CameraObjectReset2(void);
extern void CameraObjectReset1(void);

void sub_80B6B68(void)
{
    Overworld_PlaySpecialMapMusic();
    pal_fill_for_maplights();
    ScriptContext2_Enable();
    FreezeEventObjects();
    CreateTask(sub_80B6B94, 0);
    gFieldCallback = NULL;
}

void sub_80B6B94(u8 taskId)
{
    struct Task *task;
    task = &gTasks[taskId];
    while (gUnknown_0855C3C8[task->data[0]](task)); // return code signifies whether to continue blocking here
}

bool8 sub_80B6BCC(struct Task *task) // gUnknown_0855C3C8[0]
{
    struct EventObject *playerObject;
    struct Sprite *playerSprite;
    playerObject = &gEventObjects[gPlayerAvatar.eventObjectId];
    playerSprite = &gSprites[gPlayerAvatar.spriteId];
    CameraObjectReset2();
    gEventObjects[gPlayerAvatar.eventObjectId].invisible = 1;
    gPlayerAvatar.preventStep = TRUE;
    EventObjectSetHeldMovement(playerObject, GetFaceDirectionMovementAction(GetPlayerFacingDirection()));
    task->data[4] = playerSprite->subspriteMode;
    playerObject->fixedPriority = 1;
    playerSprite->oam.priority = 1;
    playerSprite->subspriteMode = 2;
    task->data[0]++;
    return TRUE;
}

bool8 sub_80B6C74(struct Task *task) // gUnknown_0855C3C8[1]
{
    if (IsWeatherNotFadingIn())
    {
        task->data[0]++;
    }
    return FALSE;
}

bool8 sub_80B6C90(struct Task *task) // gUnknown_0855C3C8[2]
{
    struct Sprite *sprite;
    s16 centerToCornerVecY;
    sprite = &gSprites[gPlayerAvatar.spriteId];
    centerToCornerVecY = -(sprite->centerToCornerVecY << 1);
    sprite->pos2.y = -(sprite->pos1.y + sprite->centerToCornerVecY + gSpriteCoordOffsetY + centerToCornerVecY);
    task->data[1] = 1;
    task->data[2] = 0;
    gEventObjects[gPlayerAvatar.eventObjectId].invisible = 0;
    PlaySE(SE_RU_HYUU);
    task->data[0]++;
    return FALSE;
}

bool8 sub_80B6D04(struct Task *task)
{
    struct EventObject *eventObject;
    struct Sprite *sprite;

    eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
    sprite = &gSprites[gPlayerAvatar.spriteId];
    sprite->pos2.y += task->data[1];
    if (task->data[1] < 8)
    {
        task->data[2] += task->data[1];
        if (task->data[2] & 0xf)
        {
            task->data[1] <<= 1;
        }
    }
    if (task->data[3] == 0 && sprite->pos2.y >= -16)
    {
        task->data[3]++;
        eventObject->fixedPriority = 0;
        sprite->subspriteMode = task->data[4];
        eventObject->triggerGroundEffectsOnMove = 1;
    }
    if (sprite->pos2.y >= 0)
    {
        PlaySE(SE_W070);
        eventObject->triggerGroundEffectsOnStop = 1;
        eventObject->landingJump = 1;
        sprite->pos2.y = 0;
        task->data[0]++;
    }
    return FALSE;
}

bool8 sub_80B6DBC(struct Task *task)
{
    task->data[0]++;
    task->data[1] = 4;
    task->data[2] = 0;
    SetCameraPanningCallback(NULL);
    return TRUE;
}

bool8 sub_80B6DD8(struct Task *task)
{
    SetCameraPanning(0, task->data[1]);
    task->data[1] = -task->data[1];
    task->data[2]++;
    if ((task->data[2] & 3) == 0)
    {
        task->data[1] >>= 1;
    }
    if (task->data[1] == 0)
    {
        task->data[0]++;
    }
    return FALSE;
}

bool8 sub_80B6E18(struct Task *task)
{
    gPlayerAvatar.preventStep = FALSE;
    ScriptContext2_Disable();
    CameraObjectReset1();
    UnfreezeEventObjects();
    InstallCameraPanAheadCallback();
    DestroyTask(FindTaskIdByFunc(sub_80B6B94));
    return FALSE;
}

void sub_80B6E88(u8);
extern void sub_80E1558(u8);
extern void sub_80AF0B4(void);

void sub_80B6FB8(struct Task *);
void sub_80B7004(struct Task *);
void sub_80B7050(void);
void sub_80B7060(void);
bool8 sub_80859A0(void);
void sub_80B70B4(void);
void sub_80E1570(void);
void sub_80B70DC(u8);

void sub_80B6E4C(u8 a0, u8 priority)
{
    u8 taskId;
    taskId = CreateTask(sub_80B6E88, priority);
    gTasks[taskId].data[1] = 0;
    if (a0 == 0x6a)
    {
        gTasks[taskId].data[1] = 1;
    }
}

void sub_80B6E88(u8 taskId)
{
    struct Task *task;
    task = &gTasks[taskId];
    while (gUnknown_0855C3E4[task->data[0]](task));
}

bool8 sub_80B6EC0(struct Task *task)
{
    FreezeEventObjects();
    CameraObjectReset2();
    sub_80E1558(task->data[1]);
    task->data[0]++;
    return FALSE;
}

bool8 sub_80B6EE0(struct Task *task)
{
    struct EventObject *eventObject;
    eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
    if (!EventObjectIsMovementOverridden(eventObject) || EventObjectClearHeldMovementIfFinished(eventObject))
    {
        EventObjectSetHeldMovement(eventObject, GetFaceDirectionMovementAction(GetPlayerFacingDirection()));
        task->data[0]++;
        task->data[2] = 0;
        task->data[3] = 0;
        if ((u8)task->data[1] == 0)
        {
            task->data[0] = 4;
        }
        PlaySE(SE_ESUKA);
    }
    return FALSE;
}

bool8 sub_80B6F50(struct Task *task)
{
    sub_80B6FB8(task);
    if (task->data[2] > 3)
    {
        sub_80B7050();
        task->data[0]++;
    }
    return FALSE;
}

bool8 sub_80B6F74(struct Task *task)
{
    sub_80B6FB8(task);
    sub_80B7060();
    return FALSE;
}

bool8 sub_80B6F84(struct Task *task)
{
    sub_80B7004(task);
    if (task->data[2] > 3)
    {
        sub_80B7050();
        task->data[0]++;
    }
    return FALSE;
}

bool8 sub_80B6FA8(struct Task *task)
{
    sub_80B7004(task);
    sub_80B7060();
    return FALSE;
}

void sub_80B6FB8(struct Task *task)
{
    struct Sprite *sprite;
    sprite = &gSprites[gPlayerAvatar.spriteId];
    sprite->pos2.x = Cos(0x84, task->data[2]);
    sprite->pos2.y = Sin(0x94, task->data[2]);
    task->data[3]++;
    if (task->data[3] & 1)
    {
        task->data[2]++;
    }
}

void sub_80B7004(struct Task *task)
{
    struct Sprite *sprite;
    sprite = &gSprites[gPlayerAvatar.spriteId];
    sprite->pos2.x = Cos(0x7c, task->data[2]);
    sprite->pos2.y = Sin(0x76, task->data[2]);
    task->data[3]++;
    if (task->data[3] & 1)
    {
        task->data[2]++;
    }
}

void sub_80B7050(void)
{
    music_something();
    sub_80AF0B4();
}

void sub_80B7060(void)
{
    if (!gPaletteFade.active && sub_80859A0() == TRUE)
    {
        sub_80E1570();
        warp_in();
        gFieldCallback = sub_80B70B4;
        SetMainCallback2(CB2_LoadMap);
        DestroyTask(FindTaskIdByFunc(sub_80B6E88));
    }
}

void sub_80B70B4(void)
{
    Overworld_PlaySpecialMapMusic();
    pal_fill_for_maplights();
    ScriptContext2_Enable();
    CreateTask(sub_80B70DC, 0);
    gFieldCallback = NULL;
}

void sub_80B70DC(u8 taskId)
{
    struct Task *task;
    task = &gTasks[taskId];
    while (gUnknown_0855C3FC[task->data[0]](task));
}

bool8 sub_80B7114(struct Task *task)
{
    struct EventObject *eventObject;
    s16 x;
    s16 y;
    u8 behavior;
    CameraObjectReset2();
    eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
    EventObjectSetHeldMovement(eventObject, GetFaceDirectionMovementAction(DIR_EAST));
    PlayerGetDestCoords(&x, &y);
    behavior = MapGridGetMetatileBehaviorAt(x, y);
    task->data[0]++;
    task->data[1] = 16;
    if (behavior == 0x6b)
    {
        behavior = 1;
        task->data[0] = 3;
    } else
    {
        behavior = 0;
    }
    sub_80E1558(behavior);
    return TRUE;
}

bool8 sub_80B7190(struct Task *task)
{
    struct Sprite *sprite;
    sprite = &gSprites[gPlayerAvatar.spriteId];
    sprite->pos2.x = Cos(0x84, task->data[1]);
    sprite->pos2.y = Sin(0x94, task->data[1]);
    task->data[0]++;
    return FALSE;
}

bool8 sub_80B71D0(struct Task *task)
{
    struct Sprite *sprite;
    sprite = &gSprites[gPlayerAvatar.spriteId];
    sprite->pos2.x = Cos(0x84, task->data[1]);
    sprite->pos2.y = Sin(0x94, task->data[1]);
    task->data[2]++;
    if (task->data[2] & 1)
    {
        task->data[1]--;
    }
    if (task->data[1] == 0)
    {
        sprite->pos2.x = 0;
        sprite->pos2.y = 0;
        task->data[0] = 5;
    }
    return FALSE;
}

bool8 sub_80B7230(struct Task *task)
{
    struct Sprite *sprite;
    sprite = &gSprites[gPlayerAvatar.spriteId];
    sprite->pos2.x = Cos(0x7c, task->data[1]);
    sprite->pos2.y = Sin(0x76, task->data[1]);
    task->data[0]++;
    return FALSE;
}

bool8 sub_80B7270(struct Task *task)
{
    struct Sprite *sprite;
    sprite = &gSprites[gPlayerAvatar.spriteId];
    sprite->pos2.x = Cos(0x7c, task->data[1]);
    sprite->pos2.y = Sin(0x76, task->data[1]);
    task->data[2]++;
    if (task->data[2] & 1)
    {
        task->data[1]--;
    }
    if (task->data[1] == 0)
    {
        sprite->pos2.x = 0;
        sprite->pos2.y = 0;
        task->data[0]++;
    }
    return FALSE;
}

extern bool8 sub_80E1584(void);

bool8 sub_80B72D0(struct Task *task)
{
    if (sub_80E1584())
    {
        return FALSE;
    }
    sub_80E1570();
    task->data[0]++;
    return TRUE;
}

bool8 sub_80B72F4(struct Task *task)
{
    struct EventObject *eventObject;
    eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
    if (EventObjectClearHeldMovementIfFinished(eventObject))
    {
        CameraObjectReset1();
        ScriptContext2_Disable();
        EventObjectSetHeldMovement(eventObject, GetWalkNormalMovementAction(DIR_EAST));
        DestroyTask(FindTaskIdByFunc(sub_80B70DC));
    }
    return FALSE;
}

void sub_80B7384(u8);

bool8 FldEff_UseWaterfall(void)
{
    u8 taskId;
    taskId = CreateTask(sub_80B7384, 0xff);
    gTasks[taskId].data[1] = gFieldEffectArguments[0];
    sub_80B7384(taskId);
    return FALSE;
}

void sub_80B7384(u8 taskId)
{
    while (gUnknown_0855C418[gTasks[taskId].data[0]](&gTasks[taskId], &gEventObjects[gPlayerAvatar.eventObjectId]));
}

bool8 sub_80B73D0(struct Task *task, struct EventObject *eventObject)
{
    ScriptContext2_Enable();
    gPlayerAvatar.preventStep = TRUE;
    task->data[0]++;
    return FALSE;
}

bool8 waterfall_1_do_anim_probably(struct Task *task, struct EventObject *eventObject)
{
    ScriptContext2_Enable();
    if (!EventObjectIsMovementOverridden(eventObject))
    {
        EventObjectClearHeldMovementIfFinished(eventObject);
        gFieldEffectArguments[0] = task->data[1];
        FieldEffectStart(FLDEFF_FIELD_MOVE_SHOW_MON_INIT);
        task->data[0]++;
    }
    return FALSE;
}

bool8 waterfall_2_wait_anim_finish_probably(struct Task *task, struct EventObject *eventObject)
{
    if (FieldEffectActiveListContains(FLDEFF_FIELD_MOVE_SHOW_MON))
    {
        return FALSE;
    }
    task->data[0]++;
    return TRUE;
}

bool8 sub_80B7450(struct Task *task, struct EventObject *eventObject)
{
    EventObjectSetHeldMovement(eventObject, GetWalkSlowMovementAction(DIR_NORTH));
    task->data[0]++;
    return FALSE;
}

bool8 sub_80B7478(struct Task *task, struct EventObject *eventObject)
{
    if (!EventObjectClearHeldMovementIfFinished(eventObject))
    {
        return FALSE;
    }
    if (MetatileBehavior_IsWaterfall(eventObject->currentMetatileBehavior))
    {
        task->data[0] = 3;
        return TRUE;
    }
    ScriptContext2_Disable();
    gPlayerAvatar.preventStep = FALSE;
    DestroyTask(FindTaskIdByFunc(sub_80B7384));
    FieldEffectActiveListRemove(FLDEFF_USE_WATERFALL);
    return FALSE;
}

void Task_Dive(u8);
extern int dive_warp(struct MapPosition *, u16);

bool8 FldEff_UseDive(void)
{
    u8 taskId;
    taskId = CreateTask(Task_Dive, 0xff);
    gTasks[taskId].data[15] = gFieldEffectArguments[0];
    gTasks[taskId].data[14] = gFieldEffectArguments[1];
    Task_Dive(taskId);
    return FALSE;
}

void Task_Dive(u8 taskId)
{
    while (gUnknown_0855C42C[gTasks[taskId].data[0]](&gTasks[taskId]));
}

bool8 dive_1_lock(struct Task *task)
{
    gPlayerAvatar.preventStep = TRUE;
    task->data[0]++;
    return FALSE;
}

bool8 dive_2_unknown(struct Task *task)
{
    ScriptContext2_Enable();
    gFieldEffectArguments[0] = task->data[15];
    FieldEffectStart(FLDEFF_FIELD_MOVE_SHOW_MON_INIT);
    task->data[0]++;
    return FALSE;
}

bool8 dive_3_unknown(struct Task *task)
{
    struct MapPosition mapPosition;
    PlayerGetDestCoords(&mapPosition.x, &mapPosition.y);
    if (!FieldEffectActiveListContains(FLDEFF_FIELD_MOVE_SHOW_MON))
    {
        dive_warp(&mapPosition, gEventObjects[gPlayerAvatar.eventObjectId].currentMetatileBehavior);
        DestroyTask(FindTaskIdByFunc(Task_Dive));
        FieldEffectActiveListRemove(FLDEFF_USE_DIVE);
    }
    return FALSE;
}

void sub_80B75F0(u8);
void mapldr_080851BC(void);

void sub_80B75D8(u8 priority)
{
    CreateTask(sub_80B75F0, priority);
}

void sub_80B75F0(u8 taskId)
{
    while (gUnknown_0855C438[gTasks[taskId].data[0]](&gTasks[taskId], &gEventObjects[gPlayerAvatar.eventObjectId], &gSprites[gPlayerAvatar.spriteId]));
}

bool8 sub_80B764C(struct Task *task, struct EventObject *eventObject, struct Sprite *sprite)
{
    FreezeEventObjects();
    CameraObjectReset2();
    SetCameraPanningCallback(NULL);
    gPlayerAvatar.preventStep = TRUE;
    eventObject->fixedPriority = 1;
    task->data[1] = 1;
    task->data[0]++;
    return TRUE;
}

bool8 sub_80B7684(struct Task *task, struct EventObject *eventObject, struct Sprite *sprite)
{
    SetCameraPanning(0, task->data[1]);
    task->data[1] = -task->data[1];
    task->data[2]++;
    if (task->data[2] > 7)
    {
        task->data[2] = 0;
        task->data[0]++;
    }
    return FALSE;
}

bool8 sub_80B76B8(struct Task *task, struct EventObject *eventObject, struct Sprite *sprite)
{
    sprite->pos2.y = 0;
    task->data[3] = 1;
    gFieldEffectArguments[0] = eventObject->currentCoords.x;
    gFieldEffectArguments[1] = eventObject->currentCoords.y;
    gFieldEffectArguments[2] = sprite->subpriority - 1;
    gFieldEffectArguments[3] = sprite->oam.priority;
    FieldEffectStart(FLDEFF_LAVARIDGE_GYM_WARP);
    PlaySE(SE_W153);
    task->data[0]++;
    return TRUE;
}

bool8 sub_80B7704(struct Task *task, struct EventObject *eventObject, struct Sprite *sprite)
{
    s16 centerToCornerVecY;
    SetCameraPanning(0, task->data[1]);
    if (task->data[1] = -task->data[1], ++task->data[2] <= 17)
    {
        if (!(task->data[2] & 1) && (task->data[1] <= 3))
        {
            task->data[1] <<= 1;
        }
    } else if (!(task->data[2] & 4) && (task->data[1] > 0))
    {
        task->data[1] >>= 1;
    }
    if (task->data[2] > 6)
    {
        centerToCornerVecY = -(sprite->centerToCornerVecY << 1);
        if (sprite->pos2.y > -(sprite->pos1.y + sprite->centerToCornerVecY + gSpriteCoordOffsetY + centerToCornerVecY))
        {
            sprite->pos2.y -= task->data[3];
            if (task->data[3] <= 7)
            {
                task->data[3]++;
            }
        } else
        {
            task->data[4] = 1;
        }
    }
    if (task->data[5] == 0 && sprite->pos2.y < -0x10)
    {
        task->data[5]++;
        eventObject->fixedPriority = 1;
        sprite->oam.priority = 1;
        sprite->subspriteMode = 2;
    }
    if (task->data[1] == 0 && task->data[4] != 0)
    {
        task->data[0]++;
    }
    return FALSE;
}

bool8 sub_80B77F8(struct Task *task, struct EventObject *eventObject, struct Sprite *sprite)
{
    music_something();
    sub_80AF0B4();
    task->data[0]++;
    return FALSE;
}

bool8 sub_80B7814(struct Task *task, struct EventObject *eventObject, struct Sprite *sprite)
{
    if (!gPaletteFade.active && sub_80859A0() == TRUE)
    {
        warp_in();
        gFieldCallback = mapldr_080851BC;
        SetMainCallback2(CB2_LoadMap);
        DestroyTask(FindTaskIdByFunc(sub_80B75F0));
    }
    return FALSE;
}

void sub_80B7890(u8);

void mapldr_080851BC(void)
{
    Overworld_PlaySpecialMapMusic();
    pal_fill_for_maplights();
    ScriptContext2_Enable();
    gFieldCallback = NULL;
    CreateTask(sub_80B7890, 0);
}

void sub_80B7890(u8 taskId)
{
    while (gUnknown_0855C450[gTasks[taskId].data[0]](&gTasks[taskId], &gEventObjects[gPlayerAvatar.eventObjectId], &gSprites[gPlayerAvatar.spriteId]));
}

bool8 sub_80B78EC(struct Task *task, struct EventObject *eventObject, struct Sprite *sprite)
{
    CameraObjectReset2();
    FreezeEventObjects();
    gPlayerAvatar.preventStep = TRUE;
    eventObject->invisible = 1;
    task->data[0]++;
    return FALSE;
}

bool8 sub_80B791C(struct Task *task, struct EventObject *eventObject, struct Sprite *sprite)
{
    if (IsWeatherNotFadingIn())
    {
        gFieldEffectArguments[0] = eventObject->currentCoords.x;
        gFieldEffectArguments[1] = eventObject->currentCoords.y;
        gFieldEffectArguments[2] = sprite->subpriority - 1;
        gFieldEffectArguments[3] = sprite->oam.priority;
        task->data[1] = FieldEffectStart(FLDEFF_POP_OUT_OF_ASH);
        task->data[0]++;
    }
    return FALSE;
}

bool8 sub_80B7968(struct Task *task, struct EventObject *eventObject, struct Sprite *sprite)
{
    sprite = &gSprites[task->data[1]];
    if (sprite->animCmdIndex > 1)
    {
        task->data[0]++;
        eventObject->invisible = 0;
        CameraObjectReset1();
        PlaySE(SE_W091);
        EventObjectSetHeldMovement(eventObject, GetJumpMovementAction(DIR_EAST));
    }
    return FALSE;
}

bool8 sub_80B79BC(struct Task *task, struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectClearHeldMovementIfFinished(eventObject))
    {
        gPlayerAvatar.preventStep = FALSE;
        ScriptContext2_Disable();
        UnfreezeEventObjects();
        DestroyTask(FindTaskIdByFunc(sub_80B7890));
    }
    return FALSE;
}

extern const struct SpriteTemplate *const gFieldEffectObjectTemplatePointers[36];

u8 FldEff_LavaridgeGymWarp(void)
{
    u8 spriteId;
    sub_80930E0((s16 *)&gFieldEffectArguments[0], (s16 *)&gFieldEffectArguments[1], 8, 8);
    spriteId = CreateSpriteAtEnd(gFieldEffectObjectTemplatePointers[33], gFieldEffectArguments[0], gFieldEffectArguments[1], gFieldEffectArguments[2]);
    gSprites[spriteId].oam.priority = gFieldEffectArguments[3];
    gSprites[spriteId].coordOffsetEnabled = 1;
    return spriteId;
}

void sub_80B7A58(struct Sprite *sprite)
{
    if (sprite->animEnded)
    {
        FieldEffectStop(sprite, FLDEFF_LAVARIDGE_GYM_WARP);
    }
}

void sub_80B7A8C(u8);

void sub_80B7A74(u8 priority)
{
    CreateTask(sub_80B7A8C, priority);
}

void sub_80B7A8C(u8 taskId)
{
    while(gUnknown_0855C460[gTasks[taskId].data[0]](&gTasks[taskId], &gEventObjects[gPlayerAvatar.eventObjectId], &gSprites[gPlayerAvatar.spriteId]));
}

bool8 sub_80B7AE8(struct Task *task, struct EventObject *eventObject, struct Sprite *sprite)
{
    FreezeEventObjects();
    CameraObjectReset2();
    gPlayerAvatar.preventStep = TRUE;
    eventObject->fixedPriority = 1;
    task->data[0]++;
    return FALSE;
}

bool8 sub_80B7B18(struct Task *task, struct EventObject *eventObject, struct Sprite *sprite)
{
    if (EventObjectClearHeldMovementIfFinished(eventObject))
    {
        if (task->data[1] > 3)
        {
            gFieldEffectArguments[0] = eventObject->currentCoords.x;
            gFieldEffectArguments[1] = eventObject->currentCoords.y;
            gFieldEffectArguments[2] = sprite->subpriority - 1;
            gFieldEffectArguments[3] = sprite->oam.priority;
            task->data[1] = FieldEffectStart(FLDEFF_POP_OUT_OF_ASH);
            task->data[0]++;
        } else
        {
            task->data[1]++;
            EventObjectSetHeldMovement(eventObject, GetWalkInPlaceFastestMovementAction(eventObject->facingDirection));
            PlaySE(SE_FU_ZUZUZU);
        }
    }
    return FALSE;
}

bool8 sub_80B7B94(struct Task *task, struct EventObject *eventObject, struct Sprite *sprite)
{
    if (gSprites[task->data[1]].animCmdIndex == 2)
    {
        eventObject->invisible = 1;
        task->data[0]++;
    }
    return FALSE;
}

bool8 sub_80B7BCC(struct Task *task, struct EventObject *eventObject, struct Sprite *sprite)
{
    if (!FieldEffectActiveListContains(FLDEFF_POP_OUT_OF_ASH))
    {
        music_something();
        sub_80AF0B4();
        task->data[0]++;
    }
    return FALSE;
}

void sub_80B7CE4(u8);
void mapldr_080859D4(void);

bool8 sub_80B7BF4(struct Task *task, struct EventObject *eventObject, struct Sprite *sprite)
{
    if (!gPaletteFade.active && sub_80859A0() == TRUE)
    {
        warp_in();
        gFieldCallback = sub_80B6B68;
        SetMainCallback2(CB2_LoadMap);
        DestroyTask(FindTaskIdByFunc(sub_80B7A8C));
    }
    return FALSE;
}

u8 FldEff_PopOutOfAsh(void)
{
    u8 spriteId;
    sub_80930E0((s16 *)&gFieldEffectArguments[0], (s16 *)&gFieldEffectArguments[1], 8, 8);
    spriteId = CreateSpriteAtEnd(gFieldEffectObjectTemplatePointers[32], gFieldEffectArguments[0], gFieldEffectArguments[1], gFieldEffectArguments[2]);
    gSprites[spriteId].oam.priority = gFieldEffectArguments[3];
    gSprites[spriteId].coordOffsetEnabled = 1;
    return spriteId;
}

void sub_80B7CAC(struct Sprite *sprite)
{
    if (sprite->animEnded)
    {
        FieldEffectStop(sprite, FLDEFF_POP_OUT_OF_ASH);
    }
}

void sub_80B7CC8(void)
{
    ScriptContext2_Enable();
    FreezeEventObjects();
    CreateTask(sub_80B7CE4, 0x50);
}

void sub_80B7CE4(u8 taskId)
{
    gUnknown_0855C474[gTasks[taskId].data[0]](&gTasks[taskId]);
}

void sub_80B7D14(struct Task *task)
{
    task->data[0]++;
    task->data[14] = 64;
    task->data[15] = GetPlayerFacingDirection();
}

void sub_80B7D34(struct Task *task)
{
    struct EventObject *eventObject;
    u8 spinDirections[5] = {1, 3, 4, 2, 1};
    if (task->data[14] != 0 && (--task->data[14]) == 0)
    {
        music_something();
        sub_80AF0B4();
    }
    eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
    if (!EventObjectIsMovementOverridden(eventObject) || EventObjectClearHeldMovementIfFinished(eventObject))
    {
        if (task->data[14] == 0 && !gPaletteFade.active && sub_80859A0() == TRUE)
        {
            SetEventObjectDirection(eventObject, task->data[15]);
            sub_8084E14();
            warp_in();
            gFieldCallback = mapldr_080859D4;
            SetMainCallback2(CB2_LoadMap);
            DestroyTask(FindTaskIdByFunc(sub_80B7CE4));
        } else if (task->data[1] == 0 || (--task->data[1]) == 0)
        {
            EventObjectSetHeldMovement(eventObject, GetFaceDirectionMovementAction(spinDirections[eventObject->facingDirection]));
            if (task->data[2] < 12)
            {
                task->data[2]++;
            }
            task->data[1] = 8 >> (task->data[2] >> 2);
        }
    }
}

void (*const gUnknown_0855C484[])(struct Task *) = {
    sub_80B7EC4,
    sub_80B7EE8
};

void sub_80B7E94(u8);

void mapldr_080859D4(void)
{
    Overworld_PlaySpecialMapMusic();
    pal_fill_for_maplights();
    ScriptContext2_Enable();
    FreezeEventObjects();
    gFieldCallback = NULL;
    gEventObjects[gPlayerAvatar.eventObjectId].invisible = 1;
    CreateTask(sub_80B7E94, 0);
}

void sub_80B7E94(u8 taskId)
{
    gUnknown_0855C484[gTasks[taskId].data[0]](&gTasks[taskId]);
}

void sub_80B7EC4(struct Task *task)
{
    if (IsWeatherNotFadingIn())
    {
        task->data[0]++;
        task->data[15] = GetPlayerFacingDirection();
    }
}

void sub_80B7EE8(struct Task *task)
{
    u8 spinDirections[5] = {1, 3, 4, 2, 1};
    struct EventObject *eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
    if (task->data[1] == 0 || (--task->data[1]) == 0)
    {
        if (EventObjectIsMovementOverridden(eventObject) && !EventObjectClearHeldMovementIfFinished(eventObject))
        {
            return;
        }
        if (task->data[2] >= 32 && task->data[15] == GetPlayerFacingDirection())
        {
            eventObject->invisible = 0;
            ScriptContext2_Disable();
            UnfreezeEventObjects();
            DestroyTask(FindTaskIdByFunc(sub_80B7E94));
            return;
        }
        EventObjectSetHeldMovement(eventObject, GetFaceDirectionMovementAction(spinDirections[eventObject->facingDirection]));
        if (task->data[2] < 32)
        {
            task->data[2]++;
        }
        task->data[1] = task->data[2] >> 2;
    }
    eventObject->invisible ^= 1;
}

static void ExecuteTeleportFieldEffectTask(u8);
static void TeleportFieldEffectTask1(struct Task*);
static void TeleportFieldEffectTask2(struct Task*);
static void TeleportFieldEffectTask3(struct Task*);
static void TeleportFieldEffectTask4(struct Task*);
static void mapldr_08085D88(void);

void CreateTeleportFieldEffectTask(void)
{
    CreateTask(ExecuteTeleportFieldEffectTask, 0);
}

static void (*const sTeleportFieldEffectTasks[])(struct Task *) = {
    TeleportFieldEffectTask1,
    TeleportFieldEffectTask2,
    TeleportFieldEffectTask3,
    TeleportFieldEffectTask4
};

static void ExecuteTeleportFieldEffectTask(u8 taskId)
{
    sTeleportFieldEffectTasks[gTasks[taskId].data[0]](&gTasks[taskId]);
}

static void TeleportFieldEffectTask1(struct Task *task)
{
    ScriptContext2_Enable();
    FreezeEventObjects();
    CameraObjectReset2();
    task->data[15] = GetPlayerFacingDirection();
    task->data[0]++;
}

static void TeleportFieldEffectTask2(struct Task *task)
{
    u8 spinDirections[5] = {DIR_SOUTH, DIR_WEST, DIR_EAST, DIR_NORTH, DIR_SOUTH};
    struct EventObject *eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
    if (task->data[1] == 0 || (--task->data[1]) == 0)
    {
        EventObjectTurn(eventObject, spinDirections[eventObject->facingDirection]);
        task->data[1] = 8;
        task->data[2]++;
    }
    if (task->data[2] > 7 && task->data[15] == eventObject->facingDirection)
    {
        task->data[0]++;
        task->data[1] = 4;
        task->data[2] = 8;
        task->data[3] = 1;
        PlaySE(SE_TK_WARPIN);
    }
}

static void TeleportFieldEffectTask3(struct Task *task)
{
    u8 spinDirections[5] = {DIR_SOUTH, DIR_WEST, DIR_EAST, DIR_NORTH, DIR_SOUTH};
    struct EventObject *eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
    struct Sprite *sprite = &gSprites[gPlayerAvatar.spriteId];
    if ((--task->data[1]) <= 0)
    {
        task->data[1] = 4;
        EventObjectTurn(eventObject, spinDirections[eventObject->facingDirection]);
    }
    sprite->pos1.y -= task->data[3];
    task->data[4] += task->data[3];
    if ((--task->data[2]) <= 0 && (task->data[2] = 4, task->data[3] < 8))
    {
        task->data[3] <<= 1;
    }
    if (task->data[4] > 8 && (sprite->oam.priority = 1, sprite->subspriteMode != 0))
    {
        sprite->subspriteMode = 2;
    }
    if (task->data[4] >= 0xa8)
    {
        task->data[0]++;
        music_something();
        sub_80AF0B4();
    }
}

static void TeleportFieldEffectTask4(struct Task *task)
{
    if (!gPaletteFade.active)
    {
        if (task->data[5] == FALSE)
        {
            sub_81BE72C();
            task->data[5] = TRUE;
        }

        if (sub_80859A0() == TRUE)
        {
            Overworld_SetWarpDestToLastHealLoc();
            warp_in();
            SetMainCallback2(CB2_LoadMap);
            gFieldCallback = mapldr_08085D88;
            DestroyTask(FindTaskIdByFunc(ExecuteTeleportFieldEffectTask));
        }
    }
}

void sub_80B8250(u8);

static void mapldr_08085D88(void)
{
    Overworld_PlaySpecialMapMusic();
    pal_fill_for_maplights();
    ScriptContext2_Enable();
    FreezeEventObjects();
    gFieldCallback = NULL;
    gEventObjects[gPlayerAvatar.eventObjectId].invisible = 1;
    CameraObjectReset2();
    CreateTask(sub_80B8250, 0);
}

void (*const gUnknown_0855C49C[])(struct Task *) = {
    sub_80B8280,
    sub_80B830C,
    sub_80B8410
};

void sub_80B8250(u8 taskId)
{
    gUnknown_0855C49C[gTasks[taskId].data[0]](&gTasks[taskId]);
}

void sub_80B8280(struct Task *task)
{
    struct Sprite *sprite;
    s16 centerToCornerVecY;
    if (IsWeatherNotFadingIn())
    {
        sprite = &gSprites[gPlayerAvatar.spriteId];
        centerToCornerVecY = -(sprite->centerToCornerVecY << 1);
        sprite->pos2.y = -(sprite->pos1.y + sprite->centerToCornerVecY + gSpriteCoordOffsetY + centerToCornerVecY);
        gEventObjects[gPlayerAvatar.eventObjectId].invisible = 0;
        task->data[0]++;
        task->data[1] = 8;
        task->data[2] = 1;
        task->data[14] = sprite->subspriteMode;
        task->data[15] = GetPlayerFacingDirection();
        PlaySE(SE_TK_WARPIN);
    }
}

void sub_80B830C(struct Task *task)
{
    u8 spinDirections[5] = {1, 3, 4, 2, 1};
    struct EventObject *eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
    struct Sprite *sprite = &gSprites[gPlayerAvatar.spriteId];
    if ((sprite->pos2.y += task->data[1]) >= -8)
    {
        if (task->data[13] == 0)
        {
            task->data[13]++;
            eventObject->triggerGroundEffectsOnMove = 1;
            sprite->subspriteMode = task->data[14];
        }
    } else
    {
        sprite->oam.priority = 1;
        if (sprite->subspriteMode != 0)
        {
            sprite->subspriteMode = 2;
        }
    }
    if (sprite->pos2.y >= -0x30 && task->data[1] > 1 && !(sprite->pos2.y & 1))
    {
        task->data[1]--;
    }
    if ((--task->data[2]) == 0)
    {
        task->data[2] = 4;
        EventObjectTurn(eventObject, spinDirections[eventObject->facingDirection]);
    }
    if (sprite->pos2.y >= 0)
    {
        sprite->pos2.y = 0;
        task->data[0]++;
        task->data[1] = 1;
        task->data[2] = 0;
    }
}

void sub_80B8410(struct Task *task)
{
    u8 spinDirections[5] = {1, 3, 4, 2, 1};
    struct EventObject *eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
    if ((--task->data[1]) == 0)
    {
        EventObjectTurn(eventObject, spinDirections[eventObject->facingDirection]);
        task->data[1] = 8;
        if ((++task->data[2]) > 4 && task->data[14] == eventObject->facingDirection)
        {
            ScriptContext2_Disable();
            CameraObjectReset1();
            UnfreezeEventObjects();
            DestroyTask(FindTaskIdByFunc(sub_80B8250));
        }
    }
}

void sub_80B8554(u8);
void sub_80B88B4(u8);
u8 sub_80B8C60(u32, u32, u32);
void sub_80B880C(void);
void sub_80B8874(u16);
void sub_80B8CC0(struct Sprite *);

bool8 FldEff_FieldMoveShowMon(void)
{
    u8 taskId;
    if (is_map_type_1_2_3_5_or_6(Overworld_GetMapTypeOfSaveblockLocation()) == TRUE)
    {
        taskId = CreateTask(sub_80B8554, 0xff);
    } else
    {
        taskId = CreateTask(sub_80B88B4, 0xff);
    }
    gTasks[taskId].data[15] = sub_80B8C60(gFieldEffectArguments[0], gFieldEffectArguments[1], gFieldEffectArguments[2]);
    return FALSE;
}

bool8 FldEff_FieldMoveShowMonInit(void)
{
    struct Pokemon *pokemon;
    u32 flag = gFieldEffectArguments[0] & 0x80000000;
    pokemon = &gPlayerParty[(u8)gFieldEffectArguments[0]];
    gFieldEffectArguments[0] = GetMonData(pokemon, MON_DATA_SPECIES);
    gFieldEffectArguments[1] = GetMonData(pokemon, MON_DATA_OT_ID);
    gFieldEffectArguments[2] = GetMonData(pokemon, MON_DATA_PERSONALITY);
    gFieldEffectArguments[0] |= flag;
    FieldEffectStart(FLDEFF_FIELD_MOVE_SHOW_MON);
    FieldEffectActiveListRemove(FLDEFF_FIELD_MOVE_SHOW_MON_INIT);
    return FALSE;
}

void (*const gUnknown_0855C4A8[])(struct Task *) = {
    sub_80B8584,
    sub_80B85F8,
    sub_80B8660,
    sub_80B86EC,
    sub_80B871C,
    sub_80B8770,
    overworld_bg_setup_2,
};

void sub_80B8554(u8 taskId)
{
    gUnknown_0855C4A8[gTasks[taskId].data[0]](&gTasks[taskId]);
}

void sub_80B8584(struct Task *task)
{
    task->data[11] = REG_WININ;
    task->data[12] = REG_WINOUT;
    StoreWordInTwoHalfwords(&task->data[13], (u32)gMain.vblankCallback);
    task->data[1] = 0xf0f1;
    task->data[2] = 0x5051;
    task->data[3] = 0x3f;
    task->data[4] = 0x3e;
    SetGpuReg(REG_OFFSET_WIN0H, task->data[1]);
    SetGpuReg(REG_OFFSET_WIN0V, task->data[2]);
    SetGpuReg(REG_OFFSET_WININ, task->data[3]);
    SetGpuReg(REG_OFFSET_WINOUT, task->data[4]);
    SetVBlankCallback(sub_80B880C);
    task->data[0]++;
}

void sub_80B85F8(struct Task *task)
{
    u16 offset;
    u16 delta;
    offset = ((REG_BG0CNT >> 2) << 14);
    delta = ((REG_BG0CNT >> 8) << 11);
    CpuCopy16(gFieldMoveStreaksTiles, (void *)(VRAM + offset), 0x200);
    CpuFill32(0, (void *)(VRAM + delta), 0x800);
    LoadPalette(gFieldMoveStreaksPalette, 0xf0, 0x20);
    sub_80B8874(delta);
    task->data[0]++;
}

void sub_80B8660(struct Task *task)
{
    s16 v0;
    s16 v2;
    s16 v3;
    task->data[5] -= 16;
    v0 = ((u16)task->data[1] >> 8);
    v2 = ((u16)task->data[2] >> 8);
    v3 = ((u16)task->data[2] & 0xff);
    v0 -= 16;
    v2 -= 2;
    v3 += 2;
    if (v0 < 0)
    {
        v0 = 0;
    }
    if (v2 < 0x28)
    {
        v2 = 0x28;
    }
    if (v3 > 0x78)
    {
        v3 = 0x78;
    }
    task->data[1] = (v0 << 8) | (task->data[1] & 0xff);
    task->data[2] = (v2 << 8) | v3;
    if (v0 == 0 && v2 == 0x28 && v3 == 0x78)
    {
        gSprites[task->data[15]].callback = sub_80B8CC0;
        task->data[0]++;
    }
}

void sub_80B86EC(struct Task *task)
{
    task->data[5] -= 16;
    if (gSprites[task->data[15]].data[7])
    {
        task->data[0]++;
    }
}

void sub_80B871C(struct Task *task)
{
    s16 v2;
    s16 v3;
    task->data[5] -= 16;
    v2 = (task->data[2] >> 8);
    v3 = (task->data[2] & 0xff);
    v2 += 6;
    v3 -= 6;
    if (v2 > 0x50)
    {
        v2 = 0x50;
    }
    if (v3 < 0x51)
    {
        v3 = 0x51;
    }
    task->data[2] = (v2 << 8) | v3;
    if (v2 == 0x50 && v3 == 0x51)
    {
        task->data[0]++;
    }
}

void sub_80B8770(struct Task *task)
{
    u16 bg0cnt;
    bg0cnt = (REG_BG0CNT >> 8) << 11;
    CpuFill32(0, (void *)VRAM + bg0cnt, 0x800);
    task->data[1] = 0xf1;
    task->data[2] = 0xa1;
    task->data[3] = task->data[11];
    task->data[4] = task->data[12];
    task->data[0]++;
}

void overworld_bg_setup_2(struct Task *task)
{
    IntrCallback callback;
    LoadWordFromTwoHalfwords((u16 *)&task->data[13], (u32 *)&callback);
    SetVBlankCallback(callback);
    sub_8197200();
    FreeResourcesAndDestroySprite(&gSprites[task->data[15]], task->data[15]);
    FieldEffectActiveListRemove(FLDEFF_FIELD_MOVE_SHOW_MON);
    DestroyTask(FindTaskIdByFunc(sub_80B8554));
}

void sub_80B880C(void)
{
    struct Task *task;
    IntrCallback callback;
    task = &gTasks[FindTaskIdByFunc(sub_80B8554)];
    LoadWordFromTwoHalfwords((u16 *)&task->data[13], (u32 *)&callback);
    callback();
    SetGpuReg(REG_OFFSET_WIN0H, task->data[1]);
    SetGpuReg(REG_OFFSET_WIN0V, task->data[2]);
    SetGpuReg(REG_OFFSET_WININ, task->data[3]);
    SetGpuReg(REG_OFFSET_WINOUT, task->data[4]);
    SetGpuReg(REG_OFFSET_BG0HOFS, task->data[5]);
    SetGpuReg(REG_OFFSET_BG0VOFS, task->data[6]);
}

void sub_80B8874(u16 offs)
{
    u16 i;
    u16 *dest;
    dest = (u16 *)(VRAM + 0x140 + offs);
    for (i = 0; i < 0x140; i++, dest++)
    {
        *dest = gFieldMoveStreaksTilemap[i] | 0xf000;
    }
}

void sub_80B8AE0(void);
bool8 sub_80B8B38(struct Task *);
void sub_80B8B28(struct Task *);
bool8 sub_80B8BF0(struct Task *);

void (*const gUnknown_0855C4C4[])(struct Task *) = {
    sub_80B88E4,
    sub_80B8920,
    sub_80B898C,
    sub_80B89DC,
    sub_80B8A0C,
    sub_80B8A44,
    sub_80B8A64,
};

void sub_80B88B4(u8 taskId)
{
    gUnknown_0855C4C4[gTasks[taskId].data[0]](&gTasks[taskId]);
}

void sub_80B88E4(struct Task *task)
{
    SetGpuReg(REG_OFFSET_BG0HOFS, task->data[1]);
    SetGpuReg(REG_OFFSET_BG0VOFS, task->data[2]);
    StoreWordInTwoHalfwords((u16 *)&task->data[13], (u32)gMain.vblankCallback);
    SetVBlankCallback(sub_80B8AE0);
    task->data[0]++;
}

void sub_80B8920(struct Task *task)
{
    u16 offset;
    u16 delta;
    offset = ((REG_BG0CNT >> 2) << 14);
    delta = ((REG_BG0CNT >> 8) << 11);
    task->data[12] = delta;
    CpuCopy16(gDarknessFieldMoveStreaksTiles, (void *)(VRAM + offset), 0x80);
    CpuFill32(0, (void *)(VRAM + delta), 0x800);
    LoadPalette(gDarknessFieldMoveStreaksPalette, 0xf0, 0x20);
    task->data[0]++;
}

void sub_80B898C(struct Task *task)
{
    if (sub_80B8B38(task))
    {
        SetGpuReg(REG_OFFSET_WIN1H, 0x00f0);
        SetGpuReg(REG_OFFSET_WIN1V, 0x2878);
        gSprites[task->data[15]].callback = sub_80B8CC0;
        task->data[0]++;
    }
    sub_80B8B28(task);
}

void sub_80B89DC(struct Task *task)
{
    sub_80B8B28(task);
    if (gSprites[task->data[15]].data[7])
    {
        task->data[0]++;
    }
}

void sub_80B8A0C(struct Task *task)
{
    sub_80B8B28(task);
    task->data[3] = task->data[1] & 7;
    task->data[4] = 0;
    SetGpuReg(REG_OFFSET_WIN1H, 0xffff);
    SetGpuReg(REG_OFFSET_WIN1V, 0xffff);
    task->data[0]++;
}

void sub_80B8A44(struct Task *task)
{
    sub_80B8B28(task);
    if (sub_80B8BF0(task))
    {
        task->data[0]++;
    }
}

void sub_80B8A64(struct Task *task)
{
    IntrCallback intrCallback;
    u16 bg0cnt;
    bg0cnt = (REG_BG0CNT >> 8) << 11;
    CpuFill32(0, (void *)VRAM + bg0cnt, 0x800);
    LoadWordFromTwoHalfwords((u16 *)&task->data[13], (u32 *)&intrCallback);
    SetVBlankCallback(intrCallback);
    sub_8197200();
    FreeResourcesAndDestroySprite(&gSprites[task->data[15]], task->data[15]);
    FieldEffectActiveListRemove(FLDEFF_FIELD_MOVE_SHOW_MON);
    DestroyTask(FindTaskIdByFunc(sub_80B88B4));
}

void sub_80B8AE0(void)
{
    IntrCallback intrCallback;
    struct Task *task;
    task = &gTasks[FindTaskIdByFunc(sub_80B88B4)];
    LoadWordFromTwoHalfwords((u16 *)&task->data[13], (u32 *)&intrCallback);
    intrCallback();
    SetGpuReg(REG_OFFSET_BG0HOFS, task->data[1]);
    SetGpuReg(REG_OFFSET_BG0VOFS, task->data[2]);
}

void sub_80B8B28(struct Task *task)
{
    task->data[1] -= 16;
    task->data[3] += 16;
}

#ifdef NONMATCHING
bool8 sub_80B8B38(struct Task *task)
{
    u16 i;
    u16 srcOffs;
    u16 dstOffs;
    u16 *dest;
    if (task->data[4] >= 32)
    {
        return TRUE;
    }
    dstOffs = (task->data[3] >> 3) & 0x1f;
    if (dstOffs >= task->data[4])
    {
        dstOffs = (32 - dstOffs) & 0x1f;
        srcOffs = (32 - task->data[4]) & 0x1f;
        dest = (u16 *)(VRAM + 0x140 + (u16)task->data[12]);
        for (i=0; i<10; i++)
        {
            dest[dstOffs + i * 32] = gDarknessFieldMoveStreaksTilemap[srcOffs + i * 32] | 0xf000;
            dest[((dstOffs + 1) & 0x1f) + i * 32] = gDarknessFieldMoveStreaksTilemap[((srcOffs + 1) & 0x1f) + i * 32] | 0xf000;
        }
        task->data[4] += 2;
    }
    return FALSE;
}
#else
NAKED
bool8 sub_80B8B38(struct Task *task)
{
    asm_unified("\tpush {r4-r7,lr}\n"
                    "\tmov r7, r10\n"
                    "\tmov r6, r9\n"
                    "\tmov r5, r8\n"
                    "\tpush {r5-r7}\n"
                    "\tsub sp, 0x4\n"
                    "\tadds r5, r0, 0\n"
                    "\tldrh r2, [r5, 0x10]\n"
                    "\tmovs r1, 0x10\n"
                    "\tldrsh r0, [r5, r1]\n"
                    "\tcmp r0, 0x1F\n"
                    "\tble _08088724\n"
                    "\tmovs r0, 0x1\n"
                    "\tb _080887A8\n"
                    "_08088724:\n"
                    "\tldrh r0, [r5, 0xE]\n"
                    "\tlsls r0, 16\n"
                    "\tasrs r3, r0, 19\n"
                    "\tmovs r1, 0x1F\n"
                    "\tands r3, r1\n"
                    "\tmovs r4, 0x10\n"
                    "\tldrsh r0, [r5, r4]\n"
                    "\tcmp r3, r0\n"
                    "\tblt _080887A6\n"
                    "\tmovs r0, 0x20\n"
                    "\tsubs r3, r0, r3\n"
                    "\tands r3, r1\n"
                    "\tsubs r0, r2\n"
                    "\tmov r12, r0\n"
                    "\tmov r7, r12\n"
                    "\tands r7, r1\n"
                    "\tmov r12, r7\n"
                    "\tldrh r0, [r5, 0x20]\n"
                    "\tldr r1, _080887B8 @ =0x06000140\n"
                    "\tadds r1, r0\n"
                    "\tmov r8, r1\n"
                    "\tmovs r4, 0\n"
                    "\tldr r7, _080887BC @ =gDarknessFieldMoveStreaksTilemap\n"
                    "\tmov r10, r7\n"
                    "\tmovs r0, 0xF0\n"
                    "\tlsls r0, 8\n"
                    "\tmov r9, r0\n"
                    "\tadds r1, r3, 0x1\n"
                    "\tmovs r0, 0x1F\n"
                    "\tands r1, r0\n"
                    "\tstr r1, [sp]\n"
                    "\tmov r6, r12\n"
                    "\tadds r6, 0x1\n"
                    "\tands r6, r0\n"
                    "_08088768:\n"
                    "\tlsls r1, r4, 5\n"
                    "\tadds r2, r1, r3\n"
                    "\tlsls r2, 1\n"
                    "\tadd r2, r8\n"
                    "\tmov r7, r12\n"
                    "\tadds r0, r7, r1\n"
                    "\tlsls r0, 1\n"
                    "\tadd r0, r10\n"
                    "\tldrh r0, [r0]\n"
                    "\tmov r7, r9\n"
                    "\torrs r0, r7\n"
                    "\tstrh r0, [r2]\n"
                    "\tldr r0, [sp]\n"
                    "\tadds r2, r1, r0\n"
                    "\tlsls r2, 1\n"
                    "\tadd r2, r8\n"
                    "\tadds r1, r6, r1\n"
                    "\tlsls r1, 1\n"
                    "\tadd r1, r10\n"
                    "\tldrh r0, [r1]\n"
                    "\tmov r1, r9\n"
                    "\torrs r0, r1\n"
                    "\tstrh r0, [r2]\n"
                    "\tadds r0, r4, 0x1\n"
                    "\tlsls r0, 16\n"
                    "\tlsrs r4, r0, 16\n"
                    "\tcmp r4, 0x9\n"
                    "\tbls _08088768\n"
                    "\tldrh r0, [r5, 0x10]\n"
                    "\tadds r0, 0x2\n"
                    "\tstrh r0, [r5, 0x10]\n"
                    "_080887A6:\n"
                    "\tmovs r0, 0\n"
                    "_080887A8:\n"
                    "\tadd sp, 0x4\n"
                    "\tpop {r3-r5}\n"
                    "\tmov r8, r3\n"
                    "\tmov r9, r4\n"
                    "\tmov r10, r5\n"
                    "\tpop {r4-r7}\n"
                    "\tpop {r1}\n"
                    "\tbx r1\n"
                    "\t.align 2, 0\n"
                    "_080887B8: .4byte 0x06000140\n"
                    "_080887BC: .4byte gDarknessFieldMoveStreaksTilemap");
}
#endif

bool8 sub_80B8BF0(struct Task *task)
{
    u16 i;
    u16 dstOffs;
    u16 *dest;
    if (task->data[4] >= 32)
    {
        return TRUE;
    }
    dstOffs = task->data[3] >> 3;
    if (dstOffs >= task->data[4])
    {
        dstOffs = (task->data[1] >> 3) & 0x1f;
        dest = (u16 *)(VRAM + 0x140 + (u16)task->data[12]);
        for (i=0; i<10; i++)
        {
            dest[dstOffs + i * 32] = 0xf000;
            dest[((dstOffs + 1) & 0x1f) + i * 32] = 0xf000;
        }
        task->data[4] += 2;
    }
    return FALSE;
}

u8 sub_80B8C60(u32 a0, u32 a1, u32 a2)
{
    u16 v0;
    u8 monSprite;
    struct Sprite *sprite;
    v0 = (a0 & 0x80000000) >> 16;
    a0 &= 0x7fffffff;
    monSprite = CreateMonSprite_FieldMove(a0, a1, a2, 0x140, 0x50, 0);
    sprite = &gSprites[monSprite];
    sprite->callback = SpriteCallbackDummy;
    sprite->oam.priority = 0;
    sprite->data[0] = a0;
    sprite->data[6] = v0;
    return monSprite;
}

void sub_80B8D04(struct Sprite *);

void sub_80B8CC0(struct Sprite *sprite)
{
    if ((sprite->pos1.x -= 20) <= 0x78)
    {
        sprite->pos1.x = 0x78;
        sprite->data[1] = 30;
        sprite->callback = sub_80B8D04;
        if (sprite->data[6])
        {
            PlayCry2(sprite->data[0], 0, 0x7d, 0xa);
        } else
        {
            PlayCry1(sprite->data[0], 0);
        }
    }
}

void sub_80B8D20(struct Sprite *);

void sub_80B8D04(struct Sprite *sprite)
{
    if ((--sprite->data[1]) == 0)
    {
        sprite->callback = sub_80B8D20;
    }
}

void sub_80B8D20(struct Sprite *sprite)
{
    if (sprite->pos1.x < -0x40)
    {
        sprite->data[7] = 1;
    } else
    {
        sprite->pos1.x -= 20;
    }
}

void sub_80B8D84(u8);

u8 FldEff_UseSurf(void)
{
    u8 taskId;
    taskId = CreateTask(sub_80B8D84, 0xff);
    gTasks[taskId].data[15] = gFieldEffectArguments[0];
    Overworld_ClearSavedMusic();
    Overworld_ChangeMusicTo(MUS_NAMINORI);
    return FALSE;
}

void (*const gUnknown_0855C4E0[])(struct Task *) = {
    sub_80B8DB4,
    sub_80B8E14,
    sub_80B8E60,
    sub_80B8EA8,
    sub_80B8F24,
};

void sub_80B8D84(u8 taskId)
{
    gUnknown_0855C4E0[gTasks[taskId].data[0]](&gTasks[taskId]);
}

void sub_80B8DB4(struct Task *task)
{
    ScriptContext2_Enable();
    FreezeEventObjects();
    gPlayerAvatar.preventStep = TRUE;
    SetPlayerAvatarStateMask(8);
    PlayerGetDestCoords(&task->data[1], &task->data[2]);
    MoveCoords(gEventObjects[gPlayerAvatar.eventObjectId].movementDirection, &task->data[1], &task->data[2]);
    task->data[0]++;
}

void sub_80B8E14(struct Task *task)
{
    struct EventObject *eventObject;
    eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
    if (!EventObjectIsMovementOverridden(eventObject) || EventObjectClearHeldMovementIfFinished(eventObject))
    {
        sub_808C114();
        EventObjectSetHeldMovement(eventObject, 0x39);
        task->data[0]++;
    }
}

void sub_80B8E60(struct Task *task)
{
    struct EventObject *eventObject;
    eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
    if (EventObjectCheckHeldMovementStatus(eventObject))
    {
        gFieldEffectArguments[0] = task->data[15] | 0x80000000;
        FieldEffectStart(FLDEFF_FIELD_MOVE_SHOW_MON_INIT);
        task->data[0]++;
    }
}

void sub_80B8EA8(struct Task *task)
{
    struct EventObject *eventObject;
    if (!FieldEffectActiveListContains(FLDEFF_FIELD_MOVE_SHOW_MON))
    {
        eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
        EventObjectSetGraphicsId(eventObject, GetPlayerAvatarGraphicsIdByStateId(3));
        EventObjectClearHeldMovementIfFinished(eventObject);
        EventObjectSetHeldMovement(eventObject, GetJumpSpecialMovementAction(eventObject->movementDirection));
        gFieldEffectArguments[0] = task->data[1];
        gFieldEffectArguments[1] = task->data[2];
        gFieldEffectArguments[2] = gPlayerAvatar.eventObjectId;
        eventObject->fieldEffectSpriteId = FieldEffectStart(FLDEFF_SURF_BLOB);
        task->data[0]++;
    }
}

void sub_80B8F24(struct Task *task)
{
    struct EventObject *eventObject;
    eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
    if (EventObjectClearHeldMovementIfFinished(eventObject))
    {
        gPlayerAvatar.preventStep = FALSE;
        gPlayerAvatar.flags &= 0xdf;
        EventObjectSetHeldMovement(eventObject, GetFaceDirectionMovementAction(eventObject->movementDirection));
        sub_81555AC(eventObject->fieldEffectSpriteId, 1);
        UnfreezeEventObjects();
        ScriptContext2_Disable();
        FieldEffectActiveListRemove(FLDEFF_USE_SURF);
        DestroyTask(FindTaskIdByFunc(sub_80B8D84));
    }
}

#ifdef NONMATCHING
u8 sub_80B8F98(void)
{
    u8 spriteId, i, j, k, l;
    struct Sprite *sprite;
    spriteId = CreateSprite(gFieldEffectObjectTemplatePointers[36], 0x78, -0x18, 1);
    sprite = &gSprites[spriteId];
    sprite->oam.priority = 1;
    sprite->oam.paletteNum = 4;
    sprite->data[0] = 0;
    sprite->data[1] = 0;
    sprite->data[2] = 0;
    sprite->data[3] = -1;
    sprite->data[4] = sprite->pos1.y;
    sprite->data[5] = 0;
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT2_BG1 | BLDCNT_TGT2_BG2 | BLDCNT_TGT2_BG3 | BLDCNT_TGT2_OBJ | BLDCNT_TGT2_BD);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(14, 14));
    SetGpuReg(REG_OFFSET_WININ, 0x3F3F);
    LoadPalette(gUnknown_0855B610, 0xC0, sizeof(gUnknown_0855B610));
    SetGpuReg(REG_OFFSET_BG0VOFS, 120);
    for (i = 3; i < 15; i++)
    {
        for (j = 12; j < 18; j++)
        {
            ((u16*)(VRAM + 0xF800))[i * 32 + j] = 0xBFF4 + i * 6 + j + 1;
        }
    }
    for (k = 0; k < 90; k++)
    {
        for (l = 0; l < 8; l++)
        {
            *(u16*)(VRAM + 0x8000 + (k + 1) * 32 + l * 4) = (gUnknown_0855B630[k * 32 + l * 4 + 1] << 8) + gUnknown_0855B630[k * 32 + l * 4];
            *(u16*)(VRAM + 0x8000 + (k + 1) * 32 + l * 4 + 2) = (gUnknown_0855B630[k * 32 + l * 4 + 3] << 8) + gUnknown_0855B630[k * 32 + l * 4 + 2];
        }
    }
    return spriteId;
}
#else
NAKED
u8 sub_80B8F98(void)
{
    asm_unified("push {r4-r7,lr}\n\
	mov r7, r8\n\
	push {r7}\n\
	ldr r0, =gFieldEffectObjectTemplatePointers\n\
	adds r0, 0x90\n\
	ldr r0, [r0]\n\
	movs r2, 0x18\n\
	negs r2, r2\n\
	movs r1, 0x78\n\
	movs r3, 0x1\n\
	bl CreateSprite\n\
	lsls r0, 24\n\
	lsrs r0, 24\n\
	mov r8, r0\n\
	lsls r1, r0, 4\n\
	add r1, r8\n\
	lsls r1, 2\n\
	ldr r0, =gSprites\n\
	adds r1, r0\n\
	ldrb r2, [r1, 0x5]\n\
	movs r0, 0xD\n\
	negs r0, r0\n\
	ands r0, r2\n\
	movs r2, 0x4\n\
	orrs r0, r2\n\
	movs r2, 0xF\n\
	ands r0, r2\n\
	movs r2, 0x40\n\
	orrs r0, r2\n\
	strb r0, [r1, 0x5]\n\
	movs r2, 0\n\
	strh r2, [r1, 0x2E]\n\
	strh r2, [r1, 0x30]\n\
	strh r2, [r1, 0x32]\n\
	ldr r0, =0x0000ffff\n\
	strh r0, [r1, 0x34]\n\
	ldrh r0, [r1, 0x22]\n\
	strh r0, [r1, 0x36]\n\
	strh r2, [r1, 0x38]\n\
	ldr r1, =0x00003e41\n\
	movs r0, 0x50\n\
	bl SetGpuReg\n\
	ldr r1, =0x00000e0e\n\
	movs r0, 0x52\n\
	bl SetGpuReg\n\
	ldr r1, =0x00003f3f\n\
	movs r0, 0x48\n\
	bl SetGpuReg\n\
	ldr r0, =gUnknown_0855B610\n\
	movs r1, 0xC0\n\
	movs r2, 0x20\n\
	bl LoadPalette\n\
	movs r0, 0x12\n\
	movs r1, 0x78\n\
	bl SetGpuReg\n\
	movs r4, 0x3\n\
	ldr r7, =0x0600f800\n\
	ldr r0, =0x0000bff4\n\
	adds r6, r0, 0\n\
_080B901A:\n\
	movs r2, 0xC\n\
	lsls r0, r4, 1\n\
	lsls r5, r4, 5\n\
	adds r0, r4\n\
	lsls r3, r0, 1\n\
_080B9024:\n\
	adds r0, r5, r2\n\
	lsls r0, 1\n\
	adds r0, r7\n\
	adds r1, r2, r6\n\
	adds r1, r3, r1\n\
	adds r1, 0x1\n\
	strh r1, [r0]\n\
	adds r0, r2, 0x1\n\
	lsls r0, 24\n\
	lsrs r2, r0, 24\n\
	cmp r2, 0x11\n\
	bls _080B9024\n\
	adds r0, r4, 0x1\n\
	lsls r0, 24\n\
	lsrs r4, r0, 24\n\
	cmp r4, 0xE\n\
	bls _080B901A\n\
	movs r0, 0\n\
	ldr r5, =gUnknown_0855B630\n\
_080B904A:\n\
	movs r4, 0\n\
	adds r7, r0, 0x1\n\
	lsls r6, r0, 5\n\
_080B9050:\n\
	lsls r1, r4, 2\n\
	adds r1, r6, r1\n\
	ldr r0, =0x06008020\n\
	adds r3, r1, r0\n\
	adds r0, r1, 0x1\n\
	adds r0, r5\n\
	ldrb r2, [r0]\n\
	lsls r2, 8\n\
	adds r0, r1, r5\n\
	ldrb r0, [r0]\n\
	adds r0, r2\n\
	strh r0, [r3]\n\
	ldr r0, =0x06008022\n\
	adds r3, r1, r0\n\
	adds r0, r1, 0x3\n\
	adds r0, r5\n\
	ldrb r2, [r0]\n\
	lsls r2, 8\n\
	adds r1, 0x2\n\
	adds r1, r5\n\
	ldrb r0, [r1]\n\
	adds r0, r2\n\
	strh r0, [r3]\n\
	adds r0, r4, 0x1\n\
	lsls r0, 24\n\
	lsrs r4, r0, 24\n\
	cmp r4, 0x7\n\
	bls _080B9050\n\
	lsls r0, r7, 24\n\
	lsrs r0, 24\n\
	cmp r0, 0x59\n\
	bls _080B904A\n\
	mov r0, r8\n\
	pop {r3}\n\
	mov r8, r3\n\
	pop {r4-r7}\n\
	pop {r1}\n\
	bx r1\n\
	.pool");
}
#endif // NONMATCHING

void sub_80B9128(struct Sprite *);

u8 FldEff_NPCFlyOut(void)
{
    u8 spriteId;
    struct Sprite *sprite;
    spriteId = CreateSprite(gFieldEffectObjectTemplatePointers[26], 0x78, 0, 1);
    sprite = &gSprites[spriteId];
    sprite->oam.paletteNum = 0;
    sprite->oam.priority = 1;
    sprite->callback = sub_80B9128;
    sprite->data[1] = gFieldEffectArguments[0];
    PlaySE(SE_W019);
    return spriteId;
}

void sub_80B9128(struct Sprite *sprite)
{
    struct Sprite *npcSprite;
    sprite->pos2.x = Cos(sprite->data[2], 0x8c);
    sprite->pos2.y = Sin(sprite->data[2], 0x48);
    sprite->data[2] = (sprite->data[2] + 4) & 0xff;
    if (sprite->data[0])
    {
        npcSprite = &gSprites[sprite->data[1]];
        npcSprite->coordOffsetEnabled = 0;
        npcSprite->pos1.x = sprite->pos1.x + sprite->pos2.x;
        npcSprite->pos1.y = sprite->pos1.y + sprite->pos2.y - 8;
        npcSprite->pos2.x = 0;
        npcSprite->pos2.y = 0;
    }
    if (sprite->data[2] >= 0x80)
    {
        FieldEffectStop(sprite, FLDEFF_NPCFLY_OUT);
    }
}

void sub_80B91D4(u8);
extern void sub_81555D8(u8, u8);
u8 sub_80B94C4(void);
bool8 sub_80B9508(u8);
void sub_80B9524(u8);
void sub_80B9560(u8, u8);
void sub_80B957C(struct Sprite *);
void sub_80B963C(struct Sprite *);

u8 FldEff_UseFly(void)
{
    u8 taskId;
    taskId = CreateTask(sub_80B91D4, 0xfe);
    gTasks[taskId].data[1] = gFieldEffectArguments[0];
    return 0;
}

void (*const gUnknown_0855C4F4[])(struct Task *) = {
    sub_80B9204,
    sub_80B925C,
    sub_80B92A0,
    sub_80B92F8,
    sub_80B933C,
    sub_80B9390,
    sub_80B9418,
    sub_80B9474,
    sub_80B9494,
};

void sub_80B91D4(u8 taskId)
{
    gUnknown_0855C4F4[gTasks[taskId].data[0]](&gTasks[taskId]);
}

void sub_80B9204(struct Task *task)
{
    struct EventObject *eventObject;
    eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
    if (!EventObjectIsMovementOverridden(eventObject) || EventObjectClearHeldMovementIfFinished(eventObject))
    {
        task->data[15] = gPlayerAvatar.flags;
        gPlayerAvatar.preventStep = TRUE;
        SetPlayerAvatarStateMask(1);
        sub_808C114();
        EventObjectSetHeldMovement(eventObject, 0x39);
        task->data[0]++;
    }
}

void sub_80B925C(struct Task *task)
{
    struct EventObject *eventObject;
    eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
    if (EventObjectClearHeldMovementIfFinished(eventObject))
    {
        task->data[0]++;
        gFieldEffectArguments[0] = task->data[1];
        FieldEffectStart(FLDEFF_FIELD_MOVE_SHOW_MON_INIT);
    }
}

void sub_80B92A0(struct Task *task)
{
    struct EventObject *eventObject;
    if (!FieldEffectActiveListContains(FLDEFF_FIELD_MOVE_SHOW_MON))
    {
        eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
        if (task->data[15] & 0x08)
        {
            sub_81555AC(eventObject->fieldEffectSpriteId, 2);
            sub_81555D8(eventObject->fieldEffectSpriteId, 0);
        }
        task->data[1] = sub_80B94C4();
        task->data[0]++;
    }
}

void sub_80B92F8(struct Task *task)
{
    if (sub_80B9508(task->data[1]))
    {
        task->data[0]++;
        task->data[2] = 16;
        SetPlayerAvatarTransitionFlags(PLAYER_AVATAR_FLAG_ON_FOOT);
        EventObjectSetHeldMovement(&gEventObjects[gPlayerAvatar.eventObjectId], 0x02);
    }
}

void sub_80B933C(struct Task *task)
{
    struct EventObject *eventObject;
    eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
    if ((task->data[2] == 0 || (--task->data[2]) == 0) && EventObjectClearHeldMovementIfFinished(eventObject))
    {
        task->data[0]++;
        PlaySE(SE_W019);
        sub_80B9524(task->data[1]);
    }
}

void sub_80B9390(struct Task *task)
{
    struct EventObject *eventObject;
    if ((++task->data[2]) >= 8)
    {
        eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
        EventObjectSetGraphicsId(eventObject, GetPlayerAvatarGraphicsIdByStateId(0x03));
        StartSpriteAnim(&gSprites[eventObject->spriteId], 0x16);
        eventObject->inanimate = 1;
        EventObjectSetHeldMovement(eventObject, 0x48);
        if (task->data[15] & 0x08)
        {
            DestroySprite(&gSprites[eventObject->fieldEffectSpriteId]);
        }
        task->data[0]++;
        task->data[2] = 0;
    }
}

void sub_80B9418(struct Task *task)
{
    struct EventObject *eventObject;
    if ((++task->data[2]) >= 10)
    {
        eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
        EventObjectClearHeldMovementIfActive(eventObject);
        eventObject->inanimate = 0;
        eventObject->hasShadow = 0;
        sub_80B9560(task->data[1], eventObject->spriteId);
        CameraObjectReset2();
        task->data[0]++;
    }
}

void sub_80B9474(struct Task *task)
{
    if (sub_80B9508(task->data[1]))
    {
        sub_80AF0B4();
        task->data[0]++;
    }
}

void sub_80B9494(struct Task *task)
{
    if (!gPaletteFade.active)
    {
        FieldEffectActiveListRemove(FLDEFF_USE_FLY);
        DestroyTask(FindTaskIdByFunc(sub_80B91D4));
    }
}

u8 sub_80B94C4(void)
{
    u8 spriteId;
    struct Sprite *sprite;
    spriteId = CreateSprite(gFieldEffectObjectTemplatePointers[26], 0xff, 0xb4, 0x1);
    sprite = &gSprites[spriteId];
    sprite->oam.paletteNum = 0;
    sprite->oam.priority = 1;
    sprite->callback = sub_80B957C;
    return spriteId;
}

u8 sub_80B9508(u8 spriteId)
{
    return gSprites[spriteId].data[7];
}

void sub_80B9524(u8 spriteId)
{
    struct Sprite *sprite;
    sprite = &gSprites[spriteId];
    sprite->callback = sub_80B963C;
    sprite->pos1.x = 0x78;
    sprite->pos1.y = 0x00;
    sprite->pos2.x = 0;
    sprite->pos2.y = 0;
    memset(&sprite->data[0], 0, 8 * sizeof(u16) /* zero all data cells */);
    sprite->data[6] = 0x40;
}

void sub_80B9560(u8 a0, u8 a1)
{
    gSprites[a0].data[6] = a1;
}

const union AffineAnimCmd SpriteAffineAnim_855C518[] = {
    AFFINEANIMCMD_FRAME(8, 8, -30, 0),
    AFFINEANIMCMD_FRAME(28, 28, 0, 30),
    AFFINEANIMCMD_END
};

const union AffineAnimCmd SpriteAffineAnim_855C530[] = {
    AFFINEANIMCMD_FRAME(256, 256, 64, 0),
    AFFINEANIMCMD_FRAME(-10, -10, 0, 22),
    AFFINEANIMCMD_END
};

const union AffineAnimCmd *const gSpriteAffineAnimTable_0855C548[] = {
    SpriteAffineAnim_855C518,
    SpriteAffineAnim_855C530
};

void sub_80B957C(struct Sprite *sprite)
{
    if (sprite->data[7] == 0)
    {
        if (sprite->data[0] == 0)
        {
            sprite->oam.affineMode = 3;
            sprite->affineAnims = gSpriteAffineAnimTable_0855C548;
            InitSpriteAffineAnim(sprite);
            StartSpriteAffineAnim(sprite, 0);
            sprite->pos1.x = 0x76;
            sprite->pos1.y = -0x30;
            sprite->data[0]++;
            sprite->data[1] = 0x40;
            sprite->data[2] = 0x100;
        }
        sprite->data[1] += (sprite->data[2] >> 8);
        sprite->pos2.x = Cos(sprite->data[1], 0x78);
        sprite->pos2.y = Sin(sprite->data[1], 0x78);
        if (sprite->data[2] < 0x800)
        {
            sprite->data[2] += 0x60;
        }
        if (sprite->data[1] > 0x81)
        {
            sprite->data[7]++;
            sprite->oam.affineMode = 0;
            FreeOamMatrix(sprite->oam.matrixNum);
            CalcCenterToCornerVec(sprite, sprite->oam.shape, sprite->oam.size, 0);
        }
    }
}

void sub_80B963C(struct Sprite *sprite)
{
    struct Sprite *sprite1;
    sprite->pos2.x = Cos(sprite->data[2], 0x8c);
    sprite->pos2.y = Sin(sprite->data[2], 0x48);
    sprite->data[2] = (sprite->data[2] + 4) & 0xff;
    if (sprite->data[6] != 0x40)
    {
        sprite1 = &gSprites[sprite->data[6]];
        sprite1->coordOffsetEnabled = 0;
        sprite1->pos1.x = sprite->pos1.x + sprite->pos2.x;
        sprite1->pos1.y = sprite->pos1.y + sprite->pos2.y - 8;
        sprite1->pos2.x = 0;
        sprite1->pos2.y = 0;
    }
    if (sprite->data[2] >= 0x80)
    {
        sprite->data[7] = 1;
    }
}

void sub_80B96B0(struct Sprite *sprite)
{
    if (sprite->data[7] == 0)
    {
        if (sprite->data[0] == 0)
        {
            sprite->oam.affineMode = 3;
            sprite->affineAnims = gSpriteAffineAnimTable_0855C548;
            InitSpriteAffineAnim(sprite);
            StartSpriteAffineAnim(sprite, 1);
            sprite->pos1.x = 0x5e;
            sprite->pos1.y = -0x20;
            sprite->data[0]++;
            sprite->data[1] = 0xf0;
            sprite->data[2] = 0x800;
            sprite->data[4] = 0x80;
        }
        sprite->data[1] += sprite->data[2] >> 8;
        sprite->data[3] += sprite->data[2] >> 8;
        sprite->data[1] &= 0xff;
        sprite->pos2.x = Cos(sprite->data[1], 0x20);
        sprite->pos2.y = Sin(sprite->data[1], 0x78);
        if (sprite->data[2] > 0x100)
        {
            sprite->data[2] -= sprite->data[4];
        }
        if (sprite->data[4] < 0x100)
        {
            sprite->data[4] += 24;
        }
        if (sprite->data[2] < 0x100)
        {
            sprite->data[2] = 0x100;
        }
        if (sprite->data[3] >= 60)
        {
            sprite->data[7]++;
            sprite->oam.affineMode = 0;
            FreeOamMatrix(sprite->oam.matrixNum);
            sprite->invisible = 1;
        }
    }
}

void sub_80B9794(u8 spriteId)
{
    sub_80B9524(spriteId);
    gSprites[spriteId].callback = sub_80B96B0;
}

void sub_80B97D4(u8);

u8 FldEff_FlyIn(void)
{
    CreateTask(sub_80B97D4, 0xfe);
    return 0;
}

void (*const gUnknown_0855C550[])(struct Task *) = {
    sub_80B9804,
    sub_80B98B8,
    sub_80B9924,
    sub_80B9978,
    sub_80B99F0,
    sub_80B9A28,
    sub_80B9A60,
};

void sub_80B97D4(u8 taskId)
{
    gUnknown_0855C550[gTasks[taskId].data[0]](&gTasks[taskId]);
}

void sub_80B9804(struct Task *task)
{
    struct EventObject *eventObject;
    eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
    if (!EventObjectIsMovementOverridden(eventObject) || EventObjectClearHeldMovementIfFinished(eventObject))
    {
        task->data[0]++;
        task->data[2] = 17;
        task->data[15] = gPlayerAvatar.flags;
        gPlayerAvatar.preventStep = TRUE;
        SetPlayerAvatarStateMask(0x01);
        if (task->data[15] & 0x08)
        {
            sub_81555AC(eventObject->fieldEffectSpriteId, 0);
        }
        EventObjectSetGraphicsId(eventObject, GetPlayerAvatarGraphicsIdByStateId(0x3));
        CameraObjectReset2();
        EventObjectTurn(eventObject, DIR_WEST);
        StartSpriteAnim(&gSprites[eventObject->spriteId], 0x16);
        eventObject->invisible = 0;
        task->data[1] = sub_80B94C4();
        sub_80B9524(task->data[1]);
        sub_80B9560(task->data[1], eventObject->spriteId);
    }
}

void sub_80B98B8(struct Task *task)
{
    struct EventObject *eventObject;
    struct Sprite *sprite;
    if (task->data[2] == 0 || (--task->data[2]) == 0)
    {
        eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
        sprite = &gSprites[eventObject->spriteId];
        sub_80B9560(task->data[1], 0x40);
        sprite->pos1.x += sprite->pos2.x;
        sprite->pos1.y += sprite->pos2.y;
        sprite->pos2.x = 0;
        sprite->pos2.y = 0;
        task->data[0]++;
        task->data[2] = 0;
    }
}

void sub_80B9924(struct Task *task)
{
    s16 unknown_0855C56C[18] = {
        -2,
        -4,
        -5,
        -6,
        -7,
        -8,
        -8,
        -8,
        -7,
        -7,
        -6,
        -5,
        -3,
        -2,
        0,
        2,
        4,
        8
    };
    struct Sprite *sprite = &gSprites[gPlayerAvatar.spriteId];
    sprite->pos2.y = unknown_0855C56C[task->data[2]];
    if ((++task->data[2]) >= 18)
    {
        task->data[0]++;
    }
}

void sub_80B9978(struct Task *task)
{
    struct EventObject *eventObject;
    struct Sprite *sprite;
    if (sub_80B9508(task->data[1]))
    {
        eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
        sprite = &gSprites[eventObject->spriteId];
        eventObject->inanimate = 0;
        sub_808EB08(eventObject, eventObject->currentCoords.x, eventObject->currentCoords.y);
        sprite->pos2.x = 0;
        sprite->pos2.y = 0;
        sprite->coordOffsetEnabled = 1;
        sub_808C114();
        EventObjectSetHeldMovement(eventObject, 0x39);
        task->data[0]++;
    }
}

void sub_80B99F0(struct Task *task)
{
    if (EventObjectClearHeldMovementIfFinished(&gEventObjects[gPlayerAvatar.eventObjectId]))
    {
        task->data[0]++;
        sub_80B9794(task->data[1]);
    }
}

void sub_80B9A28(struct Task *task)
{
    if (sub_80B9508(task->data[1]))
    {
        DestroySprite(&gSprites[task->data[1]]);
        task->data[0]++;
        task->data[1] = 0x10;
    }
}

void sub_80B9A60(struct Task *task)
{
    u8 state;
    struct EventObject *eventObject;
    if ((--task->data[1]) == 0)
    {
        eventObject = &gEventObjects[gPlayerAvatar.eventObjectId];
        state = 0;
        if (task->data[15] & 0x08)
        {
            state = 3;
            sub_81555AC(eventObject->fieldEffectSpriteId, 1);
        }
        EventObjectSetGraphicsId(eventObject, GetPlayerAvatarGraphicsIdByStateId(state));
        EventObjectTurn(eventObject, DIR_SOUTH);
        gPlayerAvatar.flags = task->data[15];
        gPlayerAvatar.preventStep = FALSE;
        FieldEffectActiveListRemove(FLDEFF_FLY_IN);
        DestroyTask(FindTaskIdByFunc(sub_80B97D4));
    }
}

void sub_80B9BE8(u8 taskId);

bool8 sub_80B9ADC(void)
{
    u8 taskId;
    u8 eventObjectIdBuffer;
    if (!TryGetEventObjectIdByLocalIdAndMap(gFieldEffectArguments[0], gFieldEffectArguments[1], gFieldEffectArguments[2], &eventObjectIdBuffer))
    {
        taskId = CreateTask(sub_80B9BE8, 0x50);
        gTasks[taskId].data[2] = eventObjectIdBuffer;
        gTasks[taskId].data[6] = gFieldEffectArguments[0];
        gTasks[taskId].data[7] = gFieldEffectArguments[1];
        gTasks[taskId].data[8] = gFieldEffectArguments[2];
    }
    else
    {
        FieldEffectActiveListRemove(0x41);
    }
    return FALSE;
}

void sub_80B9B3C(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (data[7] != 0)
    {
        if (++data[6] > 20)
        {
            data[6] = 0;
            if (data[5] != 0)
                data[5]--;
        }
    }
    else
    {
        data[5] = 4;
    }

    if (++data[0] > 1)
    {
        data[0] = 0;
        if (++data[1] & 1)
        {
            SetCameraPanning(0, -data[5]);
        }
        else
        {
            SetCameraPanning(0, data[5]);
        }
    }
    UpdateCameraPanning();
    if (data[5] == 0)
        DestroyTask(taskId);
}

void sub_80B9BD0(u8 taskId)
{
    gTasks[taskId].data[7] = 1;
}

void (*const gUnknown_0855C590[])(s16*, u8) = {
    sub_80B9C28,
    sub_80B9C54,
    sub_80B9CDC,
};

void sub_80B9BE8(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    InstallCameraPanAheadCallback();
    SetCameraPanningCallback(0);
    gUnknown_0855C590[data[1]](data, taskId);
}

void sub_80B9C28(s16* data, u8 taskId)
{
    u8 newTaskId = CreateTask(sub_80B9B3C, 0x5A);
    PlaySE(SE_T_KAMI2);
    data[5] = newTaskId;
    data[1]++;
}

void sub_80B9D24(struct Sprite*);

void sub_80B9C54(s16* data, u8 taskId)
{
    if (++data[3] > 0x78)
    {
        struct Sprite *sprite = &gSprites[gEventObjects[data[2]].spriteId];
        gEventObjects[data[2]].invisible = TRUE;
        BlendPalettes(0x0000FFFF, 0x10, RGB_WHITE);
        BeginNormalPaletteFade(0x0000FFFF, 0, 0x10, 0, RGB_WHITE);
        sub_80B9D24(sprite);
        PlaySE(SE_T_KAMI);
        sub_80B9BD0(data[5]);
        data[3] = 0;
        data[1]++;
    }
}

void sub_80B9CDC(s16* a0, u8 taskId)
{
    if (!gPaletteFade.active && !FuncIsActiveTask(sub_80B9B3C))
    {
        InstallCameraPanAheadCallback();
        RemoveEventObjectByLocalIdAndMap(a0[6], a0[7], a0[8]);
        FieldEffectActiveListRemove(0x41);
        DestroyTask(taskId);
    }
}

void sub_80B9DB8(struct Sprite* sprite);

const struct SpriteFrameImage gSpriteImageTable_855C59C[] = {
    obj_frame_tiles(gUnknown_0855C170),
    obj_frame_tiles(gUnknown_0855C190),
    obj_frame_tiles(gUnknown_0855C1B0),
    obj_frame_tiles(gUnknown_0855C1D0),
};

const union AnimCmd gSpriteAnim_855C5BC[] = {
    ANIMCMD_FRAME(.imageValue = 0),
    ANIMCMD_END
};

const union AnimCmd gSpriteAnim_855C5C4[] = {
    ANIMCMD_FRAME(.imageValue = 1),
    ANIMCMD_END
};

const union AnimCmd gSpriteAnim_855C5CC[] = {
    ANIMCMD_FRAME(.imageValue = 2),
    ANIMCMD_END
};

const union AnimCmd gSpriteAnim_855C5D4[] = {
    ANIMCMD_FRAME(.imageValue = 3),
    ANIMCMD_END
};

const union AnimCmd *const gSpriteAnimTable_855C5DC[] = {
    gSpriteAnim_855C5BC,
    gSpriteAnim_855C5C4,
    gSpriteAnim_855C5CC,
    gSpriteAnim_855C5D4,
};

const struct SpriteTemplate gUnknown_0855C5EC = {
    .tileTag = 0xffff,
    .paletteTag = 4378,
    .oam = &gOamData_855C218,
    .anims = gSpriteAnimTable_855C5DC,
    .images = gSpriteImageTable_855C59C,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = sub_80B9DB8
};

void sub_80B9D24(struct Sprite* sprite)
{
    int i;
    int xPos = (s16)gUnknown_03005DEC + sprite->pos1.x + sprite->pos2.x;
    int yPos = (s16)gUnknown_03005DE8 + sprite->pos1.y + sprite->pos2.y - 4;

    for (i = 0; i < 4; i++)
    {
        u8 spriteId = CreateSprite(&gUnknown_0855C5EC, xPos, yPos, 0);
        if (spriteId != 0x40)
        {
            StartSpriteAnim(&gSprites[spriteId], i);
            gSprites[spriteId].data[0] = i;
            gSprites[spriteId].oam.paletteNum = sprite->oam.paletteNum;
        }
    }
}

void sub_80B9DB8(struct Sprite* sprite)
{
    switch (sprite->data[0])
    {
        case 0:
            sprite->pos1.x -= 16;
            sprite->pos1.y -= 12;
            break;
        case 1:
            sprite->pos1.x += 16;
            sprite->pos1.y -= 12;
            break;
        case 2:
            sprite->pos1.x -= 16;
            sprite->pos1.y += 12;
            break;
        case 3:
            sprite->pos1.x += 16;
            sprite->pos1.y += 12;
            break;
    }
    if ((u16)(sprite->pos1.x + 4) > 0xF8 || sprite->pos1.y < -4 || sprite->pos1.y > 0xA4)
        DestroySprite(sprite);
}

void sub_80B9EDC(u8 taskId);

bool8 sub_80B9E28(struct Sprite* sprite)
{
    u8 eventObjectIdBuffer;
    if (!TryGetEventObjectIdByLocalIdAndMap(gFieldEffectArguments[0], gFieldEffectArguments[1], gFieldEffectArguments[2], &eventObjectIdBuffer))
    {
        struct EventObject *object;
        int xPos, yPos;
        u8 taskId;
        object = &gEventObjects[eventObjectIdBuffer];
        xPos = object->currentCoords.x - 7;
        yPos = object->currentCoords.y - 7;
        xPos = (gFieldEffectArguments[3] - xPos) * 16;
        yPos = (gFieldEffectArguments[4] - yPos) * 16;
        ShiftEventObjectCoords(object, gFieldEffectArguments[3] + 7, gFieldEffectArguments[4] + 7);
        taskId = CreateTask(sub_80B9EDC, 0x50);
        gTasks[taskId].data[1] = object->spriteId;
        gTasks[taskId].data[2] = gSprites[object->spriteId].pos1.x + xPos;
        gTasks[taskId].data[3] = gSprites[object->spriteId].pos1.y + yPos;
        gTasks[taskId].data[8] = gFieldEffectArguments[5];
        gTasks[taskId].data[9] = eventObjectIdBuffer;
    }
    return FALSE;
}

void sub_80B9EDC(u8 taskId)
{
    // BUG: Possible divide by zero
    s16 *data = gTasks[taskId].data;
    struct Sprite *sprite = &gSprites[data[1]];
    switch (data[0])
    {
        case 0:
            data[4] = sprite->pos1.x << 4;
            data[5] = sprite->pos1.y << 4;
            data[6] = (data[2] * 16 - data[4]) / data[8];
            data[7] = (data[3] * 16 - data[5]) / data[8];
            data[0]++;
        case 1:
            if (data[8] != 0)
            {
                data[8]--;
                data[4] += data[6];
                data[5] += data[7];
                sprite->pos1.x = data[4] >> 4;
                sprite->pos1.y = data[5] >> 4;
            }
            else
            {
                struct EventObject *object = &gEventObjects[data[9]];
                sprite->pos1.x = data[2];
                sprite->pos1.y = data[3];
                ShiftStillEventObjectCoords(object);
                object->triggerGroundEffectsOnStop = TRUE;
                FieldEffectActiveListRemove(0x42);
                DestroyTask(taskId);
            }
            break;
    }
}
