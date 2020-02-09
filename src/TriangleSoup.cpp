#include "TriangleSoup.h"
#include "Triangle.h"
#include "first_hit.h"
#include <igl/Hit.h>
bool TriangleSoup::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  igl::Hit hit;
  if(!ei.intersectRay(
     ray.origin.cast<float>().transpose(),
     ray.direction.cast<float>().transpose(),
     hit,
     1e-4))
  {
    return false;
  }
  t = hit.t;
  if(N.rows() == F.rows())
  {
    n = N.row(hit.id).transpose();
  }else
  {
    n = 
      ((1.0-hit.u-hit.v)*N.row(F(hit.id,0))+
      hit.u*N.row(F(hit.id,1))+
      hit.v*N.row(F(hit.id,2))).normalized().transpose();
  }

  return true;
}
