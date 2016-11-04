#ifndef VECTOR3D_H_
#define VECTOR3D_H_


class Vector3D{

public:
  Vector3D();
  Vector3D(double r, double phi, double z);
  Vector3D(const Vector3D& v);
  ~Vector3D(){}
  Vector3D& operator = (const Vector3D& v); // a che fine hai inserito questo metodo???
  const double GetR() {return this->r;}
  const double GetPhi() {return this->phi;}
  const double GetZ() {return this->z;}
  static double Dot(const Vector3D& v1, const Vector3D& v2);
  const double Dot(const Vector3D& v);
  static Vector3D Cross(const Vector3D& v1, const Vector3D& v2);
  const Vector3D Cross(const Vector3D& v);

  // vector<double> ScalarMultiplication(double l, vector<double> v1);

private:
  double r;
  double phi;
  double z;

};


#endif /* VECTOR3D_H_ */
