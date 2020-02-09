#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  const double epsilon = 1e-6;
  int hit_id;
  double t;
  Eigen::Vector3d n;
  if(first_hit(ray,min_t,objects,hit_id,t,n))
  {
    rgb = blinn_phong_shading(ray,hit_id,t,n,objects,lights);
    return true;
  }
  return false;
}
