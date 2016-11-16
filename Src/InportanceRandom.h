#ifndef INPORTANCE_RANDOM
#define INPORTANCE_RANDOM

#include <Riostream.h>
#include <TRandom3.h>
#include <TMath.h>
#include <functional>

class InportanceRandom : public TRandom3 {
public:
  InportanceRandom();
  InportanceRandom(std::function<double(double *, double *)> f, double * args_f, double xmin, double xmax,
                   std::function<double(double *, double *)> fbig, double * args_fbig,
                   std::function<double(double *, double *)> fbig_inv, double * args_fbig_inv);
  virtual ~InportanceRandom();

  virtual Double_t Rndm();
  InportanceRandom* SetFArgs(double* args_f, double* args_fbig, double* args_fbig_inv);
  void Setinterval(double, double);

private:
  function<double(double*, double*)> func;
  function<double(double*, double*)> fbig;
  function<double(double*, double*)> fbig_inv;
  double * args_f;
  double * args_fbig;
  double * args_fbig_inv;

  double xmin;
  double xmax;

  ClassDef(InportanceRandom,0)
};

#endif
