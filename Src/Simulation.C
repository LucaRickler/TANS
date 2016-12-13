#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1D.h>
#include <TF1.h>
#include <TRandom3.h>
#include <TRandom2.h>
#include <TStyle.h>
#include <TString.h>
#include <TVector.h>
#include "Particle.h"
#endif

void EMShower (double init_energy, double &max_point, int seed = 42, bool print = true) {
  vector<Particle> *all_particles = new vector<Particle>[2]();

  const int max_particles = 1.e7;

  all_particles[0] = vector<Particle>();
  all_particles[1] = vector<Particle>();

  int bin_number = 500;

  int counter = 0;
  double h = 0.;
  double dh = 0.1;

  int max_k = 0;
  unsigned int max = 0.;
  int id = 0, id2 = 1;

  TH1D* particle_count = new TH1D("Particelle per strato atmosferico", "Particelle per strato atmosferico", bin_number, 0,bin_number*dh);
  TH1D* energy_loss = new TH1D("Energia rilasicata per strato atmosferico", "Energia rilasicata per strato atmosferico", bin_number, 0,bin_number*dh);
  double energy_lost_here = 0.0;
  all_particles[0].push_back(Particle(PGAMMA, init_energy, Vector3D(0.,0.,1.), Vector3D(0.,0.,h), true));

  for(int k = 1; k <= bin_number; k++) {
    if (print)
      cout << "Ciclo #" << k << endl;
    counter = 0;
    energy_lost_here = 0.0;
    id2 = (id+1)%2;
    for(unsigned int i = 0; i < all_particles[id].size(); i++) {
      vector<Particle> p1;
      Particle p = all_particles[id][i];
      if(p.Divide(h, dh, p1,counter,energy_lost_here)){
        for(unsigned int j = 0; j < p1.size(); j++) {
          all_particles[id2].push_back(p1[j]);
        }
        if(p.GetPType() != PGAMMA) {
          all_particles[id2].push_back(p);
        }
      } else {
        if(p.Propagate(h, dh)) { // ->
          all_particles[id2].push_back(p); ///Valido se la particella non interagisce qui, ma dopo
        } else ///Valido se la particella è assorbita
          energy_lost_here += p.GetEnergy(); // ->
      }
    }
    //Raccolgo i dati
    particle_count->SetBinContent(k,all_particles[id].size());
    if(all_particles[id].size() > max){
      max = all_particles[id].size();
      max_k = k;
    }
    energy_loss->SetBinContent(k,energy_lost_here/init_energy);
    all_particles[id].clear();
    id = id2;
    h = h + dh;
  }

  max_point = max_k * dh;

  cout << "Punto di massimo: " << max_point << endl;
  //print dei dati
  if(print) {
    new TCanvas();
    particle_count->DrawCopy();
    new TCanvas();
    //energy_loss->Scale(1./energy_loss->Integral(), "width");
    energy_loss->DrawCopy("histo");
  } else {
    delete energy_loss;
    delete particle_count;
  }
  delete[] all_particles;
}

void ElongationFit(double Emin, double Emax, double increment, int seed = 42) {
  TRandom2 rnd(42);

  const int samples = 10;

  TH1D *data = new TH1D("Elongation Rate", "Elongation Rate", 10000, TMath::Log10(Emin), TMath::Log10(Emax));

  double energy = Emin;
  int bin = 1;
  while(energy < Emax) {
    double mean = 0, stdev = 0, raws[samples];

    cout << "E: " << energy << endl;
    bin = data->GetXaxis()->FindBin(TMath::Log10(energy));
    for(int i = 0; i < samples; i++) {
      EMShower(energy, raws[i], rnd.Rndm(), false);
      mean += raws[i]/samples;
    }

    for(int i = 0; i < samples; i++) {
      stdev = (mean - raws[i])*(mean - raws[i])/(samples - 1);
    }

    data->SetBinContent(bin,mean);
    data->SetBinError(bin,stdev);
    energy *= increment;
  }

  new TCanvas();
  data->SetMarkerStyle(20);
  data->Draw("p");
  data->Fit("pol1");
}
