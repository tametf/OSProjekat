#include "thread.h"
#include <stdlib.h>
#include <iostream.h>
#include "timer.h"
#include "lista.h"
#include "ivtEntry.h"
#include "listaS.h"
#include <dos.h>
#include "lock.h"

typedef void interrupt(*pInterrupt)(...);
pInterrupt oldR;


extern int userMain(int argc, char* argv[]);
void inicijalizuj() {
#ifndef BCC_BLOCK_IGNORE
	lock;
	oldR=getvect(0x8);
	setvect(0x8, timer);
	setvect(0x60, oldR);
	unlock;
#endif
}

void restauriraj() {
#ifndef BCC_BLOCK_IGNORE
	lock;
	setvect(0x8, oldR);
	unlock;
#endif
}

int main(int argc, char* argv[]) {

	Idle::idle = new Idle();
	Idle::idle->start();

	inicijalizuj();

	Timer::pocetna = new Thread();
	Timer::pocetna->myPCB->stanje=Tekuca;
	PCB::running=Timer::pocetna->myPCB;
	Timer::pocetna->myPCB->kreirajStek();

	int kraj = userMain(argc, argv);


	delete Idle::idle;
	//Idle::idlePCB=0;

	delete semafori;
	delete Lista::sveNiti;

	for(int i=0;i<256;i++){
		if(IVTEntry::ulazi[i]!=0) {
			delete IVTEntry::ulazi[i];
		}
	}

	restauriraj();

	delete Timer::pocetna;
	//delete PCB::running;

	return kraj;
}
