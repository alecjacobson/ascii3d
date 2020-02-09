#include "Sphere.h"
#include "Ray.h"

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  const double A = ray.direction.squaredNorm();
  const Eigen::Vector3d disp = ray.origin - center;
  const double B = 2.*ray.direction.dot(disp);
  const double C = disp.squaredNorm() - radius*radius;
  double discriminant = B*B - 4.*A*C;
  if(discriminant <= 0)
  {
    return false;
  }
  // smaller of the two solutions
  t = (-B - sqrt(discriminant))/(2.*A);
  if(t < min_t)
  {
    // we're inside the sphere. Use larger option.
    t = (-B + sqrt(discriminant))/(2.*A);
  }
  if(t < min_t)
  {
    // we're still  too close
    return false;
  }
  const Eigen::Vector3d hit = ray.origin + t * ray.direction;
  n = (hit-center)/radius;
  return true;
}

