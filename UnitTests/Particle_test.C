#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include "../Src/Particle.h"
#endif

void ParticleTest (int seed = 42) {
  gRandom->SetSeed(seed);
  const int samples = 1.e6;

  double Emin = g_threshold_gamma;
  double Emax = 1.e8;
  TH1D* couple_production_theta = new TH1D("Gamma Couple Production Theta", "Gamma Couple Production Theta", 1000, Emin, Emax);
  TH1D* couple_production_energy = new TH1D("Gamma Couple Production Energy", "Gamma Couple Production Energy", 1000, Emin, Emax);
  TCanvas *couple_production_canvas_theta = new TCanvas();
  TCanvas *couple_production_canvas_energy = new TCanvas();

  double step = (Emax - Emin) / samples;
  Particle* gamma, *p2;
  vector<Particle*> p1;
  for(double E = Emin; E < Emax; E+=step){
    gamma = new Particle(PGAMMA, E, Vector3D(0.,0.,0), Vector3D(0.,0.,0), true);
    gamma->Divide(0,0,p1,p2);
    if(p2) {
      couple_production_theta->Fill(p2->GetDirection().GetTheta());
      couple_production_energy->Fill(p2->GetEnergy());
      delete p2;
      delete p1[0];
    }
    delete gamma;
  }

  couple_production_canvas_theta->cd();
  couple_production_canvas_theta->SetLogx();
  couple_production_theta->Draw();

  couple_production_canvas_energy->cd();
  couple_production_canvas_energy->SetLogx();
  couple_production_energy->Draw();

}
