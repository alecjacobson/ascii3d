#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  // plane equation (q-p)⋅n = 0
  // subsititue (o+t*d-p)⋅n = 0
  // solve for -(o-p)⋅n/(d⋅n) 
  t = -(ray.origin - point).dot(normal) / (ray.direction.dot(normal));
  if(t>=min_t)
  {
    n = normal;
    return true;
  }
  return false;
}

