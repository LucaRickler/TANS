#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Vector3D.h"
#include <TObject.h>

enum PType {
	PGAMMA = 0,
	PELECTRON,
	PPOSITRON,
	NUMBER_OF_PARTICLES
}

//da qualche parte ci sarà un array di double così:
/*
* double *masses = new double[NUMBER_OF_PARTICLES]
* masses[(int)PGAMMA] = 0.0
* masses[(int)PELECTRON] = masses[(int)PPOSITRON] = ...
*/
//Devo decidere come e dove metterlo. Probabilmente una classe di costanti

//Se non compila ancora, non ti preoccupare. Tu abbozza il codice, al debug ci penso io

class Particle : public TObject{
	public:
		Particle();
		Particle(PType ptype, double energy, const Vector3D& direction, bool primary = false); //(const Vector3D&, double theta); // nell'implementazione, devi omettere ""= false", altrimenti non compila
		//void PFeatures(PType ptype, double penergy, bool pprimary); //??? A cosa serve? Senza reference non puoi passare dati all'esterno

		void Propagate(); //Trasporto della particella
		/*
		* static Vector3D delta_pos; (Codice vero, devi scriverlo così)
		*	old_position = position
		*	position = ...
		* delta_pos += position - old_position (ci sono gli operatori di somma e differenza per Vector3D, quindi puoi fare c=a+-b)
		* if(delta_pos > libero cammino assorb)
		* 	assorbi (non te ne preoccupare adesso, lo faremo più tardi. Sostituiscilo con solo un ";", fidati)
		*/

		bool Divide(Particle* p1, Particle* p2); //vedi gli appunti che ti avevo scritto, questo deve:
		/* if(soglia)
		*  	if(PGAMMA)
		*			p1 = new e+
		*			p2 = new e-
		*		else
		*			p1 = new gamma
		*			p2 = NULL
		*		return true
		*	(else) (non serve scriverlo, è per farti capire il concetto. Senza il codice è più elegante)
		* 	return false
		*/
		//Nel codice chiamante:
		/*
		* for (Particle *p in all_particles)
		* 	Particle *p1, *p2
		* 	if(p->Divide(p1,p2))
		*			all_particles.remove(p)
		*			delete p
		*/

		const double GetEnergy const {return energy;}
		const PType GetPType const {return ptype;}
		const bool IsPrimary const {return is_primary;}
		Vector3D GetPositon const {return position;}
		Vector3D GetOldPositon const {return old_position;}
		Vector3D GetDirection const {return direction;}

	private:
		//vector<Particle*> pall_particles; //NON serve qua dentro, non ha senso logico che una particella contenga delle particelle
		double energy;
		bool is_primary;
		const double threshold_g = 0.0; //Queste convieme metterle come costanti. Le sposteremo altrove. Metti il numero giusto al posto di 0.0
		const double threshold_ep = 0.0;
		PType ptype;
		Vector3D position;
		Vector3D old_position;
		Vector3D direction;

		ClassDef(Particle, 1)
};


#endif /* PARTICLE_H_ */
