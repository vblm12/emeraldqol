#ifndef GUARD_GLOBAL_H
#define GUARD_GLOBAL_H

#include <string.h>
#include "config.h" // we need to define config before gba headers as print stuff needs the functions nulled before defines.
#include "gba/gba.h"

// Prevent cross-jump optimization.
#define BLOCK_CROSS_JUMP asm("");

// to help in decompiling
#define asm_comment(x) asm volatile("@ -- " x " -- ")
#define asm_unified(x) asm(".syntax unified\n" x "\n.syntax divided")
#define NAKED __attribute__((naked))

// IDE support
#if defined (__APPLE__) || defined (__CYGWIN__) || defined (_MSC_VER)
#define _(x) x
#define __(x) x
#define INCBIN_U8 {0}
#define INCBIN_U16 {0}
#define INCBIN_U32 {0}
#define INCBIN_S8 {0}
#define INCBIN_S16 {0}
#define INCBIN_S32 {0}
#endif // IDE support

#define ARRAY_COUNT(array) (size_t)(sizeof(array) / sizeof((array)[0]))

// useful math macros

// Converts a number to Q8.8 fixed-point format
#define Q_8_8(n) ((s16)((n) * 256))

// Converts a number to Q4.12 fixed-point format
#define Q_4_12(n)  ((s16)((n) * 4096))

// Converts a number to Q24.8 fixed-point format
#define Q_24_8(n)  ((s32)((n) * 256))

// Converts a Q8.8 fixed-point format number to a regular integer
#define Q_8_8_TO_INT(n) ((int)((n) / 256))

// Converts a Q4.12 fixed-point format number to a regular integer
#define Q_4_12_TO_INT(n)  ((int)((n) / 4096))

// Converts a Q24.8 fixed-point format number to a regular integer
#define Q_24_8_TO_INT(n) ((int)((n) >> 8))

#define PARTY_SIZE 6

#define POKEMON_SLOTS_NUMBER 412
#define POKEMON_NAME_LENGTH 10
#define OT_NAME_LENGTH 7

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) >= (b) ? (a) : (b))

#define HEAP_SIZE 0x1C000

extern u8 gStringVar1[];
extern u8 gStringVar2[];
extern u8 gStringVar3[];
extern u8 gStringVar4[];

// There are many quirks in the source code which have overarching behavioral differences from
// a number of other files. For example, diploma.c seems to declare rodata before each use while
// other files declare out of order and must be at the beginning. There are also a number of
// macros which differ from one file to the next due to the method of obtaining the result, such
// as these below. Because of this, there is a theory (Two Team Theory) that states that these
// programming projects had more than 1 "programming team" which utilized different macros for
// each of the files that were worked on.
#define T1_READ_8(ptr)  ((ptr)[0])
#define T1_READ_16(ptr) ((ptr)[0] | ((ptr)[1] << 8))
#define T1_READ_32(ptr) ((ptr)[0] | ((ptr)[1] << 8) | ((ptr)[2] << 16) | ((ptr)[3] << 24))
#define T1_READ_PTR(ptr) (u8*) T1_READ_32(ptr)

// T2_READ_8 is a duplicate to remain consistent with each group.
#define T2_READ_8(ptr)  ((ptr)[0])
#define T2_READ_16(ptr) ((ptr)[0] + ((ptr)[1] << 8))
#define T2_READ_32(ptr) ((ptr)[0] + ((ptr)[1] << 8) + ((ptr)[2] << 16) + ((ptr)[3] << 24))
#define T2_READ_PTR(ptr) (void*) T2_READ_32(ptr)

enum
{
    VERSION_SAPPHIRE = 1,
    VERSION_RUBY = 2,
    VERSION_EMERALD = 3,
    VERSION_FIRE_RED = 4,
    VERSION_LEAF_GREEN = 5,
};

enum LanguageId
{
    LANGUAGE_JAPANESE = 1,
    LANGUAGE_ENGLISH = 2,
    LANGUAGE_FRENCH = 3,
    LANGUAGE_ITALIAN = 4,
    LANGUAGE_GERMAN = 5,
    // 6 goes unused but the theory is it was meant to be Korean
    LANGUAGE_SPANISH = 7,
};

#define GAME_VERSION (VERSION_EMERALD)
#define GAME_LANGUAGE (LANGUAGE_ENGLISH)

// capacities of various saveblock objects
#define DAYCARE_MON_COUNT   2
#define POKEBLOCKS_COUNT    40
#define EVENT_OBJECTS_COUNT   16
#define BERRY_TREES_COUNT   128
#define FLAGS_COUNT         300
#define VARS_COUNT          256
#define MAIL_COUNT          16
#define SECRET_BASES_COUNT  20
#define TV_SHOWS_COUNT      25
#define POKE_NEWS_COUNT     16
#define PC_ITEMS_COUNT      50
#define BAG_ITEMS_COUNT     30
#define BAG_KEYITEMS_COUNT  30
#define BAG_POKEBALLS_COUNT 16
#define BAG_TMHM_COUNT      64
#define BAG_BERRIES_COUNT   46

#define PYRAMID_BAG_ITEMS_COUNT 10

// string lengths
#define ITEM_NAME_LENGTH    14
#define POKEMON_NAME_LENGTH 10
#define OT_NAME_LENGTH      7
#define PLAYER_NAME_LENGTH  8
#define MAIL_WORDS_COUNT    9

enum
{
    MALE,
    FEMALE
};

enum
{
    OPTIONS_BUTTON_MODE_NORMAL,
    OPTIONS_BUTTON_MODE_LR,
    OPTIONS_BUTTON_MODE_L_EQUALS_A
};

enum
{
    OPTIONS_TEXT_SPEED_SLOW,
    OPTIONS_TEXT_SPEED_MID,
    OPTIONS_TEXT_SPEED_FAST
};

enum
{
    OPTIONS_SOUND_MONO,
    OPTIONS_SOUND_STEREO
};

enum
{
    OPTIONS_BATTLE_STYLE_SHIFT,
    OPTIONS_BATTLE_STYLE_SET
};

struct Coords16
{
    s16 x;
    s16 y;
};

struct UCoords16
{
    u16 x;
    u16 y;
};

struct Coords32
{
    s32 x;
    s32 y;
};

struct UCoords32
{
    u32 x;
    u32 y;
};

struct Time
{
    /*0x00*/ s16 days;
    /*0x02*/ s8 hours;
    /*0x03*/ s8 minutes;
    /*0x04*/ s8 seconds;
};

#define DEX_FLAGS_NO ((POKEMON_SLOTS_NUMBER / 8) + ((POKEMON_SLOTS_NUMBER % 8) ? 1 : 0))

struct Pokedex
{
    /*0x00*/ u8 order;
    /*0x01*/ u8 unknown1;
    /*0x02*/ u8 nationalMagic; // must equal 0xDA in order to have National mode
    /*0x03*/ u8 unknown2;
    /*0x04*/ u32 unownPersonality; // set when you first see Unown
    /*0x08*/ u32 spindaPersonality; // set when you first see Spinda
    /*0x0C*/ u32 unknown3;
    /*0x10*/ u8 owned[DEX_FLAGS_NO];
    /*0x44*/ u8 seen[DEX_FLAGS_NO];
};

struct PokemonJumpResults // possibly used in the game itself?
{
    u16 jumpsInRow;
    u16 field2;
    u16 excellentsInRow;
    u16 field6;
    u16 field8;
    u16 fieldA;
    u32 bestJumpScore;
};

struct BerryPickingResults // possibly used in the game itself? Size may be wrong as well
{
    u32 bestScore;
    u16 berriesPicked;
    u16 berriesPickedInRow;
    u8 field_8;
    u8 field_9;
    u8 field_A;
    u8 field_B;
    u8 field_C;
    u8 field_D;
    u8 field_E;
    u8 field_F;
};

// two arrays for lvl50 and open level
struct PyramidBag
{
    u16 itemId[2][PYRAMID_BAG_ITEMS_COUNT];
    u8 quantity[2][PYRAMID_BAG_ITEMS_COUNT];
};

struct BerryCrush
{
    u16 berryCrushResults[4];
    u32 berryPowderAmount;
    u32 unk;
};

struct UnknownSaveBlock2Struct
{
    u8 field_0;
    u8 field_1;
    u8 field_2[2];
    u8 field_4[8];
    u8 field_C[16];
    u16 field_1C[6];
    u16 field_28[6];
    u8 field_34[176];
    u8 field_E4;
    u8 field_E5;
    u8 field_E6;
    u8 field_E7;
    u8 field_E8;
    u8 field_E9;
    u8 field_EA;
    u8 field_EB;
}; // sizeof = 0xEC

struct UnkRecordMixingStruct
{
    u8 field_0[0x34];
    u8 playerId[4];
    u8 field_38[10];
};

struct UnknownPokemonStruct
{
    u16 species;
    u16 heldItem;
    u16 moves[4];
    u8 level;
    u8 ppBonuses;
    u8 hpEV;
    u8 attackEV;
    u8 defenseEV;
    u8 speedEV;
    u8 spAttackEV;
    u8 spDefenseEV;
    u32 otId;
    u32 hpIV:5;
    u32 attackIV:5;
    u32 defenseIV:5;
    u32 speedIV:5;
    u32 spAttackIV:5;
    u32 spDefenseIV:5;
    u32 gap:1;
    u32 altAbility:1;
    u32 personality;
    u8 nickname[POKEMON_NAME_LENGTH + 1];
    u8 friendship;
};

struct EmeraldBattleTowerRecord
{
    /*0x00*/ u8 battleTowerLevelType; // 0 = level 50, 1 = level 100
    /*0x01*/ u8 trainerClass;
    /*0x02*/ u16 winStreak;
    /*0x04*/ u8 name[8];
    /*0x0C*/ u8 trainerId[4];
    /*0x10*/ struct {
        u16 easyChat[6];
    } greeting;
    /*0x1C*/ u8 filler_1c[0x18];
    /*0x34*/ struct UnknownPokemonStruct party[4];
    /*0xE4*/ u8 language;
    /*0xE8*/ u32 checksum;
};

struct BattleFrontier
{
    /*0x64C*/ struct EmeraldBattleTowerRecord battleTower;
    /*0x738*/ struct UnknownSaveBlock2Struct field_738[5]; // No idea here, it's probably wrong, no clue.
    /*0xBD4*/ u16 field_BD4;
    /*0xBD6*/ u16 field_BD6;
    /*0xBD8*/ u8 field_BD8[11];
    /*0xBE3*/ u8 field_BE3[8];
    /*0xBEB*/ u8 field_BEB;
    /*0xBEC*/ u8 filler_BEC[16];
    /*0xBFC*/ u16 ecwords_BFC[6];
    /*0xC08*/ u16 ecwords_C08[6];
    /*0xC14*/ u16 ecwords_C14[6];
    /*0xC20*/ u8 filler_C20[0x88];
    /*0xCA8*/ u8 field_CA8;
    /*0xCA9*/ u8 chosenLvl:2; // 0x1, 0x2 -> 0x3
    /*0xCA9*/ u8 field_CA9_a:1;   // 0x4
    /*0xCA9*/ u8 field_CA9_b:1;   // 0x8
    /*0xCA9*/ u8 field_CA9_c:1;   // 0x10
    /*0xCA9*/ u8 field_CA9_d:1;   // 0x20
    /*0xCA9*/ u8 field_CA9_e:1;   // 0x40
    /*0xCA9*/ u8 field_CA9_f:1;   // 0x80
    /*0xCAA*/ u16 field_CAA[4];
    /*0xCB2*/ u16 field_CB2;
    /*0xCB4*/ u16 field_CB4[30];
    /*0xCF0*/ u16 field_CF0[2];
    /*0xCF4*/ u16 field_CF4[2];
    /*0xCF8*/ u16 field_CF8[2];
    /*0xCFC*/ u16 field_CFC[5];
    /*0xD06*/ u8 field_D06;
    /*0xD07*/ u8 field_D07;
    /*0xD08*/ u8 filler_D08;
    /*0xD09*/ u8 filler_D09;
    /*0xD0A*/ u8 filler_D0A;
    /*0xD0B*/ u8 filler_D0B;
    /*0xD0C*/ u8 filler_D0C;
    /*0xD0D*/ u8 filler_D0D;
    /*0xD0E*/ u8 filler_D0E;
    /*0xD0F*/ u8 filler_D0F;
    /*0xD10*/ u8 filler_D10;
    /*0xD11*/ u8 filler_D11;
    /*0xD12*/ u8 filler_D12;
    /*0xD13*/ u8 filler_D13;
    /*0xD14*/ u16 field_D14[2];
    /*0xD18*/ u8 field_D18[0xB8];
    /*0xDD0*/ u16 field_DD0[2];
    /*0xDD4*/ u16 field_DD4[2];
    /*0xDD8*/ u16 field_DD8;
    /*0xDDA*/ u16 field_DDA;
    /*0xDDC*/ u16 field_DDC;
    /*0xDDE*/ u16 field_DDE[2];
    /*0xDE2*/ u16 field_DE2;
    /*0xDE4*/ u16 field_DE4;
    /*0xDE6*/ u16 field_DE6;
    /*0xDE8*/ u16 field_DE8;
    /*0xDEA*/ u16 field_DEA[2];
    /*0xDEE*/ u16 field_DEE;
    /*0xDF0*/ u16 field_DF0;
    /*0xDF2*/ u16 field_DF2;
    /*0xDF4*/ u16 field_DF4;
    /*0xDF6*/ u16 field_DF6;
    /*0xDF8*/ u16 field_DF8;
    /*0xDFA*/ u16 field_DFA;
    /*0xDFC*/ u16 field_DFC;
    /*0xDFE*/ u16 field_DFE;
    /*0xE00*/ u16 field_E00;
    /*0xE02*/ u16 field_E02;
    /*0xE04*/ u16 field_E04;
    /*0xE06*/ u16 field_E06;
    /*0xE08*/ u16 field_E08[9];
    /*0xE1A*/ u16 field_E1A;
    /*0xE1C*/ u16 field_E1C;
    /*0xE1E*/ u16 field_E1E[7];
    /*0xE2C*/ struct PyramidBag pyramidBag;
    /*0xE58*/ u16 field_E58;
    /*0xE6A*/ u16 field_E6A;
    /*0xE6C*/ u16 field_E6C;
    /*0xE6E*/ u16 field_E6E;
    /*0xE70*/ u8 field_E70[72];
    /*0xEB8*/ u16 frontierBattlePoints;
    /*0xEBA*/ u8 field_EBA[39];
    /*0xEE1*/ u8 field_EE1[2][PLAYER_NAME_LENGTH];
    /*0xEF1*/ u8 field_EF1[2][4];
    /*0xEF9*/ u8 field_EF9[51];
};

struct SaveBlock2
{
    /*0x00*/ u8 playerName[PLAYER_NAME_LENGTH];
    /*0x08*/ u8 playerGender; // MALE, FEMALE
    /*0x09*/ u8 specialSaveWarp;
    /*0x0A*/ u8 playerTrainerId[4];
    /*0x0E*/ u16 playTimeHours;
    /*0x10*/ u8 playTimeMinutes;
    /*0x11*/ u8 playTimeSeconds;
    /*0x12*/ u8 playTimeVBlanks;
    /*0x13*/ u8 optionsButtonMode;  // OPTIONS_BUTTON_MODE_[NORMAL/LR/L_EQUALS_A]
    /*0x14*/ u16 optionsTextSpeed:3; // OPTIONS_TEXT_SPEED_[SLOW/MID/FAST]
             u16 optionsWindowFrameType:5; // Specifies one of the 20 decorative borders for text boxes
             u16 optionsSound:1; // OPTIONS_SOUND_[MONO/STEREO]
             u16 optionsBattleStyle:1; // OPTIONS_BATTLE_STYLE_[SHIFT/SET]
             u16 optionsBattleSceneOff:1; // whether battle animations are disabled
             u16 regionMapZoom:1; // whether the map is zoomed in
    /*0x18*/ struct Pokedex pokedex;
    /*0x90*/ u8 filler_90[0x8];
    /*0x98*/ struct Time localTimeOffset;
    /*0xA0*/ struct Time lastBerryTreeUpdate;
    /*0xA8*/ u32 field_A8;
    /*0xAC*/ u32 encryptionKey;

        // TODO: fix and verify labels
    /*0xB0*/ u8 field_B0;
    /*0xB1*/ u8 field_B1;
    /*0xB2*/ u8 field_B2_0:3;
    /*0xB2*/ u8 field_B2_1:2;
    /*0xB3*/ u8 field_B3[0x29];
    /*0xDC*/ struct UnkRecordMixingStruct field_DC[4];
    /*0x1EC*/ struct BerryCrush berryCrush;
    /*0x1FC*/ struct PokemonJumpResults pokeJump;
    /*0x20C*/ struct BerryPickingResults berryPick;
    /*0x21C*/ u8 field_21C[1032];
    /*0x624*/ u16 contestLinkResults[20]; // 4 positions for 5 categories, possibly a struct or a 2d array
    /*0x64C*/ struct BattleFrontier frontier;
}; // sizeof=0xF2C

extern struct SaveBlock2 *gSaveBlock2Ptr;

struct SecretBaseParty
{
    u32 personality[PARTY_SIZE];
    u16 moves[PARTY_SIZE * 4];
    u16 species[PARTY_SIZE];
    u16 heldItems[PARTY_SIZE];
    u8 levels[PARTY_SIZE];
    u8 EVs[PARTY_SIZE];
};

struct SecretBaseRecord
{
    /*0x1A9C*/ u8 secretBaseId;
    /*0x1A9D*/ u8 sbr_field_1_0:4;
    /*0x1A9D*/ u8 gender:1;
    /*0x1A9D*/ u8 sbr_field_1_5:1;
    /*0x1A9D*/ u8 sbr_field_1_6:2;
    /*0x1A9E*/ u8 trainerName[OT_NAME_LENGTH];
    /*0x1AA5*/ u8 trainerId[4]; // byte 0 is used for determining trainer class
    /*0x1AA9*/ u8 language;
    /*0x1AAA*/ u16 sbr_field_e;
    /*0x1AAC*/ u8 sbr_field_10;
    /*0x1AAD*/ u8 sbr_field_11;
    /*0x1AAE*/ u8 decorations[16];
    /*0x1ABE*/ u8 decorationPos[16];
    /*0x1AD0*/ struct SecretBaseParty party;
};

#include "constants/game_stat.h"
#include "global.fieldmap.h"
#include "global.berry.h"
#include "global.tv.h"
#include "pokemon.h"

struct WarpData
{
    s8 mapGroup;
    s8 mapNum;
    s8 warpId;
    s16 x, y;
};

struct ItemSlot
{
    u16 itemId;
    u16 quantity;
};

struct Pokeblock
{
    u8 color;
    u8 spicy;
    u8 dry;
    u8 sweet;
    u8 bitter;
    u8 sour;
    u8 feel;
};

struct Roamer
{
    /*0x00*/ u32 ivs;
    /*0x04*/ u32 personality;
    /*0x08*/ u16 species;
    /*0x0A*/ u16 hp;
    /*0x0C*/ u8 level;
    /*0x0D*/ u8 status;
    /*0x0E*/ u8 cool;
    /*0x0F*/ u8 beauty;
    /*0x10*/ u8 cute;
    /*0x11*/ u8 smart;
    /*0x12*/ u8 tough;
    /*0x13*/ bool8 active;
    /*0x14*/ u8 filler[0x8];
};

struct RamScriptData
{
    u8 magic;
    u8 mapGroup;
    u8 mapNum;
    u8 objectId;
    u8 script[995];
};

struct RamScript
{
    u32 checksum;
    struct RamScriptData data;
};

struct EasyChatPair
{
    u16 unk0_0:7;
    u16 unk0_7:7;
    u16 unk1_6:1;
    u16 unk2;
    u16 words[2];
}; /*size = 0x8*/

struct MailStruct
{
    /*0x00*/ u16 words[MAIL_WORDS_COUNT];
    /*0x12*/ u8 playerName[PLAYER_NAME_LENGTH];
    /*0x1A*/ u8 trainerId[4];
    /*0x1E*/ u16 species;
    /*0x20*/ u16 itemId;
};

struct MauvilleManCommon
{
    u8 id;
};

struct MauvilleManBard
{
    /*0x00*/ u8 id;
    /*0x02*/ u16 songLyrics[6];
    /*0x0E*/ u16 temporaryLyrics[6];
    /*0x1A*/ u8 playerName[8];
    /*0x22*/ u8 filler_2DB6[0x3];
    /*0x25*/ u8 playerTrainerId[4];
    /*0x29*/ bool8 hasChangedSong;
    /*0x2A*/ u8 language;
}; /*size = 0x2C*/

struct MauvilleManStoryteller
{
    u8 id;
    bool8 alreadyRecorded;
    u8 filler2[2];
    u8 gameStatIDs[4];
    u8 trainerNames[4][7];
    u8 statValues[4][4];
    u8 language[4];
};

struct MauvilleManGiddy
{
    /*0x00*/ u8 id;
    /*0x01*/ u8 taleCounter;
    /*0x02*/ u8 questionNum;
    /*0x04*/ u16 randomWords[10];
    /*0x18*/ u8 questionList[8];
    /*0x20*/ u8 language;
}; /*size = 0x2C*/

struct MauvilleManHipster
{
    u8 id;
    bool8 alreadySpoken;
    u8 language;
};

struct MauvilleOldManTrader
{
    u8 id;
    u8 decorIds[4];
    u8 playerNames[4][11];
    u8 alreadyTraded;
    u8 language[4];
};

typedef union OldMan
{
    struct MauvilleManCommon common;
    struct MauvilleManBard bard;
    struct MauvilleManGiddy giddy;
    struct MauvilleManHipster hipster;
    struct MauvilleOldManTrader trader;
    struct MauvilleManStoryteller storyteller;
    u8 filler[0x40];
} OldMan;

struct RecordMixing_UnknownStructSub
{
    u32 unk0;
    u8 data[0x34];
    //u8 data[0x38];
};

struct RecordMixing_UnknownStruct
{
    struct RecordMixing_UnknownStructSub data[2];
    u32 unk70;
    u16 unk74[0x2];
};

#define LINK_B_RECORDS_COUNT 5

struct LinkBattleRecord
{
    u8 name[8];
    u16 trainerId;
    u16 wins;
    u16 losses;
    u16 draws;
};

struct LinkBattleRecords
{
    struct LinkBattleRecord entries[LINK_B_RECORDS_COUNT];
    u8 languages[LINK_B_RECORDS_COUNT];
};

struct RecordMixingGiftData
{
    u8 unk0;
    u8 quantity;
    u16 itemId;
    u8 filler4[8];
};

struct RecordMixingGift
{
    int checksum;
    struct RecordMixingGiftData data;
};

struct ContestWinner
{
    u32 personality;
    u32 trainerId;
    u16 species;
    u8 contestCategory;
    u8 monName[11];
    u8 trainerName[8];
    u8 contestRank;
};

struct DayCareMail
{
    struct MailStruct message;
    u8 OT_name[OT_NAME_LENGTH + 1];
    u8 monName[POKEMON_NAME_LENGTH + 1];
    u8 gameLanguage:4;
    u8 monLanguage:4;
};

struct DaycareMon
{
    struct BoxPokemon mon;
    struct DayCareMail mail;
    u32 steps;
};

struct DayCare
{
    struct DaycareMon mons[DAYCARE_MON_COUNT];
    u32 offspringPersonality;
    u8 stepCounter;
};

struct RecordMixingDayCareMail
{
    struct DayCareMail mail[DAYCARE_MON_COUNT];
    u32 numDaycareMons;
    bool16 holdsItem[DAYCARE_MON_COUNT];
};

enum
{
    LILYCOVE_LADY_QUIZ,
    LILYCOVE_LADY_FAVOUR,
    LILYCOVE_LADY_CONTEST
};

struct LilycoveLadyQuiz
{
    /*0x000*/ u8 id;
    /*0x001*/ u8 phase;
    /*0x002*/ u16 unk_002[9];
    /*0x014*/ u16 unk_014;
    /*0x016*/ u16 unk_016;
    /*0x018*/ u8 playerName[8];
    /*0x020*/ u16 playerTrainerId[4];
    /*0x028*/ u16 itemId;
    /*0x02a*/ u8 unk_02a;
    /*0x02b*/ u8 unk_02b;
    /*0x02c*/ u8 unk_02c;
    /*0x02d*/ u8 language;
};

struct LilycoveLadyFavour
{
    /*0x000*/ u8 id;
    /*0x001*/ u8 phase;
    /*0x002*/ u8 unk_002;
    /*0x003*/ u8 unk_003;
    /*0x004*/ u8 playerName[8];
    /*0x00c*/ u8 unk_00c;
    /*0x00e*/ u16 itemId;
    /*0x010*/ u16 unk_010;
    /*0x012*/ u8 language;
};

struct LilycoveLadyContest
{
    /*0x000*/ u8 id;
    /*0x001*/ u8 phase;
    /*0x002*/ u8 fave_pkblk;
    /*0x003*/ u8 other_pkblk;
    /*0x004*/ u8 playerName[8];
    /*0x00c*/ u8 max_sheen;
    /*0x00d*/ u8 category;
    /*0x00e*/ u8 language;
};

typedef union
{
    struct LilycoveLadyQuiz quiz;
    struct LilycoveLadyFavour favour;
    struct LilycoveLadyContest contest;
    u8 id;
    u8 pad[0x40];
} LilycoveLady;

struct WaldaPhrase
{
    u16 field_0;
    u16 field_2;
    u8 text[16];
    u8 iconId;
    u8 patternId;
    bool8 patternUnlocked;
};

struct UnkSaveSubstruct_3b98 {
    u32 trainerId;
    u8 trainerName[8];
};

struct SaveBlock1
{
    /*0x00*/ struct Coords16 pos;
    /*0x04*/ struct WarpData location;
    /*0x0C*/ struct WarpData warp1;
    /*0x14*/ struct WarpData warp2;
    /*0x1C*/ struct WarpData lastHealLocation;
    /*0x24*/ struct WarpData warp4;
    /*0x2C*/ u16 savedMusic;
    /*0x2E*/ u8 weather;
    /*0x2F*/ u8 filler_2F;
    /*0x30*/ u8 flashLevel;
    /*0x32*/ u16 mapLayoutId;
    /*0x34*/ u16 mapView[0x100];
    /*0x234*/ u8 playerPartyCount;
    /*0x238*/ struct Pokemon playerParty[PARTY_SIZE];
    /*0x490*/ u32 money;
    /*0x494*/ u16 coins;
    /*0x496*/ u16 registeredItem; // registered for use with SELECT button
    /*0x498*/ struct ItemSlot pcItems[PC_ITEMS_COUNT];
    /*0x560*/ struct ItemSlot bagPocket_Items[BAG_ITEMS_COUNT];
    /*0x5D8*/ struct ItemSlot bagPocket_KeyItems[BAG_KEYITEMS_COUNT];
    /*0x650*/ struct ItemSlot bagPocket_PokeBalls[BAG_POKEBALLS_COUNT];
    /*0x690*/ struct ItemSlot bagPocket_TMHM[BAG_TMHM_COUNT];
    /*0x790*/ struct ItemSlot bagPocket_Berries[BAG_BERRIES_COUNT];
    /*0x848*/ struct Pokeblock pokeblocks[POKEBLOCKS_COUNT];
    /*0x988*/ u8 seen1[DEX_FLAGS_NO];
    /*0x9BC*/ u16 berryBlenderRecords[3];
    /*0x9C2*/ u8 field_9C2[6];
    /*0x9C8*/ u16 trainerRematchStepCounter;
    /*0x9CA*/ u8 trainerRematches[100];
    /*0xA30*/ struct EventObject eventObjects[EVENT_OBJECTS_COUNT];
    /*0xC70*/ struct EventObjectTemplate eventObjectTemplates[64];
    /*0x1270*/ u8 flags[FLAGS_COUNT];
    /*0x139C*/ u16 vars[VARS_COUNT];
    /*0x159C*/ u32 gameStats[NUM_GAME_STATS];
    /*0x169C*/ struct BerryTree berryTrees[BERRY_TREES_COUNT];
    /*0x1A9C*/ struct SecretBaseRecord secretBases[SECRET_BASES_COUNT];
    /*0x271C*/ u8 playerRoomDecor[12];
    /*0x2728*/ u8 playerRoomDecorPos[12];
    /*0x2734*/ u8 decorDesk[10];
    /*0x????*/ u8 decorChair[10];
    /*0x????*/ u8 decorPlant[10];
    /*0x????*/ u8 decorOrnament[30];
    /*0x????*/ u8 decorMat[30];
    /*0x????*/ u8 decorPoster[10];
    /*0x????*/ u8 decorDoll[40];
    /*0x????*/ u8 decorCushion[10];
    /*0x27CA*/ u8 padding_27CA[2];
    /*0x27CC*/ TVShow tvShows[TV_SHOWS_COUNT];
    /*0x2B50*/ PokeNews pokeNews[POKE_NEWS_COUNT];
    /*0x2B90*/ u16 outbreakPokemonSpecies;
    /*0x2B92*/ u8 outbreakLocationMapNum;
    /*0x2B93*/ u8 outbreakLocationMapGroup;
    /*0x2B94*/ u8 outbreakPokemonLevel;
    /*0x2B95*/ u8 outbreakUnk1;
    /*0x2B96*/ u16 outbreakUnk2;
    /*0x2B98*/ u16 outbreakPokemonMoves[4];
    /*0x2BA0*/ u8 outbreakUnk4;
    /*0x2BA1*/ u8 outbreakPokemonProbability;
    /*0x2BA2*/ u16 outbreakDaysLeft;
    /*0x2BA4*/ struct GabbyAndTyData gabbyAndTyData;
    /*0x2BB0*/ u16 unk2BB0[6];
    /*0x2BBC*/ u16 unk2BBC[6];
    /*0x2BC8*/ u16 unk2BC8[6];
    /*0x2BD4*/ u16 unk2BD4[6];
    /*0x2BE0*/ struct MailStruct mail[MAIL_COUNT];
    /*0x2E20*/ u8 additionalPhrases[5]; // bitfield for 33 additional phrases in easy chat system
    /*0x2E25*/ u8 unk2E25[3]; // possibly padding?
    /*0x2E28*/ OldMan oldMan;
    /*0x2e64*/ struct EasyChatPair easyChatPairs[5]; //Dewford trend [0] and some other stuff
    /*0x2e90*/ struct ContestWinner contestWinners[13]; // 0 - 5 used in contest hall, 6 - 7 unused?, 8 - 12 museum
    /*0x3030*/ struct DayCare daycare;
    /*0x3150*/ struct LinkBattleRecords linkBattleRecords;
    /*0x31A8*/ u8 giftRibbons[52];
    /*0x31DC*/ struct Roamer roamer;
    /*0x31F8*/ struct EnigmaBerry enigmaBerry;
    /*0x322C*/ u8 field_322C[1276];
    /*0x3728*/ struct RamScript ramScript;
    /*0x3B14*/ struct RecordMixingGift recordMixingGift;
    /*0x3B24*/ u8 seen2[DEX_FLAGS_NO];
    /*0x3B58*/ LilycoveLady lilycoveLady;
    /*0x3B98*/ struct UnkSaveSubstruct_3b98 unk_3B98[20];
    /*0x3C88*/ u8 filler_3C88[0xE8];
    /*0x3D70*/ struct WaldaPhrase waldaPhrase;
    // sizeof: 0x3D88
};

extern struct SaveBlock1* gSaveBlock1Ptr;

struct MapPosition
{
    s16 x;
    s16 y;
    s8 height;
};

struct UnkStruct_8054FF8
{
    u8 a;
    u8 b;
    u8 c;
    u8 d;
    struct MapPosition sub;
    u16 field_C;
};

struct Bitmap           // TODO: Find a better spot for this
{
    u8* pixels;
    u32 width:16;
    u32 height:16;
};

extern u8 gReservedSpritePaletteCount;

#endif // GUARD_GLOBAL_H
