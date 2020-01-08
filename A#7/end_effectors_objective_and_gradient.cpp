#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>
#include <Eigen/Dense>
#include <algorithm>

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  f = [&](const Eigen::VectorXd & A)->double
  {
      Eigen::VectorXd position = transformed_tips(copy_skeleton_at(skeleton, A), b);
      return (position - xb0).squaredNorm();
  };
  grad_f = [&](const Eigen::VectorXd & A)->Eigen::VectorXd
  {
      Eigen::VectorXd position = transformed_tips(copy_skeleton_at(skeleton, A), b);
      Eigen::VectorXd gradient = (position - xb0) * 2;

      Eigen::MatrixXd jacob;
      kinematics_jacobian(skeleton, b, jacob);

      return jacob.transpose() * gradient;
  };
  proj_z = [&](Eigen::VectorXd & A)
  {
      for (auto i = 0; i < skeleton.size(); ++i){
          A(i * 3) = std::min(std::max(A(i * 3), skeleton[i].xzx_min(0)), skeleton[i].xzx_max(0));
          A(i * 3 + 1) = std::min(std::max(A(i * 3 + 1), skeleton[i].xzx_min(1)), skeleton[i].xzx_max(1));
          A(i * 3 + 2) = std::min(std::max(A(i * 3 + 2), skeleton[i].xzx_min(2)), skeleton[i].xzx_max(2));
      }
      assert(skeleton.size() * 3 == A.size());
  };
  /////////////////////////////////////////////////////////////////////////////
}
