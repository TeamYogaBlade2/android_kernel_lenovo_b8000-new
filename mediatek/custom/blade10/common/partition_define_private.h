#include "partition_define.h"

static const struct excel_info PartInfo_Private[PART_NUM] = {
	{"preloader", 0x600000, 0x0, EMMC, 0, BOOT_1},
	{"mbr", 0x80000, 0x600000, EMMC, 0, USER},
	{"ebr1", 0x80000, 0x680000, EMMC, 1, USER},
	{"pmt", 0x400000, 0x700000, EMMC, 0, USER},
	{"pro_info", 0x300000, 0xB00000, EMMC, 0, USER},
	{"nvram", 0x500000, 0xE00000, EMMC, 0, USER},
	{"protect_f", 0xA00000, 0x1300000, EMMC, 2, USER},
	{"protect_s", 0xA00000, 0x1D00000, EMMC, 3, USER},
	{"seccfg", 0x20000, 0x2700000, EMMC, 0, USER},
	{"uboot", 0x60000, 0x2720000, EMMC, 0, USER},
	{"bootimg", 0x600000, 0x2780000, EMMC, 0, USER},
	{"recovery", 0x600000, 0x2D80000, EMMC, 0, USER},
	{"sec_ro", 0x600000, 0x3380000, EMMC, 4, USER},
	{"misc", 0x80000, 0x3980000, EMMC, 0, USER},
	{"logo", 0x300000, 0x3A00000, EMMC, 0, USER},
	{"ebr2", 0x80000, 0x3D00000, EMMC, 0, USER},
	{"expdb", 0xA00000, 0x3D80000, EMMC, 0, USER},
	{"fac", 0xC800000, 0x4780000, EMMC, 5, USER},
	{"android", 0x40000000, 0x10F80000, EMMC, 6, USER},
	{"cache", 0x7E00000, 0x50F80000, EMMC, 7, USER},
	{"usrdata", 0x40000000, 0x58D80000, EMMC, 8, USER},
	{"bmtpool", 0x1500000, 0xFFFF00A8, EMMC, 0, USER},
};

#ifdef  MTK_EMMC_SUPPORT
struct MBR_EBR_struct MBR_EBR_px[MBR_COUNT]={
        {"mbr", {1, 2, 3, 4, }},
        {"ebr1", {5, 6, 7, }},
        {"ebr2", {8, }},
};

EXPORT_SYMBOL(MBR_EBR_px);
#endif
