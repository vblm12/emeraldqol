#include "global.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "event_data.h"
#include "event_scripts.h"
#include "field_effect.h"
#include "field_player_avatar.h"
#include "field_screen.h"
#include "palette.h"
#include "party_menu.h"
#include "rom6.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "wild_encounter.h"

void hm2_sweet_scent(void);
void sub_8159F5C(void);
void sub_8159FEC(u8 taskId);
void sub_815A090(u8 taskId);
void sub_81BE6B8(void);
void sub_81BE72C(void);

bool8 SetUpFieldMove_SweetScent(void)
{
    gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
    gPostMenuFieldCallback = hm2_sweet_scent;
    return TRUE;
}

void hm2_sweet_scent(void)
{
    FieldEffectStart(FLDEFF_SWEET_SCENT);
    gFieldEffectArguments[0] = GetCursorSelectionMonId();
}

bool8 FldEff_SweetScent()
{
    u8 taskId;

    sub_80AC3D0();
    taskId = oei_task_add();
    gTasks[taskId].data[8] = (u32)sub_8159F5C >> 16;
    gTasks[taskId].data[9] = (u32)sub_8159F5C;
    return FALSE;
}

void sub_8159F5C(void)
{
    u8 taskId;

    PlaySE(SE_W230);
    CpuFastSet(gPlttBufferUnfaded, gPaletteDecompressionBuffer, 0x100);
    CpuFastSet(gPlttBufferFaded, gPlttBufferUnfaded, 0x100);
    BeginNormalPaletteFade(~(1 << (gSprites[GetPlayerAvatarObjectId()].oam.paletteNum + 16)), 4, 0, 8, RGB_RED);
    taskId = CreateTask(sub_8159FEC, 0);
    gTasks[taskId].data[0] = 0;
    FieldEffectActiveListRemove(FLDEFF_SWEET_SCENT);
}

void sub_8159FEC(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        sub_81BE72C();
        BlendPalettes(0x00000040, 8, RGB_RED);
        if (gTasks[taskId].data[0] == 64)
        {
            gTasks[taskId].data[0] = 0;
            if (SweetScentWildEncounter() == TRUE)
            {
                DestroyTask(taskId);
            }
            else
            {
                gTasks[taskId].func = sub_815A090;
                BeginNormalPaletteFade(~(1 << (gSprites[GetPlayerAvatarObjectId()].oam.paletteNum + 16)), 4, 8, 0, RGB_RED);
                sub_81BE6B8();
            }
        }
        else
        {
            gTasks[taskId].data[0]++;
        }
    }
}

void sub_815A090(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CpuFastSet(gPaletteDecompressionBuffer, gPlttBufferUnfaded, 0x100);
        sub_80AC3E4();
        ScriptContext1_SetupScript(EventScript_290CAE);
        DestroyTask(taskId);
    }
}
