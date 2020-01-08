#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const {
    ////////////////////////////////////////////////////////////////////////////
    // Replace with your code here:
    Eigen::Vector3d d = ray.direction;
    // if the ray is parallel with the plane, there is no intersection
    if (d.dot(this->normal) == 0) {
        return false;
    } else {
        t = ((this->normal).dot(this->point) - (this->normal).dot(ray.origin)) / ((this->normal).dot(ray.direction));
        if (t >= min_t) {
            //n = n1 / (pow(pow(n1[0],2) + pow(n1[1],2) + pow(n1[2],2) ,0.5));
            n = this->normal;
            return true;
        } else {
            return false;
        }
        ////////////////////////////////////////////////////////////////////////////
    }
}

