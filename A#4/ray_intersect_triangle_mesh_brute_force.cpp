#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  hit_t = 0;
  hit_f = -1;

  double current_min_t = max_t, current_t;

  // brute force for loop over all triangles
  for(auto i = 0; i < F.rows(); ++i){
      int A_i = F(i, 0);
      int B_i = F(i, 1);
      int C_i = F(i, 2);

      Eigen::RowVector3d A(V(A_i,0), V(A_i,1), V(A_i,2));
      Eigen::RowVector3d B(V(B_i,0), V(B_i,1), V(B_i,2));
      Eigen::RowVector3d C(V(C_i,0), V(C_i,1), V(C_i,2));

      // if there is a hit
      if(ray_intersect_triangle(ray, A,B,C, min_t, max_t, current_t) && current_t <= current_min_t){
          current_min_t = current_t;
          hit_f = i;
      }
  }

  if (hit_f >= 0){
      hit_t = current_min_t;
      return true;
  } else{
      return false;
  }

  ////////////////////////////////////////////////////////////////////////////
}
