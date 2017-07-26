#ifndef DEMO_H
#define DEMO_H

class VramBatcher;

class Demo {
public:
	Demo();
	virtual ~Demo();
	virtual void PrepareFrame(VramBatcher &)=0;
	virtual void Load()=0;
	virtual void Unload()=0;

protected:
	void setupDefaultBG();
};


#endif