#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Light.h"
#include <Eigen/Core>
class PointLight : public Light
{
  public:
    Eigen::Vector3d p;
    // Given a query point return the direction _toward_ the Light.
    //
    // Input:
    //   q  3D query point in space
    // Outputs:
    //    d  3D direction from point toward light as a vector.
    //    max_t  parametric distance from q along d to light (may be inf)
    void direction(
      const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const;
};
#endif

