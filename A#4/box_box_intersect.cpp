#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  bool flag = true;
  Eigen::RowVector3d min_(3), max_(3);
  for(auto i = 0; i < 3; ++i){
      min_(i) = std::min(A.max_corner(i), B.max_corner(i));
      max_(i) = std::max(A.min_corner(i), B.min_corner(i));

      if(min_(i) <= max_(i)){
          flag = false;
      }
  }
  return flag;

  ////////////////////////////////////////////////////////////////////////////
}

