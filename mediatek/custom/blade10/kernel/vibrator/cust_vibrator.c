#include <cust_vibrator.h>
#include <linux/types.h>

/*
 * Values read out of the shipped kernel: get_cust_vibrator_hw()
 * (kernel_blade10_row_wifi-kk.elf @ c046a820) returns &DAT_c098cf1c, and the
 * two ints there are 60 and -1.
 *
 * Both matter, because vibrator_enable() clamps with
 *
 *     if (value > hw->vib_limit && value < hw->vib_timer)
 *             value = hw->vib_timer;
 *
 * With vib_limit = -1 that condition is true for every request shorter than
 * vib_timer, so any buzz below 60 ms is rounded up to 60 ms.  This file had
 * vib_timer = 20 / vib_limit = 9, which rounds up only the 10..19 ms range and
 * lets everything below 10 ms through unchanged - a noticeably shorter, and
 * for the low values a barely perceptible, vibration.
 */
static struct vibrator_hw cust_vibrator_hw = {
	.vib_timer = 60,
  #ifdef CUST_VIBR_LIMIT
	.vib_limit = -1,
  #endif
};

struct vibrator_hw *get_cust_vibrator_hw(void)
{
    return &cust_vibrator_hw;
}
