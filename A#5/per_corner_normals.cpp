#include "per_corner_normals.h"
#include "triangle_area_normal.h"
#include <vector>
#include <cmath>
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:

  std::vector<std::vector<int>> VF;
  vertex_triangle_adjacency(F, V.rows(), VF);

  for (auto i = 0; i < F.rows(); ++i){
      Eigen::RowVector3d f_normal = triangle_area_normal(V.row(F(i, 0)), V.row(F(i, 1)), V.row(F(i, 2)));
      Eigen::RowVector3d f_normal_prim = f_normal * (double(1) / sqrt(f_normal.dot(f_normal)));

      for (auto j = 0; j < 3; ++j){
          Eigen::RowVector3d normal_sum(0,0,0);

          for (auto k = 0; k < VF[F(i, j)].size(); ++k){
              int tri_i = VF[F(i, j)][k];
              Eigen::RowVector3d new_normal = triangle_area_normal(V.row(F(tri_i, 0)), V.row(F(tri_i, 1)), V.row(F(tri_i, 2)));

              Eigen::RowVector3d new_normal_prim = new_normal * (double(1) / sqrt(new_normal.dot(new_normal)));
              if (f_normal_prim.dot(new_normal_prim) > cos(corner_threshold * M_PI / 180.0)){
                  normal_sum += new_face_n;
              }
          }
          N.row(i * 3 + j) = normal_sum * (double(1) / sqrt(normal_sum.dot(normal_sum)));
      }

  }

  ////////////////////////////////////////////////////////////////////////////
}
