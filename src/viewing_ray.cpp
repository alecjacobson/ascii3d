#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  double u = -camera.width*0.5 + camera.width*(j+0.5)/double(width);
  // We want +y pointing up
  double v = -(-camera.height*0.5 + camera.height*(i+0.5)/double(height));
  ray.origin = camera.e;
  ray.direction = -camera.d*camera.w + u*camera.u + v*camera.v;
}
