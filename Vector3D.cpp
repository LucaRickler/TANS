#include "Vector3D.h"

//---------------------------------------------------------------------------//

Vector3D::Vector3D(){}

//---------------------------------------------------------------------------//

double Vector3D::Dot(vector<double> v1, vector<double> v2){

  double scalar = 0.;
  for(int i = 0; i < 3; i++)
    scalar += v1.at(i)*v2.at(i);

  return scalar;
}

//---------------------------------------------------------------------------//

vector<double> Vector3D::Cross(vector<double> v1, vector<double> v2){

  vector<double> cross_product;

  for(int i = 0; i < 3; i++)
  switch(i){
    case 0:
    cross_product.push_back(v1.at(1)*v2.at(2) - v1.at(2)*v2.at(1));
    break;

    case 1:
    cross_product.push_back(- v1.at(0)*v2.at(2) + v1.at(2)*v2.at(0));
    break;

    case 2:
    cross_product.push_back(v1.at(0)*v2.at(1) - v1.at(1)*v2.at(0));
    break;
  }

  return cross_product;
  }

//---------------------------------------------------------------------------//

vector<double> Vector3D::ScalarMultiplication(double l, vector<double> v1){

  vector<double> by_scalar;

  for(int i = 0; i < 3; i++)
    by_scalar.push_back(v1.at(i)*l);

  return by_scalar;
}

//---------------------------------------------------------------------------//
