BattleFrontier_Mart_MapScripts:: @ 8267ACB
	.byte 0

BattleFrontier_Mart_EventScript_267ACC:: @ 8267ACC
	lock
	faceplayer
	message gUnknown_08272A21
	waitmessage
	pokemart BattleFrontier_Mart_Pokemart_267AE4
	msgbox gUnknown_08272A3F, 4
	release
	end

	.align 2
BattleFrontier_Mart_Pokemart_267AE4: @ 8267AE4
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SITRUS_BERRY
	.2byte ITEM_LUM_BERRY
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_PROTEIN
	.2byte ITEM_CALCIUM
	.2byte ITEM_IRON
	.2byte ITEM_ZINC
	.2byte ITEM_CARBOS
	.2byte ITEM_HP_UP
	.2byte ITEM_NONE
	release
	end

BattleFrontier_Mart_EventScript_267B02:: @ 8267B02
	msgbox BattleFrontier_Mart_Text_267B29, 2
	end

BattleFrontier_Mart_EventScript_267B0B:: @ 8267B0B
	lock
	applymovement 2, BattleFrontier_Mart_Movement_2725B0
	waitmovement 0
	msgbox BattleFrontier_Mart_Text_267B8F, 4
	release
	end

BattleFrontier_Mart_EventScript_267B20:: @ 8267B20
	msgbox BattleFrontier_Mart_Text_267C01, 2
	end

BattleFrontier_Mart_Text_267B29: @ 8267B29
	.string "We came here to chaperon our\n"
	.string "grandson.\p"
	.string "But since we’re here, we thought\n"
	.string "we should get some souvenirs.$"

BattleFrontier_Mart_Text_267B8F: @ 8267B8F
	.string "Dear, what do you think of this?\n"
	.string "Wouldn’t this make a nice gift?\p"
	.string "It’s…PRO…TE…IN?\n"
	.string "It sounds delicious, doesn’t it?$"

BattleFrontier_Mart_Text_267C01: @ 8267C01
	.string "A lot of the BATTLE FRONTIER’s\n"
	.string "facilities don’t allow the use of items\l"
	.string "during battles.\p"
	.string "That rule makes things tougher than\n"
	.string "they already are!$"

