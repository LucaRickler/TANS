#include "Presentation.h"

//---------------------------------------------------------------------------//

Presentation::Presentation(){}

//---------------------------------------------------------------------------//

void Presentation::Pres1(){
	cout<< "\n*********************************************************" <<endl;
	cout<< "* CREMS (Cosmic Rays ElectroMagnetic Showers simulator) *" <<endl;
	cout<< "*                                                       *" <<endl;
	cout<< "* Authors:                                              *" <<endl;
	cout<< "*    - Alessandro Liberatore                            *" <<endl;
	cout<< "*    - Luca Rickler                                     *" <<endl;
	cout<< "*                                                       *" <<endl;
	cout<< "*********************************************************\n" <<endl;
}

//---------------------------------------------------------------------------//

void Presentation::Pres2(){
	for(int pparticle = PGAMMA; pparticle <= PPOSITRON; pparticle++)
	    switch(pparticle){
	    	case PGAMMA:
				cout<< "Gamma" << setw(7) << "-> " << PGAMMA;
				break;
	    	case PELECTRON:
				cout<< "\nElectron" << setw(4) << "-> " << PELECTRON;
				break;
	    	case PPOSITRON:
				cout<< "\nPositron" << setw(4) << "-> " << PPOSITRON <<endl;
				break;
			}
	cout<< "Your choice: ";
}

//---------------------------------------------------------------------------//
