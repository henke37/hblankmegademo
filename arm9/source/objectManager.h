#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <vector>
#include <nds/arm9/sprite.h>

#ifdef __INTELLISENSE__
#undef ITCM_CODE
#define ITCM_CODE
#endif

ITCM_CODE void objHdmaMainHandler();
ITCM_CODE void objHdmaSubHandler();

class ObjectManager {
public:
	ObjectManager(unsigned int dmaChannel, bool isSub);
	~ObjectManager();

	std::vector<SpriteEntry> objects;

	void activate();
	void deactivate();

	void operator =(bool e) {
		if (e) activate();
		else deactivate();
	};

	void tick();

private:
	bool enabled;
	bool isSub;
	unsigned int dmaChannel;

	std::vector<SpriteEntry> shadowObjects;

	SpriteEntry objBuff[SPRITE_COUNT];

	friend void objHdmaMainHandler();
	friend void objHdmaSubHandler();

	void hdmaCompleteHandler();
	void updateObjsForScanline(int scanline);
	void setHDMA(std::size_t transferSize);
};

extern ObjectManager mainObjManager, subObjManager;
#endif