#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include <Eigen/Core>

class Triangle : public Object
{
  public:
    // A triangle has three corners
    std::tuple< Eigen::Vector3d, Eigen::Vector3d, Eigen::Vector3d> corners;
    // Intersect a triangle with ray.
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
