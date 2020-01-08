#include "line_search.h"
#include <iostream>
#include <cmath>

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code

  double distance, criter;
  Eigen::VectorXd z_prim = Eigen::VectorXd::Zero(z.size());

  distance = max_step;
  while(distance > 0.0001){
      z_prim = z - distance * dz;
      proj_z(z_prim);
      criter = f(z_prim);

      if(criter < f(z)){
          return distance;
      }
      if(abs(criter - f(z)) <= 0.00001){
          return 0;
      }
      distance /= 2;
  }
  return 0;

  /////////////////////////////////////////////////////////////////////////////
}
