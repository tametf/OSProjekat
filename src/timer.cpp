#include "timer.h"
#include "pcb.h"
#include "SCHEDULE.H"
#include "semaphor.h"
#include "idle.h"
#include "lock.h"
#include <iostream.h>
#include "listaS.h"
#include <dos.h>

volatile int Timer::zahtevana_promena_konteksta=0;
volatile int Timer::brojac=2;
volatile int Timer::brNiti=0;
Thread* Timer::pocetna = 0;


unsigned tss;
unsigned tsp;
unsigned tbp;



extern void tick();



void interrupt timer(...) {

	if(!Timer::zahtevana_promena_konteksta) {
		if(Timer::brojac>0) {
			Timer::brojac--;
		}
		semafori->vremeSem();
		tick();
		asm int 60h;
		if(/*Timer::brojac > 0 &&*/ PCB::running->nulaTs==1) {return; }
	}

//	if(Timer::brojac>0 && Timer::zahtevana_promena_konteksta==0)
		//return;


	if(Timer::zahtevana_promena_konteksta || Timer::brojac==0) {
		//if(lockFlag) {
		asm {
			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}


		PCB::running->sp=tsp;
		PCB::running->ss=tss;
		PCB::running->bp=tbp;

		if(PCB::running->stanje != Zavrsila && PCB::running->stanje != Blokirana && PCB::running != Idle::idlePCB) {
			PCB::running->stanje=Spremna;
			Scheduler::put(PCB::running);
		}

		PCB::running=Scheduler::get();
		if(PCB::running==0) {
			//if(Timer::brNiti!=0) {
				PCB::running=Idle::idlePCB;
			//}
		}
		else {
			PCB::running->stanje=Tekuca;
		}

		tsp=PCB::running->sp;

		tbp=PCB::running->bp;

		tss=PCB::running->ss;
		Timer::brojac=PCB::running->timeSlice;
		asm {
			mov sp, tsp
			mov bp, tbp
			mov ss, tss
		}
		Timer::zahtevana_promena_konteksta=0;
	/*} else {
			Timer::zahtevana_promena_konteksta=1;
		}*/
	}
}
