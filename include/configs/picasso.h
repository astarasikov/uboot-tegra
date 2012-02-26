/*
 *  (C) Copyright 2010,2011
 *  NVIDIA Corporation <www.nvidia.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <asm/sizes.h>
#include "tegra2-common.h"

/* High-level configuration options */
#define TEGRA2_SYSMEM		"nvmem=128M@384M mem=1024M@0M vmalloc=256M"
#define V_PROMPT		"Tegra2 (Ventana) # "
#define CONFIG_TEGRA2_BOARD_STRING	"Acer Iconia Tab A500"

/* Board-specific serial config */
#define CONFIG_SERIAL_MULTI

#define CONFIG_STD_DEVICES_SETTINGS	"stdin=serial\0" \
					"stdout=serial,lcd\0" \
					"stderr=serial,lcd\0"


#define CONFIG_MACH_TYPE		3403
#define CONFIG_SYS_BOARD_ODMDATA	0x300d8011 /* lp1, 1GB */

/* SD/MMC */
#define CONFIG_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_TEGRA2_MMC
#define CONFIG_CMD_MMC

#define CONFIG_DOS_PARTITION
#define CONFIG_EFI_PARTITION
#define CONFIG_EFI_FORCE_DEVICE 0

#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT


/* Environment not stored */
#define CONFIG_ENV_IS_NOWHERE

#define CONFIG_TEGRA2_GPIO
#define CONFIG_CMD_TEGRA2_GPIO_INFO

/*
 *  LCDC configuration
 */
#define CONFIG_LCD
#define CONFIG_VIDEO_TEGRA2

/* TODO: This needs to be configurable at run-time */
#define LCD_BPP             LCD_COLOR16
#define CONFIG_SYS_WHITE_ON_BLACK       /*Console colors*/

#define CONFIG_DEFAULT_DEVICE_TREE "tegra2-picasso"

#define CONFIG_EXTRA_ENV_SETTINGS \
	CONFIG_STD_DEVICES_SETTINGS \
	CONFIG_REGEN_ALL_SETTINGS \
	CONFIG_EXT2_BOOT_HELPER_SETTINGS\
	CONFIG_NETBOOT_SETTINGS \
	\
	"usb_boot=setenv devtype usb; " \
		"setenv devnum 0; " \
		"setenv devname sda; " \
		"run run_disk_boot_script;" \
		"run ext2_boot\0" \
	\
	"fat_boot=" \
		"setenv bootdev_bootargs " \
			"root=/dev/${devname}${rootpart} rootwait ro; " \
		"if ext2load ${devtype} ${devnum}:${script_part} " \
				"${loadaddr} /uImage; then " \
			"bootm ${loadaddr};" \
		"fi\0" \
	\
	"ext4_boot=" \
		"setenv bootdev_bootargs " \
			"root=/dev/${devname}${rootpart} rootwait ro; " \
		"if ext2load ${devtype} ${devnum}:${script_part} " \
				"${loadaddr} /uImage; then " \
			"bootm ${loadaddr};" \
		"fi\0" \
	\
	"mmc_boot=mmc rescan ${devnum}; " \
		"setenv devtype mmc; " \
		"setenv devname mmcblk${devnum}p; " \
		"run run_disk_boot_script;" \
		"echo Load Address:${loadaddr};" \
		"echo Cmdline:${bootargs}; " \
		"run ext4_boot\0" \
	"mmc0_boot=setenv devnum 0; " \
		"setenv script_part 8; " \
		"setenv rootpart 2; " \
		"run mmc_boot\0" \
	"mmc1_boot=setenv devnum 1; " \
		"setenv script_part 1; " \
		"setenv rootpart 2; " \
		"run mmc_boot\0" \
	\
	"non_verified_boot=" \
		"setenv dev_extras video=tegrafb console=tty0; "\
		"setenv script_part 1; "\
		"run mmc0_boot; " \
		"run mmc1_boot; " \
		"usb start; " \
		"run usb_boot; " \
	\
	"board=picasso\0"
#endif /* __CONFIG_H */
