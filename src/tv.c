#include "global.h"
#include "rtc.h"
#include "overworld.h"
#include "constants/maps.h"
#include "random.h"
#include "event_data.h"
#include "fieldmap.h"
#include "field_camera.h"
#include "strings.h"
#include "string_util.h"
#include "international_string_util.h"
#include "pokemon_storage_system.h"
#include "field_message_box.h"
#include "easy_chat.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "battle.h"
#include "battle_tower.h"
#include "contest.h"
#include "constants/items.h"
#include "item.h"
#include "link.h"
#include "main.h"
#include "event_scripts.h"
#include "shop.h"
#include "lilycove_lady.h"
#include "rom6.h"
#include "pokedex.h"
#include "event_object_movement.h"
#include "text.h"
#include "script_menu.h"
#include "naming_screen.h"
#include "malloc.h"
#include "region_map.h"
#include "constants/region_map_sections.h"
#include "decoration.h"
#include "secret_base.h"
#include "tv.h"
#include "data2.h"

// Static type declarations

#define rbernoulli(num, den) TV_BernoulliTrial(0xFFFF * (num) / (den))

// Static RAM declarations

s8 sCurTVShowSlot;
u16 sTV_SecretBaseVisitMovesTemp[8];
u8 sTV_DecorationsBuffer[16];
struct {
    u8 level;
    u16 species;
    u16 move;
} sTV_SecretBaseVisitMonsTemp[10];

IWRAM_DATA u8 sTVShowMixingNumPlayers;
IWRAM_DATA u8 sTVShowNewsMixingNumPlayers;
IWRAM_DATA s8 sTVShowMixingCurSlot;

EWRAM_DATA u16 sPokemonAnglerSpecies = 0;
EWRAM_DATA u16 sPokemonAnglerAttemptCounters = 0;
EWRAM_DATA u16 sFindThatGamerCoinsSpent = 0;
EWRAM_DATA bool8 sFindThatGamerWhichGame = FALSE;
EWRAM_DATA ALIGNED(4) u8 sRecordMixingPartnersWithoutShowsToShare = 0;
EWRAM_DATA ALIGNED(4) u8 sTVShowState = 0;
EWRAM_DATA u8 sTVSecretBaseSecretsRandomValues[3] = {};

// Static ROM declarations

extern const u8 *const sTVBravoTrainerTextGroup[];
extern const u8 *const sTVBravoTrainerBattleTowerTextGroup[];

void ClearPokemonNews(void);
u8 GetTVChannelByShowType(u8 kind);
u8 FindFirstActiveTVShowThatIsNotAMassOutbreak(void);
u8 CheckForBigMovieOrEmergencyNewsOnTV(void);
void SetTVMetatilesOnMap(int width, int height, u16 tileId);
u8 FindAnyTVNewsOnTheAir(void);
bool8 IsTVShowInSearchOfTrainersAiring(void);
void TakeTVShowInSearchOfTrainersOffTheAir(void);
bool8 TV_BernoulliTrial(u16 ratio);
s8 FindEmptyTVSlotBeyondFirstFiveShowsOfArray(TVShow *shows);
bool8 HasMixableShowAlreadyBeenSpawnedWithPlayerID(u8 kind, bool8 flag);
void tv_store_id_3x(TVShow *show);
void DeleteTVShowInArrayByIdx(TVShow *shows, u8 idx);
s8 FindEmptyTVSlotWithinFirstFiveShowsOfArray(TVShow *shows);
void FindActiveBroadcastByShowType_SetScriptResult(u8 kind);
static void InterviewBefore_BravoTrainerPkmnProfile(void);
static void InterviewBefore_NameRater(void);
u16 TV_GetSomeOtherSpeciesAlreadySeenByPlayer(u16 passedSpecies);
static void sub_80EFA88(void);
static void sub_80EF93C(TVShow *shows);
s8 sub_80EEE30(PokeNews *pokeNews);
bool8 sub_80EF0E4(u8 newsKind);
void ClearPokemonNewsI(u8 i);
static void sub_80F1254(TVShow *shows);
static void sub_80F12A4(TVShow *shows);
static void sub_80F0358(TVShow *player1, TVShow *player2, TVShow *player3, TVShow *player4);
static void sub_80F0C04(void);
static void sub_80F0708(void);
static void sub_80F0B64(void);
static s8 sub_80F06D0(TVShow *tvShows);
static bool8 sub_80F049C(TVShow *dest[], TVShow *src[], u8 idx);
static bool8 sub_80F0580(TVShow *tv1, TVShow *tv2, u8 idx);
static bool8 sub_80F05E8(TVShow *tv1, TVShow *tv2, u8 idx);
static bool8 sub_80F0668(TVShow *tv1, TVShow *tv2, u8 idx);
void SetTvShowInactive(u8 showIdx);
static void sub_80F0B24(u16 species, u8 showIdx);
static void sub_80F0D60(PokeNews *player1, PokeNews *player2, PokeNews *player3, PokeNews *player4);
static void sub_80F0EEC(void);
static void sub_80F0F24(void);
static s8 sub_80F0ECC(PokeNews *pokeNews, u8 idx);
static void sub_80F0E58(PokeNews *dest[], PokeNews *src[]);
static bool8 sub_80F0E84(PokeNews *dest, PokeNews *src, s8 slot);
void TVShowDone(void);
static void InterviewAfter_FanClubLetter(void);
static void InterviewAfter_RecentHappenings(void);
static void InterviewAfter_PkmnFanClubOpinions(void);
static void InterviewAfter_DummyShow4(void);
static void InterviewAfter_BravoTrainerPokemonProfile(void);
static void InterviewAfter_BravoTrainerBattleTowerProfile(void);
static void InterviewAfter_ContestLiveUpdates(void);
void UpdateWorldOfMastersAndPutItOnTheAir(void);
void PutPokemonTodayFailedOnTheAir(void);
static void sub_80ED718(void);
static void sub_80EED88(void);
void TV_SortPurchasesByQuantity(void);
static void sub_80ED8B4(u16 days);
void UpdateMassOutbreakTimeLeft(u16 days);
static void sub_80EF120(u16 days);
static void sub_80EDA48(u16 days);
static void sub_80EEB98(u16 days);
void PutFishingAdviceShowOnTheAir(void);
u8 TV_MonDataIdxToRibbon(u8 monDataIdx);
static void sub_80EEBF4(u8 actionIdx);
bool8 IsPriceDiscounted(u8 newsKind);
static void InterviewBefore_FanClubLetter(void);
static void InterviewBefore_RecentHappenings(void);
static void InterviewBefore_PkmnFanClubOpinions(void);
static void InterviewBefore_Dummy(void);
static void InterviewBefore_BravoTrainerBTProfile(void);
static void InterviewBefore_ContestLiveUpdates(void);
static void InterviewBefore_3CheersForPokeblocks(void);
static void InterviewBefore_FanClubSpecial(void);
void ChangeBoxPokemonNickname_CB(void);
static void DoTVShowPokemonFanClubLetter(void);
static void DoTVShowRecentHappenings(void);
static void DoTVShowPokemonFanClubOpinions(void);
static void DoTVShowDummiedOut(void);
static void DoTVShowPokemonNewsMassOutbreak(void);
static void DoTVShowBravoTrainerPokemonProfile(void);
static void DoTVShowBravoTrainerBattleTower(void);
static void DoTVShowPokemonTodaySuccessfulCapture(void);
static void DoTVShowTodaysSmartShopper(void);
static void DoTVShowTheNameRaterShow(void);
static void DoTVShowPokemonContestLiveUpdates(void);
static void DoTVShowPokemonBattleUpdate(void);
static void DoTVShow3CheersForPokeblocks(void);
static void DoTVShowPokemonTodayFailedCapture(void);
static void DoTVShowPokemonAngler(void);
static void DoTVShowTheWorldOfMasters(void);
static void DoTVShowTodaysRivalTrainer(void);
static void DoTVShowDewfordTrendWatcherNetwork(void);
static void DoTVShowHoennTreasureInvestigators(void);
static void DoTVShowFindThatGamer(void);
static void DoTVShowBreakingNewsTV(void);
static void DoTVShowSecretBaseVisit(void);
static void DoTVShowPokemonLotteryWinnerFlashReport(void);
static void DoTVShowThePokemonBattleSeminar(void);
static void DoTVShowTrainerFanClubSpecial(void);
static void DoTVShowTrainerFanClub(void);
static void DoTVShowSpotTheCuties(void);
static void DoTVShowPokemonNewsBattleFrontier(void);
static void DoTVShowWhatsNo1InHoennToday(void);
static void DoTVShowSecretBaseSecrets(void);
static void DoTVShowSafariFanClub(void);
static void DoTVShowPokemonContestLiveUpdates2(void);

// .rodata

static const struct {
    u16 species;
    u16 moves[4];
    u8 level;
    u8 location;
} sPokeOutbreakSpeciesList[] = {
    {
        SPECIES_SEEDOT,
        {MOVE_BIDE, MOVE_HARDEN, MOVE_LEECH_SEED},
        3, 0x11 // Route 102
    },
    {
        SPECIES_NUZLEAF,
        {MOVE_HARDEN, MOVE_GROWTH, MOVE_NATURE_POWER, MOVE_LEECH_SEED},
        15, 0x1D // Route 114
    },
    {
        SPECIES_SEEDOT,
        {MOVE_HARDEN, MOVE_GROWTH, MOVE_NATURE_POWER, MOVE_LEECH_SEED},
        13, 0x20 // Route 117
    },
    {
        SPECIES_SEEDOT,
        {MOVE_GIGA_DRAIN, MOVE_FRUSTRATION, MOVE_SOLAR_BEAM, MOVE_LEECH_SEED},
        25, 0x23 // Route 110
    },
    {
        SPECIES_SKITTY,
        {MOVE_GROWL, MOVE_TACKLE, MOVE_TAIL_WHIP, MOVE_ATTRACT},
        8, 0x1F // Route 116
    }
};

static const u16 sGoldSymbolFlags[] = {
    FLAG_SYS_TOWER_GOLD,
    FLAG_SYS_DOME_GOLD,
    FLAG_SYS_PALACE_GOLD,
    FLAG_SYS_ARENA_GOLD,
    FLAG_SYS_FACTORY_GOLD,
    FLAG_SYS_PIKE_GOLD,
    FLAG_SYS_PYRAMID_GOLD
};

static const u16 sSilverSymbolFlags[] = {
    FLAG_SYS_TOWER_SILVER,
    FLAG_SYS_DOME_SILVER,
    FLAG_SYS_PALACE_SILVER,
    FLAG_SYS_ARENA_SILVER,
    FLAG_SYS_FACTORY_SILVER,
    FLAG_SYS_PIKE_SILVER,
    FLAG_SYS_PYRAMID_SILVER
};

static const u16 sNumberOneVarsAndThresholds[][2] = {
    {VAR_DAILY_SLOTS, 100},
    {VAR_DAILY_ROULETTE,  50},
    {VAR_DAILY_WILDS, 100},
    {VAR_DAILY_BLENDER,  20},
    {VAR_DAILY_PLANTED_BERRIES,  20},
    {VAR_DAILY_PICKED_BERRIES,  20},
    {VAR_DAILY_BP,  30}
};

static const u8 *const sPokeNewsTextGroup_Upcoming[] = {
    NULL,
    gPokeNewsTextSlateport_Upcoming,
    gPokeNewsTextGameCorner_Upcoming,
    gPokeNewsTextLilycove_Upcoming,
    gPokeNewsTextBlendMaster_Upcoming
};

static const u8 *const sPokeNewsTextGroup_Ongoing[] = {
    NULL,
    gPokeNewsTextSlateport_Ongoing,
    gPokeNewsTextGameCorner_Ongoing,
    gPokeNewsTextLilycove_Ongoing,
    gPokeNewsTextBlendMaster_Ongoing
};

static const u8 *const sPokeNewsTextGroup_Ending[] = {
    NULL,
    gPokeNewsTextSlateport_Ending,
    gPokeNewsTextGameCorner_Ending,
    gPokeNewsTextLilycove_Ending,
    gPokeNewsTextBlendMaster_Ending
};

u8 *const gTVStringVarPtrs[] = {
    gStringVar1,
    gStringVar2,
    gStringVar3
};

static const u8 *const sTVFanClubTextGroup[] = {
    gTVFanClubText00,
    gTVFanClubText01,
    gTVFanClubText02,
    gTVFanClubText03,
    gTVFanClubText04,
    gTVFanClubText05,
    gTVFanClubText06,
    gTVFanClubText07
};

static const u8 *const sTVRecentHappeninssTextGroup[] = {
    gTVRecentHappeningsText00,
    gTVRecentHappeningsText01,
    gTVRecentHappeningsText02,
    gTVRecentHappeningsText03,
    gTVRecentHappeningsText04,
    gTVRecentHappeningsText05
};

static const u8 *const sTVFanClubOpinionsTextGroup[] = {
    gTVFanClubOpinionsText00,
    gTVFanClubOpinionsText01,
    gTVFanClubOpinionsText02,
    gTVFanClubOpinionsText03,
    gTVFanClubOpinionsText04
};

static const u8 *const sTVMassOutbreakTextGroup[] = {
    gTVMassOutbreakText00
};

static const u8 *const sTVPokemonTodaySuccessfulTextGroup[] = {
    gTVPokemonTodaySuccessfulText00,
    gTVPokemonTodaySuccessfulText01,
    gTVPokemonTodaySuccessfulText02,
    gTVPokemonTodaySuccessfulText03,
    gTVPokemonTodaySuccessfulText04,
    gTVPokemonTodaySuccessfulText05,
    gTVPokemonTodaySuccessfulText06,
    gTVPokemonTodaySuccessfulText07,
    gTVPokemonTodaySuccessfulText08,
    gTVPokemonTodaySuccessfulText09,
    gTVPokemonTodaySuccessfulText10,
    gTVPokemonTodaySuccessfulText11
};

static const u8 *const sTVTodaysSmartShopperTextGroup[] = {
    gTVTodaysSmartShopperText00,
    gTVTodaysSmartShopperText01,
    gTVTodaysSmartShopperText02,
    gTVTodaysSmartShopperText03,
    gTVTodaysSmartShopperText04,
    gTVTodaysSmartShopperText05,
    gTVTodaysSmartShopperText06,
    gTVTodaysSmartShopperText07,
    gTVTodaysSmartShopperText08,
    gTVTodaysSmartShopperText09,
    gTVTodaysSmartShopperText10,
    gTVTodaysSmartShopperText11,
    gTVTodaysSmartShopperText12
};

static const u8 *const sTVBravoTrainerTextGroup[] = {
    gTVBravoTrainerText00,
    gTVBravoTrainerText01,
    gTVBravoTrainerText02,
    gTVBravoTrainerText03,
    gTVBravoTrainerText04,
    gTVBravoTrainerText05,
    gTVBravoTrainerText06,
    gTVBravoTrainerText07,
    gTVBravoTrainerText08
};

static const u8 *const sTV3CheersForPokeblocksTextGroup[] = {
    gTV3CheersForPokeblocksText00,
    gTV3CheersForPokeblocksText01,
    gTV3CheersForPokeblocksText02,
    gTV3CheersForPokeblocksText03,
    gTV3CheersForPokeblocksText04,
    gTV3CheersForPokeblocksText05
};

static const u8 *const sTVBravoTrainerBattleTowerTextGroup[] = {
    gTVBravoTrainerBattleTowerText00,
    gTVBravoTrainerBattleTowerText01,
    gTVBravoTrainerBattleTowerText02,
    gTVBravoTrainerBattleTowerText03,
    gTVBravoTrainerBattleTowerText04,
    gTVBravoTrainerBattleTowerText05,
    gTVBravoTrainerBattleTowerText06,
    gTVBravoTrainerBattleTowerText07,
    gTVBravoTrainerBattleTowerText08,
    gTVBravoTrainerBattleTowerText09,
    gTVBravoTrainerBattleTowerText10,
    gTVBravoTrainerBattleTowerText11,
    gTVBravoTrainerBattleTowerText12,
    gTVBravoTrainerBattleTowerText13,
    gTVBravoTrainerBattleTowerText14
};

static const u8 *const sTVContestLiveUpdatesTextGroup[] = {
    gTVContestLiveUpdatesText00,
    gTVContestLiveUpdatesText01,
    gTVContestLiveUpdatesText02,
    gTVContestLiveUpdatesText03,
    gTVContestLiveUpdatesText04,
    gTVContestLiveUpdatesText05,
    gTVContestLiveUpdatesText06,
    gTVContestLiveUpdatesText07,
    gTVContestLiveUpdatesText08,
    gTVContestLiveUpdatesText09,
    gTVContestLiveUpdatesText10,
    gTVContestLiveUpdatesText11,
    gTVContestLiveUpdatesText12,
    gTVContestLiveUpdatesText13,
    gTVContestLiveUpdatesText14,
    gTVContestLiveUpdatesText15,
    gTVContestLiveUpdatesText16,
    gTVContestLiveUpdatesText17,
    gTVContestLiveUpdatesText18,
    gTVContestLiveUpdatesText19,
    gTVContestLiveUpdatesText20,
    gTVContestLiveUpdatesText21,
    gTVContestLiveUpdatesText22,
    gTVContestLiveUpdatesText23,
    gTVContestLiveUpdatesText24,
    gTVContestLiveUpdatesText25,
    gTVContestLiveUpdatesText26,
    gTVContestLiveUpdatesText27,
    gTVContestLiveUpdatesText28,
    gTVContestLiveUpdatesText29,
    gTVContestLiveUpdatesText30,
    gTVContestLiveUpdatesText31,
    gTVContestLiveUpdatesText32
};

static const u8 *const sTVPokemonBattleUpdateTextGroup[] = {
    gTVPokemonBattleUpdateText00,
    gTVPokemonBattleUpdateText01,
    gTVPokemonBattleUpdateText02,
    gTVPokemonBattleUpdateText03,
    gTVPokemonBattleUpdateText04,
    gTVPokemonBattleUpdateText05,
    gTVPokemonBattleUpdateText06,
    gTVPokemonBattleUpdateText07
};

static const u8 *const sTVTrainerFanClubSpecialTextGroup[] = {
    gTVTrainerFanClubSpecialText00,
    gTVTrainerFanClubSpecialText01,
    gTVTrainerFanClubSpecialText02,
    gTVTrainerFanClubSpecialText03,
    gTVTrainerFanClubSpecialText04,
    gTVTrainerFanClubSpecialText05
};

static const u8 *const sTVNameRaterTextGroup[] = {
    gTVNameRaterText00,
    gTVNameRaterText01,
    gTVNameRaterText02,
    gTVNameRaterText03,
    gTVNameRaterText04,
    gTVNameRaterText05,
    gTVNameRaterText06,
    gTVNameRaterText07,
    gTVNameRaterText08,
    gTVNameRaterText09,
    gTVNameRaterText10,
    gTVNameRaterText11,
    gTVNameRaterText12,
    gTVNameRaterText13,
    gTVNameRaterText14,
    gTVNameRaterText15,
    gTVNameRaterText16,
    gTVNameRaterText17,
    gTVNameRaterText18
};

static const u8 *const sTVPokemonContestLiveUpdates2TextGroup[] = {
    gTVPokemonContestLiveUpdates2Text00,
    gTVPokemonContestLiveUpdates2Text01,
    gTVPokemonContestLiveUpdates2Text02,
    gTVPokemonContestLiveUpdates2Text03
};

static const u8 *const sTVPokemonTodayFailedTextGroup[] = {
    gTVPokemonTodayFailedText00,
    gTVPokemonTodayFailedText01,
    gTVPokemonTodayFailedText02,
    gTVPokemonTodayFailedText03,
    gTVPokemonTodayFailedText04,
    gTVPokemonTodayFailedText05,
    gTVPokemonTodayFailedText06
};

static const u8 *const sTVPokemonAnslerTextGroup[] = {
    gTVPokemonAnglerText00,
    gTVPokemonAnglerText01
};

static const u8 *const sTVWorldOfMastersTextGroup[] = {
    gTVWorldOfMastersText00,
    gTVWorldOfMastersText01,
    gTVWorldOfMastersText02
};

static const u8 *const sTVTodaysRivalTrainerTextGroup[] = {
    gTVTodaysRivalTrainerText00,
    gTVTodaysRivalTrainerText01,
    gTVTodaysRivalTrainerText02,
    gTVTodaysRivalTrainerText03,
    gTVTodaysRivalTrainerText04,
    gTVTodaysRivalTrainerText05,
    gTVTodaysRivalTrainerText06,
    gTVTodaysRivalTrainerText07,
    gTVTodaysRivalTrainerText08,
    gTVTodaysRivalTrainerText09,
    gTVTodaysRivalTrainerText10
};

static const u8 *const sTVDewfordTrendWatcherNetworkTextGroup[] = {
    gTVDewfordTrendWatcherNetworkText00,
    gTVDewfordTrendWatcherNetworkText01,
    gTVDewfordTrendWatcherNetworkText02,
    gTVDewfordTrendWatcherNetworkText03,
    gTVDewfordTrendWatcherNetworkText04,
    gTVDewfordTrendWatcherNetworkText05,
    gTVDewfordTrendWatcherNetworkText06
};

static const u8 *const sTVHoennTreasureInvestisatorsTextGroup[] = {
    gTVHoennTreasureInvestigatorsText00,
    gTVHoennTreasureInvestigatorsText01,
    gTVHoennTreasureInvestigatorsText02
};

static const u8 *const sTVFindThatGamerTextGroup[] = {
    gTVFindThatGamerText00,
    gTVFindThatGamerText01,
    gTVFindThatGamerText02,
    gTVFindThatGamerText03
};

static const u8 *const sTVBreakinsNewsTextGroup[] = {
    gTVBreakingNewsText00,
    gTVBreakingNewsText01,
    gTVBreakingNewsText02,
    gTVBreakingNewsText03,
    gTVBreakingNewsText04,
    gTVBreakingNewsText05,
    gTVBreakingNewsText06,
    gTVBreakingNewsText07,
    gTVBreakingNewsText08,
    gTVBreakingNewsText09,
    gTVBreakingNewsText10,
    gTVBreakingNewsText11,
    gTVBreakingNewsText12
};

static const u8 *const sTVSecretBaseVisitTextGroup[] = {
    gTVSecretBaseVisitText00,
    gTVSecretBaseVisitText01,
    gTVSecretBaseVisitText02,
    gTVSecretBaseVisitText03,
    gTVSecretBaseVisitText04,
    gTVSecretBaseVisitText05,
    gTVSecretBaseVisitText06,
    gTVSecretBaseVisitText07,
    gTVSecretBaseVisitText08,
    gTVSecretBaseVisitText09,
    gTVSecretBaseVisitText10,
    gTVSecretBaseVisitText11,
    gTVSecretBaseVisitText12,
    gTVSecretBaseVisitText13
};

static const u8 *const sTVPokemonLotteryWinnerFlashReportTextGroup[] = {
    gTVPokemonLotteryWinnerFlashReportText00
};

static const u8 *const sTVThePokemonBattleSeminarTextGroup[] = {
    gTVThePokemonBattleSeminarText00,
    gTVThePokemonBattleSeminarText01,
    gTVThePokemonBattleSeminarText02,
    gTVThePokemonBattleSeminarText03,
    gTVThePokemonBattleSeminarText04,
    gTVThePokemonBattleSeminarText05,
    gTVThePokemonBattleSeminarText06
};

static const u8 *const sTVTrainerFanClubTextGroup[] = {
    gTVTrainerFanClubText00,
    gTVTrainerFanClubText01,
    gTVTrainerFanClubText02,
    gTVTrainerFanClubText03,
    gTVTrainerFanClubText04,
    gTVTrainerFanClubText05,
    gTVTrainerFanClubText06,
    gTVTrainerFanClubText07,
    gTVTrainerFanClubText08,
    gTVTrainerFanClubText09,
    gTVTrainerFanClubText10,
    gTVTrainerFanClubText11
};

static const u8 *const sTVCutiesTextGroup[] = {
    gTVCutiesText00,
    gTVCutiesText01,
    gTVCutiesText02,
    gTVCutiesText03,
    gTVCutiesText04,
    gTVCutiesText05,
    gTVCutiesText06,
    gTVCutiesText07,
    gTVCutiesText08,
    gTVCutiesText09,
    gTVCutiesText10,
    gTVCutiesText11,
    gTVCutiesText12,
    gTVCutiesText13,
    gTVCutiesText14,
    gTVCutiesText15
};

static const u8 *const sTVPokemonNewsBattleFrontierTextGroup[] = {
    gTVPokemonNewsBattleFrontierText00,
    gTVPokemonNewsBattleFrontierText01,
    gTVPokemonNewsBattleFrontierText02,
    gTVPokemonNewsBattleFrontierText03,
    gTVPokemonNewsBattleFrontierText04,
    gTVPokemonNewsBattleFrontierText05,
    gTVPokemonNewsBattleFrontierText06,
    gTVPokemonNewsBattleFrontierText07,
    gTVPokemonNewsBattleFrontierText08,
    gTVPokemonNewsBattleFrontierText09,
    gTVPokemonNewsBattleFrontierText10,
    gTVPokemonNewsBattleFrontierText11,
    gTVPokemonNewsBattleFrontierText12,
    gTVPokemonNewsBattleFrontierText13,
    gTVPokemonNewsBattleFrontierText14,
    gTVPokemonNewsBattleFrontierText15,
    gTVPokemonNewsBattleFrontierText16,
    gTVPokemonNewsBattleFrontierText17,
    gTVPokemonNewsBattleFrontierText18
};

static const u8 *const sTVWhatsNo1InHoennTodayTextGroup[] = {
    gTVWhatsNo1InHoennTodayText00,
    gTVWhatsNo1InHoennTodayText01,
    gTVWhatsNo1InHoennTodayText02,
    gTVWhatsNo1InHoennTodayText03,
    gTVWhatsNo1InHoennTodayText04,
    gTVWhatsNo1InHoennTodayText05,
    gTVWhatsNo1InHoennTodayText06,
    gTVWhatsNo1InHoennTodayText07,
    gTVWhatsNo1InHoennTodayText08
};

static const u8 *const sTVSecretBaseSecretsTextGroup[] = {
    gTVSecretBaseSecretsText00,
    gTVSecretBaseSecretsText01,
    gTVSecretBaseSecretsText02,
    gTVSecretBaseSecretsText03,
    gTVSecretBaseSecretsText04,
    gTVSecretBaseSecretsText05,
    gTVSecretBaseSecretsText06,
    gTVSecretBaseSecretsText07,
    gTVSecretBaseSecretsText08,
    gTVSecretBaseSecretsText09,
    gTVSecretBaseSecretsText10,
    gTVSecretBaseSecretsText11,
    gTVSecretBaseSecretsText12,
    gTVSecretBaseSecretsText13,
    gTVSecretBaseSecretsText14,
    gTVSecretBaseSecretsText15,
    gTVSecretBaseSecretsText16,
    gTVSecretBaseSecretsText17,
    gTVSecretBaseSecretsText18,
    gTVSecretBaseSecretsText19,
    gTVSecretBaseSecretsText20,
    gTVSecretBaseSecretsText21,
    gTVSecretBaseSecretsText22,
    gTVSecretBaseSecretsText23,
    gTVSecretBaseSecretsText24,
    gTVSecretBaseSecretsText25,
    gTVSecretBaseSecretsText26,
    gTVSecretBaseSecretsText27,
    gTVSecretBaseSecretsText28,
    gTVSecretBaseSecretsText29,
    gTVSecretBaseSecretsText30,
    gTVSecretBaseSecretsText31,
    gTVSecretBaseSecretsText32,
    gTVSecretBaseSecretsText33,
    gTVSecretBaseSecretsText34,
    gTVSecretBaseSecretsText35,
    gTVSecretBaseSecretsText36,
    gTVSecretBaseSecretsText37,
    gTVSecretBaseSecretsText38,
    gTVSecretBaseSecretsText39,
    gTVSecretBaseSecretsText40,
    gTVSecretBaseSecretsText41,
    gTVSecretBaseSecretsText42
};

static const u8 *const sTVSafariFanClubTextGroup[] = {
    gTVSafariFanClubText00,
    gTVSafariFanClubText01,
    gTVSafariFanClubText02,
    gTVSafariFanClubText03,
    gTVSafariFanClubText04,
    gTVSafariFanClubText05,
    gTVSafariFanClubText06,
    gTVSafariFanClubText07,
    gTVSafariFanClubText08,
    gTVSafariFanClubText09,
    gTVSafariFanClubText10
};

static const u8 *const sTVInSearchOfTrainersTextGroup[] = {
    gTVInSearchOfTrainersText00,
    gTVInSearchOfTrainersText01,
    gTVInSearchOfTrainersText02,
    gTVInSearchOfTrainersText03,
    gTVInSearchOfTrainersText04,
    gTVInSearchOfTrainersText05,
    gTVInSearchOfTrainersText06,
    gTVInSearchOfTrainersText07,
    gTVInSearchOfTrainersText08
};

const u8 sTVSecretBaseSecretsStateLookup[] = {
    0x0a,
    0x0b,
    0x0c,
    0x0d,
    0x0e,
    0x0f,
    0x10,
    0x11,
    0x12,
    0x13,
    0x14,
    0x17,
    0x18,
    0x19,
    0x1a,
    0x1b,
    0x1c,
    0x1d,
    0x1e,
    0x1f,
    0x20,
    0x21,
    0x22,
    0x23,
    0x24,
    0x25,
    0x26,
    0x27,
    0x28,
    0x29,
    0x2a,
    0x2b
};

// .text

void ClearTVShowData(void)
{
    u8 i;
    u8 j;

    for (i = 0; i < ARRAY_COUNT(gSaveBlock1Ptr->tvShows); i ++)
    {
        gSaveBlock1Ptr->tvShows[i].common.kind = 0;
        gSaveBlock1Ptr->tvShows[i].common.active = 0;
        for (j = 0; j < sizeof(TVShow) - 2; j ++)
        {
            gSaveBlock1Ptr->tvShows[i].common.pad02[j] = 0;
        }
    }
    ClearPokemonNews();
}

u8 special_0x44(void)
{
    u8 i;
    u8 j;
    u8 selIdx;
    TVShow *show;

    for (i = 5; i < ARRAY_COUNT(gSaveBlock1Ptr->tvShows) - 1; i ++)
    {
        if (gSaveBlock1Ptr->tvShows[i].common.kind == 0)
        {
            break;
        }
    }
    j = Random() % i;
    selIdx = j;
    do
    {
        if (GetTVChannelByShowType(gSaveBlock1Ptr->tvShows[j].common.kind) != 4)
        {
            if (gSaveBlock1Ptr->tvShows[j].common.active == TRUE)
            {
                return j;
            }
        }
        else
        {
            show = &gSaveBlock1Ptr->tvShows[j];
            if (show->massOutbreak.daysLeft == 0 && show->massOutbreak.active == TRUE)
            {
                return j;
            }
        }
        if (j == 0)
        {
            j = ARRAY_COUNT(gSaveBlock1Ptr->tvShows) - 2;
        }
        else
        {
            j --;
        }
    } while (j != selIdx);
    return 0xFF;
}

u8 FindAnyTVShowOnTheAir(void)
{
    u8 response;

    response = special_0x44();
    if (response == 0xFF)
    {
        return 0xFF;
    }
    if (gSaveBlock1Ptr->outbreakPokemonSpecies != SPECIES_NONE && gSaveBlock1Ptr->tvShows[response].common.kind == TVSHOW_MASS_OUTBREAK)
    {
        return FindFirstActiveTVShowThatIsNotAMassOutbreak();
    }
    return response;
}

void UpdateTVScreensOnMap(int width, int height)
{
    FlagSet(FLAG_SYS_TV_WATCH);
    switch (CheckForBigMovieOrEmergencyNewsOnTV())
    {
        case 1:
            SetTVMetatilesOnMap(width, height, 0x3);
            break;
        case 2:
            break;
        default:
            if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(LILYCOVE_CITY_COVE_LILY_MOTEL_1F) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(LILYCOVE_CITY_COVE_LILY_MOTEL_1F))
            {
                SetTVMetatilesOnMap(width, height, 0x3);
            }
            else if (FlagGet(FLAG_SYS_TV_START) && (FindAnyTVShowOnTheAir() != 0xff || FindAnyTVNewsOnTheAir() != 0xff || IsTVShowInSearchOfTrainersAiring()))
            {
                FlagClear(FLAG_SYS_TV_WATCH);
                SetTVMetatilesOnMap(width, height, 0x3);
            }
            break;
    }
}

void SetTVMetatilesOnMap(int width, int height, u16 tileId)
{
    int x;
    int y;

    for (y = 0; y < height; y ++)
    {
        for (x = 0; x < width; x ++)
        {
            if (MapGridGetMetatileBehaviorAt(x, y) == 0x86) // is this tile a TV?
            {
                MapGridSetMetatileIdAt(x, y, tileId | 0xc00);
            }
        }
    }
}

void TurnOffTVScreen(void)
{
    SetTVMetatilesOnMap(gUnknown_03005DC0.width, gUnknown_03005DC0.height, 0x0002);
    DrawWholeMapView();
}

void TurnOnTVScreen(void)
{
    SetTVMetatilesOnMap(gUnknown_03005DC0.width, gUnknown_03005DC0.height, 0x0003);
    DrawWholeMapView();
}

u8 special_0x45(void)
{
    return gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004].common.kind;
}

u8 FindFirstActiveTVShowThatIsNotAMassOutbreak(void)
{
    u8 i;

    for (i = 0; i < ARRAY_COUNT(gSaveBlock1Ptr->tvShows) - 1; i ++)
    {
        if (gSaveBlock1Ptr->tvShows[i].common.kind != 0 && gSaveBlock1Ptr->tvShows[i].common.kind != TVSHOW_MASS_OUTBREAK && gSaveBlock1Ptr->tvShows[i].common.active == TRUE)
        {
            return i;
        }
    }
    return 0xFF;
}

u8 special_0x4a(void)
{
    TVShow *tvShow;

    tvShow = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    if (tvShow->common.kind == TVSHOW_MASS_OUTBREAK && gSaveBlock1Ptr->outbreakPokemonSpecies != SPECIES_NONE)
    {
        return FindFirstActiveTVShowThatIsNotAMassOutbreak();
    }
    return gSpecialVar_0x8004;
}

// IN SEARCH OF TRAINERS

void ResetGabbyAndTy(void)
{
    gSaveBlock1Ptr->gabbyAndTyData.mon1 = SPECIES_NONE;
    gSaveBlock1Ptr->gabbyAndTyData.mon2 = SPECIES_NONE;
    gSaveBlock1Ptr->gabbyAndTyData.lastMove = MOVE_NONE;
    gSaveBlock1Ptr->gabbyAndTyData.quote[0] = -1;
    gSaveBlock1Ptr->gabbyAndTyData.battleTookMoreThanOneTurn = FALSE;
    gSaveBlock1Ptr->gabbyAndTyData.playerLostAMon = FALSE;
    gSaveBlock1Ptr->gabbyAndTyData.playerUsedAnItem = FALSE;
    gSaveBlock1Ptr->gabbyAndTyData.playerThrewABall = FALSE;
    gSaveBlock1Ptr->gabbyAndTyData.onAir = FALSE;
    gSaveBlock1Ptr->gabbyAndTyData.valA_5 = 0;
    gSaveBlock1Ptr->gabbyAndTyData.battleTookMoreThanOneTurn2 = FALSE;
    gSaveBlock1Ptr->gabbyAndTyData.playerLostAMon2 = FALSE;
    gSaveBlock1Ptr->gabbyAndTyData.playerUsedAnItem2 = FALSE;
    gSaveBlock1Ptr->gabbyAndTyData.playerThrewABall2 = FALSE;
    gSaveBlock1Ptr->gabbyAndTyData.valB_4 = 0;
    gSaveBlock1Ptr->gabbyAndTyData.mapnum = 0;
    gSaveBlock1Ptr->gabbyAndTyData.battleNum = 0;
}

void GabbyAndTyBeforeInterview(void)
{
    u8 i;

    gSaveBlock1Ptr->gabbyAndTyData.mon1 = gBattleResults.playerMon1Species;
    gSaveBlock1Ptr->gabbyAndTyData.mon2 = gBattleResults.playerMon2Species;
    gSaveBlock1Ptr->gabbyAndTyData.lastMove = gBattleResults.lastUsedMovePlayer;
    if (gSaveBlock1Ptr->gabbyAndTyData.battleNum != 0xFF)
    {
        gSaveBlock1Ptr->gabbyAndTyData.battleNum ++;
    }
    gSaveBlock1Ptr->gabbyAndTyData.battleTookMoreThanOneTurn = gBattleResults.unk5_0;
    if (gBattleResults.playerFaintCounter != 0)
    {
        gSaveBlock1Ptr->gabbyAndTyData.playerLostAMon = TRUE;
    }
    else
    {
        gSaveBlock1Ptr->gabbyAndTyData.playerLostAMon = FALSE;
    }
    if (gBattleResults.unk3 != 0)
    {
        gSaveBlock1Ptr->gabbyAndTyData.playerUsedAnItem = TRUE;
    }
    else
    {
        gSaveBlock1Ptr->gabbyAndTyData.playerUsedAnItem = FALSE;
    }
    if (!gBattleResults.usedMasterBall)
    {
        for (i = 0; i < 11; i ++)
        {
            if (gBattleResults.catchAttempts[i])
            {
                gSaveBlock1Ptr->gabbyAndTyData.playerThrewABall = TRUE;
                break;
            }
        }
    }
    else
    {
        gSaveBlock1Ptr->gabbyAndTyData.playerThrewABall = TRUE;
    }
    TakeTVShowInSearchOfTrainersOffTheAir();
    if (gSaveBlock1Ptr->gabbyAndTyData.lastMove == MOVE_NONE)
    {
        FlagSet(0x0001);
    }
}

void GabbyAndTyAfterInterview(void)
{
    gSaveBlock1Ptr->gabbyAndTyData.battleTookMoreThanOneTurn2 = gSaveBlock1Ptr->gabbyAndTyData.battleTookMoreThanOneTurn;
    gSaveBlock1Ptr->gabbyAndTyData.playerLostAMon2 = gSaveBlock1Ptr->gabbyAndTyData.playerLostAMon;
    gSaveBlock1Ptr->gabbyAndTyData.playerUsedAnItem2 = gSaveBlock1Ptr->gabbyAndTyData.playerUsedAnItem;
    gSaveBlock1Ptr->gabbyAndTyData.playerThrewABall2 = gSaveBlock1Ptr->gabbyAndTyData.playerThrewABall;
    gSaveBlock1Ptr->gabbyAndTyData.onAir = TRUE;
    gSaveBlock1Ptr->gabbyAndTyData.mapnum = gMapHeader.regionMapSectionId;
    IncrementGameStat(GAME_STAT_GOT_INTERVIEWED);
}

void TakeTVShowInSearchOfTrainersOffTheAir(void)
{
    gSaveBlock1Ptr->gabbyAndTyData.onAir = FALSE;
}

u8 GabbyAndTyGetBattleNum(void)
{
    if (gSaveBlock1Ptr->gabbyAndTyData.battleNum > 5)
    {
        return (gSaveBlock1Ptr->gabbyAndTyData.battleNum % 3) + 6;
    }
    return gSaveBlock1Ptr->gabbyAndTyData.battleNum;
}

bool8 IsTVShowInSearchOfTrainersAiring(void)
{
    return gSaveBlock1Ptr->gabbyAndTyData.onAir;
}

bool8 GabbyAndTyGetLastQuote(void)
{
    if (gSaveBlock1Ptr->gabbyAndTyData.quote[0] == 0xFFFF)
    {
        return FALSE;
    }
    CopyEasyChatWord(gStringVar1, gSaveBlock1Ptr->gabbyAndTyData.quote[0]);
    gSaveBlock1Ptr->gabbyAndTyData.quote[0] = -1;
    return TRUE;
}

u8 GabbyAndTyGetLastBattleTrivia(void)
{
    if (!gSaveBlock1Ptr->gabbyAndTyData.battleTookMoreThanOneTurn2)
    {
        return 1;
    }
    if (gSaveBlock1Ptr->gabbyAndTyData.playerThrewABall2)
    {
        return 2;
    }
    if (gSaveBlock1Ptr->gabbyAndTyData.playerUsedAnItem2)
    {
        return 3;
    }
    if (gSaveBlock1Ptr->gabbyAndTyData.playerLostAMon2)
    {
        return 4;
    }
    return 0;
}

void GabbyAndTySetScriptVarsToEventObjectLocalIds(void)
{
    switch (GabbyAndTyGetBattleNum())
    {
        case 1:
            gSpecialVar_0x8004 = 14;
            gSpecialVar_0x8005 = 13;
            break;
        case 2:
            gSpecialVar_0x8004 = 5;
            gSpecialVar_0x8005 = 6;
            break;
        case 3:
            gSpecialVar_0x8004 = 18;
            gSpecialVar_0x8005 = 17;
            break;
        case 4:
            gSpecialVar_0x8004 = 21;
            gSpecialVar_0x8005 = 22;
            break;
        case 5:
            gSpecialVar_0x8004 = 8;
            gSpecialVar_0x8005 = 9;
            break;
        case 6:
            gSpecialVar_0x8004 = 19;
            gSpecialVar_0x8005 = 20;
            break;
        case 7:
            gSpecialVar_0x8004 = 23;
            gSpecialVar_0x8005 = 24;
            break;
        case 8:
            gSpecialVar_0x8004 = 10;
            gSpecialVar_0x8005 = 11;
            break;
    }
}

void InterviewAfter(void)
{
    switch (gSpecialVar_0x8005)
    {
        case TVSHOW_FAN_CLUB_LETTER:
            InterviewAfter_FanClubLetter();
            break;
        case TVSHOW_RECENT_HAPPENINGS:
            InterviewAfter_RecentHappenings();
            break;
        case TVSHOW_PKMN_FAN_CLUB_OPINIONS:
            InterviewAfter_PkmnFanClubOpinions();
            break;
        case TVSHOW_UNKN_SHOWTYPE_04:
            InterviewAfter_DummyShow4();
            break;
        case TVSHOW_BRAVO_TRAINER_POKEMON_PROFILE:
            InterviewAfter_BravoTrainerPokemonProfile();
            break;
        case TVSHOW_BRAVO_TRAINER_BATTLE_TOWER_PROFILE:
            InterviewAfter_BravoTrainerBattleTowerProfile();
            break;
        case TVSHOW_CONTEST_LIVE_UPDATES:
            InterviewAfter_ContestLiveUpdates();
            break;
    }
}

void PutPokemonTodayCaughtOnAir(void)
{
    u8 i;
    u16 ct;
    TVShow *show;
    u32 language2;
    u16 itemLastUsed;

    ct = 0;
    sub_80EED88();
    sub_80ED718();
    if (gBattleResults.caughtMonSpecies == SPECIES_NONE)
    {
        PutPokemonTodayFailedOnTheAir();
    }
    else
    {
        UpdateWorldOfMastersAndPutItOnTheAir();
        if (!rbernoulli(1, 1) && StringCompare(gSpeciesNames[gBattleResults.caughtMonSpecies], gBattleResults.caughtMonNick))
        {
            sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
            if (sCurTVShowSlot != -1 && HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_POKEMON_TODAY_CAUGHT, FALSE) != TRUE)
            {
                for (i = 0; i < 11; i ++)
                {
                    ct += gBattleResults.catchAttempts[i];
                }
                if (ct != 0 || gBattleResults.usedMasterBall)
                {
                    ct = 0;
                    show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
                    show->pokemonToday.kind = TVSHOW_POKEMON_TODAY_CAUGHT;
                    show->pokemonToday.active = FALSE;
                    if (gBattleResults.usedMasterBall)
                    {
                        ct = 1;
                        itemLastUsed = ITEM_MASTER_BALL;
                    }
                    else
                    {
                        for (i = 0; i < 11; i ++)
                        {
                            ct += gBattleResults.catchAttempts[i];
                        }
                        if (ct > 0xFF)
                        {
                            ct = 0xFF;
                        }
                        itemLastUsed = gLastUsedItem;
                    }
                    show->pokemonToday.nBallsUsed = ct;
                    show->pokemonToday.ball = itemLastUsed;
                    StringCopy(show->pokemonToday.playerName, gSaveBlock2Ptr->playerName);
                    StringCopy(show->pokemonToday.nickname, gBattleResults.caughtMonNick);
                    language2 = sub_81DB604(show->pokemonToday.nickname);
                    StripExtCtrlCodes(show->pokemonToday.nickname);
                    show->pokemonToday.species = gBattleResults.caughtMonSpecies;
                    tv_store_id_3x(show);
                    show->pokemonToday.language = gGameLanguage;
                    show->pokemonToday.language2 = language2;
                }
            }
        }
    }
}

void UpdateWorldOfMastersAndPutItOnTheAir(void)
{
    TVShow *show;

    show = &gSaveBlock1Ptr->tvShows[24];
    if (show->worldOfMasters.kind != TVSHOW_WORLD_OF_MASTERS)
    {
        DeleteTVShowInArrayByIdx(gSaveBlock1Ptr->tvShows, 24);
        show->worldOfMasters.steps = GetGameStat(GAME_STAT_STEPS);
        show->worldOfMasters.kind = TVSHOW_WORLD_OF_MASTERS;
    }
    show->worldOfMasters.numPokeCaught ++;
    show->worldOfMasters.caughtPoke = gBattleResults.caughtMonSpecies;
    show->worldOfMasters.species = gBattleResults.playerMon1Species;
    show->worldOfMasters.location = gMapHeader.regionMapSectionId;
}

void PutPokemonTodayFailedOnTheAir(void)
{
    u16 ct;
    u8 i;
    TVShow *show;

    if (!rbernoulli(1, 1))
    {
        for (i = 0, ct = 0; i < 11; i ++)
        {
            ct += gBattleResults.catchAttempts[i];
        }
        if (ct > 0xFF)
        {
            ct = 0xFF;
        }
        if (ct > 2 && (gBattleOutcome == B_OUTCOME_MON_FLED || gBattleOutcome == B_OUTCOME_WON))
        {
            sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
            if (sCurTVShowSlot != -1 && HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_POKEMON_TODAY_FAILED, FALSE) != TRUE)
            {
                show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
                show->pokemonTodayFailed.kind = TVSHOW_POKEMON_TODAY_FAILED;
                show->pokemonTodayFailed.active = FALSE;
                show->pokemonTodayFailed.species = gBattleResults.playerMon1Species;
                show->pokemonTodayFailed.species2 = gBattleResults.lastOpponentSpecies;
                show->pokemonTodayFailed.nBallsUsed = ct;
                show->pokemonTodayFailed.outcome = gBattleOutcome;
                show->pokemonTodayFailed.location = gMapHeader.regionMapSectionId;
                StringCopy(show->pokemonTodayFailed.playerName, gSaveBlock2Ptr->playerName);
                tv_store_id_3x(show);
                show->pokemonTodayFailed.language = gGameLanguage;
            }
        }
    }
}

void tv_store_id_3x(TVShow *show)
{
    u32 id;

    id = GetPlayerIDAsU32();
    show->common.srcTrainerId2Lo = id;
    show->common.srcTrainerId2Hi = id >> 8;
    show->common.srcTrainerIdLo = id;
    show->common.srcTrainerIdHi = id >> 8;
    show->common.trainerIdLo = id;
    show->common.trainerIdHi = id >> 8;
}

void tv_store_id_2x(TVShow *show)
{
    u32 id;

    id = GetPlayerIDAsU32();
    show->common.srcTrainerIdLo = id;
    show->common.srcTrainerIdHi = id >> 8;
    show->common.trainerIdLo = id;
    show->common.trainerIdHi = id >> 8;
}

static void InterviewAfter_ContestLiveUpdates(void)
{
    TVShow *show;
    TVShow *show2;

    show = &gSaveBlock1Ptr->tvShows[24];
    if (show->contestLiveUpdates.kind == TVSHOW_CONTEST_LIVE_UPDATES)
    {
        show2 = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
        show2->contestLiveUpdates.kind = TVSHOW_CONTEST_LIVE_UPDATES;
        show2->contestLiveUpdates.active = TRUE;
        StringCopy(show2->contestLiveUpdates.playerName, gSaveBlock2Ptr->playerName);
        show2->contestLiveUpdates.category = gSpecialVar_ContestCategory;
        show2->contestLiveUpdates.species = GetMonData(&gPlayerParty[gUnknown_02039F24], MON_DATA_SPECIES, NULL);
        show2->contestLiveUpdates.winningSpecies = show->contestLiveUpdates.winningSpecies;
        show2->contestLiveUpdates.appealFlags2 = show->contestLiveUpdates.appealFlags2;
        show2->contestLiveUpdates.round1Rank = show->contestLiveUpdates.round1Rank;
        show2->contestLiveUpdates.round2Rank = show->contestLiveUpdates.round2Rank;
        show2->contestLiveUpdates.move = show->contestLiveUpdates.move;
        show2->contestLiveUpdates.appealFlags1 = show->contestLiveUpdates.appealFlags1;
        StringCopy(show2->contestLiveUpdates.winningTrainerName, show->contestLiveUpdates.winningTrainerName);
        tv_store_id_2x(show2);
        show2->contestLiveUpdates.language = gGameLanguage;
        show2->contestLiveUpdates.winningTrainerLanguage = show->contestLiveUpdates.winningTrainerLanguage;
        DeleteTVShowInArrayByIdx(gSaveBlock1Ptr->tvShows, 24);
    }
}

void PutBattleUpdateOnTheAir(u8 opponentLinkPlayerId, u16 move, u16 speciesPlayer, u16 speciesOpponent)
{
    TVShow *show;
    u8 name[32];

    sCurTVShowSlot = FindEmptyTVSlotWithinFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1)
    {
        FindActiveBroadcastByShowType_SetScriptResult(TVSHOW_BATTLE_UPDATE);
        if (gSpecialVar_Result != 1)
        {
            show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
            show->battleUpdate.kind = TVSHOW_BATTLE_UPDATE;
            show->battleUpdate.active = TRUE;
            StringCopy(show->battleUpdate.playerName, gSaveBlock2Ptr->playerName);
            if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            {
                show->battleUpdate.battleType = 2;
            }
            else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
            {
                show->battleUpdate.battleType = 1;
            }
            else
            {
                show->battleUpdate.battleType = 0;
            }
            show->battleUpdate.move = move;
            show->battleUpdate.speciesPlayer = speciesPlayer;
            show->battleUpdate.speciesOpponent = speciesOpponent;
            StringCopy(name, gLinkPlayers[opponentLinkPlayerId].name);
            StripExtCtrlCodes(name);
            StringCopy(show->battleUpdate.linkOpponentName, name);
            tv_store_id_2x(show);
            show->battleUpdate.language = gGameLanguage;
            if (show->battleUpdate.language == LANGUAGE_JAPANESE || gLinkPlayers[opponentLinkPlayerId].language == LANGUAGE_JAPANESE)
            {
                show->battleUpdate.linkOpponentLanguage = LANGUAGE_JAPANESE;
            }
            else
            {
                show->battleUpdate.linkOpponentLanguage = gLinkPlayers[opponentLinkPlayerId].language;
            }
        }
    }
}

bool8 Put3CheersForPokeblocksOnTheAir(const u8 *partnersName, u8 flavor, u8 unused, u8 sheen, u8 language)
{
    TVShow *show;
    u8 name[32];

    sCurTVShowSlot = FindEmptyTVSlotWithinFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot == -1)
    {
        return FALSE;
    }
    FindActiveBroadcastByShowType_SetScriptResult(TVSHOW_3_CHEERS_FOR_POKEBLOCKS);
    if (gSpecialVar_Result == 1)
    {
        return FALSE;
    }
    show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
    show->threeCheers.kind = TVSHOW_3_CHEERS_FOR_POKEBLOCKS;
    show->threeCheers.active = TRUE;
    StringCopy(show->threeCheers.playerName, gSaveBlock2Ptr->playerName);
    StringCopy(name, partnersName);
    StripExtCtrlCodes(name);
    StringCopy(show->threeCheers.worstBlenderName, name);
    show->threeCheers.flavor = flavor;
    show->threeCheers.unk_03_3 = unused;
    show->threeCheers.sheen = sheen;
    tv_store_id_2x(show);
    show->threeCheers.language = gGameLanguage;
    if (show->threeCheers.language == LANGUAGE_JAPANESE || language == LANGUAGE_JAPANESE)
    {
        show->threeCheers.worstBlenderLanguage = LANGUAGE_JAPANESE;
    }
    else
    {
        show->threeCheers.worstBlenderLanguage = language;
    }
    return TRUE;
}

void PutFanClubSpecialOnTheAir(void)
{
    TVShow *show;
    u8 name[32];
    u32 id;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8006];
    show->fanClubSpecial.score = gSpecialVar_0x8005 * 10;
    StringCopy(show->fanClubSpecial.playerName, gSaveBlock2Ptr->playerName);
    show->fanClubSpecial.kind = TVSHOW_FAN_CLUB_SPECIAL;
    show->fanClubSpecial.active = TRUE;
    id = GetPlayerIDAsU32();
    show->fanClubSpecial.idLo = id;
    show->fanClubSpecial.idHi = id >> 8;
    StringCopy(name, gStringVar1);
    StripExtCtrlCodes(name);
    StringCopy(show->fanClubSpecial.idolName, name);
    tv_store_id_2x(show);
    show->fanClubSpecial.language = gGameLanguage;
    if (show->fanClubSpecial.language == LANGUAGE_JAPANESE || gSaveBlock1Ptr->linkBattleRecords.languages[0] == LANGUAGE_JAPANESE)
    {
        show->fanClubSpecial.idolNameLanguage = LANGUAGE_JAPANESE;
    }
    else
    {
        show->fanClubSpecial.idolNameLanguage = gSaveBlock1Ptr->linkBattleRecords.languages[0];
    }
}

void ContestLiveUpdates_BeforeInterview_1(u8 a0)
{
    TVShow *show;

    DeleteTVShowInArrayByIdx(gSaveBlock1Ptr->tvShows, 24);
    sCurTVShowSlot = FindEmptyTVSlotWithinFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1)
    {
        show = &gSaveBlock1Ptr->tvShows[24];
        show->contestLiveUpdates.round1Rank = a0;
        show->contestLiveUpdates.kind = TVSHOW_CONTEST_LIVE_UPDATES;
    }
}

void ContestLiveUpdates_BeforeInterview_2(u8 a0)
{
    TVShow *show;

    show = &gSaveBlock1Ptr->tvShows[24];
    sCurTVShowSlot = FindEmptyTVSlotWithinFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1)
    {
        show->contestLiveUpdates.round2Rank = a0;
    }
}

void ContestLiveUpdates_BeforeInterview_3(u8 a0)
{
    TVShow *show;

    show = &gSaveBlock1Ptr->tvShows[24];
    sCurTVShowSlot = FindEmptyTVSlotWithinFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1)
    {
        show->contestLiveUpdates.appealFlags1 = a0;
    }
}

void ContestLiveUpdates_BeforeInterview_4(u16 a0)
{
    TVShow *show;

    show = &gSaveBlock1Ptr->tvShows[24];
    sCurTVShowSlot = FindEmptyTVSlotWithinFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1)
    {
        show->contestLiveUpdates.move = a0;
    }
}

void ContestLiveUpdates_BeforeInterview_5(u8 a0, u8 a1)
{
    TVShow *show;

    show = &gSaveBlock1Ptr->tvShows[24];
    sCurTVShowSlot = FindEmptyTVSlotWithinFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1)
    {
        show->contestLiveUpdates.winningSpecies = gUnknown_02039E00[a1].unk_00;
        StringCopy(show->contestLiveUpdates.winningTrainerName, gUnknown_02039E00[a1].unk_0d);
        StripExtCtrlCodes(show->contestLiveUpdates.winningTrainerName);
        show->contestLiveUpdates.appealFlags2 = a0;
        if (a1 + 1 > gUnknown_02039F30)
        {
            show->contestLiveUpdates.winningTrainerLanguage = gLinkPlayers[0].language;
        }
        else if (gGameLanguage == LANGUAGE_JAPANESE || gLinkPlayers[a1].language == LANGUAGE_JAPANESE)
        {
            show->contestLiveUpdates.winningTrainerLanguage = LANGUAGE_JAPANESE;
        }
        else
        {
            show->contestLiveUpdates.winningTrainerLanguage = gLinkPlayers[a1].language;
        }
    }
}

static void InterviewAfter_BravoTrainerPokemonProfile(void)
{
    TVShow *show;
    TVShow *show2;

    show = &gSaveBlock1Ptr->tvShows[24];
    if (show->bravoTrainer.kind == TVSHOW_BRAVO_TRAINER_POKEMON_PROFILE)
    {
        show2 = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
        show2->bravoTrainer.kind = TVSHOW_BRAVO_TRAINER_POKEMON_PROFILE;
        show2->bravoTrainer.active = TRUE;
        show2->bravoTrainer.species = show->bravoTrainer.species;
        StringCopy(show2->bravoTrainer.playerName, gSaveBlock2Ptr->playerName);
        StringCopy(show2->bravoTrainer.pokemonNickname, show->bravoTrainer.pokemonNickname);
        show2->bravoTrainer.contestCategory = show->bravoTrainer.contestCategory;
        show2->bravoTrainer.contestRank = show->bravoTrainer.contestRank;
        show2->bravoTrainer.move = show->bravoTrainer.move;
        show2->bravoTrainer.contestResult = show->bravoTrainer.contestResult;
        show2->bravoTrainer.contestCategory = show->bravoTrainer.contestCategory;
        tv_store_id_2x(show2);
        show2->bravoTrainer.language = gGameLanguage;
        if (show2->bravoTrainer.language == LANGUAGE_JAPANESE || show->bravoTrainer.pokemonNameLanguage == LANGUAGE_JAPANESE)
        {
            show2->bravoTrainer.pokemonNameLanguage = LANGUAGE_JAPANESE;
        }
        else
        {
            show2->bravoTrainer.pokemonNameLanguage = show->bravoTrainer.pokemonNameLanguage;
        }
        DeleteTVShowInArrayByIdx(gSaveBlock1Ptr->tvShows, 24);
    }
}

void BravoTrainerPokemonProfile_BeforeInterview1(u16 a0)
{
    TVShow *show;

    show = &gSaveBlock1Ptr->tvShows[24];
    InterviewBefore_BravoTrainerPkmnProfile();
    sCurTVShowSlot = FindEmptyTVSlotWithinFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1)
    {
        DeleteTVShowInArrayByIdx(gSaveBlock1Ptr->tvShows, 24);
        show->bravoTrainer.move = a0;
        show->bravoTrainer.kind = TVSHOW_BRAVO_TRAINER_POKEMON_PROFILE;
    }
}

void BravoTrainerPokemonProfile_BeforeInterview2(u8 a0)
{
    TVShow *show;

    show = &gSaveBlock1Ptr->tvShows[24];
    sCurTVShowSlot = FindEmptyTVSlotWithinFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1)
    {
        show->bravoTrainer.contestResult = a0;
        show->bravoTrainer.contestCategory = gSpecialVar_ContestCategory;
        show->bravoTrainer.contestRank = gSpecialVar_ContestRank;
        show->bravoTrainer.species = GetMonData(&gPlayerParty[gUnknown_02039F24], MON_DATA_SPECIES, NULL);
        GetMonData(&gPlayerParty[gUnknown_02039F24], MON_DATA_NICKNAME, show->bravoTrainer.pokemonNickname);
        StripExtCtrlCodes(show->bravoTrainer.pokemonNickname);
        show->bravoTrainer.pokemonNameLanguage = GetMonData(&gPlayerParty[gUnknown_02039F24], MON_DATA_LANGUAGE);
    }
}

static void InterviewAfter_BravoTrainerBattleTowerProfile(void)
{
    TVShow *show;

    show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
    show->bravoTrainerTower.kind = TVSHOW_BRAVO_TRAINER_BATTLE_TOWER_PROFILE;
    show->bravoTrainerTower.active = TRUE;
    StringCopy(show->bravoTrainerTower.trainerName, gSaveBlock2Ptr->playerName);
    StringCopy(show->bravoTrainerTower.pokemonName, gSaveBlock2Ptr->frontier.field_BD8);
    show->bravoTrainerTower.species = gSaveBlock2Ptr->frontier.field_BD4;
    show->bravoTrainerTower.defeatedSpecies = gSaveBlock2Ptr->frontier.field_BD6;
    show->bravoTrainerTower.numFights = sub_8164FCC(gSaveBlock2Ptr->frontier.field_D07, 0);
    show->bravoTrainerTower.wonTheChallenge = gSaveBlock2Ptr->frontier.field_D06;
    if (gSaveBlock2Ptr->frontier.field_D07 == 0)
    {
        show->bravoTrainerTower.btLevel = 50;
    }
    else
    {
        show->bravoTrainerTower.btLevel = 100;
    }
    show->bravoTrainerTower.interviewResponse = gSpecialVar_0x8004;
    tv_store_id_2x(show);
    show->bravoTrainerTower.language = gGameLanguage;
    if (show->bravoTrainerTower.language == LANGUAGE_JAPANESE || gSaveBlock2Ptr->frontier.field_BEB == LANGUAGE_JAPANESE)
    {
        show->bravoTrainerTower.pokemonNameLanguage = LANGUAGE_JAPANESE;
    }
    else
    {
        show->bravoTrainerTower.pokemonNameLanguage = gSaveBlock2Ptr->frontier.field_BEB;
    }
}

void SaveRecordedItemPurchasesForTVShow(void)
{
    TVShow *show;
    u8 i;

    if (!(gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(TRAINER_HILL_ENTRANCE) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(TRAINER_HILL_ENTRANCE))
     && !(gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(BATTLE_FRONTIER_MART) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(BATTLE_FRONTIER_MART))
     && !rbernoulli(1, 3))
    {
        sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
        if (sCurTVShowSlot != -1 && HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_SMART_SHOPPER, FALSE) != TRUE)
        {
            TV_SortPurchasesByQuantity();
            if (gUnknown_02039F80[0].quantity >= 20)
            {
                show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
                show->smartshopperShow.kind = TVSHOW_SMART_SHOPPER;
                show->smartshopperShow.active = FALSE;
                show->smartshopperShow.shopLocation = gMapHeader.regionMapSectionId;
                for (i = 0; i < 3; i ++)
                {
                    show->smartshopperShow.itemIds[i] = gUnknown_02039F80[i].itemId;
                    show->smartshopperShow.itemAmounts[i] = gUnknown_02039F80[i].quantity;
                }
                show->smartshopperShow.priceReduced = GetPriceReduction(1);
                StringCopy(show->smartshopperShow.playerName, gSaveBlock2Ptr->playerName);
                tv_store_id_3x(show);
                show->smartshopperShow.language = gGameLanguage;
            }
        }
    }
}

void PutNameRaterShowOnTheAir(void)
{
    TVShow *show;

    InterviewBefore_NameRater();
    if (gSpecialVar_Result != 1)
    {
        GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_NICKNAME, gStringVar1);
        if (StringLength(gSaveBlock2Ptr->playerName) > 1 && StringLength(gStringVar1) > 1)
        {
            show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
            show->nameRaterShow.kind = TVSHOW_NAME_RATER_SHOW;
            show->nameRaterShow.active = TRUE;
            show->nameRaterShow.species = GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_SPECIES, NULL);
            show->nameRaterShow.random = Random() % 3;
            show->nameRaterShow.random2 = Random() % 2;
            show->nameRaterShow.randomSpecies = TV_GetSomeOtherSpeciesAlreadySeenByPlayer(show->nameRaterShow.species);
            StringCopy(show->nameRaterShow.trainerName, gSaveBlock2Ptr->playerName);
            GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_NICKNAME, show->nameRaterShow.pokemonName);
            StripExtCtrlCodes(show->nameRaterShow.pokemonName);
            tv_store_id_2x(show);
            show->nameRaterShow.language = gGameLanguage;
            show->nameRaterShow.pokemonNameLanguage = GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_LANGUAGE);
        }
    }
}

void StartMassOutbreak(void)
{
    TVShow *show;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSaveBlock1Ptr->outbreakPokemonSpecies = show->massOutbreak.species;
    gSaveBlock1Ptr->outbreakLocationMapNum = show->massOutbreak.locationMapNum;
    gSaveBlock1Ptr->outbreakLocationMapGroup = show->massOutbreak.locationMapGroup;
    gSaveBlock1Ptr->outbreakPokemonLevel = show->massOutbreak.level;
    gSaveBlock1Ptr->outbreakUnk1 = show->massOutbreak.var02;
    gSaveBlock1Ptr->outbreakUnk2 = show->massOutbreak.var0E;
    gSaveBlock1Ptr->outbreakPokemonMoves[0] = show->massOutbreak.moves[0];
    gSaveBlock1Ptr->outbreakPokemonMoves[1] = show->massOutbreak.moves[1];
    gSaveBlock1Ptr->outbreakPokemonMoves[2] = show->massOutbreak.moves[2];
    gSaveBlock1Ptr->outbreakPokemonMoves[3] = show->massOutbreak.moves[3];
    gSaveBlock1Ptr->outbreakUnk4 = show->massOutbreak.var03;
    gSaveBlock1Ptr->outbreakPokemonProbability = show->massOutbreak.probability;
    gSaveBlock1Ptr->outbreakDaysLeft = 2;
}

void PutLilycoveContestLadyShowOnTheAir(void)
{
    TVShow *show;

    sub_80EFA88();
    if (gSpecialVar_Result != TRUE)
    {
        show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
        sub_818E848(&show->contestLiveUpdates2.language);
        show->contestLiveUpdates2.pokemonNameLanguage = LANGUAGE_ENGLISH;
        show->contestLiveUpdates2.kind = TVSHOW_CONTEST_LIVE_UPDATES_2;
        show->contestLiveUpdates2.active = TRUE;
        sub_818E81C(show->contestLiveUpdates2.playerName);
        sub_818E7E0(&show->contestLiveUpdates2.contestCategory, show->contestLiveUpdates2.nickname);
        show->contestLiveUpdates2.pokeblockState = sub_818E880();
        tv_store_id_2x(show);
    }
}

static void InterviewAfter_FanClubLetter(void)
{
    TVShow *show;

    show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
    show->fanclubLetter.kind = TVSHOW_FAN_CLUB_LETTER;
    show->fanclubLetter.active = TRUE;
    StringCopy(show->fanclubLetter.playerName, gSaveBlock2Ptr->playerName);
    show->fanclubLetter.species = GetMonData(&gPlayerParty[GetLeadMonIndex()], MON_DATA_SPECIES, NULL);
    tv_store_id_2x(show);
    show->fanclubLetter.language = gGameLanguage;
}

static void InterviewAfter_RecentHappenings(void)
{
    TVShow *show;

    show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
    show->recentHappenings.kind = TVSHOW_RECENT_HAPPENINGS;
    show->recentHappenings.active = TRUE;
    StringCopy(show->recentHappenings.playerName, gSaveBlock2Ptr->playerName);
    show->recentHappenings.var02 = 0;
    tv_store_id_2x(show);
    show->recentHappenings.language = gGameLanguage;
}

static void InterviewAfter_PkmnFanClubOpinions(void)
{
    TVShow *show;

    show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
    show->fanclubOpinions.kind = TVSHOW_PKMN_FAN_CLUB_OPINIONS;
    show->fanclubOpinions.active = TRUE;
    show->fanclubOpinions.friendshipHighNybble = GetMonData(&gPlayerParty[GetLeadMonIndex()], MON_DATA_FRIENDSHIP, NULL) >> 4;
    show->fanclubOpinions.questionAsked = gSpecialVar_0x8007;
    StringCopy(show->fanclubOpinions.playerName, gSaveBlock2Ptr->playerName);
    GetMonData(&gPlayerParty[GetLeadMonIndex()], MON_DATA_NICKNAME, show->fanclubOpinions.nickname);
    StripExtCtrlCodes(show->fanclubOpinions.nickname);
    show->fanclubOpinions.species = GetMonData(&gPlayerParty[GetLeadMonIndex()], MON_DATA_SPECIES, NULL);
    tv_store_id_2x(show);
    show->fanclubOpinions.language = gGameLanguage;
    if (gGameLanguage == LANGUAGE_JAPANESE || GetMonData(&gPlayerParty[GetLeadMonIndex()], MON_DATA_LANGUAGE) == LANGUAGE_JAPANESE)
    {
        show->fanclubOpinions.pokemonNameLanguage = LANGUAGE_JAPANESE;
    }
    else
    {
        show->fanclubOpinions.pokemonNameLanguage = GetMonData(&gPlayerParty[GetLeadMonIndex()], MON_DATA_LANGUAGE);
    }
}

static void InterviewAfter_DummyShow4(void)
{
    TVShow *show;

    show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
}

static void sub_80ED718(void)
{
    u8 i;
    u16 outbreakIdx;
    TVShow *show;

    if (FlagGet(FLAG_SYS_GAME_CLEAR))
    {
        for (i = 0; i < 24; i ++)
        {
            if (gSaveBlock1Ptr->tvShows[i].common.kind == TVSHOW_MASS_OUTBREAK)
            {
                return;
            }
        }
        if (!rbernoulli(1, 200))
        {
            sCurTVShowSlot = FindEmptyTVSlotWithinFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
            if (sCurTVShowSlot != -1)
            {
                outbreakIdx = Random() % ARRAY_COUNT(sPokeOutbreakSpeciesList);
                show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
                show->massOutbreak.kind = TVSHOW_MASS_OUTBREAK;
                show->massOutbreak.active = TRUE;
                show->massOutbreak.level = sPokeOutbreakSpeciesList[outbreakIdx].level;
                show->massOutbreak.var02 = 0;
                show->massOutbreak.var03 = 0;
                show->massOutbreak.species = sPokeOutbreakSpeciesList[outbreakIdx].species;
                show->massOutbreak.var0E = 0;
                show->massOutbreak.moves[0] = sPokeOutbreakSpeciesList[outbreakIdx].moves[0];
                show->massOutbreak.moves[1] = sPokeOutbreakSpeciesList[outbreakIdx].moves[1];
                show->massOutbreak.moves[2] = sPokeOutbreakSpeciesList[outbreakIdx].moves[2];
                show->massOutbreak.moves[3] = sPokeOutbreakSpeciesList[outbreakIdx].moves[3];
                show->massOutbreak.locationMapNum = sPokeOutbreakSpeciesList[outbreakIdx].location;
                show->massOutbreak.locationMapGroup = 0;
                show->massOutbreak.var12 = 0;
                show->massOutbreak.probability = 50;
                show->massOutbreak.var15 = 0;
                show->massOutbreak.daysLeft = 1;
                tv_store_id_2x(show);
                show->massOutbreak.language = gGameLanguage;
            }
        }
    }
}

void EndMassOutbreak(void)
{
    gSaveBlock1Ptr->outbreakPokemonSpecies = SPECIES_NONE;
    gSaveBlock1Ptr->outbreakLocationMapNum = 0;
    gSaveBlock1Ptr->outbreakLocationMapGroup = 0;
    gSaveBlock1Ptr->outbreakPokemonLevel = 0;
    gSaveBlock1Ptr->outbreakUnk1 = 0;
    gSaveBlock1Ptr->outbreakUnk2 = 0;
    gSaveBlock1Ptr->outbreakPokemonMoves[0] = MOVE_NONE;
    gSaveBlock1Ptr->outbreakPokemonMoves[1] = MOVE_NONE;
    gSaveBlock1Ptr->outbreakPokemonMoves[2] = MOVE_NONE;
    gSaveBlock1Ptr->outbreakPokemonMoves[3] = MOVE_NONE;
    gSaveBlock1Ptr->outbreakUnk4 = 0;
    gSaveBlock1Ptr->outbreakPokemonProbability = 0;
    gSaveBlock1Ptr->outbreakDaysLeft = 0;
}

void UpdateTVShowsPerDay(u16 days)
{
    sub_80ED8B4(days);
    UpdateMassOutbreakTimeLeft(days);
    sub_80EF120(days);
    sub_80EDA48(days);
    sub_80EEB98(days);
}

static void sub_80ED8B4(u16 days)
{
    u8 i;
    TVShow *show;

    if (gSaveBlock1Ptr->outbreakPokemonSpecies == SPECIES_NONE)
    {
        for (i = 0; i < 24; i ++)
        {
            if (gSaveBlock1Ptr->tvShows[i].massOutbreak.kind == TVSHOW_MASS_OUTBREAK && gSaveBlock1Ptr->tvShows[i].massOutbreak.active == TRUE)
            {
                show = &gSaveBlock1Ptr->tvShows[i];
                if (show->massOutbreak.daysLeft < days)
                {
                    show->massOutbreak.daysLeft = 0;
                }
                else
                {
                    show->massOutbreak.daysLeft -= days;
                }
                break;
            }
        }
    }
}

void UpdateMassOutbreakTimeLeft(u16 days)
{
    if (gSaveBlock1Ptr->outbreakDaysLeft <= days)
    {
        EndMassOutbreak();
    }
    else
    {
        gSaveBlock1Ptr->outbreakDaysLeft -= days;
    }
}

void sub_80ED950(bool8 flag)
{
    if (flag)
    {
        if (sPokemonAnglerAttemptCounters >> 8 > 4)
        {
            PutFishingAdviceShowOnTheAir();
        }
        sPokemonAnglerAttemptCounters &= 0xFF;
        if (sPokemonAnglerAttemptCounters != 0xFF)
        {
            sPokemonAnglerAttemptCounters += 0x01;
        }
    }
    else
    {
        if ((u8)sPokemonAnglerAttemptCounters > 4)
        {
            PutFishingAdviceShowOnTheAir();
        }
        sPokemonAnglerAttemptCounters &= 0xFF00;
        if (sPokemonAnglerAttemptCounters >> 8 != 0xFF)
        {
            sPokemonAnglerAttemptCounters += 0x0100;
        }
    }
}

void PutFishingAdviceShowOnTheAir(void)
{
    TVShow *show;

    sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1 && HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_FISHING_ADVICE, FALSE) != TRUE)
    {
        show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
        show->pokemonAngler.kind = TVSHOW_FISHING_ADVICE;
        show->pokemonAngler.active = FALSE;
        show->pokemonAngler.nBites = sPokemonAnglerAttemptCounters;
        show->pokemonAngler.nFails = sPokemonAnglerAttemptCounters >> 8;
        show->pokemonAngler.species = sPokemonAnglerSpecies;
        StringCopy(show->pokemonAngler.playerName, gSaveBlock2Ptr->playerName);
        tv_store_id_3x(show);
        show->pokemonAngler.language = gGameLanguage;
    }
}

void SetPokemonAnglerSpecies(u16 species)
{
    sPokemonAnglerSpecies = species;
}

static void sub_80EDA48(u16 days)
{
    TVShow *show;

    show = &gSaveBlock1Ptr->tvShows[24];
    if (show->worldOfMasters.kind == TVSHOW_WORLD_OF_MASTERS)
    {
        if (show->worldOfMasters.numPokeCaught >= 20)
        {
            sub_80EDA80();
        }
        DeleteTVShowInArrayByIdx(gSaveBlock1Ptr->tvShows, 24);
    }
}

void sub_80EDA80(void)
{
    TVShow *show;
    TVShow *show2;

    show = &gSaveBlock1Ptr->tvShows[24];
    if (!rbernoulli(1, 1))
    {
        sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
        if (sCurTVShowSlot != -1 && HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_WORLD_OF_MASTERS, FALSE) != TRUE)
        {
            show2 = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
            show2->worldOfMasters.kind = TVSHOW_WORLD_OF_MASTERS;
            show2->worldOfMasters.active = FALSE;
            show2->worldOfMasters.numPokeCaught = show->worldOfMasters.numPokeCaught;
            show2->worldOfMasters.steps = GetGameStat(GAME_STAT_STEPS) - show->worldOfMasters.steps;
            show2->worldOfMasters.caughtPoke = show->worldOfMasters.caughtPoke;
            show2->worldOfMasters.species = show->worldOfMasters.species;
            show2->worldOfMasters.location = show->worldOfMasters.location;
            StringCopy(show2->worldOfMasters.playerName, gSaveBlock2Ptr->playerName);
            tv_store_id_3x(show2);
            show2->worldOfMasters.language = gGameLanguage;
            DeleteTVShowInArrayByIdx(gSaveBlock1Ptr->tvShows, 24);
        }
    }
}

void sub_80EDB44(void)
{
    TVShow *show;
    u32 i;
    u8 nBadges;

    HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_TODAYS_RIVAL_TRAINER, TRUE);
    sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1)
    {
        show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
        show->rivalTrainer.kind = TVSHOW_TODAYS_RIVAL_TRAINER;
        show->rivalTrainer.active = FALSE;
        for (i = FLAG_BADGE01_GET, nBadges = 0; i < FLAG_BADGE01_GET + 8; i ++)
        {
            if (FlagGet(i))
            {
                nBadges ++;
            }
        }
        show->rivalTrainer.badgeCount = nBadges;
        if (IsNationalPokedexEnabled())
        {
            show->rivalTrainer.dexCount = GetNationalPokedexCount(0x01);
        }
        else
        {
            show->rivalTrainer.dexCount = GetHoennPokedexCount(0x01);
        }
        show->rivalTrainer.location = gMapHeader.regionMapSectionId;
        show->rivalTrainer.mapLayoutId = gMapHeader.mapLayoutId;
        show->rivalTrainer.nSilverSymbols = 0;
        show->rivalTrainer.nGoldSymbols = 0;
        for (i = 0; i < 7; i ++)
        {
            if (FlagGet(sSilverSymbolFlags[i]) == TRUE)
            {
                show->rivalTrainer.nSilverSymbols ++;
            }
            if (FlagGet(sGoldSymbolFlags[i]) == TRUE)
            {
                show->rivalTrainer.nGoldSymbols ++;
            }
        }
        show->rivalTrainer.battlePoints = gSaveBlock2Ptr->frontier.frontierBattlePoints;
        StringCopy(show->rivalTrainer.playerName, gSaveBlock2Ptr->playerName);
        tv_store_id_3x(show);
        show->rivalTrainer.language = gGameLanguage;
    }
}

void sub_80EDC60(const u16 *words)
{
    TVShow *show;

    sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1 && HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_TREND_WATCHER, FALSE) != TRUE)
    {
        show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
        show->trendWatcher.kind = TVSHOW_TREND_WATCHER;
        show->trendWatcher.active = FALSE;
        show->trendWatcher.gender = gSaveBlock2Ptr->playerGender;
        show->trendWatcher.words[0] = words[0];
        show->trendWatcher.words[1] = words[1];
        StringCopy(show->trendWatcher.playerName, gSaveBlock2Ptr->playerName);
        tv_store_id_3x(show);
        show->trendWatcher.language = gGameLanguage;
    }
}

void sub_80EDCE8(void)
{
    TVShow *show;

    sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1 && HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_TREASURE_INVESTIGATORS, FALSE) != TRUE)
    {
        show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
        show->treasureInvestigators.kind = TVSHOW_TREASURE_INVESTIGATORS;
        show->treasureInvestigators.active = FALSE;
        show->treasureInvestigators.item = gSpecialVar_0x8005;
        show->treasureInvestigators.location = gMapHeader.regionMapSectionId;
        show->treasureInvestigators.mapLayoutId = gMapHeader.mapLayoutId;
        StringCopy(show->treasureInvestigators.playerName, gSaveBlock2Ptr->playerName);
        tv_store_id_3x(show);
        show->treasureInvestigators.language = gGameLanguage;
    }
}

void sub_80EDD78(u16 nCoinsPaidOut)
{
    TVShow *show;
    bool8 flag;
    u16 nCoinsWon;

    sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1 && HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_FIND_THAT_GAMER, FALSE) != TRUE)
    {
        flag = FALSE;
        switch (sFindThatGamerWhichGame)
        {
            case FALSE:
                if (nCoinsPaidOut >= sFindThatGamerCoinsSpent + 200)
                {
                    flag = TRUE;
                    nCoinsWon = nCoinsPaidOut - sFindThatGamerCoinsSpent;
                    break;
                }
                if (sFindThatGamerCoinsSpent >= 100 && nCoinsPaidOut <= sFindThatGamerCoinsSpent - 100)
                {
                    nCoinsWon = sFindThatGamerCoinsSpent - nCoinsPaidOut;
                    break;
                }
                return;
            case TRUE:
                if (nCoinsPaidOut >= sFindThatGamerCoinsSpent + 50)
                {
                    flag = TRUE;
                    nCoinsWon = nCoinsPaidOut - sFindThatGamerCoinsSpent;
                    break;
                }
                if (sFindThatGamerCoinsSpent >= 50 && nCoinsPaidOut <= sFindThatGamerCoinsSpent - 50)
                {
                    nCoinsWon = sFindThatGamerCoinsSpent - nCoinsPaidOut;
                    break;
                }
                return;
            default:
                return;
        }
        show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
        show->findThatGamer.kind = TVSHOW_FIND_THAT_GAMER;
        show->findThatGamer.active = FALSE;
        show->findThatGamer.nCoins = nCoinsWon;
        show->findThatGamer.whichGame = sFindThatGamerWhichGame;
        show->findThatGamer.won = flag;
        StringCopy(show->findThatGamer.playerName, gSaveBlock2Ptr->playerName);
        tv_store_id_3x(show);
        show->findThatGamer.language = gGameLanguage;
    }
}

void sub_80EDE70(u16 nCoinsSpent)
{
    sFindThatGamerWhichGame = FALSE;
    sFindThatGamerCoinsSpent = nCoinsSpent;
}

void sub_80EDE84(u16 nCoinsSpent)
{
    sFindThatGamerWhichGame = TRUE;
    sFindThatGamerCoinsSpent = nCoinsSpent;
}

static void sub_80EDE98(TVShow *show)
{
    u8 i;
    u8 j;
    u16 k;
    u8 n;
    u8 deco;
    u8 x;

    for (i = 0; i < 16; i ++)
    {
        sTV_DecorationsBuffer[i] = 0;
    }
    for (i = 0, n = 0; i < 16; i ++)
    {
        deco = gSaveBlock1Ptr->secretBases[0].decorations[i];
        if (deco)
        {
            for (j = 0; j < 16; j ++)
            {
                if (sTV_DecorationsBuffer[j] == 0)
                {
                    sTV_DecorationsBuffer[j] = deco;
                    n ++;
                    break;
                }
                if (sTV_DecorationsBuffer[j] == deco)
                {
                    break;
                }
            }
        }
    }
    if (n > 4)
    {
        show->secretBaseVisit.nDecorations = 4;
    }
    else
    {
        show->secretBaseVisit.nDecorations = n;
    }
    switch (show->secretBaseVisit.nDecorations)
    {
        case 0:
            break;
        case 1:
            show->secretBaseVisit.decorations[0] = sTV_DecorationsBuffer[0];
            break;
        default:
            for (k = 0; k < n * n; k ++)
            {
                deco = Random() % n;
                j = Random() % n;
                i = sTV_DecorationsBuffer[deco];
                sTV_DecorationsBuffer[deco] = sTV_DecorationsBuffer[j];
                sTV_DecorationsBuffer[j] = i;
            }
            for (i = 0; i < show->secretBaseVisit.nDecorations; i ++)
            {
                show->secretBaseVisit.decorations[i] = sTV_DecorationsBuffer[i];
            }
            break;
    }
}

static void sub_80EDFB4(TVShow *show)
{
    u8 i;
    u16 move;
    u16 j;
    u8 nMoves;
    u8 nPokemon;
    u16 sum;

    for (i = 0, nPokemon = 0; i < PARTY_SIZE; i ++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) != SPECIES_NONE && !GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG))
        {
            sTV_SecretBaseVisitMonsTemp[nPokemon].level = GetMonData(&gPlayerParty[i], MON_DATA_LEVEL);
            sTV_SecretBaseVisitMonsTemp[nPokemon].species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES);
            nMoves = 0;
            move = GetMonData(&gPlayerParty[i], MON_DATA_MOVE1);
            if (move != MOVE_NONE)
            {
                sTV_SecretBaseVisitMovesTemp[nMoves] = move;
                nMoves ++;
            }
            move = GetMonData(&gPlayerParty[i], MON_DATA_MOVE2);
            if (move != MOVE_NONE)
            {
                sTV_SecretBaseVisitMovesTemp[nMoves] = move;
                nMoves ++;
            }
            move = GetMonData(&gPlayerParty[i], MON_DATA_MOVE3);
            if (move != MOVE_NONE)
            {
                sTV_SecretBaseVisitMovesTemp[nMoves] = move;
                nMoves ++;
            }
            move = GetMonData(&gPlayerParty[i], MON_DATA_MOVE4);
            if (move != MOVE_NONE)
            {
                sTV_SecretBaseVisitMovesTemp[nMoves] = move;
                nMoves ++;
            }
            sTV_SecretBaseVisitMonsTemp[nPokemon].move = sTV_SecretBaseVisitMovesTemp[Random() % nMoves];
            nPokemon ++;
        }
    }
    for (i = 0, sum = 0; i < nPokemon; i ++)
    {
        sum += sTV_SecretBaseVisitMonsTemp[i].level;
    }
    show->secretBaseVisit.avgLevel = sum / nPokemon;
    j = Random() % nPokemon;
    show->secretBaseVisit.species = sTV_SecretBaseVisitMonsTemp[j].species;
    show->secretBaseVisit.move = sTV_SecretBaseVisitMonsTemp[j].move;
}

void TV_PutSecretBaseVisitOnTheAir(void)
{
    TVShow *show;

    HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_SECRET_BASE_VISIT, TRUE);
    sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1)
    {
        show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
        show->secretBaseVisit.kind = TVSHOW_SECRET_BASE_VISIT;
        show->secretBaseVisit.active = FALSE;
        StringCopy(show->secretBaseVisit.playerName, gSaveBlock2Ptr->playerName);
        sub_80EDE98(show);
        sub_80EDFB4(show);
        tv_store_id_3x(show);
        show->secretBaseVisit.language = gGameLanguage;
    }
}

void sub_80EE184(void)
{
    TVShow *show;
    u8 i;
    u16 balls;

    sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1 && HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_BREAKING_NEWS, FALSE) != TRUE)
    {
        show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
        show->breakingNews.kind = TVSHOW_BREAKING_NEWS;
        show->breakingNews.active = FALSE;
        balls = 0;
        for (i = 0; i < 11; i ++)
        {
            balls += gBattleResults.catchAttempts[i];
        }
        if (gBattleResults.usedMasterBall)
        {
            balls ++;
        }
        show->breakingNews.location = gMapHeader.regionMapSectionId;
        StringCopy(show->breakingNews.playerName, gSaveBlock2Ptr->playerName);
        show->breakingNews.poke1Species = gBattleResults.playerMon1Species;
        switch (gBattleOutcome)
        {
            case B_OUTCOME_LOST:
            case B_OUTCOME_DREW:
                show->breakingNews.kind = TVSHOW_OFF_AIR;
                return;
            case B_OUTCOME_CAUGHT:
                show->breakingNews.outcome = 0;
                break;
            case B_OUTCOME_WON:
                show->breakingNews.outcome = 1;
                break;
            case B_OUTCOME_RAN:
            case B_OUTCOME_PLAYER_TELEPORTED:
            case B_OUTCOME_NO_SAFARI_BALLS:
                show->breakingNews.outcome = 2;
                break;
            case B_OUTCOME_MON_FLED:
            case B_OUTCOME_MON_TELEPORTED:
                show->breakingNews.outcome = 3;
                break;
        }
        show->breakingNews.lastOpponentSpecies = gBattleResults.lastOpponentSpecies;
        switch (show->breakingNews.outcome)
        {
            case 0:
                if (gBattleResults.usedMasterBall)
                {
                    show->breakingNews.caughtMonBall = ITEM_MASTER_BALL;
                }
                else
                {
                    show->breakingNews.caughtMonBall = gBattleResults.caughtMonBall;
                }
                show->breakingNews.balls = balls;
                break;
            case 1:
                show->breakingNews.lastUsedMove = gBattleResults.lastUsedMovePlayer;
                break;
            case 2:
                break;
            case 3:
                break;
        }
        tv_store_id_3x(show);
        show->breakingNews.language = gGameLanguage;
    }
}

void sub_80EE2CC(void)
{
    TVShow *show;

    sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1 && HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_LOTTO_WINNER, FALSE) != TRUE)
    {
        show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
        show->lottoWinner.kind = TVSHOW_LOTTO_WINNER;
        show->lottoWinner.active = FALSE;
        StringCopy(show->lottoWinner.playerName, gSaveBlock2Ptr->playerName);
        show->lottoWinner.whichPrize = 4 - gSpecialVar_0x8004;
        show->lottoWinner.item = gSpecialVar_0x8005;
        tv_store_id_3x(show);
        show->lottoWinner.language = gGameLanguage;
    }
}

void sub_80EE35C(u16 foeSpecies, u16 species, u8 moveIdx, const u16 *movePtr, u16 betterMove)
{
    TVShow *show;
    u8 i;
    u8 j;

    sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1 && HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_BATTLE_SEMINAR, FALSE) != TRUE)
    {
        show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
        show->battleSeminar.kind = TVSHOW_BATTLE_SEMINAR;
        show->battleSeminar.active = FALSE;
        StringCopy(show->battleSeminar.playerName, gSaveBlock2Ptr->playerName);
        show->battleSeminar.foeSpecies = foeSpecies;
        show->battleSeminar.species = species;
        show->battleSeminar.move = movePtr[moveIdx];
        for (i = 0, j = 0; i < 4; i ++)
        {
            if (i != moveIdx && movePtr[i])
            {
                show->battleSeminar.otherMoves[j] = movePtr[i];
                j ++;
            }
        }
        show->battleSeminar.nOtherMoves = j;
        show->battleSeminar.betterMove = betterMove;
        tv_store_id_3x(show);
        show->battleSeminar.language = gGameLanguage;
    }
}

void sub_80EE44C(u8 nMonsCaught, u8 nPkblkUsed)
{
    TVShow *show;

    sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1 && HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_SAFARI_FAN_CLUB, FALSE) != TRUE)
    {
        show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
        show->safariFanClub.kind = TVSHOW_SAFARI_FAN_CLUB;
        show->safariFanClub.active = FALSE;
        StringCopy(show->safariFanClub.playerName, gSaveBlock2Ptr->playerName);
        show->safariFanClub.nMonsCaught = nMonsCaught;
        show->safariFanClub.nPkblkUsed = nPkblkUsed;
        tv_store_id_3x(show);
        show->safariFanClub.language = gGameLanguage;
    }
}

void sub_80EE4DC(struct Pokemon *pokemon, u8 ribbonMonDataIdx)
{
    TVShow *show;

    sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1 && HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_CUTIES, FALSE) != TRUE)
    {
        show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
        show->cuties.kind = TVSHOW_CUTIES;
        show->cuties.active = FALSE;
        StringCopy(show->cuties.playerName, gSaveBlock2Ptr->playerName);
        GetMonData(pokemon, MON_DATA_NICKNAME, show->cuties.nickname);
        StripExtCtrlCodes(show->cuties.nickname);
        show->cuties.nRibbons = GetRibbonCount(pokemon);
        show->cuties.selectedRibbon = TV_MonDataIdxToRibbon(ribbonMonDataIdx);
        tv_store_id_3x(show);
        show->cuties.language = gGameLanguage;
        if (show->cuties.language == LANGUAGE_JAPANESE || GetMonData(pokemon, MON_DATA_LANGUAGE) == LANGUAGE_JAPANESE)
        {
            show->cuties.pokemonNameLanguage = LANGUAGE_JAPANESE;
        }
        else
        {
            show->cuties.pokemonNameLanguage = GetMonData(pokemon, MON_DATA_LANGUAGE);
        }
    }
}

u8 GetRibbonCount(struct Pokemon *pokemon)
{
    u8 nRibbons;

    nRibbons = 0;
    nRibbons += GetMonData(pokemon, MON_DATA_COOL_RIBBON);
    nRibbons += GetMonData(pokemon, MON_DATA_BEAUTY_RIBBON);
    nRibbons += GetMonData(pokemon, MON_DATA_CUTE_RIBBON);
    nRibbons += GetMonData(pokemon, MON_DATA_SMART_RIBBON);
    nRibbons += GetMonData(pokemon, MON_DATA_TOUGH_RIBBON);
    nRibbons += GetMonData(pokemon, MON_DATA_CHAMPION_RIBBON);
    nRibbons += GetMonData(pokemon, MON_DATA_WINNING_RIBBON);
    nRibbons += GetMonData(pokemon, MON_DATA_VICTORY_RIBBON);
    nRibbons += GetMonData(pokemon, MON_DATA_ARTIST_RIBBON);
    nRibbons += GetMonData(pokemon, MON_DATA_EFFORT_RIBBON);
    nRibbons += GetMonData(pokemon, MON_DATA_GIFT_RIBBON_1);
    nRibbons += GetMonData(pokemon, MON_DATA_GIFT_RIBBON_2);
    nRibbons += GetMonData(pokemon, MON_DATA_GIFT_RIBBON_3);
    nRibbons += GetMonData(pokemon, MON_DATA_GIFT_RIBBON_4);
    nRibbons += GetMonData(pokemon, MON_DATA_GIFT_RIBBON_5);
    nRibbons += GetMonData(pokemon, MON_DATA_GIFT_RIBBON_6);
    nRibbons += GetMonData(pokemon, MON_DATA_GIFT_RIBBON_7);
    return nRibbons;
}

u8 TV_MonDataIdxToRibbon(u8 monDataIdx)
{
    if (monDataIdx == MON_DATA_CHAMPION_RIBBON) return  0;
    if (monDataIdx == MON_DATA_COOL_RIBBON)     return  1;
    if (monDataIdx == MON_DATA_BEAUTY_RIBBON)   return  5;
    if (monDataIdx == MON_DATA_CUTE_RIBBON)     return  9;
    if (monDataIdx == MON_DATA_SMART_RIBBON)    return 13;
    if (monDataIdx == MON_DATA_TOUGH_RIBBON)    return 17;
    if (monDataIdx == MON_DATA_WINNING_RIBBON)  return 21;
    if (monDataIdx == MON_DATA_VICTORY_RIBBON)  return 22;
    if (monDataIdx == MON_DATA_ARTIST_RIBBON)   return 23;
    if (monDataIdx == MON_DATA_EFFORT_RIBBON)   return 24;
    if (monDataIdx == MON_DATA_GIFT_RIBBON_1)   return 25;
    if (monDataIdx == MON_DATA_GIFT_RIBBON_2)   return 26;
    if (monDataIdx == MON_DATA_GIFT_RIBBON_3)   return 27;
    if (monDataIdx == MON_DATA_GIFT_RIBBON_4)   return 28;
    if (monDataIdx == MON_DATA_GIFT_RIBBON_5)   return 29;
    if (monDataIdx == MON_DATA_GIFT_RIBBON_6)   return 30;
    if (monDataIdx == MON_DATA_GIFT_RIBBON_7)   return 31;
    return 0;
}

void sub_80EE72C(void)
{
    TVShow *show;

    sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1 && HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_TRAINER_FAN_CLUB, FALSE) != TRUE)
    {
        show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
        show->trainerFanClub.kind = TVSHOW_TRAINER_FAN_CLUB;
        show->trainerFanClub.active = FALSE;
        StringCopy(show->trainerFanClub.playerName, gSaveBlock2Ptr->playerName);
        show->trainerFanClub.words[0] = gSaveBlock1Ptr->unk2BB0[0];
        show->trainerFanClub.words[1] = gSaveBlock1Ptr->unk2BB0[1];
        tv_store_id_3x(show);
        show->trainerFanClub.language = gGameLanguage;
    }
}

bool8 sub_80EE7C0(void)
{
    sCurTVShowSlot = FindEmptyTVSlotWithinFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot == -1)
    {
        return TRUE;
    }
    FindActiveBroadcastByShowType_SetScriptResult(TVSHOW_FAN_CLUB_SPECIAL);
    if (gSpecialVar_Result == TRUE)
    {
        return TRUE;
    }
    if (gSaveBlock1Ptr->linkBattleRecords.entries[0].name[0] == EOS)
    {
        return TRUE;
    }
    return FALSE;
}

bool8 sub_80EE818(void)
{
    u32 playerId;
    u8 showIdx;
    TVShow *shows;

    if (HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_FRONTIER, FALSE) == TRUE)
    {
        shows = gSaveBlock1Ptr->tvShows;
        playerId = GetPlayerIDAsU32();
        for (showIdx = 5; showIdx < 24; showIdx ++)
        {
            if (shows[showIdx].common.kind == TVSHOW_FRONTIER && (playerId & 0xFF) == shows[showIdx].common.trainerIdLo && ((playerId >> 8) & 0xFF) == shows[showIdx].common.trainerIdHi)
            {
                DeleteTVShowInArrayByIdx(gSaveBlock1Ptr->tvShows, showIdx);
                sub_80EF93C(gSaveBlock1Ptr->tvShows);
                return TRUE;
            }
        }
    }
    sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot == -1)
    {
        return FALSE;
    }
    return TRUE;
}

void sub_80EE8C8(u16 winStreak, u8 facility)
{
    TVShow *show;

    sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1)
    {
        show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
        show->frontier.kind = TVSHOW_FRONTIER;
        show->frontier.active = FALSE;
        StringCopy(show->frontier.playerName, gSaveBlock2Ptr->playerName);
        show->frontier.winStreak = winStreak;
        show->frontier.facility = facility;
        switch (facility)
        {
            case  1:
            case  5:
            case  6:
            case  7:
            case  8:
            case  9:
            case 10:
            case 11:
            case 12:
            case 13:
                show->frontier.species1 = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES, NULL);
                show->frontier.species2 = GetMonData(&gPlayerParty[1], MON_DATA_SPECIES, NULL);
                show->frontier.species3 = GetMonData(&gPlayerParty[2], MON_DATA_SPECIES, NULL);
                break;
            case 2:
                show->frontier.species1 = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES, NULL);
                show->frontier.species2 = GetMonData(&gPlayerParty[1], MON_DATA_SPECIES, NULL);
                show->frontier.species3 = GetMonData(&gPlayerParty[2], MON_DATA_SPECIES, NULL);
                show->frontier.species4 = GetMonData(&gPlayerParty[3], MON_DATA_SPECIES, NULL);
                break;
            case 3:
                show->frontier.species1 = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES, NULL);
                show->frontier.species2 = GetMonData(&gPlayerParty[1], MON_DATA_SPECIES, NULL);
                break;
            case 4:
                show->frontier.species1 = GetMonData(&gSaveBlock1Ptr->playerParty[gSaveBlock2Ptr->frontier.field_CAA[0] - 1], MON_DATA_SPECIES, NULL);
                show->frontier.species2 = GetMonData(&gSaveBlock1Ptr->playerParty[gSaveBlock2Ptr->frontier.field_CAA[1] - 1], MON_DATA_SPECIES, NULL);
                break;
        }
        tv_store_id_3x(show);
        show->frontier.language = gGameLanguage;
    }
}

void sub_80EEA70(void)
{
    TVShow *show;
    u8 strbuf[32];

    if (HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_SECRET_BASE_SECRETS, FALSE) != TRUE)
    {
        sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
        if (sCurTVShowSlot != -1)
        {
            show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
            show->secretBaseSecrets.kind = TVSHOW_SECRET_BASE_SECRETS;
            show->secretBaseSecrets.active = FALSE;
            StringCopy(show->secretBaseSecrets.playerName, gSaveBlock2Ptr->playerName);
            show->secretBaseSecrets.stepsInBase = VarGet(0x40ec);
            sub_80E980C();
            StringCopy(strbuf, gStringVar1);
            StripExtCtrlCodes(strbuf);
            StringCopy(show->secretBaseSecrets.baseOwnersName, strbuf);
            show->secretBaseSecrets.item = VarGet(0x40ed);
            show->secretBaseSecrets.flags = VarGet(0x40ee) + (VarGet(0x40ef) << 16);
            tv_store_id_3x(show);
            show->secretBaseSecrets.language = gGameLanguage;
            if (show->secretBaseSecrets.language == LANGUAGE_JAPANESE || gSaveBlock1Ptr->secretBases[VarGet(VAR_0x4054)].language == LANGUAGE_JAPANESE)
            {
                show->secretBaseSecrets.baseOwnersNameLanguage = LANGUAGE_JAPANESE;
            }
            else
            {
                show->secretBaseSecrets.baseOwnersNameLanguage = gSaveBlock1Ptr->secretBases[VarGet(VAR_0x4054)].language;
            }
        }
    }
}

static void sub_80EEB98(u16 days)
{
    u8 i;

    for (i = 0; i < ARRAY_COUNT(sNumberOneVarsAndThresholds); i ++)
    {
        if (VarGet(sNumberOneVarsAndThresholds[i][0]) >= sNumberOneVarsAndThresholds[i][1])
        {
            sub_80EEBF4(i);
            break;
        }
    }
    for (i = 0; i < ARRAY_COUNT(sNumberOneVarsAndThresholds); i ++)
    {
        VarSet(sNumberOneVarsAndThresholds[i][0], 0);
    }
}

static void sub_80EEBF4(u8 actionIdx)
{
    TVShow *show;

    HasMixableShowAlreadyBeenSpawnedWithPlayerID(TVSHOW_NUMBER_ONE, TRUE);
    sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    if (sCurTVShowSlot != -1)
    {
        show = &gSaveBlock1Ptr->tvShows[sCurTVShowSlot];
        show->numberOne.kind = TVSHOW_NUMBER_ONE;
        show->numberOne.active = FALSE;
        StringCopy(show->numberOne.playerName, gSaveBlock2Ptr->playerName);
        show->numberOne.actionIdx = actionIdx;
        show->numberOne.count = VarGet(sNumberOneVarsAndThresholds[actionIdx][0]);
        tv_store_id_3x(show);
        show->numberOne.language = gGameLanguage;
    }
}

void sub_80EEC80(void)
{
    VarSet(VAR_DAILY_SLOTS, VarGet(VAR_DAILY_SLOTS) + 1);
}

void sub_80EECA4(void)
{
    VarSet(VAR_DAILY_ROULETTE, VarGet(VAR_DAILY_ROULETTE) + 1);
}

void sub_80EECC8(void)
{
    VarSet(VAR_DAILY_WILDS, VarGet(VAR_DAILY_WILDS) + 1);
}

void sub_80EECEC(void)
{
    VarSet(VAR_DAILY_BLENDER, VarGet(VAR_DAILY_BLENDER) + 1);
}

void sub_80EED10(void)
{
    VarSet(VAR_DAILY_PLANTED_BERRIES, VarGet(VAR_DAILY_PLANTED_BERRIES) + 1);
}

void sub_80EED34(void)
{
    VarSet(VAR_DAILY_PICKED_BERRIES, VarGet(VAR_DAILY_PICKED_BERRIES) + gSpecialVar_0x8006);
}

void sub_80EED60(u16 delta)
{
    VarSet(VAR_DAILY_BP, VarGet(VAR_DAILY_BP) + delta);
}

// PokeNews

static void sub_80EED88(void)
{
    u8 newsKind;

    if (FlagGet(FLAG_SYS_GAME_CLEAR))
    {
        sCurTVShowSlot = sub_80EEE30(gSaveBlock1Ptr->pokeNews);
        if (sCurTVShowSlot != -1 && rbernoulli(1, 100) != TRUE)
        {
            newsKind = (Random() % 4) + POKENEWS_SLATEPORT;
            if (sub_80EF0E4(newsKind) != TRUE)
            {
                gSaveBlock1Ptr->pokeNews[sCurTVShowSlot].kind = newsKind;
                gSaveBlock1Ptr->pokeNews[sCurTVShowSlot].days = 4;
                gSaveBlock1Ptr->pokeNews[sCurTVShowSlot].state = TRUE;
            }
        }
    }
}

s8 sub_80EEE30(PokeNews *pokeNews)
{
    s8 i;

    for (i = 0; i < 16; i ++)
    {
        if (pokeNews[i].kind == 0)
        {
            return i;
        }
    }
    return -1;
}

void ClearPokemonNews(void)
{
    u8 i;

    for (i = 0; i < 16; i ++)
    {
        ClearPokemonNewsI(i);
    }
}

void ClearPokemonNewsI(u8 i)
{
    gSaveBlock1Ptr->pokeNews[i].kind = POKENEWS_NONE;
    gSaveBlock1Ptr->pokeNews[i].state = FALSE;
    gSaveBlock1Ptr->pokeNews[i].days = 0;
}

static void sub_80EEEB8(void)
{
    u8 i;
    u8 j;

    for (i = 0; i < 15; i ++)
    {
        if (gSaveBlock1Ptr->pokeNews[i].kind == POKENEWS_NONE)
        {
            for (j = i + 1; j < 16; j ++)
            {
                if (gSaveBlock1Ptr->pokeNews[j].kind != POKENEWS_NONE)
                {
                    gSaveBlock1Ptr->pokeNews[i] = gSaveBlock1Ptr->pokeNews[j];
                    ClearPokemonNewsI(j);
                    break;
                }
            }
        }
    }
}

u8 FindAnyTVNewsOnTheAir(void)
{
    u8 i;

    for (i = 0; i < 16; i ++)
    {
        if (gSaveBlock1Ptr->pokeNews[i].kind != POKENEWS_NONE && gSaveBlock1Ptr->pokeNews[i].state == TRUE && gSaveBlock1Ptr->pokeNews[i].days < 3)
        {
            return i;
        }
    }
    return -1;
}

void DoPokeNews(void)
{
    u8 i;
    u16 n;

    i = FindAnyTVNewsOnTheAir();
    if (i == 0xFF)
    {
        gSpecialVar_Result = FALSE;
    }
    else
    {
        if (gSaveBlock1Ptr->pokeNews[i].days == 0)
        {
            gSaveBlock1Ptr->pokeNews[i].state = 2;
            if (gLocalTime.hours < 20)
            {
                ShowFieldMessage(sPokeNewsTextGroup_Ongoing[gSaveBlock1Ptr->pokeNews[i].kind]);
            }
            else
            {
                ShowFieldMessage(sPokeNewsTextGroup_Ending[gSaveBlock1Ptr->pokeNews[i].kind]);
            }
        }
        else
        {
            n = gSaveBlock1Ptr->pokeNews[i].days;
            ConvertIntToDecimalStringN(gStringVar1, n, STR_CONV_MODE_LEFT_ALIGN, 1);
            gSaveBlock1Ptr->pokeNews[i].state = 0;
            ShowFieldMessage(sPokeNewsTextGroup_Upcoming[gSaveBlock1Ptr->pokeNews[i].kind]);
        }
        gSpecialVar_Result = TRUE;
    }
}

bool8 GetPriceReduction(u8 newsKind)
{
    u8 i;

    if (newsKind == 0)
    {
        return FALSE;
    }
    for (i = 0; i < 16; i ++)
    {
        if (gSaveBlock1Ptr->pokeNews[i].kind == newsKind)
        {
            if (gSaveBlock1Ptr->pokeNews[i].state == 2 && IsPriceDiscounted(newsKind))
            {
                return TRUE;
            }
            return FALSE;
        }
    }
    return FALSE;
}

bool8 IsPriceDiscounted(u8 newsKind)
{
    switch (newsKind)
    {
        case POKENEWS_SLATEPORT:
            if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(SLATEPORT_CITY) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(SLATEPORT_CITY) && gSpecialVar_LastTalked == 25)
            {
                return TRUE;
            }
            return FALSE;
        case POKENEWS_LILYCOVE:
            if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(LILYCOVE_CITY_DEPARTMENT_STORE_ROOFTOP) && gSaveBlock1Ptr->location.mapNum == MAP_NUM(LILYCOVE_CITY_DEPARTMENT_STORE_ROOFTOP))
            {
                return TRUE;
            }
            return FALSE;
    }
    return TRUE;
}

bool8 sub_80EF0E4(u8 newsKind)
{
    u8 i;
    if (newsKind == POKENEWS_NONE)
    {
        return TRUE;
    }
    for (i = 0; i < 16; i ++)
    {
        if (gSaveBlock1Ptr->pokeNews[i].kind == newsKind)
        {
            return TRUE;
        }
    }
    return FALSE;
}

static void sub_80EF120(u16 days)
{
    u8 i;

    for (i = 0; i < 16; i ++)
    {
        if (gSaveBlock1Ptr->pokeNews[i].kind != POKENEWS_NONE)
        {
            if (gSaveBlock1Ptr->pokeNews[i].days < days)
            {
                ClearPokemonNewsI(i);
            }
            else
            {
                if (gSaveBlock1Ptr->pokeNews[i].state == 0 && FlagGet(FLAG_SYS_GAME_CLEAR) == TRUE)
                {
                    gSaveBlock1Ptr->pokeNews[i].state = 1;
                }
                gSaveBlock1Ptr->pokeNews[i].days -= days;
            }
        }
    }
    sub_80EEEB8();
}

void CopyContestRankToStringVar(u8 varIdx, u8 rank)
{
    switch (rank)
    {
        case 0: // NORMAL
            StringCopy(gTVStringVarPtrs[varIdx], gUnknown_0858BAF0[5]);
            break;
        case 1: // SUPER
            StringCopy(gTVStringVarPtrs[varIdx], gUnknown_0858BAF0[6]);
            break;
        case 2: // HYPER
            StringCopy(gTVStringVarPtrs[varIdx], gUnknown_0858BAF0[7]);
            break;
        case 3: // MASTER
            StringCopy(gTVStringVarPtrs[varIdx], gUnknown_0858BAF0[8]);
            break;
    }
}

void CopyContestCategoryToStringVar(u8 varIdx, u8 category)
{
    switch (category)
    {
        case 0: // COOL
            StringCopy(gTVStringVarPtrs[varIdx], gUnknown_0858BAF0[0]);
            break;
        case 1: // BEAUTY
            StringCopy(gTVStringVarPtrs[varIdx], gUnknown_0858BAF0[1]);
            break;
        case 2: // CUTE
            StringCopy(gTVStringVarPtrs[varIdx], gUnknown_0858BAF0[2]);
            break;
        case 3: // SMART
            StringCopy(gTVStringVarPtrs[varIdx], gUnknown_0858BAF0[3]);
            break;
        case 4: // TOUGH
            StringCopy(gTVStringVarPtrs[varIdx], gUnknown_0858BAF0[4]);
            break;
    }
}

void SetContestCategoryStringVarForInterview(void)
{
    TVShow *show;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    CopyContestCategoryToStringVar(1, show->bravoTrainer.contestCategory);
}

void TV_PrintIntToStringVar(u8 varIdx, int value)
{
    int nDigits;

    nDigits = CountDigits(value);
    ConvertIntToDecimalStringN(gTVStringVarPtrs[varIdx], value, STR_CONV_MODE_LEFT_ALIGN, nDigits);
}

size_t CountDigits(int value)
{
    if (value / 10 == 0)        return 1;
    if (value / 100 == 0)       return 2;
    if (value / 1000 == 0)      return 3;
    if (value / 10000 == 0)     return 4;
    if (value / 100000 == 0)    return 5;
    if (value / 1000000 == 0)   return 6;
    if (value / 10000000 == 0)  return 7;
    if (value / 100000000 == 0) return 8;

    return 1;
}

static void sub_80EF40C(u8 varIdx, TVShow *show)
{
    u8 i;
    int price;

    price = 0;
    for (i = 0; i < 3; i ++)
    {
        if (show->smartshopperShow.itemIds[i] != ITEM_NONE)
        {
            price += ItemId_GetPrice(show->smartshopperShow.itemIds[i]) * show->smartshopperShow.itemAmounts[i];
        }
    }
    if (show->smartshopperShow.priceReduced == TRUE)
    {
        TV_PrintIntToStringVar(varIdx, price >> 1);
    }
    else
    {
        TV_PrintIntToStringVar(varIdx, price);
    }
}

bool8 HasMixableShowAlreadyBeenSpawnedWithPlayerID(u8 kind, bool8 flag)
{
    u32 playerId;
    TVShow *shows;
    u8 i;

    shows = gSaveBlock1Ptr->tvShows;
    playerId = GetPlayerIDAsU32();
    for (i = 5; i < 24; i ++)
    {
        if (shows[i].common.kind == kind && (playerId & 0xFF) == shows[i].common.trainerIdLo && ((playerId >> 8) & 0xFF) == shows[i].common.trainerIdHi)
        {
            if (flag == TRUE)
            {
                DeleteTVShowInArrayByIdx(gSaveBlock1Ptr->tvShows, i);
                sub_80EF93C(gSaveBlock1Ptr->tvShows);
            }
            return TRUE;
        }
    }
    return FALSE;
}

void TV_SortPurchasesByQuantity(void)
{
    u8 i;
    u8 j;
    u16 tmpId;
    u16 tmpQn;

    for (i = 0; i < 2; i ++)
    {
        for (j = i + 1; j < 3; j ++)
        {
            if (gUnknown_02039F80[i].quantity < gUnknown_02039F80[j].quantity)
            {
                tmpId = gUnknown_02039F80[i].itemId;
                tmpQn = gUnknown_02039F80[i].quantity;
                gUnknown_02039F80[i].itemId = gUnknown_02039F80[j].itemId;
                gUnknown_02039F80[i].quantity = gUnknown_02039F80[j].quantity;
                gUnknown_02039F80[j].itemId = tmpId;
                gUnknown_02039F80[j].quantity = tmpQn;
            }
        }
    }
}

void FindActiveBroadcastByShowType_SetScriptResult(u8 kind)
{
    u8 i;
    for (i = 0; i < 5; i ++)
    {
        if (gSaveBlock1Ptr->tvShows[i].common.kind == kind)
        {
            if (gSaveBlock1Ptr->tvShows[i].common.active == TRUE)
            {
                gSpecialVar_Result = TRUE;
            }
            else
            {
                DeleteTVShowInArrayByIdx(gSaveBlock1Ptr->tvShows, i);
                sub_80EF93C(gSaveBlock1Ptr->tvShows);
                sub_80EFA88();
            }
            return;
        }
    }
    sub_80EFA88();
}

void InterviewBefore(void)
{
    gSpecialVar_Result = FALSE;
    switch (gSpecialVar_0x8005)
    {
        case TVSHOW_FAN_CLUB_LETTER:
            InterviewBefore_FanClubLetter();
            break;
        case TVSHOW_RECENT_HAPPENINGS:
            InterviewBefore_RecentHappenings();
            break;
        case TVSHOW_PKMN_FAN_CLUB_OPINIONS:
            InterviewBefore_PkmnFanClubOpinions();
            break;
        case TVSHOW_UNKN_SHOWTYPE_04:
            InterviewBefore_Dummy();
            break;
        case TVSHOW_NAME_RATER_SHOW:
            InterviewBefore_NameRater();
            break;
        case TVSHOW_BRAVO_TRAINER_POKEMON_PROFILE:
            InterviewBefore_BravoTrainerPkmnProfile();
            break;
        case TVSHOW_BRAVO_TRAINER_BATTLE_TOWER_PROFILE:
            InterviewBefore_BravoTrainerBTProfile();
            break;
        case TVSHOW_CONTEST_LIVE_UPDATES:
            InterviewBefore_ContestLiveUpdates();
            break;
        case TVSHOW_3_CHEERS_FOR_POKEBLOCKS:
            InterviewBefore_3CheersForPokeblocks();
            break;
        case TVSHOW_FAN_CLUB_SPECIAL:
            InterviewBefore_FanClubSpecial();
            break;
    }
}

static void InterviewBefore_FanClubLetter(void)
{
    FindActiveBroadcastByShowType_SetScriptResult(TVSHOW_FAN_CLUB_LETTER);
    if (!gSpecialVar_Result)
    {
        StringCopy(gStringVar1, gSpeciesNames[GetMonData(&gPlayerParty[GetLeadMonIndex()], MON_DATA_SPECIES, NULL)]);
        InitializeEasyChatWordArray(gSaveBlock1Ptr->tvShows[sCurTVShowSlot].fanclubLetter.words, 6);
    }
}

static void InterviewBefore_RecentHappenings(void)
{
    FindActiveBroadcastByShowType_SetScriptResult(TVSHOW_RECENT_HAPPENINGS);
    if (!gSpecialVar_Result)
    {
        InitializeEasyChatWordArray(gSaveBlock1Ptr->tvShows[sCurTVShowSlot].recentHappenings.words, 6);
    }
}

static void InterviewBefore_PkmnFanClubOpinions(void)
{
    FindActiveBroadcastByShowType_SetScriptResult(TVSHOW_PKMN_FAN_CLUB_OPINIONS);
    if (!gSpecialVar_Result)
    {
        StringCopy(gStringVar1, gSpeciesNames[GetMonData(&gPlayerParty[GetLeadMonIndex()], MON_DATA_SPECIES, NULL)]);
        GetMonData(&gPlayerParty[GetLeadMonIndex()], MON_DATA_NICKNAME, gStringVar2);
        StringGetEnd10(gStringVar2);
        InitializeEasyChatWordArray(gSaveBlock1Ptr->tvShows[sCurTVShowSlot].fanclubOpinions.words, 2);
    }
}

static void InterviewBefore_Dummy(void)
{
    gSpecialVar_Result = TRUE;
}

static void InterviewBefore_NameRater(void)
{
    FindActiveBroadcastByShowType_SetScriptResult(TVSHOW_NAME_RATER_SHOW);
}

static void InterviewBefore_BravoTrainerPkmnProfile(void)
{
    FindActiveBroadcastByShowType_SetScriptResult(TVSHOW_BRAVO_TRAINER_POKEMON_PROFILE);
    if (!gSpecialVar_Result)
    {
        InitializeEasyChatWordArray(gSaveBlock1Ptr->tvShows[sCurTVShowSlot].bravoTrainer.words, 2);
    }
}

static void InterviewBefore_ContestLiveUpdates(void)
{
    FindActiveBroadcastByShowType_SetScriptResult(TVSHOW_CONTEST_LIVE_UPDATES);
}

static void InterviewBefore_3CheersForPokeblocks(void)
{
    FindActiveBroadcastByShowType_SetScriptResult(TVSHOW_3_CHEERS_FOR_POKEBLOCKS);
}

static void InterviewBefore_BravoTrainerBTProfile(void)
{
    FindActiveBroadcastByShowType_SetScriptResult(TVSHOW_BRAVO_TRAINER_BATTLE_TOWER_PROFILE);
    if (!gSpecialVar_Result)
    {
        InitializeEasyChatWordArray(gSaveBlock1Ptr->tvShows[sCurTVShowSlot].bravoTrainerTower.words, 1);
    }
}

static void InterviewBefore_FanClubSpecial(void)
{
    FindActiveBroadcastByShowType_SetScriptResult(TVSHOW_FAN_CLUB_SPECIAL);
    if (!gSpecialVar_Result)
    {
        InitializeEasyChatWordArray(gSaveBlock1Ptr->tvShows[sCurTVShowSlot].fanClubSpecial.words, 1);
    }
}

bool8 sub_80EF88C(u8 monIdx)
{
    struct Pokemon *pokemon;
    u8 language;

    pokemon = &gPlayerParty[monIdx];
    GetMonData(pokemon, MON_DATA_NICKNAME, gStringVar1);
    language = GetMonData(pokemon, MON_DATA_LANGUAGE, &language);
    if (language == LANGUAGE_ENGLISH && !StringCompare(gSpeciesNames[GetMonData(pokemon, MON_DATA_SPECIES, NULL)], gStringVar1))
    {
        return FALSE;
    }
    return TRUE;
}

bool8 sub_80EF8F8(void)
{
    return sub_80EF88C(GetLeadMonIndex());
}

void DeleteTVShowInArrayByIdx(TVShow *shows, u8 idx)
{
    u8 i;

    shows[idx].common.kind = TVSHOW_OFF_AIR;
    shows[idx].common.active = FALSE;
    for (i = 0; i < 34; i ++)
    {
        shows[idx].common.pad02[i] = 0;
    }
}

static void sub_80EF93C(TVShow *shows)
{
    u8 i;
    u8 j;

    for (i = 0; i < 4; i ++)
    {
        if (shows[i].common.kind == TVSHOW_OFF_AIR)
        {
            for (j = i + 1; j < 5; j ++)
            {
                if (shows[j].common.kind != TVSHOW_OFF_AIR)
                {
                    shows[i] = shows[j];
                    DeleteTVShowInArrayByIdx(shows, j);
                    break;
                }
            }
        }
    }
    for (i = 5; i < 24; i ++)
    {
        if (shows[i].common.kind == TVSHOW_OFF_AIR)
        {
            for (j = i + 1; j < 24; j ++)
            {
                if (shows[j].common.kind != TVSHOW_OFF_AIR)
                {
                    shows[i] = shows[j];
                    DeleteTVShowInArrayByIdx(shows, j);
                    break;
                }
            }
        }
    }
}

u16 TV_GetSomeOtherSpeciesAlreadySeenByPlayer_AndPrintName(u8 varIdx, u16 passedSpecies)
{
    u16 species;

    species = TV_GetSomeOtherSpeciesAlreadySeenByPlayer(passedSpecies);
    StringCopy(gTVStringVarPtrs[varIdx], gSpeciesNames[species]);
    return species;
}

u16 TV_GetSomeOtherSpeciesAlreadySeenByPlayer(u16 passedSpecies)
{
    u16 species;
    u16 initSpecies;

    species = (Random() % (NUM_SPECIES - 1)) + 1;
    initSpecies = species;
    while (GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), 0) != 1 || species == passedSpecies)
    {
        if (species == 1)
        {
            species = NUM_SPECIES - 1;
        }
        else
        {
            species --;
        }
        if (species == initSpecies)
        {
            species = passedSpecies;
            return species;
        }
    };
    return species;
}

static void sub_80EFA88(void)
{
    sCurTVShowSlot = FindEmptyTVSlotWithinFirstFiveShowsOfArray(gSaveBlock1Ptr->tvShows);
    gSpecialVar_0x8006 = sCurTVShowSlot;
    if (sCurTVShowSlot == -1)
    {
        gSpecialVar_Result = TRUE;
    }
    else
    {
        gSpecialVar_Result = FALSE;
    }
}

s8 FindEmptyTVSlotWithinFirstFiveShowsOfArray(TVShow *shows)
{
    u8 i;

    for (i = 0; i < 5; i ++)
    {
        if (shows[i].common.kind == TVSHOW_OFF_AIR)
        {
            return i;
        }
    }
    return -1;
}

s8 FindEmptyTVSlotBeyondFirstFiveShowsOfArray(TVShow *shows)
{
    s8 i;

    for (i = 5; i < 24; i ++)
    {
        if (shows[i].common.kind == TVSHOW_OFF_AIR)
        {
            return i;
        }
    }
    return -1;
}

bool8 TV_BernoulliTrial(u16 ratio)
{
    if (Random() <= ratio)
    {
        return FALSE;
    }
    return TRUE;
}

void TV_FanClubLetter_RandomWordToStringVar3(TVShow *show)
{
    u8 i;

    i = Random() % 6;
    while (TRUE)
    {
        if (i == 6)
        {
            i = 0;
        }
        if (show->fanclubLetter.words[i] != 0xFFFF)
        {
            break;
        }
        i ++;
    }
    CopyEasyChatWord(gStringVar3, show->fanclubLetter.words[i]);
}

u8 TV_GetNicknameSumMod8(TVShow *show)
{
    u8 i;
    u16 ct;

    ct = 0;
    for (i = 0; i < 11; i ++)
    {
        if (show->nameRaterShow.pokemonName[i] == EOS)
        {
            break;
        }
        ct += show->nameRaterShow.pokemonName[i];
    }
    return ct & 7;
}

void TV_GetNicknameSubstring(u8 varIdx, u8 whichPosition, u8 charParam, u16 whichString, u16 species, TVShow *show)
{
    u8 buff[16];
    u8 i;
    u16 strlen;

    for (i = 0; i < 3; i ++)
    {
        buff[i] = EOS;
    }
    if (whichString == 0)
    {
        strlen = StringLength(show->nameRaterShow.trainerName);
        if (charParam == 0)
        {
            buff[0] = show->nameRaterShow.trainerName[whichPosition];
        }
        else if (charParam == 1)
        {
            buff[0] = show->nameRaterShow.trainerName[strlen - whichPosition];
        }
        else if (charParam == 2)
        {
            buff[0] = show->nameRaterShow.trainerName[whichPosition];
            buff[1] = show->nameRaterShow.trainerName[whichPosition + 1];
        }
        else
        {
            buff[0] = show->nameRaterShow.trainerName[strlen - (whichPosition + 2)];
            buff[1] = show->nameRaterShow.trainerName[strlen - (whichPosition + 1)];
        }
        ConvertInternationalString(buff, show->nameRaterShow.language);
    }
    else if (whichString == 1)
    {
        strlen = StringLength(show->nameRaterShow.pokemonName);
        if (charParam == 0)
        {
            buff[0] = show->nameRaterShow.pokemonName[whichPosition];
        }
        else if (charParam == 1)
        {
            buff[0] = show->nameRaterShow.pokemonName[strlen - whichPosition];
        }
        else if (charParam == 2)
        {
            buff[0] = show->nameRaterShow.pokemonName[whichPosition];
            buff[1] = show->nameRaterShow.pokemonName[whichPosition + 1];
        }
        else
        {
            buff[0] = show->nameRaterShow.pokemonName[strlen - (whichPosition + 2)];
            buff[1] = show->nameRaterShow.pokemonName[strlen - (whichPosition + 1)];
        }
        ConvertInternationalString(buff, show->nameRaterShow.pokemonNameLanguage);
    }
    else
    {
        strlen = StringLength(gSpeciesNames[species]);
        if (charParam == 0)
        {
            buff[0] = gSpeciesNames[species][whichPosition];
        }
        else if (charParam == 1)
        {
            buff[0] = gSpeciesNames[species][strlen - whichPosition];
        }
        else if (charParam == 2)
        {
            buff[0] = gSpeciesNames[species][whichPosition];
            buff[1] = gSpeciesNames[species][whichPosition + 1];
        }
        else
        {
            buff[0] = gSpeciesNames[species][strlen - (whichPosition + 2)];
            buff[1] = gSpeciesNames[species][strlen - (whichPosition + 1)];
        }
    }
    StringCopy(gTVStringVarPtrs[varIdx], buff);
}

bool8 TV_IsScriptShowKindAlreadyInQueue(void)
{
    u8 i;

    for (i = 0; i < 5; i ++)
    {
        if (gSaveBlock1Ptr->tvShows[i].common.kind == gSpecialVar_0x8004)
        {
            return TRUE;
        }
    }
    return FALSE;
}

bool8 TV_PutNameRaterShowOnTheAirIfNicnkameChanged(void)
{
    GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_NICKNAME, gStringVar1);
    if (!StringCompare(gStringVar3, gStringVar1))
    {
        return FALSE;
    }
    PutNameRaterShowOnTheAir();
    return TRUE;
}

void ChangePokemonNickname(void)
{
    void ChangePokemonNickname_CB(void);

    GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_NICKNAME, gStringVar3);
    GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_NICKNAME, gStringVar2);
    DoNamingScreen(3, gStringVar2, GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_SPECIES, NULL), GetMonGender(&gPlayerParty[gSpecialVar_0x8004]), GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_PERSONALITY, NULL), ChangePokemonNickname_CB);
}

void ChangePokemonNickname_CB(void)
{
    SetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_NICKNAME, gStringVar2);
    CB2_ReturnToFieldContinueScriptPlayMapMusic();
}

void ChangeBoxPokemonNickname(void)
{
    struct BoxPokemon *boxMon;

    boxMon = GetBoxedMonPtr(gSpecialVar_MonBoxId, gSpecialVar_MonBoxPos);
    GetBoxMonData(boxMon, MON_DATA_NICKNAME, gStringVar3);
    GetBoxMonData(boxMon, MON_DATA_NICKNAME, gStringVar2);
    DoNamingScreen(3, gStringVar2, GetBoxMonData(boxMon, MON_DATA_SPECIES, NULL), GetBoxMonGender(boxMon), GetBoxMonData(boxMon, MON_DATA_PERSONALITY, NULL), ChangeBoxPokemonNickname_CB);
}

void ChangeBoxPokemonNickname_CB(void)
{
    SetBoxMonNickFromAnyBox(gSpecialVar_MonBoxId, gSpecialVar_MonBoxPos, gStringVar2);
    CB2_ReturnToFieldContinueScriptPlayMapMusic();
}

void TV_CopyNicknameToStringVar1AndEnsureTerminated(void)
{
    GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_NICKNAME, gStringVar1);
    StringGetEnd10(gStringVar1);
}

void TV_CheckMonOTIDEqualsPlayerID(void)
{
    if (GetPlayerIDAsU32() == GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_OT_ID, NULL))
    {
        gSpecialVar_Result = FALSE;
    }
    else
    {
        gSpecialVar_Result = TRUE;
    }
}

u8 GetTVChannelByShowType(u8 kind)
{
    if (kind == TVSHOW_OFF_AIR)
    {
        return 0;
    }
    if (kind >= TVSHOW_FAN_CLUB_LETTER && kind < TVSHOW_POKEMON_TODAY_CAUGHT)
    {
        return 2;
    }
    if (kind >= TVSHOW_POKEMON_TODAY_CAUGHT && kind < TVSHOW_MASS_OUTBREAK)
    {
        return 3;
    }
    if (kind >= TVSHOW_MASS_OUTBREAK && kind < 61)
    {
        return 4;
    }
    return 0;
}

u32 GetPlayerIDAsU32(void)
{
    return (gSaveBlock2Ptr->playerTrainerId[3] << 24) | (gSaveBlock2Ptr->playerTrainerId[2] << 16) | (gSaveBlock2Ptr->playerTrainerId[1] << 8) | gSaveBlock2Ptr->playerTrainerId[0];
}

u8 CheckForBigMovieOrEmergencyNewsOnTV(void)
{
    if (gSaveBlock1Ptr->location.mapGroup != MAP_GROUP(LITTLEROOT_TOWN_BRENDANS_HOUSE_1F))
    {
        return 0;
    }
    if (gSaveBlock2Ptr->playerGender == MALE)
    {
        if (gSaveBlock1Ptr->location.mapNum != MAP_NUM(LITTLEROOT_TOWN_BRENDANS_HOUSE_1F))
        {
            return 0;
        }
    }
    else
    {
        if (gSaveBlock1Ptr->location.mapNum != MAP_NUM(LITTLEROOT_TOWN_MAYS_HOUSE_1F))
        {
            return 0;
        }
    }
    if (FlagGet(FLAG_SYS_TV_LATI) == TRUE)
    {
        return 1;
    }
    if (FlagGet(FLAG_SYS_TV_HOME) == TRUE)
    {
        return 2;
    }
    return 1;
}

void GetMomOrDadStringForTVMessage(void)
{
    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(LITTLEROOT_TOWN_BRENDANS_HOUSE_1F))
    {
        if (gSaveBlock2Ptr->playerGender == MALE)
        {
            if (gSaveBlock1Ptr->location.mapNum == MAP_NUM(LITTLEROOT_TOWN_BRENDANS_HOUSE_1F))
            {
                StringCopy(gStringVar1, gText_Mom);
                VarSet(VAR_TEMP_3, 1);
            }
        }
        else
        {
            if (gSaveBlock1Ptr->location.mapNum == MAP_NUM(LITTLEROOT_TOWN_MAYS_HOUSE_1F))
            {
                StringCopy(gStringVar1, gText_Mom);
                VarSet(VAR_TEMP_3, 1);
            }
        }
    }
    if (VarGet(VAR_TEMP_3) == 1)
    {
        StringCopy(gStringVar1, gText_Mom);
    }
    else if (VarGet(VAR_TEMP_3) == 2)
    {
        StringCopy(gStringVar1, gText_Dad);
    }
    else if (VarGet(VAR_TEMP_3) > 2)
    {
        if (VarGet(VAR_TEMP_3) % 2 == 0)
            StringCopy(gStringVar1, gText_Mom);
        else
            StringCopy(gStringVar1, gText_Dad);
    }
    else
    {
        if (Random() % 2 != 0)
        {
            StringCopy(gStringVar1, gText_Mom);
            VarSet(VAR_TEMP_3, 1);
        }
        else
        {
            StringCopy(gStringVar1, gText_Dad);
            VarSet(VAR_TEMP_3, 2);
        }
    }
}

void sub_80F01B8(void)
{
    VarSet(VAR_0x40BC, 0);
    RemoveEventObjectByLocalIdAndMap(5, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
    FlagSet(0x396);
}

void ReceiveTvShowsData(void *src, u32 size, u8 masterIdx)
{
    u8 i;
    u16 version;
    TVShow (*rmBuffer2)[4][25];
    TVShow (*rmBuffer)[4][25];

    rmBuffer2 = malloc(4 * 25 * sizeof(TVShow));
    if (rmBuffer2 != NULL)
    {
        for (i = 0; i < 4; i ++)
        {
            memcpy((*rmBuffer2)[i], src + i * size, sizeof((*rmBuffer2)[i]));
        }
        rmBuffer = rmBuffer2;
        for (i = 0; i < GetLinkPlayerCount(); i ++)
        {
            version = (u8)gLinkPlayers[i].version;
            if (version == VERSION_RUBY || version == VERSION_SAPPHIRE)
            {
                sub_80F1254((*rmBuffer)[i]);
            }
            else if (version == VERSION_EMERALD && gLinkPlayers[i].language == LANGUAGE_JAPANESE)
            {
                sub_80F12A4((*rmBuffer)[i]);
            }
        }
        switch (masterIdx)
        {
            case 0:
                sub_80F0358(gSaveBlock1Ptr->tvShows, (*rmBuffer)[1], (*rmBuffer)[2], (*rmBuffer)[3]);
                break;
            case 1:
                sub_80F0358((*rmBuffer)[0], gSaveBlock1Ptr->tvShows, (*rmBuffer)[2], (*rmBuffer)[3]);
                break;
            case 2:
                sub_80F0358((*rmBuffer)[0], (*rmBuffer)[1], gSaveBlock1Ptr->tvShows, (*rmBuffer)[3]);
                break;
            case 3:
                sub_80F0358((*rmBuffer)[0], (*rmBuffer)[1], (*rmBuffer)[2], gSaveBlock1Ptr->tvShows);
                break;
        }
        sub_80EF93C(gSaveBlock1Ptr->tvShows);
        sub_80F0C04();
        sub_80EF93C(gSaveBlock1Ptr->tvShows);
        sub_80F0708();
        sub_80F0B64();
        free(rmBuffer2);
    }
}

static void sub_80F0358(TVShow player1[25], TVShow player2[25], TVShow player3[25], TVShow player4[25])
{
    u8 i;
    u8 j;
    TVShow **argslist[4];

    argslist[0] = &player1;
    argslist[1] = &player2;
    argslist[2] = &player3;
    argslist[3] = &player4;
    sTVShowMixingNumPlayers = GetLinkPlayerCount();
    while (1)
    {
        for (i = 0; i < sTVShowMixingNumPlayers; i ++)
        {
            if (i == 0)
            {
                sRecordMixingPartnersWithoutShowsToShare = i;
            }
            sTVShowMixingCurSlot = sub_80F06D0(argslist[i][0]);
            if (sTVShowMixingCurSlot == -1)
            {
                sRecordMixingPartnersWithoutShowsToShare ++;
                if (sRecordMixingPartnersWithoutShowsToShare == sTVShowMixingNumPlayers)
                {
                    return;
                }
            }
            else
            {
                for (j = 0; j < sTVShowMixingNumPlayers - 1; j ++)
                {
                    sCurTVShowSlot = FindEmptyTVSlotBeyondFirstFiveShowsOfArray(argslist[(i + j + 1) % sTVShowMixingNumPlayers][0]);
                    if (sCurTVShowSlot != -1
                        && sub_80F049C(&argslist[(i + j + 1) % sTVShowMixingNumPlayers][0], &argslist[i][0], (i + j + 1) % sTVShowMixingNumPlayers) == 1)
                    {
                        break;
                    }
                }
                if (j == sTVShowMixingNumPlayers - 1)
                {
                    DeleteTVShowInArrayByIdx(argslist[i][0], sTVShowMixingCurSlot);
                }
            }
        }
    }
}

static bool8 sub_80F049C(TVShow *dest[25], TVShow *src[25], u8 idx)
{
    u8 value;
    u8 switchval;
    TVShow *tv1;
    TVShow *tv2;

    tv1 = *dest;
    tv2 = *src;
    value = FALSE;
    switchval = GetTVChannelByShowType(tv2[sTVShowMixingCurSlot].common.kind);
    switch (switchval)
    {
        case 2:
            value = sub_80F0580(&tv1[sCurTVShowSlot], &tv2[sTVShowMixingCurSlot], idx);
            break;
        case 3:
            value = sub_80F05E8(&tv1[sCurTVShowSlot], &tv2[sTVShowMixingCurSlot], idx);
            break;
        case 4:
            value = sub_80F0668(&tv1[sCurTVShowSlot], &tv2[sTVShowMixingCurSlot], idx);
            break;
    }
    if (value == TRUE)
    {
        DeleteTVShowInArrayByIdx(tv2, sTVShowMixingCurSlot);
        return TRUE;
    }
    return FALSE;
}

static bool8 sub_80F0580(TVShow *tv1, TVShow *tv2, u8 idx)
{
    u32 linkTrainerId = GetLinkPlayerTrainerId(idx);

    if ((linkTrainerId & 0xFF) == tv2->common.trainerIdLo && ((linkTrainerId >> 8) & 0xFF) == tv2->common.trainerIdHi)
    {
        return FALSE;
    }
    tv2->common.trainerIdLo = tv2->common.srcTrainerIdLo;
    tv2->common.trainerIdHi = tv2->common.srcTrainerIdHi;
    tv2->common.srcTrainerIdLo = linkTrainerId & 0xFF;
    tv2->common.srcTrainerIdHi = linkTrainerId >> 8;
    *tv1 = *tv2;
    tv1->common.active = TRUE;
    return TRUE;
}

static bool8 sub_80F05E8(TVShow *tv1, TVShow *tv2, u8 idx)
{
    u32 linkTrainerId = GetLinkPlayerTrainerId(idx);
    if ((linkTrainerId & 0xFF) == tv2->common.srcTrainerIdLo && ((linkTrainerId >> 8) & 0xFF) == tv2->common.srcTrainerIdHi)
    {
        return FALSE;
    }
    if ((linkTrainerId & 0xFF) == tv2->common.trainerIdLo && ((linkTrainerId >> 8) & 0xFF) == tv2->common.trainerIdHi)
    {
        return FALSE;
    }
    tv2->common.srcTrainerIdLo = tv2->common.srcTrainerId2Lo;
    tv2->common.srcTrainerIdHi = tv2->common.srcTrainerId2Hi;
    tv2->common.srcTrainerId2Lo = linkTrainerId & 0xFF;
    tv2->common.srcTrainerId2Hi = linkTrainerId >> 8;
    *tv1 = *tv2;
    tv1->common.active = TRUE;
    return TRUE;
}

static bool8 sub_80F0668(TVShow *tv1, TVShow *tv2, u8 idx)
{
    u32 linkTrainerId = GetLinkPlayerTrainerId(idx);
    if ((linkTrainerId & 0xFF) == tv2->common.trainerIdLo && ((linkTrainerId >> 8) & 0xFF) == tv2->common.trainerIdHi)
    {
        return FALSE;
    }
    tv2->common.trainerIdLo = tv2->common.srcTrainerIdLo;
    tv2->common.trainerIdHi = tv2->common.srcTrainerIdHi;
    tv2->common.srcTrainerIdLo = linkTrainerId & 0xFF;
    tv2->common.srcTrainerIdHi = linkTrainerId >> 8;
    *tv1 = *tv2;
    tv1->common.active = TRUE;
    tv1->massOutbreak.daysLeft = 1;
    return TRUE;
}

static s8 sub_80F06D0(TVShow *tvShows)
{
    u8 i;

    for (i = 0; i < 24; i ++)
    {
        if (tvShows[i].common.active == FALSE && (u8)(tvShows[i].common.kind - 1) < 60)
        {
            return i;
        }
    }
    return -1;
}

#ifdef NONMATCHING
static void sub_80F0708(void) // FIXME: register allocation shenanigans
{
    u16 i;
    TVShow *show;

    for (i = 0; i < 24; i ++)
    {
        switch (gSaveBlock1Ptr->tvShows[i].common.kind)
        {
            case TVSHOW_CONTEST_LIVE_UPDATES:
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->contestLiveUpdates.species, i);
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->contestLiveUpdates.winningSpecies, i);
                break;
            case TVSHOW_3_CHEERS_FOR_POKEBLOCKS:
                break;
            case TVSHOW_BATTLE_UPDATE:
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->battleUpdate.speciesPlayer, i);
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->battleUpdate.speciesOpponent, i);
                break;
            case TVSHOW_FAN_CLUB_SPECIAL:
                break;
            case TVSHOW_CONTEST_LIVE_UPDATES_2:
                break;

            case TVSHOW_OFF_AIR:
                break;
            case TVSHOW_FAN_CLUB_LETTER:
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->fanclubLetter.species, i);
                break;
            case TVSHOW_RECENT_HAPPENINGS:
                break;
            case TVSHOW_PKMN_FAN_CLUB_OPINIONS:
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->fanclubOpinions.species, i);
                break;
            case TVSHOW_UNKN_SHOWTYPE_04:
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->unkShow04.var06, i);
                break;
            case TVSHOW_NAME_RATER_SHOW:
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->nameRaterShow.species, i);
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->nameRaterShow.randomSpecies, i);
                break;
            case TVSHOW_BRAVO_TRAINER_POKEMON_PROFILE:
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->bravoTrainer.species, i);
                break;
            case TVSHOW_BRAVO_TRAINER_BATTLE_TOWER_PROFILE:
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->bravoTrainerTower.species, i);
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->bravoTrainerTower.defeatedSpecies, i);
                break;

            case TVSHOW_POKEMON_TODAY_CAUGHT:
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->pokemonToday.species, i);
                break;
            case TVSHOW_SMART_SHOPPER:
                break;
            case TVSHOW_POKEMON_TODAY_FAILED:
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->pokemonTodayFailed.species, i);
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->pokemonTodayFailed.species2, i);
                break;
            case TVSHOW_FISHING_ADVICE:
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->pokemonAngler.species, i);
                break;
            case TVSHOW_WORLD_OF_MASTERS:
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->worldOfMasters.species, i);
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->worldOfMasters.caughtPoke, i);
                break;

            case TVSHOW_TODAYS_RIVAL_TRAINER:
                break;
            case TVSHOW_TREND_WATCHER:
                break;
            case TVSHOW_TREASURE_INVESTIGATORS:
                break;
            case TVSHOW_FIND_THAT_GAMER:
                break;
            case TVSHOW_BREAKING_NEWS:
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->breakingNews.lastOpponentSpecies, i);
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->breakingNews.poke1Species, i);
                break;
            case TVSHOW_SECRET_BASE_VISIT:
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->secretBaseVisit.species, i);
                break;
            case TVSHOW_LOTTO_WINNER:
                break;
            case TVSHOW_BATTLE_SEMINAR:
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->battleSeminar.species, i);
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->battleSeminar.foeSpecies, i);
                break;
            case TVSHOW_TRAINER_FAN_CLUB:
                break;
            case TVSHOW_CUTIES:
                break;
            case TVSHOW_FRONTIER:
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->frontier.species1, i);
                sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->frontier.species2, i);
                switch ((&gSaveBlock1Ptr->tvShows[i])->frontier.facility)
                {
                    case  3:
                    case  4:
                        break;
                    case  1:
                    case  5 ... 13:
                        sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->frontier.species3, i);
                        break;
                    case 2:
                        sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->frontier.species3, i);
                        sub_80F0B24((&gSaveBlock1Ptr->tvShows[i])->frontier.species4, i);
                        break;
                }
                break;
            case TVSHOW_NUMBER_ONE:
                break;
            case TVSHOW_SECRET_BASE_SECRETS:
                break;
            case TVSHOW_SAFARI_FAN_CLUB:
                break;

            case TVSHOW_MASS_OUTBREAK:
                break;

            default:
                SetTvShowInactive(i);
                break;
        }
    }
}
#else
NAKED static void sub_80F0708(void)
{
    asm_unified("\tpush {r4-r7,lr}\n"
                    "\tmov r7, r9\n"
                    "\tmov r6, r8\n"
                    "\tpush {r6,r7}\n"
                    "\tsub sp, 0x8\n"
                    "\tmovs r0, 0\n"
                    "\tmov r9, r0\n"
                    "_080F0716:\n"
                    "\tldr r3, =gSaveBlock1Ptr\n"
                    "\tldr r1, [r3]\n"
                    "\tmov r4, r9\n"
                    "\tlsls r2, r4, 3\n"
                    "\tadds r0, r2, r4\n"
                    "\tlsls r0, 2\n"
                    "\tadds r1, r0\n"
                    "\tldr r0, =0x000027cc\n"
                    "\tadds r1, r0\n"
                    "\tldrb r0, [r1]\n"
                    "\tadds r7, r2, 0\n"
                    "\tcmp r0, 0x29\n"
                    "\tbls _080F0732\n"
                    "\tb _080F0AD8\n"
                    "_080F0732:\n"
                    "\tlsls r0, 2\n"
                    "\tldr r1, =_080F0748\n"
                    "\tadds r0, r1\n"
                    "\tldr r0, [r0]\n"
                    "\tmov pc, r0\n"
                    "\t.pool\n"
                    "\t.align 2, 0\n"
                    "_080F0748:\n"
                    "\t.4byte _080F0AE2_break  @ TVSHOW_OFF_AIR\n"
                    "\t.4byte _080F0848  @ TVSHOW_FAN_CLUB_LETTER\n"
                    "\t.4byte _080F0AE2_break  @ TVSHOW_RECENT_HAPPENINGS\n"
                    "\t.4byte _080F0860  @ TVSHOW_PKMN_FAN_CLUB_OPINIONS\n"
                    "\t.4byte _080F0878  @ TVSHOW_UNKN_SHOWTYPE_04\n"
                    "\t.4byte _080F0890  @ TVSHOW_NAME_RATER_SHOW\n"
                    "\t.4byte _080F08BC  @ TVSHOW_BRAVO_TRAINER_POKEMON_PROFILE\n"
                    "\t.4byte _080F08D4  @ TVSHOW_BRAVO_TRAINER_BATTLE_TOWER_PROFILE\n"
                    "\t.4byte _080F07F0  @ TVSHOW_CONTEST_LIVE_UPDATES\n"
                    "\t.4byte _080F0AE2_break  @ TVSHOW_3_CHEERS_FOR_POKEBLOCKS\n"
                    "\t.4byte _080F081C  @ TVSHOW_BATTLE_UPDATE\n"
                    "\t.4byte _080F0AE2_break  @ TVSHOW_FAN_CLUB_SPECIAL\n"
                    "\t.4byte _080F0AE2_break  @ TVSHOW_CONTEST_LIVE_UPDATES_2\n"
                    "\t.4byte _080F0AD8  @ \n"
                    "\t.4byte _080F0AD8  @ \n"
                    "\t.4byte _080F0AD8  @ \n"
                    "\t.4byte _080F0AD8  @ \n"
                    "\t.4byte _080F0AD8  @ \n"
                    "\t.4byte _080F0AD8  @ \n"
                    "\t.4byte _080F0AD8  @ \n"
                    "\t.4byte _080F0AD8  @ \n"
                    "\t.4byte _080F0900  @ TVSHOW_POKEMON_TODAY_CAUGHT\n"
                    "\t.4byte _080F0AE2_break  @ TVSHOW_SMART_SHOPPER\n"
                    "\t.4byte _080F0918  @ TVSHOW_POKEMON_TODAY_FAILED\n"
                    "\t.4byte _080F0944  @ TVSHOW_FISHING_ADVICE\n"
                    "\t.4byte _080F095C  @ TVSHOW_WORLD_OF_MASTERS\n"
                    "\t.4byte _080F0AE2_break  @ TVSHOW_TODAYS_RIVAL_TRAINER\n"
                    "\t.4byte _080F0AE2_break  @ TVSHOW_TREND_WATCHER\n"
                    "\t.4byte _080F0AE2_break  @ TVSHOW_TREASURE_INVESTIGATORS\n"
                    "\t.4byte _080F0AE2_break  @ TVSHOW_FIND_THAT_GAMER\n"
                    "\t.4byte _080F0974  @ TVSHOW_BREAKING_NEWS\n"
                    "\t.4byte _080F09A0  @ TVSHOW_SECRET_BASE_VISIT\n"
                    "\t.4byte _080F0AE2_break  @ TVSHOW_LOTTO_WINNER\n"
                    "\t.4byte _080F09C0  @ TVSHOW_BATTLE_SEMINAR\n"
                    "\t.4byte _080F0AE2_break  @ TVSHOW_TRAINER_FAN_CLUB\n"
                    "\t.4byte _080F0AE2_break  @ TVSHOW_CUTIES\n"
                    "\t.4byte _080F09F4  @ TVSHOW_FRONTIER\n"
                    "\t.4byte _080F0AE2_break  @ TVSHOW_NUMBER_ONE\n"
                    "\t.4byte _080F0AE2_break  @ TVSHOW_SECRET_BASE_SECRETS\n"
                    "\t.4byte _080F0AE2_break  @ TVSHOW_SAFARI_FAN_CLUB\n"
                    "\t.4byte _080F0AD8  @ \n"
                    "\t.4byte _080F0AE2_break  @ TVSHOW_MASS_OUTBREAK\n"
                    "_080F07F0:\n"
                    "\tldr r0, [r3]\n"
                    "\tmov r1, r9\n"
                    "\tadds r4, r7, r1\n"
                    "\tlsls r4, 2\n"
                    "\tadds r0, r4, r0\n"
                    "\tldr r6, =0x000027cc\n"
                    "\tadds r0, r6\n"
                    "\tldrh r0, [r0, 0x12]\n"
                    "\tlsls r5, r1, 24\n"
                    "\tlsrs r5, 24\n"
                    "\tadds r1, r5, 0\n"
                    "\tstr r3, [sp, 0x4]\n"
                    "\tbl sub_80F0B24\n"
                    "\tldr r3, [sp, 0x4]\n"
                    "\tldr r0, [r3]\n"
                    "\tadds r4, r0\n"
                    "\tadds r4, r6\n"
                    "\tldrh r0, [r4, 0x2]\n"
                    "\tb _080F09E6\n"
                    "\t.pool\n"
                    "_080F081C:\n"
                    "\tldr r0, [r3]\n"
                    "\tmov r2, r9\n"
                    "\tadds r4, r7, r2\n"
                    "\tlsls r4, 2\n"
                    "\tadds r0, r4, r0\n"
                    "\tldr r6, =0x000027cc\n"
                    "\tadds r0, r6\n"
                    "\tldrh r0, [r0, 0x16]\n"
                    "\tlsls r5, r2, 24\n"
                    "\tlsrs r5, 24\n"
                    "\tadds r1, r5, 0\n"
                    "\tstr r3, [sp, 0x4]\n"
                    "\tbl sub_80F0B24\n"
                    "\tldr r3, [sp, 0x4]\n"
                    "\tldr r0, [r3]\n"
                    "\tadds r4, r0\n"
                    "\tadds r4, r6\n"
                    "\tldrh r0, [r4, 0x2]\n"
                    "\tb _080F09E6\n"
                    "\t.pool\n"
                    "_080F0848:\n"
                    "\tldr r0, [r3]\n"
                    "\tmov r4, r9\n"
                    "\tadds r1, r7, r4\n"
                    "\tlsls r1, 2\n"
                    "\tadds r1, r0\n"
                    "\tldr r0, =0x000027cc\n"
                    "\tadds r1, r0\n"
                    "\tldrh r0, [r1, 0x2]\n"
                    "\tb _080F09B0\n"
                    "\t.pool\n"
                    "_080F0860:\n"
                    "\tldr r0, [r3]\n"
                    "\tmov r2, r9\n"
                    "\tadds r1, r7, r2\n"
                    "\tlsls r1, 2\n"
                    "\tadds r1, r0\n"
                    "\tldr r4, =0x000027cc\n"
                    "\tadds r1, r4\n"
                    "\tldrh r0, [r1, 0x2]\n"
                    "\tlsls r1, r2, 24\n"
                    "\tb _080F09B2\n"
                    "\t.pool\n"
                    "_080F0878:\n"
                    "\tldr r0, [r3]\n"
                    "\tmov r2, r9\n"
                    "\tadds r1, r7, r2\n"
                    "\tlsls r1, 2\n"
                    "\tadds r1, r0\n"
                    "\tldr r4, =0x000027cc\n"
                    "\tadds r1, r4\n"
                    "\tldrh r0, [r1, 0x6]\n"
                    "\tlsls r1, r2, 24\n"
                    "\tb _080F09B2\n"
                    "\t.pool\n"
                    "_080F0890:\n"
                    "\tldr r0, [r3]\n"
                    "\tmov r1, r9\n"
                    "\tadds r4, r7, r1\n"
                    "\tlsls r4, 2\n"
                    "\tadds r0, r4, r0\n"
                    "\tldr r6, =0x000027cc\n"
                    "\tadds r0, r6\n"
                    "\tldrh r0, [r0, 0x2]\n"
                    "\tlsls r5, r1, 24\n"
                    "\tlsrs r5, 24\n"
                    "\tadds r1, r5, 0\n"
                    "\tstr r3, [sp, 0x4]\n"
                    "\tbl sub_80F0B24\n"
                    "\tldr r3, [sp, 0x4]\n"
                    "\tldr r0, [r3]\n"
                    "\tadds r4, r0\n"
                    "\tadds r4, r6\n"
                    "\tldrh r0, [r4, 0x1C]\n"
                    "\tb _080F09E6\n"
                    "\t.pool\n"
                    "_080F08BC:\n"
                    "\tldr r0, [r3]\n"
                    "\tmov r2, r9\n"
                    "\tadds r1, r7, r2\n"
                    "\tlsls r1, 2\n"
                    "\tadds r1, r0\n"
                    "\tldr r4, =0x000027cc\n"
                    "\tadds r1, r4\n"
                    "\tldrh r0, [r1, 0x2]\n"
                    "\tlsls r1, r2, 24\n"
                    "\tb _080F09B2\n"
                    "\t.pool\n"
                    "_080F08D4:\n"
                    "\tldr r0, [r3]\n"
                    "\tmov r1, r9\n"
                    "\tadds r4, r7, r1\n"
                    "\tlsls r4, 2\n"
                    "\tadds r0, r4, r0\n"
                    "\tldr r6, =0x000027cc\n"
                    "\tadds r0, r6\n"
                    "\tldrh r0, [r0, 0xA]\n"
                    "\tlsls r5, r1, 24\n"
                    "\tlsrs r5, 24\n"
                    "\tadds r1, r5, 0\n"
                    "\tstr r3, [sp, 0x4]\n"
                    "\tbl sub_80F0B24\n"
                    "\tldr r3, [sp, 0x4]\n"
                    "\tldr r0, [r3]\n"
                    "\tadds r4, r0\n"
                    "\tadds r4, r6\n"
                    "\tldrh r0, [r4, 0x14]\n"
                    "\tb _080F09E6\n"
                    "\t.pool\n"
                    "_080F0900:\n"
                    "\tldr r0, [r3]\n"
                    "\tmov r2, r9\n"
                    "\tadds r1, r7, r2\n"
                    "\tlsls r1, 2\n"
                    "\tadds r1, r0\n"
                    "\tldr r4, =0x000027cc\n"
                    "\tadds r1, r4\n"
                    "\tldrh r0, [r1, 0x10]\n"
                    "\tlsls r1, r2, 24\n"
                    "\tb _080F09B2\n"
                    "\t.pool\n"
                    "_080F0918:\n"
                    "\tldr r0, [r3]\n"
                    "\tmov r1, r9\n"
                    "\tadds r4, r7, r1\n"
                    "\tlsls r4, 2\n"
                    "\tadds r0, r4, r0\n"
                    "\tldr r6, =0x000027cc\n"
                    "\tadds r0, r6\n"
                    "\tldrh r0, [r0, 0xC]\n"
                    "\tlsls r5, r1, 24\n"
                    "\tlsrs r5, 24\n"
                    "\tadds r1, r5, 0\n"
                    "\tstr r3, [sp, 0x4]\n"
                    "\tbl sub_80F0B24\n"
                    "\tldr r3, [sp, 0x4]\n"
                    "\tldr r0, [r3]\n"
                    "\tadds r4, r0\n"
                    "\tadds r4, r6\n"
                    "\tldrh r0, [r4, 0xE]\n"
                    "\tb _080F09E6\n"
                    "\t.pool\n"
                    "_080F0944:\n"
                    "\tldr r0, [r3]\n"
                    "\tmov r2, r9\n"
                    "\tadds r1, r7, r2\n"
                    "\tlsls r1, 2\n"
                    "\tadds r1, r0\n"
                    "\tldr r4, =0x000027cc\n"
                    "\tadds r1, r4\n"
                    "\tldrh r0, [r1, 0x4]\n"
                    "\tlsls r1, r2, 24\n"
                    "\tb _080F09B2\n"
                    "\t.pool\n"
                    "_080F095C:\n"
                    "\tldr r0, [r3]\n"
                    "\tmov r1, r9\n"
                    "\tadds r4, r7, r1\n"
                    "\tlsls r4, 2\n"
                    "\tadds r0, r4, r0\n"
                    "\tldr r6, =0x000027cc\n"
                    "\tadds r0, r6\n"
                    "\tldrh r0, [r0, 0x8]\n"
                    "\tb _080F09D0\n"
                    "\t.pool\n"
                    "_080F0974:\n"
                    "\tldr r0, [r3]\n"
                    "\tmov r2, r9\n"
                    "\tadds r4, r7, r2\n"
                    "\tlsls r4, 2\n"
                    "\tadds r0, r4, r0\n"
                    "\tldr r6, =0x000027cc\n"
                    "\tadds r0, r6\n"
                    "\tldrh r0, [r0, 0x2]\n"
                    "\tlsls r5, r2, 24\n"
                    "\tlsrs r5, 24\n"
                    "\tadds r1, r5, 0\n"
                    "\tstr r3, [sp, 0x4]\n"
                    "\tbl sub_80F0B24\n"
                    "\tldr r3, [sp, 0x4]\n"
                    "\tldr r0, [r3]\n"
                    "\tadds r4, r0\n"
                    "\tadds r4, r6\n"
                    "\tldrh r0, [r4, 0xA]\n"
                    "\tb _080F09E6\n"
                    "\t.pool\n"
                    "_080F09A0:\n"
                    "\tldr r0, [r3]\n"
                    "\tmov r4, r9\n"
                    "\tadds r1, r7, r4\n"
                    "\tlsls r1, 2\n"
                    "\tadds r1, r0\n"
                    "\tldr r0, =0x000027cc\n"
                    "\tadds r1, r0\n"
                    "\tldrh r0, [r1, 0x8]\n"
                    "_080F09B0:\n"
                    "\tlsls r1, r4, 24\n"
                    "_080F09B2:\n"
                    "\tlsrs r1, 24\n"
                    "\tbl sub_80F0B24\n"
                    "\tb _080F0AE2_break\n"
                    "\t.pool\n"
                    "_080F09C0:\n"
                    "\tldr r0, [r3]\n"
                    "\tmov r1, r9\n"
                    "\tadds r4, r7, r1\n"
                    "\tlsls r4, 2\n"
                    "\tadds r0, r4, r0\n"
                    "\tldr r6, =0x000027cc\n"
                    "\tadds r0, r6\n"
                    "\tldrh r0, [r0, 0x6]\n"
                    "_080F09D0:\n"
                    "\tlsls r5, r1, 24\n"
                    "\tlsrs r5, 24\n"
                    "\tadds r1, r5, 0\n"
                    "\tstr r3, [sp, 0x4]\n"
                    "\tbl sub_80F0B24\n"
                    "\tldr r3, [sp, 0x4]\n"
                    "\tldr r0, [r3]\n"
                    "\tadds r4, r0\n"
                    "\tadds r4, r6\n"
                    "\tldrh r0, [r4, 0x4]\n"
                    "_080F09E6:\n"
                    "\tadds r1, r5, 0\n"
                    "\tbl sub_80F0B24\n"
                    "\tb _080F0AE2_break\n"
                    "\t.pool\n"
                    "_080F09F4:\n"
                    "\tldr r0, [r3]\n"
                    "\tmov r2, r9\n"
                    "\tadds r4, r7, r2\n"
                    "\tlsls r4, 2\n"
                    "\tadds r0, r4, r0\n"
                    "\tldr r5, =0x000027cc\n"
                    "\tadds r0, r5\n"
                    "\tldrh r0, [r0, 0x4]\n"
                    "\tlsls r2, 24\n"
                    "\tmov r8, r2\n"
                    "\tlsrs r6, r2, 24\n"
                    "\tadds r1, r6, 0\n"
                    "\tstr r3, [sp, 0x4]\n"
                    "\tbl sub_80F0B24\n"
                    "\tldr r3, [sp, 0x4]\n"
                    "\tldr r0, [r3]\n"
                    "\tadds r0, r4, r0\n"
                    "\tadds r0, r5\n"
                    "\tldrh r0, [r0, 0x6]\n"
                    "\tadds r1, r6, 0\n"
                    "\tbl sub_80F0B24\n"
                    "\tldr r3, [sp, 0x4]\n"
                    "\tldr r0, [r3]\n"
                    "\tadds r4, r0\n"
                    "\tadds r4, r5\n"
                    "\tldrb r0, [r4, 0xD]\n"
                    "\tsubs r0, 0x1\n"
                    "\tmov r6, r8\n"
                    "\tcmp r0, 0xC\n"
                    "\tbhi _080F0AE2_break\n"
                    "\tlsls r0, 2\n"
                    "\tldr r1, =_080F0A48\n"
                    "\tadds r0, r1\n"
                    "\tldr r0, [r0]\n"
                    "\tmov pc, r0\n"
                    "\t.pool\n"
                    "\t.align 2, 0\n"
                    "_080F0A48:\n"
                    "\t.4byte _080F0A7C\n"
                    "\t.4byte _080F0AA0\n"
                    "\t.4byte _080F0AE2_break\n"
                    "\t.4byte _080F0AE2_break\n"
                    "\t.4byte _080F0A7C\n"
                    "\t.4byte _080F0A7C\n"
                    "\t.4byte _080F0A7C\n"
                    "\t.4byte _080F0A7C\n"
                    "\t.4byte _080F0A7C\n"
                    "\t.4byte _080F0A7C\n"
                    "\t.4byte _080F0A7C\n"
                    "\t.4byte _080F0A7C\n"
                    "\t.4byte _080F0A7C\n"
                    "_080F0A7C:\n"
                    "\tldr r0, =gSaveBlock1Ptr\n"
                    "\tldr r1, [r0]\n"
                    "\tmov r4, r9\n"
                    "\tadds r0, r7, r4\n"
                    "\tlsls r0, 2\n"
                    "\tadds r0, r1\n"
                    "\tldr r1, =0x000027cc\n"
                    "\tadds r0, r1\n"
                    "\tldrh r0, [r0, 0x8]\n"
                    "\tlsrs r1, r6, 24\n"
                    "\tbl sub_80F0B24\n"
                    "\tb _080F0AE2_break\n"
                    "\t.pool\n"
                    "_080F0AA0:\n"
                    "\tldr r2, =gSaveBlock1Ptr\n"
                    "\tldr r0, [r2]\n"
                    "\tmov r1, r9\n"
                    "\tadds r4, r7, r1\n"
                    "\tlsls r4, 2\n"
                    "\tadds r0, r4, r0\n"
                    "\tldr r5, =0x000027cc\n"
                    "\tadds r0, r5\n"
                    "\tldrh r0, [r0, 0x8]\n"
                    "\tlsrs r6, 24\n"
                    "\tadds r1, r6, 0\n"
                    "\tstr r2, [sp]\n"
                    "\tbl sub_80F0B24\n"
                    "\tldr r2, [sp]\n"
                    "\tldr r0, [r2]\n"
                    "\tadds r4, r0\n"
                    "\tadds r4, r5\n"
                    "\tldrh r0, [r4, 0xA]\n"
                    "\tadds r1, r6, 0\n"
                    "\tbl sub_80F0B24\n"
                    "\tb _080F0AE2_break\n"
                    "\t.pool\n"
                    "_080F0AD8:\n"
                    "\tmov r2, r9\n"
                    "\tlsls r0, r2, 24\n"
                    "\tlsrs r0, 24\n"
                    "\tbl SetTvShowInactive\n"
                    "_080F0AE2_break:\n"
                    "\tmov r0, r9\n"
                    "\tadds r0, 0x1\n"
                    "\tlsls r0, 16\n"
                    "\tlsrs r0, 16\n"
                    "\tmov r9, r0\n"
                    "\tcmp r0, 0x17\n"
                    "\tbhi _080F0AF2\n"
                    "\tb _080F0716\n"
                    "_080F0AF2:\n"
                    "\tadd sp, 0x8\n"
                    "\tpop {r3,r4}\n"
                    "\tmov r8, r3\n"
                    "\tmov r9, r4\n"
                    "\tpop {r4-r7}\n"
                    "\tpop {r0}\n"
                    "\tbx r0");
}
#endif

void SetTvShowInactive(u8 showIdx)
{
    gSaveBlock1Ptr->tvShows[showIdx].common.active = FALSE;
}

static void sub_80F0B24(u16 species, u8 showIdx)
{
    if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), 0) == 0)
    {
        gSaveBlock1Ptr->tvShows[showIdx].common.active = FALSE;
    }
}

static void sub_80F0B64(void)
{
    u16 i;

    if (FlagGet(FLAG_SYS_GAME_CLEAR) != TRUE)
    {
        for (i = 0; i < 24; i ++)
        {
            if (gSaveBlock1Ptr->tvShows[i].common.kind == TVSHOW_BRAVO_TRAINER_BATTLE_TOWER_PROFILE)
            {
                gSaveBlock1Ptr->tvShows[i].common.active = FALSE;
            }
            else if (gSaveBlock1Ptr->tvShows[i].common.kind == TVSHOW_MASS_OUTBREAK)
            {
                gSaveBlock1Ptr->tvShows[i].common.active = FALSE;
            }
        }
    }
}

void sub_80F0BB8(void)
{
    u8 i;

    for (i = 0; i < 5; i ++)
    {
        if (GetTVChannelByShowType(gSaveBlock1Ptr->tvShows[i].common.kind) == 2)
        {
            gSaveBlock1Ptr->tvShows[i].common.active = FALSE;
        }
    }
}

static void sub_80F0C04(void)
{
    s8 i;
    s8 ct;

    ct = 0;
    for (i = 5; i < 24; i ++)
    {
        if (gSaveBlock1Ptr->tvShows[i].common.kind == TVSHOW_OFF_AIR)
        {
            ct ++;
        }
    }
    for (i = 0; i < 5 - ct; i ++)
    {
        DeleteTVShowInArrayByIdx(gSaveBlock1Ptr->tvShows, i + 5);
    }
}

void ReceivePokeNewsData(void *src, u32 size, u8 masterIdx)
{
    u8 i;
    PokeNews (*rmBuffer2)[4][16];
    PokeNews (*rmBuffer)[4][16];

    rmBuffer2 = malloc(4 * 16 * sizeof(PokeNews));
    if (rmBuffer2 != NULL)
    {
        for (i = 0; i < 4; i ++)
        {
            memcpy((*rmBuffer2)[i], src + i * size, sizeof((*rmBuffer2)[i]));
        }
        rmBuffer = rmBuffer2;
        switch (masterIdx)
        {
            case 0:
                sub_80F0D60(gSaveBlock1Ptr->pokeNews, (*rmBuffer)[1], (*rmBuffer)[2], (*rmBuffer)[3]);
                break;
            case 1:
                sub_80F0D60((*rmBuffer)[0], gSaveBlock1Ptr->pokeNews, (*rmBuffer)[2], (*rmBuffer)[3]);
                break;
            case 2:
                sub_80F0D60((*rmBuffer)[0], (*rmBuffer)[1], gSaveBlock1Ptr->pokeNews, (*rmBuffer)[3]);
                break;
            case 3:
                sub_80F0D60((*rmBuffer)[0], (*rmBuffer)[1], (*rmBuffer)[2], gSaveBlock1Ptr->pokeNews);
                break;
        }
        sub_80F0EEC();
        sub_80F0F24();
        free(rmBuffer2);
    }
}

static void sub_80F0D60(PokeNews player1[16], PokeNews player2[16], PokeNews player3[16], PokeNews player4[16])
{
    u8 i;
    u8 j;
    u8 k;
    PokeNews **argslist[4];

    argslist[0] = &player1;
    argslist[1] = &player2;
    argslist[2] = &player3;
    argslist[3] = &player4;
    sTVShowNewsMixingNumPlayers = GetLinkPlayerCount();
    for (i = 0; i < 16; i ++)
    {
        for (j = 0; j < sTVShowNewsMixingNumPlayers; j ++)
        {
            sTVShowMixingCurSlot = sub_80F0ECC(*argslist[j], i);
            if (sTVShowMixingCurSlot != -1)
            {
                for (k = 0; k < sTVShowNewsMixingNumPlayers - 1; k++)
                {
                    sCurTVShowSlot = sub_80EEE30(*argslist[(j + k + 1) % sTVShowNewsMixingNumPlayers]);
                    if (sCurTVShowSlot != -1)
                    {
                        sub_80F0E58(argslist[(j + k + 1) % sTVShowNewsMixingNumPlayers], argslist[j]);
                    }
                }
            }
        }
    }
}

static void sub_80F0E58(PokeNews *dest[16], PokeNews *src[16])
{
    PokeNews *ptr1;
    PokeNews *ptr2;

    ptr1 = *dest;
    ptr2 = *src;
    ptr2 += sTVShowMixingCurSlot;
    sub_80F0E84(ptr1, ptr2, sCurTVShowSlot);
}

static bool8 sub_80F0E84(PokeNews *dest, PokeNews *src, s8 slot)
{
    u8 i;
    u8 kind;

    if (src->kind == POKENEWS_NONE)
    {
        return FALSE;
    }
    for (i = 0; i < 16; i ++)
    {
        if (dest[i].kind == src->kind)
        {
            return FALSE;
        }
    }
    dest[slot].kind = src->kind;
    dest[slot].state = 1;
    dest[slot].days = src->days;
    return TRUE;
}

static s8 sub_80F0ECC(PokeNews *pokeNews, u8 idx)
{
    if (pokeNews[idx].kind == POKENEWS_NONE)
    {
        return -1;
    }
    return idx;
}

static void sub_80F0EEC(void)
{
    u8 i;

    for (i = 0; i < 16; i ++)
    {
        if (gSaveBlock1Ptr->pokeNews[i].kind > POKENEWS_BLENDMASTER)
        {
            ClearPokemonNewsI(i);
        }
    }
    sub_80EEEB8();
}

static void sub_80F0F24(void)
{
    u8 i;

    if (FlagGet(FLAG_SYS_GAME_CLEAR) != TRUE)
    {
        for (i = 0; i < 16; i ++)
        {
            gSaveBlock1Ptr->pokeNews[i].state = 0;
        }
    }
}

#define tvlangfix(strptr, langptr, langfix) \
if (IsStringJapanese(strptr)) \
{   \
    (langptr) = LANGUAGE_JAPANESE; \
} \
else \
{ \
    (langptr) = langfix; \
}

static void sub_80F0F64(TVShow *show, u32 language)
{
    int i;
    TVShow **r4;

    r4 = calloc(11, sizeof(TVShow *));
    for (i = 0; i < 24; i ++)
    {
        switch (show[i].common.kind)
        {
            case TVSHOW_FAN_CLUB_LETTER:
            case TVSHOW_RECENT_HAPPENINGS:
                r4[0] = &show[i];
                tvlangfix(r4[0]->fanclubLetter.playerName, r4[0]->fanclubLetter.language, language);
                break;
            case TVSHOW_PKMN_FAN_CLUB_OPINIONS:
                r4[1] = &show[i];
                tvlangfix(r4[1]->fanclubOpinions.playerName, r4[1]->fanclubOpinions.language, language);
                tvlangfix(r4[1]->fanclubOpinions.nickname, r4[1]->fanclubOpinions.pokemonNameLanguage, language);
                break;
            case TVSHOW_POKEMON_TODAY_CAUGHT:
                r4[6] = &show[i];
                tvlangfix(r4[6]->pokemonToday.playerName, r4[6]->pokemonToday.language, language);
                tvlangfix(r4[6]->pokemonToday.nickname, r4[6]->pokemonToday.language2, language);
                break;
            case TVSHOW_SMART_SHOPPER:
                r4[7] = &show[i];
                tvlangfix(r4[7]->smartshopperShow.playerName, r4[7]->smartshopperShow.language, language);
                break;
            case TVSHOW_BRAVO_TRAINER_BATTLE_TOWER_PROFILE:
                r4[5] = &show[i];
                tvlangfix(r4[5]->bravoTrainerTower.trainerName, r4[5]->bravoTrainerTower.language, language);
                tvlangfix(r4[5]->bravoTrainerTower.pokemonName, r4[5]->bravoTrainerTower.pokemonNameLanguage, language);
                break;
            case TVSHOW_BRAVO_TRAINER_POKEMON_PROFILE:
                r4[4] = &show[i];
                tvlangfix(r4[4]->bravoTrainer.playerName, r4[4]->bravoTrainer.language, language);
                tvlangfix(r4[4]->bravoTrainer.pokemonNickname, r4[4]->bravoTrainer.pokemonNameLanguage, language);
                break;
            case TVSHOW_NAME_RATER_SHOW:
                r4[3] = &show[i];
                tvlangfix(r4[3]->nameRaterShow.trainerName, r4[3]->nameRaterShow.language, language);
                tvlangfix(r4[3]->nameRaterShow.pokemonName, r4[3]->nameRaterShow.pokemonNameLanguage, language);
                break;
            case TVSHOW_POKEMON_TODAY_FAILED:
                r4[2] = &show[i];
                tvlangfix(r4[2]->pokemonTodayFailed.playerName, r4[2]->pokemonTodayFailed.language, language);
                break;
            case TVSHOW_FISHING_ADVICE:
                r4[8] = &show[i];
                tvlangfix(r4[8]->pokemonAngler.playerName, r4[8]->pokemonAngler.language, language);
                break;
            case TVSHOW_WORLD_OF_MASTERS:
                r4[9] = &show[i];
                tvlangfix(r4[9]->worldOfMasters.playerName, r4[9]->worldOfMasters.language, language);
                break;
            case TVSHOW_MASS_OUTBREAK:
                r4[10] = &show[i];
                r4[10]->massOutbreak.language = language;
                break;
        }
    }
    free(r4);
}

void sub_80F1208(TVShow *shows)
{
    TVShow *curShow;

    sub_80F14F8(shows);
    for (curShow = shows; curShow < shows + 24; curShow ++)
    {
        if (curShow->bravoTrainerTower.kind == TVSHOW_BRAVO_TRAINER_BATTLE_TOWER_PROFILE)
        {
            if ((curShow->bravoTrainerTower.language == LANGUAGE_JAPANESE && curShow->bravoTrainerTower.pokemonNameLanguage != LANGUAGE_JAPANESE) || (curShow->bravoTrainerTower.language != LANGUAGE_JAPANESE && curShow->bravoTrainerTower.pokemonNameLanguage == LANGUAGE_JAPANESE))
            {
                memset(curShow, 0, sizeof(TVShow));
            }
        }
    }
}

static void sub_80F1254(TVShow *shows)
{
    TVShow *curShow;

    for (curShow = shows; curShow < shows + 24; curShow ++)
    {
        if (curShow->bravoTrainerTower.kind == TVSHOW_BRAVO_TRAINER_BATTLE_TOWER_PROFILE)
        {
            if (IsStringJapanese(curShow->bravoTrainerTower.pokemonName))
            {
                curShow->bravoTrainerTower.pokemonNameLanguage = LANGUAGE_JAPANESE;
            }
            else
            {
                curShow->bravoTrainerTower.pokemonNameLanguage = LANGUAGE_ENGLISH;
            }
        }
    }
}

u8 TV_GetStringLanguage(u8 *str)
{
    return IsStringJapanese(str) ? LANGUAGE_JAPANESE : LANGUAGE_ENGLISH;
}

static void sub_80F12A4(TVShow *shows)
{
    TVShow *curShow;

    for (curShow = shows; curShow < shows + 24; curShow ++)
    {
        switch(curShow->common.kind)
        {
            case TVSHOW_FAN_CLUB_LETTER:
                curShow->fanclubLetter.language = TV_GetStringLanguage(curShow->fanclubLetter.playerName);
                break;
            case TVSHOW_RECENT_HAPPENINGS:
                curShow->recentHappenings.language = TV_GetStringLanguage(curShow->recentHappenings.playerName);
                break;
            case TVSHOW_PKMN_FAN_CLUB_OPINIONS:
                curShow->fanclubOpinions.language = TV_GetStringLanguage(curShow->fanclubOpinions.playerName);
                curShow->fanclubOpinions.pokemonNameLanguage = TV_GetStringLanguage(curShow->fanclubOpinions.nickname);
                break;
            case TVSHOW_UNKN_SHOWTYPE_04:
                curShow->unkShow04.language = TV_GetStringLanguage(curShow->unkShow04.string_0b);
                break;
            case TVSHOW_NAME_RATER_SHOW:
                curShow->nameRaterShow.language = TV_GetStringLanguage(curShow->nameRaterShow.trainerName);
                curShow->nameRaterShow.pokemonNameLanguage = TV_GetStringLanguage(curShow->nameRaterShow.pokemonName);
                break;
            case TVSHOW_BRAVO_TRAINER_POKEMON_PROFILE:
                curShow->bravoTrainer.language = TV_GetStringLanguage(curShow->bravoTrainer.playerName);
                curShow->bravoTrainer.pokemonNameLanguage = TV_GetStringLanguage(curShow->bravoTrainer.pokemonNickname);
                break;
            case TVSHOW_BRAVO_TRAINER_BATTLE_TOWER_PROFILE:
                curShow->bravoTrainerTower.language = TV_GetStringLanguage(curShow->bravoTrainerTower.trainerName);
                curShow->bravoTrainerTower.pokemonNameLanguage = TV_GetStringLanguage(curShow->bravoTrainerTower.pokemonName);
                break;
            case TVSHOW_CONTEST_LIVE_UPDATES:
                curShow->contestLiveUpdates.language = TV_GetStringLanguage(curShow->contestLiveUpdates.playerName);
                curShow->contestLiveUpdates.winningTrainerLanguage = TV_GetStringLanguage(curShow->contestLiveUpdates.winningTrainerName);
                break;
            case TVSHOW_3_CHEERS_FOR_POKEBLOCKS:
                curShow->threeCheers.language = TV_GetStringLanguage(curShow->threeCheers.playerName);
                curShow->threeCheers.worstBlenderLanguage = TV_GetStringLanguage(curShow->threeCheers.worstBlenderName);
                break;
            case TVSHOW_BATTLE_UPDATE:
                curShow->battleUpdate.language = TV_GetStringLanguage(curShow->battleUpdate.playerName);
                curShow->battleUpdate.linkOpponentLanguage = TV_GetStringLanguage(curShow->battleUpdate.linkOpponentName);
                break;
            case TVSHOW_FAN_CLUB_SPECIAL:
                curShow->fanClubSpecial.language = TV_GetStringLanguage(curShow->fanClubSpecial.playerName);
                curShow->fanClubSpecial.idolNameLanguage = TV_GetStringLanguage(curShow->fanClubSpecial.idolName);
                break;
            case TVSHOW_CONTEST_LIVE_UPDATES_2:
                curShow->contestLiveUpdates2.language = TV_GetStringLanguage(curShow->contestLiveUpdates2.playerName);
                curShow->contestLiveUpdates2.pokemonNameLanguage = TV_GetStringLanguage(curShow->contestLiveUpdates2.nickname);
                break;

            case TVSHOW_POKEMON_TODAY_CAUGHT:
                curShow->pokemonToday.language = TV_GetStringLanguage(curShow->pokemonToday.playerName);
                curShow->pokemonToday.language2 = TV_GetStringLanguage(curShow->pokemonToday.nickname);
                break;
            case TVSHOW_SMART_SHOPPER:
                curShow->smartshopperShow.language = TV_GetStringLanguage(curShow->smartshopperShow.playerName);
                break;
            case TVSHOW_POKEMON_TODAY_FAILED:
                curShow->pokemonTodayFailed.language = TV_GetStringLanguage(curShow->pokemonTodayFailed.playerName);
                break;
            case TVSHOW_FISHING_ADVICE:
                curShow->pokemonAngler.language = TV_GetStringLanguage(curShow->pokemonAngler.playerName);
                break;
            case TVSHOW_WORLD_OF_MASTERS:
                curShow->worldOfMasters.language = TV_GetStringLanguage(curShow->worldOfMasters.playerName);
                break;
            case TVSHOW_TREND_WATCHER:
                curShow->trendWatcher.language = TV_GetStringLanguage(curShow->trendWatcher.playerName);
                break;
            case TVSHOW_BREAKING_NEWS:
                curShow->breakingNews.language = TV_GetStringLanguage(curShow->breakingNews.playerName);
                break;
            case TVSHOW_BATTLE_SEMINAR:
                curShow->battleSeminar.language = TV_GetStringLanguage(curShow->battleSeminar.playerName);
                break;
            case TVSHOW_FIND_THAT_GAMER:
            case TVSHOW_TRAINER_FAN_CLUB:
                curShow->trainerFanClub.language = TV_GetStringLanguage(curShow->trainerFanClub.playerName);
                break;
            case TVSHOW_CUTIES:
                curShow->cuties.language = TV_GetStringLanguage(curShow->cuties.playerName);
                curShow->cuties.pokemonNameLanguage = TV_GetStringLanguage(curShow->cuties.nickname);
                break;
            case TVSHOW_TODAYS_RIVAL_TRAINER:
            case TVSHOW_SECRET_BASE_VISIT:
            case TVSHOW_FRONTIER:
                curShow->rivalTrainer.language = TV_GetStringLanguage(curShow->rivalTrainer.playerName);
                break;
            case TVSHOW_TREASURE_INVESTIGATORS:
            case TVSHOW_LOTTO_WINNER:
            case TVSHOW_NUMBER_ONE:
                curShow->treasureInvestigators.language = TV_GetStringLanguage(curShow->treasureInvestigators.playerName);
                break;
            case TVSHOW_SECRET_BASE_SECRETS:
                curShow->secretBaseSecrets.language = TV_GetStringLanguage(curShow->secretBaseSecrets.playerName);
                curShow->secretBaseSecrets.baseOwnersNameLanguage = TV_GetStringLanguage(curShow->secretBaseSecrets.baseOwnersName);
                break;
            case TVSHOW_SAFARI_FAN_CLUB:
                curShow->safariFanClub.language = TV_GetStringLanguage(curShow->safariFanClub.playerName);
                break;
            case TVSHOW_MASS_OUTBREAK:
                break;
        }
    }
}

void sub_80F14F8(TVShow *shows)
{
    int i;

    for (i = 0; i < 24; i ++)
    {
        switch (shows[i].common.kind)
        {
            case TVSHOW_WORLD_OF_MASTERS:
                if (shows[i].worldOfMasters.location > 0x58)
                {
                    memset(&shows[i], 0, sizeof(TVShow));
                }
                break;
            case TVSHOW_POKEMON_TODAY_FAILED:
                if (shows[i].pokemonTodayFailed.location > 0x58)
                {
                    memset(&shows[i], 0, sizeof(TVShow));
                }
                break;
        }
    }
}

void DoTVShow(void)
{
    if (gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004].common.active)
    {
        switch (gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004].common.kind)
        {
            case TVSHOW_FAN_CLUB_LETTER:
                DoTVShowPokemonFanClubLetter();
                break;
            case TVSHOW_RECENT_HAPPENINGS:
                DoTVShowRecentHappenings();
                break;
            case TVSHOW_PKMN_FAN_CLUB_OPINIONS:
                DoTVShowPokemonFanClubOpinions();
                break;
            case TVSHOW_UNKN_SHOWTYPE_04:
                DoTVShowDummiedOut();
                break;
            case TVSHOW_MASS_OUTBREAK:
                DoTVShowPokemonNewsMassOutbreak();
                break;
            case TVSHOW_BRAVO_TRAINER_POKEMON_PROFILE:
                DoTVShowBravoTrainerPokemonProfile();
                break;
            case TVSHOW_BRAVO_TRAINER_BATTLE_TOWER_PROFILE:
                DoTVShowBravoTrainerBattleTower();
                break;
            case TVSHOW_POKEMON_TODAY_CAUGHT:
                DoTVShowPokemonTodaySuccessfulCapture();
                break;
            case TVSHOW_SMART_SHOPPER:
                DoTVShowTodaysSmartShopper();
                break;
            case TVSHOW_NAME_RATER_SHOW:
                DoTVShowTheNameRaterShow();
                break;
            case TVSHOW_CONTEST_LIVE_UPDATES:
                DoTVShowPokemonContestLiveUpdates();
                break;
            case TVSHOW_BATTLE_UPDATE:
                DoTVShowPokemonBattleUpdate();
                break;
            case TVSHOW_3_CHEERS_FOR_POKEBLOCKS:
                DoTVShow3CheersForPokeblocks();
                break;
            case TVSHOW_POKEMON_TODAY_FAILED:
                DoTVShowPokemonTodayFailedCapture();
                break;
            case TVSHOW_FISHING_ADVICE:
                DoTVShowPokemonAngler();
                break;
            case TVSHOW_WORLD_OF_MASTERS:
                DoTVShowTheWorldOfMasters();
                break;
            case TVSHOW_TODAYS_RIVAL_TRAINER:
                DoTVShowTodaysRivalTrainer();
                break;
            case TVSHOW_TREND_WATCHER:
                DoTVShowDewfordTrendWatcherNetwork();
                break;
            case TVSHOW_TREASURE_INVESTIGATORS:
                DoTVShowHoennTreasureInvestigators();
                break;
            case TVSHOW_FIND_THAT_GAMER:
                DoTVShowFindThatGamer();
                break;
            case TVSHOW_BREAKING_NEWS:
                DoTVShowBreakingNewsTV();
                break;
            case TVSHOW_SECRET_BASE_VISIT:
                DoTVShowSecretBaseVisit();
                break;
            case TVSHOW_LOTTO_WINNER:
                DoTVShowPokemonLotteryWinnerFlashReport();
                break;
            case TVSHOW_BATTLE_SEMINAR:
                DoTVShowThePokemonBattleSeminar();
                break;
            case TVSHOW_FAN_CLUB_SPECIAL:
                DoTVShowTrainerFanClubSpecial();
                break;
            case TVSHOW_TRAINER_FAN_CLUB:
                DoTVShowTrainerFanClub();
                break;
            case TVSHOW_CUTIES:
                DoTVShowSpotTheCuties();
                break;
            case TVSHOW_FRONTIER:
                DoTVShowPokemonNewsBattleFrontier();
                break;
            case TVSHOW_NUMBER_ONE:
                DoTVShowWhatsNo1InHoennToday();
                break;
            case TVSHOW_SECRET_BASE_SECRETS:
                DoTVShowSecretBaseSecrets();
                break;
            case TVSHOW_SAFARI_FAN_CLUB:
                DoTVShowSafariFanClub();
                break;
            case TVSHOW_CONTEST_LIVE_UPDATES_2:
                DoTVShowPokemonContestLiveUpdates2();
                break;
        }
    }
}

static void DoTVShowBravoTrainerPokemonProfile(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->bravoTrainer.playerName, show->bravoTrainer.language);
            CopyContestCategoryToStringVar(1, show->bravoTrainer.contestCategory);
            CopyContestRankToStringVar(2, show->bravoTrainer.contestRank);
            if (!StringCompare(gSpeciesNames[show->bravoTrainer.species], show->bravoTrainer.pokemonNickname))
                sTVShowState = 8;
            else
                sTVShowState = 1;
            break;
        case 1:
            StringCopy(gStringVar1, gSpeciesNames[show->bravoTrainer.species]);
            TVShowConvertInternationalString(gStringVar2, show->bravoTrainer.pokemonNickname, show->bravoTrainer.pokemonNameLanguage);
            CopyContestCategoryToStringVar(2, show->bravoTrainer.contestCategory);
            sTVShowState = 2;
            break;
        case 2:
            TVShowConvertInternationalString(gStringVar1, show->bravoTrainer.playerName, show->bravoTrainer.language);
            if (show->bravoTrainer.contestResult == 0) // placed first
                sTVShowState = 3;
            else
                sTVShowState = 4;
            break;
        case 3:
            TVShowConvertInternationalString(gStringVar1, show->bravoTrainer.playerName, show->bravoTrainer.language);
            CopyEasyChatWord(gStringVar2, show->bravoTrainer.words[0]);
            TV_PrintIntToStringVar(2, show->bravoTrainer.contestResult + 1);
            sTVShowState = 5;
            break;
        case 4:
            TVShowConvertInternationalString(gStringVar1, show->bravoTrainer.playerName, show->bravoTrainer.language);
            CopyEasyChatWord(gStringVar2, show->bravoTrainer.words[0]);
            TV_PrintIntToStringVar(2, show->bravoTrainer.contestResult + 1);
            sTVShowState = 5;
            break;
        case 5:
            TVShowConvertInternationalString(gStringVar1, show->bravoTrainer.playerName, show->bravoTrainer.language);
            CopyContestCategoryToStringVar(1, show->bravoTrainer.contestCategory);
            CopyEasyChatWord(gStringVar3, show->bravoTrainer.words[1]);
            if (show->bravoTrainer.move)
                sTVShowState = 6;
            else
                sTVShowState = 7;
            break;
        case 6:
            StringCopy(gStringVar1, gSpeciesNames[show->bravoTrainer.species]);
            StringCopy(gStringVar2, gMoveNames[show->bravoTrainer.move]);
            CopyEasyChatWord(gStringVar3, show->bravoTrainer.words[1]);
            sTVShowState = 7;
            break;
        case 7:
            TVShowConvertInternationalString(gStringVar1, show->bravoTrainer.playerName, show->bravoTrainer.language);
            StringCopy(gStringVar2, gSpeciesNames[show->bravoTrainer.species]);
            TVShowDone();
            break;
        case 8:
            StringCopy(gStringVar1, gSpeciesNames[show->bravoTrainer.species]);
            sTVShowState = 2;
            break;
    }
    ShowFieldMessage(sTVBravoTrainerTextGroup[state]);
}

static void DoTVShowBravoTrainerBattleTower(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch(state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->bravoTrainerTower.trainerName, show->bravoTrainerTower.language);
            StringCopy(gStringVar2, gSpeciesNames[show->bravoTrainerTower.species]);
            if (show->bravoTrainerTower.numFights >= 7)
                sTVShowState = 1;
            else
                sTVShowState = 2;
            break;
        case 1:
            if (show->bravoTrainerTower.btLevel == 50)
            {
                StringCopy(gStringVar1, gText_Lv50);
            }
            else
            {
                StringCopy(gStringVar1, gText_OpenLevel);
            }
            TV_PrintIntToStringVar(1, show->bravoTrainerTower.numFights);
            if (show->bravoTrainerTower.wonTheChallenge == TRUE)
                sTVShowState = 3;
            else
                sTVShowState = 4;
            break;
        case 2:
            TVShowConvertInternationalString(gStringVar1, show->bravoTrainerTower.pokemonName, show->bravoTrainerTower.pokemonNameLanguage);
            TV_PrintIntToStringVar(1, show->bravoTrainerTower.numFights + 1);
            if (show->bravoTrainerTower.interviewResponse == 0)
                sTVShowState = 5;
            else
                sTVShowState = 6;
            break;
        case 3:
            TVShowConvertInternationalString(gStringVar1, show->bravoTrainerTower.pokemonName, show->bravoTrainerTower.pokemonNameLanguage);
            StringCopy(gStringVar2, gSpeciesNames[show->bravoTrainerTower.defeatedSpecies]);
            if (show->bravoTrainerTower.interviewResponse == 0)
                sTVShowState = 5;
            else
                sTVShowState = 6;
            break;
        case 4:
            TVShowConvertInternationalString(gStringVar1, show->bravoTrainerTower.pokemonName, show->bravoTrainerTower.pokemonNameLanguage);
            StringCopy(gStringVar2, gSpeciesNames[show->bravoTrainerTower.defeatedSpecies]);
            if (show->bravoTrainerTower.interviewResponse == 0)
                sTVShowState = 5;
            else
                sTVShowState = 6;
            break;
        case 5:
            TVShowConvertInternationalString(gStringVar1, show->bravoTrainerTower.pokemonName, show->bravoTrainerTower.pokemonNameLanguage);
            sTVShowState = 11;
            break;
        case 6:
            TVShowConvertInternationalString(gStringVar1, show->bravoTrainerTower.pokemonName, show->bravoTrainerTower.pokemonNameLanguage);
            sTVShowState = 11;
            break;
        case 7:
            sTVShowState = 11;
            break;
        case 8:
        case 9:
        case 10:
            TVShowConvertInternationalString(gStringVar1, show->bravoTrainerTower.trainerName, show->bravoTrainerTower.language);
            sTVShowState = 11;
            break;
        case 11:
            CopyEasyChatWord(gStringVar1, show->bravoTrainerTower.words[0]);
            if (show->bravoTrainerTower.interviewResponse == 0)
                sTVShowState = 12;
            else
                sTVShowState = 13;
            break;
        case 12:
        case 13:
            CopyEasyChatWord(gStringVar1, show->bravoTrainerTower.words[0]);
            TVShowConvertInternationalString(gStringVar2, show->bravoTrainerTower.trainerName, show->bravoTrainerTower.language);
            TVShowConvertInternationalString(gStringVar3, show->bravoTrainerTower.pokemonName, show->bravoTrainerTower.pokemonNameLanguage);
            sTVShowState = 14;
            break;
        case 14:
            TVShowConvertInternationalString(gStringVar1, show->bravoTrainerTower.trainerName, show->bravoTrainerTower.language);
            StringCopy(gStringVar2, gSpeciesNames[show->bravoTrainerTower.species]);
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVBravoTrainerBattleTowerTextGroup[state]);
}

static void DoTVShowTodaysSmartShopper(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch(state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->smartshopperShow.playerName, show->smartshopperShow.language);
            GetMapName(gStringVar2, show->smartshopperShow.shopLocation, 0);
            if (show->smartshopperShow.itemAmounts[0] >= 255)
            {
                sTVShowState = 11;
            }
            else
            {
                sTVShowState = 1;
            }
            break;
        case 1:
            TVShowConvertInternationalString(gStringVar1, show->smartshopperShow.playerName, show->smartshopperShow.language);
            StringCopy(gStringVar2, ItemId_GetName(show->smartshopperShow.itemIds[0]));
            TV_PrintIntToStringVar(2, show->smartshopperShow.itemAmounts[0]);
            sTVShowState += 1 + (Random() % 4);
            break;
        case 2:
        case 4:
        case 5:
            if (show->smartshopperShow.itemIds[1] != ITEM_NONE)
            {
                sTVShowState = 6;
            }
            else
            {
                sTVShowState = 10;
            }
            break;
        case 3:
            TV_PrintIntToStringVar(2, show->smartshopperShow.itemAmounts[0] + 1);
            if (show->smartshopperShow.itemIds[1] != ITEM_NONE)
            {
                sTVShowState = 6;
            }
            else
            {
                sTVShowState = 10;
            }
            break;
        case 6:
            StringCopy(gStringVar2, ItemId_GetName(show->smartshopperShow.itemIds[1]));
            TV_PrintIntToStringVar(2, show->smartshopperShow.itemAmounts[1]);
            if (show->smartshopperShow.itemIds[2] != ITEM_NONE)
            {
                sTVShowState = 7;
            }
            else if (show->smartshopperShow.priceReduced == TRUE)
            {
                sTVShowState = 8;
            }
            else
            {
                sTVShowState = 9;
            }
            break;
        case 7:
            StringCopy(gStringVar2, ItemId_GetName(show->smartshopperShow.itemIds[2]));
            TV_PrintIntToStringVar(2, show->smartshopperShow.itemAmounts[2]);
            if (show->smartshopperShow.priceReduced == TRUE)
            {
                sTVShowState = 8;
            }
            else
            {
                sTVShowState = 9;
            }
            break;
        case 8:
            if (show->smartshopperShow.itemAmounts[0] >= 255)
            {
                sTVShowState = 12;
            }
            else
            {
                sTVShowState = 9;
            }
            break;
        case 9:
            sub_80EF40C(1, show);
            TVShowDone();
            break;
        case 10:
            if (show->smartshopperShow.priceReduced == TRUE)
            {
                sTVShowState = 8;
            }
            else
            {
                sTVShowState = 9;
            }
            break;
        case 11:
            TVShowConvertInternationalString(gStringVar1, show->smartshopperShow.playerName, show->smartshopperShow.language);
            StringCopy(gStringVar2, ItemId_GetName(show->smartshopperShow.itemIds[0]));
            if (show->smartshopperShow.priceReduced == TRUE)
            {
                sTVShowState = 8;
            }
            else
            {
                sTVShowState = 12;
            }
            break;
        case 12:
            TVShowConvertInternationalString(gStringVar1, show->smartshopperShow.playerName, show->smartshopperShow.language);
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVTodaysSmartShopperTextGroup[state]);
}

static void DoTVShowTheNameRaterShow(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->nameRaterShow.trainerName, show->nameRaterShow.language);
            StringCopy(gStringVar2, gSpeciesNames[show->nameRaterShow.species]);
            TVShowConvertInternationalString(gStringVar3, show->nameRaterShow.pokemonName, show->nameRaterShow.pokemonNameLanguage);
            sTVShowState = TV_GetNicknameSumMod8(show) + 1;
            break;
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            if (show->nameRaterShow.random == 0)
            {
                sTVShowState = 9;
            }
            else if (show->nameRaterShow.random == 1)
            {
                sTVShowState = 10;
            }
            else if (show->nameRaterShow.random == 2)
            {
                sTVShowState = 11;
            }
            break;
        case 2:
            TVShowConvertInternationalString(gStringVar1, show->nameRaterShow.trainerName, show->nameRaterShow.language);
            if (show->nameRaterShow.random == 0)
            {
                sTVShowState = 9;
            }
            else if (show->nameRaterShow.random == 1)
            {
                sTVShowState = 10;
            }
            else if (show->nameRaterShow.random == 2)
            {
                sTVShowState = 11;
            }
            break;
        case 9:
        case 10:
        case 11:
            TVShowConvertInternationalString(gStringVar1, show->nameRaterShow.pokemonName, show->nameRaterShow.pokemonNameLanguage);
            TV_GetNicknameSubstring(1, 0, 0, 1, 0, show);
            TV_GetNicknameSubstring(2, 1, 0, 1, 0, show);
            sTVShowState = 12;
            break;
        case 13:
            TVShowConvertInternationalString(gStringVar1, show->nameRaterShow.trainerName, show->nameRaterShow.language);
            TV_GetNicknameSubstring(1, 0, 2, 0, 0, show);
            TV_GetNicknameSubstring(2, 0, 3, 1, 0, show);
            sTVShowState = 14;
            break;
        case 14:
            TV_GetNicknameSubstring(1, 0, 2, 1, 0, show);
            TV_GetNicknameSubstring(2, 0, 3, 0, 0, show);
            sTVShowState = 18;
            break;
        case 15:
            TV_GetNicknameSubstring(0, 0, 2, 1, 0, show);
            StringCopy(gStringVar2, gSpeciesNames[show->nameRaterShow.species]);
            TV_GetNicknameSubstring(2, 0, 3, 2, show->nameRaterShow.species, show);
            sTVShowState = 16;
            break;
        case 16:
            TV_GetNicknameSubstring(0, 0, 2, 2, show->nameRaterShow.species, show);
            TV_GetNicknameSubstring(2, 0, 3, 1, 0, show);
            sTVShowState = 17;
            break;
        case 17:
            TV_GetNicknameSubstring(0, 0, 2, 1, 0, show);
            StringCopy(gStringVar2, gSpeciesNames[show->nameRaterShow.randomSpecies]);
            TV_GetNicknameSubstring(2, 0, 3, 2, show->nameRaterShow.randomSpecies, show);
            sTVShowState = 18;
            break;
        case 12:
            state = 18;
            sTVShowState = 18;
        case 18:
            TVShowConvertInternationalString(gStringVar1, show->nameRaterShow.pokemonName, show->nameRaterShow.pokemonNameLanguage);
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVNameRaterTextGroup[state]);
}

static void DoTVShowPokemonTodaySuccessfulCapture(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->pokemonToday.playerName, show->pokemonToday.language);
            StringCopy(gStringVar2, gSpeciesNames[show->pokemonToday.species]);
            TVShowConvertInternationalString(gStringVar3, show->pokemonToday.nickname, show->pokemonToday.language2);
            if (show->pokemonToday.ball == ITEM_MASTER_BALL)
            {
                sTVShowState = 5;
            }
            else
            {
                sTVShowState = 1;
            }
            break;
        case 1:
            sTVShowState = 2;
            break;
        case 2:
            StringCopy(gStringVar2, ItemId_GetName(show->pokemonToday.ball));
            TV_PrintIntToStringVar(2, show->pokemonToday.nBallsUsed);
            if (show->pokemonToday.nBallsUsed < 4)
            {
                sTVShowState = 3;
            }
            else
            {
                sTVShowState = 4;
            }
            break;
        case 3:
            TVShowConvertInternationalString(gStringVar1, show->pokemonToday.playerName, show->pokemonToday.language);
            StringCopy(gStringVar2, gSpeciesNames[show->pokemonToday.species]);
            TVShowConvertInternationalString(gStringVar3, show->pokemonToday.nickname, show->pokemonToday.language2);
            sTVShowState = 6;
            break;
        case 4:
            sTVShowState = 6;
            break;
        case 5:
            TVShowConvertInternationalString(gStringVar1, show->pokemonToday.playerName, show->pokemonToday.language);
            StringCopy(gStringVar2, gSpeciesNames[show->pokemonToday.species]);
            sTVShowState = 6;
            break;
        case 6:
            TVShowConvertInternationalString(gStringVar1, show->pokemonToday.playerName, show->pokemonToday.language);
            StringCopy(gStringVar2, gSpeciesNames[show->pokemonToday.species]);
            TVShowConvertInternationalString(gStringVar3, show->pokemonToday.nickname, show->pokemonToday.language2);
            sTVShowState += 1 + (Random() % 4);
            break;
        case 7:
        case 8:
            StringCopy(gStringVar1, gSpeciesNames[show->pokemonToday.species]);
            TVShowConvertInternationalString(gStringVar2, show->pokemonToday.nickname, show->pokemonToday.language2);
            TV_GetSomeOtherSpeciesAlreadySeenByPlayer_AndPrintName(2, show->pokemonToday.species);
            sTVShowState = 11;
            break;
        case 9:
        case 10:
            StringCopy(gStringVar1, gSpeciesNames[show->pokemonToday.species]);
            TVShowConvertInternationalString(gStringVar2, show->pokemonToday.nickname, show->pokemonToday.language2);
            sTVShowState = 11;
            break;
        case 11:
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVPokemonTodaySuccessfulTextGroup[state]);
}

static void DoTVShowPokemonTodayFailedCapture(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->pokemonTodayFailed.playerName, show->pokemonTodayFailed.language);
            StringCopy(gStringVar2, gSpeciesNames[show->pokemonTodayFailed.species]);
            sTVShowState = 1;
            break;
        case 1:
            TVShowConvertInternationalString(gStringVar1, show->pokemonTodayFailed.playerName, show->pokemonTodayFailed.language);
            GetMapName(gStringVar2, show->pokemonTodayFailed.location, 0);
            StringCopy(gStringVar3, gSpeciesNames[show->pokemonTodayFailed.species2]);
            if (show->pokemonTodayFailed.outcome == 1)
            {
                sTVShowState = 3;
            }
            else
            {
                sTVShowState = 2;
            }
            break;
        case 2:
        case 3:
            TVShowConvertInternationalString(gStringVar1, show->pokemonTodayFailed.playerName, show->pokemonTodayFailed.language);
            TV_PrintIntToStringVar(1, show->pokemonTodayFailed.nBallsUsed);
            if (Random() % 3 == 0)
            {
                sTVShowState = 5;
            }
            else
            {
                sTVShowState = 4;
            }
            break;
        case 4:
        case 5:
            TVShowConvertInternationalString(gStringVar1, show->pokemonTodayFailed.playerName, show->pokemonTodayFailed.language);
            sTVShowState = 6;
            break;
        case 6:
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVPokemonTodayFailedTextGroup[state]);
}

static void DoTVShowPokemonFanClubLetter(void)
{
    TVShow *show;
    u8 state;
    u16 rval;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->fanclubLetter.playerName, show->fanclubLetter.language);
            StringCopy(gStringVar2, gSpeciesNames[show->fanclubLetter.species]);
            sTVShowState = 50;
            break;
        case 1:
            rval = (Random() % 4) + 1;
            if (rval == 1)
                sTVShowState = 2;
            else
                sTVShowState = rval + 2;
            break;
        case 2:
            sTVShowState = 51;
            break;
        case 3:
            sTVShowState += (Random() % 3) + 1;
            break;
        case 4:
        case 5:
        case 6:
            TV_FanClubLetter_RandomWordToStringVar3(show);
            sTVShowState = 7;
            break;
        case 7:
            rval = (Random() % 0x1f) + 0x46;
            TV_PrintIntToStringVar(2, rval);
            TVShowDone();
            break;
        case 50:
            ConvertEasyChatWordsToString(gStringVar4, show->fanclubLetter.words, 2, 2);
            ShowFieldMessage(gStringVar4);
            sTVShowState = 1;
            return;
        case 51:
            ConvertEasyChatWordsToString(gStringVar4, show->fanclubLetter.words, 2, 2);
            ShowFieldMessage(gStringVar4);
            sTVShowState = 3;
            return;
    }
    ShowFieldMessage(sTVFanClubTextGroup[state]);
}

static void DoTVShowRecentHappenings(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->recentHappenings.playerName, show->recentHappenings.language);
            TV_FanClubLetter_RandomWordToStringVar3(show);
            sTVShowState = 50;
            break;
        case 1:
            sTVShowState += 1 + (Random() % 3);
            break;
        case 2:
        case 3:
        case 4:
            sTVShowState = 5;
            break;
        case 5:
            TVShowDone();
            break;
        case 50:
            ConvertEasyChatWordsToString(gStringVar4, show->recentHappenings.words, 2, 2);
            ShowFieldMessage(gStringVar4);
            sTVShowState = 1;
            return;
    }
    ShowFieldMessage(sTVRecentHappeninssTextGroup[state]);
}

static void DoTVShowPokemonFanClubOpinions(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->fanclubOpinions.playerName, show->fanclubOpinions.language);
            StringCopy(gStringVar2, gSpeciesNames[show->fanclubOpinions.species]);
            TVShowConvertInternationalString(gStringVar3, show->fanclubOpinions.nickname, show->fanclubOpinions.pokemonNameLanguage);
            sTVShowState = show->fanclubOpinions.questionAsked + 1;
            break;
        case 1:
        case 2:
        case 3:
            TVShowConvertInternationalString(gStringVar1, show->fanclubOpinions.playerName, show->fanclubOpinions.language);
            StringCopy(gStringVar2, gSpeciesNames[show->fanclubOpinions.species]);
            CopyEasyChatWord(gStringVar3, show->fanclubOpinions.words[0]);
            sTVShowState = 4;
            break;
        case 4:
            TVShowConvertInternationalString(gStringVar1, show->fanclubOpinions.playerName, show->fanclubOpinions.language);
            CopyEasyChatWord(gStringVar3, show->fanclubOpinions.words[1]);
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVFanClubOpinionsTextGroup[state]);
}

static void DoTVShowDummiedOut(void)
{

}

static void DoTVShowPokemonNewsMassOutbreak(void)
{
    TVShow *show;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    GetMapName(gStringVar1, show->massOutbreak.locationMapNum, 0);
    StringCopy(gStringVar2, gSpeciesNames[show->massOutbreak.species]);
    TVShowDone();
    StartMassOutbreak();
    ShowFieldMessage(sTVMassOutbreakTextGroup[sTVShowState]);
}

static void DoTVShowPokemonContestLiveUpdates(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case  0:
            sub_818E868(gStringVar1, show->contestLiveUpdates.category);
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            TVShowConvertInternationalString(gStringVar3, show->contestLiveUpdates.playerName, show->contestLiveUpdates.language);
            if (show->contestLiveUpdates.round1Rank == show->contestLiveUpdates.round2Rank)
            {
                if (show->contestLiveUpdates.round1Rank == 0)
                {
                    sTVShowState = 1;
                }
                else
                {
                    sTVShowState = 3;
                }
            }
            else if (show->contestLiveUpdates.round1Rank > show->contestLiveUpdates.round2Rank)
            {
                sTVShowState = 2;
            }
            else
            {
                sTVShowState = 4;
            }
            break;
        case  1:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            switch (show->contestLiveUpdates.appealFlags1)
            {
                case 0x01:
                    sTVShowState = 8;
                    break;
                case 0x02:
                    sTVShowState = 5;
                    break;
                case 0x04:
                    sTVShowState = 14;
                    break;
                case 0x08:
                    sTVShowState = 7;
                    break;
                case 0x10:
                    sTVShowState = 6;
                    break;
                case 0x20:
                    sTVShowState = 20;
                    break;
                case 0x40:
                    sTVShowState = 21;
                    break;
                case 0x80:
                    sTVShowState = 22;
                    break;
            }
            break;
        case  2:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            switch (show->contestLiveUpdates.appealFlags1)
            {
                case 0x01:
                    sTVShowState = 8;
                    break;
                case 0x02:
                    sTVShowState = 5;
                    break;
                case 0x04:
                    sTVShowState = 14;
                    break;
                case 0x08:
                    sTVShowState = 7;
                    break;
                case 0x10:
                    sTVShowState = 6;
                    break;
                case 0x20:
                    sTVShowState = 20;
                    break;
                case 0x40:
                    sTVShowState = 21;
                    break;
                case 0x80:
                    sTVShowState = 22;
                    break;
            }
            break;
        case  3:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            TVShowConvertInternationalString(gStringVar3, show->contestLiveUpdates.playerName, show->contestLiveUpdates.language);
            switch (show->contestLiveUpdates.appealFlags1)
            {
                case 0x01:
                    sTVShowState = 8;
                    break;
                case 0x02:
                    sTVShowState = 5;
                    break;
                case 0x04:
                    sTVShowState = 14;
                    break;
                case 0x08:
                    sTVShowState = 7;
                    break;
                case 0x10:
                    sTVShowState = 6;
                    break;
                case 0x20:
                    sTVShowState = 20;
                    break;
                case 0x40:
                    sTVShowState = 21;
                    break;
                case 0x80:
                    sTVShowState = 22;
                    break;
            }
            break;
        case  4:
            switch (show->contestLiveUpdates.category)
            {
                case 0:
                    StringCopy(gStringVar1, gText_Cool);
                    break;
                case 1:
                    StringCopy(gStringVar1, gText_Beauty);
                    break;
                case 2:
                    StringCopy(gStringVar1, gText_Cute);
                    break;
                case 3:
                    StringCopy(gStringVar1, gText_Smart);
                    break;
                case 4:
                    StringCopy(gStringVar1, gText_Tough);
                    break;
            }
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            switch (show->contestLiveUpdates.appealFlags1)
            {
                case 0x01:
                    sTVShowState = 8;
                    break;
                case 0x02:
                    sTVShowState = 5;
                    break;
                case 0x04:
                    sTVShowState = 14;
                    break;
                case 0x08:
                    sTVShowState = 7;
                    break;
                case 0x10:
                    sTVShowState = 6;
                    break;
                case 0x20:
                    sTVShowState = 20;
                    break;
                case 0x40:
                    sTVShowState = 21;
                    break;
                case 0x80:
                    sTVShowState = 22;
                    break;
            }
            break;
        case  5:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            sTVShowState = 23;
            break;
        case  6:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            sTVShowState = 23;
            break;
        case  7:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            sTVShowState = 23;
            break;
        case  8:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            switch (show->contestLiveUpdates.category)
            {
                case 0:
                    sTVShowState = 9;
                    break;
                case 1:
                    sTVShowState = 10;
                    break;
                case 2:
                    sTVShowState = 11;
                    break;
                case 3:
                    sTVShowState = 12;
                    break;
                case 4:
                    sTVShowState = 13;
                    break;
            }
            break;
        case  9:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            sTVShowState = 23;
            break;
        case 10:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            sTVShowState = 23;
            break;
        case 11:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            sTVShowState = 23;
            break;
        case 12:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            sTVShowState = 23;
            break;
        case 13:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            sTVShowState = 23;
            break;
        case 14:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            switch (show->contestLiveUpdates.category)
            {
                case 0:
                    sTVShowState = 15;
                    break;
                case 1:
                    sTVShowState = 16;
                    break;
                case 2:
                    sTVShowState = 17;
                    break;
                case 3:
                    sTVShowState = 18;
                    break;
                case 4:
                    sTVShowState = 19;
                    break;
            }
            break;
        case 15:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            sTVShowState = 23;
            break;
        case 16:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            sTVShowState = 23;
            break;
        case 17:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            sTVShowState = 23;
            break;
        case 18:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            sTVShowState = 23;
            break;
        case 19:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            sTVShowState = 23;
            break;
        case 20:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            sTVShowState = 23;
            break;
        case 21:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            sTVShowState = 23;
            break;
        case 22:
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            StringCopy(gStringVar3, gMoveNames[show->contestLiveUpdates.move]);
            sTVShowState = 23;
            break;
        case 23:
            StringCopy(gStringVar1, gSpeciesNames[show->contestLiveUpdates.species]);
            TVShowConvertInternationalString(gStringVar2, show->contestLiveUpdates.winningTrainerName, show->contestLiveUpdates.winningTrainerLanguage);
            StringCopy(gStringVar3, gSpeciesNames[show->contestLiveUpdates.winningSpecies]);
            switch (show->contestLiveUpdates.appealFlags2)
            {
                case 0x01:
                    sTVShowState = 31;
                    break;
                case 0x02:
                    sTVShowState = 30;
                    break;
                case 0x04:
                    sTVShowState = 29;
                    break;
                case 0x08:
                    sTVShowState = 28;
                    break;
                case 0x10:
                    sTVShowState = 27;
                    break;
                case 0x20:
                    sTVShowState = 26;
                    break;
                case 0x40:
                    sTVShowState = 25;
                    break;
                case 0x80:
                    sTVShowState = 24;
                    break;
            }
            break;
        case 24:
            StringCopy(gStringVar1, gSpeciesNames[show->contestLiveUpdates.winningSpecies]);
            sTVShowState = 32;
            break;
        case 25:
            TVShowConvertInternationalString(gStringVar1, show->contestLiveUpdates.winningTrainerName, show->contestLiveUpdates.winningTrainerLanguage);
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.winningSpecies]);
            sTVShowState = 32;
            break;
        case 28:
            sTVShowState = 32;
            break;
        case 29:
            TVShowConvertInternationalString(gStringVar1, show->contestLiveUpdates.playerName, show->contestLiveUpdates.language);
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            TVShowConvertInternationalString(gStringVar3, show->contestLiveUpdates.winningTrainerName, show->contestLiveUpdates.winningTrainerLanguage);
            sTVShowState = 32;
            break;
        case 26:
        case 27:
        case 30:
        case 31:
            TVShowConvertInternationalString(gStringVar1, show->contestLiveUpdates.winningTrainerName, show->contestLiveUpdates.winningTrainerLanguage);
            sTVShowState = 32;
            break;
        case 32:

            TVShowConvertInternationalString(gStringVar1, show->contestLiveUpdates.playerName, show->contestLiveUpdates.language);
            StringCopy(gStringVar2, gSpeciesNames[show->contestLiveUpdates.species]);
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVContestLiveUpdatesTextGroup[state]);
}

static void DoTVShowPokemonBattleUpdate(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            switch (show->battleUpdate.battleType)
            {
                case 0:
                case 1:
                    sTVShowState = 1;
                    break;
                case 2:
                    sTVShowState = 5;
                    break;
            }
            break;
        case 1:
            TVShowConvertInternationalString(gStringVar1, show->battleUpdate.playerName, show->battleUpdate.language);
            TVShowConvertInternationalString(gStringVar2, show->battleUpdate.linkOpponentName, show->battleUpdate.linkOpponentLanguage);
            if (show->battleUpdate.battleType == 0)
            {
                StringCopy(gStringVar3, gText_Single);
            }
            else
            {
                StringCopy(gStringVar3, gText_Double);
            }
            sTVShowState = 2;
            break;
        case 2:
            TVShowConvertInternationalString(gStringVar1, show->battleUpdate.playerName, show->battleUpdate.language);
            StringCopy(gStringVar2, gSpeciesNames[show->battleUpdate.speciesPlayer]);
            StringCopy(gStringVar3, gMoveNames[show->battleUpdate.move]);
            sTVShowState = 3;
            break;
        case 3:
            TVShowConvertInternationalString(gStringVar1, show->battleUpdate.linkOpponentName, show->battleUpdate.linkOpponentLanguage);
            StringCopy(gStringVar2, gSpeciesNames[show->battleUpdate.speciesOpponent]);
            sTVShowState = 4;
            break;
        case 4:
            TVShowConvertInternationalString(gStringVar1, show->battleUpdate.playerName, show->battleUpdate.language);
            TVShowConvertInternationalString(gStringVar2, show->battleUpdate.linkOpponentName, show->battleUpdate.linkOpponentLanguage);
            TVShowDone();
            break;
        case 5:
            TVShowConvertInternationalString(gStringVar1, show->battleUpdate.playerName, show->battleUpdate.language);
            TVShowConvertInternationalString(gStringVar2, show->battleUpdate.linkOpponentName, show->battleUpdate.linkOpponentLanguage);
            sTVShowState = 6;
            break;
        case 6:
            TVShowConvertInternationalString(gStringVar1, show->battleUpdate.playerName, show->battleUpdate.language);
            StringCopy(gStringVar2, gSpeciesNames[show->battleUpdate.speciesPlayer]);
            StringCopy(gStringVar3, gMoveNames[show->battleUpdate.move]);
            sTVShowState = 7;
            break;
        case 7:
            TVShowConvertInternationalString(gStringVar1, show->battleUpdate.playerName, show->battleUpdate.language);
            TVShowConvertInternationalString(gStringVar2, show->battleUpdate.linkOpponentName, show->battleUpdate.linkOpponentLanguage);
            StringCopy(gStringVar3, gSpeciesNames[show->battleUpdate.speciesOpponent]);
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVPokemonBattleUpdateTextGroup[state]);
}

static void DoTVShow3CheersForPokeblocks(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->threeCheers.playerName, show->threeCheers.language);
            if (show->threeCheers.sheen > 20)
            {
                sTVShowState = 1;
            }
            else
            {
                sTVShowState = 3;
            }
            break;
        case 1:
            switch (show->threeCheers.flavor)
            {
                case 0:
                    StringCopy(gStringVar1, gText_Spicy2);
                    break;
                case 1:
                    StringCopy(gStringVar1, gText_Dry2);
                    break;
                case 2:
                    StringCopy(gStringVar1, gText_Sweet2);
                    break;
                case 3:
                    StringCopy(gStringVar1, gText_Bitter2);
                    break;
                case 4:
                    StringCopy(gStringVar1, gText_Sour2);
                    break;
            }
            if (show->threeCheers.sheen > 24)
            {
                StringCopy(gStringVar2, gText_Excellent);
            } else if (show->threeCheers.sheen > 22)
            {
                StringCopy(gStringVar2, gText_VeryGood);
            }
            else
            {
                StringCopy(gStringVar2, gText_Good);
            }
            TVShowConvertInternationalString(gStringVar3, show->threeCheers.playerName, show->threeCheers.language);
            sTVShowState = 2;
            break;
        case 2:
            TVShowConvertInternationalString(gStringVar1, show->threeCheers.worstBlenderName, show->threeCheers.worstBlenderLanguage);
            sTVShowState = 5;
            break;
        case 3:
            switch (show->threeCheers.flavor)
            {
                case 0:
                    StringCopy(gStringVar1, gText_Spicy2);
                    break;
                case 1:
                    StringCopy(gStringVar1, gText_Dry2);
                    break;
                case 2:
                    StringCopy(gStringVar1, gText_Sweet2);
                    break;
                case 3:
                    StringCopy(gStringVar1, gText_Bitter2);
                    break;
                case 4:
                    StringCopy(gStringVar1, gText_Sour2);
                    break;
            }
            if (show->threeCheers.sheen > 16)
            {
                StringCopy(gStringVar2, gText_SoSo);
            } else if (show->threeCheers.sheen > 13)
            {
                StringCopy(gStringVar2, gText_Bad);
            }
            else
            {
                StringCopy(gStringVar2, gText_TheWorst);
            }
            TVShowConvertInternationalString(gStringVar3, show->threeCheers.playerName, show->threeCheers.language);
            sTVShowState = 4;
            break;
        case 4:
            TVShowConvertInternationalString(gStringVar1, show->threeCheers.worstBlenderName, show->threeCheers.worstBlenderLanguage);
            TVShowConvertInternationalString(gStringVar2, show->threeCheers.playerName, show->threeCheers.language);
            sTVShowState = 5;
            break;
        case 5:
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTV3CheersForPokeblocksTextGroup[state]);
}

void DoTVShowInSearchOfTrainers(void)
{
    u8 state;

    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            GetMapName(gStringVar1, gSaveBlock1Ptr->gabbyAndTyData.mapnum, 0);
            if (gSaveBlock1Ptr->gabbyAndTyData.battleNum > 1)
            {
                sTVShowState = 1;
            }
            else
            {
                sTVShowState = 2;
            }
            break;
        case 1:
            sTVShowState = 2;
            break;
        case 2:
            if (!gSaveBlock1Ptr->gabbyAndTyData.battleTookMoreThanOneTurn)
            {
                sTVShowState = 4;
            }
            else if (gSaveBlock1Ptr->gabbyAndTyData.playerThrewABall)
            {
                sTVShowState = 5;
            }
            else if (gSaveBlock1Ptr->gabbyAndTyData.playerUsedAnItem)
            {
                sTVShowState = 6;
            }
            else if (gSaveBlock1Ptr->gabbyAndTyData.playerLostAMon)
            {
                sTVShowState = 7;
            }
            else
            {
                sTVShowState = 3;
            }
            break;
        case 3:
            StringCopy(gStringVar1, gSpeciesNames[gSaveBlock1Ptr->gabbyAndTyData.mon1]);
            StringCopy(gStringVar2, gMoveNames[gSaveBlock1Ptr->gabbyAndTyData.lastMove]);
            StringCopy(gStringVar3, gSpeciesNames[gSaveBlock1Ptr->gabbyAndTyData.mon2]);
            sTVShowState = 8;
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            sTVShowState = 8;
            break;
        case 8:
            CopyEasyChatWord(gStringVar1, gSaveBlock1Ptr->gabbyAndTyData.quote[0]);
            StringCopy(gStringVar2, gSpeciesNames[gSaveBlock1Ptr->gabbyAndTyData.mon1]);
            StringCopy(gStringVar3, gSpeciesNames[gSaveBlock1Ptr->gabbyAndTyData.mon2]);
            gSpecialVar_Result = TRUE;
            sTVShowState = 0;
            TakeTVShowInSearchOfTrainersOffTheAir();
            break;
    }
    ShowFieldMessage(sTVInSearchOfTrainersTextGroup[state]);
}

static void DoTVShowPokemonAngler(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    if (show->pokemonAngler.nBites < show->pokemonAngler.nFails)
    {
        sTVShowState = 0;
    }
    else
    {
        sTVShowState = 1;
    }
    state = sTVShowState;
    switch (state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->pokemonAngler.playerName, show->pokemonAngler.language);
            StringCopy(gStringVar2, gSpeciesNames[show->pokemonAngler.species]);
            TV_PrintIntToStringVar(2, show->pokemonAngler.nFails);
            TVShowDone();
            break;
        case 1:
            TVShowConvertInternationalString(gStringVar1, show->pokemonAngler.playerName, show->pokemonAngler.language);
            StringCopy(gStringVar2, gSpeciesNames[show->pokemonAngler.species]);
            TV_PrintIntToStringVar(2, show->pokemonAngler.nBites);
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVPokemonAnslerTextGroup[state]);
}

static void DoTVShowTheWorldOfMasters(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->worldOfMasters.playerName, show->worldOfMasters.language);
            TV_PrintIntToStringVar(1, show->worldOfMasters.steps);
            TV_PrintIntToStringVar(2, show->worldOfMasters.numPokeCaught);
            sTVShowState = 1;
            break;
        case 1:
            StringCopy(gStringVar1, gSpeciesNames[show->worldOfMasters.species]);
            sTVShowState = 2;
            break;
        case 2:
            TVShowConvertInternationalString(gStringVar1, show->worldOfMasters.playerName, show->worldOfMasters.language);
            GetMapName(gStringVar2, show->worldOfMasters.location, 0);
            StringCopy(gStringVar3, gSpeciesNames[show->worldOfMasters.caughtPoke]);
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVWorldOfMastersTextGroup[state]);
}

static void DoTVShowTodaysRivalTrainer(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            switch (show->rivalTrainer.location)
            {
                default:
                    sTVShowState = 7;
                    break;
                case MAPSEC_SECRET_BASE:
                    sTVShowState = 8;
                    break;
                case MAPSEC_DYNAMIC:
                    switch (show->rivalTrainer.mapLayoutId)
                    {
                        case 0x115 ... 0x117:
                            sTVShowState = 10;
                            break;
                        default:
                            sTVShowState = 9;
                            break;
                    }
                    break;
            }
            break;
        case 7:
            TVShowConvertInternationalString(gStringVar1, show->rivalTrainer.playerName, show->rivalTrainer.language);
            TV_PrintIntToStringVar(1, show->rivalTrainer.dexCount);
            GetMapName(gStringVar3, show->rivalTrainer.location, 0);
            if (show->rivalTrainer.badgeCount != 0)
            {
                sTVShowState = 1;
            }
            else
            {
                sTVShowState = 2;
            }
            break;
        case 8:
            TVShowConvertInternationalString(gStringVar1, show->rivalTrainer.playerName, show->rivalTrainer.language);
            TV_PrintIntToStringVar(1, show->rivalTrainer.dexCount);
            if (show->rivalTrainer.badgeCount != 0)
            {
                sTVShowState = 1;
            }
            else
            {
                sTVShowState = 2;
            }
            break;
        case 9:
            TVShowConvertInternationalString(gStringVar1, show->rivalTrainer.playerName, show->rivalTrainer.language);
            TV_PrintIntToStringVar(1, show->rivalTrainer.dexCount);
            if (show->rivalTrainer.badgeCount != 0)
            {
                sTVShowState = 1;
            }
            else
            {
                sTVShowState = 2;
            }
            break;
        case 10:
            TVShowConvertInternationalString(gStringVar1, show->rivalTrainer.playerName, show->rivalTrainer.language);
            TV_PrintIntToStringVar(1, show->rivalTrainer.dexCount);
            if (show->rivalTrainer.badgeCount != 0)
            {
                sTVShowState = 1;
            }
            else
            {
                sTVShowState = 2;
            }
            break;
        case 1:
            TV_PrintIntToStringVar(0, show->rivalTrainer.badgeCount);
            if (FlagGet(FLAG_LANDMARK_BATTLE_FRONTIER))
            {
                if (show->rivalTrainer.nSilverSymbols || show->rivalTrainer.nGoldSymbols)
                {
                    sTVShowState = 4;
                }
                else
                {
                    sTVShowState = 3;
                }
            }
            else
            {
                sTVShowState = 6;
            }
            break;
        case 2:
            if (FlagGet(FLAG_LANDMARK_BATTLE_FRONTIER))
            {
                if (show->rivalTrainer.nSilverSymbols || show->rivalTrainer.nGoldSymbols)
                {
                    sTVShowState = 4;
                }
                else
                {
                    sTVShowState = 3;
                }
            }
            else
            {
                sTVShowState = 6;
            }
            break;
        case 3:
            if (show->rivalTrainer.battlePoints == 0)
            {
                sTVShowState = 6;
            }
            else
            {
                sTVShowState = 5;
            }
            break;
        case 4:
            TV_PrintIntToStringVar(0, show->rivalTrainer.nGoldSymbols);
            TV_PrintIntToStringVar(1, show->rivalTrainer.nSilverSymbols);
            if (show->rivalTrainer.battlePoints == 0)
            {
                sTVShowState = 6;
            }
            else
            {
                sTVShowState = 5;
            }
            break;
        case 5:
            TV_PrintIntToStringVar(0, show->rivalTrainer.battlePoints);
            sTVShowState = 6;
            break;
        case 6:
            TVShowConvertInternationalString(gStringVar1, show->rivalTrainer.playerName, show->rivalTrainer.language);
            TVShowDone();
    }
    ShowFieldMessage(sTVTodaysRivalTrainerTextGroup[state]);
}

static void DoTVShowDewfordTrendWatcherNetwork(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            CopyEasyChatWord(gStringVar1, show->trendWatcher.words[0]);
            CopyEasyChatWord(gStringVar2, show->trendWatcher.words[1]);
            if (show->trendWatcher.gender == MALE)
            {
                sTVShowState = 1;
            }
            else
            {
                sTVShowState = 2;
            }
            break;
        case 1:
        case 2:
            CopyEasyChatWord(gStringVar1, show->trendWatcher.words[0]);
            CopyEasyChatWord(gStringVar2, show->trendWatcher.words[1]);
            TVShowConvertInternationalString(gStringVar3, show->trendWatcher.playerName, show->trendWatcher.language);
            sTVShowState = 3;
            break;
        case 3:
            CopyEasyChatWord(gStringVar1, show->trendWatcher.words[0]);
            CopyEasyChatWord(gStringVar2, show->trendWatcher.words[1]);
            if (show->trendWatcher.gender == MALE)
            {
                sTVShowState = 4;
            }
            else
            {
                sTVShowState = 5;
            }
            break;
        case 4:
        case 5:
            CopyEasyChatWord(gStringVar1, show->trendWatcher.words[0]);
            CopyEasyChatWord(gStringVar2, show->trendWatcher.words[1]);
            TVShowConvertInternationalString(gStringVar3, show->trendWatcher.playerName, show->trendWatcher.language);
            sTVShowState = 6;
            break;
        case 6:
            CopyEasyChatWord(gStringVar1, show->trendWatcher.words[0]);
            CopyEasyChatWord(gStringVar2, show->trendWatcher.words[1]);
            TVShowDone();
    }
    ShowFieldMessage(sTVDewfordTrendWatcherNetworkTextGroup[state]);
}

static void DoTVShowHoennTreasureInvestigators(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            StringCopy(gStringVar1, ItemId_GetName(show->treasureInvestigators.item));
            if (show->treasureInvestigators.location == MAPSEC_DYNAMIC)
            {
                switch (show->treasureInvestigators.mapLayoutId)
                {
                    case 0x115 ... 0x117:
                        sTVShowState = 2;
                        break;
                    default:
                        sTVShowState = 1;
                        break;
                }
            }
            else
            {
                sTVShowState = 1;
            }
            break;
        case 1:
            StringCopy(gStringVar1, ItemId_GetName(show->treasureInvestigators.item));
            TVShowConvertInternationalString(gStringVar2, show->treasureInvestigators.playerName, show->treasureInvestigators.language);
            GetMapName(gStringVar3, show->treasureInvestigators.location, 0);
            TVShowDone();
            break;
        case 2:
            StringCopy(gStringVar1, ItemId_GetName(show->treasureInvestigators.item));
            TVShowConvertInternationalString(gStringVar2, show->treasureInvestigators.playerName, show->treasureInvestigators.language);
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVHoennTreasureInvestisatorsTextGroup[state]);
}

static void DoTVShowFindThatGamer(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->findThatGamer.playerName, show->findThatGamer.language);
            switch (show->findThatGamer.whichGame)
            {
                case 0:
                    StringCopy(gStringVar2, gText_Slots);
                    break;
                case 1:
                    StringCopy(gStringVar2, gText_Roulette);
                    break;
            }
            if (show->findThatGamer.won == TRUE)
            {
                sTVShowState = 1;
            }
            else
            {
                sTVShowState = 2;
            }
            break;
        case 1:
            TVShowConvertInternationalString(gStringVar1, show->findThatGamer.playerName, show->findThatGamer.language);
            switch (show->findThatGamer.whichGame)
            {
                case 0:
                    StringCopy(gStringVar2, gText_Slots);
                    break;
                case 1:
                    StringCopy(gStringVar2, gText_Roulette);
                    break;
            }
            TV_PrintIntToStringVar(2, show->findThatGamer.nCoins);
            TVShowDone(); break;
        case 2:
            TVShowConvertInternationalString(gStringVar1, show->findThatGamer.playerName, show->findThatGamer.language);
            switch (show->findThatGamer.whichGame)
            {
                case 0:
                    StringCopy(gStringVar2, gText_Slots);
                    break;
                case 1:
                    StringCopy(gStringVar2, gText_Roulette);
                    break;
            }
            TV_PrintIntToStringVar(2, show->findThatGamer.nCoins);
            sTVShowState = 3;
            break;
        case 3:
            TVShowConvertInternationalString(gStringVar1, show->findThatGamer.playerName, show->findThatGamer.language);
            switch (show->findThatGamer.whichGame)
            {
                case 0:
                    StringCopy(gStringVar2, gText_Roulette);
                    break;
                case 1:
                    StringCopy(gStringVar2, gText_Slots);
                    break;
            }
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVFindThatGamerTextGroup[state]);
}

static void DoTVShowBreakingNewsTV(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            if (show->breakingNews.outcome == 0)
            {
                sTVShowState = 1;
            }
            else
            {
                sTVShowState = 5;
            }
            break;
        case 1:
            TVShowConvertInternationalString(gStringVar1, show->breakingNews.playerName, show->breakingNews.language);
            StringCopy(gStringVar2, gSpeciesNames[show->breakingNews.lastOpponentSpecies]);
            GetMapName(gStringVar3, show->breakingNews.location, 0);
            sTVShowState = 2;
            break;
        case 2:
            TVShowConvertInternationalString(gStringVar1, show->breakingNews.playerName, show->breakingNews.language);
            StringCopy(gStringVar2, gSpeciesNames[show->breakingNews.lastOpponentSpecies]);
            StringCopy(gStringVar3, gSpeciesNames[show->breakingNews.poke1Species]);
            sTVShowState = 3;
            break;
        case 3:
            TV_PrintIntToStringVar(0, show->breakingNews.balls);
            StringCopy(gStringVar2, ItemId_GetName(show->breakingNews.caughtMonBall));
            sTVShowState = 4;
            break;
        case 4:
            TVShowConvertInternationalString(gStringVar1, show->breakingNews.playerName, show->breakingNews.language);
            GetMapName(gStringVar2, show->breakingNews.location, 0);
            TVShowDone();
            break;
        case 5:
            TVShowConvertInternationalString(gStringVar1, show->breakingNews.playerName, show->breakingNews.language);
            StringCopy(gStringVar2, gSpeciesNames[show->breakingNews.lastOpponentSpecies]);
            GetMapName(gStringVar3, show->breakingNews.location, 0);
            sTVShowState = 6;
            break;
        case 6:
            TVShowConvertInternationalString(gStringVar1, show->breakingNews.playerName, show->breakingNews.language);
            StringCopy(gStringVar2, gSpeciesNames[show->breakingNews.lastOpponentSpecies]);
            StringCopy(gStringVar3, gSpeciesNames[show->breakingNews.poke1Species]);
            switch (show->breakingNews.outcome)
            {
                case 1:
                    if (show->breakingNews.lastUsedMove == MOVE_NONE)
                    {
                        sTVShowState = 12;
                    }
                    else
                    {
                        sTVShowState = 7;
                    }
                    break;
                case 2:
                    sTVShowState = 9;
                    break;
                case 3:
                    sTVShowState = 10;
                    break;
            }
            break;
        case 7:
            StringCopy(gStringVar1, gMoveNames[show->breakingNews.lastUsedMove]);
            StringCopy(gStringVar2, gSpeciesNames[show->breakingNews.poke1Species]);
            sTVShowState = 8;
            break;
        case 12:
            TVShowConvertInternationalString(gStringVar1, show->breakingNews.playerName, show->breakingNews.language);
            StringCopy(gStringVar2, gSpeciesNames[show->breakingNews.lastOpponentSpecies]);
            StringCopy(gStringVar3, gSpeciesNames[show->breakingNews.poke1Species]);
            sTVShowState = 8;
            break;
        case 8:
            TVShowConvertInternationalString(gStringVar1, show->breakingNews.playerName, show->breakingNews.language);
            GetMapName(gStringVar2, show->breakingNews.location, 0);
            sTVShowState = 11;
            break;
        case 9:
        case 10:
            TVShowConvertInternationalString(gStringVar1, show->breakingNews.playerName, show->breakingNews.language);
            StringCopy(gStringVar2, gSpeciesNames[show->breakingNews.lastOpponentSpecies]);
            GetMapName(gStringVar3, show->breakingNews.location, 0);
            sTVShowState = 11;
            break;
        case 11:
            TVShowConvertInternationalString(gStringVar1, show->breakingNews.playerName, show->breakingNews.language);
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVBreakinsNewsTextGroup[state]);
}

static void DoTVShowSecretBaseVisit(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->secretBaseVisit.playerName, show->secretBaseVisit.language);
            if (show->secretBaseVisit.nDecorations == 0)
            {
                sTVShowState = 2;
            }
            else
            {
                sTVShowState = 1;
            }
            break;
        case 1:
            StringCopy(gStringVar2, gDecorations[show->secretBaseVisit.decorations[0]].name);
            if (show->secretBaseVisit.nDecorations == 1)
            {
                sTVShowState = 4;
            }
            else
            {
                sTVShowState = 3;
            }
            break;
        case 3:
            StringCopy(gStringVar2, gDecorations[show->secretBaseVisit.decorations[1]].name);
            switch (show->secretBaseVisit.nDecorations)
            {
                case 2:
                    sTVShowState = 7;
                    break;
                case 3:
                    sTVShowState = 6;
                    break;
                case 4:
                    sTVShowState = 5;
                    break;
            }
            break;
        case 5:
            StringCopy(gStringVar2, gDecorations[show->secretBaseVisit.decorations[2]].name);
            StringCopy(gStringVar3, gDecorations[show->secretBaseVisit.decorations[3]].name);
            sTVShowState = 8;
            break;
        case 6:
            StringCopy(gStringVar2, gDecorations[show->secretBaseVisit.decorations[2]].name);
            sTVShowState = 8;
            break;
        case 2:
        case 4:
        case 7:
            sTVShowState = 8;
            break;
        case 8:
            TVShowConvertInternationalString(gStringVar1, show->secretBaseVisit.playerName, show->secretBaseVisit.language);
            if (show->secretBaseVisit.avgLevel < 25)
            {
                sTVShowState = 12;
            }
            else if (show->secretBaseVisit.avgLevel < 50)
            {
                sTVShowState = 11;
            }
            else if (show->secretBaseVisit.avgLevel < 70)
            {
                sTVShowState = 10;
            }
            else
            {
                sTVShowState = 9;
            }
            break;
        case 9:
        case 10:
        case 11:
        case 12:
            TVShowConvertInternationalString(gStringVar1, show->secretBaseVisit.playerName, show->secretBaseVisit.language);
            StringCopy(gStringVar2, gSpeciesNames[show->secretBaseVisit.species]);
            StringCopy(gStringVar3, gMoveNames[show->secretBaseVisit.move]);
            sTVShowState = 13;
            break;
        case 13:
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVSecretBaseVisitTextGroup[state]);
}

static void DoTVShowPokemonLotteryWinnerFlashReport(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    TVShowConvertInternationalString(gStringVar1, show->lottoWinner.playerName, show->lottoWinner.language);
    if (show->lottoWinner.whichPrize == 0)
    {
        StringCopy(gStringVar2, gText_Jackpot);
    }
    else if (show->lottoWinner.whichPrize == 1)
    {
        StringCopy(gStringVar2, gText_First);
    }
    else if (show->lottoWinner.whichPrize == 2)
    {
        StringCopy(gStringVar2, gText_Second);
    }
    else
    {
        StringCopy(gStringVar2, gText_Third);
    }
    StringCopy(gStringVar3, ItemId_GetName(show->lottoWinner.item));
    TVShowDone();
    ShowFieldMessage(sTVPokemonLotteryWinnerFlashReportTextGroup[state]);
}

static void DoTVShowThePokemonBattleSeminar(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->battleSeminar.playerName, show->battleSeminar.language);
            StringCopy(gStringVar2, gSpeciesNames[show->battleSeminar.species]);
            StringCopy(gStringVar3, gSpeciesNames[show->battleSeminar.foeSpecies]);
            sTVShowState = 1;
            break;
        case 1:
            TVShowConvertInternationalString(gStringVar1, show->battleSeminar.playerName, show->battleSeminar.language);
            StringCopy(gStringVar2, gSpeciesNames[show->battleSeminar.foeSpecies]);
            StringCopy(gStringVar3, gMoveNames[show->battleSeminar.move]);
            sTVShowState = 2;
            break;
        case 2:
            StringCopy(gStringVar1, gSpeciesNames[show->battleSeminar.species]);
            switch (show->battleSeminar.nOtherMoves)
            {
                case 1:
                    sTVShowState = 5;
                    break;
                case 2:
                    sTVShowState = 4;
                    break;
                case 3:
                    sTVShowState = 3;
                    break;
                default:
                    sTVShowState = 6;
                    break;
            }
            break;
        case 3:
            StringCopy(gStringVar1, gMoveNames[show->battleSeminar.otherMoves[0]]);
            StringCopy(gStringVar2, gMoveNames[show->battleSeminar.otherMoves[1]]);
            StringCopy(gStringVar3, gMoveNames[show->battleSeminar.otherMoves[2]]);
            sTVShowState = 6;
            break;
        case 4:
            StringCopy(gStringVar1, gMoveNames[show->battleSeminar.otherMoves[0]]);
            StringCopy(gStringVar2, gMoveNames[show->battleSeminar.otherMoves[1]]);
            sTVShowState = 6;
            break;
        case 5:
            StringCopy(gStringVar2, gMoveNames[show->battleSeminar.otherMoves[0]]);
            sTVShowState = 6;
            break;
        case 6:
            StringCopy(gStringVar1, gMoveNames[show->battleSeminar.betterMove]);
            StringCopy(gStringVar2, gMoveNames[show->battleSeminar.move]);
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVThePokemonBattleSeminarTextGroup[state]);
}

static void DoTVShowTrainerFanClubSpecial(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->fanClubSpecial.idolName, show->fanClubSpecial.idolNameLanguage);
            TVShowConvertInternationalString(gStringVar2, show->fanClubSpecial.playerName, show->fanClubSpecial.language);
            CopyEasyChatWord(gStringVar3, show->fanClubSpecial.words[0]);
            if (show->fanClubSpecial.score >= 90)
            {
                sTVShowState = 1;
            }
            else if (show->fanClubSpecial.score >= 70)
            {
                sTVShowState = 2;
            }
            else if (show->fanClubSpecial.score >= 30)
            {
                sTVShowState = 3;
            }
            else
            {
                sTVShowState = 4;
            }
            break;
        case 1:
            TVShowConvertInternationalString(gStringVar1, show->fanClubSpecial.idolName, show->fanClubSpecial.idolNameLanguage);
            TVShowConvertInternationalString(gStringVar2, show->fanClubSpecial.playerName, show->fanClubSpecial.language);
            TV_PrintIntToStringVar(2, show->fanClubSpecial.score);
            sTVShowState = 5;
            break;
        case 2:
            TVShowConvertInternationalString(gStringVar1, show->fanClubSpecial.idolName, show->fanClubSpecial.idolNameLanguage);
            TVShowConvertInternationalString(gStringVar2, show->fanClubSpecial.playerName, show->fanClubSpecial.language);
            TV_PrintIntToStringVar(2, show->fanClubSpecial.score);
            sTVShowState = 5;
            break;
        case 3:
            TVShowConvertInternationalString(gStringVar1, show->fanClubSpecial.idolName, show->fanClubSpecial.idolNameLanguage);
            TVShowConvertInternationalString(gStringVar2, show->fanClubSpecial.playerName, show->fanClubSpecial.language);
            TV_PrintIntToStringVar(2, show->fanClubSpecial.score);
            sTVShowState = 5;
            break;
        case 4:
            TVShowConvertInternationalString(gStringVar1, show->fanClubSpecial.idolName, show->fanClubSpecial.idolNameLanguage);
            TVShowConvertInternationalString(gStringVar2, show->fanClubSpecial.playerName, show->fanClubSpecial.language);
            TV_PrintIntToStringVar(2, show->fanClubSpecial.score);
            sTVShowState = 5;
            break;
        case 5:
            TVShowConvertInternationalString(gStringVar1, show->fanClubSpecial.idolName, show->fanClubSpecial.idolNameLanguage);
            TVShowConvertInternationalString(gStringVar2, show->fanClubSpecial.playerName, show->fanClubSpecial.language);
            CopyEasyChatWord(gStringVar3, show->fanClubSpecial.words[0]);
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVTrainerFanClubSpecialTextGroup[state]);
}

static void DoTVShowTrainerFanClub(void)
{
    TVShow *show;
    u8 state;
    u32 playerId;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->trainerFanClub.playerName, show->trainerFanClub.language);
            playerId = ((show->common.trainerIdHi << 8) + show->common.trainerIdLo);
            switch (playerId % 10)
            {
                case 0:
                    sTVShowState = 1;
                    break;
                case 1:
                    sTVShowState = 2;
                    break;
                case 2:
                    sTVShowState = 3;
                    break;
                case 3:
                    sTVShowState = 4;
                    break;
                case 4:
                    sTVShowState = 5;
                    break;
                case 5:
                    sTVShowState = 6;
                    break;
                case 6:
                    sTVShowState = 7;
                    break;
                case 7:
                    sTVShowState = 8;
                    break;
                case 8:
                    sTVShowState = 9;
                    break;
                case 9:
                    sTVShowState = 10;
                    break;
            }
            break;
        case 1:
            sTVShowState = 11;
            break;
        case 2:
            sTVShowState = 11;
            break;
        case 3:
            sTVShowState = 11;
            break;
        case 4:
            sTVShowState = 11;
            break;
        case 5:
            sTVShowState = 11;
            break;
        case 6:
            sTVShowState = 11;
            break;
        case 7:
            sTVShowState = 11;
            break;
        case 8:
            sTVShowState = 11;
            break;
        case 9:
            sTVShowState = 11;
            break;
        case 10:
            sTVShowState = 11;
            break;
        case 11:
            TVShowConvertInternationalString(gStringVar1, show->trainerFanClub.playerName, show->trainerFanClub.language);
            CopyEasyChatWord(gStringVar2, show->trainerFanClub.words[0]);
            CopyEasyChatWord(gStringVar3, show->trainerFanClub.words[1]);
            TVShowDone();
    }
    ShowFieldMessage(sTVTrainerFanClubTextGroup[state]);
}

static void DoTVShowSpotTheCuties(void)
{
    TVShow *show;
    u8 state;
    u32 playerId;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->cuties.playerName, show->cuties.language);
            TVShowConvertInternationalString(gStringVar2, show->cuties.nickname, show->cuties.pokemonNameLanguage);
            if (show->cuties.nRibbons < 10)
            {
                sTVShowState = 1;
            }
            else if (show->cuties.nRibbons < 20)
            {
                sTVShowState = 2;
            }
            else
            {
                sTVShowState = 3;
            }
            break;
        case 1:
        case 2:
        case 3:
            TVShowConvertInternationalString(gStringVar1, show->cuties.playerName, show->cuties.language);
            TVShowConvertInternationalString(gStringVar2, show->cuties.nickname, show->cuties.pokemonNameLanguage);
            TV_PrintIntToStringVar(2, show->cuties.nRibbons);
            sTVShowState = 4;
            break;
        case 4:
            TVShowConvertInternationalString(gStringVar2, show->cuties.nickname, show->cuties.pokemonNameLanguage);
            switch (show->cuties.selectedRibbon)
            {
                case 0:
                    sTVShowState = 5;
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                    sTVShowState = 6;
                    break;
                case 5:
                case 6:
                case 7:
                case 8:
                    sTVShowState = 7;
                    break;
                case 9:
                case 10:
                case 11:
                case 12:
                    sTVShowState = 8;
                    break;
                case 13:
                case 14:
                case 15:
                case 16:
                    sTVShowState = 9;
                    break;
                case 17:
                case 18:
                case 19:
                case 20:
                    sTVShowState = 10;
                    break;
                case 21:
                    sTVShowState = 11;
                    break;
                case 22:
                    sTVShowState = 12;
                    break;
                case 23:
                    sTVShowState = 13;
                    break;
                case 24:
                    sTVShowState = 14;
                    break;
            }
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            TVShowConvertInternationalString(gStringVar2, show->cuties.nickname, show->cuties.pokemonNameLanguage);
            sTVShowState = 15;
            break;
        case 15:
            TVShowDone();
    }
    ShowFieldMessage(sTVCutiesTextGroup[state]);
}

static void DoTVShowPokemonNewsBattleFrontier(void)
{
    TVShow *show;
    u8 state;
    u32 playerId;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            switch (show->frontier.facility)
            {
                case 1:
                    sTVShowState = 1;
                    break;
                case 2:
                    sTVShowState = 2;
                    break;
                case 3:
                    sTVShowState = 3;
                    break;
                case 4:
                    sTVShowState = 4;
                    break;
                case 5:
                    sTVShowState = 5;
                    break;
                case 6:
                    sTVShowState = 6;
                    break;
                case 7:
                    sTVShowState = 7;
                    break;
                case 8:
                    sTVShowState = 8;
                    break;
                case 9:
                    sTVShowState = 9;
                    break;
                case 10:
                    sTVShowState = 10;
                    break;
                case 11:
                    sTVShowState = 11;
                    break;
                case 12:
                    sTVShowState = 12;
                    break;
                case 13:
                    sTVShowState = 13;
                    break;
            }
            break;
        case 1:
            TVShowConvertInternationalString(gStringVar1, show->frontier.playerName, show->frontier.language);
            TV_PrintIntToStringVar(1, show->frontier.winStreak);
            sTVShowState = 14;
            break;
        case 2:
            TVShowConvertInternationalString(gStringVar1, show->frontier.playerName, show->frontier.language);
            TV_PrintIntToStringVar(1, show->frontier.winStreak);
            sTVShowState = 16;
            break;
        case 3:
            TVShowConvertInternationalString(gStringVar1, show->frontier.playerName, show->frontier.language);
            TV_PrintIntToStringVar(1, show->frontier.winStreak);
            sTVShowState = 15;
            break;
        case 4:
            TVShowConvertInternationalString(gStringVar1, show->frontier.playerName, show->frontier.language);
            TV_PrintIntToStringVar(1, show->frontier.winStreak);
            sTVShowState = 15;
            break;
        case 5:
            TVShowConvertInternationalString(gStringVar1, show->frontier.playerName, show->frontier.language);
            TV_PrintIntToStringVar(1, show->frontier.winStreak);
            sTVShowState = 14;
            break;
        case 6:
            TVShowConvertInternationalString(gStringVar1, show->frontier.playerName, show->frontier.language);
            TV_PrintIntToStringVar(1, show->frontier.winStreak);
            sTVShowState = 14;
            break;
        case 7:
            TVShowConvertInternationalString(gStringVar1, show->frontier.playerName, show->frontier.language);
            TV_PrintIntToStringVar(1, show->frontier.winStreak);
            sTVShowState = 14;
            break;
        case 8:
            TVShowConvertInternationalString(gStringVar1, show->frontier.playerName, show->frontier.language);
            TV_PrintIntToStringVar(1, show->frontier.winStreak);
            sTVShowState = 14;
            break;
        case 9:
            TVShowConvertInternationalString(gStringVar1, show->frontier.playerName, show->frontier.language);
            TV_PrintIntToStringVar(1, show->frontier.winStreak);
            sTVShowState = 14;
            break;
        case 10:
            TVShowConvertInternationalString(gStringVar1, show->frontier.playerName, show->frontier.language);
            TV_PrintIntToStringVar(1, show->frontier.winStreak);
            sTVShowState = 14;
            break;
        case 11:
            TVShowConvertInternationalString(gStringVar1, show->frontier.playerName, show->frontier.language);
            TV_PrintIntToStringVar(1, show->frontier.winStreak);
            sTVShowState = 14;
            break;
        case 12:
            TVShowConvertInternationalString(gStringVar1, show->frontier.playerName, show->frontier.language);
            TV_PrintIntToStringVar(1, show->frontier.winStreak);
            sTVShowState = 14;
            break;
        case 13:
            TVShowConvertInternationalString(gStringVar1, show->frontier.playerName, show->frontier.language);
            TV_PrintIntToStringVar(1, show->frontier.winStreak);
            sTVShowState = 14;
            break;
        case 14:
            StringCopy(gStringVar1, gSpeciesNames[show->frontier.species1]);
            StringCopy(gStringVar2, gSpeciesNames[show->frontier.species2]);
            StringCopy(gStringVar3, gSpeciesNames[show->frontier.species3]);
            sTVShowState = 18;
            break;
        case 15:
            StringCopy(gStringVar1, gSpeciesNames[show->frontier.species1]);
            StringCopy(gStringVar2, gSpeciesNames[show->frontier.species2]);
            sTVShowState = 18;
            break;
        case 16:
            StringCopy(gStringVar1, gSpeciesNames[show->frontier.species1]);
            StringCopy(gStringVar2, gSpeciesNames[show->frontier.species2]);
            StringCopy(gStringVar3, gSpeciesNames[show->frontier.species3]);
            sTVShowState = 17;
            break;
        case 17:
            StringCopy(gStringVar1, gSpeciesNames[show->frontier.species4]);
            sTVShowState = 18;
            break;
        case 18:
            TVShowConvertInternationalString(gStringVar1, show->frontier.playerName, show->frontier.language);
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVPokemonNewsBattleFrontierTextGroup[state]);
}

static void DoTVShowWhatsNo1InHoennToday(void)
{
    TVShow *show;
    u8 state;
    u32 playerId;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->numberOne.playerName, show->numberOne.language);
            switch (show->numberOne.actionIdx)
            {
                case 0:
                    sTVShowState = 1;
                    break;
                case 1:
                    sTVShowState = 2;
                    break;
                case 2:
                    sTVShowState = 3;
                    break;
                case 3:
                    sTVShowState = 4;
                    break;
                case 4:
                    sTVShowState = 5;
                    break;
                case 5:
                    sTVShowState = 6;
                    break;
                case 6:
                    sTVShowState = 7;
                    break;
            }
            break;
        case 1:
            TVShowConvertInternationalString(gStringVar1, show->numberOne.playerName, show->numberOne.language);
            TV_PrintIntToStringVar(1, show->numberOne.count);
            sTVShowState = 8;
            break;
        case 2:
            TVShowConvertInternationalString(gStringVar1, show->numberOne.playerName, show->numberOne.language);
            TV_PrintIntToStringVar(1, show->numberOne.count);
            sTVShowState = 8;
            break;
        case 3:
            TVShowConvertInternationalString(gStringVar1, show->numberOne.playerName, show->numberOne.language);
            TV_PrintIntToStringVar(1, show->numberOne.count);
            sTVShowState = 8;
            break;
        case 4:
            TVShowConvertInternationalString(gStringVar1, show->numberOne.playerName, show->numberOne.language);
            TV_PrintIntToStringVar(1, show->numberOne.count);
            sTVShowState = 8;
            break;
        case 5:
            TVShowConvertInternationalString(gStringVar1, show->numberOne.playerName, show->numberOne.language);
            TV_PrintIntToStringVar(1, show->numberOne.count);
            sTVShowState = 8;
            break;
        case 6:
            TVShowConvertInternationalString(gStringVar1, show->numberOne.playerName, show->numberOne.language);
            TV_PrintIntToStringVar(1, show->numberOne.count);
            sTVShowState = 8;
            break;
        case 7:
            TVShowConvertInternationalString(gStringVar1, show->numberOne.playerName, show->numberOne.language);
            TV_PrintIntToStringVar(1, show->numberOne.count);
            sTVShowState = 8;
            break;
        case 8:
            TVShowConvertInternationalString(gStringVar1, show->numberOne.playerName, show->numberOne.language);
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVWhatsNo1InHoennTodayTextGroup[state]);
}

u8 sub_80F5180(TVShow *show)
{
    u8 i;
    u8 tot;

    for (i = 0, tot = 0; i < 32; i ++)
    {
        if ((show->secretBaseSecrets.flags >> i) & 1)
        {
            tot ++;
        }
    }
    return tot;
}

u8 sub_80F51AC(TVShow *show, u8 a1)
{
    u8 i;
    u8 tot;

    for (i = 0, tot = 0; i < 32; i ++)
    {
        if ((show->secretBaseSecrets.flags >> i) & 1)
        {
            if (tot == a1)
            {
                return sTVSecretBaseSecretsStateLookup[i];
            }
            tot ++;
        }
    }
    return 0;
}

static void DoTVShowSecretBaseSecrets(void)
{
    TVShow *show;
    u8 state;
    u8 bitCount;
    u16 i;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            TVShowConvertInternationalString(gStringVar1, show->secretBaseSecrets.baseOwnersName, show->secretBaseSecrets.baseOwnersNameLanguage);
            TVShowConvertInternationalString(gStringVar2, show->secretBaseSecrets.playerName, show->secretBaseSecrets.language);
            bitCount = sub_80F5180(show);
            if (bitCount == 0)
            {
                sTVShowState = 8;
            }
            else
            {
                show->secretBaseSecrets.savedState = 1;
                sTVSecretBaseSecretsRandomValues[0] = Random() % bitCount;
                sTVShowState = sub_80F51AC(show, sTVSecretBaseSecretsRandomValues[0]);
            }
            break;
        case 1:
            TVShowConvertInternationalString(gStringVar2, show->secretBaseSecrets.playerName, show->secretBaseSecrets.language);
            bitCount = sub_80F5180(show);
            switch (bitCount)
            {
                case 1:
                    sTVShowState = 9;
                    break;
                case 2:
                    show->secretBaseSecrets.savedState = 2;
                    if (sTVSecretBaseSecretsRandomValues[0] == 0)
                    {
                        sTVShowState = sub_80F51AC(show, 1);
                    }
                    else
                    {
                        sTVShowState = sub_80F51AC(show, 0);
                    }
                    break;
                default:
                    for (i = 0; i < 0xFFFF; i ++)
                    {
                        sTVSecretBaseSecretsRandomValues[1] = Random() % bitCount;
                        if (sTVSecretBaseSecretsRandomValues[1] != sTVSecretBaseSecretsRandomValues[0])
                        {
                            break;
                        }
                    }
                    show->secretBaseSecrets.savedState = 2;
                    sTVShowState = sub_80F51AC(show, sTVSecretBaseSecretsRandomValues[1]);
                    break;
            }
            break;
        case 2:
            TVShowConvertInternationalString(gStringVar2, show->secretBaseSecrets.playerName, show->secretBaseSecrets.language);
            bitCount = sub_80F5180(show);
            if (bitCount == 2)
            {
                sTVShowState = 9;
            }
            else
            {
                for (i = 0; i < 0xFFFF; i ++)
                {
                    sTVSecretBaseSecretsRandomValues[2] = Random() % bitCount;
                    if (sTVSecretBaseSecretsRandomValues[2] != sTVSecretBaseSecretsRandomValues[0] && sTVSecretBaseSecretsRandomValues[2] != sTVSecretBaseSecretsRandomValues[1])
                    {
                        break;
                    }
                }
                show->secretBaseSecrets.savedState = 3;
                sTVShowState = sub_80F51AC(show, sTVSecretBaseSecretsRandomValues[2]);
            }
            break;
        case 3:
            TVShowConvertInternationalString(gStringVar1, show->secretBaseSecrets.baseOwnersName, show->secretBaseSecrets.baseOwnersNameLanguage);
            TVShowConvertInternationalString(gStringVar2, show->secretBaseSecrets.playerName, show->secretBaseSecrets.language);
            TV_PrintIntToStringVar(2, show->secretBaseSecrets.stepsInBase);
            if (show->secretBaseSecrets.stepsInBase <= 30)
            {
                sTVShowState = 4;
            }
            else if (show->secretBaseSecrets.stepsInBase <= 100)
            {
                sTVShowState = 5;
            }
            else
            {
                sTVShowState = 6;
            }
            break;
        case 4:
            TVShowConvertInternationalString(gStringVar1, show->secretBaseSecrets.baseOwnersName, show->secretBaseSecrets.baseOwnersNameLanguage);
            TVShowConvertInternationalString(gStringVar2, show->secretBaseSecrets.playerName, show->secretBaseSecrets.language);
            sTVShowState = 7;
            break;
        case 5:
            TVShowConvertInternationalString(gStringVar1, show->secretBaseSecrets.baseOwnersName, show->secretBaseSecrets.baseOwnersNameLanguage);
            TVShowConvertInternationalString(gStringVar2, show->secretBaseSecrets.playerName, show->secretBaseSecrets.language);
            sTVShowState = 7;
            break;
        case 6:
            TVShowConvertInternationalString(gStringVar1, show->secretBaseSecrets.baseOwnersName, show->secretBaseSecrets.baseOwnersNameLanguage);
            TVShowConvertInternationalString(gStringVar2, show->secretBaseSecrets.playerName, show->secretBaseSecrets.language);
            sTVShowState = 7;
            break;
        case 7:
            TVShowConvertInternationalString(gStringVar1, show->secretBaseSecrets.baseOwnersName, show->secretBaseSecrets.baseOwnersNameLanguage);
            TVShowConvertInternationalString(gStringVar2, show->secretBaseSecrets.playerName, show->secretBaseSecrets.language);
            TVShowDone();
            break;
        case 8:
            sTVShowState = 3;
            break;
        case 9:
            sTVShowState = 3;
            break;
        case 10:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 11:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 12:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 13:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 14:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 15:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 16:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 17:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 18:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 19:
            StringCopy(gStringVar2, ItemId_GetName(show->secretBaseSecrets.item));
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 20:
            if (show->common.trainerIdLo & 1)
            {
                sTVShowState = 22;
            }
            else
            {
                sTVShowState = 21;
            }
            break;
        case 21:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 22:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 23:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 24:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 25:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 26:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 27:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 28:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 29:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 30:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 31:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 32:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 33:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 34:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 35:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 36:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 37:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 38:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 39:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 40:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 41:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 42:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
        case 43:
            sTVShowState = show->secretBaseSecrets.savedState;
            break;
    }
    ShowFieldMessage(sTVSecretBaseSecretsTextGroup[state]);
}

static void DoTVShowSafariFanClub(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            if (show->safariFanClub.nMonsCaught == 0)
            {
                sTVShowState = 6;
            }
            else if (show->safariFanClub.nMonsCaught < 4)
            {
                sTVShowState = 5;
            }
            else
            {
                sTVShowState = 1;
            }
            break;
        case 1:
            TVShowConvertInternationalString(gStringVar1, show->safariFanClub.playerName, show->safariFanClub.language);
            TV_PrintIntToStringVar(1, show->safariFanClub.nMonsCaught);
            if (show->safariFanClub.nPkblkUsed == 0)
            {
                sTVShowState = 3;
            }
            else
            {
                sTVShowState = 2;
            }
            break;
        case 2:
            TV_PrintIntToStringVar(1, show->safariFanClub.nPkblkUsed);
            sTVShowState = 4;
            break;
        case 3:
            sTVShowState = 4;
            break;
        case 4:
            TVShowConvertInternationalString(gStringVar1, show->safariFanClub.playerName, show->safariFanClub.language);
            sTVShowState = 10;
            break;
        case 5:
            TVShowConvertInternationalString(gStringVar1, show->safariFanClub.playerName, show->safariFanClub.language);
            TV_PrintIntToStringVar(1, show->safariFanClub.nMonsCaught);
            if (show->safariFanClub.nPkblkUsed == 0)
            {
                sTVShowState = 8;
            }
            else
            {
                sTVShowState = 7;
            }
            break;
        case 6:
            TVShowConvertInternationalString(gStringVar1, show->safariFanClub.playerName, show->safariFanClub.language);
            if (show->safariFanClub.nPkblkUsed == 0)
            {
                sTVShowState = 8;
            }
            else
            {
                sTVShowState = 7;
            }
            break;
        case 7:
            TV_PrintIntToStringVar(1, show->safariFanClub.nPkblkUsed);
            sTVShowState = 9;
            break;
        case 8:
            sTVShowState = 9;
            break;
        case 9:
            TVShowConvertInternationalString(gStringVar1, show->safariFanClub.playerName, show->safariFanClub.language);
            sTVShowState = 10;
            break;
        case 10:
            TVShowDone();
    }
    ShowFieldMessage(sTVSafariFanClubTextGroup[state]);
}

static void DoTVShowPokemonContestLiveUpdates2(void)
{
    TVShow *show;
    u8 state;

    show = &gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004];
    gSpecialVar_Result = FALSE;
    state = sTVShowState;
    switch (state)
    {
        case 0:
            sub_818E868(gStringVar1, show->contestLiveUpdates2.contestCategory);
            if (show->contestLiveUpdates2.pokeblockState == 1)
            {
                sTVShowState = 1;
            }
            else if (show->contestLiveUpdates2.pokeblockState == 0)
            {
                sTVShowState = 2;
            }
            else
            {
                sTVShowState = 3;
            }
            break;
        case 1:
        case 2:
            TVShowConvertInternationalString(gStringVar3, show->contestLiveUpdates2.playerName, show->contestLiveUpdates2.language);
        case 3:
            TVShowConvertInternationalString(gStringVar2, show->contestLiveUpdates2.nickname, show->contestLiveUpdates2.pokemonNameLanguage);
            TVShowDone();
            break;
    }
    ShowFieldMessage(sTVPokemonContestLiveUpdates2TextGroup[state]);
}

void TVShowDone(void)
{
    gSpecialVar_Result = TRUE;
    sTVShowState = 0;
    gSaveBlock1Ptr->tvShows[gSpecialVar_0x8004].common.active = FALSE;
}

void ResetTVShowState(void)
{
    sTVShowState = 0;
}
