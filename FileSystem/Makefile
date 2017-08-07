ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

all: build/P.img.bin build/P.pal.bin build/P.map.bin

build/P.img.bin build/P.pal.bin build/P.map.bin: source/P.png build
	grit source/P.png -gB 4 -fh! -ftb -pz! -m -mLf -mR4 -mzl -gzl -o build/P

build:
	mkdir build

clean:
	rm -r build