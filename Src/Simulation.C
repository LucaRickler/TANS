#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TRandom3.h>
#include <TStyle.h>
#include <TString.h>
#include <TVector.h>
#include <TClonesArray.h>
#include "Particle.h"
//#include "Presentation.h"
#endif

void EMShower (double init_energy, int seed = 42) {
  vector<Particle> *all_particles = new vector<Particle>[2]();

  const int max_particles = 1.e7;

  all_particles[0] = vector<Particle>();
  all_particles[1] = vector<Particle>();

  /*TClonesArray *all_particles = new TClonesArray[2];

  all_particles[0] = TClonesArray("Particle", max_particles);
  all_particles[1] = TClonesArray("Particle", max_particles);*/

  int bin_number = 100;

  int counter = 0;
  double h = 0.;
  double dh = 0.1;

  int max_k = 0;
  int max = 0.;
  int id = 0, id2 = 1, size, old_size;

  TH1D* particle_count = new TH1D("Particelle per strato atmosferico", "Particelle per strato atmosferico", bin_number, 0,bin_number*dh);
  TH1D* energy_loss = new TH1D("Energia rilasicata per strato atmosferico", "Energia rilasicata per strato atmosferico", bin_number, 0,bin_number*dh);
  double energy_lost_here = 0.0;
  all_particles[0].push_back(Particle(PGAMMA, init_energy, Vector3D(0.,0.,1.), Vector3D(0.,0.,h), true));
  //size = old_size = all_particles[0].AddAtFree(new Particle(PGAMMA, init_energy, Vector3D(0.,0.,1.), Vector3D(0.,0.,h), true));

  for(int k = 1; k <= bin_number; k++) {
    cout << "Ciclo #" << k << endl;
    counter = 0;
    energy_lost_here = 0.0;
    id2 = (id+1)%2;
    //old_size = size + 1;
    //size = 0;
    for(int i = 0; i < all_particles[id].size(); i++) {//old_size; i++) {//
      vector<Particle> p1;
      Particle p2, p = all_particles[id][i];//*p = (Particle*)all_particles[id][i];
      if(p.Divide(h, dh, p1, p2, counter,energy_lost_here)){ // ->
        for(int j = 0; j < p1.size(); j++)
          //size = all_particles[id2].AddAtFree(new Particle(p1[j]));
          all_particles[id2].push_back(p1[j]);
        if(p2.GetEnergy() != 0.) {
          //size = all_particles[id2].AddAtFree(new Particle(p2));
          //delete p;
          all_particles[id2].push_back(p2);
        } else {
          //size = all_particles[id2].AddAtFree(p);
          all_particles[id2].push_back(p);
        }
        if(p.GetPType() != PGAMMA)
          //size = all_particles[id2].AddAtFree(p);
          all_particles[id2].push_back(p);
      } else {
        if(p.Propagate(h, dh)) // ->
          //size = all_particles[id2].AddAtFree(p);
          all_particles[id2].push_back(p);
        else
          energy_lost_here += p.GetEnergy(); // ->
          //delete p;
      }
    }
    //Raccolgo i dati
    //particle_count->SetBinContent(k,old_size);
    //if(size > max){
      //max = size;
    particle_count->SetBinContent(k,all_particles[id].size());
    if(all_particles[id].size() > max){
      max = all_particles[id].size();
      max_k = k;
    }
    energy_loss->SetBinContent(k,energy_lost_here);
    //all_particles[id].Clear();
    all_particles[id].clear();
    //all_particles[id].reserve(max_particles);
    id = id2;
    h = h + dh;
  }

  cout << "Punto di massimo: " << max_k * dh << endl;
  //print dei dati
  new TCanvas();
  particle_count->Draw();
  new TCanvas();
  energy_loss->Draw();
}
