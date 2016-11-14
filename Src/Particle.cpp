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
}

//---------------------------------------------------------------------------//

bool Particle::Divide(double h, vector<Particle*>& p1, Particle* p2){

		if(energy > g_threshold[(int)ptype]){

			double phi = gRandom->Rndm()*2.*TMath::Pi();
			double theta = 0.;
			double r = h * TMath::Sin(theta);
			if(ptype == PGAMMA){
				theta = (g_masses[(int)PELECTRON]*g_c2)/energy;
				p1.push_back(new Particle(PELECTRON, 0.5*energy, Vector3D(r, phi, h) + direction.GetNormalized(), GetPositon(), false));
				p2 = new Particle(PPOSITRON, 0.5*energy, Vector3D(r, TMath::Pi()+phi, h) + direction.GetNormalized(), GetPositon(), false);
			}
			else{
				if(energy > g_threshold[(int)ptype]){
					theta = (g_masses[(int)ptype]*g_c2)/energy;
					p1.push_back(new Particle(PGAMMA, 0.5*energy, Vector3D(r, phi, h) + direction.GetNormalized(), GetPositon(), false));
			  	p2 = NULL;
					energy *= 0.5;
					direction += Vector3D(r, TMath::Pi()+phi, h, true);
				}
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
