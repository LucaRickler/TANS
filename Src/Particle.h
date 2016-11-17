#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Vector3D.h"
#include "Constants.h"
#include <TRandom3.h>
#include <TVector.h>
#include "InportanceRandom.h"
#include <TMath.h>

enum PType {
	PGAMMA = 0,
	PELECTRON,
	PPOSITRON,
	NUMBER_OF_PARTICLES
};

double BSCrossSection(double* x, double* par) {
	return 4./3./x[0] - 4./3./par[0] + x[0]/par[0]/par[0];
}

double BSCrossSectionMajor(double* x, double* par) {
	return 4./3./x[0];
}

double BSCrossSectionMajorInverse(double* x, double* par) {
	return TMath::Exp(x[0]*TMath::Log(par[1]) - (x[0] + 1)*TMath::Log(par[0]));
}

class Particle : public TObject{
	public:
		Particle();
		Particle(PType ptype, double energy, const Vector3D& direction, const Vector3D& position, bool primary = false);
		bool Divide(double h, double dh, vector<Particle*>& p1,, Particle* p2); // Splitting della particella
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
		PType ptype; // Gamma, Electron, Positron
		Vector3D position;
		Vector3D old_position;
		Vector3D delta_pos;
		double lcm;
		Vector3D direction;

		double LCM(double, double);
		double BSEnergy();
		Particle* BSDecay(double h, double dh);

		InportanceRandom energy_extractor;

		ClassDef(Particle, 1)
};


#endif /* PARTICLE_H_ */
