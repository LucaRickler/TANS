#include "Vector3D.h"
ClassImp(Vector3D)

//---------------------------------------------------------------------------//

Vector3D::Vector3D(){
  this->r = 0.0;
  this->phi = 0.0;
  this->z = 0.0;
}

//---------------------------------------------------------------------------//

Vector3D::Vector3D(double r, double phi, double z){
  this->r = (r >= 0.0 ? r : 0.0);
  this->phi = phi;
  this->z = z;
}

//---------------------------------------------------------------------------//

Vector3D::Vector3D(const Vector3D& other){
  this->r = other.r;
  this->phi = other.phi;
  this->z = other.z;
}

//---------------------------------------------------------------------------//

Vector3D& Vector3D::operator= (const Vector3D& other) {
  if(this == &other)
    return *this;
  delete this;
  new(this) Vector3D(other);
  return *this;
}

//---------------------------------------------------------------------------//

const double Vector3D::GetNorm () {
  return TMath::Sqrt(GetR()*GetR() + GetZ()*GetZ());
}

//---------------------------------------------------------------------------//
//Mi sto chiedendo come prendere r, phi, z da v1 e v2...perché così non funziona?
const double Vector3D::Dot(const Vector3D& v1, const Vector3D& v2){
  return v1.GetR()*v2.GetPhi() + v1.GetPhi()*v2.GetPhi() + v1.GetZ()*v2.GetZ();
}

//---------------------------------------------------------------------------//

const double Vector3D::Dot(const Vector3D& v){
  return Dot(*this, v);
}

//---------------------------------------------------------------------------//

const Vector3D Vector3D::Cross(const Vector3D& v1, const Vector3D& v2){

   double i = v1.GetR()*v2.GetPhi() - v1.GetPhi()*v2.GetR();
   double j = -v1.GetZ()*v2.GetPhi() + v1.GetPhi()*v2.GetZ();
   double k = v1.GetZ()*v2.GetR() - v1.GetR()*v2.GetZ();

   return Vector3D(i, j, k);
}

//---------------------------------------------------------------------------//

const Vector3D Vector3D::Cross(const Vector3D& v){
  return Cross(*this, v);
}

//---------------------------------------------------------------------------//
