#ifndef MENUDEMO_H
#define MENUDEMO_H

#include "demo.h"

class MenuDemo : public Demo {
public:
	MenuDemo();
	virtual ~MenuDemo();
	virtual void PrepareFrame(VramBatcher &);
	virtual void Load();
	virtual void Unload();
};

#endif