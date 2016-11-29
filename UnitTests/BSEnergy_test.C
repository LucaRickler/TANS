#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TH2D.h>
#include <TF1.h>
#include <TCanvas.h>
#include "../Src/Particle.h"
#include <Riostream.h>
#endif

void TestEnergy(double E, int seed = 42) {
  gRandom->SetSeed(seed);
  const int samples = 1.e6;

  double Emin = g_threshold_gamma;
  double Emax = 1.e8;

  double step = (E - Emin) / 1000;

  double *args_f = new double[1];
  *args_f = E;

  double *args_f_big = new double[1];
  *args_f_big = E;

  double *args_f_inv = new double[2];
  args_f_inv[0] = g_gamma_bs_min_energy;
  args_f_inv[1] = E;
  InportanceRandom rnd = InportanceRandom(BSCrossSection, args_f, BSCrossSectionMajor, args_f_big, BSCrossSectionMajorInverse, args_f_inv);

  char title[50];
  sprintf(title,"E: %e", E);
  TH1D* h = new TH1D(title, title, 10000, Emin, E);


  for(int i = 0; i < samples; i++)
    h->Fill(rnd.Rndm());

  TH1D* exact = new TH1D("exact", "exact", 10000, Emin, E);
  for(int i = 0; i < 10000; i++){
    double x = (Emin + (0.5 + i)*step);
    exact->SetBinContent(i,BSCrossSection(&x,&E));
  }

  h->Scale(1./h->Integral(), "width");
  TCanvas* canvas = new TCanvas();
  canvas->SetLogx();
  canvas->SetLogy();
  h->DrawCopy("histo");

  exact->Scale(1./exact->Integral(), "width");
  exact->Draw("histosame");

}
