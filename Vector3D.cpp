 #include "Vector3D.h"
//---------------------------------------------------------------------------//

Vector3D::Vector3D(){}

//---------------------------------------------------------------------------//

Vector3D::Vector3D(double r, double phi, double z){
  this->r = r;
  this->phi = phi;
  this->z = z;
}

//---------------------------------------------------------------------------//
//Mi sto chiedendo come prendere r, phi, z da v1 e v2...perché così non funziona?  
static double Dot(const Vector3D& v1, const Vector3D& v2){
  double scalar = v1.GetR()*v2.GetPhi() + v1.GetPhi()*v2.GetPhi() + v1.GetZ()*v2.GetZ();
  return scalar;
}

//---------------------------------------------------------------------------//

const double Dot(const Vector3D& v){
  return Dot(*this, v);
}

//---------------------------------------------------------------------------//

static Vector3D Cross(const Vector3D& v1, const Vector3D& v2){

   double i = v1.GetR()*v2.GetPhi() - v1.GetPhi()*v2.GetR();
   double j = -v1.GetZ()*v2.GetPhi() + v1.GetPhi()*v2.GetZ();
   double k = v1.GetZ()*v2.GetR() - v1.GetR()*v2.GetZ();

   Vector3D v3 = new Vector3D(i, j, k);
   return v3;

}

//---------------------------------------------------------------------------//

const Vector3D Cross(const Vector3D& v){
  return Cross(*this, v);
}

//---------------------------------------------------------------------------//
