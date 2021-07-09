#ifndef _lista_h_
#define _lista_h_

#include "pcb.h"
#include "thread.h"

class Lista {
public:
	Lista();
	~Lista();
	friend class Thread;
	void dodaj(PCB* pcb);
	PCB* izbaciPrvi();
	void obrisi();


	void obrisiId(ID id);
	//void izbaciIzListeSvih();
	Thread* dohvatiNit(ID id);
	void obrisiCekajuce(PCB* pcb);
	static Lista* sveNiti;

	int ima();
	void vreme();
private:
	struct Elem{
			PCB* pcbNiti;
			Elem* sled;
			Elem(PCB* ppcb) {
				pcbNiti=ppcb;
				sled=0;
			}
			~Elem() {
				pcbNiti=0;
				sled=0;
			}
		};

	Elem* prvi;
	Elem* posl;
};
#endif
