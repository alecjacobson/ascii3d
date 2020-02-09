#ifndef FIRST_HIT_H
#define FIRST_HIT_H

#include "Ray.h"
#include "Object.h"
#include <Eigen/Core>
#include <vector>
#include <memory>

// Find the first (visible) hit given a ray and a collection of scene objects
//
// Inputs:
//   ray  ray along which to search
//   min_t  minimum t value to consider (for viewing rays, this is typically at
//     least the _parametric_ distance of the image plane to the camera)
//   objects  list of objects (shapes) in the scene
// Outputs:
//   hit_id  index into objects of object with first hit
//   t  _parametric_ distance along ray so that ray.origin+t*ray.direction is
//     the hit location
//   n  surface normal at hit location
// Returns true iff a hit was found
bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n);

#endif
