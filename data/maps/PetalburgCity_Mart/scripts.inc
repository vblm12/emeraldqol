PetalburgCity_Mart_MapScripts:: @ 8207D68
	.byte 0

PetalburgCity_Mart_EventScript_207D69:: @ 8207D69
	lock
	faceplayer
	message gUnknown_08272A21
	waitmessage
	checkflag FLAG_0x128
	goto_eq PetalburgCity_Mart_EventScript_207DA6
	pokemart PetalburgCity_Mart_Pokemart_207D8C
	msgbox gUnknown_08272A3F, 4
	release
	end

	.align 2
PetalburgCity_Mart_Pokemart_207D8C: @ 8207D8C
	.2byte ITEM_POKE_BALL
	.2byte ITEM_ORAN_BERRY
	.2byte ITEM_PECHA_BERRY
	.2byte ITEM_CHERI_BERRY
	.2byte ITEM_CHESTO_BERRY
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_ORANGE_MAIL
	.2byte ITEM_NONE
	release
	end

PetalburgCity_Mart_EventScript_207DA6:: @ 8207DA6
	pokemart PetalburgCity_Mart_Pokemart_207DB8
	msgbox gUnknown_08272A3F, 4
	release
	end

	.align 2
PetalburgCity_Mart_Pokemart_207DB8: @ 8207DB8
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ORAN_BERRY
	.2byte ITEM_PECHA_BERRY
	.2byte ITEM_CHERI_BERRY
	.2byte ITEM_CHESTO_BERRY
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_ORANGE_MAIL
	.2byte ITEM_NONE
	release
	end

PetalburgCity_Mart_EventScript_207DD6:: @ 8207DD6
	msgbox PetalburgCity_Mart_Text_207DF1, 2
	end

PetalburgCity_Mart_EventScript_207DDF:: @ 8207DDF
	msgbox PetalburgCity_Mart_Text_207E60, 2
	end

PetalburgCity_Mart_EventScript_207DE8:: @ 8207DE8
	msgbox PetalburgCity_Mart_Text_207EB0, 2
	end

PetalburgCity_Mart_Text_207DF1: @ 8207DF1
	.string "Even if a POKéMON is weak now,\n"
	.string "it will grow stronger.\p"
	.string "The most important thing is love!\n"
	.string "Love for your POKéMON!$"

PetalburgCity_Mart_Text_207E60: @ 8207E60
	.string "Do you use REPEL?\n"
	.string "It keeps POKéMON away, so it’s\l"
	.string "useful when you’re in a hurry.$"

PetalburgCity_Mart_Text_207EB0: @ 8207EB0
	.string "Do you have any PECHA BERRIES with\n"
	.string "you?\p"
	.string "A poisoned POKéMON, will lose HP\n"
	.string "until it faints.\l"
	.string "Take some PECHA BERRIES with you.$"

