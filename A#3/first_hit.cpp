#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
    hit_id = -1;
    int size = objects.size();
    double min_t_final = 99999999;
    Eigen::Vector3d n_final;

    for(auto i = 0; i < size; ++i){
        if(objects[i] ->intersect(ray, min_t, t, n) && (t >= min_t)){
            if(t < min_t_final){
                min_t_final = t;
                hit_id = i;
                n_final = n;
            }
        }
    }

    // Returns true iff a hit was found
    if(hit_id >= 0 && hit_id < size){
        //std::cout << "find it!" << std::endl;
        t = min_t_final;
        n = n_final;
        return true;
    }else{
        return false;
    }
  ////////////////////////////////////////////////////////////////////////////
}
