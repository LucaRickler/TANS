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
  Vector3D& operator+ (const Vector3D& v);
  Vector3D& operator+= (const Vector3D& v);
  Vector3D& operator- (const Vector3D& v);

  const double GetR() const {return this->r;}
  const double GetPhi() const {return this->phi;}
  const double GetTheta() const;
  const double GetX() const;
  const double GetY() const;
  const double GetZ() const {return this->z;}
  const double GetNorm() const;
  Vector3D GetNormalized() const;

  static const double Dot(const Vector3D& v1, const Vector3D& v2);
  const double Dot(const Vector3D& v);
  static const Vector3D Cross(const Vector3D& v1, const Vector3D& v2);
  const Vector3D Cross(const Vector3D& v);

  // const Vector3D ScalarMultiplication(double l, const Vector3D v1);

private:
  double r; // m
  double phi; // rad
  double z; // m

  ClassDef(Vector3D,1)
};


#endif /* VECTOR3D_H_ */
