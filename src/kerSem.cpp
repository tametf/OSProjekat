#include "kerSem.h"
#include "lista.h"
#include "lock.h"
#include "pcb.h"
#include "listaS.h"
#include "SCHEDULE.H"
#include <iostream.h>


volatile int KernelSem::brBlokSvi=0;

KernelSem::KernelSem(int init) {

//mojSemafor=sem;
if(init<0) {
	value=0;
}
else {
	value=init;
}
blokiraniSvi=new Lista();
semafori->dodaj(this);
}



	KernelSem::~KernelSem() {
		//mojSemafor=0;
		//lock;
		//delete blokiraniVreme;
		semafori->obrisi(this);
		delete blokiraniSvi;
		//mojKS=0;
		//unlock;

	}

	int KernelSem::wait(Time maxTimeToWait) {
		PCB::running->rezWait=1;
		if(--value<0) {

			PCB::running->timeWait=maxTimeToWait;
			PCB::running->stanje=Blokirana;
			blokiraniSvi->dodaj(PCB::running);
			brBlokSvi++;
			dispatch();
		}

		return PCB::running->rezWait;
	}



	int KernelSem::signal(int n) {
		if(n==0) {
			if(value++<0) {
				odblokiraj(1);
				return 0;
			}
		}

		if(n>0) {
			if(brBlokSvi<n) {
				int pom=brBlokSvi;
				odblokiraj(pom);
				value=value+n;
				return pom;
			}
			if(brBlokSvi>=n) {
				odblokiraj(n);
				value=value+n;
				return n;
			}
		}
		if(n<0) {
			return n;
		}
		return 0;
	}


	void KernelSem::timeS() {
		//blokiraniSvi->izbaciIzListeSvih();
		blokiraniSvi->vreme();

	}

	int KernelSem::val() const {
		return value;
	}


	void KernelSem::odblokiraj(int br) {
		for(int i=0; i<br; i++) {
			brBlokSvi--;
			PCB* pom=blokiraniSvi->izbaciPrvi();
			pom->stanje=Spremna;
			Scheduler::put(pom);
		}
	}


