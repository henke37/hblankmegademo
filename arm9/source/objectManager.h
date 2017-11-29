#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <vector>
#include <nds/arm9/sprite.h>

#ifdef __INTELLISENSE__
#undef ITCM_CODE
#undef DTCM_DATA
#define ITCM_CODE
#define DTCM_DATA
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

	int lastUsedObjSlots;

	std::vector<SpriteEntry> shadowObjects;

	struct OAMUpdate {
		SpriteEntry objBuffer[SPRITE_COUNT];
		unsigned int updateSize;//in objects
		ITCM_CODE void registerForHDMA(unsigned int dmaChannel, bool isSub);
		void DMANow(unsigned int dmaChannel, bool isSub);
	};

	OAMUpdate updates[SCREEN_HEIGHT];

	void buildUpdateForScanlines(unsigned int start, unsigned int chunkSize);

	friend void objHdmaMainHandler();
	friend void objHdmaSubHandler();

	ITCM_CODE void hdmaCompleteHandler();

};

extern ObjectManager mainObjManager, subObjManager;
#endif