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

Particle::Particle(PType ptype, double energy, const Vector3D& direction, const Vector3D& position, bool primary){
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

bool Particle::Divide(double h, double dh, vector<Particle>& p1, Particle& p2, int& counter, double& energy_lost){
		if(energy > g_threshold[(int)ptype]){
			if(ptype == PGAMMA){
				Particle electron, bs_gamma;
				Particle dummy;
				if(CoupleGeneration(h,dh,electron,p2,counter)){
					p1.push_back(electron);
					electron.Divide(h,dh,p1,dummy,counter,energy_lost); //loro potrebbero fare BS in [h,h+dh], devo farlo loro fare
					p2.Divide(h,dh,p1,dummy,counter,energy_lost);
					return true;
				}
			} else {
				Particle bs_gamma; //Questo gamma potrebbe fare coppia in [h,h+dh], dobbiamo considerarlo
				bool return_state = false;
				while(BSEmission(h,dh,bs_gamma,counter,energy_lost)) {
					if(bs_gamma.GetEnergy() != 0.) {
						if(!bs_gamma.Divide(h,dh,p1,p2,counter,energy_lost)) {
							p1.push_back(bs_gamma); //Caso senza produzione di coppia
						} else {
							p1.push_back(p2); //Caso con produzione di coppia. Il primo e- viene già inserito dentro p1 da Divide()
							//--counter;
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
	if(energy > g_threshold[(int)ptype])
		return true;
	if(ptype == PGAMMA)
		return false;
	if(!lcm_computed){
		old_position = position;
		if(energy <= g_absorb_threshold)
			position += direction.GetNormalized() * 0.71*TMath::Power(energy, 1.72);
		else
			position += direction.GetNormalized() * (0.53*energy - 0.106);
		lcm_computed = true;
	}
	if(position.GetZ() > h + dh)
		return false;
	return true;
}

//---------------------------------------------------------------------------//

bool Particle::BSEmission(double h, double dh, Particle& out_gamma, int &counter, double& energy_lost) {
	if(energy > g_threshold[(int)ptype]) {
		if(old_position.GetZ() >= h && position.GetZ() < h + dh) {
			double lambda = X0(this->ptype)/NGamma(this->energy, g_gamma_bs_min_energy, this->energy);
			old_position = position;
			position += direction.GetNormalized() * lambda;
		} else
			old_position = position;

		if(position.GetZ() >= h + dh)
			return false;

		double phi = gRandom->Rndm()*2.*TMath::Pi();
		double theta = g_masses[(int)PELECTRON]/energy;
		double r = h * TMath::Tan(theta);
		double gamma_energy = BSEnergy();
		direction += Vector3D(r, TMath::Pi()+phi, h, true);
		++counter;
		if(gamma_energy >= g_threshold_gamma){
			out_gamma =  Particle(PGAMMA, gamma_energy, Vector3D(r, phi, h) + direction.GetNormalized(), GetPositon(), false);
		} else
			out_gamma = Particle();
			energy_lost += gamma_energy;
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------//

double Particle::BSEnergy() {
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

		if(old_position.GetZ() >= h && position.GetZ() < h + dh) {
			double lambda = (7./9.)*X0(this->ptype);
			old_position = position;
			position += direction.GetNormalized() * lambda;
		}
		if(position.GetZ() >= h + dh)
			return false;

		double phi = gRandom->Rndm()*2.*TMath::Pi();
		double theta = g_masses[(int)PELECTRON]/energy;
		double r = h * TMath::Tan(theta);
		p1 = Particle(PELECTRON, 0.5*energy, Vector3D(r, phi, h) + direction.GetNormalized(), GetPositon(), false);
		p2 = Particle(PELECTRON, 0.5*energy, Vector3D(r, phi, h) + direction.GetNormalized(), GetPositon(), false);
		counter += 2;
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------//
