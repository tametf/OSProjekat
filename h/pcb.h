#ifndef _pcb_h_
#define _pcb_h_


#include "lista.h"
#include "thread.h"
class Lista;

enum Stanje {Tekuca, Nova, Startovana, Spremna, Blokirana, Zavrsila};

class PCB {
public:
	volatile Stanje stanje;
	Time timeSlice;
	static PCB* running;
	static ID posId;
	ID id;
	Thread* mojaNit;
	volatile int nulaTs;
	volatile int started;
	StackSize size;

	Lista* cekajuceNiti;
	//volatile int llock;
	volatile int rezWait;
	Time timeWait;
	unsigned sp;
	unsigned ss;
	unsigned bp;
	unsigned* stek;

	void start();
	void waitToComplete();
	~PCB();
	static void wrapper();
	void kreirajStek();
	ID getId();
	friend class Thread;
	static ID getRunningId();
	static Thread * getThreadById(ID id);
	PCB(StackSize stackSize = defaultStackSize, Time timeSlice =
				defaultTimeSlice, Thread* thread);

};
#endif
