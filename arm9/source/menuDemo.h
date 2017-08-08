#ifndef MENUDEMO_H
#define MENUDEMO_H

#include "demo.h"
#include <memory>

class MenuDemo : public Demo {
public:
	MenuDemo();
	virtual ~MenuDemo();
	virtual void Load();
	virtual void Unload();
protected:
	virtual void PrepareFrame(VramBatcher &);
	void AcceptInput();
private:
	int selection;

	const int demoCount = 3;
	std::shared_ptr<Demo> makeDemo();
};

#endif