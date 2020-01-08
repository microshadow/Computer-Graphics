#include "euler_angles_to_transform.h"
#include <iostream>
#include <cmath>

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Eigen::Affine3d A;
  Eigen::Affine3d twist_x, bend_z, twist_bend_twist;
  Eigen::Vector3d angle = xzx * M_PI / 180;
//  A.matrix() <<
//    1,0,0,0,
//    0,1,0,0,
//    0,0,1,0,
//    0,0,0,1;

  twist_x.matrix() << 1, 0, 0, 0,
                    0, cos(angle(0)), -sin(angle(0)), 0,
                    0, sin(angle(0)), cos(angle(0)), 0,
                    0, 0, 0, 1;

  bend_z.matrix() << cos(angle(1)), -sin(angle(1)), 0, 0,
                    sin(angle(1)), cos(angle(1)), 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1;

  twist_bend_twist.matrix() << 1, 0, 0, 0,
                            0, cos(angle(2)), -sin(angle(2)), 0,
                            0, sin(angle(2)), cos(angle(2)), 0,
                            0, 0, 0, 1;

  A = twist_x * bend_z * twist_bend_twist;

  return A;
  /////////////////////////////////////////////////////////////////////////////
}
