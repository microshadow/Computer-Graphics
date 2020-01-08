#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  Eigen::Vector3d o = ray.origin;
  Eigen::Vector3d d = ray.direction;

  // considering for vertex B, we can create two vectors across B on the plane containing the triangle.
  Eigen::RowVector3d b_a = B - A;
  Eigen::RowVector3d c_b = C - B;
  Eigen::Vector3d p;

  // now we calculate the normal
  Eigen::RowVector3d normal(3);
  normal(0) = b_a(1) * c_b(2) - b_a(2) * c_b(1);
  normal(1) = b_a(2) * c_b(0) - b_a(0) * c_b(2);
  normal(2) = b_a(0) * c_b(1) - b_a(1) * c_b(0);

  // check if t is in the range min_t to max_t
  double t1 = (B - o.transpose()).dot(normal);
  double t2 = d.transpose().dot(normal);
  double current_t = t1 / t2;

  // if it IS in the range
  if(current_t <= max_t && current_t >= min_t){
      p = o + current_t * d;
      Eigen::Vector3d p_a = A.transpose() - p;
      Eigen::Vector3d p_b = B.transpose() - p;
      Eigen::Vector3d p_c = C.transpose() - p;

      double a_p_b = acos(p_a.dot(p_b) / (sqrt(p_a.dot(p_a)) * sqrt(p_b.dot(p_b))));
      double b_p_c = acos(p_b.dot(p_c) / (sqrt(p_b.dot(p_b)) * sqrt(p_c.dot(p_c))));
      double c_p_a = acos(p_c.dot(p_a) / (sqrt(p_c.dot(p_c)) * sqrt(p_a.dot(p_a))));
      double angle_sum = a_p_b + b_p_c + c_p_a;

      if(angle_sum >= 2 * M_PI - 0.001 && angle_sum <= 2 * M_PI + 0.001){
          t = current_t;
          return true;
      }else{
          return false;
      }
  }else{
      return false;
  }

  ////////////////////////////////////////////////////////////////////////////
}

