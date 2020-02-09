#ifndef MATERIAL_H
#define MATERIAL_H
#include <Eigen/Core>

// Blinn-Phong Approximate Shading Material Parameters
struct Material
{
  // Ambient, Diffuse, Specular, Mirror Color
  Eigen::Vector3d ka,kd,ks,km;
  // Phong exponent
  double phong_exponent;
};
#endif
