#include "listaS.h"
#include <iostream.h>
#include "timer.h"
#include "lock.h"

ListaS* semafori = new ListaS();


ListaS::ListaS() {
	lock;
	prvi=0;
	posl=0;
	unlock;
}

ListaS::~ListaS() {
	obrisiSve();
}

void ListaS::obrisiSve() {
	lock;
	Elem* pom;
	Elem* tek=prvi;
	for(tek=prvi, pom=0; tek!=0;) {
		pom=tek;
		tek=tek->sled;
		pom->s=0;
		pom->sled=0;
		delete pom;
	}
	prvi=0;
	posl=0;
	unlock;
}



	void ListaS::dodaj(KernelSem* ks) {
		lock;
		Elem* novi=new Elem(ks);
		if(prvi==0) {
			prvi=novi;
			posl=novi;
		}else {
			posl->sled=novi;
			posl=novi;
		}
		unlock;
	}
	void ListaS::obrisi(KernelSem* ks) {
		lock;
		Elem* pret=0;

		for(Elem* tek = prvi; tek!=0; pret = tek, tek = tek->sled) {
			if(tek->s==ks) {
				if(tek==prvi) {
					prvi=prvi->sled;
				}
				if(tek==posl) {
					posl=pret;
				}
				if(pret) {
					pret->sled=tek->sled;
				}
				delete tek;
				break;
			}

		}
		unlock;
	}


	void ListaS::vremeSem() {

		if(prvi==0) return;
		lock;
		for(Elem* tek = prvi; tek!=0; tek=tek->sled) {
			tek->s->timeS();
		}
		unlock;

	}
