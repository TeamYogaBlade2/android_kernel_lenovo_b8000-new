/*
 * ALS/PS board configuration for the Lenovo YOGA Tablet 10 (blade10).
 *
 * Every value below was read out of the shipped kernel image
 * (kernel_blade10_row_wifi-kk.elf) rather than copied from another project:
 *
 *   get_cust_alsps_hw()  @ c0453fd8  returns the struct at c098b55c
 *
 *     +0x00 i2c_num            = 3
 *     +0x04 power_id           = -1   (MT65XX_POWER_NONE, no LDO)
 *     +0x08 power_vol          = 0    (VOL_DEFAULT)
 *     +0x0c polling_mode       = 0    (interrupt)
 *     +0x10 polling_mode_ps    = 0    (interrupt)
 *     +0x14 polling_mode_als   = 1    (polled)
 *     +0x18 i2c_addr[4]        = 0x1c, 0x1d, 0x1e
 *     +0x1c als_level[]        = 32, 144, 560, 1760, 5600, 8960, 10720, 13920
 *     ...   als_value[]        = 20, 90, 350, 1100, 3500, 5600, 6700, 8700,
 *                                10240
 *
 * Both ladders are strictly monotonic, which is what confirms the split
 * between them: the eight increasing entries are levels and the nine that
 * follow are the reported values.
 *
 * This agrees with the stock ROM's live I2C bus, where 3-001c is bound to the
 * AL3320B driver, and with AL3320B_i2c_probe() @ c04532dc, which reads the
 * same struct through get_cust_alsps_hw().
 *
 * The values this file used to carry were a copy of another project's table
 * (levels 0..20000, thresholds 53/46) and did not match this board.
 */
#include <linux/types.h>
#include <mach/mt_pm_ldo.h>
#include <cust_alsps.h>

static struct alsps_hw cust_alsps_hw = {
	.i2c_num          = 3,
	.power_id         = MT65XX_POWER_NONE,	/* LDO is not used */
	.power_vol        = VOL_DEFAULT,	/* LDO is not used */
	.polling_mode_ps  = 0,
	.polling_mode_als = 1,
	.i2c_addr         = {0x1c, 0x1d, 0x1e, 0x00},
	.als_level = {32, 144, 560, 1760, 5600, 8960, 10720, 13920},
	.als_value = {20, 90, 350, 1100, 3500, 5600, 6700, 8700, 10240, 10240},
	/*
	 * The shipped struct carries ps_threshold_high/low after als_value.
	 * They were not separable from the surrounding padding in the read-out,
	 * so they are left at the driver default rather than invented.
	 */
};

struct alsps_hw *get_cust_alsps_hw(void)
{
	return &cust_alsps_hw;
}
