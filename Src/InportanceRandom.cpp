#include "InportanceRandom.h"

ClassImp(InportanceRandom)

InportanceRandom::InportanceRandom() : TObject(),
                                       func(), args_f(NULL),
                                       fbig(), args_fbig(NULL),
                                       fbig_inv(), args_fbig_inv(NULL) {}

//---------------------------------------------------------------------------//

InportanceRandom::InportanceRandom(std::function<double(double *, double *)> f, double * args_f,
                                   std::function<double(double *, double *)> fbig, double * args_fbig,
                                   std::function<double(double *, double *)> fbig_inv, double * args_fbig_inv) : TObject() {
  this->func = f;
  this->args_f = args_f;
  this->fbig = fbig;
  this->args_fbig = args_fbig;
  this->fbig_inv = fbig_inv;
  this->args_fbig_inv = args_fbig_inv;
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
      y = gRandom->Rndm()*fbig(&x, args_fbig);
    } while(y >= func(&x, args_f));

    return x;
  }
  return 0.;
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
