#include "lock.h"
#include "pcb.h"
#include "idle.h"
#include "SCHEDULE.H"
#include "timer.h"
#include <dos.h>
#include <iostream.h>
#include "lista.h"

int PCB::posId = 0;
PCB* PCB::running;

PCB::PCB(StackSize size, Time time, Thread* t) {
	lock;
	this->mojaNit = t;
	this->timeSlice = time;
	this->id = ++posId;
	this->rezWait = 0;
	this->started = 0;
	//this->llock=0;
	this->timeWait = 0;
	this->stanje = Nova;

	this->cekajuceNiti = new Lista();

	if (time == 0) {
		this->nulaTs = 1;
	} else {
		this->nulaTs = 0;
	}
	//this->nulaTs = (time == 0);
	if (Idle::idleFlag != 1) {
		Lista::sveNiti->dodaj(this);
	}
	if (Idle::idleFlag == 1) {
		Idle::idleFlag = 0;
		Idle::idlePCB = this;
	}
	this->size = size;
unlock;
}

void PCB::kreirajStek() {
lock;
if (size > 65535) {
	size = 65535;
}
#ifndef BCC_BLOCK_IGNORE
size=size/sizeof(unsigned);
stek=new unsigned[size];
stek[size-1]=0x200;
stek[size-2]=FP_SEG(&wrapper);
stek[size-3]=FP_OFF(&wrapper);
ss=FP_SEG(stek+size-12);
sp=FP_OFF(stek+size-12);
bp=FP_OFF(stek+size-12);
#endif
unlock;
}

void PCB::wrapper() {
PCB::running->mojaNit->run(); //staticka metoda->mozemo da uzmemo njenu adresu; pozivamo run tekuce metode; run je definisano u thread;
//pocetna adresa na steku treba da bude adresa ovog wrappera, pa kad se desi prvi prekid od timera-dolazi se ovde
//PCB je prijateljska klasa klasi thread
lock;
Lista::sveNiti->obrisiCekajuce(PCB::running);
PCB::running->stanje = Zavrsila;
Timer::brNiti--;
unlock;
dispatch();
}

PCB::~PCB() {

delete[] stek;
delete cekajuceNiti;
if(Lista::sveNiti != 0)
	Lista::sveNiti->obrisiId(this->id);

}

void PCB::waitToComplete() {
lock;
if (this->stanje == Zavrsila || this == Idle::idlePCB
	|| this == PCB::running/* || this==Timer::pocetna*/) {
unlock;
return;
} else {
PCB::running->stanje = Blokirana;
cekajuceNiti->dodaj(PCB::running);
unlock;
dispatch();
return;
}
}

ID PCB::getId() {
return id;
}

ID PCB::getRunningId() {
return PCB::running->getId();
}

Thread* PCB::getThreadById(ID id) {
return Lista::sveNiti->dohvatiNit(id);
}

void PCB::start() {
this->stanje = Spremna;
Scheduler::put(this);
Timer::brNiti++;
kreirajStek();
}

