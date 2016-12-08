#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TH1D.h>
#include <TF1.h>
#include <TROOT.h>
#endif

enum Tests {
  ParticleTest = 0,
  BSEnergyTest
};

void CompileSimulation() {
  gROOT->ProcessLine(".L Src/Vector3D.cpp+");
  gROOT->ProcessLine(".L Src/Particle.cpp+");
  gROOT->ProcessLine(".L Src/Simulation.C+");
}

void CompileTest(Tests test_number) {
  switch (test_number) {
    case ParticleTest:
      gROOT->ProcessLine(".L Src/Vector3D.cpp+");
      gROOT->ProcessLine(".L Src/Particle.cpp+");
      gROOT->ProcessLine(".L UnitTests/Particle_test.C+");
      break;
    case BSEnergyTest:
      gROOT->ProcessLine(".L Src/Vector3D.cpp+");
      gROOT->ProcessLine(".L Src/Particle.cpp+");
      gROOT->ProcessLine(".L UnitTests/BSEnergy_test.C+");
  }
}
