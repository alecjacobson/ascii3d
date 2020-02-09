#ifndef OBJECT_H
#define OBJECT_H

#include "Material.h"
#include <Eigen/Core>
#include <memory>

struct Ray;
class Object
{
  public:
    std::shared_ptr<Material> material;
    // https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
    virtual ~Object() {}
    // Intersect object with ray.
    //
    // Inputs:
    //   Ray  ray to intersect with
    //   min_t  minimum parametric distance to consider
    // Outputs:
    //   t  first intersection at ray.origin + t * ray.direction
    //   n  surface normal at point of intersection
    // Returns iff there a first intersection is found.
    //
    // The funny = 0 just ensures that this function is defined (as a no-op)
    virtual bool intersect(
        const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const = 0;
};

#endif
