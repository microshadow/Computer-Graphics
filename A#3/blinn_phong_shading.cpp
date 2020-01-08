#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include "PointLight.h"
#include <iostream>
#include <Eigen/Core>
#include <cmath>
#include <algorithm>

using namespace std;

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:


  Eigen::Vector3d L(0,0,0);

    if(hit_id < 0){
        return L;
    }

  Eigen::Vector3d ambient(0.1,0.1,0.1);
  double power = objects[hit_id]->material->phong_exponent;
  Eigen::Vector3d k_d, k_s, k_a;
  k_d = objects[hit_id]->material->kd;
  k_s = objects[hit_id]->material->ks;
  k_a = objects[hit_id]->material->ka;
  Ray new_ray;
  double new_t, max_t;
  int new_id;
  Eigen::Vector3d new_n;

  // else we assume there is a hit
  new_ray.origin = ray.origin + t * ray.direction;
  Eigen::Vector3d v = -t * ray.direction;
  
  for(auto i = 0; i < lights.size(); ++i){

      Eigen::Vector3d I_bp = lights[i]->I;
      lights[i]->direction(new_ray.origin, new_ray.direction, max_t);
      
      if(first_hit(new_ray, pow(10.0, -7.0), objects, new_id, new_t, new_n) && new_t < max_t){
          L += 0.1 * I_bp;
    }else{
        // calculate vector h
      Eigen::Vector3d h;
      h = (new_ray.direction - ray.direction).normalized();
      Eigen::Vector3d kd_i = (k_d.array() * I_bp.array()).matrix();
      Eigen::Vector3d ks_i = (k_s.array() * I_bp.array()).matrix();
      Eigen::Vector3d ka_i = (I_bp.array() * ambient.array()).matrix();
      
      L += kd_i * max(0.0,n.dot(new_ray.direction)) + ks_i * pow(max(n.dot(h), 0.0), power) + ka_i;
    }

  }

  return L;
  ////////////////////////////////////////////////////////////////////////////
}
