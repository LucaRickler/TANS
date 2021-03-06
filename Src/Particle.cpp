#include "Particle.h"
ClassImp(Particle)

//---------------------------------------------------------------------------//

Particle::Particle() : TObject() {
	this->ptype = PGAMMA;
  this->energy = 0.0;
  this->direction = Vector3D();
	this->position = Vector3D();
	this->old_position = Vector3D();
	this->is_primary = false;
	this->lcm_computed = false;
	this->delta_pos = Vector3D();
}

//---------------------------------------------------------------------------//

Particle::Particle(PType ptype, double energy, const Vector3D& direction, const Vector3D& position, bool primary) {
	if(ptype == NUMBER_OF_PARTICLES)
		ptype = PGAMMA;
	this->ptype = ptype;
  this->energy = (energy >= 0.0 ? energy : 0.0);
	this->direction = direction;
	this->position = position;
	this->old_position = position;
	this->is_primary = primary;
	this->lcm_computed = false;
	this->delta_pos = Vector3D();
}

//---------------------------------------------------------------------------//

bool Particle::Divide(double h, double dh, vector<Particle>& p1, int& counter, double& energy_lost) {
	if(energy > g_threshold[(int)ptype]) {
		if(ptype == PGAMMA){
			Particle electron, positron;
			if(CoupleGeneration(h,dh,electron,positron,counter)) { //Se produco una coppia
				electron.Divide(h,dh,p1,counter,energy_lost); //potrebbe fare BS in [h,h+dh]
				p1.push_back(electron);
				positron.Divide(h,dh,p1,counter,energy_lost); //potrebbe fare BS in [h,h+dh]
				p1.push_back(positron);
				return true;
			}
		} else {
			Particle bs_gamma;
			bool return_state = false;
			while(BSEmission(h,dh,bs_gamma,counter,energy_lost)) { //Fintanto che emetto fotoni
				if(bs_gamma.GetEnergy() != 0.) { //Se il fotone emesso aveva energia sufficiente
					if(!bs_gamma.Divide(h,dh,p1,counter,energy_lost)) { //Se non produco una coppia
						p1.push_back(bs_gamma); //Caso senza produzione di coppia
					}
				}
				return_state = true;
			}
			return return_state;
		}
	}

	return false;
}

//---------------------------------------------------------------------------//

bool Particle::Propagate(double h, double dh){
	if(energy > g_threshold[(int)ptype]) //Caso in cui non ha emesso ora, ma lo farà dopo
		return true;
	if(ptype == PGAMMA) //Scarto subito i gamma sotto soglia
		return false;
	if(!lcm_computed){ //Se non ho mai calcolato la distanza di assorbimento
		old_position = position;
		if(energy <= g_absorb_threshold)
			position += direction.GetNormalized() * gRandom->Exp(0.71*TMath::Power(energy, 1.72));
		else
			position += direction.GetNormalized() * gRandom->Exp((0.53*energy - 0.106));
		lcm_computed = true;
	}
	if(position.GetZ() < h + dh) //Se viene assorbita in questo intervallo
		return false;
	return true;
}

//---------------------------------------------------------------------------//

bool Particle::BSEmission(double h, double dh, Particle& out_gamma, int &counter, double& energy_lost) {
	if(energy > g_threshold[(int)ptype]) {
		if(old_position.GetZ() >= h && position.GetZ() < h + dh) { //Se la particella va spostata (non è uscita dalla cella precedente senza emettere)
			double lambda = gRandom->Exp(X0(this->ptype)/NGamma(this->energy, g_gamma_bs_min_energy, this->energy));
			old_position = position;
			position += direction.GetNormalized() * lambda;
		} else
			old_position = position;

		if(position.GetZ() >= h + dh) //Se emetterà nella cella successiva
			return false;

		double phi = gRandom->Rndm()*2.*TMath::Pi();
		double theta = g_masses[(int)PELECTRON]/energy;
		double r = h * TMath::Tan(theta);
		double gamma_energy = BSEnergy();
		direction += Vector3D(r, TMath::Pi()+phi, h, true);
		++counter;
		if(gamma_energy >= g_threshold_gamma){ //Se il gamma potrà fare coppia lo istanzio
			out_gamma =  Particle(PGAMMA, gamma_energy, Vector3D(r, phi, h) + direction.GetNormalized(), GetPositon(), false);
		} else { //Altrimenti assorbo subito l'energia
			out_gamma = Particle();
			energy_lost += gamma_energy;
		}
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------//

double Particle::BSEnergy() {
	//Metodo che estrae per inportance sampling l'energia del fotone emesso per bremsstrahlung
	double y, energy_gamma = 0.1*this->energy;

	do {
		do {
			energy_gamma = BSCrossSectionMajorInverse(gRandom->Rndm(), g_gamma_bs_min_energy, this->energy);
		} while (energy_gamma >= energy);
		y = gRandom->Rndm()*BSCrossSectionMajor(energy_gamma, this->energy);
	} while(y >= BSCrossSection(energy_gamma, this->energy));

	this->energy -= energy_gamma;
	return energy_gamma;
}

//---------------------------------------------------------------------------//

bool Particle::CoupleGeneration(double h, double dh, Particle& p1, Particle& p2,int& counter){
	if(this->energy > g_threshold[(int)PGAMMA]) {

		if(old_position.GetZ() >= h && position.GetZ() < h + dh) { //Se la particella non va spostata
			double lambda = (7./9.)*X0(this->ptype);
			old_position = position;
			position += direction.GetNormalized() * lambda;
		}
		if(position.GetZ() >= h + dh) //Se emetterà nella cella successiva
			return false;

		double phi = gRandom->Rndm()*2.*TMath::Pi();
		double theta = g_masses[(int)PELECTRON]/energy;
		double r = h * TMath::Tan(theta);
		p1 = Particle(PELECTRON, 0.5*energy, Vector3D(r, phi, h) + direction.GetNormalized(), GetPositon(), false);
		p2 = Particle(PPOSITRON, 0.5*energy, Vector3D(r, phi, h) + direction.GetNormalized(), GetPositon(), false);
		counter += 2;
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------//
