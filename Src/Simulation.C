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

double ComputeH(double h,double& dh) {
  return h + dh;
}

void EMShower (double init_energy, int seed = 42) {
  vector<Particle> *all_particles = new vector<Particle>[2]();

  all_particles[0] = vector<Particle>();
  all_particles[1] = vector<Particle>();
  TH1D* particle_count = new TH1D("Particelle per strato atmosferico", "Particelle per strato atmosferico", 10, 0,10);

  int counter = 0;
  double h = 0.;
  double dh = 1.;
  //ComputeH(dh);
  all_particles[0].push_back(Particle(PGAMMA, init_energy, Vector3D(0.,0.,dh), Vector3D(0.,0.,h), true));

  int id = 0, id2 = 1;
  //while (all_particles[id].size() > 0) {
  while (h < 10) {
    id2 = (id+1)%2;
    for(int i = 0; i < all_particles[id].size(); i++) {
      vector<Particle> p1;
      Particle p2, p = all_particles[id][i];
      if(p.Divide(h, dh, p1, p2, counter)){
        for(int j = 0; j < p1.size(); j++)
          all_particles[id2].push_back(p1[j]);
        if(p2.GetEnergy() != 0.) {
          all_particles[id2].push_back(p2);
          //delete p;
        } else {
          all_particles[id2].push_back(p);
        }
      } else {
        /*if(p.Propagate(h))
          all_particles[id2].push_back(p);
        else
          delete p;*/
      }
    }
    //Raccolgo i dati
    particle_count->SetBinContent(h,all_particles[id2].size());
    all_particles[id].clear();
    id = id2;
    h = ComputeH(h,dh);
  }

  //print dei dati
  particle_count->Draw();
}
