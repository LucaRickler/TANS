#ifndef VECTOR3D_H_
#define VECTOR3D_H_


#include <TMath.h>
#include <TObject.h>

class Vector3D : public TObject{
public:
  Vector3D();
  Vector3D(double r, double phi, double z, bool versor = false);
  Vector3D(const Vector3D& v);
  ~Vector3D(){}
  Vector3D& operator= (const Vector3D& v);
  Vector3D operator+ (const Vector3D& v);
  Vector3D& operator+= (const Vector3D& v);
  Vector3D operator- (const Vector3D& v);
  Vector3D operator* (const double& a);
  Vector3D& operator*= (const double& a);

  double GetR() const {return this->r;}
  double GetPhi() const {return this->phi;}
  double GetTheta() const;
  double GetX() const;
  double GetY() const;
  double GetZ() const {return this->z;}
  double GetNorm() const;
  Vector3D GetNormalized() const;

  static double Dot(const Vector3D& v1, const Vector3D& v2);
  double Dot(const Vector3D& v);
  static Vector3D Cross(const Vector3D& v1, const Vector3D& v2);
  Vector3D Cross(const Vector3D& v);

private:
  double r; // m
  double phi; // rad
  double z; // m

  ClassDef(Vector3D,1)
};


#endif /* VECTOR3D_H_ */
