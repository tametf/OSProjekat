#ifndef _kerEv_h_
#define _kerEv_h_
#include "event.h"
#include "pcb.h"
#include "lista.h"
#include "KerSem.h"
class PCB;


class KernelEv {
public:
	KernelEv(IVTNo);
	~KernelEv();
	void wait();
	void signal();
	void signalAll();
private:
	volatile int val;
	IVTNo konkUlaz;
	PCB* kreator;
	PCB* blokirana;
	static Lista* blokirane;
	//KernelSem* mojSemafor;//obrisi
	//Event* mojDogadjaj;
};
#endif
