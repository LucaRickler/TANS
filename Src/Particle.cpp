#include "Particle.h"
ClassImp(Particle)

//---------------------------------------------------------------------------//

Particle::Particle(PType ptype, double penergy, bool pprimary){}

//---------------------------------------------------------------------------//

void Particle::PFeatures(PType ptype, double penergy, bool pprimary){
	if(pprimary == true){
		cout<< "EM shower from ";
		switch(ptype){
			case PGAMMA:
		  	cout<< penergy << " GeV" << " gamma (primary cosmic ray). " <<endl;
		  	break;
			case PELECTRON:
		  	cout<< penergy << " GeV" << " electron (primary cosmic ray). " <<endl;
				break;
			case PPOSITRON:
				cout<< penergy << " GeV" << " positron (primary cosmic ray). " <<endl;
				break;
			}
		}else
				switch(ptype){
					case PGAMMA:
				  	cout<< penergy << " GeV" << " gamma. " <<endl;
				  	break;
					case PELECTRON:
				  	cout<< penergy << " GeV" << " electron. " <<endl;
						break;
					case PPOSITRON:
						cout<< penergy << " GeV" << " positron. " <<endl;
						break;
					}
	}

//---------------------------------------------------------------------------//

vector<Particle*> Particle::Divide(PType ptype, double energy, bool pprimary){

	penergy = energy/2;

	if(ptype == PGAMMA){
		if(penergy >= 1){
			Particle *p1 = new Particle(ptype = PELECTRON, penergy, pprimary = false);
			p1->PFeatures(ptype, penergy, pprimary);
			Particle *p2 = new Particle(ptype = PPOSITRON, penergy, pprimary = false);
			p2->PFeatures(ptype, penergy, pprimary);
			pall_particles.push_back(p1);
			pall_particles.push_back(p2);
		}
	}else{
		if(penergy >= 3){
			Particle *p1 = new Particle(ptype, penergy, pprimary = false);
			p1->PFeatures(ptype, penergy, pprimary);
			Particle *p2 = new Particle(ptype = PGAMMA, penergy, pprimary = false);
			p2->PFeatures(ptype, penergy, pprimary);
			pall_particles.push_back(p1);
			pall_particles.push_back(p2);
		}
	}

	return pall_particles;

}

//---------------------------------------------------------------------------//

double Particle::GetEnergy(){
	return penergy;
}

//---------------------------------------------------------------------------//
