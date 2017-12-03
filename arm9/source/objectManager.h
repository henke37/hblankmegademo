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

class DemoRunner;

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

		OAMUpdate();

		ITCM_CODE void registerForHDMA(unsigned int dmaChannel, bool isSub);
		void DMANow(unsigned int dmaChannel, bool isSub);
	};

	OAMUpdate updates[SCREEN_HEIGHT];

	void buildUpdateForScanlines(unsigned int start, unsigned int chunkSize);

	friend class DemoRunner;

	ITCM_CODE void setupNextHDMA();

};

extern ObjectManager mainObjManager, subObjManager;
#endif