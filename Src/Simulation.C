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

double EMShower (double init_energy, int seed = 42, bool verbose = true) {
  vector<Particle> *all_particles = new vector<Particle>[2]();

  all_particles[0] = vector<Particle>();
  all_particles[1] = vector<Particle>();

  int bin_number = 500; //numero di celle degli istogrammi

  int counter = 0; //contatore delle particelle prodotte in questo step
  double h = 0.; //Unità di X0
  double dh = 0.1; //Unità di X0

  int max_k = 0;
  unsigned int max = 0.; //Variabili usate nel calcolo del massimo

  int id = 0, id2 = 1; //Indici usati per gestire i vector di particelle

  TH1D* particle_count = new TH1D("Particelle per strato atmosferico", "Particelle per strato atmosferico", bin_number, 0,bin_number*dh);
  particle_count->GetXaxis()->SetTitle("#tilde{x}_{0} [g/cm^{2}]");
  particle_count->GetXaxis()->SetTitleSize(0.045);
  particle_count->GetYaxis()->SetTitle("Numero di particelle");
  particle_count->GetYaxis()->SetTitleSize(0.045);

  TH1D* energy_loss = new TH1D("Energia rilasicata per strato atmosferico", "Energia rilasicata per strato atmosferico", bin_number, 0,bin_number*dh);
  energy_loss->GetXaxis()->SetTitle("#tilde{x}_{0} [g/cm^{2}]");
  energy_loss->GetXaxis()->SetTitleSize(0.045);
  energy_loss->GetYaxis()->SetTitle("(1/E_{0})dE/d#tilde{x}");
  energy_loss->GetYaxis()->SetTitleSize(0.045);

  double energy_lost_here = 0.0;

  //Gamma primario
  all_particles[0].push_back(Particle(PGAMMA, init_energy, Vector3D(0.,0.,1.), Vector3D(0.,0.,h), true));

  //Ciclo principale della simulazione
  for(int k = 1; k <= bin_number; k++) {
    if (verbose)
      cout << "Step #" << k;
    counter = 0;
    energy_lost_here = 0.0;
    id2 = (id+1)%2;
    for(unsigned int i = 0; i < all_particles[id].size(); i++) { //ciclo sulle particelle
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
        if(p.Propagate(h, dh)) {
          all_particles[id2].push_back(p); ///Valido se la particella non interagisce qui, ma dopo
        } else ///Valido se la particella è assorbita
          energy_lost_here += p.GetEnergy();
      }
    } //end for

    //Raccolgo i dati
    particle_count->SetBinContent(k,all_particles[id].size()); //particelle uscite da questo strato
    if(verbose)
      cout << " - Particelle: " << all_particles[id].size() << endl;
    if(all_particles[id].size() > max){  //aggiorno il punto di massimo
      max = all_particles[id].size();
      max_k = k;
    }
    energy_loss->SetBinContent(k,energy_lost_here/init_energy/dh); //energia persa in questo strato
    all_particles[id].clear();
    id = id2;
    h = h + dh;
  } //end for

  double max_point = max_k * dh; //calcolo il punto di massimo (in unità di X0)
  cout << "Punto di massimo: " << max_point << endl;

  //print dei dati
  if(verbose) {
    new TCanvas();
    particle_count->Draw();
    new TCanvas();
    energy_loss->Draw("histo");
  } else { //ripulisco la memoria, usato da ElongationFit (molte simulazioni consecutive)
    delete energy_loss;
    delete particle_count;
  }
  delete[] all_particles;

  return max_point; //punto di massimo della distribuzione
}

void ElongationFit(double Emin, double Emax, double increment, int seed = 42) {
  TRandom2 rnd(seed); //Generatore usato per estrarre i seed dati alle singole simulazioni
  //Usiamo un generatore di tipo diverso per evitare di ridurre il periodo del generatore primario

  const int samples = 10; //dimensione dei campioni

  TH1D *data = new TH1D("Elongation Rate", "Elongation Rate", 10000, TMath::Log10(Emin), TMath::Log10(Emax));
  data->GetXaxis()->SetTitle("Log_{10}(E_{0})");
  data->GetXaxis()->SetTitleSize(0.045);
  data->GetYaxis()->SetTitle("#tilde{x}_{0}^{max} [g/cm^{2}]");
  data->GetYaxis()->SetTitleSize(0.045);

  double energy = Emin;
  int bin = 1;
  while(energy < Emax) {
    double mean = 0, stdev = 0, raws[samples];

    cout << "E: " << energy << endl;
    bin = data->GetXaxis()->FindBin(TMath::Log10(energy));
    for(int i = 0; i < samples; i++) {
      raws[i] = EMShower(energy, rnd.Rndm(), false);
      mean += raws[i]/samples;
    }

    for(int i = 0; i < samples; i++) {
      stdev = (mean - raws[i])*(mean - raws[i])/(samples - 1);
    }

    data->SetBinContent(bin,mean);
    data->SetBinError(bin,stdev);
    energy += increment*energy;
  }

  new TCanvas();
  gStyle->SetOptFit(1);
  data->SetMarkerStyle(20);
  data->Draw("pe");
  data->Fit("pol1");
}
