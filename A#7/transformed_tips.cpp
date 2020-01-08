#include "transformed_tips.h"
#include "forward_kinematics.h"
#include <iostream>
#include <vector>

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code

  std::vector<Eigen::Affine3d, Eigen::aligned_allocator<Eigen::Affine3d>> transformation;
  forward_kinematics(skeleton, transformation);

  // return value: b * 3 vector of transformed tip position.
  Eigen::VectorXd result;
  Eigen::Vector4d tips, positions;
  result.resize(3 * b.size());

    for (auto i = 0; i < b.size(); ++i) {
        tips << skeleton[b[i]].length, 0, 0, 1;
        positions = transformation[b[i]] * skeleton[b[i]].rest_T * tips;

        // interpolate result
        result(i * 3) = positions(0) / positions(3);
        result(i * 3 + 1) = positions(1) / positions(3);
        result(i * 3 + 2) = positions(2) / positions(3);
    }

  return result;
  /////////////////////////////////////////////////////////////////////////////
}
