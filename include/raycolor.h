#ifndef RAYCOLOR_H
#define RAYCOLOR_H
#include "Ray.h"
#include "Object.h"
#include "Light.h"
#include <Eigen/Core>
#include <vector>

// Shoot a ray into a lit scene and collect color information.
//
// Inputs:
//   ray  ray along which to search
//   min_t  minimum t value to consider (for viewing rays, this is typically at
//     least the _parametric_ distance of the image plane to the camera)
//   objects  list of objects (shapes) in the scene
//   lights  list of lights in the scene
//   num_recursive_calls  how many times has raycolor been called already
// Outputs:
//   rgb  collected color 
// Returns true iff a hit was found
bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb);

#endif
