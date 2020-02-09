#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"
#include <Eigen/Core>

struct Camera
{
  // Origin or "eye"
  Eigen::Vector3d e;
  // orthonormal frame so that -w is the viewing direction. 
  Eigen::Vector3d u,v,w;
  // image plane distance / focal length
  double d;
  // width and height of image plane
  double width, height;
};

#endif
