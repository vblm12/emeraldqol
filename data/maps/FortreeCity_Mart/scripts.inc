FortreeCity_Mart_MapScripts:: @ 8217665
	.byte 0

FortreeCity_Mart_EventScript_217666:: @ 8217666
	lock
	faceplayer
	message gUnknown_08272A21
	waitmessage
	pokemart FortreeCity_Mart_Pokemart_217680
	msgbox gUnknown_08272A3F, 4
	release
	end

	.align 2
FortreeCity_Mart_Pokemart_217680: @ 8217680
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_ORAN_BERRY
	.2byte ITEM_SITRUS_BERRY
	.2byte ITEM_PECHA_BERRY
	.2byte ITEM_CHERI_BERRY
	.2byte ITEM_CHESTO_BERRY
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_WOOD_MAIL
	.2byte ITEM_NONE
	release
	end

FortreeCity_Mart_EventScript_217698:: @ 8217698
	msgbox FortreeCity_Mart_Text_2176B3, 2
	end

FortreeCity_Mart_EventScript_2176A1:: @ 82176A1
	msgbox FortreeCity_Mart_Text_217715, 2
	end

FortreeCity_Mart_EventScript_2176AA:: @ 82176AA
	msgbox FortreeCity_Mart_Text_21778E, 2
	end

FortreeCity_Mart_Text_2176B3: @ 82176B3
	.string "SUPER REPEL lasts a long time,\n"
	.string "and it gets the job done.\p"
	.string "It’s much better than an ordinary\n"
	.string "REPEL.$"

FortreeCity_Mart_Text_217715: @ 8217715
	.string "I always stock up on more items than\n"
	.string "I’m sure I’ll need.\p"
	.string "You never know what might happen.\n"
	.string "Better to be safe than sorry!$"

FortreeCity_Mart_Text_21778E: @ 821778E
	.string "A RARE CANDY makes a POKéMON grow\n"
	.string "immediately by one level.$"

