	.include "asm/macros.inc"
	.include "constants/constants.inc"

	.section .rodata

gUnknown_0861F3EC:: @ 861F3EC
	.4byte sub_81C9298
	.4byte sub_81C941C
	.4byte sub_81C9924
	.4byte sub_81C9990
	.4byte sub_81C99C0
	.4byte sub_81C9430
	.4byte sub_81C99D4
	.4byte sub_81C9298
	.4byte sub_81C941C
	.4byte sub_81C9940
	.4byte sub_81C9990
	.4byte sub_81C99C0
	.4byte sub_81C9430
	.4byte sub_81C99D4
	.4byte sub_81C9338
	.4byte sub_81C941C
	.4byte sub_81C9940
	.4byte sub_81C9990
	.4byte sub_81C99C0
	.4byte sub_81C9430
	.4byte sub_81C99D4
	.4byte sub_81C9368
	.4byte sub_81C941C
	.4byte sub_81C9940
	.4byte sub_81C9990
	.4byte sub_81C99C0
	.4byte sub_81C9430
	.4byte sub_81C99D4
	.4byte sub_81C92CC
	.4byte sub_81C941C
	.4byte sub_81C9940
	.4byte sub_81C9990
	.4byte sub_81C99C0
	.4byte sub_81C9430
	.4byte sub_81C99D4
	.4byte sub_81C9304
	.4byte sub_81C941C
	.4byte sub_81C9940
	.4byte sub_81C9990
	.4byte sub_81C99C0
	.4byte sub_81C9430
	.4byte sub_81C99D4
	.4byte sub_81CC4D4
	.4byte sub_81CC554
	.4byte sub_81CC5F4
	.4byte sub_81CC62C
	.4byte sub_81CC65C
	.4byte sub_81CC524
	.4byte sub_81CC670
	.4byte sub_81CCFD8
	.4byte sub_81CD070
	.4byte sub_81CDDD4
	.4byte sub_81CDE2C
	.4byte sub_81CDE64
	.4byte sub_81CD1C0
	.4byte sub_81CECA0
	.4byte sub_81CEF3C
	.4byte sub_81CEFDC
	.4byte sub_81CF330
	.4byte sub_81CF3A0
	.4byte sub_81CF3D0
	.4byte sub_81CEFF0
	.4byte sub_81CF3F8
	.4byte sub_81CD024
	.4byte sub_81CD070
	.4byte sub_81CDDD4
	.4byte sub_81CDE2C
	.4byte sub_81CDE64
	.4byte sub_81CD1C0
	.4byte sub_81CECA0
	.4byte sub_81CEF98
	.4byte sub_81CEFDC
	.4byte sub_81CF368
	.4byte sub_81CF3A0
	.4byte sub_81CF3D0
	.4byte sub_81CEFF0
	.4byte sub_81CF3F8
	.4byte sub_81CAAE8
	.4byte sub_81CAB24
	.4byte sub_81CB260
	.4byte sub_81CB29C
	.4byte sub_81CB2CC
	.4byte sub_81CAB38
	.4byte sub_81CB2E0
	.4byte sub_81CF9BC
	.4byte sub_81CFA34
	.4byte sub_81CFDD0
	.4byte sub_81CFE40
	.4byte sub_81CFE70
	.4byte sub_81CFA48
	.4byte sub_81CFE98
	.4byte sub_81D0450
	.4byte sub_81D04A0
	.4byte sub_81D0978
	.4byte sub_81D09B0
	.4byte sub_81D09E0
	.4byte sub_81D04B8
	.4byte sub_81D09F4
	.4byte sub_81CFA04
	.4byte sub_81CFA34
	.4byte sub_81CFE08
	.4byte sub_81CFE40
	.4byte sub_81CFE70
	.4byte sub_81CFA48
	.4byte sub_81CFE98

gUnknown_0861F590:: @ 861F590
	.incbin "graphics/pokenav/icon2.gbapal"

gUnknown_0861F5B0:: @ 861F5B0
	.incbin "graphics/pokenav/icon2.4bpp.lz"

gUnknown_0861F994:: @ 861F994
	.incbin "graphics/pokenav/icon2_unused.4bpp.lz"

gUnknown_0861FA04:: @ 861FA04
	.byte 0x50
	.byte 0x0
	.byte 0x0
	.byte 0x0

gUnknown_0861FA08:: @ 861FA08
	window_template 0, 1, 0x16, 0x10, 0x2, 0x0, 0x36
	null_window_template

gUnknown_0861FA18:: @ 861FA18
	.4byte gUnknown_085EBED5
	.4byte gUnknown_085EBED9
	.4byte gUnknown_085EBEE9
	.4byte gUnknown_085EBEF9
	.4byte gUnknown_085EBF0E
	.4byte gUnknown_085EBF22
	.4byte gUnknown_085EBF39
	.4byte gUnknown_085EBF49
	.4byte gUnknown_085EBF57
	.4byte gUnknown_085EBF60
	.4byte gUnknown_085EBF73
	.4byte gUnknown_085EBF84

gUnknown_0861FA48:: @ 861FA48
	.byte 0x4
	.byte 0x1
	.byte 0x2
	.byte 0x0

gUnknown_0861FA4C:: @ 861FA4C
	obj_tiles gUnknown_0861F5B0, 0x1000, 0

gUnknown_0861FA54:: @ 861FA54
	obj_pal gUnknown_0861F590, 0
	null_obj_pal

gUnknown_0861FA64:: @ 861FA64
	obj_tiles gPokenavLeftHeaderHoennMap_Gfx, 0xC00, 2

gUnknown_0861FA6C:: @ 861FA6C
	obj_tiles gPokenavLeftHeaderMainMenu_Gfx, 0x20, 3
	obj_tiles gPokenavLeftHeaderCondition_Gfx, 0x20, 1
	obj_tiles gPokenavLeftHeaderRibbons_Gfx, 0x20, 2
	obj_tiles gPokenavLeftHeaderMatchCall_Gfx, 0x20, 4
	obj_tiles gPokenavLeftHeaderHoennMap_Gfx, 0x20, 0
	obj_tiles gPokenavLeftHeaderHoennMap_Gfx, 0x40, 0

gUnknown_0861FA9C:: @ 861FA9C
	.4byte gPokenavLeftHeaderParty_Gfx, 1
	.4byte gPokenavLeftHeaderSearch_Gfx, 1
	.4byte gPokenavLeftHeaderCool_Gfx, 4
	.4byte gPokenavLeftHeaderBeauty_Gfx, 1
	.4byte gPokenavLeftHeaderCute_Gfx, 2
	.4byte gPokenavLeftHeaderSmart_Gfx, 0
	.4byte gPokenavLeftHeaderTough_Gfx, 0

gUnknown_0861FAD4:: @ 861FAD4
	.2byte 0x0
	.2byte 0x8000
	.2byte 0x0
	.2byte 0x0

gUnknown_0861FADC::
	obj_image_anim_frame 0, 8
	obj_image_anim_frame 16, 8
	obj_image_anim_frame 32, 8
	obj_image_anim_frame 48, 8
	obj_image_anim_frame 64, 8
	obj_image_anim_frame 80, 8
	obj_image_anim_frame 96, 8
	obj_image_anim_frame 112, 8
	obj_image_anim_jump 0

gUnknown_0861FB00::
	.4byte gUnknown_0861FADC

gUnknown_0861FB04:: @ 861FB04
	spr_template 0, 0, gUnknown_0861FAD4, gUnknown_0861FB00, NULL, gDummySpriteAffineAnimTable, sub_81C7CB4 

gUnknown_0861FB1C::
	.2byte 0x4000
	.2byte 0xC000
	.2byte 0x400
	.2byte 0x0

gUnknown_0861FB24::
	.2byte 0x4000
	.2byte 0x8000
	.2byte 0x400
	.2byte 0x0

gUnknown_0861FB2C:: @ 861FB2C
	spr_template 2, 1, gUnknown_0861FB1C, gDummySpriteAnimTable, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy

gUnknown_0861FB44:: @ 861FB44
	spr_template 2, 2, gUnknown_0861FB24, gDummySpriteAnimTable, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy
	
gUnknown_0861FB5C:: @ 861FB5C
	.incbin "graphics/pokenav/arrows_matchcall.gbapal"
	
gUnknown_0861FB7C:: @ 861FB7C
	.incbin "graphics/pokenav/arrows_matchcall.4bpp.lz"

gUnknown_0861FBE4:: @ 861FBE4
	.byte 0x0
	.byte 0x2
	.byte 0x5
	.byte 0x0

gUnknown_0861FBE8:: @ 861FBE8
	.4byte gUnknown_085EBEA8
	.4byte gUnknown_085EBEB1
	.4byte gUnknown_085EBEC3

gUnknown_0861FBF4:: @ 861FBF4
	.byte 0x1
	.byte 0x4
	.byte 0x5

gUnknown_0861FBF7:: @ 861FBF7
	.byte 0x2
	.byte 0x4
	.byte 0x6
	.byte 0x7
	.byte 0x0

gUnknown_0861FBFC:: @ 861FBFC
	.4byte gUnknown_0861FB7C
	.2byte 0xC0
	.2byte 0xA

gUnknown_0861FC04:: @ 861FC04
	.4byte gUnknown_0861FB5C
	.4byte 0x14
	.4byte 0x0
	.4byte 0x0
	
gUnknown_0861FC14:: @ 861FC14
	.4byte 0x8000
	.4byte 0x800

gUnknown_0861FC1C:: @ 861FC1C
	spr_template 10, 20, gUnknown_0861FC14, gDummySpriteAnimTable, NULL, gDummySpriteAffineAnimTable, sub_81C9080
	
gUnknown_0861FC34:: @ 861FC34
	.4byte 0x4000
	.4byte 0x800

gUnknown_0861FC3C:: @ 861FC3C
	spr_template 10, 20, gUnknown_0861FC34, gDummySpriteAnimTable, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy

gUnknown_0861FC54:: @ 861FC54
	.byte 2
	.byte 3
	.byte 4
	.byte 2
	.byte 5

gUnknown_0861FC59:: @ 861FC59
	.byte 0, 1, 4, 4, 4, 4, 0, 1, 2, 4, 4, 4, 0, 1, 2, 3, 4, 4, 5, 6, 7, 4, 4, 4, 8, 9, 10, 11, 12, 13, 0

gUnknown_0861FC78:: @ 861FC78
	.incbin "graphics/pokenav/bg.gbapal"

gUnknown_0861FC98:: @ 861FC98
	.incbin "graphics/pokenav/bg.4bpp.lz"

gUnknown_0861FCAC:: @ 861FCAC
	.incbin "graphics/pokenav/bg.bin.lz"

gUnknown_0861FD4C:: @ 861FD4C
	.incbin "graphics/pokenav/outline.gbapal"

gUnknown_0861FD6C:: @ 861FD6C
	.incbin "graphics/pokenav/outline.4bpp.lz"

gUnknown_0861FFF4:: @ 861FFF4
	.incbin "graphics/pokenav/outline_map.bin.lz"

gUnknown_08620104:: @ 8620104
	.incbin "graphics/pokenav/blue_light.gbapal"
	
gUnknown_08620124:: @ 8620124
	.incbin "graphics/pokenav/blue_light.4bpp.lz"

gUnknown_08620194:: @ 8620194
	.byte 0xF5, 0x10, 0, 0, 0x7A, 0x21, 0, 0, 0xFF, 0x31, 0, 0

gUnknown_086201A0:: @ 86201A0
	.4byte NULL
	.4byte sub_81C9C6C
	.4byte sub_81C9CA8
	.4byte sub_81C9D44
	.4byte sub_81C9DD8
	.4byte sub_81C9E58
	.4byte sub_81C9EC8
	.4byte sub_81C9EF8
	.4byte sub_81C9F28

gUnknown_086201C4:: @ 86201C4
	.4byte gPokenavOptions_Gfx
	.byte 0, 0x34, 3, 0
	.4byte gUnknown_08620124
	.byte 0, 1, 1, 0

gUnknown_086201D4:: @ 86201D4
	.4byte gPokenavOptions_Pal + 0x0, 4
	.4byte gPokenavOptions_Pal + 0x20, 5
	.4byte gPokenavOptions_Pal + 0x40, 6
	.4byte gPokenavOptions_Pal + 0x60, 7
	.4byte gPokenavOptions_Pal + 0x80, 8
	.4byte gUnknown_08620104, 3
	.4byte 0, 0
	
gUnknown_0862020C:: @ 862020C
	.2byte 0, 0

gUnknown_08620210:: @ 8620210
	.2byte 0x20, 1
	
gUnknown_08620214:: @ 8620214
	.2byte 0x40, 4
	
gUnknown_08620218:: @ 8620218
	.2byte 0x60, 2

gUnknown_0862021C:: @ 862021C
	.2byte 0x80, 3
	
gUnknown_08620220:: @ 8620220
	.2byte 0xA0, 1

gUnknown_08620224:: @ 8620224
	.2byte 0xC0, 1

gUnknown_08620228:: @ 8620228
	.2byte 0xE0, 4

gUnknown_0862022C:: @ 862022C
	.2byte 0x100, 1

gUnknown_08620230:: @ 8620230
	.2byte 0x120, 2

gUnknown_08620234:: @ 8620234
	.2byte 0x140, 0

gUnknown_08620238:: @ 8620238
	.2byte 0x160, 0

gUnknown_0862023C:: @ 862023C
	.2byte 0x180, 3

gUnknown_08620240:: @ 8620240
	.2byte 0x2A, 0x14

gUnknown_08620244:: @ 8620244
	.4byte gUnknown_0862020C
	.4byte gUnknown_08620210
	.4byte gUnknown_0862021C
	.4byte NULL
	.4byte NULL
	.4byte NULL
	.2byte 0x2A, 0x14
	.4byte gUnknown_0862020C
	.4byte gUnknown_08620210
	.4byte gUnknown_08620214
	.4byte gUnknown_0862021C
	.4byte NULL
	.4byte NULL
	.2byte 0x2A, 0x14
	.4byte gUnknown_0862020C
	.4byte gUnknown_08620210
	.4byte gUnknown_08620214
	.4byte gUnknown_08620218
	.4byte gUnknown_0862021C
	.4byte NULL
	.2byte 0x38, 0x14
	.4byte gUnknown_08620220
	.4byte gUnknown_08620224
	.4byte gUnknown_0862023C
	.4byte NULL
	.4byte NULL
	.4byte NULL
	.2byte 0x28, 0x10
	.4byte gUnknown_08620228
	.4byte gUnknown_0862022C
	.4byte gUnknown_08620230
	.4byte gUnknown_08620234
	.4byte gUnknown_08620238
	.4byte gUnknown_0862023C

gUnknown_086202CC:: @ 86202CC
	window_template 1, 3, 17, 0x18, 2, 1, 8

gUnknown_086202D4:: @ 86202D4
	.4byte gUnknown_085EBCC5
	.4byte gUnknown_085EBCE8
	.4byte gUnknown_085EBD01
	.4byte gUnknown_085EBD1C
	.4byte gUnknown_085EBD34
	.4byte gUnknown_085EBD83
	.4byte gUnknown_085EBDA2
	.4byte gUnknown_085EBDBF
	.4byte gUnknown_085EBDDB
	.4byte gUnknown_085EBDEE
	.4byte gUnknown_085EBE06
	.4byte gUnknown_085EBE19
	.4byte gUnknown_085EBE2D
	.4byte gUnknown_085EBE41

gUnknown_0862030C:: @ 862030C
	.byte 6, 8, 7

gUnknown_0862030F:: @ 862030F
	.byte 6, 8, 7, 0, 0
	
gUnknown_08620314:: @ 8620314
	.byte 0, 0x40, 0, 0x80, 0, 8, 0, 0
	
gUnknown_0862031C:: @ 862031C
	obj_rot_scal_anim_frame 0x100, 0x100, 0, 0
	obj_rot_scal_anim_end
	
gUnknown_0862032C:: @ 862032C
	obj_rot_scal_anim_frame 0x100, 0x100, 0, 0
	obj_rot_scal_anim_frame 0x10, 0x10, 0, 0x12
	obj_rot_scal_anim_end

gUnknown_08620344:: @ 8620344
	.4byte gUnknown_0862031C
	.4byte gUnknown_0862032C

gUnknown_0862034C:: @ 862034C
	spr_template 3, 4, gUnknown_08620314, gDummySpriteAnimTable, NULL, gUnknown_08620344, SpriteCallbackDummy
	
gUnknown_08620364:: @ 8620364
	.2byte 0x4000
	.2byte 0x8000
	.2byte 0x800
	.2byte 0

gUnknown_0862036C:: @ 862036C
	spr_template 1, 3, gUnknown_08620364, gDummySpriteAnimTable, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy

gUnknown_08620384:: @ 8620384
	 .4byte 0x4000040
	 .4byte 0xa2600001
	 .byte 1, 0, 0, 0
	 
gUnknown_08620390:: @ 8620390
	.string "Becalm fighting emotions.$"

gUnknown_086203AA:: @ 86203AA
	.string "Fragrant GRASS POKéMON.$"

gUnknown_086203C2:: @ 86203C2
	.string "Soothing aromas make the$"

gUnknown_086203DB:: @ 86203DB
	.string "body and mind healthy.$"

gUnknown_086203F2:: @ 86203F2
	.string "I’m not very good at this.$"

gUnknown_0862040D:: @ 862040D
	.string "Ruin-exploration partners.$"

gUnknown_08620428:: @ 8620428
	.string "I am searching for undersea$"

gUnknown_08620444:: @ 8620444
	.string "ruins and relics.$"

gUnknown_08620456:: @ 8620456
	.string "Overwhelm with power!$"

gUnknown_0862046C:: @ 862046C
	.string "Craggy ROCK POKéMON.$"

gUnknown_08620481:: @ 8620481
	.string "In search of ancient lore,$"

gUnknown_0862049C:: @ 862049C
	.string "I travel the world.$"

gUnknown_086204B0:: @ 86204B0
	.string "I’m going to try hard!$"

gUnknown_086204C7:: @ 86204C7
	.string "Good swimmer POKéMON.$"

gUnknown_086204DD:: @ 86204DD
	.string "I wish I could swim without$"

gUnknown_086204F9:: @ 86204F9
	.string "using an inner tube.$"

gUnknown_0862050E:: @ 862050E
	.string "I don’t know. I’ll try hard.$"

gUnknown_0862052B:: @ 862052B
	.string "WATER POKéMON are buddies.$"

gUnknown_08620546:: @ 8620546
	.string "It’s not like I can’t swim.$"

gUnknown_08620562:: @ 8620562
	.string "I just like my inner tube.$"

gUnknown_0862057D:: @ 862057D
	.string "We split our duties.$"

gUnknown_08620592:: @ 8620592
	.string "We like friendly POKéMON.$"

gUnknown_086205AC:: @ 86205AC
	.string "We enjoy POKéMON together$"

gUnknown_086205C6:: @ 86205C6
	.string "as sister and brother.$"

gUnknown_086205DD:: @ 86205DD
	.string "I finish with power moves!$"

gUnknown_086205F8:: @ 86205F8
	.string "A mix of different types.$"

gUnknown_08620612:: @ 8620612
	.string "I aim to become the ultimate$"

gUnknown_0862062F:: @ 862062F
	.string "TRAINER!$"

gUnknown_08620638:: @ 8620638
	.string "Exploit the foe’s weakness.$"

gUnknown_08620654:: @ 8620654
	.string "Balance is crucial.$"

gUnknown_08620668:: @ 8620668
	.string "My goal is to become the$"

gUnknown_08620681:: @ 8620681
	.string "POKéMON CHAMPION.$"

gUnknown_08620693:: @ 8620693
	.string "Upset the opponent.$"

gUnknown_086206A7:: @ 86206A7
	.string "Type doesn’t matter.$"

gUnknown_086206BC:: @ 86206BC
	.string "I’m a top student at the$"

gUnknown_086206D5:: @ 86206D5
	.string "TRAINER’S SCHOOL.$"

gUnknown_086206E7:: @ 86206E7
	.string "Slow, steady suffering.$"

gUnknown_086206FF:: @ 86206FF
	.string "Scary to meet at night.$"

gUnknown_08620717:: @ 8620717
	.string "I see things that others$"

gUnknown_08620730:: @ 8620730
	.string "can’t see...$"

gUnknown_0862073D:: @ 862073D
	.string "Anything to win.$"

gUnknown_0862074E:: @ 862074E
	.string "Gorgeous type!$"

gUnknown_0862075D:: @ 862075D
	.string "I have a pool specially for$"

gUnknown_08620779:: @ 8620779
	.string "my POKéMON at home.$"

gUnknown_0862078D:: @ 862078D
	.string "You’ll fall under my spell!$"

gUnknown_086207A9:: @ 86207A9
	.string "Mature WATER type.$"

gUnknown_086207BC:: @ 86207BC
	.string "I dream of cruising around$"

gUnknown_086207D7:: @ 86207D7
	.string "the world on a luxury liner.$"

gUnknown_086207F4:: @ 86207F4
	.string "I’ll lead you astray.$"

gUnknown_0862080A:: @ 862080A
	.string "Cute, of course.$"

gUnknown_0862081B:: @ 862081B
	.string "I love the SAFARI ZONE.$"

gUnknown_08620833:: @ 8620833
	.string "I seem to end up there.$"

gUnknown_0862084B:: @ 862084B
	.string "Strategy? Who needs it?$"

gUnknown_08620863:: @ 8620863
	.string "I spent big money on it!$"

gUnknown_0862087C:: @ 862087C
	.string "I, being rich, sleep in a$"

gUnknown_08620896:: @ 8620896
	.string "custom POKéMON bed.$"

gUnknown_086208AA:: @ 86208AA
	.string "Wrestle down with power.$"

gUnknown_086208C3:: @ 86208C3
	.string "Took all night to catch.$"

gUnknown_086208DC:: @ 86208DC
	.string "Big, burly, and buff$"

gUnknown_086208F1:: @ 86208F1
	.string "POKéMON are the best...$"

gUnknown_08620909:: @ 8620909
	.string "Ram at full speed!$"

gUnknown_0862091C:: @ 862091C
	.string "Funky WATER type!$"

gUnknown_0862092E:: @ 862092E
	.string "If I can’t be out swimming,$"

gUnknown_0862094A:: @ 862094A
	.string "I’ll be pumping weights.$"

gUnknown_08620963:: @ 8620963
	.string "Grand slam pummeling!$"

gUnknown_08620979:: @ 8620979
	.string "FIGHTING type.$"

gUnknown_08620988:: @ 8620988
	.string "Not to brag, but I can bust$"

gUnknown_086209A4:: @ 86209A4
	.string "ten roof tiles!$"

gUnknown_086209B4:: @ 86209B4
	.string "Witness karate power!$"

gUnknown_086209CA:: @ 86209CA
	.string "My partners in training!$"

gUnknown_086209E3:: @ 86209E3
	.string "Let us discuss matters of$"

gUnknown_086209FD:: @ 86209FD
	.string "the world with bare fists!$"

gUnknown_08620A18:: @ 8620A18
	.string "Rock to stunning sounds!$"

gUnknown_08620A31:: @ 8620A31
	.string "Electric-and-sound combo!$"

gUnknown_08620A4B:: @ 8620A4B
	.string "My compositions will shock$"

gUnknown_08620A66:: @ 8620A66
	.string "you and stun you!$"

gUnknown_08620A78:: @ 8620A78
	.string "I’ll electrify you!$"

gUnknown_08620A8C:: @ 8620A8C
	.string "They’re ELECTRIC!$"

gUnknown_08620A9E:: @ 8620A9E
	.string "I want to make people cry$"

gUnknown_08620AB8:: @ 8620AB8
	.string "with songs from my heart.$"

gUnknown_08620AD2:: @ 8620AD2
	.string "Burn it all down!$"

gUnknown_08620AE4:: @ 8620AE4
	.string "Burn-inducing POKéMON.$"

gUnknown_08620AFB:: @ 8620AFB
	.string "When you light a campfire,$"

gUnknown_08620B16:: @ 8620B16
	.string "be sure there’s some water.$"

gUnknown_08620B32:: @ 8620B32
	.string "Hang in and be tenacious!$"

gUnknown_08620B4C:: @ 8620B4C
	.string "I’ll raise any POKéMON.$"

gUnknown_08620B64:: @ 8620B64
	.string "POKéMON raised in the wild$"

gUnknown_08620B7F:: @ 8620B7F
	.string "grow strong!$"

gUnknown_08620B8C:: @ 8620B8C
	.string "Our love lets us prevail.$"

gUnknown_08620BA6:: @ 8620BA6
	.string "We’ve had them for years.$"

gUnknown_08620BC0:: @ 8620BC0
	.string "Married 50 years, we’ve$"

gUnknown_08620BD8:: @ 8620BD8
	.string "devotedly raised POKéMON.$"

gUnknown_08620BF2:: @ 8620BF2
	.string "Attack in waves!$"

gUnknown_08620C03:: @ 8620C03
	.string "BUG POKéMON are cool.$"

gUnknown_08620C19:: @ 8620C19
	.string "I go into the forest every$"

gUnknown_08620C34:: @ 8620C34
	.string "day to catch BUG POKéMON.$"

gUnknown_08620C4E:: @ 8620C4E
	.string "Daze and confuse!$"

gUnknown_08620C60:: @ 8620C60
	.string "Ones with weird powers.$"

gUnknown_08620C78:: @ 8620C78
	.string "I can see through exactly$"

gUnknown_08620C92:: @ 8620C92
	.string "what you’re thinking!$"

gUnknown_08620CA8:: @ 8620CA8
	.string "Battle at full power.$"

gUnknown_08620CBE:: @ 8620CBE
	.string "POKéMON of many mysteries.$"

gUnknown_08620CD9:: @ 8620CD9
	.string "When we spoke, I was really$"

gUnknown_08620CF5:: @ 8620CF5
	.string "using telepathy.$"

gUnknown_08620D06:: @ 8620D06
	.string "Calm and collected.$"

gUnknown_08620D1A:: @ 8620D1A
	.string "POKéMON of distinction.$"

gUnknown_08620D32:: @ 8620D32
	.string "We enjoy a spot of tea$"

gUnknown_08620D49:: @ 8620D49
	.string "every day. It’s imported.$"

gUnknown_08620D63:: @ 8620D63
	.string "I use my head to battle.$"

gUnknown_08620D7C:: @ 8620D7C
	.string "I love any kind of POKéMON!$"

gUnknown_08620D98:: @ 8620D98
	.string "My daddy gives me spending$"

gUnknown_08620DB3:: @ 8620DB3
	.string "money if I ace a test.$"

gUnknown_08620DCA:: @ 8620DCA
	.string "My knowledge rules!$"

gUnknown_08620DDE:: @ 8620DDE
	.string "Any smart POKéMON!$"

gUnknown_08620DF1:: @ 8620DF1
	.string "I want to be a POKéMON$"

gUnknown_08620E08:: @ 8620E08
	.string "researcher in the future.$"

gUnknown_08620E22:: @ 8620E22
	.string "We talk it over first.$"

gUnknown_08620E39:: @ 8620E39
	.string "POKéMON that we both like.$"

gUnknown_08620E54:: @ 8620E54
	.string "We’re senior and junior$"

gUnknown_08620E6C:: @ 8620E6C
	.string "students into POKéMON!$"

gUnknown_08620E83:: @ 8620E83
	.string "Go for it, my dears!$"

gUnknown_08620E98:: @ 8620E98
	.string "I have no likes or dislikes.$"

gUnknown_08620EB5:: @ 8620EB5
	.string "While out shopping for$"

gUnknown_08620ECC:: @ 8620ECC
	.string "supper, I battle too.$"

gUnknown_08620EE2:: @ 8620EE2
	.string "I battle with love!$"

gUnknown_08620EF6:: @ 8620EF6
	.string "A POKéMON raised with love!$"

gUnknown_08620F12:: @ 8620F12
	.string "It’s important to build$"

gUnknown_08620F2A:: @ 8620F2A
	.string "trust with your POKéMON.$"

gUnknown_08620F43:: @ 8620F43
	.string "I see through your moves!$"

gUnknown_08620F5D:: @ 8620F5D
	.string "The essence of FIGHTING.$"

gUnknown_08620F76:: @ 8620F76
	.string "I’m not ready to give way$"

gUnknown_08620F90:: @ 8620F90
	.string "to the young yet!$"

gUnknown_08620FA2:: @ 8620FA2
	.string "Attack while defending.$"

gUnknown_08620FBA:: @ 8620FBA
	.string "The FIGHTING type.$"

gUnknown_08620FCD:: @ 8620FCD
	.string "Being old, I have my own$"

gUnknown_08620FE6:: @ 8620FE6
	.string "style of battling.$"

gUnknown_08620FF9:: @ 8620FF9
	.string "I do what I can.$"

gUnknown_0862100A:: @ 862100A
	.string "I use different types.$"

gUnknown_08621021:: @ 8621021
	.string "I’m going to keep working$"

gUnknown_0862103B:: @ 862103B
	.string "until I beat a GYM LEADER.$"

gUnknown_08621056:: @ 8621056
	.string "I battle patiently.$"

gUnknown_0862106A:: @ 862106A
	.string "WATER POKéMON to battle!$"

gUnknown_08621083:: @ 8621083
	.string "I’m the world’s only guy to$"

gUnknown_0862109F:: @ 862109F
	.string "catch a huge POKéMON!$"

gUnknown_086210B5:: @ 86210B5
	.string "Exploit the environment!$"

gUnknown_086210CE:: @ 86210CE
	.string "All hail the WATER type!$"

gUnknown_086210E7:: @ 86210E7
	.string "I won’t be beaten by some$"

gUnknown_08621101:: @ 8621101
	.string "beach bum SWIMMER!$"

gUnknown_08621114:: @ 8621114
	.string "Speed above all!$"

gUnknown_08621125:: @ 8621125
	.string "I use a speedy POKéMON.$"

gUnknown_0862113D:: @ 862113D
	.string "A marathon is a challenge$"

gUnknown_08621157:: @ 8621157
	.string "against your own self.$"

gUnknown_0862116E:: @ 862116E
	.string "Defense is crucial.$"

gUnknown_08621182:: @ 8621182
	.string "My POKéMON is solid.$"

gUnknown_08621197:: @ 8621197
	.string "I started this for dieting,$"

gUnknown_086211B3:: @ 86211B3
	.string "but I got right into it.$"

gUnknown_086211CC:: @ 86211CC
	.string "Strike before stricken!$"

gUnknown_086211E4:: @ 86211E4
	.string "A fast-running POKéMON!$"

gUnknown_086211FC:: @ 86211FC
	.string "If you ran and ran, you’d$"

gUnknown_08621216:: @ 8621216
	.string "become one with the wind.$"

gUnknown_08621230:: @ 8621230
	.string "All-out offensive!$"

gUnknown_08621243:: @ 8621243
	.string "WATER POKéMON rule!$"

gUnknown_08621257:: @ 8621257
	.string "I must swim over 6 miles$"

gUnknown_08621270:: @ 8621270
	.string "every day.$"

gUnknown_0862127B:: @ 862127B
	.string "Push and push again!$"

gUnknown_08621290:: @ 8621290
	.string "The strength of STEEL.$"

gUnknown_086212A7:: @ 86212A7
	.string "If you’re sweating, get$"

gUnknown_086212BF:: @ 86212BF
	.string "fluids into you regularly.$"

gUnknown_086212DA:: @ 86212DA
	.string "Draw the power of WATER.$"

gUnknown_086212F3:: @ 86212F3
	.string "Toughened WATER POKéMON.$"

gUnknown_0862130C:: @ 862130C
	.string "Training POKéMON is good,$"

gUnknown_08621326:: @ 8621326
	.string "but don’t neglect yourself.$"

gUnknown_08621342:: @ 8621342
	.string "It’s about POKéMON power!$"

gUnknown_0862135C:: @ 862135C
	.string "See the power of DRAGONS!$"

gUnknown_08621376:: @ 8621376
	.string "I’ll become legendary as the$"

gUnknown_08621393:: @ 8621393
	.string "strongest one day!$"

gUnknown_086213A6:: @ 86213A6
	.string "I’ll show you my technique!$"

gUnknown_086213C2:: @ 86213C2
	.string "Elegantly wheeling BIRDS.$"

gUnknown_086213DC:: @ 86213DC
	.string "My BIRD POKéMON, deliver my$"

gUnknown_086213F8:: @ 86213F8
	.string "love to that girl!$"

gUnknown_0862140B:: @ 862140B
	.string "You’ll suffer from poison!$"

gUnknown_08621426:: @ 8621426
	.string "Poisonous POKéMON.$"

gUnknown_08621439:: @ 8621439
	.string "I undertake training so$"

gUnknown_08621451:: @ 8621451
	.string "that I may become a ninja.$"

gUnknown_0862146C:: @ 862146C
	.string "The first strike wins!$"

gUnknown_08621483:: @ 8621483
	.string "Speedy FIGHTING type.$"

gUnknown_08621499:: @ 8621499
	.string "If my POKéMON lose,$"

gUnknown_086214AD:: @ 86214AD
	.string "I’ll carry on the fight!$"

gUnknown_086214C6:: @ 86214C6
	.string "Go, go, my POKéMON!$"

gUnknown_086214DA:: @ 86214DA
	.string "I’ll raise anything.$"

gUnknown_086214EF:: @ 86214EF
	.string "UV rays are your skin’s$"

gUnknown_08621507:: @ 8621507
	.string "enemy. Get protected.$"

gUnknown_0862151D:: @ 862151D
	.string "No mercy!$"

gUnknown_08621527:: @ 8621527
	.string "Cute WATER POKéMON.$"

gUnknown_0862153B:: @ 862153B
	.string "I have too many fans.$"

gUnknown_08621551:: @ 8621551
	.string "I was interviewed on TV.$"

gUnknown_0862156A:: @ 862156A
	.string "I think about this & that.$"

gUnknown_08621585:: @ 8621585
	.string "I like all POKéMON.$"

gUnknown_08621599:: @ 8621599
	.string "What lies beyond that$"

gUnknown_086215AF:: @ 86215AF
	.string "yonder hill?$"

gUnknown_086215BC:: @ 86215BC
	.string "We battle together!$"

gUnknown_086215D0:: @ 86215D0
	.string "We train together!$"

gUnknown_086215E3:: @ 86215E3
	.string "We like the same POKéMON,$"

gUnknown_086215FD:: @ 86215FD
	.string "but different desserts.$"

gUnknown_08621615:: @ 8621615
	.string "I force things with power!$"

gUnknown_08621630:: @ 8621630
	.string "WATER and FIGHTING types.$"

gUnknown_0862164A:: @ 862164A
	.string "Seamen are rough spirits!$"

gUnknown_08621664:: @ 8621664
	.string "Any complaints?$"

gUnknown_08621674:: @ 8621674
	.string "Up for a fight anytime!$"

gUnknown_0862168C:: @ 862168C
	.string "WATER POKéMON are my faves!$"

gUnknown_086216A8:: @ 86216A8
	.string "If you want to shout loud,$"

gUnknown_086216C3:: @ 86216C3
	.string "suck in air with your belly!$"

gUnknown_086216E0:: @ 86216E0
	.string "Protect POKéMON from harm.$"

gUnknown_086216FB:: @ 86216FB
	.string "I love rare POKéMON.$"

gUnknown_08621710:: @ 8621710
	.string "I want to collect all the$"

gUnknown_0862172A:: @ 862172A
	.string "world’s rare POKéMON.$"

gUnknown_08621740:: @ 8621740
	.string "I count on power.$"

gUnknown_08621752:: @ 8621752
	.string "POKéMON are my children.$"

gUnknown_0862176B:: @ 862176B
	.string "It takes knowledge and$"

gUnknown_08621782:: @ 8621782
	.string "love to raise POKéMON.$"

gUnknown_08621799:: @ 8621799
	.string "Full-on attack!$"

gUnknown_086217A9:: @ 86217A9
	.string "Anything. I’ll raise it.$"

gUnknown_086217C2:: @ 86217C2
	.string "I give them {POKEBLOCK}S for$"

gUnknown_086217D9:: @ 86217D9
	.string "going after CONTEST titles.$"

gUnknown_086217F5:: @ 86217F5
	.string "I raise POKéMON with care.$"

gUnknown_08621810:: @ 8621810
	.string "Fun-to-raise POKéMON.$"

gUnknown_08621826:: @ 8621826
	.string "Treat every POKéMON you$"

gUnknown_0862183E:: @ 862183E
	.string "meet with respect.$"

gUnknown_08621851:: @ 8621851
	.string "I believe in my POKéMON.$"

gUnknown_0862186A:: @ 862186A
	.string "I like strong POKéMON.$"

gUnknown_08621881:: @ 8621881
	.string "I’m training for rescue$"

gUnknown_08621899:: @ 8621899
	.string "work with my POKéMON.$"

gUnknown_086218AF:: @ 86218AF
	.string "Attack in waves!$"

gUnknown_086218C0:: @ 86218C0
	.string "I use different types.$"

gUnknown_086218D7:: @ 86218D7
	.string "Those who destroy nature$"

gUnknown_086218F0:: @ 86218F0
	.string "must never be forgiven!$"

gUnknown_08621908:: @ 8621908
	.string "I’ll show you some guts!$"

gUnknown_08621921:: @ 8621921
	.string "Cute POKéMON are my faves!$"

gUnknown_0862193C:: @ 862193C
	.string "After a battle, I always$"

gUnknown_08621955:: @ 8621955
	.string "bathe with my POKéMON.$"

gUnknown_0862196C:: @ 862196C
	.string "Lightning-fast attack!$"

gUnknown_08621983:: @ 8621983
	.string "BUG POKéMON are number 1!$"

gUnknown_0862199D:: @ 862199D
	.string "If you want to catch BUG$"

gUnknown_086219B6:: @ 86219B6
	.string "POKéMON, wake up early.$"

gUnknown_086219CE:: @ 86219CE
	.string "I battle with power.$"

gUnknown_086219E3:: @ 86219E3
	.string "Hard-bodied POKéMON.$"

gUnknown_086219F8:: @ 86219F8
	.string "I’ve been planning a month$"

gUnknown_08621A13:: @ 8621A13
	.string "for today’s hike.$"

gUnknown_08621A25:: @ 8621A25
	.string "I like it hot!$"

gUnknown_08621A34:: @ 8621A34
	.string "Hot POKéMON!$"

gUnknown_08621A41:: @ 8621A41
	.string "As much as I love POKéMON,$"

gUnknown_08621A5C:: @ 8621A5C
	.string "I surely like hiking!$"

gUnknown_08621A72:: @ 8621A72
	.string "Lovey-dovey strategy!$"

gUnknown_08621A88:: @ 8621A88
	.string "Lovey-dovey POKéMON!$"

gUnknown_08621A9D:: @ 8621A9D
	.string "We’re lovey-dovey!$"

gUnknown_08621AB0:: @ 8621AB0
	.string "Forever lovey-dovey!$"

gUnknown_08621AC5:: @ 8621AC5
	.string "We let it all hang out.$"

gUnknown_08621ADD:: @ 8621ADD
	.string "The 1st POKéMON I caught.$"

gUnknown_08621AF7:: @ 8621AF7
	.string "POKéMON and I have grown$"

gUnknown_08621B10:: @ 8621B10
	.string "stronger together.$"

gUnknown_08621B23:: @ 8621B23
	.string "ROCK-type power attack.$"

gUnknown_08621B3B:: @ 8621B3B
	.string "I prefer rock-hard POKéMON.$"

gUnknown_08621B57:: @ 8621B57
	.string "A LEADER of a big GYM bears$"

gUnknown_08621B73:: @ 8621B73
	.string "a lot of responsibility.$"

gUnknown_08621B8C:: @ 8621B8C
	.string "Direct physical action!$"

gUnknown_08621BA4:: @ 8621BA4
	.string "FIGHTING POKéMON rule!$"

gUnknown_08621BBB:: @ 8621BBB
	.string "The world awaits me as the$"

gUnknown_08621BD6:: @ 8621BD6
	.string "next big wave!$"

gUnknown_08621BE5:: @ 8621BE5
	.string "I choose to electrify.$"

gUnknown_08621BFC:: @ 8621BFC
	.string "Get shocked by electricity!$"

gUnknown_08621C18:: @ 8621C18
	.string "One must never throw a$"

gUnknown_08621C2F:: @ 8621C2F
	.string "match. Even I must not.$"

gUnknown_08621C47:: @ 8621C47
	.string "Battle aggressively.$"

gUnknown_08621C5C:: @ 8621C5C
	.string "Burn with passion!$"

gUnknown_08621C6F:: @ 8621C6F
	.string "Completely wash away daily$"

gUnknown_08621C8A:: @ 8621C8A
	.string "fatigue in hot springs!$"

gUnknown_08621CA2:: @ 8621CA2
	.string "I flexibly adapt my style.$"

gUnknown_08621CBD:: @ 8621CBD
	.string "Grown in a balanced manner.$"

gUnknown_08621CD9:: @ 8621CD9
	.string "I walk the 30 minutes from$"

gUnknown_08621CF4:: @ 8621CF4
	.string "home to here every day.$"

gUnknown_08621D0C:: @ 8621D0C
	.string "I take advantage of speed.$"

gUnknown_08621D27:: @ 8621D27
	.string "Graceful sky dancers.$"

gUnknown_08621D3D:: @ 8621D3D
	.string "The ultimate would be to$"

gUnknown_08621D56:: @ 8621D56
	.string "live as one with nature.$"

gUnknown_08621D6F:: @ 8621D6F
	.string "We battle in cooperation.$"

gUnknown_08621D89:: @ 8621D89
	.string "Always friendly POKéMON.$"

gUnknown_08621DA2:: @ 8621DA2
	.string "Papa has trouble telling$"

gUnknown_08621DBB:: @ 8621DBB
	.string "the two of us apart!$"

gUnknown_08621DD0:: @ 8621DD0
	.string "I use splendid waterpower.$"

gUnknown_08621DEB:: @ 8621DEB
	.string "POKéMON of elegance!$"

gUnknown_08621E00:: @ 8621E00
	.string "The adulation of beautiful$"

gUnknown_08621E1B:: @ 8621E1B
	.string "ladies fills me with energy!$"

gUnknown_08621E38:: @ 8621E38
	.string "Offense over defense!$"

gUnknown_08621E4E:: @ 8621E4E
	.string "The DARK side’s beauties.$"

gUnknown_08621E68:: @ 8621E68
	.string "They said I was a punk, but$"

gUnknown_08621E84:: @ 8621E84
	.string "I’m one of the ELITE FOUR!$"

gUnknown_08621E9F:: @ 8621E9F
	.string "Confuse and confound.$"

gUnknown_08621EB5:: @ 8621EB5
	.string "There’s nothing definite.$"

gUnknown_08621ECF:: @ 8621ECF
	.string "I wonder how my grandma at$"

gUnknown_08621EEA:: @ 8621EEA
	.string "MT. PYRE is doing?$"

gUnknown_08621EFD:: @ 8621EFD
	.string "I use items for help.$"

gUnknown_08621F13:: @ 8621F13
	.string "Flaming passion in icy cold!$"

gUnknown_08621F30:: @ 8621F30
	.string "The ICE type can be better$"

gUnknown_08621F4B:: @ 8621F4B
	.string "trained in this hot land.$"

gUnknown_08621F65:: @ 8621F65
	.string "Harness strong abilities.$"

gUnknown_08621F7F:: @ 8621F7F
	.string "The raw power of DRAGONS!$"

gUnknown_08621F99:: @ 8621F99
	.string "I dedicate myself to the$"

gUnknown_08621FB2:: @ 8621FB2
	.string "POKéMON that saved me.$"

gUnknown_08621FC9:: @ 8621FC9
	.string "Dignity and respect.$"

gUnknown_08621FDE:: @ 8621FDE
	.string "I prefer POKéMON of grace.$"

gUnknown_08621FF9:: @ 8621FF9
	.string "I represent beauty as$"

gUnknown_0862200F:: @ 862200F
	.string "well as intelligence.$"

.align 2

@ strategy, mon text, introduction1, introduction2 
gUnknown_08622028:: @ 8622028
	.4byte gUnknown_08620390, gUnknown_086203AA, gUnknown_086203C2, gUnknown_086203DB
	.4byte gUnknown_086203F2, gUnknown_0862040D, gUnknown_08620428, gUnknown_08620444
	.4byte gUnknown_08620456, gUnknown_0862046C, gUnknown_08620481, gUnknown_0862049C
	.4byte gUnknown_086204B0, gUnknown_086204C7, gUnknown_086204DD, gUnknown_086204F9
	.4byte gUnknown_0862050E, gUnknown_0862052B, gUnknown_08620546, gUnknown_08620562
	.4byte gUnknown_0862057D, gUnknown_08620592, gUnknown_086205AC, gUnknown_086205C6
	.4byte gUnknown_086205DD, gUnknown_086205F8, gUnknown_08620612, gUnknown_0862062F
	.4byte gUnknown_08620638, gUnknown_08620654, gUnknown_08620668, gUnknown_08620681
	.4byte gUnknown_08620693, gUnknown_086206A7, gUnknown_086206BC, gUnknown_086206D5
	.4byte gUnknown_086206E7, gUnknown_086206FF, gUnknown_08620717, gUnknown_08620730
	.4byte gUnknown_0862073D, gUnknown_0862074E, gUnknown_0862075D, gUnknown_08620779
	.4byte gUnknown_0862078D, gUnknown_086207A9, gUnknown_086207BC, gUnknown_086207D7
	.4byte gUnknown_086207F4, gUnknown_0862080A, gUnknown_0862081B, gUnknown_08620833
	.4byte gUnknown_0862084B, gUnknown_08620863, gUnknown_0862087C, gUnknown_08620896
	.4byte gUnknown_086208AA, gUnknown_086208C3, gUnknown_086208DC, gUnknown_086208F1
	.4byte gUnknown_08620909, gUnknown_0862091C, gUnknown_0862092E, gUnknown_0862094A
	.4byte gUnknown_08620963, gUnknown_08620979, gUnknown_08620988, gUnknown_086209A4
	.4byte gUnknown_086209B4, gUnknown_086209CA, gUnknown_086209E3, gUnknown_086209FD
	.4byte gUnknown_08620A18, gUnknown_08620A31, gUnknown_08620A4B, gUnknown_08620A66
	.4byte gUnknown_08620A78, gUnknown_08620A8C, gUnknown_08620A9E, gUnknown_08620AB8
	.4byte gUnknown_08620AD2, gUnknown_08620AE4, gUnknown_08620AFB, gUnknown_08620B16
	.4byte gUnknown_08620B32, gUnknown_08620B4C, gUnknown_08620B64, gUnknown_08620B7F
	.4byte gUnknown_08620B8C, gUnknown_08620BA6, gUnknown_08620BC0, gUnknown_08620BD8
	.4byte gUnknown_08620BF2, gUnknown_08620C03, gUnknown_08620C19, gUnknown_08620C34
	.4byte gUnknown_08620C4E, gUnknown_08620C60, gUnknown_08620C78, gUnknown_08620C92
	.4byte gUnknown_08620CA8, gUnknown_08620CBE, gUnknown_08620CD9, gUnknown_08620CF5
	.4byte gUnknown_08620D06, gUnknown_08620D1A, gUnknown_08620D32, gUnknown_08620D49
	.4byte gUnknown_08620D63, gUnknown_08620D7C, gUnknown_08620D98, gUnknown_08620DB3
	.4byte gUnknown_08620DCA, gUnknown_08620DDE, gUnknown_08620DF1, gUnknown_08620E08
	.4byte gUnknown_08620E22, gUnknown_08620E39, gUnknown_08620E54, gUnknown_08620E6C
	.4byte gUnknown_08620E83, gUnknown_08620E98, gUnknown_08620EB5, gUnknown_08620ECC
	.4byte gUnknown_08620EE2, gUnknown_08620EF6, gUnknown_08620F12, gUnknown_08620F2A
	.4byte gUnknown_08620F43, gUnknown_08620F5D, gUnknown_08620F76, gUnknown_08620F90
	.4byte gUnknown_08620FA2, gUnknown_08620FBA, gUnknown_08620FCD, gUnknown_08620FE6
	.4byte gUnknown_08620FF9, gUnknown_0862100A, gUnknown_08621021, gUnknown_0862103B
	.4byte gUnknown_08621056, gUnknown_0862106A, gUnknown_08621083, gUnknown_0862109F
	.4byte gUnknown_086210B5, gUnknown_086210CE, gUnknown_086210E7, gUnknown_08621101
	.4byte gUnknown_08621114, gUnknown_08621125, gUnknown_0862113D, gUnknown_08621157
	.4byte gUnknown_0862116E, gUnknown_08621182, gUnknown_08621197, gUnknown_086211B3
	.4byte gUnknown_086211CC, gUnknown_086211E4, gUnknown_086211FC, gUnknown_08621216
	.4byte gUnknown_08621230, gUnknown_08621243, gUnknown_08621257, gUnknown_08621270
	.4byte gUnknown_0862127B, gUnknown_08621290, gUnknown_086212A7, gUnknown_086212BF
	.4byte gUnknown_086212DA, gUnknown_086212F3, gUnknown_0862130C, gUnknown_08621326
	.4byte gUnknown_08621342, gUnknown_0862135C, gUnknown_08621376, gUnknown_08621393
	.4byte gUnknown_086213A6, gUnknown_086213C2, gUnknown_086213DC, gUnknown_086213F8
	.4byte gUnknown_0862140B, gUnknown_08621426, gUnknown_08621439, gUnknown_08621451
	.4byte gUnknown_0862146C, gUnknown_08621483, gUnknown_08621499, gUnknown_086214AD
	.4byte gUnknown_086214C6, gUnknown_086214DA, gUnknown_086214EF, gUnknown_08621507
	.4byte gUnknown_0862151D, gUnknown_08621527, gUnknown_0862153B, gUnknown_08621551
	.4byte gUnknown_0862156A, gUnknown_08621585, gUnknown_08621599, gUnknown_086215AF
	.4byte gUnknown_086215BC, gUnknown_086215D0, gUnknown_086215E3, gUnknown_086215FD
	.4byte gUnknown_08621615, gUnknown_08621630, gUnknown_0862164A, gUnknown_08621664
	.4byte gUnknown_08621674, gUnknown_0862168C, gUnknown_086216A8, gUnknown_086216C3
	.4byte gUnknown_086216E0, gUnknown_086216FB, gUnknown_08621710, gUnknown_0862172A
	.4byte gUnknown_08621740, gUnknown_08621752, gUnknown_0862176B, gUnknown_08621782
	.4byte gUnknown_08621799, gUnknown_086217A9, gUnknown_086217C2, gUnknown_086217D9
	.4byte gUnknown_086217F5, gUnknown_08621810, gUnknown_08621826, gUnknown_0862183E
	.4byte gUnknown_08621851, gUnknown_0862186A, gUnknown_08621881, gUnknown_08621899
	.4byte gUnknown_086218AF, gUnknown_086218C0, gUnknown_086218D7, gUnknown_086218F0
	.4byte gUnknown_08621908, gUnknown_08621921, gUnknown_0862193C, gUnknown_08621955
	.4byte gUnknown_0862196C, gUnknown_08621983, gUnknown_0862199D, gUnknown_086219B6
	.4byte gUnknown_086219CE, gUnknown_086219E3, gUnknown_086219F8, gUnknown_08621A13
	.4byte gUnknown_08621A25, gUnknown_08621A34, gUnknown_08621A41, gUnknown_08621A5C
	.4byte gUnknown_08621A72, gUnknown_08621A88, gUnknown_08621A9D, gUnknown_08621AB0
	.4byte gUnknown_08621AC5, gUnknown_08621ADD, gUnknown_08621AF7, gUnknown_08621B10
	.4byte gUnknown_08621B23, gUnknown_08621B3B, gUnknown_08621B57, gUnknown_08621B73
	.4byte gUnknown_08621B8C, gUnknown_08621BA4, gUnknown_08621BBB, gUnknown_08621BD6
	.4byte gUnknown_08621BE5, gUnknown_08621BFC, gUnknown_08621C18, gUnknown_08621C2F
	.4byte gUnknown_08621C47, gUnknown_08621C5C, gUnknown_08621C6F, gUnknown_08621C8A
	.4byte gUnknown_08621CA2, gUnknown_08621CBD, gUnknown_08621CD9, gUnknown_08621CF4
	.4byte gUnknown_08621D0C, gUnknown_08621D27, gUnknown_08621D3D, gUnknown_08621D56
	.4byte gUnknown_08621D6F, gUnknown_08621D89, gUnknown_08621DA2, gUnknown_08621DBB
	.4byte gUnknown_08621DD0, gUnknown_08621DEB, gUnknown_08621E00, gUnknown_08621E1B
	.4byte gUnknown_08621E38, gUnknown_08621E4E, gUnknown_08621E68, gUnknown_08621E84
	.4byte gUnknown_08621E9F, gUnknown_08621EB5, gUnknown_08621ECF, gUnknown_08621EEA
	.4byte gUnknown_08621EFD, gUnknown_08621F13, gUnknown_08621F30, gUnknown_08621F4B
	.4byte gUnknown_08621F65, gUnknown_08621F7F, gUnknown_08621F99, gUnknown_08621FB2
	.4byte gUnknown_08621FC9, gUnknown_08621FDE, gUnknown_08621FF9, gUnknown_0862200F

gUnknown_08622508:: @ 8622508
	.byte 0, 2

gUnknown_0862250A:: @ 862250A
	.byte 0, 1, 2, 0, 0, 0

gUnknown_08622510:: @ 8622510
	.incbin "graphics/pokenav/ui_matchcall.gbapal"

gUnknown_08622530:: @ 8622530
	.incbin "graphics/pokenav/ui_matchcall.4bpp.lz"

gUnknown_086225D4:: @ 86225D4
	.incbin "graphics/pokenav/ui_matchcall.bin.lz"

gUnknown_08622698:: @ 8622698
	.incbin "graphics/pokenav/arrow2.gbapal"
	
gUnknown_086226B8:: @ 86226B8
	.incbin "graphics/pokenav/arrow2.4bpp.lz"

gUnknown_086226E0:: @ 86226E0
	.incbin "graphics/pokenav/86226E0.gbapal"

gUnknown_08622700:: @ 8622700
	.incbin "graphics/pokenav/8622700.gbapal"

gUnknown_08622720:: @ 8622720
	.incbin "graphics/pokenav/pokeball_matchcall.gbapal"

gUnknown_08622760:: @ 8622760
	.incbin "graphics/pokenav/pokeball_matchcall.4bpp.lz"

gUnknown_0862278C:: @ 862278C
	.4byte 0x11FD
	.4byte 0x20206A

gUnknown_08622794:: @ 8622794
	.4byte 0x3077

gUnknown_08622798:: @ 8622798
	.4byte NULL
	.4byte sub_81CB510
	.4byte sub_81CB588
	.4byte sub_81CB600
	.4byte sub_81CB678
	.4byte sub_81CB6F0
	.4byte sub_81CB734
	.4byte sub_81CB75C
	.4byte sub_81CB7A0
	.4byte sub_81CB824
	.4byte sub_81CB888
	.4byte sub_81CB93C
	.4byte sub_81CBAD4
	.4byte sub_81CB9C8
	.4byte sub_81CBA68
	.4byte sub_81CBB74

gUnknown_086227D8:: @ 86227D8
	window_template 2, 0, 5, 11, 2, 2, 16

gUnknown_086227E0:: @ 86227E0
	window_template 2, 0, 9, 11, 8, 2, 0x26

gUnknown_086227E8:: @ 86227E8
	.4byte gUnknown_085EC017
	.4byte gUnknown_085EC01C
	.4byte gUnknown_085EC022

gUnknown_086227F4:: @ 86227F4
	.string "·{PAUSE 0x04}·{PAUSE 0x04}·{PAUSE 0x04}·{PAUSE 0x04}·\p"
	.string "$"
	.align 2

gUnknown_08622808:: @ 8622808
	window_template 1, 1, 12, 0x1C, 4, 1, 10

gUnknown_08622810:: @ 8622810
	obj_tiles gUnknown_086226B8, 0x40, 7

gUnknown_08622818:: @ 8622818
	obj_pal gUnknown_08622698, 12
	null_obj_pal

gUnknown_08622828:: @ 8622828
	.2byte 0x8000
	.2byte 0x0
	.2byte 0x400
	.2byte 0x0

gUnknown_08622830:: @ 8622830
	spr_template 7, 12, gUnknown_08622828, gDummySpriteAnimTable, NULL, gDummySpriteAffineAnimTable, sub_81CC34C

gUnknown_08622848:: @ 8622848
	.2byte 0x0
	.2byte 0xC000
	.2byte 0x400
	.2byte 0x0

gUnknown_08622850:: @ 8622850
	spr_template 8, 13, gUnknown_08622848, gDummySpriteAnimTable, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy

gUnknown_08622868:: @ 8622868
	.incbin "graphics/pokenav/8622868.gbapal"

gUnknown_08622888:: @ 8622888
	.incbin "graphics/pokenav/zoom_tiles.4bpp.lz"

gUnknown_08622A7C:: @ 8622A7C
	 .incbin "graphics/pokenav/city_maps/lavaridge_0.bin.lz"

gUnknown_08622AC0:: @ 8622AC0
	 .incbin "graphics/pokenav/city_maps/fallarbor_0.bin.lz"

gUnknown_08622B08:: @ 8622B08
	 .incbin "graphics/pokenav/city_maps/fortree_0.bin.lz"

gUnknown_08622B58:: @ 8622B58
	 .incbin "graphics/pokenav/city_maps/slateport_0.bin.lz"

gUnknown_08622BB8:: @ 8622BB8
	 .incbin "graphics/pokenav/city_maps/slateport_1.bin.lz"

gUnknown_08622C04:: @ 8622C04
	 .incbin "graphics/pokenav/city_maps/rustboro_0.bin.lz"

gUnknown_08622C58:: @ 8622C58
	 .incbin "graphics/pokenav/city_maps/rustboro_1.bin.lz"

gUnknown_08622CAC:: @ 8622CAC
	 .incbin "graphics/pokenav/city_maps/pacifidlog_0.bin.lz"

gUnknown_08622CEC:: @ 8622CEC
	 .incbin "graphics/pokenav/city_maps/mauville_0.bin.lz"

gUnknown_08622D44:: @ 8622D44
	 .incbin "graphics/pokenav/city_maps/mauville_1.bin.lz"

gUnknown_08622D98:: @ 8622D98
	 .incbin "graphics/pokenav/city_maps/oldale_0.bin.lz"

gUnknown_08622DC8:: @ 8622DC8
	 .incbin "graphics/pokenav/city_maps/lilycove_0.bin.lz"

gUnknown_08622E14:: @ 8622E14
	 .incbin "graphics/pokenav/city_maps/lilycove_1.bin.lz"

gUnknown_08622E6C:: @ 8622E6C
	 .incbin "graphics/pokenav/city_maps/littleroot_0.bin.lz"

gUnknown_08622E9C:: @ 8622E9C
	 .incbin "graphics/pokenav/city_maps/dewford_0.bin.lz"

gUnknown_08622ED4:: @ 8622ED4
	 .incbin "graphics/pokenav/city_maps/sootopolis_0.bin.lz"

gUnknown_08622F14:: @ 8622F14
	 .incbin "graphics/pokenav/city_maps/ever_grande_0.bin.lz"

gUnknown_08622F5C:: @ 8622F5C
	 .incbin "graphics/pokenav/city_maps/ever_grande_1.bin.lz"

gUnknown_08622FA0:: @ 8622FA0
	 .incbin "graphics/pokenav/city_maps/verdanturf_0.bin.lz"

gUnknown_08622FD8:: @ 8622FD8
	 .incbin "graphics/pokenav/city_maps/mossdeep_0.bin.lz"

gUnknown_08623020:: @ 8623020
	 .incbin "graphics/pokenav/city_maps/mossdeep_1.bin.lz"

gUnknown_0862307C:: @ 862307C
	 .incbin "graphics/pokenav/city_maps/petalburg_0.bin.lz"

gUnknown_086230D8:: @ 86230D8
	.4byte 0x11F5
	.4byte 0x206A
	.4byte 0x3402

gUnknown_086230E4:: @ 86230E4
	.4byte NULL
	.4byte sub_81CC848
	.4byte sub_81CC878
	.4byte sub_81CC8D8
	.4byte sub_81CC95C

gUnknown_086230F8:: @ 86230F8
	obj_tiles gHoennMapZoomIcons_Gfx, 0x800, 6

gUnknown_08623100:: @ 8623100
	obj_pal gHoennMapZoomIcons_Pal, 11
	null_obj_pal

gUnknown_08623110:: @ 8623110
	.byte 1
	.byte 17
	.byte 4
	.byte 12
	.byte 13
	.byte 1
	.2byte 0x4C

gUnknown_08623118:: @ 8623118
	.4byte 0, gUnknown_08622E6C 
	.4byte 1, gUnknown_08622D98
	.4byte 2, gUnknown_08622E9C
	.4byte 3, gUnknown_08622A7C
	.4byte 4, gUnknown_08622AC0
	.4byte 5, gUnknown_08622FA0
	.4byte 6, gUnknown_08622CAC
	.4byte 7, gUnknown_0862307C
	.4byte 8, gUnknown_08622B58
	.4byte 0x10008, gUnknown_08622BB8
	.4byte 9, gUnknown_08622D44
	.4byte 0x10009, gUnknown_08622CEC
	.4byte 0xA, gUnknown_08622C04
	.4byte 0x1000A, gUnknown_08622C58
	.4byte 0xB, gUnknown_08622B08
	.4byte 0xC, gUnknown_08622E14
	.4byte 0x1000C, gUnknown_08622DC8
	.4byte 0xD, gUnknown_08623020
	.4byte 0x1000D, gUnknown_08622FD8
	.4byte 0xE, gUnknown_08622ED4
	.4byte 0xF, gUnknown_08622F14
	.4byte 0x1000F, gUnknown_08622F5C

gUnknown_086231C8:: @ 86231C8
	.2byte 0x4000
	.2byte 0x4000
	.2byte 0x400
	.2byte 0x0

gUnknown_086231D0:: @ 86231D0
	spr_template 6, 11, gUnknown_086231C8, gDummySpriteAnimTable, NULL, gDummySpriteAffineAnimTable, sub_81CCEF4

gUnknown_086231E8:: @ 86231E8
	.incbin "graphics/pokenav/86231E8.gbapal"

gUnknown_08623208:: @ 8623208
	.incbin "graphics/pokenav/8623208.gbapal"

gUnknown_08623228:: @ 8623228
	.incbin "graphics/pokenav/8623228.4bpp.lz"

gUnknown_0862323C:: @ 862323C
	.incbin "graphics/pokenav/862323C.bin.lz"

gUnknown_08623338:: @ 8623338
	.incbin "graphics/pokenav/8623338.gbapal"

gUnknown_08623358:: @ 8623358
	.4byte 0x11F5
	.4byte 0x21DE
	.4byte 0x31EB

gUnknown_08623364:: @ 8623364
	window_template 1, 13, 1, 13, 4, 15, 2

gUnknown_0862336C:: @ 862336C
	window_template 1, 1, 6, 7, 2, 15, 0x36

gUnknown_08623374:: @ 8623374
	window_template 1, 1, 0x1C, 5, 2, 15, 0x44

gUnknown_0862337C:: @ 862337C
	window_template 1, 13, 0x1C, 3, 2, 15, 0x44

gUnknown_08623384:: @ 8623384
	.4byte NULL
	.4byte sub_81CE37C
	.4byte sub_81CE2D0
	.4byte sub_81CE4D8
	.4byte sub_81CE5E4
	.4byte sub_81CE6BC
	.4byte sub_81CE700

gUnknown_086233A0:: @ 86233A0
	.4byte 0x16, 0x17, 0x18, 0x21, 0x2F

gUnknown_086233B4:: @ 86233B4
	.4byte sub_81CF134
	.4byte sub_81CF1C4
	.4byte sub_81CF1D8
	.4byte sub_81CF278

gUnknown_086233C4:: @ 86233C4
	.incbin "graphics/pokenav/condition_search2.gbapal"

gUnknown_086233E4:: @ 86233E4
	.incbin "graphics/pokenav/condition_search2.4bpp.lz"

gUnknown_086234AC:: @ 86234AC
	.incbin "graphics/pokenav/condition_search2.bin.lz"

gUnknown_08623570:: @ 8623570
	.incbin "graphics/pokenav/8623570.gbapal"

gUnknown_08623590:: @ 8623590
	.4byte 0x2065

gUnknown_08623594:: @ 8623594
	.4byte 0x307A

gUnknown_08623598:: @ 8623598
	.4byte NULL
	.4byte sub_81CF578
	.4byte sub_81CF5F0
	.4byte sub_81CF668
	.4byte sub_81CF6E0
	.4byte sub_81CF758
	.4byte sub_81CF798

gUnknown_086235B4:: @ 86235B4
	window_template 1, 1, 6, 7, 2, 1, 20

gUnknown_086235BC:: @ 86235BC
	.string "{COLOR_HIGHLIGHT_SHADOW}{LIGHT_RED}{WHITE}{GREEN}♂{COLOR_HIGHLIGHT_SHADOW}{DARK_GREY}{WHITE}{LIGHT_GREY}$"
	.align 2

gUnknown_086235C8:: @ 86235C8
	.string "{COLOR_HIGHLIGHT_SHADOW}{LIGHT_GREEN}{WHITE}{BLUE}♀{COLOR_HIGHLIGHT_SHADOW}{DARK_GREY}{WHITE}{LIGHT_GREY}$"
	.align 2

gUnknown_086235D4:: @ 86235D4
	.string "{UNK_SPACER}$"
	.align 2

gUnknown_086235D8:: @ 86235D8
	.4byte sub_81CFB8C
	.4byte sub_81CFC2C
	.4byte sub_81CFC40

gUnknown_086235E4:: @ 86235E4
	.incbin "graphics/pokenav/ui_ribbons.gbapal"

gUnknown_08623604:: @ 8623604
	.incbin "graphics/pokenav/ui_ribbons.4bpp.lz"

gUnknown_086236CC:: @ 86236CC
	.incbin "graphics/pokenav/ui_ribbons.bin.lz"

gUnknown_08623790:: @ 8623790
	.incbin "graphics/pokenav/8623790.gbapal"

gUnknown_086237B0:: @ 86237B0
	.4byte 0x2065

gUnknown_086237B4:: @ 86237B4
	.4byte 0x307A

gUnknown_086237B8:: @ 86237B8
	.4byte NULL
	.4byte sub_81CFFFC
	.4byte sub_81D0074
	.4byte sub_81D00EC
	.4byte sub_81D0164
	.4byte sub_81D01DC
	.4byte sub_81D021C

gUnknown_086237D4:: @ 86237D4
	window_template 1, 1, 6, 7, 2, 1, 20

gUnknown_086237DC:: @ 86237DC
	.string "{COLOR_HIGHLIGHT_SHADOW}{LIGHT_RED}{WHITE}{GREEN}♂{COLOR_HIGHLIGHT_SHADOW}{DARK_GREY}{WHITE}{LIGHT_GREY}$"
	.align 2

gUnknown_086237E8:: @ 86237E8
	.string "{COLOR_HIGHLIGHT_SHADOW}{LIGHT_GREEN}{WHITE}{BLUE}♀{COLOR_HIGHLIGHT_SHADOW}{DARK_GREY}{WHITE}{LIGHT_GREY}$"
	.align 2

gUnknown_086237F4:: @ 86237F4
	.string "{UNK_SPACER}$"
	.align 2

gUnknown_086237F8:: @ 86237F8
	.byte 1, 1, 0, 0
	.byte 3, 4, 1, 0
	.byte 3, 4, 5, 0
	.byte 3, 4, 9, 0
	.byte 3, 4, 13, 0
	.byte 3, 4, 17, 0
	.byte 1, 1, 21, 0
	.byte 1, 1, 22, 0
	.byte 1, 1, 23, 0
	.byte 1, 1, 24, 0
	.byte 1, 1, 25, 1
	.byte 1, 1, 26, 1
	.byte 1, 1, 27, 1
	.byte 1, 1, 28, 1
	.byte 1, 1, 29, 1
	.byte 1, 1, 30, 1
	.byte 1, 1, 31, 1

@ 862383C
	.include "data/text/ribbon_descriptions.inc"

@ 8623A74
	.include "data/text/gift_ribbon_descriptions.inc"

gUnknown_08623FF8:: @ 8623FF8
	 .incbin "graphics/pokenav/ribbons_icon1.gbapal"

gUnknown_08624018:: @ 8624018
	 .incbin "graphics/pokenav/ribbons_icon2.gbapal"

gUnknown_08624038:: @ 8624038
	 .incbin "graphics/pokenav/ribbons_icon3.gbapal"

gUnknown_08624058:: @ 8624058
	 .incbin "graphics/pokenav/ribbons_icon4.gbapal"

gUnknown_08624078:: @ 8624078
	 .incbin "graphics/pokenav/ribbons_icon5.gbapal"

gUnknown_08624098:: @ 8624098
	 .incbin "graphics/pokenav/8624098.gbapal"

gUnknown_086240B8:: @ 86240B8
	 .incbin "graphics/pokenav/ribbons_icon.4bpp.lz"

gUnknown_08624280:: @ 8624280
	 .incbin "graphics/pokenav/ribbons_icon_big.4bpp.lz"

gUnknown_08624B98:: @ 8624B98
	.4byte 0x107D
	.4byte 0x2066

gUnknown_08624BA0:: @ 8624BA0
	.4byte NULL
	.4byte sub_81D0C84
	.4byte sub_81D0D2C
	.4byte sub_81D0D8C
	.4byte sub_81D0E00
	.4byte sub_81D0C54

gUnknown_08624BB8:: @ 8624BB8
	window_template 2, 12, 13, 16, 4, 1, 20

gUnknown_08624BC0:: @ 8624BC0
	.byte 4, 2, 3, 0

gUnknown_08624BC4:: @ 8624BC4
	window_template 2, 14, 1, 13, 2, 10, 0x54

gUnknown_08624BCC:: @ 8624BCC
	.string "{COLOR_HIGHLIGHT_SHADOW}{LIGHT_RED}{WHITE}{GREEN}♂{COLOR_HIGHLIGHT_SHADOW}{DARK_GREY}{WHITE}{LIGHT_GREY}$"
	.align 2

gUnknown_08624BD8:: @ 8624BD8
	.string "{COLOR_HIGHLIGHT_SHADOW}{LIGHT_GREEN}{WHITE}{BLUE}♀{COLOR_HIGHLIGHT_SHADOW}{DARK_GREY}{WHITE}{LIGHT_GREY}$"
	.align 2

gUnknown_08624BE4:: @ 8624BE4
	.string "{UNK_SPACER}$"
	.align 2

gUnknown_08624BE8:: @ 8624BE8
	window_template 2, 1, 5, 7, 2, 1, 0x6E
	.4byte NULL
	.4byte NULL

gUnknown_08624BF8:: @ 8624BF8
	.2byte 0, 0, 1, 0
	.2byte 2, 0, 3, 0
	.2byte 4, 0, 1, 1
	.2byte 2, 1, 3, 1
	.2byte 4, 1, 1, 2
	.2byte 2, 2, 3, 2
	.2byte 4, 2, 1, 3
	.2byte 2, 3, 3, 3
	.2byte 4, 3, 1, 4
	.2byte 2, 4, 3, 4
	.2byte 4, 4, 5, 0
	.2byte 6, 0, 7, 1
	.2byte 8, 2, 9, 1
	.2byte 9, 3, 9, 4
	.2byte 10, 3, 10, 4
	.2byte 11, 0, 11, 1

gUnknown_08624C78:: @ 8624C78
	obj_tiles gUnknown_08624280, 0x1800, 9

gUnknown_08624C80:: @ 8624C80
	obj_pal gUnknown_08623FF8, 15
	obj_pal gUnknown_08624018, 16
	obj_pal gUnknown_08624038, 17
	obj_pal gUnknown_08624058, 18
	obj_pal gUnknown_08624078, 19
	null_obj_pal

gUnknown_08624CB0:: @ 8624CB0
	.2byte 0x100
	.2byte 0x8000
	.2byte 0x400
	.2byte 0x0

gUnknown_08624CB8:: @ 8624CB8
	.2byte 0x80
	.2byte 0x80
	.2byte 0
	.2byte 0
	.2byte 0x7FFF
	.2byte 0
	.2byte 0
	.2byte 0
	
gUnknown_08624CC8:: @ 8624CC8
	.2byte 0x80
	.2byte 0x80
	.2byte 0
	.2byte 0
	.2byte 0x20
	.2byte 0x20
	.2byte 0x400
	.2byte 0
	.2byte 0x7FFF
	.2byte 0
	.2byte 0
	.2byte 0
	
gUnknown_08624CE0:: @ 8624CE0
	.2byte 0x100
	.2byte 0x100
	.2byte 0
	.2byte 0
	.2byte 0xFFE0
	.2byte 0xFFE0
	.2byte 0x400
	.2byte 0
	.2byte 0x7FFF
	.2byte 0
	.2byte 0
	.2byte 0
	
gUnknown_08624CF8:: @ 8624CF8
	.4byte gUnknown_08624CB8
	.4byte gUnknown_08624CC8
	.4byte gUnknown_08624CE0

gUnknown_08624D04:: @ 8624D04
	spr_template 9, 15, gUnknown_08624CB0, gDummySpriteAnimTable, NULL, gUnknown_08624CF8, SpriteCallbackDummy

	.section .rodata.after.match.call

gUnknown_086253E8:: @ 86253E8
	.4byte 0x8010100
	.4byte 0x80F02
	.4byte 0x8011500
	.4byte 0x180F12
	.4byte 0xB010100
	.4byte 0x180F08

gUnknown_08625400:: @ 8625400
	.byte 1, 2, 3

gUnknown_08625403:: @ 8625403
	.byte 0xFF

gUnknown_08625404:: @ 8625404
	.byte 0x40, 0, 0, 4, 1, 0, 0x60, 0xA6, 1, 0, 0, 0

gUnknown_08625410:: @ 8625410
	.byte 4, 5, 6, 7, 8, 9, 9, 0xA, 0xA, 0xB, 0xB, 0xC, 0xC, 0xD, 0xD, 0xD, 0xD, 0xE, 0xE, 0xE, 0xE, 0xF, 0xF, 0xF, 0xF, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x17, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x23

gUnknown_08625510:: @ 8625510
	.4byte 0x10010101
	.4byte 0xA0F0C
	.4byte 0x10010101
	.4byte 0xCA0F0C
	.4byte 0xA011301
	.4byte 0x18A0F0C
	.4byte 0x160F0401
	.4byte 0x2020F04
	.4byte 0x5081600
	.4byte 0x25A0F04
	.4byte 0xFF
	.4byte NULL

gUnknown_08625540:: @ 8625540
	.4byte 0x5081600
	.4byte 0x25A0F04

gUnknown_08625548:: @ 8625548
	.4byte NULL
	.4byte sub_81D2BD0
	.4byte NULL
	.2byte 0
	.2byte 0
	.byte 2
	.byte 0
	.byte 8
	.byte 0
	.4byte 0x1003121
	
gUnknown_08625560:: @ 8625560
	.incbin "graphics/pokenav/pokeball.4bpp"

gUnknown_08625660:: @ 8625660
	.incbin "graphics/pokenav/8625660.4bpp"
	
gUnknown_08625680:: @ 8625680
	.incbin "graphics/pokenav/sparkle.gbapal"
	
gUnknown_086256A0:: @ 86255A0
	.incbin "graphics/pokenav/sparkle.4bpp"
	
gUnknown_08625A20:: @ 8625A20
	.2byte 0
	.2byte 0xC000
	.2byte 0x400
	.2byte 0
	
gUnknown_08625A28:: @ 8625A28
	.2byte 0
	.2byte 0x4000
	.2byte 0x800
	.2byte 0
	
gUnknown_08625A30:: @ 8625A30
	.2byte 0
	.2byte 5
	.2byte 0xFFFF
	.2byte 0
	
gUnknown_08625A38:: @ 8625A38
	.2byte 4
	.2byte 5
	.2byte 0xFFFF
	.2byte 0
	
gUnknown_08625A40:: @ 8625A40
	.4byte gUnknown_08625A30
	.4byte gUnknown_08625A38

gUnknown_08625A48:: @ 8625A48
	.4byte NULL
	.4byte 0x640800

gUnknown_08625A50:: @ 8625A50
	spr_template 0x64, 0x64, gUnknown_08625A20, gDummySpriteAnimTable, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy

gUnknown_08625A68:: @ 8625A68
	.4byte NULL
	.4byte 0x64

gUnknown_08625A70:: @ 8625A70
	.4byte gUnknown_08625560
	.byte 0, 1, 0x65, 0
	.4byte gUnknown_08625660
	.2byte 0x20, 0x67
	.4byte gPokenavConditionCancel_Gfx
	.byte 0, 1, 0x66, 0
	.4byte NULL, NULL

gUnknown_08625A90:: @ 8625A90
	.4byte gPokenavConditionCancel_Pal + 0x0
	.byte 0x65, 0, 0, 0
	.4byte gPokenavConditionCancel_Pal + 0x20
	.byte 0x66, 0, 0, 0
	.4byte NULL, NULL

gUnknown_08625AA8:: @ 8625AA8
	spr_template 0x65, 0x65, gUnknown_08625A28, gUnknown_08625A40, NULL, gDummySpriteAffineAnimTable, SpriteCallbackDummy

gUnknown_08625AC0:: @ 8625AC0
	.4byte gUnknown_086256A0
	.byte 0x80, 3, 0x68, 0

gUnknown_08625AC8:: @ 8625AC8
	.4byte gUnknown_08625680
	.byte 0x68, 0, 0, 0
	
gUnknown_08625AD0:: @ 8625AD0
	.2byte 0
	.2byte 0x4000
	.2byte 0
	.2byte 0
	
gUnknown_08625AD8:: @ 8625AD8
	.2byte 0
	.2byte 5
	.2byte 4
	.2byte 5
	
gUnknown_08625AE0:: @ 8625AE0
	.2byte 8
	.2byte 5
	.2byte 12
	.2byte 5
	
gUnknown_08625AE8:: @ 8625AE8
	.2byte 16
	.2byte 5
	.2byte 20
	.2byte 5
	
gUnknown_08625AF0:: @ 8625AF0
	.2byte 24
	.2byte 5
	.2byte 0xFFFF
	.2byte 0
	
gUnknown_08625AF8:: @ 8625AF8
	.4byte gUnknown_08625AD8
	.4byte gUnknown_08625AE0
	
gUnknown_08625B00:: @ 8625B00
	.4byte gUnknown_08625AE8
	.4byte gUnknown_08625AF0
	
gUnknown_08625B08:: @ 8625B08
	.4byte gUnknown_08625AF8
	.4byte gUnknown_08625B00
	.4byte gUnknown_08625B08

gUnknown_08625B14:: @ 8625B14
	spr_template 0x68, 0x68, gUnknown_08625AD0, gUnknown_08625AF8, NULL gDummySpriteAffineAnimTable, sub_81D3564

gUnknown_08625B2C:: @ 8625B2C
	.2byte 0, 0xFFDD
	.2byte 20, 0xFFE4
	.2byte 33, 0xFFF6
	.2byte 33, 10
	.2byte 20, 28
	.2byte 0, 35
	.2byte 0xFFEC, 28
	.2byte 0xFFDF, 10
	.2byte 0xFFDF, 0xFFF6
	.2byte 0xFFEC, 0xFFE4

gUnknown_08625B54:: @ 8625B54
	.4byte gUnknown_085EEA46
	.4byte gUnknown_085EEA4E
	.4byte gUnknown_085EEA55
	.4byte gUnknown_085EEA63
	.4byte gUnknown_085EEA6B
	.4byte gUnknown_085EEA5D

gUnknown_08625B6C:: @ 8625B6C
@ apparently e-reader trainer data? idk
.byte 0x6f, 0x57, 0x54, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x0c, 0x01, 0x00, 0x00, 0x00, 0x2e, 0x14, 0x0c, 0x0e, 0x23, 0x10, 0x47, 0x0a, 0x1f, 0x06, 0x24, 0x0e, 0x48, 0x0a, 0x0f, 0x06
.byte 0x22, 0x27, 0x2c, 0x16, 0x07, 0x06, 0x01, 0x0c, 0x47, 0x0a, 0x06, 0x06, 0x24, 0x0e, 0x00, 0x1e, 0x19, 0x12, 0x05, 0x0c, 0x25, 0x16, 0x25, 0x10, 0x0d, 0x1c, 0x2a, 0x1c, 0x06, 0x0a, 0x06, 0x0c
.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
.byte 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
.byte 0xff, 0xff, 0xff, 0x00, 0x70, 0x01, 0xdb, 0x00, 0xbc, 0x00, 0xf7, 0x00, 0xdc, 0x00, 0x19, 0x01, 0x00, 0x00, 0x37, 0xff, 0x64, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x10, 0xa5, 0x94, 0x52, 0x8a
.byte 0x80, 0x00, 0x00, 0x00, 0x6f, 0x79, 0x69, 0xae, 0x71, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x26, 0x01, 0xb3, 0x00, 0x3e, 0x01, 0xbc, 0x00, 0xf7, 0x00, 0xca, 0x00, 0x00, 0x00, 0x00, 0xff
.byte 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x10, 0xa5, 0x94, 0x52, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x95, 0x58, 0x59, 0x52, 0x79, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7d, 0x01, 0xb7, 0x00
.byte 0xf6, 0x00, 0x39, 0x00, 0x59, 0x00, 0x85, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x9b, 0xff, 0x00, 0x00, 0x00, 0x10, 0xa5, 0x94, 0x52, 0x0a, 0x2f, 0x00, 0x00, 0x00, 0x8d, 0xae, 0x77, 0x7e
.byte 0x5d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6a, 0x79, 0x6b, 0x64, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x1b, 0x01, 0x00, 0x00, 0x00, 0x54, 0x27, 0x2b, 0x0e, 0xff, 0xff, 0x3b, 0x0a
.byte 0x20, 0x06, 0x00, 0x0c, 0x13, 0x24, 0x2b, 0x0e, 0xff, 0xff, 0x3b, 0x0a, 0x05, 0x12, 0x00, 0x0c, 0x6b, 0x26, 0x2b, 0x0e, 0xff, 0xff, 0x3b, 0x0a, 0x0e, 0x12, 0x00, 0x0c, 0x2c, 0x24, 0x2b, 0x0e
.byte 0xff, 0xff, 0x3b, 0x0a, 0x17, 0x12, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00
.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
.byte 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x59, 0x01, 0xb7, 0x00, 0xca, 0x00, 0xb9, 0x00, 0x09, 0x00, 0x4a, 0x00, 0x00, 0x00, 0x37, 0x00, 0x64, 0x00, 0xff, 0x64
.byte 0x00, 0x00, 0x00, 0x10, 0xa5, 0x94, 0x52, 0x0a, 0x8c, 0x00, 0x00, 0x00, 0x69, 0x58, 0x60, 0x5d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x31, 0x01, 0xb3, 0x00, 0x07, 0x01, 0x4c, 0x01
.byte 0x62, 0x00, 0x68, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xa5, 0x94, 0x52, 0x0a, 0x80, 0x00, 0x00, 0x00, 0x55, 0x55, 0x5d, 0x96, 0x72, 0xff, 0xff, 0xff
.byte 0xff, 0xff, 0xff, 0xff, 0x44, 0x01, 0x86, 0x00, 0x39, 0x00, 0x59, 0x00, 0x85, 0x00, 0x9c, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x10, 0xa5, 0x94, 0x52, 0x0a
.byte 0x00, 0x00, 0x00, 0x00, 0x65, 0x6f, 0x8e, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x72, 0x52, 0x5a, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x27, 0x01, 0x00, 0x00, 0x00
.byte 0x4a, 0x04, 0x0e, 0x02, 0x35, 0x16, 0x10, 0x10, 0xda, 0x26, 0x3e, 0x10, 0x4a, 0x04, 0x0e, 0x02, 0x47, 0x0a, 0xd9, 0x26, 0x21, 0x16, 0x3e, 0x10, 0x14, 0x1e, 0x07, 0x1e, 0x30, 0x06, 0x23, 0x16
.byte 0x24, 0x0e, 0x06, 0x0c, 0x18, 0x14, 0x2f, 0x14, 0x1a, 0x08, 0x27, 0x1c, 0x00, 0x0c, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff
.byte 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x3c, 0x01, 0x8d, 0x00, 0x2f, 0x00, 0x22, 0x00, 0xf7, 0x00, 0xe7, 0x00
.byte 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xa5, 0x94, 0x52, 0x0a, 0x03, 0x00, 0x00, 0x00, 0x54, 0x68, 0x5a, 0x7b, 0x7b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
.byte 0x6b, 0x01, 0xc8, 0x00, 0xca, 0x00, 0x40, 0x01, 0x5c, 0x00, 0x49, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x10, 0xa5, 0x94, 0x52, 0x8a, 0x06, 0x00, 0x00, 0x00
.byte 0x7b, 0x8f, 0x78, 0x51, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x24, 0x01, 0xb3, 0x00, 0x3e, 0x01, 0x4c, 0x01, 0xd5, 0x00, 0x5e, 0x00, 0x00, 0x00, 0x64, 0xc8, 0x00, 0x00, 0xc8, 0x00
.byte 0x00, 0x00, 0x00, 0x10, 0xa5, 0x94, 0x52, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x51, 0x8a, 0x6a, 0x7e, 0x64, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9c, 0x54, 0xae, 0x79, 0xff, 0xff, 0xff, 0xff
.byte 0x00, 0x00, 0x00, 0x20, 0x01, 0x00, 0x00, 0x00, 0x46, 0x0a, 0x02, 0x06, 0x20, 0x06, 0x0a, 0x0a, 0x23, 0x10, 0x00, 0x0c, 0x28, 0x0c, 0x14, 0x18, 0x32, 0x14, 0x02, 0x16, 0x05, 0x10, 0xff, 0xff
.byte 0x0c, 0x1e, 0x0a, 0x0a, 0x34, 0x12, 0x11, 0x1e, 0x1a, 0x08, 0x05, 0x0c, 0x1e, 0x0a, 0x02, 0x06, 0x20, 0x06, 0x22, 0x0a, 0x15, 0x10, 0x01, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
.byte 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
.byte 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x63, 0x01, 0xb3, 0x00
.byte 0xf2, 0x00, 0x35, 0x00, 0x09, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0xff, 0x9b, 0x00, 0x00, 0x00, 0x10, 0xa5, 0x94, 0x52, 0x8a, 0x00, 0x00, 0x00, 0x00, 0x58, 0x61, 0xae, 0x64
.byte 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x4b, 0x01, 0xc6, 0x00, 0x39, 0x00, 0xf2, 0x00, 0x26, 0x00, 0x59, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x10
.byte 0xa5, 0x94, 0x52, 0x0a, 0x96, 0x00, 0x00, 0x00, 0x5b, 0x72, 0x6a, 0x91, 0xae, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7a, 0x01, 0x8d, 0x00, 0x5e, 0x00, 0xf7, 0x00, 0x55, 0x00, 0x05, 0x01
.byte 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x10, 0xa5, 0x94, 0x52, 0x0a, 0x96, 0x00, 0x00, 0x00, 0x8d, 0x85, 0x9e, 0xa0, 0x60, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff

gUnknown_0862608C:: @ 862608C
	.2byte 21, 16
	.2byte 25, 16
	.2byte 16, 17
	.2byte 20, 20
	
gUnknown_0862609C:: @ 862609C
	.incbin "data/unknown_jp_62609C.bin"
	
gUnknown_08626814:: @ 8626814
	.incbin "data/pokenav/unk_struct_1.bin"

gUnknown_086276FC:: @ 86276FC
	.incbin "data/pokenav/unk_struct_2.bin"

gUnknown_086285E4:: @ 86285E4
	.incbin "data/pokenav/unk_struct_3.bin"

gUnknown_086294CC:: @ 86294CC
	.incbin "data/pokenav/unk_struct_4.bin"

gUnknown_0862A3B4:: @ 862A3B4
	.byte 0x03, 0x06, 0x00, 0x00, 0x0B, 0x06, 0x00, 0x00, 0x0D, 0x06, 0x00, 0x00, 0x0F, 0x01, 0x00, 0x00, 0x2B, 0x04, 0x00, 0x00, 0x2D, 0x01, 0x00, 0x00, 0x24, 0x09, 0x00, 0x00, 0x29, 0x04, 0x00, 0x00, 0x05, 0x05, 0x00, 0x00, 0x18, 0x04, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x2E, 0x09, 0x00, 0x00, 0x11, 0x0C, 0x00, 0x00, 0x10, 0x0B, 0x00, 0x00, 0x1E, 0x0D, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00, 0x17, 0x03, 0x00, 0x00, 0x0C, 0x04, 0x00, 0x00, 0x38, 0x04, 0x00, 0x00, 0x1C, 0x03, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x19, 0x0B, 0x00, 0x00, 0x09, 0x07, 0x00, 0x00, 0x31, 0x07, 0x00, 0x00, 0x35, 0x07, 0x00, 0x00, 0x36, 0x01, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x2A, 0x03, 0x00, 0x00, 0x16, 0x0D, 0x00, 0x00, 0x0E, 0x03, 0x00, 0x00, 0x15, 0x01, 0x00, 0x00, 0x14, 0x01, 0x00, 0x00, 0x2C, 0x01, 0x00, 0x00, 0x1B, 0x02, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x07, 0x03, 0x00, 0x00, 0x34, 0x05, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x37, 0x02, 0x00, 0x00, 0x1D, 0x04, 0x00, 0x00, 0x22, 0x09, 0x00, 0x00, 0x1F, 0x01, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x0A, 0x04, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x06, 0x05, 0x00, 0x00, 0x27, 0x0B, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x12, 0x02, 0x00, 0x00, 0x39, 0x08, 0x00, 0x00, 0x02, 0x0B, 0x00, 0x00, 0x20, 0x01, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00

gUnknown_0862A48C:: @ 862A48C
	.2byte 0x44, 0x22, 0x14, 0x18, 0x51, 0x3
	
gUnknown_0862A498:: @ 862A498
	.2byte 0xB, 0x22, 0x14, 0x18, 0x51, 3
	
gUnknown_0862A4A4:: @ 862A4A4
	.2byte 0x19, 0x22, 0x14, 0x18, 0x51, 3

gUnknown_0862A4B0:: @ 862A4B0
	.2byte 0x23, 0x22, 0x14, 0x18, 0x51, 0x3

gUnknown_0862A4BC:: @ 862A4BC
	.2byte 0x24, 0x22, 0x14, 0x18, 0x51, 0x3

gUnknown_0862A4C8:: @ 862A4C8
	.2byte 0x125, 0x22, 0x14, 0x18, 0x51, 0x3

gUnknown_0862A4D4:: @ 862A4D4
	.2byte 0x144, 0x22, 0x14, 0x18, 0x51, 0x3

gUnknown_0862A4E0:: @ 862A4E0  
	.2byte 0x126, 0x22, 0x14, 0x18, 0x51, 0x3

gUnknown_0862A4EC:: @ 862A4EC
	.2byte 0x12B, 0x22, 0x14, 0x18, 0x51, 0x3

gUnknown_0862A4F8:: @ 862A4F8
	.2byte 0x13A, 0x22, 0x14, 0x18, 0x51, 0x3

gUnknown_0862A504:: @ 862A504
	.2byte 0x44, 0x22, 0x14, 0x18, 0x51, 0x3

gUnknown_0862A510:: @ 862A510
	.2byte 0xB, 0x22, 0x14, 0x18, 0x51, 0x3

gUnknown_0862A51C:: @ 862A51C	 
	.2byte 0x19, 0x22, 0x14, 0x18, 0x51, 0x3

gUnknown_0862A528:: @ 862A528
	.2byte 0x23, 0x22, 0x14, 0x18, 0x51, 0x3

gUnknown_0862A534:: @ 862A534
	.2byte 0x24, 0x22, 0x14, 0x18, 0x51, 0x3

gUnknown_0862A540:: @ 862A540
	.2byte 0x13F, 0x22, 0x14, 0x18, 0x51, 0x3

gUnknown_0862A54C:: @ 862A54C
	.2byte 0x149, 0x22, 0x14, 0x18, 0x51, 0x3

gUnknown_0862A558:: @ 862A558
	.2byte 0x150, 0x22, 0x14, 0x18, 0x51, 0x3

gUnknown_0862A564:: @ 862A564
	.2byte 0x133, 0x22, 0x14, 0x18, 0x51, 0x3

gUnknown_0862A570:: @ 862A570
	.2byte 0x14D, 0x22, 0x14, 0x18, 0x51, 0x3

gUnknown_0862A57C:: @ 862A57C	
	.4byte gUnknown_0862A48C
	.4byte gUnknown_0862A498
	.4byte gUnknown_0862A4A4
	.4byte gUnknown_0862A4B0
	.4byte gUnknown_0862A4BC
	.4byte gUnknown_0862A4C8
	.4byte gUnknown_0862A4D4
	.4byte gUnknown_0862A4E0
	.4byte gUnknown_0862A4EC
	.4byte gUnknown_0862A4F8

gUnknown_0862A5A4:: @ 862A5A4
	.4byte gUnknown_0862A504
	.4byte gUnknown_0862A510
	.4byte gUnknown_0862A51C
	.4byte gUnknown_0862A528
	.4byte gUnknown_0862A534
	.4byte gUnknown_0862A540
	.4byte gUnknown_0862A54C
	.4byte gUnknown_0862A558
	.4byte gUnknown_0862A564
	.4byte gUnknown_0862A570
	
gUnknown_0862A5CC:: @ 862A5CC
	.4byte gUnknown_0862A57C
	.4byte gUnknown_0862A5A4

gUnknown_0862A5D4:: @ 862A5D4
	.incbin "graphics/pokenav/862A5D4.gbapal"

gUnknown_0862A5F4:: @ 862A5F4
	.byte 0, 2, 3, 0

gUnknown_0862A5F8:: @ 862A5F8
	.4byte gUnknown_08626814
	.4byte gUnknown_086276FC
	.4byte gUnknown_086285E4
	.4byte gUnknown_086294CC
	.4byte gUnknown_085EF8B6
	.4byte gUnknown_085EF8B9
	.4byte gUnknown_085EF8BC
	.4byte gUnknown_085EF8BF

gUnknown_0862A618:: @ 862A618
	.4byte sub_81D581C
	.4byte sub_81D58D8
	.4byte sub_81D5924
	.4byte sub_81D59D0
	.4byte sub_81D5A70
	.4byte sub_81D5AB4
	.4byte sub_81D5AD0
	.4byte sub_81D5B2C
	.4byte sub_81D5BBC
	.4byte sub_81D5C00
	.4byte sub_81D5C5C
	.4byte sub_81D62B4
	.4byte sub_81D64AC
	.4byte sub_81D64DC
	.4byte sub_81D64FC
	.4byte sub_81D6518
	.4byte sub_81D6568
	.4byte sub_81D65A0

gUnknown_0862A660:: @ 862A660
	.4byte gUnknown_085EB32D
	.4byte gUnknown_085EB33E
	.4byte gUnknown_085EB350
	.4byte gUnknown_085EB361

gUnknown_0862A670:: @ 862A670
	.byte 0, 0x64
	.4byte NULL
	.2byte 0, 0x103, 17, 1, 0, 0, 0, 0, 0

gUnknown_0862A688:: @ 862A688
	.2byte 0x3E, 0, 0x3F, 0, 0x40, 0, 0x41, 0

gUnknown_0862A698:: @ 862A698
	.byte 0, 1, 2, 3, 4, 5, 0, 0
