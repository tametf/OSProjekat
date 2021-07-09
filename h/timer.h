#ifndef _timer_h_
#define _timer_h_
#include "idle.h"
#include "pcb.h"

void interrupt timer(...);

void inicijalizuj();
void restauriraj();

class Idle;
class Timer {
public:
	static volatile int zahtevana_promena_konteksta;
	static volatile int brojac;
	static volatile int brNiti;

	static Thread* pocetna;


};

#endif
