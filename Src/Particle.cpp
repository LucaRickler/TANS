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
		this->energy_extractor = InportanceRandom(BSCrossSection, NULL, BSCrossSectionMajor, NULL, BSCrossSectionMajorInverse, NULL);
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
		this->energy_extractor = InportanceRandom(BSCrossSection, NULL, BSCrossSectionMajor, NULL, BSCrossSectionMajorInverse, NULL);
}

//---------------------------------------------------------------------------//

bool Particle::Divide(double h, double dh, vector<Particle>& p1, Particle& p2){
		if(energy > g_threshold[(int)ptype]){
			if(ptype == PGAMMA){
				Particle electron, bs_gamma;
				Particle dummy;
				if(CoupleGeneration(h,dh,electron,p2)){
					p1.push_back(electron);
					electron.Divide(h,dh,p1,dummy); //loro potrebbero fare BS in [h,h+dh], devo farlo loro fare
					p2.Divide(h,dh,p1,dummy);
					return true;
				}
			} else {
				Particle bs_gamma; //Questo gamma potrebbe fare coppia in [h,h+dh], dobbiamo considerarlo
				bool return_state = false;
				while(BSDecay(h,dh,bs_gamma)) {
					//if(!bs_gamma.Divide(h,dh,p1,p2))
						p1.push_back(bs_gamma); //Caso senza produzione di coppia
					//else {
					//	p1.push_back(p2); //Caso con produzione di coppia. Il primo e- viene già inserito dentro p1 da Divide()
					//}
					return_state = true;
				}
				//p2 = NULL;

				return return_state;
			}

			//return true;
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

bool Particle::BSDecay(double h, double dh, Particle& out_gamma) {
	if(energy > g_threshold[(int)ptype]) {
		if(old_position.GetZ() > h) {
			double lambda = gRandom->Exp(1.);
			old_position = position;
			position += direction.GetNormalized() * lambda;
		} else
			old_position = position;

		if(position.GetZ() >= h + dh)
			return false;

		double phi = gRandom->Rndm()*2.*TMath::Pi();
		double theta = (g_masses[(int)ptype]*g_c2)/energy;
		double r = h * TMath::Tan(theta);
		double gamma_energy = BSEnergy();
		direction += Vector3D(r, TMath::Pi()+phi, h, true);
		out_gamma = Particle(PGAMMA, gamma_energy, Vector3D(r, phi, h) + direction.GetNormalized(), GetPositon(), false);
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------//

double Particle::BSEnergy() {
	double *args_f = new double[1];
	*args_f = this->energy;

	double *args_f_inv = new double[2];
	args_f_inv[0] = g_gamma_bs_min_energy;
	args_f_inv[1] = this->energy;
	energy_extractor.SetFArgs(args_f,NULL,args_f_inv);

	double energy_gamma;
	do {
		 energy_gamma = energy_extractor.Rndm();
	} while (energy_gamma >= this->energy);
	this->energy -= energy_gamma;
	return energy_gamma;
}

//---------------------------------------------------------------------------//

bool Particle::CoupleGeneration(double h, double dh, Particle& p1, Particle& p2){
	if(this->energy > g_threshold[(int)PGAMMA]) {

		if(old_position.GetZ() > h) {
			double lambda = gRandom->Exp(1.);
			old_position = position;
			position += direction.GetNormalized() * lambda;
		} else
			old_position = position;

		if(position.GetZ() > h + dh)
			return false;

		double phi = gRandom->Rndm()*2.*TMath::Pi();
		double theta = TMath::Exp(TMath::Log(g_masses[(int)PELECTRON]) + TMath::Log(g_c2) - TMath::Log(energy));
		double r = h * TMath::Tan(theta);
		//new Particle(PPOSITRON, 0.5*energy, Vector3D(r, TMath::Pi()+phi, h) + direction.GetNormalized(), GetPositon(), false);
		p1 =  Particle(PELECTRON, 0.5*energy, Vector3D(r, phi, h) + direction.GetNormalized(), GetPositon(), false);
		p2 =  Particle(PELECTRON, 0.5*energy, Vector3D(r, phi, h) + direction.GetNormalized(), GetPositon(), false);
		//if(!p1) printf("Error\n");
		//if(!p2) printf("Error\n");
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------//
