#ifndef MENUDEMO_H
#define MENUDEMO_H

#include "demo.h"

class MenuDemo : public Demo {
public:
	MenuDemo();
	virtual ~MenuDemo();
	virtual void Load();
	virtual void Unload();
protected:
	virtual void PrepareFrame(VramBatcher &);
	void AcceptInput();
};

#endif