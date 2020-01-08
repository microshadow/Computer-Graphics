#include "sphere.h"
#include <iostream>
#include <cmath>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:

  V.resize((num_faces_u + 1) * (num_faces_v + 1), 3);
  F.resize(num_faces_u * num_faces_v, 4);
  UV.resize((num_faces_u + 1) * (num_faces_v + 1), 3);
  NV.resize((num_faces_u + 1) * (num_faces_v + 1), 3);
  UF.resize(num_faces_u * num_faces_v, 4);
  NF.resize(num_faces_u * num_faces_v, 4);

  double u_prim = double(1) / num_faces_u;
  double v_prim = double(1) / num_faces_v;   // 1 and 1.0 are different in C++

  for (auto i = 0; i < num_faces_v; ++i){
      for(auto j = 0; j < num_faces_u; ++j){
          double x1 = sin(M_PI - ((double)i / num_faces_v) * M_PI) * sin(((double)j / num_faces_u) * 2 * M_PI);
          double y1 = cos(M_PI - ((double)i / num_faces_v) * M_PI);
          double z1 = sin(M_PI - ((double)i / num_faces_v) * M_PI) * cos(((double)j / num_faces_u) * 2 * M_PI);

          V(i * (num_faces_u + 1) + j, 0) = x1;
          V(i * (num_faces_u+1) + j, 1) = y1;
          V(i * (num_faces_u+1) + j, 2) = z1;

          F(i * (num_faces_u) + j, 0) = i * (num_faces_u + 1) + j;
          F(i * (num_faces_u) + j, 1) = i * (num_faces_u + 1) + 1 + j;
          F(i * (num_faces_u) + j, 2) = (i + 1) * (num_faces_u + 1) + 1 + j;
          F(i * (num_faces_u) + j, 3) = (i + 1) * (num_faces_u + 1) + j;

          UV(i * (num_faces_u + 1) + j, 0) = j * u_prim;
          UV(i * (num_faces_u + 1) + j, 1) = i * v_prim;

          UF(i * (num_faces_u) + j, 0) = i * (num_faces_u + 1) + j;
          UF(i * (num_faces_u) + j, 1) = i * (num_faces_u + 1) + 1 + j;
          UF(i * (num_faces_u) + j, 2) = (i+1) * (num_faces_u + 1) + 1 + j;
          UF(i * (num_faces_u) + j, 3) = (i+1) * (num_faces_u + 1) + j;

          NV(i * (num_faces_u + 1) + j, 0) = x1;
          NV(i * (num_faces_u + 1) + j, 1) = y1;
          NV(i * (num_faces_u + 1) + j, 2) = z1;

          NF(i * (num_faces_u) + j, 0) = i * (num_faces_u + 1) + j;
          NF(i * (num_faces_u) + j, 1) = i * (num_faces_u + 1) + 1 + j;
          NF(i * (num_faces_u) + j, 2) = (i+1) * (num_faces_u + 1) + 1 + j;
          NF(i * (num_faces_u) + j, 3) = (i+1) * (num_faces_u + 1) + j;
      }
      UV(i * (num_faces_u + 1) + num_faces_u, 0) = 1;
      UV(i * (num_faces_u + 1) + num_faces_u, 1) = i * v_prim;

      /**********************************************************/
      double x2 = sin(M_PI - ((double)i / num_faces_v) * M_PI) * sin(2 * M_PI);
      double y2 = cos(M_PI - ((double)i / num_faces_v) * M_PI);
      double z2 = sin(M_PI - ((double)i / num_faces_v) * M_PI) * cos(2 * M_PI);

      V(i * (num_faces_u + 1) + num_faces_u, 0) = x2;
      V(i * (num_faces_u + 1) + num_faces_u, 1) = y2;
      V(i * (num_faces_u + 1) + num_faces_u, 2) = z2;

      NV(i * (num_faces_u + 1) + num_faces_u, 0) = x2;
      NV(i * (num_faces_u + 1) + num_faces_u, 1) = y2;
      NV(i * (num_faces_u + 1) + num_faces_u, 2) = z2;
  }

  /*******************************************************************/

  for (int j = 0; j < num_faces_u + 1; j++){
      double x3 = sin(0) * sin(((double)j / num_faces_u) * 2 * M_PI);
      double y3 = cos(0);
      double z3 = sin(0) * cos(((double)j / num_faces_u) * 2 * M_PI);

      V(num_faces_v * (num_faces_u + 1) + j, 0) = x3;
      V(num_faces_v * (num_faces_u + 1) + j, 1) = y3;
      V(num_faces_v * (num_faces_u + 1) + j, 2) = z3;

      NV(num_faces_v * (num_faces_u + 1) + j, 0) = x3;
      NV(num_faces_v * (num_faces_u + 1) + j, 1) = y3;
      NV(num_faces_v * (num_faces_u + 1) + j, 2) = z3;

      UV(num_faces_v * (num_faces_u + 1) + j, 0) = j * u_prim;
      UV(num_faces_v * (num_faces_u + 1) + j, 1) = 1;
  }

  ////////////////////////////////////////////////////////////////////////////
}
