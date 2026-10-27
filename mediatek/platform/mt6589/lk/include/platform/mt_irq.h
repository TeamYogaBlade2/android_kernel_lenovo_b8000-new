/*
 * MT6589 interrupt numbers for LK.
 *
 * This header used to carry its own copy of the IRQ table, and 24 of the entries
 * it shared with the kernel disagreed with it - I2C0 was 49 here and 44 there,
 * EINT 96 and 116, G2D 87 and 177, and the whole APARM/DCC/DMA-UART group was
 * shifted. The kernel is the correct one: it agrees with the datasheet and with
 * the mainline device tree
 *
 *   mmc@11230000    GIC_SPI 39  -> 32 + 39  = 71   (both sources agree)
 *   timer@10008000  GIC_SPI 113 -> 32 + 113 = 145
 *   i2c@1100d000    GIC_SPI 44  -> 32 + 44  = 76
 *
 * so the table now comes from the kernel rather than being duplicated. The full
 * difference list is in mt6589-emulator/docs/qemu/lk-irq-table.md.
 *
 * Two things below are worth knowing.
 *
 * 1. The include climbs three levels, not two. This file lives in
 *    lk/include/platform, so "../../.." is mediatek/platform/mt6589 and the
 *    kernel header sits beside it. A first attempt used two levels and did not
 *    resolve at all.
 *
 * 2. The kernel header names some lines differently from LK, and LK's sources
 *    use its own names (`MT_GPT_IRQ_ID`, not `MT6589_GPT_IRQ_ID`). Dropping the
 *    private table without adding these aliases left the LK build with
 *    undeclared identifiers, so they are mapped here. Checked by preprocessing
 *    every name LK uses.
 */
#ifndef _MT_IRQ_H_
#define _MT_IRQ_H_

#include "../../../kernel/core/include/mach/mt_irq.h"

/* Names LK uses for lines the kernel spells with its own prefix. */
#define MT_GPT_IRQ_ID                   MT6589_GPT_IRQ_ID
#define MT_APARM_GPTTIMER_IRQ_LINE      MT6589_GPT_IRQ_ID
#define MT_USB0_IRQ_ID                  MT6589_USB0_IRQ_ID
#define MT_DSI_IRQ_ID                   MT6589_DISP_DSI_IRQ_ID

/*
 * The following have no separate source and are aliases of the same block on
 * other SoCs of this family. They are mapped onto the MT6589 block because that
 * is the only one this SoC has; a caller reaching them is display code that also
 * exists on MT6575/MT6577.
 */
#define MT6575_DSI_IRQ_ID               MT6589_DISP_DSI_IRQ_ID
#define MT6577_DSI_IRQ_ID               MT6589_DISP_DSI_IRQ_ID
#define MT6589_DSI_IRQ_ID               MT6589_DISP_DSI_IRQ_ID
#define MT6589_DPI_IRQ_ID               MT6589_DISP_DPI0_IRQ_ID
#define MT6577_LCD_IRQ_ID               MT6589_DISP_DPI0_IRQ_ID
#define MT6589_LCD_IRQ_ID               MT6589_DISP_DPI0_IRQ_ID

#endif /* _MT_IRQ_H_ */
