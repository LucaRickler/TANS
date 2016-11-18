#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TH1D.h>
#include <TF1.h>
#include <TROOT.h>
#endif

enum Tests {
  InportanceRandomTest = 0,
  ParticleTest
};

void CompileSimulation() {
  gROOT->ProcessLine(".L Src/Vector3D.cpp+");
  gROOT->ProcessLine(".L Src/InportanceRandom.cpp+");
  gROOT->ProcessLine(".L Src/Particle.cpp+");
  gROOT->ProcessLine(".L Src/Simulation.C+");
}

void CompileTest(Tests test_number) {
  switch (test_number) {
    case ParticleTest:
      gROOT->ProcessLine(".L Src/Vector3D.cpp+");
      gROOT->ProcessLine(".L Src/InportanceRandom.cpp+");
      gROOT->ProcessLine(".L Src/Particle.cpp+");
      gROOT->ProcessLine(".L UnitTests/Particle_test.C+");
      break;
    case InportanceRandomTest:
      gROOT->ProcessLine(".L Src/InportanceRandom.cpp+");
      gROOT->ProcessLine(".L UnitTests/InportanceRandom_test.C+");
      break;
  }
}
