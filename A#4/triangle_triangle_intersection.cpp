#include "triangle_triangle_intersection.h"
#include <vector>
#include <Eigen/Geometry>

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  Eigen::RowVector3d a_nor = (A0 - A1).cross(A2 - A1), b_nor = (B0 - B1).cross(B2 - B1);
  double d_a = -a_nor.dot(A1), d_b = -b_nor.dot(B1);
  double a0 = b_nor.dot(A0) + d_b, a1 = b_nor.dot(A1) + d_b, a2 = b_nor.dot(A2) + d_b,
  b0 = a_nor.dot(B0) + d_a, b1 = a_nor.dot(B1) + d_a, b2 = a_nor.dot(B2) + d_a;
  Eigen::RowVector3d o(0.0, 0.0, 0.0); // note: int 0 causes error here
  // the cross product of two vectors is the normal of that intersection plane (right-hand rule)
  Eigen::RowVector3d V_a0, V_a1, V_a2, V_b0, V_b1, V_b2, N = a_nor.cross(b_nor);
  o(0) = (a_nor(1) * d_b - b_nor(1) * d_a) / (a_nor(0) * b_nor(1) - b_nor(0) * a_nor(1));
  o(1) = (a_nor(0) * d_b - b_nor(0) * d_a) / (a_nor(1) * b_nor(0) - b_nor(1) * a_nor(0));

  if(a0 * a1 >= 0){
      V_a0 = A0;
      V_a1 = A1;
      V_a2 = A2;
  }else if(a1 * a2 >= 0){
      V_a0 = A2;
      V_a1 = A1;
      V_a2 = A0;
  }else if(a2 * a0 >= 0){
      V_a0 = A0;
      V_a1 = A2;
      V_a2 = A1;
  }else if(b0 * b1 >= 0){
      V_b0 = B0;
      V_b1 = B1;
      V_b2 = B2;
  }else if(b1 * b2 >= 0){
      V_b0 = B2;
      V_b1 = B1;
      V_b2 = B0;
  }else if(b2 * b0 >= 0){
      V_b0 = B0;
      V_b1 = B2;
      V_b2 = B1;
  }

  Eigen::RowVector3d V_A_02 = V_a0 - V_a2, V_A_12 = V_a1 - V_a2, V_B_02 = V_b0 - V_b2, V_B_12 = V_b1 - V_b2;
  double N_a0 = ((V_a2(0) * V_A_02(1) - V_a2(1) * V_A_02(0))
          - (o(0) * V_A_02(1) - o(1) * V_A_02(0)))
          / (N(0) * V_A_02(1) - N(1) - V_A_02(0));

  double N_a1 = ((V_a2(0) * V_A_12(1) - V_a2(1) * V_A_12(0))
                 - (o(0) * V_A_12(1) - o(1) * V_A_12(0)))
                / (N(0) * V_A_12(1) - N(1) - V_A_12(0));

  double N_b0 = ((V_a2(0) * V_B_02(1) - V_a2(1) * V_B_02(0))
                 - (o(0) * V_B_02(1) - o(1) * V_B_02(0)))
                / (N(0) * V_B_02(1) - N(1) - V_B_02(0));

  double N_b1 = ((V_a2(0) * V_B_12(1) - V_a2(1) * V_B_12(0))
                 - (o(0) * V_B_12(1) - o(1) * V_B_12(0)))
                / (N(0) * V_B_12(1) - N(1) - V_B_12(0));

  if((a0 * a1 >= 0 && a1 * a2 >= 0) || (b0 * b1 >= 0 && b1 * b1 >= 0)){
      return false;
  }

  if(std::min(N_a0, N_a1) <= std::max(N_b0, N_b1) && std::min(N_b0, N_b1) <= std::max(N_a0, N_a1)){
      return true;
  }else{
      return false;
  }

  ////////////////////////////////////////////////////////////////////////////
}
