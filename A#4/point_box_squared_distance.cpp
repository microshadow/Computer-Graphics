#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here

  double squr_dist;
  Eigen::RowVector3d d(0, 0, 0);

  for(auto i = 0; i < 3; ++i){
      if(query(i) < box.min_corner(i)){
          d(i) = box.min_corner(i) - query(i);
      } else if(query(i) > box.max_corner(i)){
          d(i) = query(i) - box.max_corner(i);
      }
  }

  squr_dist = d.dot(d);
  return squr_dist;

  ////////////////////////////////////////////////////////////////////////////
}
