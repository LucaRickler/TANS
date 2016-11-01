#ifndef PARTICLE_H_
#define PARTICLE_H_

enum PType{
	PGAMMA = 1,
	PELECTRON,
	PPOSITRON} ptype;

class Particle{

	public:
		Particle(PType ptype, double penergy, bool pprimary); //(const Vector3D&, double theta);
		void PFeatures(PType ptype, double penergy, bool pprimary);
		vector<Particle*> Divide(PType ptype, double penergy, bool pprimary);
		double GetEnergy();

	private:
		vector<Particle*> pall_particles;
		double penergy;
		bool pprimary;
		double pthreshold_g;
		double pthreshold_ep;
		Vector3D pold_position;
		Vector3D pposition;
		PType ptype;
};


#endif /* PARTICLE_H_ */
