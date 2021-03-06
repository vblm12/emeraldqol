Route104_MrBrineysHouse_MapScripts:: @ 8229D2E
	map_script 3, Route104_MrBrineysHouse_MapScript1_229D34
	.byte 0

Route104_MrBrineysHouse_MapScript1_229D34: @ 8229D34
	setflag FLAG_LANDMARK_MR_BRINEY_HOUSE
	compare VAR_0x4090, 1
	call_if 1, Route104_MrBrineysHouse_EventScript_229D50
	checkflag FLAG_0x0BC
	call_if 1, Route104_MrBrineysHouse_EventScript_229D4C
	end

Route104_MrBrineysHouse_EventScript_229D4C:: @ 8229D4C
	setflag FLAG_0x32E
	return

Route104_MrBrineysHouse_EventScript_229D50:: @ 8229D50
	setobjectxyperm 1, 9, 3
	setobjectmovementtype 1, 50
	setobjectxyperm 2, 9, 6
	setobjectmovementtype 2, 51
	return

Route104_MrBrineysHouse_EventScript_229D67:: @ 8229D67
	lock
	faceplayer
	checkflag FLAG_0x093
	call_if 0, Route104_MrBrineysHouse_EventScript_229D8A
	checkflag FLAG_0x0BD
	goto_if 0, Route104_MrBrineysHouse_EventScript_229DE1
	checkflag FLAG_0x095
	goto_if 0, Route104_MrBrineysHouse_EventScript_229DFA
	goto Route104_MrBrineysHouse_EventScript_229DAE
	end

Route104_MrBrineysHouse_EventScript_229D8A:: @ 8229D8A
	setflag FLAG_0x093
	msgbox Route104_MrBrineysHouse_Text_229E70, 4
	msgbox Route104_MrBrineysHouse_Text_229E9B, 5
	compare VAR_RESULT, 0
	goto_eq Route104_MrBrineysHouse_EventScript_229E13
	goto Route104_MrBrineysHouse_EventScript_229E27
	end

Route104_MrBrineysHouse_EventScript_229DAE:: @ 8229DAE
	message Route104_MrBrineysHouse_Text_22A268
	waitmessage
	multichoicedefault 20, 8, 14, 1, 0
	switch VAR_RESULT
	case 0, Route104_MrBrineysHouse_EventScript_229E27
	case 1, Route104_MrBrineysHouse_EventScript_229E1D
	case 127, Route104_MrBrineysHouse_EventScript_229E1D
	end

Route104_MrBrineysHouse_EventScript_229DE1:: @ 8229DE1
	msgbox Route104_MrBrineysHouse_Text_22A0AD, 5
	compare VAR_RESULT, 0
	goto_eq Route104_MrBrineysHouse_EventScript_229E13
	goto Route104_MrBrineysHouse_EventScript_229E27
	end

Route104_MrBrineysHouse_EventScript_229DFA:: @ 8229DFA
	msgbox Route104_MrBrineysHouse_Text_22A18F, 5
	compare VAR_RESULT, 0
	goto_eq Route104_MrBrineysHouse_EventScript_229E13
	goto Route104_MrBrineysHouse_EventScript_229E27
	end

Route104_MrBrineysHouse_EventScript_229E13:: @ 8229E13
	msgbox Route104_MrBrineysHouse_Text_22A041, 4
	release
	end

Route104_MrBrineysHouse_EventScript_229E1D:: @ 8229E1D
	msgbox Route104_MrBrineysHouse_Text_22A2C3, 4
	release
	end

Route104_MrBrineysHouse_EventScript_229E27:: @ 8229E27
	msgbox Route104_MrBrineysHouse_Text_229FE9, 4
	call Route104_MrBrineysHouse_EventScript_271E95
	setvar VAR_0x408E, 1
	clearflag FLAG_0x2E2
	setflag FLAG_0x2E3
	setflag FLAG_0x371
	setvar VAR_0x405A, 8
	setvar VAR_0x4063, 2
	setflag FLAG_0x32E
	setflag FLAG_0x2CF
	warp MAP_ROUTE104, 255, 13, 51
	waitstate
	releaseall
	end

Route104_MrBrineysHouse_EventScript_229E5D:: @ 8229E5D
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, 0
	msgbox Route104_MrBrineysHouse_Text_22A337, 4
	waitmoncry
	release
	end

Route104_MrBrineysHouse_Text_229E70: @ 8229E70
	.string "MR. BRINEY: Hold on, lass!\n"
	.string "Wait up, PEEKO!$"

Route104_MrBrineysHouse_Text_229E9B: @ 8229E9B
	.string "Hm? You’re {PLAYER}{KUN}!\n"
	.string "You saved my darling PEEKO!\l"
	.string "We owe so much to you!\p"
	.string "What’s that?\n"
	.string "You want to sail with me?\p"
	.string "Hmhm…\p"
	.string "You have a LETTER bound for DEWFORD\n"
	.string "and a package for SLATEPORT, then?\p"
	.string "Quite the busy life you must lead!\p"
	.string "But, certainly, what you’re asking is\n"
	.string "no problem at all.\p"
	.string "You’ve come to the right man!\n"
	.string "We’ll set sail for DEWFORD.$"

Route104_MrBrineysHouse_Text_229FE9: @ 8229FE9
	.string "MR. BRINEY: DEWFORD it is, then!\p"
	.string "Anchors aweigh!\n"
	.string "PEEKO, we’re setting sail, my darling!$"

Route104_MrBrineysHouse_Text_22A041: @ 822A041
	.string "MR. BRINEY: Is that so?\n"
	.string "Your deliveries can wait?\p"
	.string "You just go on and tell me whenever\n"
	.string "you want to set sail!$"

Route104_MrBrineysHouse_Text_22A0AD: @ 822A0AD
	.string "MR. BRINEY: Ahoy!\n"
	.string "I know exactly what you want to say!\p"
	.string "You’re to deliver a LETTER to DEWFORD\n"
	.string "and a package to SLATEPORT.\p"
	.string "What you need me to do is no problem\n"
	.string "at all--I’m the man for the job!\p"
	.string "First, we’ll set sail for DEWFORD.$"

Route104_MrBrineysHouse_Text_22A18F: @ 822A18F
	.string "MR. BRINEY: Ahoy!\n"
	.string "I know exactly what you want to say!\p"
	.string "You’re to deliver a package to\n"
	.string "CAPT. STERN in SLATEPORT.\p"
	.string "What you need me to do is no problem\n"
	.string "at all--I’m the man for the job!\p"
	.string "First, we’ll set sail for DEWFORD.$"

Route104_MrBrineysHouse_Text_22A268: @ 822A268
	.string "MR. BRINEY: Ahoy!\n"
	.string "For you, I’ll go out to sea anytime!\p"
	.string "Now, my friend, where are we bound?$"

Route104_MrBrineysHouse_Text_22A2C3: @ 822A2C3
	.string "MR. BRINEY: Is that so?\n"
	.string "Well, PEEKO owes her life to you.\p"
	.string "You just go on and tell me whenever\n"
	.string "you want to set sail!$"

Route104_MrBrineysHouse_Text_22A337: @ 822A337
	.string "PEEKO: Pii piihyoro!$"

