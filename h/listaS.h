#ifndef _listaS_h_
#define _listaS_h_
#include "pcb.h"
#include "kerSem.h"

class ListaS {
public:
	ListaS();
	~ListaS();
	void dodaj(KernelSem* ks);
	void obrisi(KernelSem* ks);
	void obrisiSve();
	void vremeSem();
private:
	struct Elem {
			Elem* sled;
			KernelSem* s;
			Elem(KernelSem* ss) {
				s=ss;
				sled=0;
			}
			~Elem() {
				sled = 0;
				s = 0;
			}
		};
		Elem* prvi;
		Elem* posl;
};

extern ListaS* semafori;

#endif
