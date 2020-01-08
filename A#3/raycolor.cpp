#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  rgb = Eigen::Vector3d(0,0,0);

  int hit_id;
  double t;
  Eigen::Vector3d n;

  // if there is a 1st hit
  if(first_hit(ray,min_t,objects,hit_id,t,n)){
      rgb += blinn_phong_shading(ray, hit_id, t, n, objects, lights);
      // recur base case
      if(num_recursive_calls == 3){
          return true;
      }
  
      Eigen::Vector3d ref = reflect(ray.direction,n);
      Eigen::Vector3d k_m = objects[hit_id]->material->km;

      Eigen::Vector3d rgb_ref;
      Ray new_ray;
      new_ray.direction = ref;
      new_ray.origin = ray.origin + t * ray.direction;
      if(raycolor(new_ray, min_t, objects,lights,num_recursive_calls + 1,rgb_ref)){
          rgb += (k_m.array() * rgb_ref.array()).matrix();
      }else{
          return true;
    }

      
  }else{
      return false;
  }

  ////////////////////////////////////////////////////////////////////////////
}
