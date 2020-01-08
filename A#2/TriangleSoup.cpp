#include "TriangleSoup.h"
#include "Ray.h"
// Hint
#include "first_hit.h"

bool TriangleSoup::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  double min_t_final = 999999999;
  int hit_id = -1, size = (this->triangles).size();
  Eigen::Vector3d n_final;
  for(auto i = 0; i < size; ++i){
      if((this->triangles)[i]->intersect(ray, min_t, t,n) && t >= min_t){
          if(t < min_t_final){
              min_t_final = t;
              hit_id = i;
              n_final = n;
          }
      }
  }

  if(hit_id >= 0 && hit_id < size){
      t = min_t_final;
      n = n_final;
      return true;
  }else{
      return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}



