#include "Vector3D.h"
ClassImp(Vector3D)

//---------------------------------------------------------------------------//

Vector3D::Vector3D(){
  this->r = 0.0;
  this->phi = 0.0;
  this->z = 0.0;
}

//---------------------------------------------------------------------------//

Vector3D::Vector3D(double r, double phi, double z, bool versor){
  this->r = (r >= 0.0 ? r : 0.0);
  while(phi < 0.0)
    phi += 2.0*TMath::Pi();
  while(phi > 2.0*TMath::Pi())
    phi -= 2.0*TMath::Pi();
  this->phi = phi;
  this->z = (z >= 0.0 ? z : 0.0);

  if(versor)
    *this = GetNormalized();
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
  //delete this;
  //new(this) Vector3D(other);
  this->r = other.GetR();
  this->phi = other.GetPhi();
  this->z = other.GetZ();
  return *this;
}

//---------------------------------------------------------------------------//

Vector3D& Vector3D::operator+ (const Vector3D& other) {
  double x = GetX() + other.GetX();
  double y = GetY() + other.GetY();
  this->r = TMath::Sqrt(x*x + y*y);
  this->phi = TMath::ATan2(y,x);
  this->z += other.GetZ();
  return *this;
}

//---------------------------------------------------------------------------//

Vector3D& Vector3D::operator+= (const Vector3D& other) {
  *this = *this + other;
  return *this;
}

//---------------------------------------------------------------------------//

Vector3D& Vector3D::operator- (const Vector3D& other) {
  double x = GetX() - other.GetX();
  double y = GetY() - other.GetY();
  this->r = TMath::Sqrt(x*x + y*y);
  this->phi = TMath::ATan2(y,x);
  this->z -= other.GetZ();
  return *this;
}

//---------------------------------------------------------------------------//

const double Vector3D::GetTheta() const {
  return TMath::ATan2(GetR(),GetZ());
}

//---------------------------------------------------------------------------//

const double Vector3D::GetX() const {
  return GetR()*TMath::Cos(GetPhi());
}

//---------------------------------------------------------------------------//

const double Vector3D::GetY() const {
  return GetR()*TMath::Sin(GetPhi());
}

//---------------------------------------------------------------------------//

const double Vector3D::GetNorm () const {
  return TMath::Sqrt(GetR()*GetR() + GetZ()*GetZ());
}

//---------------------------------------------------------------------------//

Vector3D Vector3D::GetNormalized () const {
  double r = GetR()/GetNorm();
  double z = GetZ()/GetNorm();
  return Vector3D(r, GetPhi(), z);
}

//---------------------------------------------------------------------------//

const double Vector3D::Dot(const Vector3D& v1, const Vector3D& v2){
  return v1.GetX()*v2.GetX() + v1.GetY()*v2.GetY() + v1.GetZ()*v2.GetZ();
}

//---------------------------------------------------------------------------//

const double Vector3D::Dot(const Vector3D& v){
  return Dot(*this, v);
}

//---------------------------------------------------------------------------//

const Vector3D Vector3D::Cross(const Vector3D& v1, const Vector3D& v2){

   double x = v1.GetX()*v2.GetY() - v1.GetY()*v2.GetX();
   double y = -v1.GetZ()*v2.GetY() + v1.GetY()*v2.GetZ();
   double z = v1.GetZ()*v2.GetX() - v1.GetX()*v2.GetZ();

   double r = TMath::Sqrt(x*x + y*y);
   double phi = TMath::ATan2(y,x);

   return Vector3D(r, phi, z);
}

//---------------------------------------------------------------------------//

const Vector3D Vector3D::Cross(const Vector3D& v){
  return Cross(*this, v);
}

//---------------------------------------------------------------------------//
