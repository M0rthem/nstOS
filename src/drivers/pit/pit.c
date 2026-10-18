#include <stdint.h>
#include "asm/exp/asm.h"

#define PIT_CHANNEL_ZERO_PORT 0x40
#define PIT_COMMAND_PORT 0x43

typedef enum PIT_channel {
	PIT_CHANNEL_ZERO_E,
	PIT_CHANNEL_ONE_E,
	PIT_CHANNEL_THREE_E,
	PIT_READ_BACK_COMMAND_E
} PIT_channel_t;

typedef enum PIT_access_mode {
	PIT_LATCH_E,
	PIT_ACCESS_LOBYTE_E,
	PIT_ACCESS_HIBITE_E,
	PIT_ACCESS_LOBYTE_HYBYTE_E	
} PIT_access_mode_t;

typedef enum PIT_operating_mode {
	PIT_MODE_0_E,
	PIT_MODE_1_E,
	PIT_MODE_2_E,
	PIT_MODE_3_E,
	PIT_MODE_4_E,
	PIT_MODE_5_E,
	PIT_MODE_6_E,
	PIT_MODE_7_E,
	PIT_MODE_LIKE_2_E,
	PIT_MODE_LIKE_3_E
} PIT_operating_mode_t;

typedef enum PIT_bcd_binary_mode {
	PIT_BINARY_MODE_E,
	PIT_BCD_MODE_E
} PIT_bcd_binary_mode_t;

void setupPIT() {
	uint8_t message = 0;

	message = (uint8_t)PIT_BINARY_MODE_E;
	message |= (uint8_t)((unsigned int)PIT_MODE_3_E << 1);
	message |= (uint8_t)((unsigned int)PIT_ACCESS_LOBYTE_HYBYTE_E << 4);
	message |= (uint8_t)((unsigned int)PIT_CHANNEL_ZERO_E << 6);

	ASM_outb(PIT_COMMAND_PORT, message);	
	ASM_outb(PIT_CHANNEL_ZERO_PORT, 0);
	ASM_outb(PIT_CHANNEL_ZERO_PORT, 0);	
}
