#ifndef GUARD_OVERWORLD_H
#define GUARD_OVERWORLD_H

struct UnkPlayerStruct
{
    u8 player_field_0;
    u8 player_field_1;
};

struct LinkPlayerEventObject
{
    u8 active;
    u8 linkPlayerId;
    u8 eventObjId;
    u8 mode;
};

// Exported RAM declarations
extern struct WarpData gUnknown_020322DC;
extern struct LinkPlayerEventObject gLinkPlayerEventObjects[4];

extern u16 *gBGTilemapBuffers1;
extern u16 *gBGTilemapBuffers2;
extern u16 *gBGTilemapBuffers3;

extern void (*gFieldCallback)(void);

// Exported ROM declarations
extern const struct UCoords32 gUnknown_08339D64[];

void DoWhiteOut(void);
void Overworld_ResetStateAfterFly(void);
void Overworld_ResetStateAfterTeleport(void);
void Overworld_ResetStateAfterDigEscRope(void);
void ResetGameStats(void);
void IncrementGameStat(u8 index);
u32 GetGameStat(u8 index);
void SetGameStat(u8 index, u32 value);
void ApplyNewEncryptionKeyToGameStats(u32 newKey);
void LoadEventObjTemplatesFromHeader(void);
void LoadSaveblockEventObjScripts(void);
void Overworld_SetEventObjTemplateCoords(u8 localId, s16 x, s16 y);
void Overworld_SetEventObjTemplateMovementType(u8 localId, u8 movementType);
const struct MapLayout *GetMapLayout(void);
void ApplyCurrentWarp(void);
void set_warp2_warp3_to_neg_1(void);
void SetWarpData(struct WarpData *warp, s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y);
bool32 warp_data_is_not_neg_1(struct WarpData *warp);
struct MapHeader const *const Overworld_GetMapHeaderByGroupAndId(u16 mapGroup, u16 mapNum);
struct MapHeader const *const warp1_get_mapheader(void);
void set_current_map_header_from_sav1_save_old_name(void);
void LoadSaveblockMapHeader(void);
void update_camera_pos_from_warpid(void);
void warp_in(void);
void Overworld_SetWarpDestination(s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y);
void warp1_set_2(s8 mapGroup, s8 mapNum, s8 warpId);
void saved_warp2_set(s32 unused, s8 mapGroup, s8 mapNum, s8 warpId);
void saved_warp2_set_2(s32 unused, s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y);
void copy_saved_warp2_bank_and_enter_x_to_warp1(u8 unused);
void sub_8084CCC(u8 a1);
void Overworld_SetWarpDestToLastHealLoc(void);
void Overworld_SetHealLocationWarp(u8 healLocationId);
void sub_8084D5C(s16 a1, s16 a2);
void sub_8084DD4(s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y);
void sub_8084E14(void);
void sub_8084E2C(s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y);
void warp1_set_to_warp2(void);
void sub_8084E80(s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y);
void sub_8084EBC(s16 x, s16 y);
void warp1_set_to_sav1w(void);
void sub_8084F2C(s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y);
void sub_8084F6C(u8 a1);
void sub_8084FAC(void);
const struct MapConnection *GetMapConnection(u8 dir);
bool8 sub_8084FF8(u8 dir, u16 x, u16 y);
bool8 sub_8085058(u16 x, u16 y);
bool8 sub_8085078(u16 x, u16 y);
void mliX_load_map(u8 mapGroup, u8 mapNum);
void player_avatar_init_params_reset(void);
void walkrun_find_lowest_active_bit_in_bitfield(void);
bool32 Overworld_IsBikingAllowed(void);
void SetDefaultFlashLevel(void);
void Overworld_SetFlashLevel(s32 flashLevel);
u8 Overworld_GetFlashLevel(void);
void sub_8085524(u16 mapLayoutId);
void sub_8085540(u8 var);
u8 sub_808554C(void);
u16 GetLocationMusic(struct WarpData *warp);
u16 GetCurrLocationDefaultMusic(void);
u16 GetWarpDestinationMusic(void);
void Overworld_ResetMapMusic(void);
void Overworld_PlaySpecialMapMusic(void);
void Overworld_SetSavedMusic(u16 songNum);
void Overworld_ClearSavedMusic(void);
void Overworld_ChangeMusicToDefault(void);
void Overworld_ChangeMusicTo(u16 newMusic);
u8 GetMapMusicFadeoutSpeed(void);
void music_something(void);
bool8 sub_80859A0(void);
void Overworld_FadeOutMapMusic(void);
void UpdateAmbientCry(s16 *state, u16 *delayCounter);
u8 GetMapTypeByGroupAndId(s8 mapGroup, s8 mapNum);
u8 GetMapTypeByWarpData(struct WarpData *warp);
u8 Overworld_GetMapTypeOfSaveblockLocation(void);
u8 get_map_light_from_warp0(void);
bool8 is_map_type_1_2_3_5_or_6(u8 mapType);
bool8 Overworld_MapTypeAllowsTeleportAndFly(u8 mapType);
bool8 Overworld_MapTypeIsIndoors(u8 mapType);
u8 sav1_saved_warp2_map_get_name(void);
u8 sav1_map_get_name(void);
u8 GetCurrentMapBattleScene(void);
void overworld_free_bg_tilemaps(void);
bool32 is_c1_link_related_active(void);
void CB1_Overworld(void);
void CB2_OverworldBasic(void);
void CB2_Overworld(void);
void SetMainCallback1(void (*cb)(void));
void sub_8085E94(void *a0);
void CB2_NewGame(void);
void CB2_WhiteOut(void);
void CB2_LoadMap(void);
void sub_8086024(void);
void sub_8086074(void);
void CB2_ReturnToField(void);
void CB2_ReturnToFieldLocal(void);
void CB2_ReturnToFieldLink(void);
void c2_8056854(void);
void CB2_ReturnToFieldWithOpenMenu(void);
void CB2_ReturnToFieldContinueScript(void);
void CB2_ReturnToFieldContinueScriptPlayMapMusic(void);
void sub_80861E8(void);
void CB2_ContinueSavedGame(void);
void sub_8086C2C(void);
u32 sub_8087214(void);
bool32 sub_808727C(void);
u16 sub_8087288(void);
u16 sub_808729C(void);
u16 sub_80872B0(void);
u16 sub_80872C4(void);
bool32 sub_8087598(void);
bool32 sub_80875C8(void);
bool32 sub_8087634(void);
bool32 sub_808766C(void);
void ClearLinkPlayerEventObjects(void);

#endif // GUARD_OVERWORLD_H
