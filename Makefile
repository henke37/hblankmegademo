# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2023

BLOCKSDS	?= /opt/blocksds/core

# User config

NAME		= hblankmegademo
GAME_TITLE = HBlank megademo
GAME_SUBTITLE1 = henke37
GAME_SUBTITLE2 = prealpha
GAME_ICON = icon.bmp
NITROFSDIR = FileSystem/build

include $(BLOCKSDS)/sys/default_makefiles/rom_arm9arm7/Makefile
