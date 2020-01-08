#include <Eigen/Core>
#include <Eigen/Geometry>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  Eigen::Vector3d d;
  d = in.normalized();
  
  Eigen::Vector3d new_n = (-1.0 * n).normalized();
  Eigen::Vector3d r = d - 2 * (d.dot(new_n)) * new_n;
  return r.normalized();


  ////////////////////////////////////////////////////////////////////////////
}
