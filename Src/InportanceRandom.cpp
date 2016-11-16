#include "InportanceRandom.h"

ClassImp(InportanceRandom)

InportanceRandom::InportanceRandom() : TRandom3(),
                                       func(), args_f(NULL),
                                       fbig(), args_fbig(NULL),
                                       fbig_inv(), args_fbig_inv(NULL),
                                       xmin(0), xmax(0) {}

//---------------------------------------------------------------------------//

InportanceRandom::InportanceRandom(std::function<double(double *, double *)> f,
                                   double * args_f, double xmin, double xmax,
                                   std::function<double(double *, double *)> fbig,
                                   double * args_fbig) : TRandom3(seed) {
  this->func = f;
  this->args_f = args_f;
  this->fbig = fbig;
  this->args_fbig = args_fbig;
  this->fbig_inv = fbig_inv;
  this->args_fbig_inv = args_fbig_inv;
  SetInterval(xmin,xmax);
}

//---------------------------------------------------------------------------//

InportanceRandom::~InportanceRandom(){
  if(args_f) delete[] args_f;
  if(args_fbig) delete[] args_fbig;
  if(args_fbig_inv) delete[] args_fbig_inv;
}

//---------------------------------------------------------------------------//

Double_t InportanceRandom::Rndm() {
  if(func && fbig && fbig_inv){
    double x,y,u;

    do {
      u = gRandom->Rndm();
      x = fbig_inv(&u, args_fbig_inv);
      y = gRandom->Rndm()*fbig(&x, args_list);
    } while(y >= func(&x, args_list));

    return x;
  }
  return 0.;
}

//---------------------------------------------------------------------------//

void InportanceRandom::SetInterval(double xmin, double xmax) {
  this->xmin = xmin;
  this->xmax = xmax;
}

//---------------------------------------------------------------------------//

InportanceRandom* InportanceRandom::SetFArgs(double * args_f, double * args_fbig, double* args_fbig_inv) {
  if(args_f) delete[] args_f;
  if(args_fbig) delete[] args_fbig;
  if(args_fbig_inv) delete[] args_fbig_inv;

  this->args_f = args_f;
  this->args_fbig = args_fbig;
  this->args_fbig_inv = args_fbig_inv;

  return this;
}
