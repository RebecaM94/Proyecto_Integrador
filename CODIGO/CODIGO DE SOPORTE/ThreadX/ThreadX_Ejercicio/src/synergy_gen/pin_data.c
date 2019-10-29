/* generated pin source file - do not edit */
#include "r_ioport.h"
#if defined(__ICCARM__)
#pragma diag_suppress=Pa089
#endif
const ioport_pin_cfg_t g_bsp_pin_cfg_data[] = {
	{
		.pin = IOPORT_PORT_01_PIN_08,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_DEBUG),
	},
	{
		.pin = IOPORT_PORT_01_PIN_09,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_DEBUG),
	},
	{
		.pin = IOPORT_PORT_01_PIN_10,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_DEBUG),
	},
	{
		.pin = IOPORT_PORT_03_PIN_00,
		.pin_cfg = (IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_DEBUG),
	},
};
const ioport_cfg_t g_bsp_pin_cfg = {
	.number_of_pins = sizeof(g_bsp_pin_cfg_data)/sizeof(ioport_pin_cfg_t),
	.p_pin_cfg_data = &g_bsp_pin_cfg_data[0],
};
#if defined(__ICCARM__)
#pragma diag_default=Pa089
#endif
