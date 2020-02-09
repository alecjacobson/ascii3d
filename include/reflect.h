#ifndef REFLECT_H
#define REFLECT_H
#include <Eigen/Core>
// Reflect an incoming ray into an out going ray
//
// Inputs:
//   in  incoming _unit_ ray direction
//   n  surface _unit_ normal about which to reflect
// Returns outward _unit_ ray direction
Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n);
#endif 
