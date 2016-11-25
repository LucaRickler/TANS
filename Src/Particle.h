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

//---------------------------------------------------------------------------//
//														Sezioni d'urto																 //
//---------------------------------------------------------------------------//
//NOTA: possibile miglioria: calcolo di Z(h) da aggiungere alle sezioni d'urto

double BSCrossSection(double* x, double* par) {
	//Sezione d'urto per brehmsstrahlung
	double xx = x[0];
	//return 4./3./xx - 4./3./par[0] + xx/par[0]/par[0];
	return x[0] + (1. - x[0])*(4./3. + 2.*bs_b)/x[0]
}

double BSCrossSectionMajor(double* x, double* par) {
	//Maggiorante della sezione d'urto per brehmsstrahlung
	double xx = x[0];
	return 4./3./xx;
}

double BSCrossSectionMajorInverse(double* x, double* par) {
	//Inverso dell'integrale del maggiorante della sezione d'urto per brehmsstrahlung
	double xx = x[0];
	return TMath::Exp(xx*TMath::Log(par[1]) - (xx + 1)*TMath::Log(par[0]));
}

//---------------------------------------------------------------------------//

class Particle : public TObject{
	public:
		Particle();
		Particle(PType ptype, double energy, const Vector3D& direction, const Vector3D& position, bool primary = false);
		bool Divide(double h, double dh, vector<Particle*>& p1, Particle** p2); // Splitting della particella
		bool Propagate(double h); // Trasporto della particella
		double GetEnergy() const {return energy;}
		PType GetPType() const {return ptype;}
		bool IsPrimary() const {return is_primary;}
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
		bool BSDecay(double h, double dh, Particle** out_gamma);
		bool CoupleGeneration(double h, double dh, Particle** p1, Particle** p2);
		InportanceRandom energy_extractor;

		ClassDef(Particle, 1)
};


#endif /* PARTICLE_H_ */
