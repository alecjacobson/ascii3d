#ifndef BLINN_PHONG_SHADING_H
#define BLINN_PHONG_SHADING_H
#include "Ray.h"
#include "Light.h"
#include "Object.h"
#include <Eigen/Core>
#include <vector>
#include <memory>


// Given a ray and its hit in the scene, return the Blinn-Phong shading
// contribution over all _visible_ light sources (e.g., take into account
// shadows). Use a hard-coded value of ia=0.1 for ambient light.
// 
// Inputs:
//   ray  incoming ray
//   hit_id  index into objects of the object just hit by ray
//   t  _parametric_ distance along ray to hit
//   n  unit surface normal at hit
//   objects  list of objects in the scene
//   lights  list of lights in the scene
// Returns shaded color collected by this ray as rgb 3-vector
Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights);

#endif
