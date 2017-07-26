#ifndef REGISTER_OVERRIDE_H
#define REGISTER_OVERRIDE_H

template <class T>class registerOverride {
public:

	registerOverride() : regAddr(nullptr) {}

	void set(volatile T *regAddr, T newVal) {
		oldVal = *regAddr;
		this->regAddr = regAddr;
		*regAddr = newVal;
	}

	void reset() {
		if(regAddr) {
			*regAddr = oldVal;
			oldVal = nullptr;
		}
	}

	~registerOverride() {
		if(regAddr) {
			*regAddr = oldVal;
		}
	}

private:

	volatile T *regAddr;
	T oldVal;
};

#endif

