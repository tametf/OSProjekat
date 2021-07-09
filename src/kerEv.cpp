#include "kerEv.h"
#include "SCHEDULE.H"
#include "ivtEntry.h"
#include "lock.h"
#include "timer.h"
#include <IOSTREAM.H>
#include <DOS.H>
#include "pcb.h"

class Scheduler;


KernelEv::KernelEv(IVTNo ivtNo) {
lock;
	kreator=PCB::running;
	val=0;
	blokirana=0;

	//mojDogadjaj=dog;
	konkUlaz=ivtNo;
	//mojSemafor = new KernelSem(0);
	IVTEntry::ulazi[ivtNo]->mojDogadjaj=this;
unlock;
}

//promena
KernelEv::~KernelEv() {
	kreator=0;
	if(IVTEntry::ulazi[konkUlaz]!=0) {
		IVTEntry::ulazi[konkUlaz]->mojDogadjaj=0;
	}
	//delete mojSemafor;
}


	void KernelEv::wait() {
		lock;
		if(kreator==PCB::running) {
			if(val==1) {
				val=0;
			}
			else { //val==0-moze da bude samo 1 ili 0
				blokirana=PCB::running;
				blokirana->stanje=Blokirana;
				dispatch();
			}
		}

unlock;

	}




	void KernelEv::signal() {
		lock;
		if(!blokirana) {
			val=1; //koliko god signala da bude, val ima max vrednost 1
		}
		else {
			blokirana->stanje=Spremna; //isto sto i kreator->stanje=Spremna
			Scheduler::put(blokirana);
			blokirana=0; //nemam blokiranu
			val=0; //kad sam odblokirala, iskoristio se ovaj jedan signal i smanjio val
		}
		unlock;
	}
