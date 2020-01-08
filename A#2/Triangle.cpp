#include "Triangle.h"
#include "Ray.h"
#include <tuple>
#include <algorithm>
#include <Eigen/Geometry>
#include <math.h>
#include <cmath>
#include <iostream>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  double t_temp;
  Eigen::Vector3d a = std::get<0>(this->corners);
  Eigen::Vector3d b = std::get<1>(this->corners);
  Eigen::Vector3d c = std::get<2>(this->corners);
  Eigen::Vector3d d = ray.direction, e = ray.origin;
  // calculate normal, passing vertex a
  Eigen::Vector3d normal = (c - a).cross(b - a);
  if(d.dot(normal) == 0){
      std::cout << "parallel..." << std::endl;
      return false;
  }else{
      // otherwise there must be one intersection, we calculate that point's t
      t_temp = (a - e).dot(normal) / d.dot(normal);
      // thus, the point on the plane containing the triangle is:
      Eigen::Vector3d o = e + t_temp * d;
      // connecting point o with all 3 vertex
      Eigen::Vector3d a_o = o - a, b_o = o - b, c_o = o - c;

      // calculate the magnitude of each side
      double ao_mag = pow(pow(a_o[0],2) + pow(a_o[1],2) + pow(a_o[2],2), 0.5);
      double bo_mag = pow(pow(b_o[0],2) + pow(b_o[1],2) + pow(b_o[2],2), 0.5);
      double co_mag = pow(pow(c_o[0],2) + pow(c_o[1],2) + pow(c_o[2],2), 0.5);
      //std::cout << ao_mag << " " << bo_mag << " " << co_mag;

      // calculate the angle of each vertex
      double a_o_c = acos(a_o.dot(c_o) / (ao_mag * co_mag)) * 180 / M_PI;
      double b_o_c = acos(b_o.dot(c_o) / (bo_mag * co_mag)) * 180 / M_PI;
      double a_o_b = acos(a_o.dot(b_o) / (ao_mag * bo_mag)) * 180 / M_PI;
      if(a_o_c < 0){
          a_o_c *= -1;
    }
    if(b_o_c < 0){
          b_o_c *= -1;
    }
    if(a_o_b < 0){
          a_o_b *= -1;
    }

      // test if the point is inside the triangle
      double total_ang = a_o_c + b_o_c + a_o_b;
      std::cout << "angle: " << total_ang << std::endl;
      if((total_ang >= 359.9 && total_ang <= 360.1) || (total_ang >= 179.9 && total_ang <= 180.1)){
          if(t_temp >= min_t){
              t = t_temp;
              n = normal / sqrt(normal.dot(normal));
              return true;
          }
      }else{
          return false;
      }
  }

  ////////////////////////////////////////////////////////////////////////////
}


