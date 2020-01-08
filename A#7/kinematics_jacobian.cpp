#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  J = Eigen::MatrixXd::Zero(b.size()*3,skeleton.size()*3);

  Eigen::VectorXd O = transformed_tips(skeleton, b);
  for (auto i = 0; i < skeleton.size(); ++i){
      for (auto j = 0; j < 3; ++j){
          Skeleton temp = skeleton;
          temp[i].xzx(j) += 0.0001;
          Eigen::VectorXd position = transformed_tips(temp, b);
          J.col(i * 3 + j) = (position - O) / 0.0001;
      }
  }  


  /////////////////////////////////////////////////////////////////////////////
}
