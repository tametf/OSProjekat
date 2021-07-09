#ifndef _ivtEntry_h_
#define _ivtEntry_h_
#include "event.h"


typedef void interrupt (*pInterrupt)(...);
typedef unsigned char IVTNo;

#define PREPAREENTRY(brUlaza, stara)\
		void interrupt prekRut##brUlaza(...);\
		IVTEntry ulaz##brUlaza = IVTEntry(brUlaza, prekRut##brUlaza);\
		void interrupt prekRut##brUlaza(...){\
		ulaz##brUlaza.signal();\
		if(stara==1)ulaz##brUlaza.zoviStaru();\
		}

class Event;
class IVTEntry {
public:
	friend class Event;
	friend class KernelEv;
	IVTEntry(IVTNo br, pInterrupt novaR);
	~IVTEntry();

	static IVTEntry* ulazi[];
	void signal();
	void zoviStaru();

	pInterrupt staraRutina;
	KernelEv* mojDogadjaj; //kojim menjam dogadjaj u ulazu brUlaza-tu je bila stara rutina
	IVTNo brUlaza;
};


#endif
