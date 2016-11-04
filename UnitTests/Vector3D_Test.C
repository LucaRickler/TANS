#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TCanvas.h>
#include "../Src/Vector3D.cpp"
#include <iostream>
#endif

void Vector3D_Test () {
  Vector3D v1;
  Vector3D v2(1.,0.,1.);
  Vector3D v3(1.,1.,0.);

  cout << Vector3D::Dot(v2,v3);

  v1 = v2.Cross(v3);

  cout << v1.GetNorm();

}
