#include "lock.h"
#include "event.h"
#include "kerEv.h"
#include "timer.h"

Event::Event(IVTNo ivtNo) {
	lock;
	myImpl=new KernelEv(ivtNo);
	unlock;
}

	Event::~Event(){
		lock;
			delete myImpl;
		unlock;
		//myImpl=0;

	}
	void Event::wait(){
		lock;
		myImpl->wait();
		unlock;
	}

	void Event::signal(){
		lock;
		myImpl->signal();
		unlock;
	}
