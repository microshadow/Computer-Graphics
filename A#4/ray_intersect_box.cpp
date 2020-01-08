#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  double current_min, current_max, min_x, max_x, min_y, max_y, min_z, max_z;
  double x = 1.0 / ray.direction(0);   // note: 1 instead of 1.0 would cause error here
  double y = 1.0 / ray.direction(1);
  double z = 1.0 / ray.direction(2);
  Eigen::Vector3d o = ray.origin;
  Eigen::RowVector3d min_c = box.min_corner;
  Eigen::RowVector3d max_c = box.max_corner;

  // considering x axis
  if(x >= 0){
      min_x = x * (min_c(0) - o(0));
      max_x = x * (max_c(0) - o(0));
  }else{
      min_x = x * (max_c(0) - o(0));
      max_x = x * (min_c(0) - o(0));
  }

  // now considering y axis
  if(y >= 0){
      min_y = y * (min_c(1) - o(1));
      max_y = y * (max_c(1) - o(1));
  }else{
      min_y = y * (max_c(1) - o(1));
      max_y = y * (min_c(1) - o(1));
  }

  // finally, the z axis
  if(z >= 0){
      min_z = z * (min_c(2) - o(2));
      max_z = z * (max_c(2) - o(2));
  }else{
      min_z = z * (max_c(2) - o(2));
      max_z = z * (min_c(2) - o(2));
  }

  current_min = std::max(min_x, std::max(min_y, min_z));
  current_max = std::min(max_x, std::min(max_y, max_z));

  return current_max >= current_min && current_min <= max_t && current_max >= min_t;

  ////////////////////////////////////////////////////////////////////////////
}
