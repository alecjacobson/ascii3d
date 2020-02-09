#ifndef TRIANGLE_SOUP_H
#define TRIANGLE_SOUP_H

#include "Object.h"
#include <igl/embree/EmbreeIntersector.h>
#include <Eigen/Core>
#include <memory>
#include <vector>

// Forward declaration
class TriangleSoup : public Object
{
  public:
    igl::embree::EmbreeIntersector ei;
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    Eigen::MatrixXd N;

    // Intersect a triangle soup with ray.
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

