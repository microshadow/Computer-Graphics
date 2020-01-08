#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  I = -1;
  sqrD = std::numeric_limits<double>::infinity();

  // brute force foor loop
  for(auto i = 0; i < points.rows(); ++i){
      Eigen::RowVector3d p(points(i, 0), points(i, 1), points(i, 2));
      double d = (p - query).dot(p - query);

      if(d < sqrD || d == sqrD){
          sqrD = d;
          I = i;
      }
  }

  ////////////////////////////////////////////////////////////////////////////
}
