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

bool Particle::Divide(double h, Particle* p1, Particle* p2){

/*
 *   Ho modificato un po' quanto mi avevi suggerito di fare! In particolare ora
 *   vedo prima se la soglia più bassa viene raggiunta (ovvero quella necessaria
 *   per la produzione di coppie: 10 MeV) perché, se non è raggiunta questa, non
 *   verrà raggiunta neanche quella più alta (bremsstrahlung: 88 MeV).
 *   Se è raggiunta, vedo se p1 è un gamma o no. Se NON è un gamma devo porre
 *   allora la soglia per la bremsstrahlung (che è più alta). Ho fatto queste
 *   modifiche perché come avevi suggerito tu non si teneva in conto il fatto
 *   che threshold_g != threshold_ep.
 */

		if(p1->energy > threshold_g){

			double phi = gRandom->Rndm()*2.*TMath::Pi();
			double theta = 0.;
			double r = h * TMath::Sin(theta);
			if(p1->ptype == PGAMMA){
				//theta = ...
				p1 = new Particle(PELECTRON, 0.5*energy, Vector3D(r, phi, h) + direction.GetNormalized(), GetPositon(), false);
				p2 = new Particle(PPOSITRON, 0.5*energy, Vector3D(r, TMath::Pi()+phi, h) + direction.GetNormalized(), GetPositon(), false);
			}
			else{
				if(p1->energy > threshold_ep){
					//theta = ...
					p1 = new Particle(PGAMMA, 0.5*energy, Vector3D(r, phi, h) + direction.GetNormalized(), GetPositon(), false);
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
