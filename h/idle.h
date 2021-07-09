#ifndef _idle_h_
#define _idle_h_
#include "thread.h"

class Idle:public Thread {
public:


	static Idle* idle;
	static PCB* idlePCB;
	static volatile int idleFlag;

	Idle();
	virtual void run();
	~Idle();
	void start();

	PCB* pcbZaIdle;


};



#endif
