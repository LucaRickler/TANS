#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#endif

void CompileSimulation() {
  gROOT->ProcessLine(".L Src/Vector3D.cpp+");
  gROOT->ProcessLine(".L Src/Particle.cpp+");
  gROOT->ProcessLine(".L Src/Simulation.C+");
}
