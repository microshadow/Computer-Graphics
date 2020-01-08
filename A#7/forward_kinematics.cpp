#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function
#include <iostream>

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  T.resize(skeleton.size(),Eigen::Affine3d::Identity());

  Eigen::Affine3d transformation;
  // should be inside the for loop, otherwise it would be changed everytime.
  Eigen::Affine3d R;

    for (auto i = 0; i < T.size(); ++i) {
        transformation = Eigen::Affine3d::Identity();
        R = euler_angles_to_transform(skeleton[i].xzx);

        Eigen::Affine3d res_T = skeleton[i].rest_T;
        transformation = res_T * R * res_T.inverse() * transformation;

        if (skeleton[i].parent_index != -1){
            transformation = T[skeleton[i].parent_index] * transformation;
        }
        T[i] = transformation;
    }

  /////////////////////////////////////////////////////////////////////////////
}
