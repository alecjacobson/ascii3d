#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  const double epsilon = 1e-6;
  const auto material = objects[hit_id]->material;
  // Point of hit
  const Eigen::Vector3d p = ray.origin + t*ray.direction;
  const double ia = 1.0;
  Eigen::Vector3d rgb = ia*material->ka;
  for(auto light : lights)
  {
    // In a hard shadow?
    Ray shadow_ray;
    shadow_ray.origin = p;
    double max_shadow_t;
    light->direction(p,shadow_ray.direction,max_shadow_t);
    {
      int shadow_hit_id;
      double shadow_t;
      Eigen::Vector3d shadow_n;
      // getting self hits...
      if(!first_hit(shadow_ray,epsilon,objects,shadow_hit_id,shadow_t,shadow_n) || shadow_t > max_shadow_t )
      {
        // light directxion
        const Eigen::Vector3d l = shadow_ray.direction.normalized();
        const Eigen::Vector3d h = 
          (l-ray.direction.normalized()).normalized();
        rgb.array() += 
          material->kd.array() * light->I.array() *
            std::max(0.0,n.dot(l)) +
          material->ks.array() * light->I.array() *
            std::pow(std::max(0.0,n.dot(h)),material->phong_exponent);
      }
    }
  }
  return rgb;
}
