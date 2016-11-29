#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include "../Src/InportanceRandom.h"
#endif

double f(double *x, double *par) {
  return x[0]*x[0];
}

double g(double *x, double *par) {
  return x[0];
}

double h(double *x, double *par) {
  return TMath::Sqrt(x[0]);
}

void InportanceTest (int seed = 42) {
  gRandom->SetSeed(seed);
  double xmin = 0., xmax = 1.;
  TH1D *histo = new TH1D("Inportance Random", "Inportance Random", 100, xmin, xmax);
  TF1 *exact = new TF1("Exact", f, xmin, xmax);

  int samples = 1.e6;
  double step = (xmax - xmin) /100;

  InportanceRandom rng = InportanceRandom(f,NULL,g,NULL,h,NULL);
  rng.SetFArgs(NULL,NULL,NULL);

  for(int i = 0; i < samples; i++)
    histo->Fill(rng.Rndm());

  histo->Scale(1./3./samples/step);
  histo->Draw();
  exact->Draw("same");

}
