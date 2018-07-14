#include "constants/map_types.h"
#include "constants/maps.h"
#include "constants/weather.h"
#include "constants/region_map_sections.h"
#include "constants/songs.h"
#include "constants/weather.h"
	.include "asm/macros.inc"
	.include "constants/constants.inc"

	.section .rodata

	.include "data/layouts.inc"
	.include "data/layouts_table.inc"
	.include "data/maps/headers.inc"
	.include "data/maps/groups.inc"
	.include "data/maps/connections.inc"
