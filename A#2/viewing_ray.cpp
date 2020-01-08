#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,    //   width  number of pixels width of image
  const int height,   //   height  number of pixels height of image
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here

  // the origin of ray is the eye or camera
  ray.origin = camera.e;
  // the origin of the image

  // calculate the "index" of that pixel on image coordinator
  Eigen::Vector3d img_u = (j - (double)(width - 1) / 2) / width * camera.width * camera.u;
  Eigen::Vector3d img_v = ((double)(height - 1) / 2 - i ) / height * camera.height * camera.v;
  Eigen::Vector3d img_w = camera.w * (-camera.d);

  ray.direction = img_u + img_v + img_w;

  ////////////////////////////////////////////////////////////////////////////
}

