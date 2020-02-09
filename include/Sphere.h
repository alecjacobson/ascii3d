#ifndef SPHERE_H
#define SPHERE_H

#include "Sphere.h"
#include "Object.h"
#include <Eigen/Core>

class Sphere : public Object
{
  public:
    Eigen::Vector3d center;
    double radius;
  public:
    // Intersect sphere with ray.
    //
    // Inputs:
    //   Ray  ray to intersect with
    //   min_t  minimum parametric distance to consider
    // Outputs:
    //   t  first intersection at ray.origin + t * ray.direction
    //   n  surface normal at point of intersection
    // Returns iff there a first intersection is found.
    bool intersect(
      const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const;
};

#endif
