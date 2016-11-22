#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include "../Src/Particle.h"
#endif

void TestParticle (int seed = 42) {
  gRandom->SetSeed(seed);
  const int samples = 1000;

  double Emin = g_threshold_gamma;
  double Emax = 1.e8;
  TH1D* couple_production_theta = new TH1D("Gamma Couple Production Theta", "Gamma Couple Production Theta", 1000, 0., 1.5);
  TH1D* couple_production_energy = new TH1D("Gamma Couple Production Energy", "Gamma Couple Production Energy", 1000, Emin, Emax);
  TCanvas *couple_production_canvas_theta = new TCanvas();
  TCanvas *couple_production_canvas_energy = new TCanvas();

  double step = (Emax - Emin) / samples;
  for(double E = Emin; E < Emax; E*=1.5){
    Particle gamma, p2;
    vector<Particle> p1 = vector<Particle>();
    gamma = Particle(PGAMMA, E, Vector3D(0.,0.,1), Vector3D(0.,0.,1), true);
    printf("E: %e\n", E);
    bool state = gamma.Divide(-1,100,p1,p2);
    if(state) {
      for (int i = 0; i < p1.size(); i++) {
        cout << "p1[" << i << "]: theta " << p1[i].GetDirection().GetTheta() << ", E " << p1[i].GetEnergy() << endl;
        couple_production_theta->Fill(p1[i].GetDirection().GetTheta());
        couple_production_energy->Fill(p1[i].GetEnergy());
        //if(p2) delete p2;
        //if(p1[0]) delete p1[0];
        //delete &(p1[i]);
      }
      //p1.clear();
    }
  //  delete gamma;
  }

  couple_production_canvas_theta->cd();
  //couple_production_canvas_theta->SetLogx();
  couple_production_theta->Draw();

  couple_production_canvas_energy->cd();
  couple_production_canvas_energy->SetLogx();
  couple_production_energy->Draw();

}
