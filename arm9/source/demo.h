#ifndef DEMO_H
#define DEMO_H

class VramBatcher;

class Demo {
public:
	virtual ~Demo();
	virtual void PrepareFrame(VramBatcher &)=0;
	virtual void Load()=0;
};


#endif