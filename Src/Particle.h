#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Vector3D.h"
#include "Constants.h"
#include <TRandom3.h>
#include <TVector.h>
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

double BSCrossSection(double k, double E) {
	//Sezione d'urto per brehmsstrahlung
	//return 4./3./xx - 4./3./par[0] + xx/par[0]/par[0];
	//return x[0] + (1. - x[0])*(4./3. + 2.*bs_b)/x[0];
	return E/k + 0.75*k/E - 1.;
}

double BSCrossSectionMajor(double k, double E) {
	//Maggiorante della sezione d'urto per brehmsstrahlung
	//double xx = x[0];
	//return 4./3./xx;
	return E/k;
}

double BSCrossSectionMajorInverse(double u, double kmin, double kmax) {
	//Inverso dell'integrale del maggiorante della sezione d'urto per brehmsstrahlung
	//return TMath::Exp(xx*TMath::Log(par[1]) - (xx + 1)*TMath::Log(par[0]));
	return TMath::Exp(u*(TMath::Log(kmax) - TMath::Log(kmin)));
}

double NGamma(double E, double Kmin, double Kmax) {
	//Numero di gamma emessi per BS tra Kmin (par[0]) e Kmax (par[1]) in una lunghezza di radiazione da un elettrone di energia E (x[0])
	return (4./3. * TMath::Log(Kmax/Kmin - 4.*(Kmax - Kmin)/3./E + 0.5*(Kmax*Kmax - Kmin*Kmin)/E/E));
}

//---------------------------------------------------------------------------//
//																			X0																	 //
//---------------------------------------------------------------------------//

double X0(PType ptype) {
	return 1.;
}

//---------------------------------------------------------------------------//

class Particle : public TObject{
	public:
		Particle();
		Particle(PType ptype, double energy, const Vector3D& direction, const Vector3D& position, bool primary = false);
		bool Divide(double h, double dh, vector<Particle>& p1, Particle& p2, int& counter, double& energy_lost); // Splitting della particella
		bool Propagate(double h, double dh); // Trasporto della particella
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
		bool lcm_computed;
		Vector3D direction;

		double BSEnergy();
		bool BSEmission(double h, double dh, Particle& out_gamma, int& counter, double& energy_lost);
		bool CoupleGeneration(double h, double dh, Particle& p1, Particle& p2, int& counter);

		ClassDef(Particle, 1)
};

#endif /* PARTICLE_H_ */
