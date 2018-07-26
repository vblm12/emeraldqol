	.include "asm/macros.inc"
	.include "constants/constants.inc"

	.syntax unified

	.text

	thumb_func_start sub_8161F74
sub_8161F74: @ 8161F74
	push {lr}
	ldr r1, =gUnknown_085DF96C
	ldr r0, =gSpecialVar_0x8004
	ldrh r0, [r0]
	lsls r0, 2
	adds r0, r1
	ldr r0, [r0]
	bl _call_via_r0
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8161F74

	thumb_func_start sub_8161F94
sub_8161F94: @ 8161F94
	push {r4-r7,lr}
	ldr r4, =gSaveBlock2Ptr
	ldr r0, [r4]
	ldr r1, =0x00000ca9
	adds r0, r1
	ldrb r0, [r0]
	lsls r0, 30
	lsrs r5, r0, 30
	ldr r0, =0x000040ce
	bl VarGet
	lsls r0, 16
	lsrs r6, r0, 16
	ldr r0, [r4]
	ldr r2, =0x00000ca8
	adds r0, r2
	movs r7, 0
	movs r1, 0x1
	strb r1, [r0]
	ldr r1, [r4]
	adds r2, 0xA
	adds r0, r1, r2
	strh r7, [r0]
	ldr r0, =0x00000ca9
	adds r1, r0
	ldrb r2, [r1]
	movs r0, 0x5
	negs r0, r0
	ands r0, r2
	strb r0, [r1]
	ldr r1, [r4]
	ldr r2, =0x00000ca9
	adds r1, r2
	ldrb r2, [r1]
	movs r0, 0x9
	negs r0, r0
	ands r0, r2
	strb r0, [r1]
	bl sub_81A3ACC
	ldr r4, [r4]
	ldr r0, =0x00000cdc
	adds r3, r4, r0
	ldr r2, =gUnknown_085DF9AC
	lsls r1, r5, 2
	lsls r0, r6, 3
	adds r1, r0
	adds r1, r2
	ldr r0, [r3]
	ldr r1, [r1]
	ands r0, r1
	cmp r0, 0
	bne _0816200E
	lsls r0, r5, 1
	lsls r1, r6, 2
	adds r0, r1
	movs r2, 0xCE
	lsls r2, 4
	adds r1, r4, r2
	adds r1, r0
	strh r7, [r1]
_0816200E:
	bl sub_8164ED8
	ldr r0, =gSaveBlock1Ptr
	ldr r0, [r0]
	movs r1, 0x4
	ldrsb r1, [r0, r1]
	movs r2, 0x5
	ldrsb r2, [r0, r2]
	movs r3, 0x1
	negs r3, r3
	movs r0, 0
	bl saved_warp2_set
	ldr r0, =gTrainerBattleOpponent_A
	strh r7, [r0]
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8161F94

	thumb_func_start sub_8162054
sub_8162054: @ 8162054
	push {r4-r6,lr}
	ldr r5, =gSaveBlock2Ptr
	ldr r0, [r5]
	ldr r4, =0x00000ca9
	adds r0, r4
	ldrb r0, [r0]
	lsls r0, 30
	lsrs r6, r0, 30
	ldr r0, =0x000040ce
	bl VarGet
	lsls r0, 16
	lsrs r1, r0, 16
	ldr r0, =gSpecialVar_0x8005
	ldrh r0, [r0]
	cmp r0, 0x1
	beq _08162094
	cmp r0, 0x1
	ble _081620E8
	cmp r0, 0x2
	beq _081620A8
	cmp r0, 0x3
	beq _081620D8
	b _081620E8
	.pool
_08162094:
	adds r0, r6, 0
	lsls r1, 24
	lsrs r1, 24
	bl sub_8164FCC
	ldr r1, =gSpecialVar_Result
	strh r0, [r1]
	b _081620E8
	.pool
_081620A8:
	ldr r4, =gSpecialVar_Result
	ldr r2, [r5]
	ldr r0, =0x00000cdc
	adds r2, r0
	ldr r3, =gUnknown_085DF9AC
	lsls r0, r6, 2
	lsls r1, 3
	adds r0, r1
	adds r0, r3
	ldr r1, [r2]
	ldr r0, [r0]
	ands r1, r0
	negs r0, r1
	orrs r0, r1
	lsrs r0, 31
	strh r0, [r4]
	b _081620E8
	.pool
_081620D8:
	ldr r1, [r5]
	adds r0, r1, r4
	ldrb r0, [r0]
	lsls r0, 30
	lsrs r0, 30
	ldr r2, =0x00000d07
	adds r1, r2
	strb r0, [r1]
_081620E8:
	pop {r4-r6}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8162054

	thumb_func_start sub_81620F4
sub_81620F4: @ 81620F4
	push {r4-r7,lr}
	ldr r6, =gSaveBlock2Ptr
	ldr r0, [r6]
	ldr r7, =0x00000ca9
	adds r0, r7
	ldrb r0, [r0]
	lsls r0, 30
	lsrs r5, r0, 30
	ldr r0, =0x000040ce
	bl VarGet
	lsls r0, 16
	lsrs r4, r0, 16
	ldr r0, =gSpecialVar_0x8005
	ldrh r0, [r0]
	cmp r0, 0x1
	beq _08162134
	cmp r0, 0x1
	ble _081621B4
	cmp r0, 0x2
	beq _08162150
	cmp r0, 0x3
	beq _081621A4
	b _081621B4
	.pool
_08162134:
	ldr r2, [r6]
	lsls r0, r5, 1
	lsls r1, r4, 2
	adds r0, r1
	movs r1, 0xCE
	lsls r1, 4
	adds r2, r1
	adds r2, r0
	ldr r0, =gSpecialVar_0x8006
	ldrh r0, [r0]
	strh r0, [r2]
	b _081621B4
	.pool
_08162150:
	ldr r0, =gSpecialVar_0x8006
	ldrh r0, [r0]
	cmp r0, 0
	beq _08162180
	ldr r2, [r6]
	ldr r0, =0x00000cdc
	adds r2, r0
	ldr r3, =gUnknown_085DF9AC
	lsls r1, r5, 2
	lsls r0, r4, 3
	adds r1, r0
	adds r1, r3
	ldr r0, [r2]
	ldr r1, [r1]
	orrs r0, r1
	str r0, [r2]
	b _081621B4
	.pool
_08162180:
	ldr r2, [r6]
	ldr r1, =0x00000cdc
	adds r2, r1
	ldr r3, =gUnknown_085DF9CC
	lsls r1, r5, 2
	lsls r0, r4, 3
	adds r1, r0
	adds r1, r3
	ldr r0, [r2]
	ldr r1, [r1]
	ands r0, r1
	str r0, [r2]
	b _081621B4
	.pool
_081621A4:
	ldr r1, [r6]
	adds r0, r1, r7
	ldrb r0, [r0]
	lsls r0, 30
	lsrs r0, 30
	ldr r2, =0x00000d07
	adds r1, r2
	strb r0, [r1]
_081621B4:
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_81620F4

	thumb_func_start sub_81621C0
sub_81621C0: @ 81621C0
	push {r4,r5,lr}
	ldr r0, =gTrainerBattleOpponent_A
	ldrh r1, [r0]
	movs r0, 0xFA
	lsls r0, 1
	cmp r1, r0
	bne _081621DA
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0x00000bec
	adds r0, r1
	bl sub_816534C
_081621DA:
	ldr r5, =gSaveBlock2Ptr
	ldr r0, [r5]
	ldr r1, =0x00000d04
	adds r2, r0, r1
	ldrh r1, [r2]
	ldr r0, =0x0000270e
	cmp r1, r0
	bhi _081621EE
	adds r0, r1, 0x1
	strh r0, [r2]
_081621EE:
	ldr r1, [r5]
	ldr r4, =0x00000cb2
	adds r1, r4
	ldrh r0, [r1]
	adds r0, 0x1
	strh r0, [r1]
	bl sub_8163E90
	ldr r1, =gSpecialVar_Result
	ldr r0, [r5]
	adds r0, r4
	ldrh r0, [r0]
	strh r0, [r1]
	pop {r4,r5}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_81621C0

	thumb_func_start sub_816222C
sub_816222C: @ 816222C
	push {r4-r7,lr}
	mov r7, r10
	mov r6, r9
	mov r5, r8
	push {r5-r7}
	sub sp, 0x3C
	movs r0, 0
	str r0, [sp, 0x24]
	ldr r4, =gSaveBlock2Ptr
	ldr r0, [r4]
	ldr r1, =0x00000ca9
	adds r0, r1
	ldrb r0, [r0]
	lsls r0, 30
	lsrs r0, 30
	mov r10, r0
	ldr r0, =0x000040ce
	bl VarGet
	lsls r0, 24
	lsrs r0, 24
	str r0, [sp, 0x2C]
	ldr r0, =0x000040cf
	bl VarGet
	lsls r0, 16
	cmp r0, 0
	beq _08162266
	b _0816239C
_08162266:
	mov r0, r10
	ldr r1, [sp, 0x2C]
	bl sub_8164FCC
	lsls r0, 16
	lsrs r0, 16
	str r0, [sp, 0x28]
	movs r7, 0
	mov r2, sp
	str r2, [sp, 0x34]
_0816227A:
	movs r3, 0xEC
	adds r0, r7, 0
	muls r0, r3
	movs r4, 0xE7
	lsls r4, 3
	adds r0, r4
	ldr r5, =gSaveBlock2Ptr
	ldr r1, [r5]
	movs r2, 0
	mov r8, r2
	mov r9, r2
	movs r5, 0
	adds r3, r7, 0x1
	str r3, [sp, 0x30]
	adds r1, r0
_08162298:
	ldm r1!, {r0}
	mov r4, r8
	orrs r4, r0
	mov r8, r4
	add r9, r0
	adds r5, 0x1
	cmp r5, 0x39
	bls _08162298
	movs r6, 0
	movs r5, 0
	movs r0, 0xEC
	adds r2, r7, 0
	muls r2, r0
_081622B2:
	ldr r3, =gSaveBlock2Ptr
	ldr r1, [r3]
	movs r0, 0x2C
	muls r0, r5
	adds r0, r2
	adds r1, r0
	ldr r4, =0x0000076c
	adds r0, r1, r4
	ldrh r0, [r0]
	cmp r0, 0
	beq _081622E4
	movs r0, 0xEF
	lsls r0, 3
	adds r4, r1, r0
	mov r0, r10
	str r2, [sp, 0x38]
	bl BattleFrontierGetOpponentLvl
	ldrb r1, [r4]
	lsls r0, 24
	lsrs r0, 24
	ldr r2, [sp, 0x38]
	cmp r1, r0
	bhi _081622E4
	adds r6, 0x1
_081622E4:
	adds r5, 0x1
	cmp r5, 0x3
	ble _081622B2
	ldr r0, =gUnknown_085DF9F6
	ldr r1, [sp, 0x2C]
	adds r0, r1, r0
	ldrb r0, [r0]
	cmp r6, r0
	blt _0816233E
	ldr r3, =gSaveBlock2Ptr
	ldr r2, [r3]
	movs r4, 0xEC
	adds r3, r7, 0
	muls r3, r4
	adds r1, r2, r3
	ldr r5, =0x0000073a
	adds r0, r1, r5
	ldrh r0, [r0]
	ldr r4, [sp, 0x28]
	cmp r0, r4
	bne _0816233E
	subs r5, 0x2
	adds r0, r1, r5
	ldrb r0, [r0]
	cmp r0, r10
	bne _0816233E
	mov r0, r8
	cmp r0, 0
	beq _0816233E
	movs r1, 0x82
	lsls r1, 4
	adds r0, r2, r1
	adds r0, r3
	ldr r0, [r0]
	cmp r0, r9
	bne _0816233E
	movs r2, 0x96
	lsls r2, 1
	adds r0, r7, r2
	ldr r3, [sp, 0x34]
	stm r3!, {r0}
	str r3, [sp, 0x34]
	ldr r4, [sp, 0x24]
	adds r4, 0x1
	str r4, [sp, 0x24]
_0816233E:
	ldr r7, [sp, 0x30]
	cmp r7, 0x4
	ble _0816227A
	ldr r5, [sp, 0x2C]
	cmp r5, 0
	bne _08162396
	bl sub_8165B20
	movs r7, 0
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r4, =gUnknown_085DF9EC
	adds r2, r0, 0
	adds r2, 0xDC
	ldr r1, [sp, 0x24]
	lsls r0, r1, 2
	mov r5, sp
	adds r3, r0, r5
_08162362:
	ldrb r0, [r2]
	lsls r1, r0, 25
	lsrs r0, r1, 30
	cmp r0, 0
	beq _0816238E
	ldrb r0, [r2, 0x1]
	adds r0, r4
	ldrb r0, [r0]
	ldr r5, [sp, 0x28]
	cmp r0, r5
	bne _0816238E
	lsrs r0, r1, 30
	subs r0, 0x1
	cmp r0, r10
	bne _0816238E
	movs r1, 0xC8
	lsls r1, 1
	adds r0, r7, r1
	stm r3!, {r0}
	ldr r5, [sp, 0x24]
	adds r5, 0x1
	str r5, [sp, 0x24]
_0816238E:
	adds r2, 0x44
	adds r7, 0x1
	cmp r7, 0x3
	ble _08162362
_08162396:
	ldr r0, [sp, 0x24]
	cmp r0, 0
	bne _081623C0
_0816239C:
	movs r0, 0
	b _081623DA
	.pool
_081623C0:
	ldr r4, =gTrainerBattleOpponent_A
	bl Random
	lsls r0, 16
	lsrs r0, 16
	ldr r1, [sp, 0x24]
	bl __modsi3
	lsls r0, 2
	add r0, sp
	ldr r0, [r0]
	strh r0, [r4]
	movs r0, 0x1
_081623DA:
	add sp, 0x3C
	pop {r3-r5}
	mov r8, r3
	mov r9, r4
	mov r10, r5
	pop {r4-r7}
	pop {r1}
	bx r1
	.pool
	thumb_func_end sub_816222C

	thumb_func_start sub_81623F0
sub_81623F0: @ 81623F0
	push {r4-r7,lr}
	ldr r6, =gSaveBlock2Ptr
	ldr r0, [r6]
	ldr r1, =0x00000ca9
	adds r0, r1
	ldrb r0, [r0]
	lsls r0, 30
	lsrs r0, 30
	cmp r0, 0x2
	bne _08162414
	bl sub_8165E18
	b _08162530
	.pool
_08162414:
	ldr r0, =0x000040ce
	bl VarGet
	adds r4, r0, 0
	lsls r4, 16
	lsrs r4, 16
	bl sub_81A39C4
	lsls r0, 16
	lsrs r0, 16
	movs r1, 0x7
	bl __udivsi3
	lsls r0, 16
	lsrs r5, r0, 16
	bl sub_8165C40
	subs r4, 0x2
	cmp r4, 0x1
	bhi _08162488
	ldr r1, [r6]
	ldr r2, =0x00000cb2
	adds r0, r1, r2
	ldrh r3, [r0]
	ldr r2, =gTrainerBattleOpponent_A
	lsls r0, r3, 2
	ldr r4, =0x00000cb4
	adds r1, r4
	adds r0, r1, r0
	ldrh r0, [r0]
	strh r0, [r2]
	ldr r4, =gTrainerBattleOpponent_B
	lsls r0, r3, 1
	adds r0, 0x1
	lsls r0, 1
	adds r1, r0
	ldrh r0, [r1]
	strh r0, [r4]
	ldrh r0, [r2]
	movs r1, 0
	bl sub_8162614
	ldrh r0, [r4]
	movs r1, 0x1
	bl sub_8162614
	b _08162530
	.pool
_08162488:
	bl sub_816222C
	lsls r0, 24
	cmp r0, 0
	beq _081624B4
	ldr r4, =gTrainerBattleOpponent_A
	ldrh r0, [r4]
	movs r1, 0
	bl sub_8162614
	ldr r1, [r6]
	ldr r2, =0x00000cb2
	adds r0, r1, r2
	ldrh r0, [r0]
	lsls r0, 1
	adds r2, 0x2
	b _08162528
	.pool
_081624B4:
	lsls r7, r5, 24
	adds r5, r6, 0
	ldr r6, =0x00000cb2
_081624BA:
	ldr r0, [r5]
	adds r0, r6
	ldrb r1, [r0]
	lsrs r0, r7, 24
	bl sub_8162548
	lsls r0, 16
	lsrs r3, r0, 16
	movs r4, 0
	ldr r1, [r5]
	adds r0, r1, r6
	ldrh r0, [r0]
	cmp r4, r0
	bge _081624FC
	ldr r2, =0x00000cb4
	adds r0, r1, r2
	ldrh r0, [r0]
	cmp r0, r3
	beq _081624FC
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	subs r2, 0x2
	adds r0, r1, r2
	ldrh r2, [r0]
	ldr r0, =0x00000cb4
	adds r1, r0
_081624EE:
	adds r1, 0x2
	adds r4, 0x1
	cmp r4, r2
	bge _081624FC
	ldrh r0, [r1]
	cmp r0, r3
	bne _081624EE
_081624FC:
	ldr r0, [r5]
	ldr r1, =0x00000cb2
	adds r0, r1
	ldrh r0, [r0]
	cmp r4, r0
	bne _081624BA
	ldr r4, =gTrainerBattleOpponent_A
	strh r3, [r4]
	ldrh r0, [r4]
	movs r1, 0
	bl sub_8162614
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	ldr r2, =0x00000cb2
	adds r0, r1, r2
	ldrh r2, [r0]
	adds r0, r2, 0x1
	cmp r0, 0x6
	bgt _08162530
	lsls r0, r2, 1
	ldr r2, =0x00000cb4
_08162528:
	adds r1, r2
	adds r1, r0
	ldrh r0, [r4]
	strh r0, [r1]
_08162530:
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_81623F0

	thumb_func_start sub_8162548
sub_8162548: @ 8162548
	push {r4,r5,lr}
	lsls r0, 24
	lsrs r0, 24
	adds r3, r0, 0
	lsls r1, 24
	lsrs r1, 24
	cmp r0, 0x7
	bhi _08162584
	cmp r1, 0x6
	bne _08162570
	ldr r2, =gUnknown_085DFA1A
	lsls r1, r0, 2
	adds r0, r2, 0x2
	adds r0, r1, r0
	adds r1, r2
	ldrh r0, [r0]
	ldrh r4, [r1]
	b _0816258A
	.pool
_08162570:
	ldr r2, =gUnknown_085DF9FA
	lsls r1, r3, 2
	adds r0, r2, 0x2
	adds r0, r1, r0
	adds r1, r2
	ldrh r0, [r0]
	ldrh r4, [r1]
	b _0816258A
	.pool
_08162584:
	ldr r1, =gUnknown_085DF9FA
	ldrh r0, [r1, 0x1E]
	ldrh r4, [r1, 0x1C]
_0816258A:
	subs r0, r4
	adds r0, 0x1
	lsls r0, 16
	lsrs r5, r0, 16
	bl Random
	lsls r0, 16
	lsrs r0, 16
	adds r1, r5, 0
	bl __umodsi3
	adds r4, r0
	lsls r4, 16
	lsrs r5, r4, 16
	adds r0, r5, 0
	pop {r4,r5}
	pop {r1}
	bx r1
	.pool
	thumb_func_end sub_8162548

	thumb_func_start sub_81625B4
sub_81625B4: @ 81625B4
	push {r4,lr}
	adds r4, r2, 0
	lsls r0, 24
	lsrs r0, 24
	adds r2, r0, 0
	lsls r1, 24
	lsrs r1, 24
	cmp r0, 0x7
	bhi _081625F4
	cmp r1, 0x6
	bne _081625D4
	ldr r1, =gUnknown_085DFA1A
	lsls r2, r0, 2
	b _081625D8
	.pool
_081625D4:
	ldr r1, =gUnknown_085DF9FA
	lsls r2, 2
_081625D8:
	adds r0, r1, 0x2
	adds r0, r2, r0
	adds r2, r1
	ldrh r0, [r0]
	ldrh r1, [r2]
	subs r0, r1
	adds r0, 0x1
	lsls r0, 16
	lsrs r1, r0, 16
	ldrh r0, [r2]
	b _08162604
	.pool
_081625F4:
	ldr r0, =gUnknown_085DF9FA
	ldrh r1, [r0, 0x1E]
	ldrh r2, [r0, 0x1C]
	subs r1, r2
	adds r1, 0x1
	lsls r1, 16
	lsrs r1, 16
	ldrh r0, [r0, 0x1C]
_08162604:
	strh r0, [r4]
	strb r1, [r3]
	pop {r4}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_81625B4

	thumb_func_start sub_8162614
sub_8162614: @ 8162614
	push {r4-r6,lr}
	lsls r0, 16
	lsrs r4, r0, 16
	adds r6, r4, 0
	lsls r1, 24
	lsrs r5, r1, 24
	bl sub_8165C40
	movs r0, 0xFA
	lsls r0, 1
	cmp r4, r0
	bne _08162640
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0x00000bed
	adds r0, r1
	b _081626BA
	.pool
_08162640:
	ldr r0, =0x000003fe
	cmp r4, r0
	bne _08162650
	bl sub_81A4DD8
	b _08162788
	.pool
_08162650:
	ldr r0, =0x0000012b
	cmp r4, r0
	bhi _0816266C
	ldr r0, =gUnknown_0203BC88
	ldr r1, [r0]
	movs r0, 0x34
	muls r0, r4
	adds r0, r1
	b _081626BA
	.pool
_0816266C:
	ldr r0, =0x0000018f
	cmp r4, r0
	bhi _08162698
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0xfffffed4
	adds r2, r4, r1
	movs r1, 0xEC
	muls r1, r2
	adds r0, r1
	ldr r1, =0x00000739
	adds r0, r1
	b _081626BA
	.pool
_08162698:
	ldr r3, =gUnknown_08610970
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	ldr r0, =0xfffffe70
	adds r2, r6, r0
	lsls r0, r2, 4
	adds r0, r2
	lsls r0, 2
	adds r1, r0
	adds r1, 0xDC
	ldrb r0, [r1]
	lsls r0, 27
	lsrs r0, 27
	movs r1, 0x58
	muls r0, r1
	adds r0, r3
	adds r0, 0x32
_081626BA:
	ldrb r2, [r0]
	movs r1, 0
	ldr r3, =gUnknown_085DCEDC
	ldrb r0, [r3]
	cmp r0, r2
	beq _081626D4
_081626C6:
	adds r1, 0x1
	cmp r1, 0x1D
	bhi _081626D4
	adds r0, r1, r3
	ldrb r0, [r0]
	cmp r0, r2
	bne _081626C6
_081626D4:
	cmp r1, 0x1E
	beq _08162700
	ldr r0, =gUnknown_085DCF0E
	adds r0, r1, r0
	ldrb r1, [r0]
	cmp r5, 0x1
	beq _08162744
	cmp r5, 0x1
	ble _0816272E
	cmp r5, 0xF
	bne _0816272E
	b _08162750
	.pool
_08162700:
	movs r1, 0
	ldr r3, =gUnknown_085DCEFA
	ldrb r0, [r3]
	cmp r0, r2
	beq _08162718
_0816270A:
	adds r1, 0x1
	cmp r1, 0x13
	bhi _08162718
	adds r0, r1, r3
	ldrb r0, [r0]
	cmp r0, r2
	bne _0816270A
_08162718:
	cmp r1, 0x14
	beq _0816275C
	ldr r0, =gUnknown_085DCF2C
	adds r0, r1, r0
	ldrb r1, [r0]
	cmp r5, 0x1
	beq _08162744
	cmp r5, 0x1
	ble _0816272E
	cmp r5, 0xF
	beq _08162750
_0816272E:
	ldr r0, =0x00004010
	bl VarSet
	b _08162788
	.pool
_08162744:
	ldr r0, =0x00004011
	bl VarSet
	b _08162788
	.pool
_08162750:
	ldr r0, =0x0000401e
	bl VarSet
	b _08162788
	.pool
_0816275C:
	cmp r5, 0x1
	beq _08162770
	cmp r5, 0x1
	ble _08162768
	cmp r5, 0xF
	beq _08162780
_08162768:
	ldr r0, =0x00004010
	b _08162772
	.pool
_08162770:
	ldr r0, =0x00004011
_08162772:
	movs r1, 0x7
	bl VarSet
	b _08162788
	.pool
_08162780:
	ldr r0, =0x0000401e
	movs r1, 0x7
	bl VarSet
_08162788:
	pop {r4-r6}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8162614

	thumb_func_start sub_8162794
sub_8162794: @ 8162794
	push {lr}
	movs r0, 0xFA
	lsls r0, 1
	movs r1, 0
	bl sub_8162614
	pop {r0}
	bx r0
	thumb_func_end sub_8162794

	thumb_func_start sub_81627A4
sub_81627A4: @ 81627A4
	push {r4,r5,lr}
	lsls r0, 16
	lsrs r4, r0, 16
	adds r5, r4, 0
	bl sub_8165C40
	movs r0, 0xFA
	lsls r0, 1
	cmp r4, r0
	bne _081627CC
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0x00000bed
	adds r0, r1
	b _08162836
	.pool
_081627CC:
	ldr r0, =0x0000012b
	cmp r4, r0
	bhi _081627E8
	ldr r0, =gUnknown_0203BC88
	ldr r1, [r0]
	movs r0, 0x34
	muls r0, r4
	adds r0, r1
	b _08162836
	.pool
_081627E8:
	ldr r0, =0x0000018f
	cmp r4, r0
	bhi _08162814
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0xfffffed4
	adds r2, r4, r1
	movs r1, 0xEC
	muls r1, r2
	adds r0, r1
	ldr r1, =0x00000739
	adds r0, r1
	b _08162836
	.pool
_08162814:
	ldr r3, =gUnknown_08610970
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	ldr r0, =0xfffffe70
	adds r2, r5, r0
	lsls r0, r2, 4
	adds r0, r2
	lsls r0, 2
	adds r1, r0
	adds r1, 0xDC
	ldrb r0, [r1]
	lsls r0, 27
	lsrs r0, 27
	movs r1, 0x58
	muls r0, r1
	adds r0, r3
	adds r0, 0x32
_08162836:
	ldrb r2, [r0]
	movs r1, 0
	ldr r3, =gUnknown_085DCEDC
	ldrb r0, [r3]
	cmp r0, r2
	beq _08162850
_08162842:
	adds r1, 0x1
	cmp r1, 0x1D
	bhi _08162850
	adds r0, r1, r3
	ldrb r0, [r0]
	cmp r0, r2
	bne _08162842
_08162850:
	cmp r1, 0x1E
	beq _0816286C
	ldr r0, =gUnknown_085DCF0E
	b _08162892
	.pool
_0816286C:
	movs r1, 0
	ldr r3, =gUnknown_085DCEFA
	ldrb r0, [r3]
	cmp r0, r2
	beq _08162884
_08162876:
	adds r1, 0x1
	cmp r1, 0x13
	bhi _08162884
	adds r0, r1, r3
	ldrb r0, [r0]
	cmp r0, r2
	bne _08162876
_08162884:
	cmp r1, 0x14
	bne _08162890
	movs r0, 0x7
	b _08162896
	.pool
_08162890:
	ldr r0, =gUnknown_085DCF2C
_08162892:
	adds r0, r1, r0
	ldrb r0, [r0]
_08162896:
	pop {r4,r5}
	pop {r1}
	bx r1
	.pool
	thumb_func_end sub_81627A4

	thumb_func_start sub_81628A0
sub_81628A0: @ 81628A0
	push {r4-r7,lr}
	mov r7, r10
	mov r6, r9
	mov r5, r8
	push {r5-r7}
	sub sp, 0x20
	movs r1, 0
	mov r8, r1
	mov r10, r0
	movs r5, 0
	ldr r2, =gSaveBlock2Ptr
	ldr r0, [r2]
	mov r4, r10
	ldrb r4, [r4, 0xC]
	str r4, [sp, 0x18]
	mov r9, r5
	movs r7, 0x4
	str r7, [sp, 0x1C]
	ldr r1, =0x00000744
	adds r1, r0
	mov r12, r1
_081628CA:
	movs r6, 0
	movs r3, 0
	mov r2, r12
	ldrb r0, [r2]
	ldr r4, [sp, 0x18]
	cmp r0, r4
	bne _081628FA
	mov r4, r9
	mov r2, r10
	adds r2, 0xC
_081628DE:
	adds r3, 0x1
	cmp r3, 0x3
	bgt _081628FA
	ldr r7, =gSaveBlock2Ptr
	ldr r0, [r7]
	adds r1, r3, r4
	ldr r7, =0x00000744
	adds r0, r7
	adds r0, r1
	adds r1, r2, r3
	ldrb r0, [r0]
	ldrb r1, [r1]
	cmp r0, r1
	beq _081628DE
_081628FA:
	cmp r3, 0x4
	bne _08162944
	movs r6, 0
	ldr r1, =gSaveBlock2Ptr
	ldr r0, [r1]
	ldr r3, =0x0000073c
	adds r0, r3
	ldr r2, [sp, 0x1C]
	adds r0, r2
	ldrb r0, [r0]
	mov r4, r10
	ldrb r4, [r4, 0x8]
	cmp r0, r4
	bne _08162944
	adds r1, r0, 0
	mov r2, r9
	adds r2, 0x4
_0816291C:
	cmp r1, 0xFF
	bne _08162930
	movs r6, 0x7
	b _08162944
	.pool
_08162930:
	adds r6, 0x1
	cmp r6, 0x6
	bgt _08162944
	ldr r7, =gSaveBlock2Ptr
	ldr r0, [r7]
	adds r0, r3
	adds r0, r2
	ldrb r0, [r0]
	cmp r0, r1
	beq _0816291C
_08162944:
	cmp r6, 0x7
	beq _0816295A
	movs r0, 0xEC
	add r9, r0
	ldr r1, [sp, 0x1C]
	adds r1, 0xEC
	str r1, [sp, 0x1C]
	add r12, r0
	adds r5, 0x1
	cmp r5, 0x4
	ble _081628CA
_0816295A:
	cmp r5, 0x4
	bgt _08162974
	ldr r2, =gSaveBlock2Ptr
	ldr r0, [r2]
	movs r1, 0xEC
	muls r1, r5
	adds r0, r1
	movs r4, 0xE7
	lsls r4, 3
	adds r0, r4
	b _081629B2
	.pool
_08162974:
	movs r5, 0
	ldr r7, =gSaveBlock2Ptr
	ldr r0, [r7]
	ldr r1, =0x0000073a
	adds r0, r1
	ldrh r0, [r0]
	cmp r0, 0
	beq _0816299E
	adds r3, r7, 0
	adds r2, r1, 0
	movs r1, 0
_0816298A:
	adds r1, 0xEC
	adds r5, 0x1
	cmp r5, 0x4
	bgt _081629C4
	ldr r0, [r3]
	adds r0, r1
	adds r0, r2
	ldrh r0, [r0]
	cmp r0, 0
	bne _0816298A
_0816299E:
	cmp r5, 0x4
	bgt _081629C4
	ldr r1, =gSaveBlock2Ptr
	ldr r0, [r1]
	movs r1, 0xEC
	muls r1, r5
	adds r0, r1
	movs r2, 0xE7
	lsls r2, 3
	adds r0, r2
_081629B2:
	mov r1, r10
	movs r2, 0xEC
	bl memcpy
	b _08162A8A
	.pool
_081629C4:
	mov r2, sp
	ldr r4, =gSaveBlock2Ptr
	ldr r0, [r4]
	ldr r3, =0x0000073a
	adds r0, r3
	ldrh r0, [r0]
	movs r1, 0
	strh r0, [r2]
	add r0, sp, 0xC
	strh r1, [r0]
	movs r7, 0x1
	add r8, r7
	movs r5, 0x1
	add r0, sp, 0xC
	mov r9, r0
	mov r12, r3
_081629E4:
	movs r3, 0
	adds r7, r5, 0x1
	cmp r3, r8
	bge _08162A2E
	ldr r1, =gSaveBlock2Ptr
	ldr r0, [r1]
	movs r2, 0xEC
	adds r1, r5, 0
	muls r1, r2
	adds r0, r1
	mov r1, r12
	adds r4, r0, r1
	mov r6, sp
_081629FE:
	lsls r0, r3, 1
	add r0, sp
	ldrh r2, [r4]
	adds r1, r2, 0
	ldrh r0, [r0]
	cmp r1, r0
	bcs _08162A24
	movs r3, 0
	movs r4, 0x1
	mov r8, r4
	strh r2, [r6]
	mov r0, r9
	strh r5, [r0]
	b _08162A2E
	.pool
_08162A24:
	cmp r1, r0
	bhi _08162A2E
	adds r3, 0x1
	cmp r3, r8
	blt _081629FE
_08162A2E:
	cmp r3, r8
	bne _08162A54
	mov r1, r8
	lsls r2, r1, 1
	mov r4, sp
	adds r3, r4, r2
	ldr r1, =gSaveBlock2Ptr
	ldr r0, [r1]
	movs r4, 0xEC
	adds r1, r5, 0
	muls r1, r4
	adds r0, r1
	add r0, r12
	ldrh r0, [r0]
	strh r0, [r3]
	add r2, r9
	strh r5, [r2]
	movs r0, 0x1
	add r8, r0
_08162A54:
	adds r5, r7, 0
	cmp r5, 0x4
	ble _081629E4
	bl Random
	lsls r0, 16
	lsrs r0, 16
	mov r1, r8
	bl __modsi3
	adds r5, r0, 0
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	lsls r1, r5, 1
	add r1, sp
	adds r1, 0xC
	ldrh r2, [r1]
	movs r1, 0xEC
	muls r1, r2
	adds r0, r1
	movs r1, 0xE7
	lsls r1, 3
	adds r0, r1
	mov r1, r10
	movs r2, 0xEC
	bl memcpy
_08162A8A:
	add sp, 0x20
	pop {r3-r5}
	mov r8, r3
	mov r9, r4
	mov r10, r5
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_81628A0

	thumb_func_start GetFrontierTrainerFrontSpriteId
GetFrontierTrainerFrontSpriteId: @ 8162AA0
	push {r4,r5,lr}
	lsls r0, 16
	lsrs r4, r0, 16
	adds r5, r4, 0
	bl sub_8165C40
	movs r0, 0xFA
	lsls r0, 1
	cmp r4, r0
	bne _08162AD0
	ldr r1, =gFacilityClassToPicIndex
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r2, =0x00000bed
	adds r0, r2
	ldrb r0, [r0]
	adds r0, r1
	b _08162BC8
	.pool
_08162AD0:
	ldr r0, =0x000003fe
	cmp r4, r0
	bne _08162AE4
	bl GetFrontierBrainTrainerPicIndex
	lsls r0, 24
	lsrs r0, 24
	b _08162BCA
	.pool
_08162AE4:
	ldr r0, =0x0000012b
	cmp r4, r0
	bhi _08162B08
	ldr r2, =gFacilityClassToPicIndex
	ldr r0, =gUnknown_0203BC88
	ldr r1, [r0]
	movs r0, 0x34
	muls r0, r4
	adds r0, r1
	ldrb r0, [r0]
	adds r0, r2
	b _08162BC8
	.pool
_08162B08:
	ldr r0, =0x0000018f
	cmp r4, r0
	bhi _08162B64
	ldr r0, =gBattleTypeFlags
	ldr r0, [r0]
	movs r1, 0x80
	lsls r1, 17
	ands r0, r1
	cmp r0, 0
	beq _08162B38
	ldr r4, =gFacilityClassToPicIndex
	bl sub_818649C
	lsls r0, 24
	lsrs r0, 24
	adds r0, r4
	b _08162BC8
	.pool
_08162B38:
	ldr r3, =gFacilityClassToPicIndex
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0xfffffed4
	adds r2, r4, r1
	movs r1, 0xEC
	muls r1, r2
	adds r0, r1
	ldr r2, =0x00000739
	adds r0, r2
	ldrb r0, [r0]
	adds r0, r3
	b _08162BC8
	.pool
_08162B64:
	ldr r0, =gBattleTypeFlags
	ldr r0, [r0]
	movs r1, 0x80
	lsls r1, 17
	ands r0, r1
	cmp r0, 0
	bne _08162BB0
	ldr r4, =gFacilityClassToPicIndex
	ldr r3, =gUnknown_08610970
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	ldr r0, =0xfffffe70
	adds r2, r5, r0
	lsls r0, r2, 4
	adds r0, r2
	lsls r0, 2
	adds r1, r0
	adds r1, 0xDC
	ldrb r0, [r1]
	lsls r0, 27
	lsrs r0, 27
	movs r1, 0x58
	muls r0, r1
	adds r0, r3
	adds r0, 0x32
	ldrb r0, [r0]
	adds r0, r4
	b _08162BC8
	.pool
_08162BB0:
	ldr r5, =gFacilityClassToPicIndex
	ldr r4, =gUnknown_08610970
	bl sub_81864A8
	lsls r0, 24
	lsrs r0, 24
	movs r1, 0x58
	muls r0, r1
	adds r0, r4
	adds r0, 0x32
	ldrb r0, [r0]
	adds r0, r5
_08162BC8:
	ldrb r0, [r0]
_08162BCA:
	pop {r4,r5}
	pop {r1}
	bx r1
	.pool
	thumb_func_end GetFrontierTrainerFrontSpriteId

	thumb_func_start GetFrontierOpponentClass
GetFrontierOpponentClass: @ 8162BD8
	push {r4,r5,lr}
	lsls r0, 16
	lsrs r4, r0, 16
	adds r5, r4, 0
	bl sub_8165C40
	movs r0, 0xFA
	lsls r0, 1
	cmp r4, r0
	bne _08162C08
	ldr r1, =gFacilityClassToTrainerClass
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r2, =0x00000bed
	adds r0, r2
	ldrb r0, [r0]
	b _08162C26
	.pool
_08162C08:
	ldr r0, =0x000003fe
	cmp r4, r0
	bne _08162C1C
	bl GetFrontierBrainTrainerClass
	lsls r0, 24
	lsrs r0, 24
	b _08162D1E
	.pool
_08162C1C:
	ldr r0, =0x00000c03
	cmp r4, r0
	bne _08162C38
	ldr r0, =gTrainers
	ldr r1, =0x00007da1
_08162C26:
	adds r0, r1
	ldrb r0, [r0]
	b _08162D1E
	.pool
_08162C38:
	ldr r0, =0x0000012b
	cmp r4, r0
	bhi _08162C60
	ldr r2, =gFacilityClassToTrainerClass
	ldr r0, =gUnknown_0203BC88
	ldr r1, [r0]
	movs r0, 0x34
	muls r0, r4
	adds r0, r1
	ldrb r0, [r0]
	adds r0, r2
	ldrb r0, [r0]
	b _08162D1E
	.pool
_08162C60:
	ldr r0, =0x0000018f
	cmp r4, r0
	bhi _08162CBC
	ldr r0, =gBattleTypeFlags
	ldr r0, [r0]
	movs r1, 0x80
	lsls r1, 17
	ands r0, r1
	cmp r0, 0
	beq _08162C90
	ldr r4, =gFacilityClassToTrainerClass
	bl sub_818649C
	lsls r0, 24
	lsrs r0, 24
	adds r0, r4
	ldrb r0, [r0]
	b _08162D1E
	.pool
_08162C90:
	ldr r3, =gFacilityClassToTrainerClass
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0xfffffed4
	adds r2, r4, r1
	movs r1, 0xEC
	muls r1, r2
	adds r0, r1
	ldr r2, =0x00000739
	adds r0, r2
	ldrb r0, [r0]
	adds r0, r3
	ldrb r0, [r0]
	b _08162D1E
	.pool
_08162CBC:
	ldr r0, =gBattleTypeFlags
	ldr r0, [r0]
	movs r1, 0x80
	lsls r1, 17
	ands r0, r1
	cmp r0, 0
	beq _08162CF4
	ldr r5, =gFacilityClassToTrainerClass
	ldr r4, =gUnknown_08610970
	bl sub_81864A8
	lsls r0, 24
	lsrs r0, 24
	movs r1, 0x58
	muls r0, r1
	adds r0, r4
	adds r0, 0x32
	ldrb r0, [r0]
	adds r0, r5
	ldrb r0, [r0]
	b _08162D1E
	.pool
_08162CF4:
	ldr r4, =gFacilityClassToTrainerClass
	ldr r3, =gUnknown_08610970
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	ldr r0, =0xfffffe70
	adds r2, r5, r0
	lsls r0, r2, 4
	adds r0, r2
	lsls r0, 2
	adds r1, r0
	adds r1, 0xDC
	ldrb r0, [r1]
	lsls r0, 27
	lsrs r0, 27
	movs r1, 0x58
	muls r0, r1
	adds r0, r3
	adds r0, 0x32
	ldrb r0, [r0]
	adds r0, r4
	ldrb r0, [r0]
_08162D1E:
	pop {r4,r5}
	pop {r1}
	bx r1
	.pool
	thumb_func_end GetFrontierOpponentClass

	thumb_func_start sub_8162D34
sub_8162D34: @ 8162D34
	push {r4,r5,lr}
	lsls r0, 16
	lsrs r4, r0, 16
	adds r5, r4, 0
	bl sub_8165C40
	movs r0, 0xFA
	lsls r0, 1
	cmp r4, r0
	bne _08162D5C
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0x00000bed
	adds r0, r1
	b _08162E0A
	.pool
_08162D5C:
	ldr r0, =0x0000012b
	cmp r4, r0
	bhi _08162D78
	ldr r0, =gUnknown_0203BC88
	ldr r1, [r0]
	movs r0, 0x34
	muls r0, r4
	adds r0, r1
	b _08162E0A
	.pool
_08162D78:
	ldr r0, =0x0000018f
	cmp r4, r0
	bhi _08162DC0
	ldr r0, =gBattleTypeFlags
	ldr r0, [r0]
	movs r1, 0x80
	lsls r1, 17
	ands r0, r1
	cmp r0, 0
	beq _08162DA0
	bl sub_818649C
	lsls r0, 24
	lsrs r0, 24
	b _08162E0C
	.pool
_08162DA0:
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0xfffffed4
	adds r2, r4, r1
	movs r1, 0xEC
	muls r1, r2
	adds r0, r1
	ldr r1, =0x00000739
	adds r0, r1
	b _08162E0A
	.pool
_08162DC0:
	ldr r0, =gBattleTypeFlags
	ldr r0, [r0]
	movs r1, 0x80
	lsls r1, 17
	ands r0, r1
	cmp r0, 0
	beq _08162DE8
	ldr r4, =gUnknown_08610970
	bl sub_81864A8
	lsls r0, 24
	lsrs r0, 24
	movs r1, 0x58
	muls r0, r1
	adds r0, r4
	b _08162E08
	.pool
_08162DE8:
	ldr r3, =gUnknown_08610970
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	ldr r0, =0xfffffe70
	adds r2, r5, r0
	lsls r0, r2, 4
	adds r0, r2
	lsls r0, 2
	adds r1, r0
	adds r1, 0xDC
	ldrb r0, [r1]
	lsls r0, 27
	lsrs r0, 27
	movs r1, 0x58
	muls r0, r1
	adds r0, r3
_08162E08:
	adds r0, 0x32
_08162E0A:
	ldrb r0, [r0]
_08162E0C:
	pop {r4,r5}
	pop {r1}
	bx r1
	.pool
	thumb_func_end sub_8162D34

	thumb_func_start GetFrontierTrainerName
GetFrontierTrainerName: @ 8162E20
	push {r4-r6,lr}
	adds r6, r0, 0
	lsls r1, 16
	lsrs r5, r1, 16
	movs r4, 0
	bl sub_8165C40
	movs r0, 0xFA
	lsls r0, 1
	cmp r5, r0
	bne _08162E54
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	movs r1, 0xBF
	lsls r1, 4
	adds r2, r0, r1
_08162E40:
	adds r0, r6, r4
	adds r1, r2, r4
	ldrb r1, [r1]
	strb r1, [r0]
	adds r4, 0x1
	cmp r4, 0x6
	ble _08162E40
	b _08162F5C
	.pool
_08162E54:
	ldr r0, =0x000003fe
	cmp r5, r0
	bne _08162E68
	adds r0, r6, 0
	bl CopyFrontierBrainTrainerName
	b _08162F62
	.pool
_08162E68:
	ldr r0, =0x00000c03
	cmp r5, r0
	bne _08162E88
	ldr r2, =gTrainers + 804 * 0x28 + 0x4 @ TRAINER_STEVEN name
_08162E70:
	adds r0, r6, r4
	adds r1, r4, r2
	ldrb r1, [r1]
	strb r1, [r0]
	adds r4, 0x1
	cmp r4, 0x6
	ble _08162E70
	b _08162F5C
	.pool
_08162E88:
	ldr r0, =0x0000012b
	cmp r5, r0
	bhi _08162EB4
	ldr r0, =gUnknown_0203BC88
	ldr r1, [r0]
	movs r0, 0x34
	muls r0, r5
	adds r0, r1
	adds r2, r0, 0x4
_08162E9A:
	adds r0, r6, r4
	adds r1, r2, r4
	ldrb r1, [r1]
	strb r1, [r0]
	adds r4, 0x1
	cmp r4, 0x6
	ble _08162E9A
	b _08162F5C
	.pool
_08162EB4:
	ldr r0, =0x0000018f
	cmp r5, r0
	bhi _08162F00
	ldr r0, =gBattleTypeFlags
	ldr r0, [r0]
	movs r1, 0x80
	lsls r1, 17
	ands r0, r1
	cmp r0, 0
	beq _08162ED8
	adds r0, r6, 0
	bl sub_8186468
	b _08162F62
	.pool
_08162ED8:
	ldr r2, =gSaveBlock2Ptr
	movs r0, 0xEC
	adds r1, r5, 0
	muls r1, r0
	ldr r0, =0xfffef2a8
	adds r1, r0
	ldr r0, [r2]
	adds r0, r1
	adds r1, r0, 0x4
	adds r0, 0xE4
	ldrb r2, [r0]
	adds r0, r6, 0
	bl TVShowConvertInternationalString
	b _08162F62
	.pool
_08162F00:
	ldr r0, =gBattleTypeFlags
	ldr r0, [r0]
	movs r1, 0x80
	lsls r1, 17
	ands r0, r1
	cmp r0, 0
	beq _08162F24
	bl sub_81864A8
	lsls r0, 24
	lsrs r5, r0, 24
	bl sub_81864C0
	lsls r0, 24
	lsrs r4, r0, 24
	b _08162F3E
	.pool
_08162F24:
	ldr r1, =gSaveBlock2Ptr
	lsls r0, r5, 4
	adds r0, r5
	lsls r0, 2
	ldr r2, =0xffff969c
	adds r0, r2
	ldr r1, [r1]
	adds r1, r0
	ldrb r0, [r1]
	lsls r0, 27
	lsrs r5, r0, 27
	adds r1, 0x3F
	ldrb r4, [r1]
_08162F3E:
	adds r0, r5, 0
	adds r1, r4, 0
	bl sub_81A1650
	adds r1, r0, 0
	adds r0, r6, 0
	adds r2, r4, 0
	bl TVShowConvertInternationalString
	b _08162F62
	.pool
_08162F5C:
	adds r1, r6, r4
	movs r0, 0xFF
	strb r0, [r1]
_08162F62:
	pop {r4-r6}
	pop {r0}
	bx r0
	thumb_func_end GetFrontierTrainerName

	thumb_func_start sub_8162F68
sub_8162F68: @ 8162F68
	push {r4,r5,lr}
	lsls r0, 16
	lsrs r4, r0, 16
	adds r5, r4, 0
	bl sub_8165C40
	movs r0, 0xFA
	lsls r0, 1
	cmp r4, r0
	bne _08162F90
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0x00000bed
	adds r0, r1
	b _0816300E
	.pool
_08162F90:
	ldr r0, =0x000003fe
	cmp r4, r0
	bne _08162FA4
	bl sub_81A4DB8
	lsls r0, 24
	lsrs r0, 24
	b _08163042
	.pool
_08162FA4:
	ldr r0, =0x0000012b
	cmp r4, r0
	bhi _08162FC0
	ldr r0, =gUnknown_0203BC88
	ldr r1, [r0]
	movs r0, 0x34
	muls r0, r4
	adds r0, r1
	b _0816300E
	.pool
_08162FC0:
	ldr r0, =0x0000018f
	cmp r4, r0
	bhi _08162FEC
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0xfffffed4
	adds r2, r4, r1
	movs r1, 0xEC
	muls r1, r2
	adds r0, r1
	ldr r1, =0x00000739
	adds r0, r1
	b _0816300E
	.pool
_08162FEC:
	ldr r3, =gUnknown_08610970
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	ldr r0, =0xfffffe70
	adds r2, r5, r0
	lsls r0, r2, 4
	adds r0, r2
	lsls r0, 2
	adds r1, r0
	adds r1, 0xDC
	ldrb r0, [r1]
	lsls r0, 27
	lsrs r0, 27
	movs r1, 0x58
	muls r0, r1
	adds r0, r3
	adds r0, 0x32
_0816300E:
	ldrb r2, [r0]
	movs r1, 0
	ldr r3, =gUnknown_085DCEFA
	ldrb r0, [r3]
	cmp r0, r2
	beq _08163028
_0816301A:
	adds r1, 0x1
	cmp r1, 0x13
	bhi _08163028
	adds r0, r1, r3
	ldrb r0, [r0]
	cmp r0, r2
	bne _0816301A
_08163028:
	cmp r1, 0x14
	bne _08163040
	movs r0, 0
	b _08163042
	.pool
_08163040:
	movs r0, 0x1
_08163042:
	pop {r4,r5}
	pop {r1}
	bx r1
	thumb_func_end sub_8162F68

	thumb_func_start sub_8163048
sub_8163048: @ 8163048
	push {r4,lr}
	adds r4, r0, 0
	lsls r4, 24
	lsrs r4, 24
	bl ZeroEnemyPartyMons
	ldr r0, =gTrainerBattleOpponent_A
	ldrh r0, [r0]
	movs r1, 0
	adds r2, r4, 0
	bl sub_81630C4
	pop {r4}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8163048

	thumb_func_start sub_816306C
sub_816306C: @ 816306C
	push {r4,lr}
	adds r4, r0, 0
	lsls r4, 24
	lsrs r4, 24
	bl ZeroEnemyPartyMons
	ldr r0, =gTrainerBattleOpponent_A
	ldrh r0, [r0]
	movs r1, 0
	adds r2, r4, 0
	bl sub_81630C4
	ldr r0, =gTrainerBattleOpponent_B
	ldrh r0, [r0]
	movs r1, 0x3
	adds r2, r4, 0
	bl sub_81630C4
	pop {r4}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_816306C

	thumb_func_start sub_81630A0
sub_81630A0: @ 81630A0
	push {r4,lr}
	adds r4, r0, 0
	lsls r4, 24
	lsrs r4, 24
	bl ZeroEnemyPartyMons
	ldr r0, =gTrainerBattleOpponent_A
	ldrh r0, [r0]
	movs r1, 0
	adds r2, r4, 0
	bl sub_8165EA4
	pop {r4}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_81630A0

	thumb_func_start sub_81630C4
sub_81630C4: @ 81630C4
	push {r4-r7,lr}
	mov r7, r10
	mov r6, r9
	mov r5, r8
	push {r5-r7}
	sub sp, 0x40
	lsls r0, 16
	lsrs r5, r0, 16
	lsls r1, 24
	lsrs r1, 24
	str r1, [sp, 0x18]
	lsls r2, 24
	lsrs r2, 24
	str r2, [sp, 0x1C]
	add r4, sp, 0x14
	movs r0, 0xFF
	strb r0, [r4]
	bl sub_8165C40
	lsls r0, 24
	lsrs r0, 24
	str r0, [sp, 0x20]
	ldr r0, =0x0000012b
	cmp r5, r0
	bhi _08163138
	adds r0, r5, 0
	bl sub_8165D08
	lsls r0, 24
	lsrs r0, 24
	str r0, [sp, 0x24]
	ldr r0, =gTrainerBattleOpponent_A
	ldrh r2, [r0]
	ldr r0, =gUnknown_0203BC88
	ldr r1, [r0]
	movs r0, 0x34
	muls r0, r2
	adds r0, r1
	ldr r0, [r0, 0x30]
	str r0, [sp, 0x2C]
	movs r0, 0
	str r0, [sp, 0x28]
	ldr r2, [sp, 0x2C]
	ldrh r1, [r2]
	ldr r0, =0x0000ffff
	cmp r1, r0
	bne _08163124
	b _08163278
_08163124:
	b _08163260
	.pool
_08163138:
	movs r0, 0xFA
	lsls r0, 1
	cmp r5, r0
	bne _08163180
	ldr r7, [sp, 0x18]
	adds r0, r7, 0x3
	cmp r7, r0
	blt _0816314A
	b _08163426
_0816314A:
	ldr r4, =gSaveBlock2Ptr
_0816314C:
	movs r0, 0x64
	muls r0, r7
	ldr r1, =gEnemyParty
	adds r0, r1
	ldr r5, [sp, 0x18]
	subs r2, r7, r5
	movs r1, 0x2C
	muls r2, r1
	movs r6, 0xC2
	lsls r6, 4
	adds r2, r6
	ldr r1, [r4]
	adds r1, r2
	bl sub_806819C
	adds r7, 0x1
	adds r0, r5, 0
	adds r0, 0x3
	cmp r7, r0
	blt _0816314C
	b _08163426
	.pool
_08163180:
	ldr r0, =0x000003fe
	cmp r5, r0
	bne _08163190
	bl sub_81A4E04
	b _08163426
	.pool
_08163190:
	ldr r0, =0x0000018f
	cmp r5, r0
	bhi _08163218
	movs r6, 0
	ldr r7, [sp, 0x18]
	ldr r1, [sp, 0x1C]
	adds r0, r7, r1
	cmp r7, r0
	blt _081631A4
	b _08163426
_081631A4:
	ldr r2, =0xfffffed4
	adds r1, r5, r2
	movs r0, 0xEC
	adds r2, r1, 0
	muls r2, r0
	mov r8, r2
	muls r0, r5
	ldr r5, =0xfffef2a8
	adds r4, r0, r5
_081631B6:
	ldr r0, =gSaveBlock2Ptr
	ldr r3, [r0]
	movs r0, 0x2C
	adds r2, r6, 0
	muls r2, r0
	mov r1, r8
	adds r0, r2, r1
	adds r1, r3, r0
	ldr r5, =0x0000076c
	adds r0, r1, r5
	ldrh r0, [r0]
	cmp r0, 0
	beq _081631F0
	adds r5, 0xC
	adds r0, r1, r5
	ldrb r0, [r0]
	ldr r1, [sp, 0x20]
	cmp r0, r1
	bhi _081631F0
	movs r0, 0x64
	muls r0, r7
	ldr r1, =gEnemyParty
	adds r0, r1
	adds r1, r3, r4
	adds r2, 0x34
	adds r1, r2
	movs r2, 0
	bl sub_8068338
_081631F0:
	adds r6, 0x1
	adds r7, 0x1
	ldr r2, [sp, 0x18]
	ldr r5, [sp, 0x1C]
	adds r0, r2, r5
	cmp r7, r0
	blt _081631B6
	b _08163426
	.pool
_08163218:
	ldr r7, [sp, 0x18]
	adds r0, r7, 0x3
	cmp r7, r0
	blt _08163222
	b _08163426
_08163222:
	ldr r6, =gSaveBlock2Ptr
	lsls r0, r5, 4
	adds r0, r5
	lsls r0, 2
	ldr r1, =0xffff969c
	adds r5, r0, r1
	movs r4, 0
_08163230:
	movs r0, 0x64
	muls r0, r7
	ldr r1, =gEnemyParty
	adds r0, r1
	ldr r1, [r6]
	adds r1, r5
	lsrs r2, r4, 24
	bl sub_8068528
	movs r2, 0x80
	lsls r2, 17
	adds r4, r2
	adds r7, 0x1
	ldr r0, [sp, 0x18]
	adds r0, 0x3
	cmp r7, r0
	blt _08163230
	b _08163426
	.pool
_08163260:
	ldr r0, [sp, 0x28]
	adds r0, 0x1
	lsls r0, 24
	lsrs r0, 24
	str r0, [sp, 0x28]
	lsls r0, 1
	ldr r5, [sp, 0x2C]
	adds r0, r5
	ldrh r1, [r0]
	ldr r0, =0x0000ffff
	cmp r1, r0
	bne _08163260
_08163278:
	movs r7, 0
	bl Random
	adds r4, r0, 0
	bl Random
	lsls r4, 16
	lsrs r4, 16
	lsls r0, 16
	orrs r4, r0
	str r4, [sp, 0x30]
	ldr r6, [sp, 0x1C]
	cmp r7, r6
	bne _08163296
	b _08163426
_08163296:
	bl Random
	lsls r0, 16
	lsrs r0, 16
	ldr r1, [sp, 0x28]
	bl __modsi3
	lsls r0, 1
	ldr r1, [sp, 0x2C]
	adds r0, r1
	ldrh r4, [r0]
	ldr r2, [sp, 0x20]
	cmp r2, 0x32
	beq _081632B6
	cmp r2, 0x14
	bne _081632BE
_081632B6:
	ldr r0, =0x00000351
	cmp r4, r0
	bls _081632BE
	b _0816341E
_081632BE:
	movs r6, 0
	ldr r5, [sp, 0x18]
	adds r5, r7
	mov r8, r5
	b _081632D2
	.pool
_081632D0:
	adds r6, 0x1
_081632D2:
	cmp r6, r8
	bge _081632F6
	movs r1, 0x64
	adds r0, r6, 0
	muls r0, r1
	ldr r2, =gEnemyParty
	adds r0, r2
	movs r1, 0xB
	movs r2, 0
	bl GetMonData
	ldr r1, =gUnknown_0203BC8C
	ldr r2, [r1]
	lsls r1, r4, 4
	adds r1, r2
	ldrh r1, [r1]
	cmp r0, r1
	bne _081632D0
_081632F6:
	cmp r6, r8
	beq _081632FC
	b _0816341E
_081632FC:
	movs r6, 0
	cmp r6, r8
	bge _08163346
	ldr r5, =gBattleFrontierHeldItems
	mov r9, r5
	movs r3, 0
_08163308:
	ldr r0, =gEnemyParty
	adds r5, r3, r0
	adds r0, r5, 0
	movs r1, 0xC
	movs r2, 0
	str r3, [sp, 0x38]
	bl GetMonData
	ldr r3, [sp, 0x38]
	cmp r0, 0
	beq _0816333E
	adds r0, r5, 0
	movs r1, 0xC
	movs r2, 0
	bl GetMonData
	ldr r1, =gUnknown_0203BC8C
	ldr r2, [r1]
	lsls r1, r4, 4
	adds r1, r2
	ldrb r1, [r1, 0xA]
	lsls r1, 1
	add r1, r9
	ldr r3, [sp, 0x38]
	ldrh r1, [r1]
	cmp r0, r1
	beq _08163346
_0816333E:
	adds r3, 0x64
	adds r6, 0x1
	cmp r6, r8
	blt _08163308
_08163346:
	cmp r6, r8
	bne _0816341E
	movs r6, 0
	cmp r6, r7
	bge _08163368
	add r0, sp, 0xC
	ldrh r0, [r0]
	cmp r0, r4
	beq _08163368
	add r1, sp, 0xC
_0816335A:
	adds r1, 0x2
	adds r6, 0x1
	cmp r6, r7
	bge _08163368
	ldrh r0, [r1]
	cmp r0, r4
	bne _0816335A
_08163368:
	cmp r6, r7
	bne _0816341E
	lsls r0, r7, 1
	add r0, sp
	adds r0, 0xC
	strh r4, [r0]
	movs r1, 0x64
	mov r0, r8
	muls r0, r1
	ldr r2, =gEnemyParty
	adds r0, r2
	ldr r5, =gUnknown_0203BC8C
	ldr r2, [r5]
	lsls r4, 4
	adds r2, r4, r2
	ldrh r1, [r2]
	ldrb r3, [r2, 0xC]
	ldr r6, [sp, 0x24]
	str r6, [sp]
	ldrb r2, [r2, 0xB]
	str r2, [sp, 0x4]
	ldr r2, [sp, 0x30]
	str r2, [sp, 0x8]
	ldr r2, [sp, 0x20]
	bl CreateMonWithEVSpreadPersonalityOTID
	movs r0, 0xFF
	mov r6, sp
	strb r0, [r6, 0x14]
	movs r6, 0
	adds r0, r7, 0x1
	str r0, [sp, 0x34]
	mov r9, r4
	movs r0, 0x64
	mov r3, r8
	muls r3, r0
	mov r1, r9
	str r1, [sp, 0x3C]
	ldr r2, =gEnemyParty
	mov r10, r2
_081633B8:
	ldr r0, [r5]
	ldr r7, [sp, 0x3C]
	adds r0, r7, r0
	lsls r4, r6, 1
	adds r0, 0x2
	adds r0, r4
	ldrh r1, [r0]
	lsls r2, r6, 24
	lsrs r2, 24
	mov r7, r10
	adds r0, r3, r7
	str r3, [sp, 0x38]
	bl SetMonMoveSlot
	ldr r0, [r5]
	ldr r1, [sp, 0x3C]
	adds r0, r1, r0
	adds r0, 0x2
	adds r0, r4
	ldrh r0, [r0]
	ldr r3, [sp, 0x38]
	cmp r0, 0xDA
	bne _081633EC
	movs r0, 0
	mov r2, sp
	strb r0, [r2, 0x14]
_081633EC:
	adds r6, 0x1
	cmp r6, 0x3
	ble _081633B8
	movs r5, 0x64
	mov r4, r8
	muls r4, r5
	ldr r6, =gEnemyParty
	adds r4, r6
	adds r0, r4, 0
	movs r1, 0x20
	add r2, sp, 0x14
	bl SetMonData
	ldr r0, =gUnknown_0203BC8C
	ldr r0, [r0]
	add r0, r9
	ldrb r2, [r0, 0xA]
	lsls r2, 1
	ldr r0, =gBattleFrontierHeldItems
	adds r2, r0
	adds r0, r4, 0
	movs r1, 0xC
	bl SetMonData
	ldr r7, [sp, 0x34]
_0816341E:
	ldr r0, [sp, 0x1C]
	cmp r7, r0
	beq _08163426
	b _08163296
_08163426:
	add sp, 0x40
	pop {r3-r5}
	mov r8, r3
	mov r9, r4
	mov r10, r5
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_81630C4

	thumb_func_start sub_8163444
sub_8163444: @ 8163444
	push {r4-r7,lr}
	mov r7, r10
	mov r6, r9
	mov r5, r8
	push {r5-r7}
	sub sp, 0x18
	lsls r1, 24
	lsrs r1, 24
	str r1, [sp, 0x8]
	movs r1, 0xFF
	add r0, sp, 0x4
	strb r1, [r0]
	ldr r0, =gSaveBlock2Ptr
	ldr r2, [r0]
	movs r0, 0xDC
	adds r0, r2
	mov r10, r0
	ldrb r0, [r0, 0x1]
	movs r1, 0x9
	str r1, [sp, 0x10]
	cmp r0, 0x4
	bhi _08163474
	movs r0, 0x6
	str r0, [sp, 0x10]
_08163474:
	ldr r1, =0x00000ca9
	adds r0, r2, r1
	ldrb r1, [r0]
	movs r0, 0x3
	ands r0, r1
	movs r1, 0x32
	str r1, [sp, 0xC]
	cmp r0, 0
	beq _0816348A
	movs r0, 0x64
	str r0, [sp, 0xC]
_0816348A:
	movs r7, 0
	adds r2, 0xE2
	str r2, [sp, 0x14]
	add r1, sp, 0x4
	mov r9, r1
_08163494:
	ldr r2, [sp, 0x8]
	adds r6, r2, r7
	movs r0, 0x64
	muls r0, r6
	ldr r1, =gEnemyParty
	adds r0, r1
	lsls r5, r7, 1
	adds r4, r5, r7
	lsls r4, 2
	mov r2, r10
	adds r1, r2, r4
	ldrh r1, [r1, 0x4]
	movs r2, 0x8
	str r2, [sp]
	ldr r2, [sp, 0xC]
	ldr r3, [sp, 0x10]
	bl CreateMonWithEVSpread
	movs r0, 0xFF
	mov r1, r9
	strb r0, [r1]
	adds r2, r7, 0x1
	mov r8, r2
	movs r1, 0x3
_081634C4:
	ldr r2, [sp, 0x14]
	adds r0, r2, r4
	ldrh r0, [r0]
	cmp r0, 0xDA
	bne _081634D4
	movs r2, 0
	mov r0, r9
	strb r2, [r0]
_081634D4:
	adds r4, 0x2
	subs r1, 0x1
	cmp r1, 0
	bge _081634C4
	movs r0, 0x64
	adds r4, r6, 0
	muls r4, r0
	ldr r0, =gEnemyParty
	adds r4, r0
	adds r0, r4, 0
	movs r1, 0x20
	add r2, sp, 0x4
	bl SetMonData
	adds r2, r5, r7
	lsls r2, 2
	add r2, r10
	adds r2, 0xE
	adds r0, r4, 0
	movs r1, 0xC
	bl SetMonData
	mov r7, r8
	cmp r7, 0x3
	bne _08163494
	add sp, 0x18
	pop {r3-r5}
	mov r8, r3
	mov r9, r4
	mov r10, r5
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8163444

	thumb_func_start sub_8163524
sub_8163524: @ 8163524
	push {r4-r6,lr}
	adds r4, r0, 0
	lsls r4, 16
	lsrs r4, 16
	bl sub_8165C40
	lsls r0, 24
	lsrs r6, r0, 24
	ldr r0, =gUnknown_0203BC88
	ldr r1, [r0]
	movs r0, 0x34
	muls r0, r4
	adds r0, r1
	ldr r5, [r0, 0x30]
	movs r4, 0
	ldrh r1, [r5]
	b _08163558
	.pool
_0816354C:
	adds r0, r4, 0x1
	lsls r0, 24
	lsrs r4, r0, 24
	lsls r0, r4, 1
	adds r0, r5
	ldrh r1, [r0]
_08163558:
	ldr r0, =0x0000ffff
	cmp r1, r0
	bne _0816354C
_0816355E:
	bl Random
	lsls r0, 16
	lsrs r0, 16
	adds r1, r4, 0
	bl __modsi3
	lsls r0, 1
	adds r0, r5
	ldrh r1, [r0]
	cmp r6, 0x32
	beq _0816357A
	cmp r6, 0x14
	bne _08163580
_0816357A:
	ldr r0, =0x00000351
	cmp r1, r0
	bhi _0816355E
_08163580:
	adds r0, r1, 0
	pop {r4-r6}
	pop {r1}
	bx r1
	.pool
	thumb_func_end sub_8163524

	thumb_func_start sub_8163590
sub_8163590: @ 8163590
	push {lr}
	bl ZeroEnemyPartyMons
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0x00000ca9
	adds r0, r1
	ldrb r1, [r0]
	movs r0, 0x3
	ands r0, r1
	cmp r0, 0x2
	beq _081635C0
	ldr r0, =gTrainerBattleOpponent_A
	ldrh r0, [r0]
	movs r1, 0
	bl sub_81635D4
	b _081635CA
	.pool
_081635C0:
	ldr r0, =gTrainerBattleOpponent_A
	ldrh r0, [r0]
	movs r1, 0
	bl sub_816379C
_081635CA:
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8163590

	thumb_func_start sub_81635D4
sub_81635D4: @ 81635D4
	push {r4-r7,lr}
	mov r7, r10
	mov r6, r9
	mov r5, r8
	push {r5-r7}
	sub sp, 0x20
	lsls r0, 16
	lsrs r2, r0, 16
	adds r3, r2, 0
	lsls r1, 24
	lsrs r1, 24
	str r1, [sp, 0x10]
	ldr r0, =0x0000012b
	cmp r2, r0
	bhi _0816364A
	ldr r4, =gSaveBlock2Ptr
	ldr r0, =0x000040ce
	bl VarGet
	lsls r0, 24
	ldr r4, [r4]
	lsrs r0, 22
	movs r2, 0xCE
	lsls r2, 4
	adds r1, r4, r2
	adds r1, r0
	ldrh r0, [r1]
	movs r1, 0x7
	bl __udivsi3
	lsls r0, 24
	lsrs r1, r0, 24
	ldr r3, =0x00000cb2
	adds r4, r3
	ldrh r0, [r4]
	cmp r0, 0x5
	bhi _0816363C
	adds r0, r1, 0
	movs r1, 0
	bl sub_81A6CA8
	lsls r0, 24
	lsrs r0, 24
	b _081636A6
	.pool
_0816363C:
	adds r0, r1, 0
	movs r1, 0x1
	bl sub_81A6CA8
	lsls r0, 24
	lsrs r0, 24
	b _081636A6
_0816364A:
	movs r0, 0xFA
	lsls r0, 1
	cmp r2, r0
	bne _08163694
	ldr r7, [sp, 0x10]
	adds r0, r7, 0x3
	cmp r7, r0
	blt _0816365C
	b _08163776
_0816365C:
	ldr r4, =gSaveBlock2Ptr
_0816365E:
	movs r0, 0x64
	muls r0, r7
	ldr r1, =gEnemyParty
	adds r0, r1
	ldr r1, [sp, 0x10]
	subs r2, r7, r1
	movs r1, 0x2C
	muls r2, r1
	movs r3, 0xC2
	lsls r3, 4
	adds r2, r3
	ldr r1, [r4]
	adds r1, r2
	bl sub_806819C
	adds r0, r7, 0x1
	lsls r0, 24
	lsrs r7, r0, 24
	ldr r0, [sp, 0x10]
	adds r0, 0x3
	cmp r7, r0
	blt _0816365E
	b _08163776
	.pool
_08163694:
	ldr r0, =0x000003fe
	cmp r3, r0
	bne _081636A4
	bl sub_81A6CD0
	b _08163776
	.pool
_081636A4:
	movs r0, 0x1F
_081636A6:
	str r0, [sp, 0x18]
	bl sub_8165C40
	lsls r0, 24
	lsrs r0, 24
	str r0, [sp, 0x14]
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	ldrb r2, [r1, 0xA]
	ldrb r0, [r1, 0xB]
	lsls r0, 8
	orrs r2, r0
	ldrb r0, [r1, 0xC]
	lsls r0, 16
	orrs r2, r0
	ldrb r0, [r1, 0xD]
	lsls r0, 24
	orrs r2, r0
	mov r8, r2
	movs r7, 0
_081636CE:
	ldr r1, =gUnknown_03006298
	lsls r0, r7, 1
	adds r0, r1
	ldrh r0, [r0]
	mov r9, r0
	ldr r3, [sp, 0x10]
	adds r5, r3, r7
	movs r0, 0x64
	adds r6, r5, 0
	muls r6, r0
	ldr r1, =gEnemyParty
	adds r0, r6, r1
	ldr r3, =gUnknown_0203BC8C
	ldr r2, [r3]
	mov r1, r9
	lsls r4, r1, 4
	adds r2, r4, r2
	ldrh r1, [r2]
	ldrb r3, [r2, 0xC]
	mov r10, r3
	ldr r3, [sp, 0x18]
	str r3, [sp]
	ldrb r2, [r2, 0xB]
	str r2, [sp, 0x4]
	mov r2, r8
	str r2, [sp, 0x8]
	ldr r2, [sp, 0x14]
	mov r3, r10
	bl CreateMonWithEVSpreadPersonalityOTID
	movs r1, 0
	add r0, sp, 0xC
	strb r1, [r0]
	movs r3, 0
	adds r7, 0x1
	mov r10, r7
	adds r7, r4, 0
_08163718:
	ldr r0, =gUnknown_0203BC8C
	ldr r1, [r0]
	mov r2, r9
	lsls r0, r2, 4
	adds r0, r1
	lsls r1, r3, 1
	adds r0, 0x2
	adds r0, r1
	ldrh r1, [r0]
	ldr r2, =gEnemyParty
	adds r0, r6, r2
	adds r2, r3, 0
	str r3, [sp, 0x1C]
	bl sub_81A7024
	ldr r3, [sp, 0x1C]
	adds r0, r3, 0x1
	lsls r0, 24
	lsrs r3, r0, 24
	cmp r3, 0x3
	bls _08163718
	movs r3, 0x64
	adds r4, r5, 0
	muls r4, r3
	ldr r0, =gEnemyParty
	adds r4, r0
	adds r0, r4, 0
	movs r1, 0x20
	add r2, sp, 0xC
	bl SetMonData
	ldr r1, =gUnknown_0203BC8C
	ldr r0, [r1]
	adds r0, r7, r0
	ldrb r2, [r0, 0xA]
	lsls r2, 1
	ldr r0, =gBattleFrontierHeldItems
	adds r2, r0
	adds r0, r4, 0
	movs r1, 0xC
	bl SetMonData
	mov r2, r10
	lsls r0, r2, 24
	lsrs r7, r0, 24
	cmp r7, 0x2
	bls _081636CE
_08163776:
	add sp, 0x20
	pop {r3-r5}
	mov r8, r3
	mov r9, r4
	mov r10, r5
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_81635D4

	thumb_func_start sub_816379C
sub_816379C: @ 816379C
	push {r4-r7,lr}
	mov r7, r10
	mov r6, r9
	mov r5, r8
	push {r5-r7}
	sub sp, 0x18
	lsls r1, 24
	lsrs r1, 24
	str r1, [sp, 0x10]
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	ldrb r0, [r1, 0xA]
	mov r9, r0
	ldrb r0, [r1, 0xB]
	lsls r0, 8
	mov r2, r9
	orrs r2, r0
	ldrb r0, [r1, 0xC]
	lsls r0, 16
	orrs r2, r0
	ldrb r0, [r1, 0xD]
	lsls r0, 24
	orrs r2, r0
	mov r9, r2
	movs r7, 0
	mov r8, r7
_081637D0:
	ldr r1, =gUnknown_03006298
	mov r2, r8
	lsls r0, r2, 1
	adds r0, r1
	ldrh r4, [r0]
	ldr r5, [sp, 0x10]
	add r5, r8
	movs r7, 0x64
	adds r6, r5, 0
	muls r6, r7
	ldr r1, =gEnemyParty
	adds r0, r6, r1
	ldr r7, =gUnknown_0203BC8C
	ldr r2, [r7]
	lsls r4, 4
	adds r2, r4, r2
	ldrh r1, [r2]
	ldrb r3, [r2, 0xC]
	movs r7, 0
	str r7, [sp]
	ldrb r2, [r2, 0xB]
	str r2, [sp, 0x4]
	mov r2, r9
	str r2, [sp, 0x8]
	movs r2, 0x1E
	bl CreateMonWithEVSpreadPersonalityOTID
	movs r1, 0
	add r0, sp, 0xC
	strb r1, [r0]
	mov r10, r5
	mov r0, r8
	adds r0, 0x1
	str r0, [sp, 0x14]
	mov r8, r4
	mov r5, r8
_08163818:
	ldr r1, =gUnknown_0203BC8C
	ldr r0, [r1]
	adds r0, r5, r0
	lsls r4, r7, 1
	adds r0, 0x2
	adds r0, r4
	ldrh r1, [r0]
	ldr r2, =gEnemyParty
	adds r0, r6, r2
	adds r2, r7, 0
	bl sub_81A7024
	ldr r1, =gUnknown_0203BC8C
	ldr r0, [r1]
	adds r0, r5, r0
	adds r0, 0x2
	adds r0, r4
	ldrh r0, [r0]
	cmp r0, 0xDA
	bne _08163846
	movs r1, 0
	add r0, sp, 0xC
	strb r1, [r0]
_08163846:
	adds r0, r7, 0x1
	lsls r0, 24
	lsrs r7, r0, 24
	cmp r7, 0x3
	bls _08163818
	movs r2, 0x64
	mov r4, r10
	muls r4, r2
	ldr r7, =gEnemyParty
	adds r4, r7
	adds r0, r4, 0
	movs r1, 0x20
	add r2, sp, 0xC
	bl SetMonData
	ldr r1, =gUnknown_0203BC8C
	ldr r0, [r1]
	add r0, r8
	ldrb r2, [r0, 0xA]
	lsls r2, 1
	ldr r0, =gBattleFrontierHeldItems
	adds r2, r0
	adds r0, r4, 0
	movs r1, 0xC
	bl SetMonData
	ldr r2, [sp, 0x14]
	lsls r0, r2, 24
	lsrs r0, 24
	mov r8, r0
	cmp r0, 0x2
	bls _081637D0
	add sp, 0x18
	pop {r3-r5}
	mov r8, r3
	mov r9, r4
	mov r10, r5
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_816379C

	thumb_func_start ConvertBattleFrontierTrainerSpeechToString
ConvertBattleFrontierTrainerSpeechToString: @ 81638AC
	push {r4,r5,lr}
	adds r5, r0, 0
	ldr r4, =gStringVar4
	adds r0, r4, 0
	adds r1, r5, 0
	movs r2, 0x3
	movs r3, 0x2
	bl ConvertEasyChatWordsToString
	movs r2, 0x1
	negs r2, r2
	movs r0, 0x1
	adds r1, r4, 0
	bl GetStringWidth
	cmp r0, 0xCC
	bls _0816390A
	adds r0, r4, 0
	adds r1, r5, 0
	movs r2, 0x2
	movs r3, 0x3
	bl ConvertEasyChatWordsToString
	ldrb r0, [r4]
	movs r1, 0x1
	cmp r0, 0xFE
	beq _081638EE
	adds r2, r4, 0
_081638E4:
	adds r0, r1, r2
	ldrb r0, [r0]
	adds r1, 0x1
	cmp r0, 0xFE
	bne _081638E4
_081638EE:
	ldr r2, =gStringVar4
	adds r0, r1, r2
	ldrb r0, [r0]
	adds r3, r2, 0
	cmp r0, 0xFE
	beq _08163904
_081638FA:
	adds r1, 0x1
	adds r0, r1, r2
	ldrb r0, [r0]
	cmp r0, 0xFE
	bne _081638FA
_08163904:
	adds r1, r3
	movs r0, 0xFA
	strb r0, [r1]
_0816390A:
	pop {r4,r5}
	pop {r0}
	bx r0
	.pool
	thumb_func_end ConvertBattleFrontierTrainerSpeechToString

	thumb_func_start sub_8163914
sub_8163914: @ 8163914
	push {lr}
	bl sub_8165C40
	ldr r0, =gSpecialVar_0x8005
	ldrh r0, [r0]
	cmp r0, 0
	beq _08163930
	ldr r0, =gTrainerBattleOpponent_B
	b _08163932
	.pool
_08163930:
	ldr r0, =gTrainerBattleOpponent_A
_08163932:
	ldrh r3, [r0]
	movs r0, 0xFA
	lsls r0, 1
	cmp r3, r0
	bne _08163950
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0x00000bfc
	b _08163986
	.pool
_08163950:
	ldr r0, =0x0000012b
	cmp r3, r0
	bhi _08163974
	ldr r2, =gUnknown_0203BC88
	movs r0, 0x34
	adds r1, r3, 0
	muls r1, r0
	ldr r0, [r2]
	adds r0, r1
	adds r0, 0xC
	bl ConvertBattleFrontierTrainerSpeechToString
	b _081639A8
	.pool
_08163974:
	ldr r0, =0x0000018f
	cmp r3, r0
	bhi _0816399C
	ldr r1, =gSaveBlock2Ptr
	movs r0, 0xEC
	muls r0, r3
	ldr r1, [r1]
	adds r0, r1
	ldr r1, =0xfffef2b8
_08163986:
	adds r0, r1
	bl ConvertBattleFrontierTrainerSpeechToString
	b _081639A8
	.pool
_0816399C:
	adds r0, r3, 0
	adds r0, 0x70
	lsls r0, 24
	lsrs r0, 24
	bl sub_819F99C
_081639A8:
	pop {r0}
	bx r0
	thumb_func_end sub_8163914

	thumb_func_start sub_81639AC
sub_81639AC: @ 81639AC
	push {r4-r6,lr}
	sub sp, 0x4
	bl sub_81864CC
	ldr r0, =gBattleScripting
	adds r0, 0x26
	ldrb r0, [r0]
	cmp r0, 0xA
	bhi _08163A78
	lsls r0, 2
	ldr r1, =_081639D0
	adds r0, r1
	ldr r0, [r0]
	mov pc, r0
	.pool
	.align 2, 0
_081639D0:
	.4byte _081639FC
	.4byte _08163A38
	.4byte _08163A74
	.4byte _081639FC
	.4byte _081639FC
	.4byte _081639FC
	.4byte _081639FC
	.4byte _081639FC
	.4byte _08163A78
	.4byte _081639FC
	.4byte _081639FC
_081639FC:
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r2, =0x00000ebc
	adds r1, r0, r2
	ldr r2, [r1]
	ldr r0, =0x00fffffe
	cmp r2, r0
	bhi _08163A2C
	adds r0, r2, 0x1
	str r0, [r1]
	movs r1, 0x14
	bl __umodsi3
	cmp r0, 0
	bne _08163A78
	bl UpdateGymLeaderRematch
	b _08163A78
	.pool
_08163A2C:
	ldr r0, =0x00ffffff
	str r0, [r1]
	b _08163A78
	.pool
_08163A38:
	movs r5, 0
	ldr r6, =gSaveBlock1Ptr
_08163A3C:
	movs r0, 0x64
	adds r4, r5, 0
	muls r4, r0
	movs r0, 0x8E
	lsls r0, 2
	adds r1, r4, r0
	ldr r0, [r6]
	adds r0, r1
	movs r1, 0xC
	bl GetMonData
	mov r1, sp
	strh r0, [r1]
	ldr r0, =gPlayerParty
	adds r4, r0
	adds r0, r4, 0
	movs r1, 0xC
	mov r2, sp
	bl SetMonData
	adds r5, 0x1
	cmp r5, 0x5
	ble _08163A3C
	b _08163A78
	.pool
_08163A74:
	bl sub_816537C
_08163A78:
	ldr r0, =CB2_ReturnToFieldContinueScriptPlayMapMusic
	bl SetMainCallback2
	add sp, 0x4
	pop {r4-r6}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_81639AC

	thumb_func_start sub_8163A8C
sub_8163A8C: @ 8163A8C
	push {r4,lr}
	lsls r0, 24
	lsrs r4, r0, 24
	bl IsBattleTransitionDone
	lsls r0, 24
	lsrs r0, 24
	cmp r0, 0x1
	bne _08163AB0
	ldr r0, =gMain
	ldr r1, =sub_81639AC
	str r1, [r0, 0x8]
	ldr r0, =CB2_InitBattle
	bl SetMainCallback2
	adds r0, r4, 0
	bl DestroyTask
_08163AB0:
	pop {r4}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8163A8C

	thumb_func_start sub_8163AC4
sub_8163AC4: @ 8163AC4
	push {r4-r6,lr}
	sub sp, 0x4
	ldr r0, =gBattleScripting
	ldr r2, =gSpecialVar_0x8004
	ldrh r1, [r2]
	adds r0, 0x26
	strb r1, [r0]
	ldrh r0, [r2]
	cmp r0, 0xA
	bls _08163ADA
	b _08163E68
_08163ADA:
	lsls r0, 2
	ldr r1, =_08163AF0
	adds r0, r1
	ldr r0, [r0]
	mov pc, r0
	.pool
	.align 2, 0
_08163AF0:
	.4byte _08163B1C
	.4byte _08163BC0
	.4byte _08163C10
	.4byte _08163C70
	.4byte _08163CC4
	.4byte _08163D28
	.4byte _08163D74
	.4byte _08163DB4
	.4byte _08163E2C
	.4byte _08163DF4
	.4byte _08163DC8
_08163B1C:
	ldr r5, =gBattleTypeFlags
	movs r0, 0x84
	lsls r0, 1
	str r0, [r5]
	ldr r0, =0x000040ce
	bl VarGet
	lsls r0, 16
	lsrs r4, r0, 16
	cmp r4, 0x1
	beq _08163B56
	cmp r4, 0x1
	bgt _08163B44
	cmp r4, 0
	beq _08163B4E
	b _08163BA6
	.pool
_08163B44:
	cmp r4, 0x2
	beq _08163B64
	cmp r4, 0x3
	beq _08163B98
	b _08163BA6
_08163B4E:
	movs r0, 0x3
	bl sub_8163048
	b _08163BA6
_08163B56:
	movs r0, 0x4
	bl sub_8163048
	ldr r0, [r5]
	orrs r0, r4
	str r0, [r5]
	b _08163BA6
_08163B64:
	movs r0, 0x2
	bl sub_816306C
	ldr r1, =gPartnerTrainerId
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r2, =0x00000cd6
	adds r0, r2
	ldrh r0, [r0]
	strh r0, [r1]
	ldrh r0, [r1]
	bl sub_8165404
	ldr r0, [r5]
	ldr r1, =0x00408041
	orrs r0, r1
	str r0, [r5]
	b _08163BA6
	.pool
_08163B98:
	ldr r0, [r5]
	ldr r1, =0x00800043
	orrs r0, r1
	str r0, [r5]
	movs r0, 0x2
	bl sub_816306C
_08163BA6:
	ldr r0, =sub_8163A8C
	movs r1, 0x1
	bl CreateTask
	movs r0, 0
	bl PlayMapChosenOrBattleBGM
	movs r0, 0
	b _08163E10
	.pool
_08163BC0:
	movs r5, 0
	ldr r6, =gSaveBlock1Ptr
_08163BC4:
	movs r0, 0x64
	adds r4, r5, 0
	muls r4, r0
	ldr r0, =gPlayerParty
	adds r0, r4, r0
	movs r1, 0xC
	bl GetMonData
	mov r1, sp
	strh r0, [r1]
	movs r0, 0x8E
	lsls r0, 2
	adds r4, r0
	ldr r0, [r6]
	adds r0, r4
	movs r1, 0xC
	mov r2, sp
	bl SetMonData
	adds r5, 0x1
	cmp r5, 0x5
	ble _08163BC4
	ldr r0, =sub_8163A8C
	movs r1, 0x1
	bl CreateTask
	movs r0, 0
	bl PlayMapChosenOrBattleBGM
	movs r0, 0xC
	b _08163E10
	.pool
_08163C10:
	bl ZeroEnemyPartyMons
	movs r5, 0
	ldr r4, =gSaveBlock2Ptr
_08163C18:
	movs r0, 0x64
	muls r0, r5
	ldr r1, =gEnemyParty
	adds r0, r1
	movs r1, 0x2C
	adds r2, r5, 0
	muls r2, r1
	movs r1, 0xC2
	lsls r1, 4
	adds r2, r1
	ldr r1, [r4]
	adds r1, r2
	bl sub_806819C
	adds r5, 0x1
	cmp r5, 0x2
	ble _08163C18
	ldr r1, =gBattleTypeFlags
	ldr r0, =0x00000808
	str r0, [r1]
	ldr r1, =gTrainerBattleOpponent_A
	movs r0, 0
	strh r0, [r1]
	ldr r0, =sub_8163A8C
	movs r1, 0x1
	bl CreateTask
	movs r0, 0
	bl PlayMapChosenOrBattleBGM
	movs r0, 0xD
	b _08163E10
	.pool
_08163C70:
	ldr r4, =gBattleTypeFlags
	ldr r0, =0x00010008
	str r0, [r4]
	ldr r0, =0x000040ce
	bl VarGet
	lsls r0, 16
	lsrs r1, r0, 16
	cmp r1, 0x1
	bne _08163C8A
	ldr r0, [r4]
	orrs r0, r1
	str r0, [r4]
_08163C8A:
	ldr r0, =gTrainerBattleOpponent_A
	ldrh r1, [r0]
	ldr r0, =0x000003fe
	cmp r1, r0
	bne _08163C9A
	movs r0, 0x2
	bl sub_8163048
_08163C9A:
	ldr r0, =sub_8163A8C
	movs r1, 0x1
	bl CreateTask
	movs r0, 0
	bl sub_806E694
	movs r0, 0x3
	b _08163E10
	.pool
_08163CC4:
	ldr r4, =gBattleTypeFlags
	ldr r0, =0x00020008
	str r0, [r4]
	ldr r0, =0x000040ce
	bl VarGet
	lsls r0, 16
	lsrs r1, r0, 16
	cmp r1, 0x1
	bne _08163CDE
	ldr r0, [r4]
	orrs r0, r1
	str r0, [r4]
_08163CDE:
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r2, =0x00000ca9
	adds r0, r2
	ldrb r1, [r0]
	movs r0, 0x3
	ands r0, r1
	cmp r0, 0x2
	beq _08163D0C
	movs r0, 0x3
	bl sub_8163048
	b _08163D12
	.pool
_08163D0C:
	movs r0, 0x3
	bl sub_81630A0
_08163D12:
	ldr r0, =sub_8163A8C
	movs r1, 0x1
	bl CreateTask
	movs r0, 0
	bl PlayMapChosenOrBattleBGM
	movs r0, 0x4
	b _08163E10
	.pool
_08163D28:
	ldr r1, =gBattleTypeFlags
	ldr r0, =0x00040008
	str r0, [r1]
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0x00000ca9
	adds r0, r1
	ldrb r1, [r0]
	movs r0, 0x3
	ands r0, r1
	cmp r0, 0x2
	beq _08163D58
	movs r0, 0x3
	bl sub_8163048
	b _08163D5E
	.pool
_08163D58:
	movs r0, 0x3
	bl sub_81630A0
_08163D5E:
	ldr r0, =sub_8163A8C
	movs r1, 0x1
	bl CreateTask
	movs r0, 0
	bl PlayMapChosenOrBattleBGM
	movs r0, 0x5
	b _08163E10
	.pool
_08163D74:
	ldr r4, =gBattleTypeFlags
	ldr r0, =0x00080008
	str r0, [r4]
	ldr r0, =0x000040ce
	bl VarGet
	lsls r0, 16
	lsrs r1, r0, 16
	cmp r1, 0x1
	bne _08163D8E
	ldr r0, [r4]
	orrs r0, r1
	str r0, [r4]
_08163D8E:
	bl sub_8163590
	ldr r0, =sub_8163A8C
	movs r1, 0x1
	bl CreateTask
	movs r0, 0
	bl PlayMapChosenOrBattleBGM
	movs r0, 0x6
	b _08163E10
	.pool
_08163DB4:
	ldr r1, =gBattleTypeFlags
	movs r0, 0x84
	lsls r0, 1
	str r0, [r1]
	movs r0, 0x3
	bl sub_8163048
	b _08163E00
	.pool
_08163DC8:
	ldr r1, =gBattleTypeFlags
	ldr r0, =0x00200008
	str r0, [r1]
	movs r0, 0x3
	bl sub_8163048
	ldr r0, =sub_8163A8C
	movs r1, 0x1
	bl CreateTask
	movs r0, 0
	bl PlayMapChosenOrBattleBGM
	movs r0, 0xA
	b _08163E10
	.pool
_08163DF4:
	ldr r1, =gBattleTypeFlags
	ldr r0, =0x00008109
	str r0, [r1]
	movs r0, 0x1
	bl sub_816306C
_08163E00:
	ldr r0, =sub_8163A8C
	movs r1, 0x1
	bl CreateTask
	movs r0, 0
	bl PlayMapChosenOrBattleBGM
	movs r0, 0x7
_08163E10:
	bl sub_80B100C
	lsls r0, 24
	lsrs r0, 24
	bl BattleTransition_StartOnField
	b _08163E68
	.pool
_08163E2C:
	ldr r1, =gBattleTypeFlags
	ldr r0, =0x00408049
	str r0, [r1]
	ldr r5, =0x00000c03
	adds r0, r5, 0
	bl sub_8165404
	ldr r4, =gApproachingTrainerId
	movs r0, 0
	strb r0, [r4]
	ldr r0, =MossdeepCity_SpaceCenter_2F_EventScript_224157 + 1
	bl BattleSetup_ConfigureTrainerBattle
	movs r0, 0x1
	strb r0, [r4]
	ldr r0, =MossdeepCity_SpaceCenter_2F_EventScript_224166 + 1
	bl BattleSetup_ConfigureTrainerBattle
	ldr r0, =gPartnerTrainerId
	strh r5, [r0]
	ldr r0, =sub_8163A8C
	movs r1, 0x1
	bl CreateTask
	movs r0, 0
	bl PlayMapChosenOrBattleBGM
	movs r0, 0x12
	bl BattleTransition_StartOnField
_08163E68:
	add sp, 0x4
	pop {r4-r6}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8163AC4

	thumb_func_start sub_8163E90
sub_8163E90: @ 8163E90
	push {r4-r6,lr}
	ldr r6, =gSaveBlock2Ptr
	ldr r0, [r6]
	ldr r1, =0x00000ca9
	adds r0, r1
	ldrb r5, [r0]
	lsls r5, 30
	lsrs r5, 30
	ldr r0, =0x000040ce
	bl VarGet
	adds r4, r0, 0
	lsls r4, 24
	lsrs r4, 24
	adds r0, r5, 0
	adds r1, r4, 0
	bl sub_8164FCC
	lsls r0, 16
	lsrs r2, r0, 16
	ldr r0, [r6]
	lsls r5, 1
	lsls r4, 2
	adds r5, r4
	movs r1, 0xCE
	lsls r1, 4
	adds r0, r1
	adds r1, r0, r5
	ldrh r0, [r1]
	cmp r0, r2
	bcs _08163ED0
	strh r2, [r1]
_08163ED0:
	pop {r4-r6}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8163E90

	thumb_func_start sub_8163EE4
sub_8163EE4: @ 8163EE4
	push {r4-r7,lr}
	mov r7, r9
	mov r6, r8
	push {r6,r7}
	ldr r4, =gSaveBlock2Ptr
	ldr r0, [r4]
	ldr r1, =0x0000064c
	adds r5, r0, r1
	adds r0, r5, 0
	bl sub_8164FB8
	ldr r0, [r4]
	ldr r2, =0x00000ca9
	adds r0, r2
	ldrb r0, [r0]
	lsls r0, 30
	lsrs r6, r0, 30
	ldr r0, =0x000040ce
	bl VarGet
	lsls r0, 24
	lsrs r7, r0, 24
	ldr r2, [r4]
	ldrb r0, [r2, 0x8]
	cmp r0, 0
	beq _08163F40
	ldr r4, =gUnknown_085DCEFA
	ldrb r0, [r2, 0xA]
	ldrb r1, [r2, 0xB]
	adds r0, r1
	ldrb r1, [r2, 0xC]
	adds r0, r1
	ldrb r1, [r2, 0xD]
	adds r0, r1
	movs r1, 0x14
	b _08163F52
	.pool
_08163F40:
	ldr r4, =gUnknown_085DCEDC
	ldrb r0, [r2, 0xA]
	ldrb r1, [r2, 0xB]
	adds r0, r1
	ldrb r1, [r2, 0xC]
	adds r0, r1
	ldrb r1, [r2, 0xD]
	adds r0, r1
	movs r1, 0x1E
_08163F52:
	bl __umodsi3
	adds r0, r4
	ldrb r0, [r0]
	strb r6, [r5]
	strb r0, [r5, 0x1]
	adds r0, r5, 0
	adds r0, 0xC
	ldr r4, =gSaveBlock2Ptr
	ldr r1, [r4]
	adds r1, 0xA
	bl CopyUnalignedWord
	adds r0, r5, 0x4
	ldr r1, [r4]
	bl StringCopy7
	adds r0, r6, 0
	adds r1, r7, 0
	bl sub_8164FCC
	strh r0, [r5, 0x2]
	movs r4, 0
	movs r2, 0x10
	adds r2, r5
	mov r12, r2
	movs r7, 0x1C
	adds r7, r5
	mov r9, r7
	adds r6, r5, 0
	adds r6, 0x28
	movs r0, 0xE4
	adds r0, r5
	mov r8, r0
_08163F96:
	lsls r2, r4, 1
	mov r1, r12
	adds r3, r1, r2
	ldr r0, =gSaveBlock1Ptr
	ldr r1, [r0]
	ldr r7, =0x00002bbc
	adds r0, r1, r7
	adds r0, r2
	ldrh r0, [r0]
	strh r0, [r3]
	mov r0, r9
	adds r3, r0, r2
	adds r7, 0xC
	adds r0, r1, r7
	adds r0, r2
	ldrh r0, [r0]
	strh r0, [r3]
	adds r3, r6, r2
	ldr r0, =0x00002bd4
	adds r1, r0
	adds r1, r2
	ldrh r0, [r1]
	strh r0, [r3]
	adds r4, 0x1
	cmp r4, 0x5
	ble _08163F96
	movs r4, 0
_08163FCC:
	ldr r6, =gSaveBlock2Ptr
	ldr r0, [r6]
	lsls r1, r4, 1
	ldr r2, =0x00000caa
	adds r0, r2
	adds r1, r0, r1
	ldrh r0, [r1]
	cmp r0, 0
	beq _08163FF4
	adds r1, r0, 0
	movs r0, 0x64
	muls r0, r1
	ldr r1, =gBattleScripting + 0x14
	adds r0, r1
	movs r1, 0x2C
	muls r1, r4
	adds r1, 0x34
	adds r1, r5, r1
	bl sub_80686FC
_08163FF4:
	adds r4, 0x1
	cmp r4, 0x3
	ble _08163FCC
	ldr r0, =gGameLanguage
	ldrb r0, [r0]
	mov r7, r8
	strb r0, [r7]
	ldr r0, [r6]
	ldr r1, =0x0000064c
	adds r0, r1
	bl CalcEmeraldBattleTowerChecksum
	bl sub_8163E90
	pop {r3,r4}
	mov r8, r3
	mov r9, r4
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8163EE4

	thumb_func_start sub_8164040
sub_8164040: @ 8164040
	push {r4,r5,lr}
	ldr r5, =gSaveBlock2Ptr
	ldr r0, [r5]
	ldr r1, =0x00000ca9
	adds r0, r1
	ldrb r4, [r0]
	lsls r4, 30
	lsrs r4, 30
	ldr r0, =0x000040ce
	bl VarGet
	lsls r0, 16
	ldr r5, [r5]
	lsls r4, 1
	lsrs r0, 14
	adds r4, r0
	movs r2, 0xCE
	lsls r2, 4
	adds r0, r5, r2
	adds r0, r4
	ldrh r0, [r0]
	movs r1, 0x7
	bl __udivsi3
	lsls r0, 16
	lsrs r1, r0, 16
	ldr r0, =gSpecialVar_0x8005
	ldrh r0, [r0]
	cmp r0, 0
	bne _0816408E
	cmp r1, 0x1
	bgt _0816408A
	ldr r1, =0x00000cb2
	adds r0, r5, r1
	ldrh r0, [r0]
	cmp r0, 0
	beq _0816408E
_0816408A:
	bl sub_8163EE4
_0816408E:
	ldr r4, =gSaveBlock2Ptr
	ldr r0, [r4]
	ldr r1, =gSpecialVar_0x8005
	ldrh r1, [r1]
	ldr r2, =0x00000ca8
	adds r0, r2
	strb r1, [r0]
	movs r0, 0x80
	lsls r0, 7
	movs r1, 0
	bl VarSet
	ldr r1, [r4]
	ldr r0, =0x00000ca9
	adds r1, r0
	ldrb r0, [r1]
	movs r2, 0x4
	orrs r0, r2
	strb r0, [r1]
	bl sub_81A4C30
	pop {r4,r5}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8164040

	thumb_func_start nullsub_61
nullsub_61: @ 81640D8
	bx lr
	thumb_func_end nullsub_61

	thumb_func_start nullsub_116
nullsub_116: @ 81640DC
	bx lr
	thumb_func_end nullsub_116

	thumb_func_start sub_81640E0
sub_81640E0: @ 81640E0
	push {r4-r7,lr}
	sub sp, 0xC
	adds r5, r0, 0
	lsls r5, 16
	lsrs r5, 16
	ldr r4, =gPlayerParty
	adds r0, r4, 0
	movs r1, 0xB
	movs r2, 0
	bl GetMonData
	lsls r0, 16
	lsrs r7, r0, 16
	adds r4, 0x64
	adds r0, r4, 0
	movs r1, 0xB
	movs r2, 0
	bl GetMonData
	lsls r0, 16
	lsrs r4, r0, 16
	movs r6, 0
	movs r2, 0
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	ldr r0, =0xfffffe70
	adds r5, r0
	lsls r0, r5, 4
	adds r0, r5
	lsls r0, 2
	adds r1, 0xE0
	adds r0, r1
	mov r3, sp
_08164122:
	ldrh r1, [r0]
	cmp r1, r7
	beq _08164130
	cmp r1, r4
	beq _08164130
	stm r3!, {r2}
	adds r6, 0x1
_08164130:
	adds r0, 0xC
	adds r2, 0x1
	cmp r2, 0x2
	ble _08164122
	bl Random
	ldr r4, =gUnknown_03006298
	lsls r0, 16
	lsrs r0, 16
	adds r1, r6, 0
	bl __modsi3
	lsls r0, 2
	add r0, sp
	ldr r0, [r0]
	strh r0, [r4]
_08164150:
	bl Random
	lsls r0, 16
	lsrs r0, 16
	adds r1, r6, 0
	bl __modsi3
	lsls r0, 2
	add r0, sp
	ldr r0, [r0]
	strh r0, [r4, 0x2]
	ldrh r1, [r4]
	lsls r0, 16
	lsrs r0, 16
	cmp r1, r0
	beq _08164150
	add sp, 0xC
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_81640E0

	thumb_func_start sub_8164188
sub_8164188: @ 8164188
	push {r4-r7,lr}
	mov r7, r10
	mov r6, r9
	mov r5, r8
	push {r5-r7}
	sub sp, 0x1C
	adds r5, r0, 0
	lsls r5, 16
	lsrs r5, 16
	ldr r6, =gSaveBlock2Ptr
	ldr r0, [r6]
	ldr r1, =0x00000ca9
	adds r0, r1
	ldrb r0, [r0]
	lsls r0, 30
	lsrs r0, 30
	str r0, [sp, 0xC]
	ldr r4, =gPlayerParty
	adds r0, r4, 0
	movs r1, 0xB
	movs r2, 0
	bl GetMonData
	lsls r0, 16
	lsrs r0, 16
	str r0, [sp, 0x10]
	adds r4, 0x64
	adds r0, r4, 0
	movs r1, 0xB
	movs r2, 0
	bl GetMonData
	lsls r0, 16
	lsrs r0, 16
	str r0, [sp, 0x14]
	movs r3, 0
	mov r8, r3
	movs r7, 0
	adds r2, r6, 0
	ldr r0, =0xfffffed4
	adds r5, r0
	ldr r6, =0x0000076c
	mov r10, sp
	movs r0, 0xEC
	adds r1, r5, 0
	muls r1, r0
	mov r9, r1
_081641E6:
	ldr r1, [r2]
	movs r0, 0x2C
	muls r0, r7
	mov r3, r9
	adds r5, r0, r3
	adds r1, r5
	adds r0, r1, r6
	ldrh r0, [r0]
	ldr r3, [sp, 0x10]
	cmp r0, r3
	beq _0816423A
	ldr r3, [sp, 0x14]
	cmp r0, r3
	beq _0816423A
	movs r0, 0xEF
	lsls r0, 3
	adds r4, r1, r0
	ldr r1, [sp, 0xC]
	lsls r0, r1, 24
	lsrs r0, 24
	str r2, [sp, 0x18]
	bl BattleFrontierGetOpponentLvl
	ldrb r1, [r4]
	lsls r0, 24
	lsrs r0, 24
	ldr r2, [sp, 0x18]
	cmp r1, r0
	bhi _0816423A
	ldr r0, [r2]
	adds r0, r5
	adds r0, r6
	ldrh r0, [r0]
	cmp r0, 0
	beq _0816423A
	mov r3, r10
	adds r3, 0x4
	mov r10, r3
	subs r3, 0x4
	stm r3!, {r7}
	movs r0, 0x1
	add r8, r0
_0816423A:
	adds r7, 0x1
	cmp r7, 0x3
	ble _081641E6
	bl Random
	ldr r4, =gUnknown_03006298
	lsls r0, 16
	lsrs r0, 16
	mov r1, r8
	bl __modsi3
	lsls r0, 2
	add r0, sp
	ldr r0, [r0]
	strh r0, [r4, 0x4]
_08164258:
	bl Random
	lsls r0, 16
	lsrs r0, 16
	mov r1, r8
	bl __modsi3
	lsls r0, 2
	add r0, sp
	ldr r0, [r0]
	strh r0, [r4, 0x6]
	ldrh r1, [r4, 0x4]
	lsls r0, 16
	lsrs r0, 16
	cmp r1, r0
	beq _08164258
	add sp, 0x1C
	pop {r3-r5}
	mov r8, r3
	mov r9, r4
	mov r10, r5
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8164188

	thumb_func_start sub_81642A0
sub_81642A0: @ 81642A0
	push {r4-r7,lr}
	mov r7, r10
	mov r6, r9
	mov r5, r8
	push {r5-r7}
	sub sp, 0x4C
	ldr r0, =gSaveBlock1Ptr
	ldr r0, [r0]
	movs r1, 0xC7
	lsls r1, 4
	adds r1, r0, r1
	str r1, [sp, 0x24]
	ldr r5, =gSaveBlock2Ptr
	ldr r0, [r5]
	ldr r2, =0x00000ca9
	adds r0, r2
	ldrb r0, [r0]
	lsls r0, 30
	lsrs r0, 30
	str r0, [sp, 0x14]
	ldr r0, =0x000040ce
	bl VarGet
	lsls r0, 16
	ldr r1, [r5]
	ldr r3, [sp, 0x14]
	lsls r2, r3, 1
	lsrs r0, 14
	adds r2, r0
	movs r4, 0xCE
	lsls r4, 4
	adds r1, r4
	adds r1, r2
	ldrh r0, [r1]
	movs r1, 0x7
	bl __udivsi3
	lsls r0, 16
	lsrs r0, 16
	str r0, [sp, 0x18]
	ldr r4, =gPlayerParty
	adds r0, r4, 0
	movs r1, 0xB
	movs r2, 0
	bl GetMonData
	str r0, [sp, 0x1C]
	adds r4, 0x64
	adds r0, r4, 0
	movs r1, 0xB
	movs r2, 0
	bl GetMonData
	str r0, [sp, 0x20]
	bl sub_8165C40
	movs r7, 0
	ldr r0, [sp, 0x18]
	lsls r0, 24
	mov r10, r0
_08164318:
	lsls r6, r7, 1
_0816431A:
	mov r1, r10
	lsrs r0, r1, 24
	movs r1, 0
	bl sub_8162548
	lsls r0, 16
	lsrs r0, 16
	mov r8, r0
	movs r2, 0
	mov r9, r2
	cmp r9, r7
	bge _08164368
	ldr r0, [r5]
	ldr r3, =0x00000cb4
	adds r1, r0, r3
	ldrh r0, [r1]
	cmp r0, r8
	beq _08164368
	ldr r0, =gUnknown_0203BC88
	ldr r2, [r0]
	movs r4, 0x34
	mov r0, r8
	muls r0, r4
	adds r0, r2
	ldrb r3, [r0]
_0816434C:
	ldrh r0, [r1]
	muls r0, r4
	adds r0, r2
	ldrb r0, [r0]
	cmp r0, r3
	beq _08164368
	adds r1, 0x2
	movs r0, 0x1
	add r9, r0
	cmp r9, r7
	bge _08164368
	ldrh r0, [r1]
	cmp r0, r8
	bne _0816434C
_08164368:
	cmp r9, r7
	bne _0816431A
	ldr r0, [r5]
	ldr r1, =0x00000cb4
	adds r0, r1
	adds r0, r6
	mov r2, r8
	strh r2, [r0]
	mov r7, r9
	adds r7, 0x1
	cmp r7, 0x5
	ble _08164318
	movs r3, 0x8
	mov r10, r3
	movs r4, 0
	mov r9, r4
	ldr r0, [sp, 0x24]
	str r0, [sp, 0x40]
_0816438C:
	ldr r1, =gSaveBlock2Ptr
	ldr r0, [r1]
	mov r2, r9
	lsls r1, r2, 1
	ldr r3, =0x00000cb4
	adds r0, r3
	adds r0, r1
	ldrh r0, [r0]
	mov r8, r0
	bl sub_81627A4
	ldr r4, [sp, 0x40]
	strb r0, [r4, 0x19]
	movs r7, 0
_081643A8:
	adds r0, r7, 0x1
	str r0, [sp, 0x30]
	mov r1, r10
	lsls r1, 1
	str r1, [sp, 0x38]
	mov r2, r10
	adds r2, 0x1
	str r2, [sp, 0x34]
	mov r0, r10
	subs r0, 0x1
	lsls r0, 1
	str r0, [sp, 0x28]
_081643C0:
	mov r0, r8
	bl sub_8163524
	lsls r0, 16
	lsrs r6, r0, 16
	movs r0, 0x1
	ands r0, r7
	cmp r0, 0
	beq _081643F4
	ldr r3, =gSaveBlock2Ptr
	ldr r0, [r3]
	ldr r4, =0x00000cb4
	adds r0, r4
	ldr r1, [sp, 0x28]
	adds r0, r1
	ldrh r2, [r0]
	ldr r0, =gUnknown_0203BC8C
	ldr r0, [r0]
	lsls r2, 4
	adds r2, r0
	lsls r1, r6, 4
	adds r1, r0
	ldrb r0, [r2, 0xA]
	ldrb r1, [r1, 0xA]
	cmp r0, r1
	beq _081643C0
_081643F4:
	movs r5, 0x8
	cmp r5, r10
	bge _08164430
	ldr r2, =gSaveBlock2Ptr
	ldr r0, [r2]
	ldr r1, =gUnknown_0203BC8C
	ldr r3, [r1]
	lsls r1, r6, 4
	adds r1, r3
	ldr r4, =0x00000cc4
	adds r2, r0, r4
	ldrh r0, [r1]
	mov r12, r0
_0816440E:
	ldrh r0, [r2]
	lsls r0, 4
	adds r0, r3
	ldrh r0, [r0]
	cmp r0, r12
	beq _08164430
	ldrh r0, [r1]
	ldr r4, [sp, 0x1C]
	cmp r4, r0
	beq _08164430
	ldr r4, [sp, 0x20]
	cmp r4, r0
	beq _08164430
	adds r2, 0x2
	adds r5, 0x1
	cmp r5, r10
	blt _0816440E
_08164430:
	cmp r5, r10
	bne _081643C0
	ldr r1, =gSaveBlock2Ptr
	ldr r0, [r1]
	ldr r2, =0x00000cb4
	adds r0, r2
	ldr r3, [sp, 0x38]
	adds r0, r3
	strh r6, [r0]
	ldr r4, [sp, 0x34]
	mov r10, r4
	ldr r7, [sp, 0x30]
	cmp r7, 0x1
	ble _081643A8
	ldr r0, [sp, 0x40]
	adds r0, 0x18
	str r0, [sp, 0x40]
	movs r1, 0x1
	add r9, r1
	mov r2, r9
	cmp r2, 0x5
	ble _0816438C
	movs r3, 0
	mov r10, r3
	bl sub_8165B20
	movs r4, 0
	mov r9, r4
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	movs r2, 0
	adds r6, r0, 0
	adds r6, 0xDC
	mov r8, sp
_08164474:
	ldrb r0, [r6]
	lsls r4, r0, 25
	lsrs r0, r4, 30
	cmp r0, 0
	beq _081644E0
	ldr r1, =gUnknown_085DF9EC
	ldrb r0, [r6, 0x1]
	adds r0, r1
	ldrb r0, [r0]
	movs r1, 0x7
	str r2, [sp, 0x44]
	bl __udivsi3
	lsls r0, 24
	lsrs r0, 24
	ldr r2, [sp, 0x44]
	ldr r1, [sp, 0x18]
	cmp r0, r1
	bgt _081644E0
	lsrs r0, r4, 30
	subs r0, 0x1
	ldr r3, [sp, 0x14]
	cmp r0, r3
	bne _081644E0
	movs r5, 0
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	adds r0, 0xE0
	adds r1, r2, r0
	movs r7, 0x2
_081644B0:
	ldrh r0, [r1]
	ldr r4, [sp, 0x1C]
	cmp r4, r0
	beq _081644C0
	ldr r3, [sp, 0x20]
	cmp r3, r0
	beq _081644C0
	adds r5, 0x1
_081644C0:
	adds r1, 0xC
	subs r7, 0x1
	cmp r7, 0
	bge _081644B0
	cmp r5, 0x2
	ble _081644E0
	movs r0, 0xC8
	lsls r0, 1
	add r0, r9
	mov r4, r8
	adds r4, 0x4
	mov r8, r4
	subs r4, 0x4
	stm r4!, {r0}
	movs r0, 0x1
	add r10, r0
_081644E0:
	adds r2, 0x44
	adds r6, 0x44
	movs r1, 0x1
	add r9, r1
	mov r3, r9
	cmp r3, 0x3
	ble _08164474
	mov r4, r10
	cmp r4, 0
	beq _08164532
	bl Random
	ldr r6, =gSaveBlock2Ptr
	ldr r4, [r6]
	lsls r0, 16
	lsrs r0, 16
	mov r1, r10
	bl __modsi3
	lsls r0, 2
	add r0, sp
	ldr r0, [r0]
	movs r5, 0xCC
	lsls r5, 4
	adds r4, r5
	strh r0, [r4]
	ldrh r0, [r4]
	bl sub_81627A4
	ldr r1, [sp, 0x24]
	adds r1, 0xA8
	strb r0, [r1, 0x1]
	movs r0, 0xD8
	lsls r0, 2
	bl FlagClear
	ldr r0, [r6]
	adds r0, r5
	ldrh r0, [r0]
	bl sub_81640E0
_08164532:
	movs r0, 0
	mov r10, r0
	mov r9, r0
	mov r1, sp
	str r1, [sp, 0x3C]
_0816453C:
	ldr r0, =gSaveBlock2Ptr
	movs r2, 0xEC
	mov r1, r9
	muls r1, r2
	movs r3, 0xE7
	lsls r3, 3
	adds r1, r3
	ldr r0, [r0]
	movs r2, 0
	movs r3, 0
	movs r7, 0
	mov r4, r9
	adds r4, 0x1
	str r4, [sp, 0x2C]
	adds r1, r0, r1
_0816455A:
	ldm r1!, {r0}
	orrs r2, r0
	adds r3, r0
	adds r7, 0x1
	cmp r7, 0x39
	bls _0816455A
	ldr r0, =gSaveBlock2Ptr
	ldr r5, [r0]
	movs r1, 0xEC
	mov r6, r9
	muls r6, r1
	adds r4, r5, r6
	ldr r1, =0x0000073a
	adds r0, r4, r1
	ldrh r0, [r0]
	movs r1, 0x7
	str r2, [sp, 0x44]
	str r3, [sp, 0x48]
	bl __udivsi3
	lsls r0, 16
	lsrs r0, 16
	ldr r2, [sp, 0x44]
	ldr r3, [sp, 0x48]
	ldr r1, [sp, 0x18]
	cmp r0, r1
	bgt _08164656
	movs r1, 0xE7
	lsls r1, 3
	adds r0, r4, r1
	ldrb r0, [r0]
	ldr r4, [sp, 0x14]
	cmp r0, r4
	bne _08164656
	cmp r2, 0
	beq _08164656
	adds r1, 0xE8
	adds r0, r5, r1
	adds r0, r6
	ldr r0, [r0]
	cmp r0, r3
	bne _08164656
	movs r5, 0
	movs r7, 0
	ldr r2, =gSaveBlock2Ptr
	mov r8, r2
	ldr r3, =0x0000076c
_081645B8:
	mov r4, r8
	ldr r2, [r4]
	movs r0, 0x2C
	adds r1, r7, 0
	muls r1, r0
	movs r4, 0xEC
	mov r0, r9
	muls r0, r4
	adds r6, r1, r0
	adds r2, r6
	adds r0, r2, r3
	ldrh r0, [r0]
	ldr r1, [sp, 0x1C]
	cmp r1, r0
	beq _0816463C
	ldr r4, [sp, 0x20]
	cmp r4, r0
	beq _0816463C
	movs r0, 0xEF
	lsls r0, 3
	adds r4, r2, r0
	ldr r1, [sp, 0x14]
	lsls r0, r1, 24
	lsrs r0, 24
	str r3, [sp, 0x48]
	bl BattleFrontierGetOpponentLvl
	ldrb r1, [r4]
	lsls r0, 24
	lsrs r0, 24
	ldr r3, [sp, 0x48]
	cmp r1, r0
	bhi _0816463C
	mov r2, r8
	ldr r0, [r2]
	adds r0, r6
	adds r0, r3
	ldrh r0, [r0]
	cmp r0, 0
	b _08164638
	.pool
_08164638:
	beq _0816463C
	adds r5, 0x1
_0816463C:
	adds r7, 0x1
	cmp r7, 0x3
	ble _081645B8
	cmp r5, 0x1
	ble _08164656
	movs r0, 0x96
	lsls r0, 1
	add r0, r9
	ldr r3, [sp, 0x3C]
	stm r3!, {r0}
	str r3, [sp, 0x3C]
	movs r4, 0x1
	add r10, r4
_08164656:
	ldr r0, [sp, 0x2C]
	mov r9, r0
	cmp r0, 0x4
	bgt _08164660
	b _0816453C
_08164660:
	mov r1, r10
	cmp r1, 0
	beq _081646A0
	bl Random
	ldr r6, =gSaveBlock2Ptr
	ldr r4, [r6]
	lsls r0, 16
	lsrs r0, 16
	mov r1, r10
	bl __modsi3
	lsls r0, 2
	add r0, sp
	ldr r0, [r0]
	ldr r5, =0x00000cc2
	adds r4, r5
	strh r0, [r4]
	ldrh r0, [r4]
	bl sub_81627A4
	ldr r1, [sp, 0x24]
	adds r1, 0xC0
	strb r0, [r1, 0x1]
	ldr r0, =0x00000361
	bl FlagClear
	ldr r0, [r6]
	adds r0, r5
	ldrh r0, [r0]
	bl sub_8164188
_081646A0:
	add sp, 0x4C
	pop {r3-r5}
	mov r8, r3
	mov r9, r4
	mov r10, r5
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_81642A0

	thumb_func_start sub_81646BC
sub_81646BC: @ 81646BC
	push {r4-r7,lr}
	mov r7, r10
	mov r6, r9
	mov r5, r8
	push {r5-r7}
	lsls r0, 16
	lsrs r5, r0, 16
	lsls r1, 16
	lsrs r4, r1, 16
	movs r0, 0
	mov r9, r0
	mov r10, r0
	bl sub_8165C40
	movs r0, 0xFA
	lsls r0, 1
	cmp r5, r0
	beq _081647CE
	subs r0, 0xC9
	cmp r5, r0
	bhi _081646FC
	ldr r0, =gUnknown_0203BC8C
	ldr r1, [r0]
	lsls r0, r4, 4
	adds r0, r1
	ldrh r1, [r0, 0x2]
	mov r9, r1
	ldrh r0, [r0]
	mov r10, r0
	b _081647CE
	.pool
_081646FC:
	ldr r0, =0x0000018f
	cmp r5, r0
	bhi _08164750
	ldr r0, =gSaveBlock2Ptr
	ldr r3, [r0]
	ldr r1, =gUnknown_03006298
	ldr r0, =gSpecialVar_0x8005
	ldrh r0, [r0]
	adds r0, 0x1
	lsls r0, 1
	adds r0, r1
	ldrh r1, [r0]
	movs r0, 0x2C
	muls r1, r0
	ldr r0, =0xfffffed4
	adds r2, r5, r0
	movs r0, 0xEC
	muls r0, r2
	adds r1, r0
	adds r3, r1
	movs r1, 0xEE
	lsls r1, 3
	adds r0, r3, r1
	ldrh r0, [r0]
	mov r9, r0
	ldr r2, =0x0000076c
	adds r3, r2
	ldrh r3, [r3]
	mov r10, r3
	b _081647CE
	.pool
_08164750:
	ldr r4, =gSaveBlock2Ptr
	ldr r3, [r4]
	ldr r1, =gUnknown_03006298
	ldr r0, =gSpecialVar_0x8005
	ldrh r0, [r0]
	subs r0, 0x1
	lsls r0, 1
	adds r0, r1
	ldrh r1, [r0]
	lsls r0, r1, 1
	adds r0, r1
	lsls r0, 2
	ldr r2, =0xfffffe70
	adds r1, r5, r2
	lsls r2, r1, 4
	adds r2, r1
	lsls r2, 2
	adds r0, r2
	adds r3, r0
	adds r0, r3, 0
	adds r0, 0xE2
	ldrh r0, [r0]
	mov r9, r0
	adds r3, 0xE0
	ldrh r3, [r3]
	mov r10, r3
	movs r3, 0
	ldr r7, =gStringVar3
	mov r8, r7
	adds r0, r4, 0
	mov r12, r0
	adds r4, r2, 0
	movs r6, 0x8A
	lsls r6, 1
_08164794:
	mov r1, r8
	adds r2, r3, r1
	mov r1, r12
	ldr r0, [r1]
	adds r1, r3, r4
	adds r0, r6
	adds r0, r1
	ldrb r0, [r0]
	strb r0, [r2]
	adds r3, 0x1
	cmp r3, 0x6
	ble _08164794
	adds r1, r3, r7
	movs r0, 0xFF
	strb r0, [r1]
	ldr r0, =gSaveBlock2Ptr
	ldr r2, [r0]
	ldr r0, =0xfffffe70
	adds r1, r5, r0
	lsls r0, r1, 4
	adds r0, r1
	lsls r0, 2
	adds r2, r0
	ldr r1, =0x0000011b
	adds r0, r2, r1
	ldrb r1, [r0]
	adds r0, r7, 0
	bl ConvertInternationalString
_081647CE:
	ldr r0, =gStringVar1
	movs r1, 0xD
	mov r2, r9
	muls r2, r1
	adds r1, r2, 0
	ldr r2, =gMoveNames
	adds r1, r2
	bl StringCopy
	ldr r0, =gStringVar2
	movs r1, 0xB
	mov r2, r10
	muls r2, r1
	adds r1, r2, 0
	ldr r2, =gSpeciesNames
	adds r1, r2
	bl StringCopy
	pop {r3-r5}
	mov r8, r3
	mov r9, r4
	mov r10, r5
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_81646BC

	thumb_func_start sub_8164828
sub_8164828: @ 8164828
	push {r4-r7,lr}
	mov r7, r10
	mov r6, r9
	mov r5, r8
	push {r5-r7}
	sub sp, 0x8
	bl sub_8165C40
	bl sub_81A39C4
	lsls r0, 16
	lsrs r0, 16
	movs r1, 0x7
	bl __udivsi3
	lsls r0, 16
	lsrs r0, 16
	mov r8, r0
	ldr r0, =gSpecialVar_LastTalked
	ldrh r0, [r0]
	subs r5, r0, 0x2
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	lsls r1, r5, 1
	ldr r2, =0x00000cb4
	adds r0, r2
	adds r0, r1
	ldrh r7, [r0]
	movs r3, 0
	str r3, [sp]
	ldr r4, =gUnknown_085DD500
	lsls r6, r7, 16
	b _08164884
	.pool
_0816487C:
	adds r4, 0x8
	ldr r0, [sp]
	adds r0, 0x1
	str r0, [sp]
_08164884:
	ldr r1, [sp]
	cmp r1, 0x31
	bhi _0816489A
	lsrs r0, r6, 16
	bl sub_8162D34
	lsls r0, 24
	lsrs r0, 24
	ldr r1, [r4]
	cmp r1, r0
	bne _0816487C
_0816489A:
	ldr r0, =gSpecialVar_0x8005
	ldrh r0, [r0]
	cmp r0, 0x4
	bls _081648A4
	b _08164AC2
_081648A4:
	lsls r0, 2
	ldr r1, =_081648B8
	adds r0, r1
	ldr r0, [r0]
	mov pc, r0
	.pool
	.align 2, 0
_081648B8:
	.4byte _081648CC
	.4byte _08164984
	.4byte _0816499C
	.4byte _081649BC
	.4byte _08164AC2
_081648CC:
	movs r0, 0xFA
	lsls r0, 1
	cmp r7, r0
	bne _081648D6
	b _08164B54
_081648D6:
	subs r0, 0xC9
	cmp r7, r0
	ble _081648E2
	ldr r0, =0x0000018f
	cmp r7, r0
	bgt _081648F4
_081648E2:
	ldr r0, =gStringVar1
	adds r1, r7, 0
	bl GetFrontierTrainerName
	b _08164AC2
	.pool
_081648F4:
	movs r3, 0
	lsls r2, r7, 16
	mov r10, r2
	ldr r6, =gStringVar1
	mov r9, r6
	ldr r4, =gSaveBlock2Ptr
	mov r8, r4
	ldr r5, =0xfffffe70
	adds r1, r7, r5
	lsls r0, r1, 4
	adds r0, r1
	lsls r4, r0, 2
	movs r5, 0x8A
	lsls r5, 1
_08164910:
	mov r0, r9
	adds r2, r3, r0
	mov r1, r8
	ldr r0, [r1]
	adds r1, r3, r4
	adds r0, r5
	adds r0, r1
	ldrb r0, [r0]
	strb r0, [r2]
	adds r3, 0x1
	cmp r3, 0x6
	ble _08164910
	adds r1, r3, r6
	movs r0, 0xFF
	strb r0, [r1]
	ldr r2, =gSaveBlock2Ptr
	ldr r1, [r2]
	ldr r3, =0xfffffe70
	adds r0, r7, r3
	lsls r4, r0, 4
	adds r4, r0
	lsls r4, 2
	adds r1, r4
	ldr r5, =0x0000011b
	adds r0, r1, r5
	ldrb r1, [r0]
	adds r0, r6, 0
	bl ConvertInternationalString
	ldr r0, =gStringVar2
	ldr r2, =gSaveBlock2Ptr
	ldr r1, [r2]
	adds r1, r4
	adds r1, 0xDE
	ldrb r1, [r1]
	movs r2, 0
	movs r3, 0x3
	bl ConvertIntToDecimalStringN
	ldr r0, =gStringVar3
	mov r3, r10
	lsrs r1, r3, 16
	bl GetFrontierTrainerName
	b _08164AC2
	.pool
_08164984:
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	lsls r0, r5, 2
	adds r1, r0
	ldr r4, =0x00000cc4
	adds r1, r4
	b _081649A8
	.pool
_0816499C:
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	lsls r0, r5, 2
	adds r1, r0
	ldr r5, =0x00000cc6
	adds r1, r5
_081649A8:
	adds r0, r7, 0
	ldrh r1, [r1]
	bl sub_81646BC
	b _08164AC2
	.pool
_081649BC:
	ldr r0, =gPartnerTrainerId
	strh r7, [r0]
	ldr r0, =0x0000012b
	cmp r7, r0
	bgt _08164A08
	ldr r0, =gSaveBlock2Ptr
	ldr r4, [r0]
	lsls r1, r5, 1
	adds r0, r1, 0
	adds r0, 0x8
	lsls r0, 1
	ldr r3, =0x00000cb4
	adds r2, r4, r3
	adds r0, r2, r0
	ldrh r3, [r0]
	ldr r5, =0x00000cd8
	adds r0, r4, r5
	strh r3, [r0]
	adds r1, 0x9
	lsls r1, 1
	adds r2, r1
	ldrh r0, [r2]
	ldr r1, =0x00000cda
	adds r4, r1
	strh r0, [r4]
	b _08164A46
	.pool
_08164A08:
	ldr r0, =0x0000018f
	cmp r7, r0
	bgt _08164A30
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	ldr r3, =gUnknown_03006298
	ldrh r2, [r3, 0x4]
	ldr r4, =0x00000cd8
	adds r0, r1, r4
	strh r2, [r0]
	ldrh r0, [r3, 0x6]
	b _08164A40
	.pool
_08164A30:
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	ldr r3, =gUnknown_03006298
	ldrh r2, [r3]
	ldr r4, =0x00000cd8
	adds r0, r1, r4
	strh r2, [r0]
	ldrh r0, [r3, 0x2]
_08164A40:
	ldr r5, =0x00000cda
	adds r1, r5
	strh r0, [r1]
_08164A46:
	movs r5, 0
	mov r0, r8
	lsls r0, 24
	str r0, [sp, 0x4]
_08164A4E:
	lsls r1, r5, 1
	mov r10, r1
	adds r2, r5, 0x1
	mov r9, r2
	lsrs r0, r5, 31
	adds r0, r5, r0
	asrs r0, 1
	lsls r0, 24
	mov r8, r0
_08164A60:
	ldr r3, [sp, 0x4]
	lsrs r0, r3, 24
	mov r4, r8
	lsrs r1, r4, 24
	bl sub_8162548
	lsls r0, 16
	lsrs r3, r0, 16
	ldr r0, =gPartnerTrainerId
	ldrh r0, [r0]
	cmp r0, r3
	beq _08164A60
	movs r2, 0
	cmp r2, r5
	bge _08164AA2
	ldr r1, =gSaveBlock2Ptr
	ldr r0, [r1]
	ldr r4, =0x00000cb4
	adds r0, r4
	ldrh r0, [r0]
	cmp r0, r3
	beq _08164AA2
	adds r6, r1, 0
_08164A8E:
	adds r2, 0x1
	cmp r2, r5
	bge _08164AA2
	ldr r0, [r6]
	lsls r1, r2, 1
	adds r0, r4
	adds r0, r1
	ldrh r0, [r0]
	cmp r0, r3
	bne _08164A8E
_08164AA2:
	cmp r2, r5
	bne _08164A60
	ldr r5, =gSaveBlock2Ptr
	ldr r0, [r5]
	ldr r1, =0x00000cb4
	adds r0, r1
	add r0, r10
	strh r3, [r0]
	mov r5, r9
	cmp r5, 0xD
	ble _08164A4E
	ldr r2, =gSaveBlock2Ptr
	ldr r0, [r2]
	ldr r3, =0x00000cd6
	adds r0, r3
	strh r7, [r0]
_08164AC2:
	movs r0, 0xFA
	lsls r0, 1
	cmp r7, r0
	beq _08164B54
	subs r0, 0xC9
	cmp r7, r0
	bgt _08164AF8
	ldr r0, =gUnknown_085DD500
	ldr r4, [sp]
	lsls r1, r4, 3
	b _08164B04
	.pool
_08164AF8:
	ldr r0, =0x0000018f
	cmp r7, r0
	bgt _08164B28
	ldr r0, =gUnknown_085DD500
	ldr r5, [sp]
	lsls r1, r5, 3
_08164B04:
	adds r0, 0x4
	adds r1, r0
	ldr r0, =gSpecialVar_0x8005
	ldrh r0, [r0]
	ldr r1, [r1]
	lsls r0, 2
	adds r0, r1
	ldr r0, [r0]
	bl ShowFieldMessage
	b _08164B54
	.pool
_08164B28:
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	ldr r0, =0xfffffe70
	adds r2, r7, r0
	lsls r0, r2, 4
	adds r0, r2
	lsls r0, 2
	adds r1, r0
	adds r1, 0xDC
	ldrb r0, [r1]
	lsls r0, 27
	ldr r1, =gUnknown_085DD690
	lsrs r0, 25
	adds r0, r1
	ldr r1, =gSpecialVar_0x8005
	ldrh r1, [r1]
	ldr r0, [r0]
	lsls r1, 2
	adds r1, r0
	ldr r0, [r1]
	bl ShowFieldMessage
_08164B54:
	add sp, 0x8
	pop {r3-r5}
	mov r8, r3
	mov r9, r4
	mov r10, r5
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8164828

	thumb_func_start sub_8164B74
sub_8164B74: @ 8164B74
	push {r4-r7,lr}
	mov r7, r9
	mov r6, r8
	push {r6,r7}
	sub sp, 0x4
	ldr r4, =gSaveBlock2Ptr
	ldr r0, [r4]
	ldr r1, =0x00000ca9
	adds r0, r1
	ldrb r0, [r0]
	lsls r0, 30
	lsrs r7, r0, 30
	ldr r0, =0x000040ce
	bl VarGet
	lsls r0, 16
	lsrs r5, r0, 16
	ldr r0, [r4]
	ldr r2, =0x00000cb2
	adds r0, r2
	ldrh r6, [r0]
	bl GetMultiplayerId
	ldr r0, =gSpecialVar_Result
	ldrh r0, [r0]
	cmp r0, 0x6
	bls _08164BAC
	b _08164DB6
_08164BAC:
	lsls r0, 2
	ldr r1, =_08164BD0
	adds r0, r1
	ldr r0, [r0]
	mov pc, r0
	.pool
	.align 2, 0
_08164BD0:
	.4byte _08164BEC
	.4byte _08164C3C
	.4byte _08164CE0
	.4byte _08164D14
	.4byte _08164D98
	.4byte _08164DA8
	.4byte _08164DB6
_08164BEC:
	cmp r5, 0x3
	beq _08164BF2
	b _08164DB0
_08164BF2:
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	lsls r1, r7, 1
	adds r0, r1
	ldr r3, =0x00000cec
	adds r0, r3
	ldrh r0, [r0]
	movs r1, 0x7
	bl __udivsi3
	lsls r0, 16
	lsrs r0, 16
	str r0, [sp]
	bl sub_800A520
	lsls r0, 24
	cmp r0, 0
	bne _08164C18
	b _08164DB6
_08164C18:
	bl bitmask_all_link_players_but_self
	lsls r0, 24
	lsrs r0, 24
	mov r1, sp
	movs r2, 0x4
	bl SendBlock
	ldr r1, =gSpecialVar_Result
	movs r0, 0x1
	b _08164DB4
	.pool
_08164C3C:
	bl GetBlockReceivedStatus
	movs r1, 0x3
	ands r1, r0
	cmp r1, 0x3
	beq _08164C4A
	b _08164DB6
_08164C4A:
	bl ResetBlockReceivedFlags
	ldr r1, =gBlockRecvBuffer
	movs r0, 0x80
	lsls r0, 1
	adds r2, r1, r0
	ldrh r0, [r1]
	ldrh r3, [r2]
	cmp r0, r3
	bhi _08164C60
	ldrh r0, [r2]
_08164C60:
	str r0, [sp]
	movs r4, 0
	ldr r0, =gSaveBlock2Ptr
	mov r9, r0
_08164C68:
	adds r1, r4, 0x1
	mov r8, r1
	lsrs r0, r4, 31
	adds r0, r4, r0
	asrs r0, 1
	lsls r7, r0, 24
_08164C74:
	ldr r0, [sp]
	lsls r0, 24
	lsrs r0, 24
	lsrs r1, r7, 24
	bl sub_8162548
	lsls r0, 16
	lsrs r3, r0, 16
	movs r2, 0
	cmp r2, r4
	bge _08164CB0
	mov r1, r9
	ldr r0, [r1]
	ldr r1, =0x00000cb4
	adds r0, r1
	ldrh r0, [r0]
	cmp r0, r3
	beq _08164CB0
	ldr r6, =gSaveBlock2Ptr
	adds r5, r1, 0
_08164C9C:
	adds r2, 0x1
	cmp r2, r4
	bge _08164CB0
	ldr r0, [r6]
	lsls r1, r2, 1
	adds r0, r5
	adds r0, r1
	ldrh r0, [r0]
	cmp r0, r3
	bne _08164C9C
_08164CB0:
	cmp r4, r2
	bne _08164C74
	mov r2, r9
	ldr r0, [r2]
	lsls r1, r4, 1
	ldr r2, =0x00000cb4
	adds r0, r2
	adds r0, r1
	strh r3, [r0]
	mov r4, r8
	cmp r4, 0xD
	ble _08164C68
	ldr r1, =gSpecialVar_Result
	movs r0, 0x2
	b _08164DB4
	.pool
_08164CE0:
	bl sub_800A520
	lsls r0, 24
	cmp r0, 0
	beq _08164DB6
	bl bitmask_all_link_players_but_self
	lsls r0, 24
	lsrs r0, 24
	ldr r1, =gSaveBlock2Ptr
	ldr r1, [r1]
	ldr r3, =0x00000cb4
	adds r1, r3
	movs r2, 0x28
	bl SendBlock
	ldr r1, =gSpecialVar_Result
	movs r0, 0x3
	b _08164DB4
	.pool
_08164D14:
	bl GetBlockReceivedStatus
	movs r1, 0x3
	ands r1, r0
	cmp r1, 0x3
	bne _08164DB6
	bl ResetBlockReceivedFlags
	ldr r4, =gSaveBlock2Ptr
	ldr r0, [r4]
	ldr r5, =0x00000cb4
	adds r0, r5
	ldr r1, =gBlockRecvBuffer
	movs r2, 0x28
	bl memcpy
	ldr r2, =gTrainerBattleOpponent_A
	ldr r1, [r4]
	lsls r0, r6, 2
	adds r1, r5
	adds r0, r1, r0
	ldrh r0, [r0]
	strh r0, [r2]
	ldr r4, =gTrainerBattleOpponent_B
	lsls r0, r6, 1
	adds r0, 0x1
	lsls r0, 1
	adds r1, r0
	ldrh r0, [r1]
	strh r0, [r4]
	ldrh r0, [r2]
	movs r1, 0
	bl sub_8162614
	ldrh r0, [r4]
	movs r1, 0x1
	bl sub_8162614
	ldr r0, =gReceivedRemoteLinkPlayers
	ldrb r0, [r0]
	cmp r0, 0
	beq _08164DB0
	ldr r0, =gWirelessCommType
	ldrb r0, [r0]
	cmp r0, 0
	bne _08164DB0
	ldr r1, =gSpecialVar_Result
	movs r0, 0x4
	b _08164DB4
	.pool
_08164D98:
	bl sub_800AC34
	ldr r1, =gSpecialVar_Result
	movs r0, 0x5
	b _08164DB4
	.pool
_08164DA8:
	ldr r0, =gReceivedRemoteLinkPlayers
	ldrb r0, [r0]
	cmp r0, 0
	bne _08164DB6
_08164DB0:
	ldr r1, =gSpecialVar_Result
	movs r0, 0x6
_08164DB4:
	strh r0, [r1]
_08164DB6:
	add sp, 0x4
	pop {r3,r4}
	mov r8, r3
	mov r9, r4
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8164B74

	thumb_func_start sub_8164DCC
sub_8164DCC: @ 8164DCC
	push {lr}
	ldr r0, =gWirelessCommType
	ldrb r0, [r0]
	cmp r0, 0
	beq _08164DDA
	bl sub_800AC34
_08164DDA:
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8164DCC

	thumb_func_start sub_8164DE4
sub_8164DE4: @ 8164DE4
	push {lr}
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0x00000cd6
	adds r0, r1
	ldrh r0, [r0]
	movs r1, 0xF
	bl sub_8162614
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8164DE4

	thumb_func_start sub_8164E04
sub_8164E04: @ 8164E04
	push {r4-r6,lr}
	sub sp, 0x20
	ldr r0, =0x000040ce
	bl VarGet
	lsls r0, 16
	cmp r0, 0
	bne _08164E9A
	ldr r5, =gTrainerBattleOpponent_A
	ldrh r1, [r5]
	mov r0, sp
	bl GetFrontierTrainerName
	mov r0, sp
	bl StripExtCtrlCodes
	ldr r4, =gSaveBlock2Ptr
	ldr r0, [r4]
	ldr r1, =0x00000bd8
	adds r0, r1
	mov r1, sp
	bl StringCopy
	ldr r0, [r4]
	ldr r2, =0x00000beb
	adds r0, r2
	ldrh r1, [r5]
	bl sub_8165B88
	ldr r6, =gBattlerPartyIndexes
	ldrh r0, [r6, 0x2]
	movs r5, 0x64
	muls r0, r5
	ldr r1, =gEnemyParty
	adds r0, r1
	movs r1, 0xB
	movs r2, 0
	bl GetMonData
	ldr r1, [r4]
	ldr r2, =0x00000bd6
	adds r1, r2
	strh r0, [r1]
	ldrh r0, [r6]
	muls r0, r5
	ldr r1, =gPlayerParty
	adds r0, r1
	movs r1, 0xB
	movs r2, 0
	bl GetMonData
	ldr r1, [r4]
	ldr r2, =0x00000bd4
	adds r1, r2
	strh r0, [r1]
	movs r2, 0
	movs r5, 0xBE
	lsls r5, 4
	ldr r3, =gBattleMons + 0x30
	adds r6, r4, 0
_08164E7C:
	ldr r0, [r4]
	adds r0, r5
	adds r0, r2
	adds r1, r2, r3
	ldrb r1, [r1]
	strb r1, [r0]
	adds r2, 0x1
	cmp r2, 0xA
	ble _08164E7C
	ldr r0, [r6]
	ldr r1, =gBattleOutcome
	ldrb r1, [r1]
	ldr r2, =0x00000d06
	adds r0, r2
	strb r1, [r0]
_08164E9A:
	add sp, 0x20
	pop {r4-r6}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8164E04

	thumb_func_start sub_8164ED8
sub_8164ED8: @ 8164ED8
	push {r4-r7,lr}
	mov r7, r8
	push {r7}
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	movs r3, 0
	movs r2, 0
	ldr r4, =0x0000064c
	adds r1, r0, r4
_08164EEA:
	ldm r1!, {r0}
	adds r3, r0
	adds r2, 0x1
	cmp r2, 0x39
	bls _08164EEA
	ldr r5, =gSaveBlock2Ptr
	ldr r1, [r5]
	ldr r2, =0x00000734
	adds r0, r1, r2
	ldr r0, [r0]
	cmp r0, r3
	beq _08164F0A
	ldr r3, =0x0000064c
	adds r0, r1, r3
	bl sub_8164FB8
_08164F0A:
	movs r4, 0
	adds r7, r5, 0
	movs r6, 0xEC
	mov r8, r7
_08164F12:
	adds r0, r4, 0
	muls r0, r6
	movs r1, 0xE7
	lsls r1, 3
	adds r0, r1
	ldr r1, [r7]
	movs r3, 0
	movs r2, 0
	adds r5, r4, 0x1
	adds r1, r0
_08164F26:
	ldm r1!, {r0}
	adds r3, r0
	adds r2, 0x1
	cmp r2, 0x39
	bls _08164F26
	mov r0, r8
	ldr r2, [r0]
	adds r1, r4, 0
	muls r1, r6
	movs r4, 0x82
	lsls r4, 4
	adds r0, r2, r4
	adds r0, r1
	ldr r0, [r0]
	cmp r0, r3
	beq _08164F52
	movs r3, 0xE7
	lsls r3, 3
	adds r0, r1, r3
	adds r0, r2, r0
	bl sub_8164FB8
_08164F52:
	adds r4, r5, 0
	cmp r4, 0x4
	ble _08164F12
	pop {r3}
	mov r8, r3
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8164ED8

	thumb_func_start CalcEmeraldBattleTowerChecksum
CalcEmeraldBattleTowerChecksum: @ 8164F70
	push {r4,lr}
	adds r2, r0, 0
	adds r2, 0xE8
	movs r1, 0
	str r1, [r2]
	movs r3, 0
	adds r4, r0, 0
_08164F7E:
	ldr r0, [r2]
	ldm r4!, {r1}
	adds r0, r1
	str r0, [r2]
	adds r3, 0x1
	cmp r3, 0x39
	bls _08164F7E
	pop {r4}
	pop {r0}
	bx r0
	thumb_func_end CalcEmeraldBattleTowerChecksum

	thumb_func_start sub_8164F94
sub_8164F94: @ 8164F94
	push {r4,lr}
	adds r2, r0, 0
	adds r2, 0xA0
	movs r1, 0
	str r1, [r2]
	movs r3, 0
	adds r4, r0, 0
_08164FA2:
	ldr r0, [r2]
	ldm r4!, {r1}
	adds r0, r1
	str r0, [r2]
	adds r3, 0x1
	cmp r3, 0x27
	bls _08164FA2
	pop {r4}
	pop {r0}
	bx r0
	thumb_func_end sub_8164F94

	thumb_func_start sub_8164FB8
sub_8164FB8: @ 8164FB8
	push {lr}
	movs r1, 0
	movs r2, 0
_08164FBE:
	stm r0!, {r2}
	adds r1, 0x1
	cmp r1, 0x3A
	bls _08164FBE
	pop {r0}
	bx r0
	thumb_func_end sub_8164FB8

	thumb_func_start sub_8164FCC
sub_8164FCC: @ 8164FCC
	push {lr}
	lsls r0, 24
	lsls r1, 24
	ldr r2, =gSaveBlock2Ptr
	ldr r2, [r2]
	lsrs r0, 23
	lsrs r1, 22
	adds r0, r1
	movs r1, 0xCE
	lsls r1, 4
	adds r2, r1
	adds r2, r0
	ldrh r0, [r2]
	ldr r1, =0x0000270f
	cmp r0, r1
	bls _08164FEE
	adds r0, r1, 0
_08164FEE:
	pop {r1}
	bx r1
	.pool
	thumb_func_end sub_8164FCC

	thumb_func_start sub_8164FFC
sub_8164FFC: @ 8164FFC
	push {r4,lr}
	sub sp, 0x4
	lsls r0, 24
	lsrs r4, r0, 24
	ldr r1, =gUnknown_085DFA42
	mov r0, sp
	movs r2, 0x4
	bl memcpy
	cmp r4, 0x3
	bls _0816501C
	movs r0, 0x3
	b _08165022
	.pool
_0816501C:
	mov r1, sp
	adds r0, r1, r4
	ldrb r0, [r0]
_08165022:
	add sp, 0x4
	pop {r4}
	pop {r1}
	bx r1
	thumb_func_end sub_8164FFC

	thumb_func_start sub_816502C
sub_816502C: @ 816502C
	push {r4-r7,lr}
	mov r7, r10
	mov r6, r9
	mov r5, r8
	push {r5-r7}
	sub sp, 0xC
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0x00000ca9
	adds r0, r1
	ldrb r0, [r0]
	lsls r0, 30
	lsrs r0, 30
	adds r5, r0, 0
	ldr r0, =0x000040ce
	bl VarGet
	lsls r0, 24
	lsrs r0, 24
	adds r4, r0, 0
	bl sub_8164FFC
	lsls r0, 24
	lsrs r0, 24
	mov r8, r0
	movs r2, 0x44
	mov r10, r2
	cmp r5, 0
	beq _0816506A
	movs r0, 0x45
	mov r10, r0
_0816506A:
	ldr r1, =gSpecialVar_Result
	mov r9, r1
	movs r0, 0
	strh r0, [r1]
	adds r0, r5, 0
	adds r1, r4, 0
	bl sub_8164FCC
	lsls r0, 16
	lsrs r0, 16
	cmp r0, 0x37
	bls _081650DC
	movs r6, 0
	cmp r6, r8
	bge _081650DC
	ldr r7, =gSaveBlock1Ptr
	mov r5, sp
_0816508C:
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	lsls r1, r6, 1
	ldr r2, =0x00000caa
	adds r0, r2
	adds r0, r1
	ldrh r1, [r0]
	subs r1, 0x1
	movs r0, 0
	strb r1, [r5]
	strb r0, [r5, 0x1]
	movs r0, 0x64
	muls r0, r1
	movs r1, 0x8E
	lsls r1, 2
	adds r4, r0, r1
	ldr r0, [r7]
	adds r0, r4
	mov r1, r10
	bl GetMonData
	cmp r0, 0
	bne _081650D4
	movs r0, 0x1
	mov r2, r9
	strh r0, [r2]
	ldr r0, [r7]
	adds r0, r4
	mov r1, r10
	bl SetMonData
	ldr r0, [r7]
	adds r0, r4
	bl GetRibbonCount
	strb r0, [r5, 0x1]
_081650D4:
	adds r5, 0x4
	adds r6, 0x1
	cmp r6, r8
	blt _0816508C
_081650DC:
	ldr r0, =gSpecialVar_Result
	ldrh r0, [r0]
	cmp r0, 0
	beq _08165132
	movs r0, 0x2A
	bl IncrementGameStat
	mov r0, r8
	cmp r0, 0x1
	ble _08165110
	mov r3, sp
	add r2, sp, 0x4
	mov r6, r8
	subs r6, 0x1
_081650F8:
	ldrb r1, [r3, 0x1]
	ldrb r0, [r2, 0x1]
	cmp r0, r1
	bls _08165108
	ldr r1, [sp]
	ldr r0, [r2]
	str r0, [sp]
	str r1, [r2]
_08165108:
	adds r2, 0x4
	subs r6, 0x1
	cmp r6, 0
	bne _081650F8
_08165110:
	mov r0, sp
	ldrb r0, [r0, 0x1]
	cmp r0, 0x4
	bls _08165132
	ldr r2, =gSaveBlock1Ptr
	mov r0, sp
	ldrb r1, [r0]
	movs r0, 0x64
	muls r1, r0
	movs r0, 0x8E
	lsls r0, 2
	adds r1, r0
	ldr r0, [r2]
	adds r0, r1
	mov r1, r10
	bl sub_80EE4DC
_08165132:
	add sp, 0xC
	pop {r3-r5}
	mov r8, r3
	mov r9, r4
	mov r10, r5
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_816502C

	thumb_func_start sub_816515C
sub_816515C: @ 816515C
	push {r4-r7,lr}
	mov r7, r9
	mov r6, r8
	push {r6,r7}
	ldr r1, =gSaveBlock2Ptr
	ldr r2, [r1]
	ldr r0, =0x00000bec
	adds r7, r2, r0
	ldrb r0, [r2, 0x8]
	adds r5, r1, 0
	cmp r0, 0
	beq _08165194
	ldr r4, =gUnknown_085DCEFA
	ldrb r0, [r2, 0xA]
	ldrb r1, [r2, 0xB]
	adds r0, r1
	ldrb r1, [r2, 0xC]
	adds r0, r1
	ldrb r1, [r2, 0xD]
	adds r0, r1
	movs r1, 0x14
	b _081651A6
	.pool
_08165194:
	ldr r4, =gUnknown_085DCEDC
	ldrb r0, [r2, 0xA]
	ldrb r1, [r2, 0xB]
	adds r0, r1
	ldrb r1, [r2, 0xC]
	adds r0, r1
	ldrb r1, [r2, 0xD]
	adds r0, r1
	movs r1, 0x1E
_081651A6:
	bl __umodsi3
	adds r0, r4
	ldrb r0, [r0]
	strb r0, [r7, 0x1]
	adds r0, r7, 0
	adds r0, 0xC
	ldr r1, [r5]
	adds r1, 0xA
	bl CopyUnalignedWord
	adds r0, r7, 0x4
	ldr r1, [r5]
	bl StringCopy7
	movs r0, 0x1
	strh r0, [r7, 0x2]
	movs r6, 0x7
	movs r4, 0
	ldr r0, =gSaveBlock1Ptr
	mov r8, r0
	adds r5, r7, 0
	adds r5, 0x10
	ldr r1, =0x00002bbc
	mov r12, r1
	adds r3, r7, 0
	adds r3, 0x28
	adds r2, r7, 0
	adds r2, 0x1C
_081651E0:
	lsls r0, r4, 1
	mov r9, r0
	mov r1, r8
	ldr r0, [r1]
	add r0, r12
	add r0, r9
	ldrh r0, [r0]
	strh r0, [r5]
	strh r6, [r2]
	adds r0, r6, 0x6
	strh r0, [r3]
	adds r6, 0x1
	adds r5, 0x2
	adds r3, 0x2
	adds r2, 0x2
	adds r4, 0x1
	cmp r4, 0x5
	ble _081651E0
	movs r4, 0
_08165206:
	movs r0, 0x64
	muls r0, r4
	ldr r1, =gPlayerParty
	adds r0, r1
	movs r1, 0x2C
	muls r1, r4
	adds r1, 0x34
	adds r1, r7, r1
	bl sub_80686FC
	adds r4, 0x1
	cmp r4, 0x2
	ble _08165206
	adds r0, r7, 0
	bl sub_8165328
	pop {r3,r4}
	mov r8, r3
	mov r9, r4
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_816515C

	thumb_func_start GetEreaderTrainerFrontSpriteId
GetEreaderTrainerFrontSpriteId: @ 8165244
	ldr r1, =gFacilityClassToPicIndex
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r2, =0x00000bed
	adds r0, r2
	ldrb r0, [r0]
	adds r0, r1
	ldrb r0, [r0]
	bx lr
	.pool
	thumb_func_end GetEreaderTrainerFrontSpriteId

	thumb_func_start GetEreaderTrainerClassId
GetEreaderTrainerClassId: @ 8165264
	ldr r1, =gFacilityClassToTrainerClass
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r2, =0x00000bed
	adds r0, r2
	ldrb r0, [r0]
	adds r0, r1
	ldrb r0, [r0]
	bx lr
	.pool
	thumb_func_end GetEreaderTrainerClassId

	thumb_func_start GetEreaderTrainerName
GetEreaderTrainerName: @ 8165284
	push {r4,lr}
	adds r3, r0, 0
	movs r2, 0
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	movs r1, 0xBF
	lsls r1, 4
	adds r4, r0, r1
_08165294:
	adds r0, r3, r2
	adds r1, r4, r2
	ldrb r1, [r1]
	strb r1, [r0]
	adds r2, 0x1
	cmp r2, 0x4
	ble _08165294
	adds r1, r3, r2
	movs r0, 0xFF
	strb r0, [r1]
	pop {r4}
	pop {r0}
	bx r0
	.pool
	thumb_func_end GetEreaderTrainerName

	thumb_func_start ValidateEReaderTrainer
ValidateEReaderTrainer: @ 81652B4
	push {r4-r6,lr}
	ldr r2, =gSpecialVar_Result
	movs r0, 0
	strh r0, [r2]
	ldr r1, =gSaveBlock2Ptr
	ldr r0, [r1]
	ldr r3, =0x00000bec
	adds r5, r0, r3
	movs r4, 0
	movs r3, 0
	adds r6, r1, 0
	adds r1, r5, 0
_081652CC:
	ldm r1!, {r0}
	orrs r4, r0
	adds r3, 0x1
	cmp r3, 0x2D
	bls _081652CC
	cmp r4, 0
	bne _081652EC
	movs r0, 0x1
	strh r0, [r2]
	b _08165316
	.pool
_081652EC:
	movs r4, 0
	movs r3, 0
	adds r2, r5, 0
_081652F2:
	ldm r2!, {r0}
	adds r4, r0
	adds r3, 0x1
	cmp r3, 0x2D
	bls _081652F2
	ldr r1, [r6]
	ldr r2, =0x00000ca4
	adds r0, r1, r2
	ldr r0, [r0]
	cmp r0, r4
	beq _08165316
	ldr r3, =0x00000bec
	adds r0, r1, r3
	bl sub_816534C
	ldr r1, =gSpecialVar_Result
	movs r0, 0x1
	strh r0, [r1]
_08165316:
	pop {r4-r6}
	pop {r0}
	bx r0
	.pool
	thumb_func_end ValidateEReaderTrainer

	thumb_func_start sub_8165328
sub_8165328: @ 8165328
	push {r4,lr}
	adds r2, r0, 0
	adds r2, 0xB8
	movs r1, 0
	str r1, [r2]
	movs r3, 0
	adds r4, r0, 0
_08165336:
	ldr r0, [r2]
	ldm r4!, {r1}
	adds r0, r1
	str r0, [r2]
	adds r3, 0x1
	cmp r3, 0x2D
	bls _08165336
	pop {r4}
	pop {r0}
	bx r0
	thumb_func_end sub_8165328

	thumb_func_start sub_816534C
sub_816534C: @ 816534C
	push {lr}
	movs r1, 0
	movs r2, 0
_08165352:
	stm r0!, {r2}
	adds r1, 0x1
	cmp r1, 0x2E
	bls _08165352
	pop {r0}
	bx r0
	thumb_func_end sub_816534C

	thumb_func_start sub_8165360
sub_8165360: @ 8165360
	push {lr}
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0x00000bfc
	adds r0, r1
	bl ConvertBattleFrontierTrainerSpeechToString
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8165360

	thumb_func_start sub_816537C
sub_816537C: @ 816537C
	push {lr}
	ldr r0, =gBattleOutcome
	ldrb r0, [r0]
	cmp r0, 0x3
	bne _08165398
	ldr r1, =gStringVar4
	movs r0, 0xFF
	strb r0, [r1]
	b _081653C0
	.pool
_08165398:
	cmp r0, 0x1
	bne _081653B4
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0x00000c14
	adds r0, r1
	bl ConvertBattleFrontierTrainerSpeechToString
	b _081653C0
	.pool
_081653B4:
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0x00000c08
	adds r0, r1
	bl ConvertBattleFrontierTrainerSpeechToString
_081653C0:
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_816537C

	thumb_func_start sub_81653CC
sub_81653CC: @ 81653CC
	push {lr}
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0x00000ca8
	adds r0, r1
	ldrb r0, [r0]
	cmp r0, 0x1
	bne _081653E0
	bl sub_80F01B8
_081653E0:
	movs r0, 0x77
	bl FlagGet
	lsls r0, 24
	lsrs r0, 24
	cmp r0, 0x1
	bne _081653F8
	bl sub_80F01B8
	movs r0, 0x77
	bl FlagClear
_081653F8:
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_81653CC

	thumb_func_start sub_8165404
sub_8165404: @ 8165404
	push {r4-r7,lr}
	mov r7, r10
	mov r6, r9
	mov r5, r8
	push {r5-r7}
	sub sp, 0x70
	lsls r0, 16
	lsrs r7, r0, 16
	bl sub_8165C40
	ldr r0, =0x00000c03
	cmp r7, r0
	beq _08165420
	b _0816554C
_08165420:
	movs r0, 0
	mov r10, r0
	mov r1, sp
	adds r1, 0x44
	str r1, [sp, 0x64]
_0816542A:
	mov r2, r10
	lsls r2, 2
	mov r9, r2
	mov r3, r10
	adds r3, 0x1
	str r3, [sp, 0x60]
	mov r0, r9
	add r0, r10
	lsls r0, 2
	ldr r6, =gUnknown_085DD6D0
	adds r5, r0, r6
_08165440:
	bl Random
	adds r4, r0, 0
	bl Random
	lsls r4, 16
	lsrs r4, 16
	lsls r0, 16
	orrs r4, r0
	str r4, [sp, 0x44]
	ldr r0, =0x0000ef2a
	adds r1, r4, 0
	bl IsShinyOtIdPersonality
	lsls r0, 24
	lsrs r7, r0, 24
	cmp r7, 0
	bne _08165440
	ldr r0, [sp, 0x44]
	bl GetNatureFromPersonality
	ldrb r1, [r5, 0x4]
	lsls r0, 24
	lsrs r0, 24
	cmp r1, r0
	bne _08165440
	movs r0, 0x64
	mov r6, r10
	muls r6, r0
	ldr r1, =gPlayerParty + 300
	mov r8, r1
	adds r0, r6, r1
	mov r5, r9
	add r5, r10
	lsls r5, 2
	ldr r2, =gUnknown_085DD6D0
	adds r3, r5, r2
	ldrh r1, [r3]
	ldrb r2, [r3, 0x3]
	ldrb r3, [r3, 0x2]
	mov r12, r3
	movs r4, 0x1
	str r4, [sp]
	mov r3, r10
	str r3, [sp, 0x4]
	str r4, [sp, 0x8]
	ldr r4, =0x0000ef2a
	str r4, [sp, 0xC]
	mov r3, r12
	bl CreateMon
	str r7, [sp, 0x44]
	movs r3, 0
	mov r4, r8
	ldr r0, =gUnknown_085DD6D5
	adds r5, r0
_081654B0:
	adds r1, r3, 0
	adds r1, 0x1A
	adds r2, r5, r3
	adds r0, r6, r4
	bl SetMonData
	ldr r0, [sp, 0x44]
	adds r0, 0x1
	str r0, [sp, 0x44]
	adds r3, r0, 0
	cmp r3, 0x5
	ble _081654B0
	movs r0, 0
	str r0, [sp, 0x44]
	movs r1, 0
	movs r6, 0x64
	mov r4, r10
	muls r4, r6
	ldr r7, =gUnknown_085DD6DC
	ldr r6, =gPlayerParty + 300
	mov r0, r9
	add r0, r10
	lsls r5, r0, 2
_081654DE:
	lsls r0, r1, 1
	adds r0, r5
	adds r0, r7
	ldrh r1, [r0]
	ldr r0, [sp, 0x64]
	ldrb r2, [r0]
	adds r0, r4, r6
	bl SetMonMoveSlot
	ldr r0, [sp, 0x44]
	adds r0, 0x1
	str r0, [sp, 0x44]
	adds r1, r0, 0
	cmp r1, 0x3
	ble _081654DE
	movs r1, 0x64
	mov r4, r10
	muls r4, r1
	ldr r0, =gPlayerParty + 300
	adds r4, r0
	adds r0, r4, 0
	movs r1, 0x7
	ldr r2, =gTrainers + 804 * 0x28 + 0x4 @ TRAINER_STEVEN name
	bl SetMonData
	movs r0, 0
	str r0, [sp, 0x44]
	adds r0, r4, 0
	movs r1, 0x31
	ldr r2, [sp, 0x64]
	bl SetMonData
	adds r0, r4, 0
	bl CalculateMonStats
	ldr r2, [sp, 0x60]
	mov r10, r2
	cmp r2, 0x2
	bgt _0816552E
	b _0816542A
_0816552E:
	b _0816585A
	.pool
_0816554C:
	movs r0, 0xFA
	lsls r0, 1
	cmp r7, r0
	bne _08165564
	add r0, sp, 0x10
	ldr r1, =gGameLanguage
	ldrb r1, [r1]
	strb r1, [r0]
	b _0816585A
	.pool
_08165564:
	ldr r0, =0x0000012b
	cmp r7, r0
	bls _0816556C
	b _081656E8
_0816556C:
	bl sub_8165C40
	lsls r0, 24
	lsrs r0, 24
	str r0, [sp, 0x50]
	adds r0, r7, 0
	bl sub_8165D08
	lsls r0, 24
	lsrs r0, 24
	str r0, [sp, 0x4C]
	bl Random
	adds r4, r0, 0
	bl Random
	lsls r4, 16
	lsrs r4, 16
	lsls r0, 16
	orrs r4, r0
	str r4, [sp, 0x58]
	movs r3, 0
	mov r10, r3
	mov r6, sp
	adds r6, 0x44
	str r6, [sp, 0x64]
	mov r0, sp
	adds r0, 0x48
	str r0, [sp, 0x5C]
_081655A6:
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	mov r0, r10
	adds r0, 0x12
	lsls r0, 1
	ldr r2, =0x00000cb4
	adds r1, r2
	adds r1, r0
	ldrh r1, [r1]
	str r1, [sp, 0x54]
	movs r6, 0x64
	mov r3, r10
	muls r3, r6
	mov r8, r3
	ldr r0, =gPlayerParty + 300
	mov r9, r0
	mov r0, r8
	add r0, r9
	ldr r6, =gUnknown_0203BC8C
	ldr r4, [r6]
	lsls r5, r1, 4
	adds r4, r5, r4
	ldrh r1, [r4]
	ldr r3, [sp, 0x50]
	lsls r2, r3, 24
	ldrb r3, [r4, 0xC]
	mov r12, r3
	ldr r3, [sp, 0x4C]
	str r3, [sp]
	ldrb r4, [r4, 0xB]
	str r4, [sp, 0x4]
	ldr r3, [sp, 0x58]
	str r3, [sp, 0x8]
	lsrs r2, 24
	mov r3, r12
	bl CreateMonWithEVSpreadPersonalityOTID
	movs r0, 0xFF
	str r0, [sp, 0x48]
	movs r0, 0
	str r0, [sp, 0x44]
	movs r2, 0
	mov r0, r10
	adds r0, 0x1
	str r0, [sp, 0x60]
	mov r4, r8
	mov r3, r9
_08165604:
	ldr r0, [r6]
	adds r0, r5, r0
	lsls r1, r2, 1
	adds r0, 0x2
	adds r0, r1
	ldrh r1, [r0]
	lsls r2, 24
	lsrs r2, 24
	adds r0, r4, r3
	str r3, [sp, 0x68]
	bl SetMonMoveSlot
	ldr r0, [r6]
	adds r0, r5, r0
	ldr r2, [sp, 0x44]
	lsls r1, r2, 1
	adds r0, 0x2
	adds r0, r1
	ldrh r0, [r0]
	ldr r3, [sp, 0x68]
	cmp r0, 0xDA
	bne _08165634
	movs r0, 0
	str r0, [sp, 0x48]
_08165634:
	adds r0, r2, 0x1
	str r0, [sp, 0x44]
	adds r2, r0, 0
	cmp r2, 0x3
	ble _08165604
	movs r1, 0x64
	mov r4, r10
	muls r4, r1
	ldr r0, =gPlayerParty + 300
	adds r4, r0
	adds r0, r4, 0
	movs r1, 0x20
	ldr r2, [sp, 0x5C]
	bl SetMonData
	ldr r0, =gUnknown_0203BC8C
	ldr r1, [r0]
	ldr r2, [sp, 0x54]
	lsls r0, r2, 4
	adds r0, r1
	ldrb r2, [r0, 0xA]
	lsls r2, 1
	ldr r0, =gBattleFrontierHeldItems
	adds r2, r0
	adds r0, r4, 0
	movs r1, 0xC
	bl SetMonData
	movs r0, 0
	str r0, [sp, 0x44]
	movs r2, 0
	ldr r0, =gUnknown_0203BC88
	ldr r1, [r0]
	movs r0, 0x34
	muls r0, r7
	adds r0, r1
	adds r3, r0, 0x4
_0816567E:
	mov r1, sp
	adds r1, r2
	adds r1, 0x10
	adds r0, r3, r2
	ldrb r0, [r0]
	strb r0, [r1]
	ldr r0, [sp, 0x44]
	adds r0, 0x1
	str r0, [sp, 0x44]
	adds r2, r0, 0
	cmp r2, 0x7
	ble _0816567E
	movs r3, 0x64
	mov r4, r10
	muls r4, r3
	ldr r0, =gPlayerParty + 300
	adds r4, r0
	adds r0, r4, 0
	movs r1, 0x7
	add r2, sp, 0x10
	bl SetMonData
	adds r0, r7, 0
	bl sub_8162F68
	lsls r0, 24
	lsrs r0, 24
	str r0, [sp, 0x44]
	adds r0, r4, 0
	movs r1, 0x31
	ldr r2, [sp, 0x64]
	bl SetMonData
	ldr r6, [sp, 0x60]
	mov r10, r6
	cmp r6, 0x1
	bgt _081656CA
	b _081655A6
_081656CA:
	b _0816585A
	.pool
_081656E8:
	ldr r0, =0x0000018f
	cmp r7, r0
	bls _081656F0
	b _081657F0
_081656F0:
	ldr r1, =0xfffffed4
	adds r0, r7, r1
	lsls r0, 16
	lsrs r7, r0, 16
	movs r2, 0
	mov r10, r2
	mov r3, sp
	adds r3, 0x44
	str r3, [sp, 0x64]
	add r5, sp, 0x18
	ldr r6, =0x000015fc
	mov r9, r6
	ldr r0, =0x0000ffff
	mov r8, r0
	movs r1, 0x24
	str r1, [sp, 0x6C]
_08165710:
	ldr r1, =gSaveBlock2Ptr
	movs r0, 0xEC
	adds r4, r7, 0
	muls r4, r0
	movs r2, 0xE7
	lsls r2, 3
	adds r4, r2
	ldr r0, [r1]
	adds r4, r0, r4
	ldr r3, =0x00000cb4
	adds r0, r3
	ldr r6, [sp, 0x6C]
	adds r0, r6
	ldrh r1, [r0]
	movs r0, 0x2C
	muls r1, r0
	adds r1, r4, r1
	adds r0, r5, 0
	adds r1, 0x34
	ldm r1!, {r2,r3,r6}
	stm r0!, {r2,r3,r6}
	ldm r1!, {r2,r3,r6}
	stm r0!, {r2,r3,r6}
	ldm r1!, {r2,r3,r6}
	stm r0!, {r2,r3,r6}
	ldm r1!, {r2,r3}
	stm r0!, {r2,r3}
	adds r1, r4, 0x4
	add r0, sp, 0x10
	bl StringCopy
	adds r4, 0xE4
	ldrb r0, [r4]
	cmp r0, 0x1
	bne _0816578C
	ldrh r0, [r5, 0x20]
	mov r6, r8
	ands r0, r6
	cmp r0, r9
	beq _0816579C
	mov r1, sp
	adds r1, 0x3D
	movs r0, 0xFF
	strb r0, [r1]
	add r0, sp, 0x38
	movs r1, 0x1
	bl ConvertInternationalString
	b _0816579C
	.pool
_0816578C:
	ldrh r0, [r5, 0x20]
	mov r1, r8
	ands r0, r1
	cmp r0, r9
	bne _0816579C
	add r1, sp, 0x10
	movs r0, 0xFF
	strb r0, [r1, 0x5]
_0816579C:
	movs r0, 0x64
	mov r4, r10
	muls r4, r0
	ldr r0, =gPlayerParty + 300
	adds r4, r0
	adds r0, r4, 0
	adds r1, r5, 0
	movs r2, 0x1
	bl sub_8068338
	adds r0, r4, 0
	movs r1, 0x7
	add r2, sp, 0x10
	bl SetMonData
	movs r2, 0x96
	lsls r2, 1
	adds r0, r7, r2
	lsls r0, 16
	lsrs r0, 16
	bl sub_8162F68
	lsls r0, 24
	lsrs r0, 24
	str r0, [sp, 0x44]
	adds r0, r4, 0
	movs r1, 0x31
	ldr r2, [sp, 0x64]
	bl SetMonData
	ldr r3, [sp, 0x6C]
	adds r3, 0x2
	str r3, [sp, 0x6C]
	movs r6, 0x1
	add r10, r6
	mov r0, r10
	cmp r0, 0x1
	ble _08165710
	b _0816585A
	.pool
_081657F0:
	ldr r1, =0xfffffe70
	adds r0, r7, r1
	lsls r0, 16
	lsrs r7, r0, 16
	movs r2, 0
	mov r10, r2
	mov r3, sp
	adds r3, 0x44
	str r3, [sp, 0x64]
	ldr r6, =gSaveBlock2Ptr
	mov r8, r6
	movs r5, 0x24
	lsls r0, r7, 4
	adds r0, r7
	lsls r0, 2
	adds r6, r0, 0
	adds r6, 0xDC
_08165812:
	movs r0, 0x64
	mov r4, r10
	muls r4, r0
	ldr r0, =gPlayerParty + 300
	adds r4, r0
	mov r1, r8
	ldr r0, [r1]
	adds r1, r0, r6
	ldr r2, =0x00000cb4
	adds r0, r2
	adds r0, r5
	ldrb r2, [r0]
	adds r0, r4, 0
	bl sub_8068528
	movs r3, 0xC8
	lsls r3, 1
	adds r0, r7, r3
	lsls r0, 16
	lsrs r0, 16
	bl sub_8162F68
	lsls r0, 24
	lsrs r0, 24
	str r0, [sp, 0x44]
	adds r0, r4, 0
	movs r1, 0x31
	ldr r2, [sp, 0x64]
	bl SetMonData
	adds r5, 0x2
	movs r0, 0x1
	add r10, r0
	mov r1, r10
	cmp r1, 0x1
	ble _08165812
_0816585A:
	add sp, 0x70
	pop {r3-r5}
	mov r8, r3
	mov r9, r4
	mov r10, r5
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8165404

	thumb_func_start sub_816587C
sub_816587C: @ 816587C
	push {r4-r7,lr}
	mov r7, r10
	mov r6, r9
	mov r5, r8
	push {r5-r7}
	sub sp, 0x14
	adds r6, r0, 0
	adds r5, r1, 0
	movs r2, 0
	adds r1, r6, 0
	adds r3, r6, 0
	adds r3, 0x58
_08165894:
	ldrh r0, [r1, 0x1C]
	cmp r0, 0
	beq _0816589C
	adds r2, 0x1
_0816589C:
	adds r1, 0x2C
	cmp r1, r3
	ble _08165894
	cmp r2, 0x3
	beq _081658B4
	adds r0, r5, 0
	movs r1, 0
	movs r2, 0xEC
	bl memset
	movs r0, 0
	b _081659BE
_081658B4:
	ldrb r0, [r6]
	strb r0, [r5]
	ldrh r0, [r6, 0x2]
	strh r0, [r5, 0x2]
	movs r2, 0
	ldr r0, =gUnknown_085DCF40
	ldrb r1, [r0]
	ldrb r3, [r6, 0x1]
	mov r12, r0
	adds r4, r5, 0x4
	adds r7, r6, 0x4
	movs r0, 0xC
	adds r0, r5
	mov r9, r0
	movs r0, 0xC
	adds r0, r6
	mov r8, r0
	adds r0, r5, 0
	adds r0, 0x10
	str r0, [sp, 0x4]
	movs r0, 0x10
	adds r0, r6
	mov r10, r0
	adds r0, r5, 0
	adds r0, 0x1C
	str r0, [sp, 0x8]
	adds r0, 0xC
	str r0, [sp, 0xC]
	adds r0, 0x90
	str r0, [sp, 0x10]
	cmp r1, r3
	beq _08165904
	mov r1, r12
_081658F6:
	adds r1, 0x2
	adds r2, 0x1
	cmp r2, 0x51
	bgt _08165904
	ldrb r0, [r1]
	cmp r0, r3
	bne _081658F6
_08165904:
	cmp r2, 0x52
	beq _08165918
	lsls r0, r2, 1
	mov r1, r12
	adds r1, 0x1
	adds r0, r1
	ldrb r0, [r0]
	b _0816591A
	.pool
_08165918:
	movs r0, 0x2B
_0816591A:
	strb r0, [r5, 0x1]
	movs r2, 0
	adds r3, r7, 0
_08165920:
	adds r0, r4, r2
	adds r1, r3, r2
	ldrb r1, [r1]
	strb r1, [r0]
	adds r2, 0x1
	cmp r2, 0x7
	ble _08165920
	movs r2, 0
	mov r4, r9
	mov r3, r8
_08165934:
	adds r0, r4, r2
	adds r1, r3, r2
	ldrb r1, [r1]
	strb r1, [r0]
	adds r2, 0x1
	cmp r2, 0x3
	ble _08165934
	mov r3, r10
	ldr r1, [sp, 0x4]
	movs r2, 0x5
_08165948:
	ldrh r0, [r3]
	strh r0, [r1]
	adds r3, 0x2
	adds r1, 0x2
	subs r2, 0x1
	cmp r2, 0
	bge _08165948
	ldr r3, =gUnknown_085DFA46
	ldr r1, [sp, 0x8]
	movs r2, 0x5
_0816595C:
	ldrh r0, [r3]
	strh r0, [r1]
	adds r3, 0x2
	adds r1, 0x2
	subs r2, 0x1
	cmp r2, 0
	bge _0816595C
	ldr r3, =gUnknown_085DFA52
	ldr r1, [sp, 0xC]
	movs r2, 0x5
_08165970:
	ldrh r0, [r3]
	strh r0, [r1]
	adds r3, 0x2
	adds r1, 0x2
	subs r2, 0x1
	cmp r2, 0
	bge _08165970
	adds r2, r6, 0
	adds r3, r5, 0
	movs r4, 0x58
	adds r4, r2
	mov r8, r4
_08165988:
	adds r1, r3, 0
	adds r1, 0x34
	adds r0, r2, 0
	adds r0, 0x1C
	ldm r0!, {r4,r6,r7}
	stm r1!, {r4,r6,r7}
	ldm r0!, {r4,r6,r7}
	stm r1!, {r4,r6,r7}
	ldm r0!, {r4,r6,r7}
	stm r1!, {r4,r6,r7}
	ldm r0!, {r6,r7}
	stm r1!, {r6,r7}
	adds r2, 0x2C
	adds r3, 0x2C
	cmp r2, r8
	ble _08165988
	movs r0, 0
	str r0, [sp]
	ldr r2, =0x0500000b
	mov r0, sp
	ldr r1, [sp, 0x10]
	bl CpuSet
	adds r0, r5, 0
	bl CalcEmeraldBattleTowerChecksum
	movs r0, 0x1
_081659BE:
	add sp, 0x14
	pop {r3-r5}
	mov r8, r3
	mov r9, r4
	mov r10, r5
	pop {r4-r7}
	pop {r1}
	bx r1
	.pool
	thumb_func_end sub_816587C

	thumb_func_start sub_81659DC
sub_81659DC: @ 81659DC
	push {r4-r7,lr}
	mov r7, r10
	mov r6, r9
	mov r5, r8
	push {r5-r7}
	sub sp, 0x4
	adds r4, r0, 0
	adds r6, r1, 0
	movs r2, 0
	adds r1, r4, 0
	adds r3, r4, 0
	adds r3, 0x58
_081659F4:
	ldrh r0, [r1, 0x34]
	cmp r0, 0
	beq _081659FC
	adds r2, 0x1
_081659FC:
	adds r1, 0x2C
	cmp r1, r3
	ble _081659F4
	cmp r2, 0x3
	beq _08165A14
	adds r0, r6, 0
	movs r1, 0
	movs r2, 0xA4
	bl memset
	movs r0, 0
	b _08165AD8
_08165A14:
	ldrb r0, [r4]
	strb r0, [r6]
	ldrh r0, [r4, 0x2]
	strh r0, [r6, 0x2]
	movs r2, 0
	ldr r0, =gUnknown_085DCF40
	ldrb r1, [r0, 0x1]
	ldrb r3, [r4, 0x1]
	mov r12, r0
	adds r5, r6, 0x4
	adds r7, r4, 0x4
	movs r0, 0xC
	adds r0, r6
	mov r9, r0
	movs r0, 0xC
	adds r0, r4
	mov r8, r0
	adds r0, r6, 0
	adds r0, 0x10
	str r0, [sp]
	movs r0, 0x10
	adds r0, r4
	mov r10, r0
	cmp r1, r3
	beq _08165A58
	mov r1, r12
	adds r1, 0x1
_08165A4A:
	adds r1, 0x2
	adds r2, 0x1
	cmp r2, 0x51
	bgt _08165A58
	ldrb r0, [r1]
	cmp r0, r3
	bne _08165A4A
_08165A58:
	cmp r2, 0x52
	beq _08165A68
	lsls r0, r2, 1
	add r0, r12
	ldrb r0, [r0]
	b _08165A6A
	.pool
_08165A68:
	movs r0, 0x24
_08165A6A:
	strb r0, [r6, 0x1]
	movs r2, 0
	adds r3, r7, 0
_08165A70:
	adds r0, r5, r2
	adds r1, r3, r2
	ldrb r1, [r1]
	strb r1, [r0]
	adds r2, 0x1
	cmp r2, 0x7
	ble _08165A70
	movs r2, 0
	mov r5, r9
	mov r3, r8
_08165A84:
	adds r0, r5, r2
	adds r1, r3, r2
	ldrb r1, [r1]
	strb r1, [r0]
	adds r2, 0x1
	cmp r2, 0x3
	ble _08165A84
	mov r3, r10
	ldr r1, [sp]
	movs r2, 0x5
_08165A98:
	ldrh r0, [r3]
	strh r0, [r1]
	adds r3, 0x2
	adds r1, 0x2
	subs r2, 0x1
	cmp r2, 0
	bge _08165A98
	adds r2, r4, 0
	adds r3, r6, 0
	movs r4, 0x58
	adds r4, r2
	mov r8, r4
_08165AB0:
	adds r1, r3, 0
	adds r1, 0x1C
	adds r0, r2, 0
	adds r0, 0x34
	ldm r0!, {r4,r5,r7}
	stm r1!, {r4,r5,r7}
	ldm r0!, {r4,r5,r7}
	stm r1!, {r4,r5,r7}
	ldm r0!, {r4,r5,r7}
	stm r1!, {r4,r5,r7}
	ldm r0!, {r5,r7}
	stm r1!, {r5,r7}
	adds r2, 0x2C
	adds r3, 0x2C
	cmp r2, r8
	ble _08165AB0
	adds r0, r6, 0
	bl sub_8164F94
	movs r0, 0x1
_08165AD8:
	add sp, 0x4
	pop {r3-r5}
	mov r8, r3
	mov r9, r4
	mov r10, r5
	pop {r4-r7}
	pop {r1}
	bx r1
	thumb_func_end sub_81659DC

	thumb_func_start sub_8165AE8
sub_8165AE8: @ 8165AE8
	push {r4,lr}
	adds r2, r0, 0
	movs r0, 0
	str r0, [r2, 0x40]
	movs r3, 0
	adds r4, r2, 0
_08165AF4:
	ldr r0, [r2, 0x40]
	ldm r4!, {r1}
	adds r0, r1
	str r0, [r2, 0x40]
	adds r3, 0x1
	cmp r3, 0xF
	bls _08165AF4
	pop {r4}
	pop {r0}
	bx r0
	thumb_func_end sub_8165AE8

	thumb_func_start sub_8165B08
sub_8165B08: @ 8165B08
	push {lr}
	movs r1, 0
	movs r3, 0
	adds r2, r0, 0
_08165B10:
	stm r2!, {r3}
	adds r1, 0x1
	cmp r1, 0x10
	bls _08165B10
	bl sub_819FA5C
	pop {r0}
	bx r0
	thumb_func_end sub_8165B08

	thumb_func_start sub_8165B20
sub_8165B20: @ 8165B20
	push {r4-r7,lr}
	mov r7, r9
	mov r6, r8
	push {r6,r7}
	movs r5, 0
	ldr r0, =gSaveBlock2Ptr
	mov r8, r0
	mov r9, r8
_08165B30:
	lsls r0, r5, 4
	adds r1, r0, r5
	lsls r1, 2
	adds r1, 0xDC
	mov r3, r9
	ldr r2, [r3]
	movs r4, 0
	movs r3, 0
	adds r6, r0, 0
	adds r7, r5, 0x1
	adds r2, r1
_08165B46:
	ldm r2!, {r0}
	adds r4, r0
	adds r3, 0x1
	cmp r3, 0xF
	bls _08165B46
	mov r0, r8
	ldr r2, [r0]
	adds r0, r6, r5
	lsls r1, r0, 2
	movs r3, 0x8E
	lsls r3, 1
	adds r0, r2, r3
	adds r0, r1
	ldr r0, [r0]
	cmp r0, r4
	beq _08165B70
	adds r0, r1, 0
	adds r0, 0xDC
	adds r0, r2, r0
	bl sub_8165B08
_08165B70:
	adds r5, r7, 0
	cmp r5, 0x3
	ble _08165B30
	pop {r3,r4}
	mov r8, r3
	mov r9, r4
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8165B20

	thumb_func_start sub_8165B88
sub_8165B88: @ 8165B88
	push {r4,lr}
	adds r4, r0, 0
	lsls r1, 16
	lsrs r2, r1, 16
	adds r3, r2, 0
	movs r0, 0xFA
	lsls r0, 1
	cmp r2, r0
	bne _08165BA4
	ldr r0, =gGameLanguage
	b _08165C28
	.pool
_08165BA4:
	ldr r0, =0x0000012b
	cmp r2, r0
	bhi _08165BB8
	ldr r0, =gGameLanguage
	b _08165C28
	.pool
_08165BB8:
	ldr r0, =0x0000018f
	cmp r2, r0
	bhi _08165BFC
	ldr r0, =gBattleTypeFlags
	ldr r0, [r0]
	movs r1, 0x80
	lsls r1, 17
	ands r0, r1
	cmp r0, 0
	beq _08165BDC
	bl sub_81864B4
	b _08165C2A
	.pool
_08165BDC:
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0xfffffed4
	adds r2, r1
	movs r1, 0xEC
	muls r1, r2
	adds r0, r1
	ldr r1, =0x0000081c
	adds r0, r1
	b _08165C28
	.pool
_08165BFC:
	ldr r0, =gBattleTypeFlags
	ldr r0, [r0]
	movs r1, 0x80
	lsls r1, 17
	ands r0, r1
	cmp r0, 0
	beq _08165C14
	bl sub_81864C0
	b _08165C2A
	.pool
_08165C14:
	ldr r0, =gSaveBlock2Ptr
	ldr r2, [r0]
	ldr r0, =0xfffffe70
	adds r1, r3, r0
	lsls r0, r1, 4
	adds r0, r1
	lsls r0, 2
	adds r2, r0
	ldr r1, =0x0000011b
	adds r0, r2, r1
_08165C28:
	ldrb r0, [r0]
_08165C2A:
	strb r0, [r4]
	pop {r4}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8165B88

	thumb_func_start sub_8165C40
sub_8165C40: @ 8165C40
	push {lr}
	ldr r0, =gSaveBlock2Ptr
	ldr r0, [r0]
	ldr r1, =0x00000ca9
	adds r2, r0, r1
	ldrb r1, [r2]
	movs r0, 0x3
	ands r0, r1
	cmp r0, 0x2
	beq _08165C84
	ldr r1, =gUnknown_0203BC88
	ldr r0, =gBattleFrontierTrainers
	str r0, [r1]
	ldr r1, =gUnknown_0203BC8C
	ldr r0, =gBattleFrontierMons
	str r0, [r1]
	ldrb r0, [r2]
	lsls r0, 30
	lsrs r0, 30
	bl BattleFrontierGetOpponentLvl
	b _08165C88
	.pool
_08165C84:
	bl sub_8165D78
_08165C88:
	lsls r0, 24
	lsrs r0, 24
	pop {r1}
	bx r1
	thumb_func_end sub_8165C40

	thumb_func_start BattleFrontierGetOpponentLvl
BattleFrontierGetOpponentLvl: @ 8165C90
	push {lr}
	lsls r0, 24
	lsrs r0, 24
	cmp r0, 0
	beq _08165C9E
	cmp r0, 0x1
	beq _08165CA2
_08165C9E:
	movs r0, 0x32
	b _08165CB0
_08165CA2:
	bl sub_8165CB4
	lsls r0, 24
	lsrs r0, 24
	cmp r0, 0x3B
	bhi _08165CB0
	movs r0, 0x3C
_08165CB0:
	pop {r1}
	bx r1
	thumb_func_end BattleFrontierGetOpponentLvl

	thumb_func_start sub_8165CB4
sub_8165CB4: @ 8165CB4
	push {r4-r6,lr}
	movs r6, 0
	movs r5, 0
_08165CBA:
	movs r0, 0x64
	adds r1, r5, 0
	muls r1, r0
	ldr r0, =gPlayerParty
	adds r4, r1, r0
	adds r0, r4, 0
	movs r1, 0xB
	movs r2, 0
	bl GetMonData
	cmp r0, 0
	beq _08165CF4
	adds r0, r4, 0
	movs r1, 0x41
	movs r2, 0
	bl GetMonData
	movs r1, 0xCE
	lsls r1, 1
	cmp r0, r1
	beq _08165CF4
	adds r0, r4, 0
	movs r1, 0x38
	movs r2, 0
	bl GetMonData
	cmp r0, r6
	ble _08165CF4
	adds r6, r0, 0
_08165CF4:
	adds r5, 0x1
	cmp r5, 0x5
	ble _08165CBA
	adds r0, r6, 0
	pop {r4-r6}
	pop {r1}
	bx r1
	.pool
	thumb_func_end sub_8165CB4

	thumb_func_start sub_8165D08
sub_8165D08: @ 8165D08
	push {lr}
	lsls r0, 16
	lsrs r0, 16
	movs r1, 0x3
	cmp r0, 0x63
	bls _08165D3A
	movs r1, 0x6
	cmp r0, 0x77
	bls _08165D3A
	movs r1, 0x9
	cmp r0, 0x8B
	bls _08165D3A
	movs r1, 0xC
	cmp r0, 0x9F
	bls _08165D3A
	movs r1, 0xF
	cmp r0, 0xB3
	bls _08165D3A
	movs r1, 0x12
	cmp r0, 0xC7
	bls _08165D3A
	movs r1, 0x1F
	cmp r0, 0xDB
	bhi _08165D3A
	movs r1, 0x15
_08165D3A:
	adds r0, r1, 0
	pop {r1}
	bx r1
	thumb_func_end sub_8165D08

	thumb_func_start sub_8165D40
sub_8165D40: @ 8165D40
	push {lr}
	ldr r0, =0x000040cf
	bl VarGet
	lsls r0, 16
	lsrs r0, 16
	cmp r0, 0x2
	beq _08165D58
	cmp r0, 0x3
	beq _08165D58
	cmp r0, 0x4
	bne _08165D70
_08165D58:
	bl Random
	lsls r0, 16
	lsrs r0, 16
	movs r1, 0x1E
	bl __umodsi3
	lsls r0, 16
	lsrs r0, 16
	b _08165D72
	.pool
_08165D70:
	movs r0, 0
_08165D72:
	pop {r1}
	bx r1
	thumb_func_end sub_8165D40

	thumb_func_start sub_8165D78
sub_8165D78: @ 8165D78
	push {lr}
	ldr r0, =0x000040cf
	bl VarGet
	lsls r0, 16
	lsrs r0, 16
	cmp r0, 0x4
	bne _08165DA8
	ldr r1, =gUnknown_0203BC88
	ldr r0, =gSlateportBattleTentTrainers
	str r0, [r1]
	ldr r1, =gUnknown_0203BC8C
	ldr r0, =gSlateportBattleTentMons
	b _08165DF2
	.pool
_08165DA8:
	cmp r0, 0x2
	bne _08165DC8
	ldr r1, =gUnknown_0203BC88
	ldr r0, =gVerdanturfBattleTentTrainers
	str r0, [r1]
	ldr r1, =gUnknown_0203BC8C
	ldr r0, =gVerdanturfBattleTentMons
	b _08165DF2
	.pool
_08165DC8:
	cmp r0, 0x3
	bne _08165DE8
	ldr r1, =gUnknown_0203BC88
	ldr r0, =gFallarborBattleTentTrainers
	str r0, [r1]
	ldr r1, =gUnknown_0203BC8C
	ldr r0, =gFallarborBattleTentMons
	b _08165DF2
	.pool
_08165DE8:
	ldr r1, =gUnknown_0203BC88
	ldr r0, =gBattleFrontierTrainers
	str r0, [r1]
	ldr r1, =gUnknown_0203BC8C
	ldr r0, =gBattleFrontierMons
_08165DF2:
	str r0, [r1]
	bl sub_8165CB4
	lsls r0, 24
	lsrs r0, 24
	cmp r0, 0x1D
	bhi _08165E02
	movs r0, 0x1E
_08165E02:
	pop {r1}
	bx r1
	.pool
	thumb_func_end sub_8165D78

	thumb_func_start sub_8165E18
sub_8165E18: @ 8165E18
	push {r4,r5,lr}
	ldr r5, =gSaveBlock2Ptr
_08165E1C:
	bl sub_8165D40
	lsls r0, 16
	lsrs r4, r0, 16
	movs r3, 0
	ldr r1, [r5]
	ldr r2, =0x00000cb2
	adds r0, r1, r2
	ldrh r0, [r0]
	cmp r3, r0
	bge _08165E58
	adds r2, 0x2
	adds r0, r1, r2
	ldrh r0, [r0]
	cmp r0, r4
	beq _08165E58
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	subs r2, 0x2
	adds r0, r1, r2
	ldrh r2, [r0]
	ldr r0, =0x00000cb4
	adds r1, r0
_08165E4A:
	adds r1, 0x2
	adds r3, 0x1
	cmp r3, r2
	bge _08165E58
	ldrh r0, [r1]
	cmp r0, r4
	bne _08165E4A
_08165E58:
	ldr r0, [r5]
	ldr r1, =0x00000cb2
	adds r0, r1
	ldrh r0, [r0]
	cmp r3, r0
	bne _08165E1C
	ldr r5, =gTrainerBattleOpponent_A
	strh r4, [r5]
	ldrh r0, [r5]
	movs r1, 0
	bl sub_8162614
	ldr r0, =gSaveBlock2Ptr
	ldr r1, [r0]
	ldr r2, =0x00000cb2
	adds r0, r1, r2
	ldrh r2, [r0]
	adds r0, r2, 0x1
	cmp r0, 0x2
	bgt _08165E8C
	lsls r0, r2, 1
	ldr r2, =0x00000cb4
	adds r1, r2
	adds r1, r0
	ldrh r0, [r5]
	strh r0, [r1]
_08165E8C:
	pop {r4,r5}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8165E18

	thumb_func_start sub_8165EA4
sub_8165EA4: @ 8165EA4
	push {r4-r7,lr}
	mov r7, r10
	mov r6, r9
	mov r5, r8
	push {r5-r7}
	sub sp, 0x38
	lsls r1, 24
	lsrs r1, 24
	str r1, [sp, 0x18]
	lsls r2, 24
	lsrs r2, 24
	str r2, [sp, 0x1C]
	bl sub_8165D78
	lsls r0, 24
	lsrs r0, 24
	str r0, [sp, 0x20]
	ldr r0, =gTrainerBattleOpponent_A
	ldrh r2, [r0]
	ldr r0, =gUnknown_0203BC88
	ldr r1, [r0]
	movs r0, 0x34
	muls r0, r2
	adds r0, r1
	ldr r0, [r0, 0x30]
	str r0, [sp, 0x28]
	movs r0, 0
	str r0, [sp, 0x24]
	ldr r2, [sp, 0x28]
	ldrh r1, [r2]
	b _08165EFE
	.pool
_08165EEC:
	ldr r0, [sp, 0x24]
	adds r0, 0x1
	lsls r0, 24
	lsrs r0, 24
	str r0, [sp, 0x24]
	lsls r0, 1
	ldr r6, [sp, 0x28]
	adds r0, r6
	ldrh r1, [r0]
_08165EFE:
	ldr r0, =0x0000ffff
	cmp r1, r0
	bne _08165EEC
	movs r0, 0
	mov r8, r0
	bl Random
	adds r4, r0, 0
	bl Random
	lsls r4, 16
	lsrs r4, 16
	lsls r0, 16
	orrs r4, r0
	str r4, [sp, 0x2C]
	b _08166092
	.pool
_08165F24:
	bl Random
	lsls r0, 16
	lsrs r0, 16
	ldr r1, [sp, 0x24]
	bl __modsi3
	lsls r0, 1
	ldr r2, [sp, 0x28]
	adds r0, r2
	ldrh r4, [r0]
	movs r6, 0
	ldr r7, [sp, 0x18]
	add r7, r8
	b _08165F44
_08165F42:
	adds r6, 0x1
_08165F44:
	cmp r6, r7
	bge _08165F68
	movs r1, 0x64
	adds r0, r6, 0
	muls r0, r1
	ldr r2, =gEnemyParty
	adds r0, r2
	movs r1, 0xB
	movs r2, 0
	bl GetMonData
	ldr r1, =gUnknown_0203BC8C
	ldr r2, [r1]
	lsls r1, r4, 4
	adds r1, r2
	ldrh r1, [r1]
	cmp r0, r1
	bne _08165F42
_08165F68:
	cmp r6, r7
	beq _08165F6E
	b _08166092
_08165F6E:
	movs r6, 0
	cmp r6, r7
	bge _08165FB8
	ldr r0, =gBattleFrontierHeldItems
	mov r9, r0
	movs r3, 0
_08165F7A:
	ldr r1, =gEnemyParty
	adds r5, r3, r1
	adds r0, r5, 0
	movs r1, 0xC
	movs r2, 0
	str r3, [sp, 0x34]
	bl GetMonData
	ldr r3, [sp, 0x34]
	cmp r0, 0
	beq _08165FB0
	adds r0, r5, 0
	movs r1, 0xC
	movs r2, 0
	bl GetMonData
	ldr r1, =gUnknown_0203BC8C
	ldr r2, [r1]
	lsls r1, r4, 4
	adds r1, r2
	ldrb r1, [r1, 0xA]
	lsls r1, 1
	add r1, r9
	ldr r3, [sp, 0x34]
	ldrh r1, [r1]
	cmp r0, r1
	beq _08165FB8
_08165FB0:
	adds r3, 0x64
	adds r6, 0x1
	cmp r6, r7
	blt _08165F7A
_08165FB8:
	cmp r6, r7
	bne _08166092
	movs r6, 0
	cmp r6, r8
	bge _08165FDA
	add r0, sp, 0xC
	ldrh r0, [r0]
	cmp r0, r4
	beq _08165FDA
	add r1, sp, 0xC
_08165FCC:
	adds r1, 0x2
	adds r6, 0x1
	cmp r6, r8
	bge _08165FDA
	ldrh r0, [r1]
	cmp r0, r4
	bne _08165FCC
_08165FDA:
	cmp r6, r8
	bne _08166092
	mov r2, r8
	lsls r0, r2, 1
	add r0, sp
	adds r0, 0xC
	strh r4, [r0]
	movs r6, 0x64
	adds r0, r7, 0
	muls r0, r6
	ldr r1, =gEnemyParty
	adds r0, r1
	ldr r5, =gUnknown_0203BC8C
	ldr r2, [r5]
	lsls r4, 4
	adds r2, r4, r2
	ldrh r1, [r2]
	ldrb r3, [r2, 0xC]
	movs r6, 0
	str r6, [sp]
	ldrb r2, [r2, 0xB]
	str r2, [sp, 0x4]
	ldr r2, [sp, 0x2C]
	str r2, [sp, 0x8]
	ldr r2, [sp, 0x20]
	bl CreateMonWithEVSpreadPersonalityOTID
	add r1, sp, 0x14
	movs r0, 0xFF
	strb r0, [r1]
	mov r9, r4
	mov r0, r8
	adds r0, 0x1
	str r0, [sp, 0x30]
	movs r0, 0x64
	adds r1, r7, 0
	muls r1, r0
	mov r8, r1
	adds r3, r5, 0
	mov r5, r9
	ldr r2, =gEnemyParty
	mov r10, r2
_0816602E:
	ldr r0, [r3]
	adds r0, r5, r0
	lsls r4, r6, 1
	adds r0, 0x2
	adds r0, r4
	ldrh r1, [r0]
	lsls r2, r6, 24
	lsrs r2, 24
	mov r0, r8
	add r0, r10
	str r3, [sp, 0x34]
	bl SetMonMoveSlot
	ldr r3, [sp, 0x34]
	ldr r0, [r3]
	adds r0, r5, r0
	adds r0, 0x2
	adds r0, r4
	ldrh r0, [r0]
	cmp r0, 0xDA
	bne _0816605E
	movs r0, 0
	mov r1, sp
	strb r0, [r1, 0x14]
_0816605E:
	adds r6, 0x1
	cmp r6, 0x3
	ble _0816602E
	movs r2, 0x64
	adds r4, r7, 0
	muls r4, r2
	ldr r6, =gEnemyParty
	adds r4, r6
	adds r0, r4, 0
	movs r1, 0x20
	add r2, sp, 0x14
	bl SetMonData
	ldr r0, =gUnknown_0203BC8C
	ldr r0, [r0]
	add r0, r9
	ldrb r2, [r0, 0xA]
	lsls r2, 1
	ldr r0, =gBattleFrontierHeldItems
	adds r2, r0
	adds r0, r4, 0
	movs r1, 0xC
	bl SetMonData
	ldr r0, [sp, 0x30]
	mov r8, r0
_08166092:
	ldr r1, [sp, 0x1C]
	cmp r8, r1
	beq _0816609A
	b _08165F24
_0816609A:
	add sp, 0x38
	pop {r3-r5}
	mov r8, r3
	mov r9, r4
	mov r10, r5
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8165EA4

	thumb_func_start sub_81660B8
sub_81660B8: @ 81660B8
	push {lr}
	lsls r0, 24
	lsrs r2, r0, 24
	movs r1, 0
	ldr r3, =gUnknown_085DCEDC
	ldrb r0, [r3]
	cmp r0, r2
	beq _081660DA
_081660C8:
	adds r0, r1, 0x1
	lsls r0, 24
	lsrs r1, r0, 24
	cmp r1, 0x1D
	bhi _081660DA
	adds r0, r1, r3
	ldrb r0, [r0]
	cmp r0, r2
	bne _081660C8
_081660DA:
	cmp r1, 0x1E
	beq _081660EC
	ldr r0, =gUnknown_085DCF0E
	b _08166116
	.pool
_081660EC:
	movs r1, 0
	ldr r3, =gUnknown_085DCEFA
	ldrb r0, [r3]
	cmp r0, r2
	beq _08166108
_081660F6:
	adds r0, r1, 0x1
	lsls r0, 24
	lsrs r1, r0, 24
	cmp r1, 0x13
	bhi _08166108
	adds r0, r1, r3
	ldrb r0, [r0]
	cmp r0, r2
	bne _081660F6
_08166108:
	cmp r1, 0x14
	bne _08166114
	movs r0, 0x7
	b _0816611A
	.pool
_08166114:
	ldr r0, =gUnknown_085DCF2C
_08166116:
	adds r0, r1, r0
	ldrb r0, [r0]
_0816611A:
	pop {r1}
	bx r1
	.pool
	thumb_func_end sub_81660B8

	thumb_func_start sub_8166124
sub_8166124: @ 8166124
	push {r4-r6,lr}
	lsls r0, 24
	lsrs r6, r0, 24
	ldr r2, =gSaveBlock2Ptr
	movs r0, 0xEC
	muls r0, r6
	movs r1, 0xE7
	lsls r1, 3
	adds r0, r1
	ldr r1, [r2]
	movs r5, 0
	movs r4, 0
	movs r3, 0
	adds r1, r0
_08166140:
	ldm r1!, {r0}
	adds r5, r0
	orrs r4, r0
	adds r3, 0x1
	cmp r3, 0x39
	bls _08166140
	cmp r5, 0
	bne _08166154
	cmp r4, 0
	beq _08166180
_08166154:
	ldr r2, [r2]
	movs r0, 0xEC
	adds r1, r6, 0
	muls r1, r0
	movs r3, 0x82
	lsls r3, 4
	adds r0, r2, r3
	adds r0, r1
	ldr r0, [r0]
	cmp r0, r5
	bne _08166174
	movs r0, 0x1
	b _08166182
	.pool
_08166174:
	movs r3, 0xE7
	lsls r3, 3
	adds r0, r1, r3
	adds r0, r2, r0
	bl sub_8164FB8
_08166180:
	movs r0, 0
_08166182:
	pop {r4-r6}
	pop {r1}
	bx r1
	thumb_func_end sub_8166124

	thumb_func_start sub_8166188
sub_8166188: @ 8166188
	push {r4-r7,lr}
	ldr r0, =gBattleTypeFlags
	ldr r0, [r0]
	ldr r1, =0x02000002
	ands r0, r1
	cmp r0, 0
	beq _081661E8
	bl sub_8165C40
	lsls r0, 24
	movs r5, 0
	ldr r7, =gBaseStats
	lsrs r0, 22
	ldr r1, =gExperienceTables
	adds r6, r0, r1
_081661A6:
	movs r0, 0x64
	adds r1, r5, 0
	muls r1, r0
	ldr r0, =gEnemyParty
	adds r4, r1, r0
	adds r0, r4, 0
	movs r1, 0xB
	movs r2, 0
	bl GetMonData
	adds r1, r0, 0
	cmp r1, 0
	beq _081661E2
	lsls r0, r1, 3
	subs r0, r1
	lsls r0, 2
	adds r0, r7
	ldrb r1, [r0, 0x13]
	movs r0, 0xCA
	lsls r0, 1
	adds r2, r1, 0
	muls r2, r0
	adds r2, r6
	adds r0, r4, 0
	movs r1, 0x19
	bl SetMonData
	adds r0, r4, 0
	bl CalculateMonStats
_081661E2:
	adds r5, 0x1
	cmp r5, 0x5
	ble _081661A6
_081661E8:
	pop {r4-r7}
	pop {r0}
	bx r0
	.pool
	thumb_func_end sub_8166188

	.align 2, 0 @ Don't pad with nop.
