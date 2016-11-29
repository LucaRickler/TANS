#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include "../Src/Constants.h"
#include <TMath.h>
#include <Riostream.h>
#endif

double NGamma(double*x, double*par) {
  return x[0]*(4./3. * TMath::Log(par[1]/par[0] - 4.*(par[1] - par[0])/3./par[2] + 0.5*(par[1]*par[1] - par[0]*par[0])/par[2]/par[2]));
}

void TestNGamma(double E, bool high = true){
  double Kmin, Kmax;

  if(high) {
    Kmin = g_threshold_gamma;
    Kmax = E;
  } else {
    Kmin = g_gamma_bs_min_energy;
    Kmax = g_threshold_gamma;
  }
  char title[50];
  sprintf(title,"E: %e", E);
  TF1* f = new TF1(title, NGamma, 0., 0.1, 3);
  f->SetParameters(Kmin, Kmax, E);

  new TCanvas();
  f->Draw();
}
