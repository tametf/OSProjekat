#include "ivtEntry.h"
#include "lock.h"
#include <dos.h>
#include <iostream.h>
#include "thread.h"
#include "kerEv.h"
#include "timer.h"

IVTEntry* IVTEntry::ulazi[256];

IVTEntry::IVTEntry(IVTNo br, pInterrupt novaPR) {
	lock;
	staraRutina=0;
	IVTEntry::ulazi[br]=this;
	mojDogadjaj=0;
	brUlaza=br;
#ifndef BCC_BLOCK_IGNORE
	staraRutina=getvect(br); //cuvam sta je u staroj rutini bilo
	setvect(br, novaPR);
#endif
	unlock;
}


IVTEntry::~IVTEntry() {
	lock;
	IVTEntry::ulazi[brUlaza]=0;
	//delete ulazi[brUlaza];
	//staraRutina();
#ifndef BCC_BLOCK_IGNORE
	setvect(brUlaza, staraRutina);
#endif
	unlock;
}

	void IVTEntry::signal() {

		if(mojDogadjaj!=0) {
			mojDogadjaj->signal();
		}
			dispatch();

	}


	void IVTEntry::zoviStaru() {
		staraRutina();
	}
