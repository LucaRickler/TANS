#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Vector3D.h"
#include "Constants.h"
#include <TRandom3.h>

enum PType {
	PGAMMA = 0,
	PELECTRON,
	PPOSITRON,
	NUMBER_OF_PARTICLES
};

// Da qualche parte ci sarà un array di double così:
/*
 *   double *masses = new double[NUMBER_OF_PARTICLES]
 *   masses[(int)PGAMMA] = 0.0 // masse espresse in MeV/c^2
 *   masses[(int)PELECTRON] = masses[(int)PPOSITRON] = 0.511 // masse espresse in MeV/c^2
 */
// Devo decidere come e dove metterlo. Probabilmente una classe di costanti.

class Particle : public TObject{
	public:
		Particle();
		Particle(PType ptype, double energy, const Vector3D& direction, const Vector3D& position, bool primary = false);
		bool Divide(double h, Particle* p1, Particle* p2); // Splitting della particella
		bool Propagate(double h); // Trasporto della particella
		const double GetEnergy() const {return energy;}
		const PType GetPType() const {return ptype;}
		const bool IsPrimary() const {return is_primary;}
		Vector3D GetPositon() const {return position;}
		Vector3D GetOldPositon() const {return old_position;}
		Vector3D GetDirection() const {return direction;}

	private:
		double energy; // MeV
		bool is_primary;
		const double threshold_g = 10.; // Soglia in MeV per i gamma (g) per fare produzione di coppia.
		//ottenuto ad occhio dai grafici di probabilità di interazione di gamma
		const double threshold_ep = 88.05; // Soglia in MeV per gli elettroni/positroni (ep) per fare bremmstrahlung.
		PType ptype; // Gamma, Electron, Positron
		Vector3D position;
		Vector3D old_position;
		Vector3D direction;

		double LCM(double, double);

		ClassDef(Particle, 1)
};


#endif /* PARTICLE_H_ */
