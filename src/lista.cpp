#include "lista.h"
#include "lock.h"
#include <iostream.h>
#include "SCHEDULE.H"
#include "timer.h"
#include "thread.h"
#include "kerSem.h"


	Lista* Lista::sveNiti = new Lista();

Lista::Lista() {
	lock;
	prvi = 0;
	posl = 0;
	unlock;
}

Lista::~Lista() {
	obrisi();
}

void Lista::dodaj(PCB* pcb) {
	lock;
	Elem* novi = new Elem(pcb);
	if(prvi==0) {
		prvi=novi;
		posl=novi;
	}
	else {
		posl->sled=novi;
		posl=novi;
	}
	unlock;
}

void Lista::obrisiCekajuce(PCB* pcb) {
	lock;
	while(pcb->cekajuceNiti->ima()) {
		PCB* pom = pcb->cekajuceNiti->izbaciPrvi();
		pom->stanje=Spremna;
		Scheduler::put(pom);
		}
	unlock;
}



	PCB* Lista::izbaciPrvi() {
lock;
		if(ima()) {
			Elem* tek=prvi;
			prvi=prvi->sled;
			if(prvi==0) {
				posl=0;
			}
			PCB *pp=tek->pcbNiti;
			tek->pcbNiti=0;
			tek->sled=0;
			tek->pcbNiti->rezWait=1;
			delete tek;
			unlock;
			return pp;
		}
		else {
			unlock;
			return 0;
		}
	}

	Thread* Lista::dohvatiNit(ID id) {
		lock;
		Elem* tek;
		Thread* t;
		for(tek=prvi; tek!=0; tek=tek->sled) {
			if(tek->pcbNiti->id==id) {
				unlock;
				return tek->pcbNiti->mojaNit;
			}
		}
		unlock;
		return 0;
	}

	void Lista::obrisi() {
		lock;
		Elem* pom;
		Elem* tek = prvi;
		for(tek=prvi, pom=0; tek!=0;)
		{
			pom=tek;
			tek=tek->sled;
			pom->pcbNiti=0;
			pom->sled=0;

			delete pom;
		}
		prvi=0;
		posl=0;
		unlock;
	}




	int Lista::ima() {
		lock;
		if(prvi==0) {
			unlock;
			return 0;
		}
		else {
			unlock;
			return 1;
		}


	}

	void Lista::vreme(){
	lock;
			if(ima()){
				Elem* tek;
				Elem* pret;
				for(tek = prvi, pret = 0; tek!=0;){
					if(tek->pcbNiti->timeWait!=0) {
					tek->pcbNiti->timeWait=tek->pcbNiti->timeWait-1;
					if(tek->pcbNiti->timeWait==0){

						Elem* pom=tek;
						tek=pom->sled;

						pom->pcbNiti->rezWait=0;
						pom->pcbNiti->stanje=Spremna;
						KernelSem::brBlokSvi--;
						Scheduler::put(pom->pcbNiti);


						if(pom==prvi){
							prvi=prvi->sled;
						}
						if(pom==posl){
							posl=pret;
						}
						delete pom;
						if(pret){
							pret->sled=tek;
						}

					}
					else{
						pret=tek;
						tek=tek->sled;
					}
				}else {
					pret = tek;
					tek=tek->sled;
				}
			}
			}
	unlock;

		}
	void Lista::obrisiId(ID id) {
		lock;
		Elem* pret = 0;
		for(Elem* tek=prvi; tek!=0; pret = tek, tek=tek->sled) {
			if(tek->pcbNiti->id==id) {
				if(tek==prvi) {
					prvi=prvi->sled;
				}

				if(pret!=0) {
					pret->sled=tek->sled;
				}

				if(tek==posl) {
					posl=pret;
				}
				tek->pcbNiti=0;
				tek->sled=0;
				delete tek;
				break;
			}
		}
		unlock;


	}
