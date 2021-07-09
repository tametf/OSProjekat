#ifndef _kerSem_h_
#define _kerSem_h_
#include "lista.h"
#include "semaphor.h"

class Lista;


class KernelSem {
	friend class Lista;
public:
	KernelSem(int init=1);
	~KernelSem();

	int wait(Time maxTimeToWait);
	int signal(int n=0);
	void timeS();
	int val() const;

	void odblokiraj(int n);
private:
	Lista* blokiraniSvi;
	static volatile int brBlokSvi;
	volatile int value;
	//Semaphore* mojSemafor;



};


#endif
