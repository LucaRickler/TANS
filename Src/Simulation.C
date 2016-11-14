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

double ComputeH(double h) {
  return 0.;
}

void EMShower (int seed = 42, double init_energy) {
  vector<Particle*> *all_particles = new vector<Particle*>[2]();

  all_particles[0] = vector<Particle*>();
  all_particles[1] = vector<Particle*>();

  double h = 0.;
  double dh = 0.;
  ComputeH(dh);
  all_particles[0].push_back(new Particle(PGAMMA, init_energy, Vector3D(0.,0.,dh), Vector3D(0.,0.,h), true));

  int id = 0, id2 = 1;
  while (all_particles[id].size() > 0) {
    h = ComputeH(dh);
    id2 = (id+1)%2;
    for(int i = 0; i < all_particles[id].size(); i++) {
      vector<Particle*> p1;
      Particle *p2, *p = all_particles[id][i];
      if(p->Divide(h, p1, p2)){
        all_particles[id2].push_back(p1); //modifica
        if(p2 != NULL) {
          all_particles[id2].push_back(p2);
          delete p;
        } else {
          all_particles[id2].push_back(p);
        }
      }
    }
    //Raccolgo i dati
    all_particles[id].clear();
    id = id2;
  }

  //print dei dati
}
