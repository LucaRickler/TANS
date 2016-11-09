#include "Particle.h"
ClassImp(Particle)

//---------------------------------------------------------------------------//

Particle::Particle(){
		this->ptype = PGAMMA;
	  this->energy = 0.0;
	  this->direction = (0., 0., 0.);  // Come inizializzo "a zero" la direzione? Non credo sia giusto scrivere così.
		this->primary = false;
}

//---------------------------------------------------------------------------//

Particle::Particle(PType ptype, double energy, const Vector3D& direction, bool primary){
		while(ptype != PGAMMA && ptype != PELECTRON && ptype != PPOSITRON){
			cout<< "Choose the primary cosmic ray between Gamma(0), Electron(1), Positron(2): " << ptype <<endl;
		}
		this->ptype = ptype;
	  this->energy = (energy >= 0.0 ? energy : 0.0);
		this->direction = direction;
		this->primary = primary;
}

//---------------------------------------------------------------------------//

bool Particle::Divide(Particle* p1, Particle* p2){

/*
 *   Ho modificato un po' quanto mi avevi suggerito di fare! In particolare ora
 *   vedo prima se la soglia più bassa viene raggiunta (ovvero quella necessaria
 *   per la produzione di coppie: 10 MeV) perché, se non è raggiunta questa, non
 *   verrà raggiunta neanche quella più alta (bremsstrahlung: 88 MeV).
 *   Se è raggiunta, vedo se p1 è un gamma o no. Se NON è un gamma devo porre
 *   allora la soglia per la bremsstrahlung (che è più alta). Ho fatto queste
 *   modifiche perché come avevi suggerito tu non si teneva in conto il fatto
 *   che threshold_g != threshold_ep.
 */

		if(p1->energy > threshold_g){

			if(p1->type == PGAMMA){
				p1 = new Particle(PELECTRON, energy/2, direction, false); // direction??
				p2 = new Particle(PPOSITRON, energy/2, direction, false);
			}
			else{
				if(p1->energy > threshold_ep){
					p1 = new new Particle(PGAMMA, energy/2, direction, false);
			  	p2 = NULL;
				}
			}

			return true;
		}

 		return false;
}

//---------------------------------------------------------------------------//

bool Particle::Propagate(){
	 static Vector3D delta_pos;
	 old_position = position;
	 position = (1, 2, 3); /*
	                        *   Stesso problema di prima; non sono sicuro di avere
	                        *   capito come passare i valori di "un oggetto che ha
													*   per tipo una classe".
													*/
	 delta_pos += position - old_position;
	 if(delta_pos > libero cammino assorb)
		 return false;
	 return true;
}

//---------------------------------------------------------------------------//
