#ifndef LIGHT_H
#define LIGHT_H
#include <Eigen/Core>
class Light
{
  public:
    // Color (intensities)
    Eigen::Vector3d I;
    // https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
    virtual ~Light() {};
    // Given a query point return the direction _toward_ the Light.
    //
    // Input:
    //   q  3D query point in space
    // Outputs:
    //    d  3D direction from point toward light as a vector.
    //    max_t  parametric distance from q along d to light (may be inf)
    virtual void direction(
      const Eigen::Vector3d & q, 
      Eigen::Vector3d & d, 
      double & max_t) const =0;
};
#endif
