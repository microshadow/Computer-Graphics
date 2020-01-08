#include "copy_skeleton_at.h"
Skeleton copy_skeleton_at(
  const Skeleton & skeleton, 
  const Eigen::VectorXd & A)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Skeleton copy = skeleton;

    for (auto i = 0; i < skeleton.size(); ++i){
        copy[i].xzx(0) = A(i * 3);
        copy[i].xzx(1) = A(i * 3 + 1);
        copy[i].xzx(2) = A(i * 3 + 2);

        copy[i].xzx_max = skeleton[i].xzx_max * 1;
        copy[i].xzx_min = skeleton[i].xzx_min * 1;
    }

  return copy;
  /////////////////////////////////////////////////////////////////////////////
}
