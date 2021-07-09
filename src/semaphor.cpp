#include "semaphor.h"
#include "kerSem.h"
#include "lock.h"
#include "timer.h"
#include <dos.h>


Semaphore::Semaphore(int init) {
	lock;
	myImpl=new KernelSem(init);
	unlock;
}

Semaphore::~Semaphore() {

	lock;
	delete myImpl;
	unlock;
	//myImpl=0;

}

int Semaphore::wait(Time maxTimeToWait) {
	lock;
	int a = this->myImpl->wait(maxTimeToWait);
	unlock;
	return a;
}

int Semaphore::signal(int n) {
	lock;
	int b = myImpl->signal(n);
	unlock;

	return b;
}

int Semaphore::val() const {
lock;
	int c = myImpl->val();
unlock;
return c;
}
