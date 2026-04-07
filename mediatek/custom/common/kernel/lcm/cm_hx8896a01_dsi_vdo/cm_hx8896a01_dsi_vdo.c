#include <linux/string.h>
#include <mach/mt_gpio.h>
#include <mach/mt_pm_ldo.h>
#include "lcm_drv.h"

// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (1280)
#define FRAME_HEIGHT (800)


// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcd_power_en(void)
{
  hwPowerOn(0x12,0x708,"LCM");
  mt_set_gpio_mode(0x89,0);
  mt_set_gpio_dir(0x89,1);
  mt_set_gpio_out(0x89,1);
  MDELAY(0x78);
  return;
}


static bool lcm_compare_id(void)
{
  uint uVar1;
  int iVar2;

  lcd_power_en();
  MDELAY(10);
  mt_set_gpio_mode(0x9a,0);
  mt_set_gpio_dir(0x9a,0);
  uVar1 = mt_get_gpio_in(0x9a);
  printk("blade10 lcd_id cmi  %d \n",uVar1);
  iVar2 = 1 - uVar1;
  if (1 < uVar1) {
    iVar2 = 0;
  }
  return iVar2;
}

static void lcm_get_params(LCM_PARAMS *params)
{
  __memzero(params,0x23c);
  params->type = LCM_TYPE_DSI;
  (params->dsi).mode = SYNC_EVENT_VDO_MODE;
  (params->dsi).LANE_NUM = LCM_FOUR_LANE;
  (params->dsi).data_format.color_order = LCM_COLOR_ORDER_RGB;
  (params->dsi).data_format.trans_seq = LCM_DSI_TRANS_SEQ_MSB_FIRST;
  (params->dsi).data_format.padding = LCM_DSI_PADDING_ON_LSB;
  (params->dsi).data_format.format = LCM_DSI_FORMAT_RGB888;
  (params->dsi).intermediat_buffer_num = 0;
  (params->dsi).PS = LCM_PACKED_PS_24BIT_RGB888;
  (params->dsi).vertical_sync_active = 2;
  params->width = 0x500;
  (params->dsi).vertical_backporch = 10;
  params->height = 800;
  (params->dsi).vertical_frontporch = 0x15;
  (params->dsi).packet_size = 0x100;
  (params->dsi).horizontal_sync_active = 5;
  (params->dsi).word_count = 0x870;
  (params->dsi).horizontal_backporch = 0x32;
  (params->dsi).vertical_active_line = 800;
  (params->dsi).horizontal_frontporch = 0xba;
  (params->dsi).horizontal_active_pixel = 0x500;
  (params->dsi).PLL_CLOCK = 6;
  return;
}

static void lcm_init(void)
{
  lcd_power_en();
  return;
}


static void lcm_resume(void)
{
  lcd_power_en();
  MDELAY(100);
  return;
}


static void lcm_set_util_funcs(LCM_UTIL_FUNCS *util)
{
  memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
  return;
}


static void lcm_suspend(void)
{
  MDELAY(200);
  MDELAY(0x78);
  mt_set_gpio_mode(0x89,0);
  mt_set_gpio_dir(0x89,1);
  mt_set_gpio_out(0x89,0);
  hwPowerDown(0x12,"LCM");
  return;
}

// ---------------------------------------------------------------------------
//  Get LCM Driver Hooks
// ---------------------------------------------------------------------------

LCM_DRIVER cm_hx8896a01_dsi_vdo_drv =
{
	.name = "cm_hx8896a01_dsi_vdo",
	.compare_id = lcm_compare_id,
	.get_params = lcm_get_params,
	.init = lcm_init,
	.resume = lcm_resume,
	.set_util_funcs = lcm_set_util_funcs,
	.suspend = lcm_suspend,
};
