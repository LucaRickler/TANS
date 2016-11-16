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
		this->lcm = 0.;
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
		this->is_primary = primary;
		this->lcm = 0.;
		this->delta_pos = Vector3D();
		//CONTROLLA CHE XMIN ABBIA SENSO
		this->energy_extractor(BSCrossSection, NULL, 0., energy, BSCrossSectionMajor, NULL, BSCrossSectionMajorInverse, NULL);
}

//---------------------------------------------------------------------------//

bool Particle::Divide(double h, double dh, vector<Particle*>& p1, Particle* p2){

		if(energy > g_threshold[(int)ptype]){
			double theta = 0.;
			double r = h * TMath::Tan(theta);
			if(ptype == PGAMMA){
				double phi = gRandom->Rndm()*2.*TMath::Pi();
				theta = (g_masses[(int)PELECTRON]*g_c2)/energy;
				p1 = new Particle*();
				*p1 = new Particle(PELECTRON, 0.5*energy, Vector3D(r, phi, h) + direction.GetNormalized(), GetPositon(), false);
				n_p1 = 1;
				p2 = new Particle(PPOSITRON, 0.5*energy, Vector3D(r, TMath::Pi()+phi, h) + direction.GetNormalized(), GetPositon(), false);
			}
			else{
				Particle* bs_gamma;
				while(BSDecay(h,dh,bs_gamma))
					p1.push_back(bs_gamma);
				p2 = NULL;

			}

			return true;
		}

 		return false;
}

//---------------------------------------------------------------------------//

bool Particle::Propagate(double h){
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

bool Particle::BSDecay(double h, double dh, Particle* out_gamma) {
	if(energy > g_threshold[(int)ptype]) {

		if(old_position.GetZ() > h) {
			double lambda = gRandom->Exp(1.);
			old_position = position;
			position += direction.GetNormalized() * lambda;
			if(position.GetZ() > h + dh)
				return false;
		} else
			old_position = position;

		double phi = gRandom->Rndm()*2.*TMath::Pi();
		double theta = (g_masses[(int)ptype]*g_c2)/energy;
		double gamma_energy = BSEnergy();
		direction += Vector3D(r, TMath::Pi()+phi, h, true);
		out_gamma = new Particle(PGAMMA, gamma_energy, Vector3D(r, phi, h) + direction.GetNormalized(), GetPositon(), false);
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------//

double Particle::BSEnergy() {
	double *args = new double[1];
	*args = this->energy;
	energy_extractor.SetFArgs(args,NULL,NULL);

	//CONTROLLA CHE XMIN ABBIA SENSO
	energy_extractor.SetInterval(0., this->energy);

	double energy_gamma = energy_extractor.Rndm();

	this->energy -= energy_gamma;
	return energy_gamma;
}

//---------------------------------------------------------------------------//
