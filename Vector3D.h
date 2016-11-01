#ifndef VECTOR3D_H_
#define VECTOR3D_H_


class Vector3D{

public:
  Vector3D();
  double Dot(vector<double> v1, vector<double> v2);
  vector<double> Cross(vector<double> v1, vector<double> v2);
  vector<double> ScalarMultiplication(double l, vector<double> v1);

private:
  vector<double> old_position;
  vector<double> position;

};


#endif /* VECTOR3D_H_ */
