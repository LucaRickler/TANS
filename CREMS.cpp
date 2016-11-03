#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TRandom3.h>
#include <TStyle.h>
#include <TMath.h>
#include <TString.h>
#include <TVector.h>
#include "Vector3D.cpp"
#include "Particle.cpp"
#include "Presentation.cpp"
#endif

void EMShower(unsigned int seed = 1234){

	double energy = 0.;
	int inputParticle = 1;
  int n = 0;
	vector<Particle*> all_particles;

	Presentation Intro;
	Intro.Pres1();

	do{
		cout<< "Choose the primary cosmic ray between Gamma, Electron, Positron:\n";
		Intro.Pres2();
		cin>> inputParticle;
		ptype = static_cast<PType>(inputParticle);}
			while(ptype != PGAMMA && ptype != PELECTRON && ptype != PPOSITRON);

	cout<< "Choose the primary cosmic ray energy E0(GeV): ";
	cin>>energy;
	cout<<endl;

  cout<< "------------------------- n = " << n <<endl;
	bool primary = true;
	Particle *p = new Particle(ptype, energy, primary);
	p->PFeatures(ptype, energy, primary);
	all_particles.push_back(p);
	cout<< "Particles in the shower: " << all_particles.size() <<endl;
	primary = false;
  n++;//--------------------------------------------------------------------

  for(unsigned int i = 0; i < all_particles.size(); i++){
    cout<< "------------------------- n = " << n <<endl;
    all_particles = p->Divide(ptype, energy, primary);
    if(n != 1)
      all_particles.erase(all_particles.begin()+i-1);
    energy = p->GetEnergy();
  	cout<< "Particles in the shower: " << all_particles.size() <<endl;
    n++;//--------------------------------------------------------------------
  }


//Check class Vector3D
	Vector3D v1(1., 2., 3.);
	Vector3D v2(2., 3., 4.);
	cout<< "Prodotto scalare: " << Vector3D::Dot(v1, v2) <<endl;

}
/*
  //Check dot product
	Vector3D vec1;
	double scalar_product = vec1.Dot(v1, v2);
	cout<< "v1 * v2 = " << scalar_product <<endl;

	//Check cross product
	Vector3D vec2;
	vector<double> cross_product = vec2.Cross(v1, v2);
	cout<< "v1 x v2 = (";
	for(UInt_t i = 0; i < cross_product.size(); i++){
		if(i == 0 || i == 1)
		cout<< cross_product.at(i) << ", ";
		else
		cout<< cross_product.at(i) << ")";}
	cout<<endl;

	//Check product by scalar
	Vector3D vec3;
	vector<double> by_scalar = vec3.ScalarMultiplication(l, v1);
	cout<< "v1 * l = (";
	for(UInt_t i = 0; i < by_scalar.size(); i++){
		if(i == 0 || i == 1)
		cout<< by_scalar.at(i) << ", ";
		else
		cout<< by_scalar.at(i) << ")";}
	cout<<endl;
*/
