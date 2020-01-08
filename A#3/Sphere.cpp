#include "Sphere.h"
#include "Ray.h"

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
    // to calculate discriminant
    Eigen::Vector3d d = ray.direction;
    Eigen::Vector3d e_c = ray.origin - (this->center);
    double A = d.dot(d);
    double B = 2 * d.dot(e_c);
    double C = e_c.dot(e_c) - pow(this->radius, 2);
    double t1, t2;

    double discriminant = pow(B,2) - 4 * A * C;

    if(discriminant >= 0){
        t1 = (-B - pow(discriminant,0.5)) / (2 * A);
        t2 = (-B + pow(discriminant,0.5)) / (2 * A);
        if(t1 == t2){
            Eigen::Vector3d p = ray.origin + t1 * ray.direction;
            t = t1;
            n = (p - this->center) / (this->radius);
            return true;
        }else{
            if((t1 < t2) && (t1 >= min_t)){
                Eigen::Vector3d p = ray.origin + t1 * ray.direction;
                t = t1;
                n = (p - this->center) / (this->radius);
                return true;
            }else if((t1 > t2) && (t2 >= min_t)){
                Eigen::Vector3d p = ray.origin + t2 * ray.direction;
                t = t2;
                n = (p - this->center) / (this->radius);
            }
        }
    }else{
        return false;
    }
  ////////////////////////////////////////////////////////////////////////////
}

