#include "thread.h"
#include "pcb.h"
#include "lock.h"
#include "timer.h"
#include <dos.h>
#include "lista.h"



Thread::Thread(StackSize stackSize, Time timeSlice) {
	lock;
	myPCB = new PCB(stackSize, timeSlice, this);
	myPCB->stanje=Nova;
	unlock;
}

void Thread::start() {
	lock;
	if(myPCB->stanje==Nova) { //da je ne bih startovala vise puta
		myPCB->start();
	}
	unlock;
}

void Thread::waitToComplete() {
	this->myPCB->waitToComplete();
}


Thread::~Thread() {
	//lock;
	waitToComplete();
	lock;
	delete myPCB;
	unlock;
}

ID Thread::getId() {
	return myPCB->getId();
}

ID Thread::getRunningId() {
	return PCB::getRunningId();
}

Thread* Thread::getThreadById(ID id) {
	return PCB::getThreadById(id);
}
void dispatch() {
	lock
	Timer::zahtevana_promena_konteksta=1;
	timer();
	unlock
	}
