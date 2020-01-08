#include "insert_box_into_box.h"

void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here

  Eigen::RowVector3d A_min = A.min_corner, A_max = A.max_corner;
  Eigen::RowVector3d B_min = B.min_corner, B_max = B.max_corner;

  B.min_corner = B_min.array().min(A_min.array()).matrix();
  B.max_corner = B_max.array().max(A_max.array()).matrix();

  ////////////////////////////////////////////////////////////////////////////
}

