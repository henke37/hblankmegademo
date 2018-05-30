#ifndef DEMO_H
#define DEMO_H

class VramBatcher;

class Demo {
public:
	Demo();
	virtual ~Demo();
	virtual void Load()=0;
	virtual void Unload()=0;
	void tick(VramBatcher &);
protected:
	void setupDefaultBG();
	void setupTilemapBG(const char *paletteFile, const char * tileSetFile, const char * tileMapFile);
	virtual void AcceptInput()=0;
	virtual void PrepareFrame(VramBatcher &) = 0;
private:
	void compressedFile2Vram(const char * filename, void * dst);
	void loadBGPalette(const char * paletteFile);
};

class HBlankDemo : public Demo {
public:
	virtual ~HBlankDemo()=0;
};


#endif