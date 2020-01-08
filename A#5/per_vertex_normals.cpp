#include "per_vertex_normals.h"
#include "triangle_area_normal.h"
#include "vertex_triangle_adjacency.h"
#include <vector>
#include <cmath>

void per_vertex_ns(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:

  std::vector<std::vector<int>> VF;
  vertex_triangle_adjacency(F, V.rows(), VF);

  for (auto i = 0; i < V.rows(); ++i){
      Eigen::RowVector3d n(0, 0, 0);
      for (auto j = 0; j < VF[i].size(); ++j){
          int tri_i = VF[i][j];
          n = n + triangle_area_n(V.row(F(tri_i, 0)), V.row(F(tri_i, 1)), V.row(F(tri_i, 2)));
      }
      N.row(i) = n * (1.0 / sqrt(n.dot(n)));
  }

  ////////////////////////////////////////////////////////////////////////////
}
