#include "Idle.h"
#include "pcb.h"
#include "timer.h"
#include "lock.h"


Idle* Idle::idle = 0;
PCB* Idle::idlePCB=0;
volatile int Idle::idleFlag = 1;

	Idle::Idle():Thread(1024, 1) {
		pcbZaIdle=Idle::idlePCB;
	}

	 void Idle::run() {
		while(1) {}
	}

	void Idle::start() {
		pcbZaIdle->kreirajStek();
		pcbZaIdle->stanje=Spremna;
	}

	Idle::~Idle() {
		pcbZaIdle=0;
	}
