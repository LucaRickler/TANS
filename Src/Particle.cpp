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
		this->current_position = 0.;
}

//---------------------------------------------------------------------------//

Particle::Particle(PType ptype, double energy, const Vector3D& direction, const Vector3D& position, bool primary){
		if(ptype == NUMBER_OF_PARTICLES)
			ptype = PGAMMA;
		this->ptype = ptype;
	  this->energy = (energy >= 0.0 ? energy : 0.0);
		this->direction = direction;
		this->position = position;
		this->is_primary = primary;
		this->current_position = position.GetZ();
}

//---------------------------------------------------------------------------//

bool Particle::Divide(double h, double dh, Particle** p1, int& n_p1, Particle* p2){

		if(energy > g_threshold[(int)ptype]){
			double phi = gRandom->Rndm()*2.*TMath::Pi();
			double theta = 0.;
			double r = h * TMath::Tan(theta);
			if(ptype == PGAMMA){
				theta = (g_masses[(int)PELECTRON]*g_c2)/energy;
				p1 = new Particle*();
				*p1 = new Particle(PELECTRON, 0.5*energy, Vector3D(r, phi, h) + direction.GetNormalized(), GetPositon(), false);
				n_p1 = 1;
				p2 = new Particle(PPOSITRON, 0.5*energy, Vector3D(r, TMath::Pi()+phi, h) + direction.GetNormalized(), GetPositon(), false);
			}
			else{
				n_p1 = NumberOfPhotonsBS(h, dh);
				p1 = new Particle*[n_p1]();
				for(int i = 0; i < n_p1; i++) {
					theta = (g_masses[(int)ptype]*g_c2)/energy;
					double gamma_energy = BSEnergy();
					p1[i] = new Particle(PGAMMA, gamma_energy, Vector3D(r, phi, h) + direction.GetNormalized(), GetPositon(), false);
				}
				p2 = NULL;
				energy *= 0.5;
				direction += Vector3D(r, TMath::Pi()+phi, h, true);
			}

			return true;
		}

 		return false;
}

//---------------------------------------------------------------------------//

bool Particle::Propagate(double h){
	 static Vector3D delta_pos;
	 static double lcm = 0.;
	 if(lcm == 0.)
	 	lcm = LCM(h,position.GetZ());
	 old_position = position;
	 position += direction;
	 delta_pos += position - old_position;
	 if(delta_pos.GetNorm() > lcm)
		 return false;
	 return true;
}

//---------------------------------------------------------------------------//

double Particle::LCM(double h, double z_top) {
	return 0.;
}

//---------------------------------------------------------------------------//

int Particle::NumberOfPhotonsBS(double h, double dh) {
	int n = 0;
	while ((current_position += gRandom->Exp(0.)) < (h + dh)/TMath::Cos(direction.GetTheta()))
		n++;
	return n;
}

//---------------------------------------------------------------------------//
double Particle::BSEnergy() {
	return 0.;
}

//---------------------------------------------------------------------------//
