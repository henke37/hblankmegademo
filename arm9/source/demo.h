#ifndef DEMO_H
#define DEMO_H

class VramBatcher;

class Demo {
public:
	Demo();
	virtual ~Demo();
	virtual void Load()=0;
	virtual void Unload()=0;
	void tick();
protected:
	void setupDefaultBG();
	virtual void AcceptInput()=0;
	virtual void PrepareFrame(VramBatcher &) = 0;
};


#endif