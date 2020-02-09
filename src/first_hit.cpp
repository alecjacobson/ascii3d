#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  t = std::numeric_limits<double>::max();
  bool found_any = false;
  for(int i = 0;i<objects.size();i++)
  {
    double t_i;
    Eigen::Vector3d n_i;
    if(objects[i]->intersect(ray,min_t,t_i,n_i) && t_i < t)
    {
      t = t_i;
      n = n_i;
      hit_id = i;
      found_any = true;
    }
  }
  return found_any;
}
